#pragma once

// プレイヤーの移動方向
enum PLAYER_DIRECTION {
	PLAYER_UP,				// 上に移動
	PLAYER_DOWN,			// 下に移動
	PLAYER_LEFT,			// 左に移動
	PLAYER_RIGHT,			// 右に移動

	PLAYER_DIRECTION_NUM	// プレイヤーの移動方向の総数
};

// プレイヤーのジャンプパワー
enum PLAYER_JUMP_POWER
{
	JUMP_POWER_1,			// ジャンプのパワー1
	JUMP_POWER_2,			// ジャンプのパワー2
	JUMP_POWER_3,			// ジャンプのパワー3

	PLAYER_JUMP_POWER_NUM	// ジャンプのパワー総数
};

// プレイヤーの大きさ
const float PLAYER_SIZE = 32.0f;

class CPlayer {
private:
	int m_iHndl;		// 画像ハンドル
	float m_fPosX;		// X座標
	float m_fPosY;		// Y座標
	float m_fOldPosX;	// 移動前のX座標
	float m_fOldPosY;	// 移動前のY座標
	float m_fSpeed;		// 速度
	float m_fYSpeed;	// Y軸加速度

	// プレイヤーのどの方向に進んでいるか
	bool m_bDir[PLAYER_DIRECTION_NUM];

	// ジャンプ力
	PLAYER_JUMP_POWER m_eJumpPower;

public:
	// コンストラクタ・デストラクタ
	CPlayer();
	~CPlayer();

	void Init();	// 初期化
	void Step();	// 通常処理
	void Draw();	// 描画処理
	void Fin();		// 終了処理

	// 更新処理
	void Update();

	//====================
	//      　関数
	//====================
	
	// 移動処理
	void Move();

	// ジャンプ処理
	void Jump();

	// プレイヤーの方向
	void Direction();

	// マップに当たった時
	void HitMapX(float fOverlap);
	void HitMapY(float fOverlap);

	// 上側に当たった時
	void HitUpperSide();

	// 下側に当たった時
	void HitLowerSide();

	// プレイヤーのジャンプパワーを変える
	void SetJumpPower(PLAYER_JUMP_POWER JumpPower);

	//====================
	//   取得・設定関連
	//====================

	// プレイヤーの座標取得
	float& GetPosX() { return m_fPosX; }
	float& GetPosY() { return m_fPosY; }

	// プレイヤーの移動前の座標取得
	float GetOldPosX() { return m_fOldPosX; }
	float GetOldPosY() { return m_fOldPosY; }

	// プレイヤーの大きさ
	float GetSize() { return PLAYER_SIZE; }

	// プレイヤーの移動方向を取得
	bool GetDir(PLAYER_DIRECTION DirID) { return m_bDir[DirID]; }

	// プレイヤーの座標を設定
	void SetPos(float fPosX, float fPosY)
	{
		m_fPosX = fPosX;
		m_fPosY = fPosY;
	}
};
