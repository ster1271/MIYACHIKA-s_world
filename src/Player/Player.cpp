#include "Player.h"
#include "../Common.h"
#include "../Input/Input.h"

//==================================================
// ��`�֘A

// �v���C���[�̉摜�t�@�C���p�X
const char PLAYER_FILE_PATH[] = { "data/Player/�v���C���[(��).png" };

// �v���C���[�������W
const float INIT_POS_X = (float)(SCREEN_SIZE_X / 2);
const float INIT_POS_Y = (float)(SCREEN_SIZE_Y / 2);

// �v���C���[���x
const float SPEED = 2.0f;

// �v���C���[�d��
const float GRAVITY = 0.1f;

// Y�������x�̍ŏ�
const float MIN_YSPEED = 0.3;

// �W�����v�p���[
const float MAX_JUMP_Y[PLAYER_JUMP_POWER_NUM] = { 3.0f,4.0f,5.0f };

// ���̒l���f�B���C����
const int DELAY_NUM = 30;

//==================================================

// �R���X�g���N�^�E�f�X�g���N�^
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

// ������
void CPlayer::Init(VECTOR vStartPos)
{
	m_iHndl = LoadGraph(PLAYER_FILE_PATH);
	m_fPosX = vStartPos.x;
	m_fPosY = vStartPos.y;
	m_fSpeed = SPEED;
	m_fYSpeed = MAX_JUMP_Y[m_eJumpPower];
}

// �ʏ폈��
void CPlayer::Step()
{
	Move();
	Jump();
	Direction();
	AddDelayCnt();
}

// �`�揈��
void CPlayer::Draw()
{
	DrawGraph((int)m_fPosX, (int)m_fPosY, m_iHndl, true);
}

// �I������
void CPlayer::Fin()
{
	DeleteGraph(m_iHndl);
	m_iHndl = -1;

	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_fSpeed = 0.0f;
	m_fYSpeed = 0.0f;
}

// �X�V����
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

// �v���C���[�̕���
void CPlayer::Direction()
{
	// ������̃`�F�b�N
	if (m_fYSpeed < 0.0f && m_fPosY < m_fOldPosY)
	{
		m_bDir[PLAYER_UP] = true;
	}
	// �������̃`�F�b�N
	if (m_fYSpeed > MIN_YSPEED && m_fPosY > m_fOldPosY)
	{
		m_bDir[PLAYER_DOWN] = true;
	}
	// �������̃`�F�b�N
	if (m_fPosX < m_fOldPosX) 
	{
		m_bDir[PLAYER_LEFT] = true;
	}
	// �E�����̃`�F�b�N
	if (m_fPosX > m_fOldPosX) 
	{
		m_bDir[PLAYER_RIGHT] = true;
	}
}

// �f�B���C�J�E���g�����Z
void CPlayer::AddDelayCnt()
{
	if (m_iDelayCnt < DELAY_NUM)
	{
		m_iDelayCnt++;
	}
}

// �}�b�v�ɓ���������
void CPlayer::HitMapX(float fOverlap)
{
	m_fPosX = fOverlap;
}
void CPlayer::HitMapY(float fOverlap)
{
	m_fPosY = fOverlap;
}

// �v���C���[�̏㑤������������
void CPlayer::HitUpperSide()
{
	m_fYSpeed = 0.0f;
}

// �v���C���[�̉���������������
void CPlayer::HitLowerSide()
{
	m_fYSpeed = MIN_YSPEED;
}

// �W�����v�u���b�N�ɓ���������
void CPlayer::HitJumpBlock(PLAYER_JUMP_POWER JumpPower)
{
	m_eJumpPower = JumpPower;
	m_fYSpeed = -MAX_JUMP_Y[m_eJumpPower];
	m_iDelayCnt = 0;
}

// �v���C���[�̏㑤���W�����v�u���b�N�ɓ���������
void CPlayer::HitJumpBlockUpperSide()
{
	m_iDelayCnt = 0;
}

//====================
//   �擾�E�ݒ�֘A
//====================
// �f�B���C������
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