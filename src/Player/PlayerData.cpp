#include "PlayerData.h"

CPlayerData* CPlayerData::m_Instance = NULL;

CPlayerData::CPlayerData()
{
	// 値を初期化
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
	// CPlayerDataを取得して情報を表示
	CPlayerData* LData = CPlayerData::GetInstance();
}

// CPlayerDataを取得
CPlayerData* CPlayerData::GetInstance()
{
	// まだ生成されていないなら
	if (m_Instance == NULL)
	{
		m_Instance = new CPlayerData();
	}

	return m_Instance;
}

// CPlayerDataを削除
void CPlayerData::DeleteInstance()
{
	// NULLでないなら削除
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;	// 削除したらNULL代入
	}
}

//====================
//   取得・設定関連
//====================

// ジャンプした回数を取得
int CPlayerData::GetJumpCnt()
{
	return m_iJumpCnt;
}

// 死んだ回数を取得
int CPlayerData::GetDeathCnt()
{
	return m_iDeathCnt;
}

// ステージクリア数を取得
int CPlayerData::GetClearStage()
{
	return m_iClearStage;
}

//====================
//      　関数
//====================

// ジャンプした回数を加算
void CPlayerData::AddJumpCnt()
{
	m_iJumpCnt++;
}

// 死んだ回数を加算
void CPlayerData::AddDeathCnt()
{
	m_iDeathCnt++;
}

// ステージクリア数を加算
void CPlayerData::AddClearStage()
{
	m_iClearStage++;
}