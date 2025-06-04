#pragma once
#include "../JoyPad/JoyPad.h"

constexpr int KEY_BUF_LEN = 256;
constexpr int MOUSE_BUF_LEN = 3;

class Input
{
private:
	//現在フレームのキー情報
	static char currentKeyBuf[KEY_BUF_LEN];
	//現在フレームのマウス情報
	static char currentMouseBuf[MOUSE_BUF_LEN];

	//前のフレームのキー情報
	static char preKeyBuf[KEY_BUF_LEN];
	//前のフレームのマウス情報
	static char preMouseBuf[MOUSE_BUF_LEN];

public:
	enum class Type{
		// プレイヤー関連
		MOVE_LEFT,	// 左移動
		MOVE_RIGHT,	// 右移動
		MOVE_UP,	// 上移動
		MOVE_DOWN,	// 下移動
		INPUT_DASH,	// ダッシュ(移動キーが押されている)
		JUMP,		// ジャンプ
		ATTACK,		// 攻撃ボタン
		BOTTOLE,	// 瓶攻撃
		TAKE_CLUB,	// 持ち替え
		SELECT_OBJECT_DECREMENT,	// 選択オブジェクト変更(減算)
		SELECT_OBJECT_INCREMENT,	// 選択オブジェクト変更(加算)
		INSTALLATOPN,	// 設置
		DEMOLITION,		// 削除
		ENHANCEMENT,	// 強化

		// システム
		NEXT,		// 次に進む
		HOLD_NEXT,	// 次に進む(長押し)
		RELEASE_NEXT,	// 次に進む(離す)
		BACK,		// 前に戻る
		END,		// ゲーム終了

		NUM,
	};
	//入力制御初期化
	static void Init();

	//入力制御ステップ
	//他のStepより早く呼ぶ
	static void Step();

	// 入力情報まとめ=================================
	static bool Conclusion(Type type);
	
	////今押された
	//static bool Push(Type type);
	////押し続けられている
	//static bool Keep(Type type);
	////たった今離された
	//static bool Release(Type type);
	////単純に押されているか
	//static bool Down(Type type);
	
	// =================================================

//private:
	/*==========================================================
							キーボード
	==========================================================*/
	class Key
	{
	public:
		//今押された：KEY_INPUT_～
		static bool Push(int key_code);

		//押し続けられている：KEY_INPUT_～
		static bool Keep(int key_code);

		//たった今離された：KEY_INPUT_～
		static bool Release(int key_code);

		//=======================================

		//単純に押されているか：KEY_INPUT_～
		static bool Down(int key_code);
	};


	/*==========================================================
								マウス
	==========================================================*/
	class Mouse
	{
	public:
		//今押された：MOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
		static bool Push(int key_code);

		//押し続けられている：MOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
		static bool Keep(int key_code);

		//たった今離された：MOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
		static bool Release(int key_code);

		//=======================================

		//たった今離された：MOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
		static bool Down(int key_code);
	};
};