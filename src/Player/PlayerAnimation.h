#pragma once

// プレイヤーの画像種類
enum PLAYER_IMAGE_TYPE {
	PLAYER_FRONT,			// 前を向いている
	PLAYER_JUMP,			// ジャンプしている
	PLAYER_WALK_A,			// 歩いているA
	PLAYER_WALK_B,			// 歩いているB
};
// プレイヤーの画像種類総数
static const int PLAYER_IMAGE_TYPE_NUM = 4;

// プレイヤーの状態
enum class PLAYER_STATE {
	FRONT,		// 前を向いている
	JUMP,		// ジャンプしている
	WALK		// 歩いている
};

class CPlayerAnimation {
private:
	PLAYER_STATE m_PlayerID;		// プレイヤーID

	int m_iHndl[PLAYER_IMAGE_TYPE_NUM];	// 画像ハンドル
	float m_fPlayerPosX;				// プレイヤーX座標
	float m_fPlayerPosY;				// プレイヤーY座標
	int m_iChangeCnt;					// 変換カウント
	bool m_CurrentImageTypeA;			// 現在の画像タイプがAか
	bool m_Right;						// 右を向いている

public:
	// コンストラクタ・デストラクタ
	CPlayerAnimation();
	~CPlayerAnimation();

	// 初期化
	void Init(float fPosX, float fPosY);
	// 通常処理
	void Step();
	// 描画処理
	void Draw();
	// 終了処理
	void Fin();

	// 更新処理
	void Update(float fPosX, float fPosY);

	//====================
	//      　関数
	//====================

	// プレイヤーIDを変更
	void ChangeID(PLAYER_STATE PlayerID) { m_PlayerID = PlayerID; }

	// プレイヤーが右を向いているか
	void isRight(bool isRight) { m_Right = isRight; }

	//====================
	//   取得・設定関連
	//====================

	// プレイヤーIDを取得
	PLAYER_STATE GetID() { return m_PlayerID; }
};
