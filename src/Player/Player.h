#pragma once
#include "DxLib.h"
#include "PlayerAnimation.h"

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
	float m_fPosX;		// X座標
	float m_fPosY;		// Y座標
	float m_fOldPosX;	// 移動前のX座標
	float m_fOldPosY;	// 移動前のY座標
	float m_fSpeed;		// 速度
	float m_fYSpeed;	// Y軸加速度
	int m_iDelayCnt;	// ディレイカウント
	int secount;        //SE再生回数

	// プレイヤーのどの方向に進んでいるか
	bool m_bDir[PLAYER_DIRECTION_NUM];

	// ジャンプ力
	PLAYER_JUMP_POWER m_eJumpPower;

	// プレイヤーアニメーションクラスをインスタンス化
	CPlayerAnimation cAnimation;

public:
	// コンストラクタ・デストラクタ
	CPlayer();
	~CPlayer();

	void Init(VECTOR vStartPos);	// 初期化
	void Step();					// 通常処理
	void Draw();					// 描画処理
	void Fin();						// 終了処理

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

	// ディレイカウントを加算
	void AddDelayCnt();

	// マップに当たった時
	void HitMapX(float fOverlap);
	void HitMapY(float fOverlap);

	// プレイヤーの上側が当たった時
	void HitUpperSide();

	// プレイヤーの下側が当たった時
	void HitLowerSide();

	// ジャンプブロックに当たった時
	void HitJumpBlock(PLAYER_JUMP_POWER JumpPower);

	// プレイヤーの上側がジャンプブロックに当たった時
	void HitJumpBlockUpperSide();

	// とげに当たったら
	void HitThorn(float fStartPosX, float fStartPosY);

	// ゴールに当たったら
	void HitGoal(float fStartPosX, float fStartPosY);

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

	// ディレイしたか
	bool GetDelay();

	// プレイヤーの座標を設定
	void SetPos(float fPosX, float fPosY)
	{
		m_fPosX = fPosX;
		m_fPosY = fPosY;
	}
};
