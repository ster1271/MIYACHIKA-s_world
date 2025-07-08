#include "PlayerData.h"

CPlayerData* CPlayerData::m_Instance = NULL;

CPlayerData::CPlayerData()
{
	// �l��������
	m_iJumpCnt = 0;
	m_iDeathCnt = 0;
	m_iClearStage = 0;
}
CPlayerData::~CPlayerData() {}

CPlayerData CPlayerData::operator==(const CPlayerData& other)
{
	return CPlayerData();
}

void CPlayerData::Init()
{
	// CPlayerData���擾���ď���\��
	CPlayerData* LData = CPlayerData::GetInstance();
}

// CPlayerData���擾
CPlayerData* CPlayerData::GetInstance()
{
	// �܂���������Ă��Ȃ��Ȃ�
	if (m_Instance == NULL)
	{
		m_Instance = new CPlayerData();
	}

	return m_Instance;
}

// CPlayerData���폜
void CPlayerData::DeleteInstance()
{
	// NULL�łȂ��Ȃ�폜
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;	// �폜������NULL���
	}
}

//====================
//   �擾�E�ݒ�֘A
//====================

// �W�����v�����񐔂��擾
int CPlayerData::GetJumpCnt()
{
	return m_iJumpCnt;
}

// ���񂾉񐔂��擾
int CPlayerData::GetDeathCnt()
{
	return m_iDeathCnt;
}

// �X�e�[�W�N���A�����擾
int CPlayerData::GetClearStage()
{
	return m_iClearStage;
}

//====================
//      �@�֐�
//====================

// �W�����v�����񐔂����Z
void CPlayerData::AddJumpCnt()
{
	m_iJumpCnt++;
}

// ���񂾉񐔂����Z
void CPlayerData::AddDeathCnt()
{
	m_iDeathCnt++;
}

// �X�e�[�W�N���A�������Z
void CPlayerData::AddClearStage()
{
	m_iClearStage++;
}