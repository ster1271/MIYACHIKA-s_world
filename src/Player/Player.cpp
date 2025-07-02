#include "Player.h"
#include "../Common.h"
#include "../Input/Input.h"

//==================================================
// 定義関連

// プレイヤーの画像ファイルパス
const char PLAYER_FILE_PATH[] = { "data/Player/プレイヤー(仮).png" };

// プレイヤー初期座標
const float INIT_POS_X = (float)(SCREEN_SIZE_X / 2);
const float INIT_POS_Y = (float)(SCREEN_SIZE_Y / 2);

// プレイヤー速度
const float SPEED = 2.0f;

// プレイヤー重力
const float GRAVITY = 0.1f;

// Y軸加速度の最小
const float MIN_YSPEED = 0.3;

// ジャンプパワー
const float MAX_JUMP_Y[PLAYER_JUMP_POWER_NUM] = { 3.0f,4.0f,5.0f };

// この値分ディレイする
const int DELAY_NUM = 30;

//==================================================

// コンストラクタ・デストラクタ
CPlayer::CPlayer()
{
	m_iHndl = -1;
	m_eJumpPower = JUMP_POWER_1;
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_fOldPosX = 0.0f;
	m_fOldPosY = 0.0f;
	m_fSpeed = 0.0f;
	m_fYSpeed = 0.0f;
	m_iDelayCnt = 0;

	for (int i = 0; i < PLAYER_DIRECTION_NUM; i++)
	{
		m_bDir[i] = false;
	}
}
CPlayer::~CPlayer() {}

// 初期化
void CPlayer::Init(VECTOR vStartPos)
{
	m_iHndl = LoadGraph(PLAYER_FILE_PATH);
	m_fPosX = vStartPos.x;
	m_fPosY = vStartPos.y;
	m_fSpeed = SPEED;
	m_fYSpeed = MAX_JUMP_Y[m_eJumpPower];
}

// 通常処理
void CPlayer::Step()
{
	Move();
	Jump();
	Direction();
	AddDelayCnt();
}

// 描画処理
void CPlayer::Draw()
{
	DrawGraph((int)m_fPosX, (int)m_fPosY, m_iHndl, true);
}

// 終了処理
void CPlayer::Fin()
{
	DeleteGraph(m_iHndl);
	m_iHndl = -1;

	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_fSpeed = 0.0f;
	m_fYSpeed = 0.0f;
}

// 更新処理
void CPlayer::Update()
{
	m_fOldPosX = m_fPosX;
	m_fOldPosY = m_fPosY;

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
	}
	else if (Input::Key::Keep(KEY_INPUT_D))
	{
		m_fPosX += SPEED;
	}
}

// ジャンプ処理
void CPlayer::Jump()
{
	/*if (Input::Key::Push(KEY_INPUT_SPACE))
	{
		m_fYSpeed = -MAX_JUMP_Y[m_eJumpPower];
	}*/

	if (m_fYSpeed < MAX_JUMP_Y[m_eJumpPower])
	{
		m_fYSpeed += GRAVITY;
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
}

// ジャンプブロックに当たった時
void CPlayer::HitJumpBlock(PLAYER_JUMP_POWER JumpPower)
{
	m_eJumpPower = JumpPower;
	m_fYSpeed = -MAX_JUMP_Y[m_eJumpPower];
	m_iDelayCnt = 0;
}

// プレイヤーの上側がジャンプブロックに当たった時
void CPlayer::HitJumpBlockUpperSide()
{
	m_iDelayCnt = 0;
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