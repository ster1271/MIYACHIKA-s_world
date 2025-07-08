#pragma once
#include <DxLib.h>

// プレイヤーデータ
class CPlayerData {
public:
	int m_iJumpCnt;		// ジャンプした回数
	int m_iDeathCnt;	// 死んだ回数
	int m_iClearStage;	// ステージクリア数

private:
	// CPlayerDataのポインタを静的変数で持つ
	static CPlayerData* m_Instance;

	CPlayerData();
	~CPlayerData();

	// コピーを禁止する
	CPlayerData operator == (const CPlayerData& other);

public:
	// 初期化処理
	static void Init();

	// CPlayerDataを取得
	static CPlayerData* GetInstance();

	// CPlayerDataを削除
	static void DeleteInstance();

	//====================
	//   取得・設定関連
	//====================

	// ジャンプした回数を取得
	int GetJumpCnt();

	// 死んだ回数を取得
	int GetDeathCnt();

	// ステージクリア数を取得
	int GetClearStage();

	//====================
	//      　関数
	//====================

	// ジャンプした回数を加算
	void AddJumpCnt();

	// 死んだ回数を加算
	void AddDeathCnt();

	// ステージクリア数を加算
	void AddClearStage();
	
};