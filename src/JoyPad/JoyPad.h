#pragma once
#include "../Common.h"

// パッド入力情報
enum class PadInputState {
	X,		// X
	A,		// A
	B,		// B
	Y,		// Y
	LB,		// LB
	RB,		// RB
	LT,		// LT
	RT,		// RT
	BACK,	// BACK
	START,	// START
	LSTICK_PUSHING,			// 左スティック押し込み
	RSTICK_PUSHING,			// 右スティック押し込み

	CROSS,		// 十字
	UP,			// 上
	UPRIGHT,	// 右上
	RIGHT,		// 右
	DOWNRIGHT,	// 右下
	DOWN,		// 下
	DOWNLEFT,	// 左下
	LEFT,		// 左
	UPLEFT,		// 左上

	LSTICK,			// 左スティック
	LSTICKLEFT,		// 左スティック左
	LSTICKRIGHT,	// 左スティック右
	LSTICKUP,		// 左スティック上
	LSTICKDOWN,		// 左スティック下

	RSTICK,			// 右スティック
	RSTICKLEFT,		// 右スティック左
	RSTICKRIGHT,	// 右スティック右
	RSTICKUP,		// 右スティック上
	RSTICKDOWN,		// 右スティック下

	NUM,			// 総数
};

class JoyPadInput
{
private:
	// 左スティックの倒しているラジアン値
	static float LStickDefeatRad;
	// 右スティックの倒しているラジアン値
	static float RStickDefeatRad;

	// 左スティックの倒している量(0.0f~1.0f)
	static float LStickDefeatQuantity;
	// 右スティックの倒している量(0.0f~1.0f)
	static float RStickDefeatQuantity;

	// LT押し込み具合(0.0f~1.0f)
	static float LTPushingCondition;
	// RT押し込み具合(0.0f~1.0f)
	static float RTPushingCondition;

	// 現在フレームの入力情報
	static bool isPushcurrentJoy[static_cast<int>(PadInputState::NUM)];
	// 前のフレームの入力情報
	static bool isPushpreJoy[static_cast<int>(PadInputState::NUM)];

	// DInputの入力情報取得
	static void GetHitDPadStateAll();
	// XInputの入力情報取得
	static void GetHitXPadStateAll();
public:
	//入力制御初期化
	static void Init();

	//入力制御ステップ
	//他のStepより早く呼ぶ
	static void Step();

	//今押された：PAD_INPUT_～
	static bool Push(PadInputState key_code);

	//押し続けられている：PAD_INPUT_～
	static bool Keep(PadInputState key_code);

	//たった今離された：PAD_INPUT_～
	static bool Release(PadInputState key_code);

	//単純に押されているか：PAD_INPUT_～
	static bool Down(PadInputState key_code);

	// スティック角度取得
	static float GetLSticRad() {return LStickDefeatRad;}
	static float GetRSticRad() {return RStickDefeatRad;}
	// スティック入力量取得
	static float GetLSticQuantity() {return LStickDefeatQuantity;}
	static float GetRSticQuantity() {return RStickDefeatQuantity;}
	// LT押し込み具合取得(0.0f~1.0f)
	static float GetLTPushingCondition(){ return LTPushingCondition; }
	// RT押し込み具合取得(0.0f~1.0f)
	static float GetRTPushingCondition() { return RTPushingCondition; }
};