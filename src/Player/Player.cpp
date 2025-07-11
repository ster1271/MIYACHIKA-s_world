#include "Player.h"
#include "../Common.h"
#include "../Input/Input.h"
#include "PlayerData.h"
#include "../SoundManager/SoundManager.h"


//==================================================
// 定義関連

// プレイヤー速度
const float SPEED = 2.0f;

// プレイヤー重力
const float GRAVITY = 0.1f;

// Y軸加速度の最小
const float MIN_YSPEED = 0.3;

// ジャンプパワー
const float MAX_JUMP_Y[PLAYER_JUMP_POWER_NUM] = { 2.7f,3.65f,4.5f };

// この値分ディレイする
const int DELAY_NUM = 20;

//==================================================

// コンストラクタ・デストラクタ
CPlayer::CPlayer()
{
	m_eJumpPower = JUMP_POWER_1;
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_fOldPosX = 0.0f;
	m_fOldPosY = 0.0f;
	m_fSpeed = 0.0f;
	m_fYSpeed = 0.0f;
	m_iDelayCnt = 0;
	secount = 0;

	for (int i = 0; i < PLAYER_DIRECTION_NUM; i++)
	{
		m_bDir[i] = false;
	}
}
CPlayer::~CPlayer() {}

// 初期化
void CPlayer::Init(VECTOR vStartPos)
{
	m_fPosX = vStartPos.x;
	m_fPosY = vStartPos.y;
	m_fSpeed = SPEED;
	m_fYSpeed = MAX_JUMP_Y[m_eJumpPower];

	cAnimation.Init(m_fPosX, m_fPosY);
	CPlayerData::Init();
}

// 通常処理
void CPlayer::Step()
{
	Move();
	Jump();
	Direction();
	AddDelayCnt();

	cAnimation.Step();
}

// 描画処理
void CPlayer::Draw()
{
	cAnimation.Draw();

	DrawFormatString(0,  60, GREEN, "ジャンプ回数 : %d", CPlayerData::GetInstance()->GetJumpCnt());
	DrawFormatString(0,  80, GREEN, "クリア回数　 : %d", CPlayerData::GetInstance()->GetClearStage());
	DrawFormatString(0, 100, GREEN, "死んだ回数　 : %d", CPlayerData::GetInstance()->GetDeathCnt());
}

// 終了処理
void CPlayer::Fin()
{
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_fSpeed = 0.0f;
	m_fYSpeed = 0.0f;

	cAnimation.Fin();
	CPlayerData::DeleteInstance();
}

// 更新処理
void CPlayer::Update()
{
	m_fOldPosX = m_fPosX;
	m_fOldPosY = m_fPosY;

	cAnimation.Update(m_fPosX, m_fPosY);

	for (int i = 0; i < PLAYER_DIRECTION_NUM; i++)
	{
		m_bDir[i] = false;
	}
}

//====================
//      　関数
//====================

// 移動処理
void CPlayer::Move()
{
	// 左に動く
	if (Input::Key::Keep(KEY_INPUT_A))
	{
		m_fPosX -= SPEED;
		cAnimation.isRight(false);
		if (cAnimation.GetID() != PLAYER_STATE::JUMP)
		{
			cAnimation.ChangeID(PLAYER_STATE::WALK);
		}
	}
	// 右に動く
	else if (Input::Key::Keep(KEY_INPUT_D))
	{
		m_fPosX += SPEED;
		cAnimation.isRight(true);
		if (cAnimation.GetID() != PLAYER_STATE::JUMP)
		{
			cAnimation.ChangeID(PLAYER_STATE::WALK);
		}
	}
	// 動いていなかったら
	else
	{
		if (cAnimation.GetID() != PLAYER_STATE::JUMP)
		{
			cAnimation.ChangeID(PLAYER_STATE::FRONT);
		}
	}
}

