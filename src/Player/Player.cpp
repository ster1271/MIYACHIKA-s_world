#include "Player.h"
#include "../Common.h"
#include "../Input/Input.h"
#include "PlayerData.h"
#include "../SoundManager/SoundManager.h"


//==================================================
// ��`�֘A

// �v���C���[���x
const float SPEED = 2.0f;

// �v���C���[�d��
const float GRAVITY = 0.1f;

// Y�������x�̍ŏ�
const float MIN_YSPEED = 0.3;

// �W�����v�p���[
const float MAX_JUMP_Y[PLAYER_JUMP_POWER_NUM] = { 2.7f,3.65f,4.5f };

// ���̒l���f�B���C����
const int DELAY_NUM = 20;

//==================================================

// �R���X�g���N�^�E�f�X�g���N�^
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

// ������
void CPlayer::Init(VECTOR vStartPos)
{
	m_fPosX = vStartPos.x;
	m_fPosY = vStartPos.y;
	m_fSpeed = SPEED;
	m_fYSpeed = MAX_JUMP_Y[m_eJumpPower];

	cAnimation.Init(m_fPosX, m_fPosY);
	CPlayerData::Init();
}

// �ʏ폈��
void CPlayer::Step()
{
	Move();
	Jump();
	Direction();
	AddDelayCnt();

	cAnimation.Step();
}

// �`�揈��
void CPlayer::Draw()
{
	cAnimation.Draw();

	DrawFormatString(0,  60, GREEN, "�W�����v�� : %d", CPlayerData::GetInstance()->GetJumpCnt());
	DrawFormatString(0,  80, GREEN, "�N���A�񐔁@ : %d", CPlayerData::GetInstance()->GetClearStage());
	DrawFormatString(0, 100, GREEN, "���񂾉񐔁@ : %d", CPlayerData::GetInstance()->GetDeathCnt());
}

// �I������
void CPlayer::Fin()
{
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_fSpeed = 0.0f;
	m_fYSpeed = 0.0f;

	cAnimation.Fin();
	CPlayerData::DeleteInstance();
}

// �X�V����
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
//      �@�֐�
//====================

// �ړ�����
void CPlayer::Move()
{
	// ���ɓ���
	if (Input::Key::Keep(KEY_INPUT_A))
	{
		m_fPosX -= SPEED;
		cAnimation.isRight(false);
		if (cAnimation.GetID() != PLAYER_STATE::JUMP)
		{
			cAnimation.ChangeID(PLAYER_STATE::WALK);
		}
	}
	// �E�ɓ���
	else if (Input::Key::Keep(KEY_INPUT_D))
	{
		m_fPosX += SPEED;
		cAnimation.isRight(true);
		if (cAnimation.GetID() != PLAYER_STATE::JUMP)
		{
			cAnimation.ChangeID(PLAYER_STATE::WALK);
		}
	}
	// �����Ă��Ȃ�������
	else
	{
		if (cAnimation.GetID() != PLAYER_STATE::JUMP)
		{
			cAnimation.ChangeID(PLAYER_STATE::FRONT);
		}
	}
}

// �W�����v����
void CPlayer::Jump()
{
	/*�蓮�W�����v
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

	// �����Ă��Ȃ�������
	if (cAnimation.GetID() != PLAYER_STATE::WALK)
	{
		// �O������
		cAnimation.ChangeID(PLAYER_STATE::FRONT);
		secount++;
		if (secount <= 1) {
			SoundManager::Play(SoundKind::LANDING);  //���nSE
		}
	}
}

// �W�����v�u���b�N�ɓ���������
void CPlayer::HitJumpBlock(PLAYER_JUMP_POWER JumpPower)
{
	m_eJumpPower = JumpPower;
	m_fYSpeed = -MAX_JUMP_Y[m_eJumpPower];
	cAnimation.ChangeID(PLAYER_STATE::JUMP);
	m_iDelayCnt = 0;
	secount = 0;
	SoundManager::Play(SoundKind::JANP);       //�W�����vSE
	SoundManager::Play(SoundKind::JANPBLOAK);  //�W�����v�u���b�NSE

	// �W�����v�������Z
	CPlayerData::GetInstance()->AddJumpCnt();
}

// �v���C���[�̏㑤���W�����v�u���b�N�ɓ���������
void CPlayer::HitJumpBlockUpperSide()
{
	m_iDelayCnt = 0;
}

// �Ƃ��ɓ���������
void CPlayer::HitThorn(float fStartPosX, float fStartPosY)
{
	// �X�^�[�g�ʒu�ɖ߂�
	m_fPosX = fStartPosX;
	m_fPosY = fStartPosY;
	SoundManager::Play(SoundKind::THORN);  //�Ƃ�SE
	SoundManager::Play(SoundKind::POTAL);

	m_fSpeed = 0.0f;
	m_fYSpeed = 0.0f;

	// ���S�������Z
	CPlayerData::GetInstance()->AddDeathCnt();
}

// �S�[���ɓ���������
void CPlayer::HitGoal(float fStartPosX, float fStartPosY)
{
	// �X�^�[�g�ʒu�ɐݒ肷��
	m_fPosX = fStartPosX;
	m_fPosY = fStartPosY;

	m_fSpeed = 0.0f;
	m_fYSpeed = 0.0f;
	secount = 0;
	SoundManager::Play(SoundKind::POTAL);

	// �N���A�������Z
	CPlayerData::GetInstance()->AddClearStage();
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