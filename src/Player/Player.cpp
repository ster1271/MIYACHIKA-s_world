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

const float MAX_JUMP_Y[PLAYER_JUMP_POWER_NUM] = { 3.0f,4.0f,5.0f };

//==================================================

// コンストラクタ・デストラクタ
CPlayer::CPlayer()
{
	m_iHndl = -1;
	m_eJumpPower = JUMP_POWER_1;
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_fSpeed = 0.0f;
	m_fYSpeed = 0.0f;
}
CPlayer::~CPlayer() {}

// 初期化
void CPlayer::Init()
{
	m_iHndl = LoadGraph(PLAYER_FILE_PATH);
	m_fPosX = INIT_POS_X;
	m_fPosY = INIT_POS_Y;
	m_fSpeed = SPEED;
	m_fYSpeed = MAX_JUMP_Y[m_eJumpPower];
}

// 通常処理
void CPlayer::Step()
{
	Move();
	Jump();
}

// 描画処理
void CPlayer::Draw()
{
	DrawGraph((int)m_fPosX, (int)m_fPosY, m_iHndl, true);
	DrawLine(0, (float)SCREEN_SIZE_Y - PLAYER_SIZE, SCREEN_SIZE_X, (float)SCREEN_SIZE_Y - PLAYER_SIZE, RED);
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
	if (Input::Key::Push(KEY_INPUT_SPACE))
	{
		m_fYSpeed = -MAX_JUMP_Y[m_eJumpPower];
	}

	m_fYSpeed += GRAVITY;

	if (m_fYSpeed > MAX_JUMP_Y[m_eJumpPower])
	{
		m_fYSpeed = MAX_JUMP_Y[m_eJumpPower];
	}

	m_fPosY += m_fYSpeed;

	float fFloorPos = (float)SCREEN_SIZE_Y - PLAYER_SIZE * 2.0f;
	if (m_fPosY >= fFloorPos)
	{
		m_fPosY = fFloorPos;
	}
}

// マップに当たった時
void CPlayer::HitMapCalc_X(float iPlusorMinus)
{
	m_fPosX += SPEED * iPlusorMinus;
}
void CPlayer::HitMapCalc_Y(float iPlusorMinus)
{
	m_fPosY += SPEED * iPlusorMinus;
}