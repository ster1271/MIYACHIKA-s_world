#include "PlayerAnimation.h"
#include <DxLib.h>

//==================================================
// ��`�֘A

// �v���C���[�̉摜�t�@�C���p�X
const char PLAYER_FILE_PATH[PLAYER_IMAGE_TYPE_NUM][128] = { 
	"data/Player/PlayerFront.png",
	"data/Player/PlayerJump.png",
	"data/Player/PlayerWalkA.png",
	"data/Player/PlayerWalkB.png",
};

//==================================================

// �R���X�g���N�^�E�f�X�g���N�^
CPlayerAnimation::CPlayerAnimation()
{
	m_PlayerID = PLAYER_STATE::FRONT;

	for (int i = 0; i < PLAYER_IMAGE_TYPE_NUM; i++)
	{
		m_iHndl[i] = -1;
	}
	m_fPlayerPosX = 0.0f;
	m_fPlayerPosY = 0.0f;
	m_iChangeCnt = 0;
	m_CurrentImageTypeA = true;
	m_Right = true;
}
CPlayerAnimation::~CPlayerAnimation(){}

// ������
void CPlayerAnimation::Init(float fPosX, float fPosY)
{
	m_fPlayerPosX = fPosX;
	m_fPlayerPosY = fPosY;

	for (int i = 0; i < PLAYER_IMAGE_TYPE_NUM; i++)
	{
		m_iHndl[i] = LoadGraph(PLAYER_FILE_PATH[i]);
	}
}

// �ʏ폈��
void CPlayerAnimation::Step()
{
	m_iChangeCnt++;

	if (m_iChangeCnt > 30)
	{
		if (m_CurrentImageTypeA)
		{
			m_CurrentImageTypeA = false;
		}
		else if (!m_CurrentImageTypeA)
		{
			m_CurrentImageTypeA = true;
		}

		m_iChangeCnt = 0;
	}
}

// �`�揈��
void CPlayerAnimation::Draw()
{
	switch (m_PlayerID)
	{
	case PLAYER_STATE::FRONT:
		DrawGraph((int)m_fPlayerPosX, (int)m_fPlayerPosY, m_iHndl[PLAYER_FRONT], true);
		break;
	case PLAYER_STATE::JUMP:
		if (m_Right)
		{
			DrawGraph((int)m_fPlayerPosX, (int)m_fPlayerPosY, m_iHndl[PLAYER_JUMP], true);
		}
		else
		{
			DrawTurnGraph((int)m_fPlayerPosX, (int)m_fPlayerPosY, m_iHndl[PLAYER_JUMP], true);
		}
		break;
	case PLAYER_STATE::WALK:
		if (m_CurrentImageTypeA)
		{
			if (m_Right)
			{
				DrawGraph((int)m_fPlayerPosX, (int)m_fPlayerPosY, m_iHndl[PLAYER_WALK_A], true);
			}
			else
			{
				DrawTurnGraph((int)m_fPlayerPosX, (int)m_fPlayerPosY, m_iHndl[PLAYER_WALK_A], true);
			}
		}
		else if(!m_CurrentImageTypeA)
		{
			if (m_Right)
			{
				DrawGraph((int)m_fPlayerPosX, (int)m_fPlayerPosY, m_iHndl[PLAYER_WALK_B], true);
			}
			else
			{
				DrawTurnGraph((int)m_fPlayerPosX, (int)m_fPlayerPosY, m_iHndl[PLAYER_WALK_B], true);
			}
		}
		break;
	default:
		break;
	}
}

// �I������
void CPlayerAnimation::Fin()
{
	for (int i = 0; i < PLAYER_IMAGE_TYPE_NUM; i++)
	{
		DeleteGraph(m_iHndl[i]);
		m_iHndl[i] = -1;
	}
}


// �X�V����
void CPlayerAnimation::Update(float fPosX, float fPosY)
{
	m_fPlayerPosX = fPosX;
	m_fPlayerPosY = fPosY;
}