// ジャンプ処理
void CPlayer::Jump()
{
	/*手動ジャンプ
	if (Input::Key::Push(KEY_INPUT_SPACE))
	{
		m_fYSpeed = -MAX_JUMP_Y[m_eJumpPower];
	}*/

	if (m_fYSpeed < MAX_JUMP_Y[m_eJumpPower])
	{
		m_fYSpeed += GRAVITY;
	}
	else
	{
		cAnimation.ChangeID(PLAYER_STATE::FRONT);
	}

	m_fPosY += m_fYSpeed;
}

// プレイヤーの方向
void CPlayer::Direction()
{
	// 上方向のチェック
	if (m_fYSpeed < 0.0f && m_fPosY < m_fOldPosY)
	{
		m_bDir[PLAYER_UP] = true;
	}
	// 下方向のチェック
	if (m_fYSpeed > MIN_YSPEED && m_fPosY > m_fOldPosY)
	{
		m_bDir[PLAYER_DOWN] = true;
	}
	// 左方向のチェック
	if (m_fPosX < m_fOldPosX)
	{
		m_bDir[PLAYER_LEFT] = true;
	}
	// 右方向のチェック
	if (m_fPosX > m_fOldPosX)
	{
		m_bDir[PLAYER_RIGHT] = true;
	}
}

// ディレイカウントを加算
void CPlayer::AddDelayCnt()
{
	if (m_iDelayCnt < DELAY_NUM)
	{
		m_iDelayCnt++;
	}
}

// マップに当たった時
void CPlayer::HitMapX(float fOverlap)
{
	m_fPosX = fOverlap;
}
void CPlayer::HitMapY(float fOverlap)
{
	m_fPosY = fOverlap;
}

// プレイヤーの上側が当たった時
void CPlayer::HitUpperSide()
{
	m_fYSpeed = 0.0f;
}

// プレイヤーの下側が当たった時
void CPlayer::HitLowerSide()
{
	m_fYSpeed = MIN_YSPEED;

	// 歩いていなかったら
	if (cAnimation.GetID() != PLAYER_STATE::WALK)
	{
		// 前を向く
		cAnimation.ChangeID(PLAYER_STATE::FRONT);
		secount++;
		if (secount <= 1) {
			SoundManager::Play(SoundKind::LANDING);  //着地SE
		}
	}
}

// ジャンプブロックに当たった時
void CPlayer::HitJumpBlock(PLAYER_JUMP_POWER JumpPower)
{
	m_eJumpPower = JumpPower;
	m_fYSpeed = -MAX_JUMP_Y[m_eJumpPower];
	cAnimation.ChangeID(PLAYER_STATE::JUMP);
	m_iDelayCnt = 0;
	secount = 0;
	SoundManager::Play(SoundKind::JANP);       //ジャンプSE
	SoundManager::Play(SoundKind::JANPBLOAK);  //ジャンプブロックSE

	// ジャンプ数を加算
	CPlayerData::GetInstance()->AddJumpCnt();
}

// プレイヤーの上側がジャンプブロックに当たった時
void CPlayer::HitJumpBlockUpperSide()
{
	m_iDelayCnt = 0;
}

// とげに当たったら
void CPlayer::HitThorn(float fStartPosX, float fStartPosY)
{
	// スタート位置に戻す
	m_fPosX = fStartPosX;
	m_fPosY = fStartPosY;
	SoundManager::Play(SoundKind::THORN);  //とげSE
	SoundManager::Play(SoundKind::POTAL);

	m_fSpeed = 0.0f;
	m_fYSpeed = 0.0f;

	// 死亡数を加算
	CPlayerData::GetInstance()->AddDeathCnt();
}

// ゴールに当たったら
void CPlayer::HitGoal(float fStartPosX, float fStartPosY)
{
	// スタート位置に設定する
	m_fPosX = fStartPosX;
	m_fPosY = fStartPosY;

	m_fSpeed = 0.0f;
	m_fYSpeed = 0.0f;
	secount = 0;
	SoundManager::Play(SoundKind::POTAL);

	// クリア数を加算
	CPlayerData::GetInstance()->AddClearStage();
}

//====================
//   取得・設定関連
//====================
// ディレイしたか
bool CPlayer::GetDelay()
{
	if (m_iDelayCnt >= DELAY_NUM)
	{
		return true;
	}
	else
	{
		return false;
	}
}