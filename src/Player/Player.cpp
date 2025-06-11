#include "Player.h"
#include "../Common.h"
#include "../Input/Input.h"

//==================================================
// ��`�֘A

PLAYER_JUMP_POWER CPlayer::m_eJumpPower;

// �v���C���[�������W
const float INIT_POS_X = (float)(SCREEN_SIZE_X / 2);
const float INIT_POS_Y = (float)(SCREEN_SIZE_Y / 2);

// �v���C���[���x
const float SPEED = 2.0f;

// �v���C���[�d��
const float GRAVITY = 0.1f;

const float MAX_JUMP_Y[PLAYER_JUMP_POWER_NUM] = { 3.0f,4.0f,5.0f };

//==================================================

// �R���X�g���N�^�E�f�X�g���N�^
CPlayer::CPlayer()
{
	m_eJumpPower = JUMP_POWER_1;
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_fSpeed = 0.0f;
	m_fYSpeed = 0.0f;
}
CPlayer::~CPlayer() {}

// ������
void CPlayer::Init()
{
	m_fPosX = INIT_POS_X;
	m_fPosY = INIT_POS_Y;
	m_fSpeed = SPEED;
	m_fYSpeed = MAX_JUMP_Y[m_eJumpPower];
}

// �ʏ폈��
void CPlayer::Step()
{
	Move();
	Jump();
}

// �`�揈��
void CPlayer::Draw()
{
	DrawBox((int)m_fPosX, (int)m_fPosY, (int)(m_fPosX + PLAYER_SIZE), (int)(m_fPosY + PLAYER_SIZE), WHITE, true);
	DrawLine(0, (float)SCREEN_SIZE_Y - PLAYER_SIZE, SCREEN_SIZE_X, (float)SCREEN_SIZE_Y - PLAYER_SIZE, RED);
}

// �I������
void CPlayer::Fin()
{
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_fSpeed = 0.0f;
	m_fYSpeed = 0.0f;
}

//====================
//      �@�֐�
//====================
// �ړ�����
void CPlayer::Move()
{
	// ���ɓ���
	if (Input::Key::Keep(KEY_INPUT_A))
	{
		m_fPosX -= SPEED;
	}
	else if (Input::Key::Keep(KEY_INPUT_D))
	{
		m_fPosX += SPEED;
	}
}

// �W�����v����
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