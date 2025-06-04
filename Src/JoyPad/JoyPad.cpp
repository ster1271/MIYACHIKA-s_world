#include "JoyPad.h"
#include "../Debug/DebugString.h"

// 十字ボタンの角度倍率
constexpr int CROSS_INPUT_INFO_MAG = 4500;
// ボタンの数
constexpr int BUTTON_NUM = 16;
// XInput時のジョイスティックのデッドライン
constexpr int JOYSTICK_DEADLINE = 2000;
// トリガー入力最大値
constexpr int TRIGER_MAX_VALUE = 255;

// XInput時のジョイスティック最大値
constexpr float XINPUT_STICK_MAX_QUANTITY = 65536;
// DInput時のジョイスティック最大値
constexpr float DINPUT_STICK_MAX_QUANTITY = 1000;

// 左スティックの倒しているラジアン値
float JoyPadInput::LStickDefeatRad;
// 右スティックの倒しているラジアン値
float JoyPadInput::RStickDefeatRad;

// 左スティックの倒している量
float JoyPadInput::LStickDefeatQuantity;
// 右スティックの倒している量
float JoyPadInput::RStickDefeatQuantity;

// LT押し込み具合(0.0f~1.0f)
float JoyPadInput::LTPushingCondition;
// RT押し込み具合(0.0f~1.0f)
float JoyPadInput::RTPushingCondition;

// 現在フレームの入力情報
bool JoyPadInput::isPushcurrentJoy[static_cast<int>(PadInputState::NUM)];
// 前のフレームの入力情報
bool JoyPadInput::isPushpreJoy[static_cast<int>(PadInputState::NUM)];

// 初期化
void JoyPadInput::Init()
{
	LTPushingCondition = 0.0f;
	RTPushingCondition = 0.0f;
	LStickDefeatQuantity = 0.0f;
	RStickDefeatQuantity = 0.0f;
	LStickDefeatRad = 0.0f;
	RStickDefeatRad = 0.0f;
	memset(isPushcurrentJoy, 0, sizeof(isPushcurrentJoy));
	memset(isPushpreJoy, 0, sizeof(isPushpreJoy));
}

// 毎フレーム実行する処理
void JoyPadInput::Step()
{
	// 前フレームのパッド情報変数に記録しておく
	for (int i = 0; i < static_cast<int>(PadInputState::NUM); i++)
		isPushpreJoy[i] = isPushcurrentJoy[i];

	// 今フレームの情報をすべてfalseに
	for (int i = 0; i < static_cast<int>(PadInputState::NUM); i++)
		isPushcurrentJoy[i] = false;

	// 押し込み具合はすべてリセット
	LTPushingCondition = 0.0f;
	RTPushingCondition = 0.0f;
	LStickDefeatRad = 0.0f;
	RStickDefeatRad = 0.0f;

	// 入力情報取得
	// XInputならこっち
	if (CheckJoypadXInput(DX_INPUT_PAD1))
		GetHitXPadStateAll();
	// DInputならこっち
	else
		GetHitDPadStateAll();
}

//今押された：PadInputState::～
bool JoyPadInput::Push(PadInputState key_code)
{
	//前フレで押されてない　かつ　現フレで押されている

	int StateIndex = static_cast<int>(key_code);

	//前フレで押されてない　かつ　現フレで押されている
	if (!isPushpreJoy[StateIndex] && isPushcurrentJoy[StateIndex])
		return true;

	//押されてないので false
	return false;
}

//押し続けられている：PadInputState::～
bool JoyPadInput::Keep(PadInputState key_code)
{
	//前フレで押されている　かつ　現フレで押されている

	int StateIndex = static_cast<int>(key_code);

	if (isPushpreJoy[StateIndex]&& isPushcurrentJoy[StateIndex])
		return true;

	return false;
}

//たった今離された：PadInputState::～
bool JoyPadInput::Release(PadInputState key_code)
{
	//前フレで押されている　かつ　現フレで押されていない

	int StateIndex = static_cast<int>(key_code);

	if (isPushpreJoy[StateIndex] && !isPushcurrentJoy[StateIndex])
		return true;

	return false;
}

//単純に押されているか：PadInputState::～
bool JoyPadInput::Down(PadInputState key_code)
{
	//現フレで押されている（前フレの状態は関係なし）
	int StateIndex = static_cast<int>(key_code);

	if (isPushcurrentJoy[StateIndex])
		return true;

	return false;
}

// DInputの入力情報取得
void JoyPadInput::GetHitDPadStateAll()
{
	// 入力情報取得用
	DINPUT_JOYSTATE DJoystate{};
	// パッド情報取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &DJoystate);

	// 情報代入
	for (int i = 0; i < static_cast<int>(PadInputState::NUM); i++) {
		// コード入力
		PadInputState key_code = static_cast<PadInputState>(i);
		// そのボタンが押されているか
		bool isPushed = false;

		// 左右スティック関係確認
		switch (key_code)
		{
		case PadInputState::LSTICK:
			if (DJoystate.X != 0 || DJoystate.Y != 0)
				isPushed = true;
			break;
		case PadInputState::LSTICKLEFT:
			if (DJoystate.X < 0)
				isPushed = true;
			break;
		case PadInputState::LSTICKRIGHT:
			if (DJoystate.X > 0)
				isPushed = true;
			break;
		case PadInputState::LSTICKUP:
			if (DJoystate.Y < 0)
				isPushed = true;
			break;
		case PadInputState::LSTICKDOWN:
			if (DJoystate.Y > 0)
				isPushed = true;
			break;
		case PadInputState::RSTICK:
			if (DJoystate.Z != 0 || DJoystate.Rz != 0)
				isPushed = true;
			break;
		case PadInputState::RSTICKLEFT:
			if (DJoystate.Z < 0)
				isPushed = true;
			break;
		case PadInputState::RSTICKRIGHT:
			if (DJoystate.Z > 0)
				isPushed = true;
			break;
		case PadInputState::RSTICKUP:
			if (DJoystate.Rz < 0)
				isPushed = true;
			break;
		case PadInputState::RSTICKDOWN:
			if (DJoystate.Rz > 0)
				isPushed = true;
			break;
		case PadInputState::CROSS:
			if (DJoystate.POV[0] != -1)
				isPushed = true;
			break;
		default:
			break;
		}

		// 押されていないことが分かったなら飛ばす
		if (!isPushed) 
			// 十字の指定の方向が押されているか
			if (PadInputState::UP <= key_code && key_code <= PadInputState::UPLEFT)
				if (DJoystate.POV[0] == (static_cast<int>(key_code) - static_cast<int>(PadInputState::UP)) * CROSS_INPUT_INFO_MAG)
					isPushed = true;

		// 押されていないことが分かったなら飛ばす
		if (!isPushed) {
			// 左右スティック十字ボタン以外なら
			if (PadInputState::X <= key_code && key_code <= PadInputState::RSTICKDOWN)
				if (DJoystate.Buttons[static_cast<int>(key_code)] != 0)
					isPushed = true;
		}

		isPushcurrentJoy[i] = isPushed;
	}

	// スティックが上下左右いずれかが入力差されているなら入力されていることに
	// 左スティック
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKUP)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKDOWN)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKLEFT)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKRIGHT)])
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICK)] = true;
	// 左スティック
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKUP)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKDOWN)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKLEFT)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKRIGHT)])
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICK)] = true;

	// 左スティックの角度計算(左スティックが入力されているなら計算)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LSTICK)])
		LStickDefeatRad = atan2f(static_cast<float>(DJoystate.X), static_cast<float>(-DJoystate.Y));

	// 右スティックの角度計算(右スティックが入力されているなら計算)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RSTICK)])
		RStickDefeatRad = atan2f(static_cast<float>(DJoystate.Z), static_cast<float>(-DJoystate.Rz));

	// 左スティックの倒している量計算
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LSTICK)])
		// VSizeを使って距離を計算
		LStickDefeatQuantity = VSize(VGet(static_cast<float>(DJoystate.X), static_cast<float>(-DJoystate.Y), 0.0f)) / DINPUT_STICK_MAX_QUANTITY;

	// 右スティックの倒している量計算
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RSTICK)])
		// VSizeを使って距離を計算
		RStickDefeatQuantity = VSize(VGet(static_cast<float>(DJoystate.Z), static_cast<float>(-DJoystate.Rz), 0.0f)) / DINPUT_STICK_MAX_QUANTITY;

	// LT押し込み具合代入
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LT)])
		LTPushingCondition = 1.0f;

	// RT押し込み具合代入
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RT)])
		RTPushingCondition = 1.0f;
}

// XInputの入力情報取得
void JoyPadInput::GetHitXPadStateAll()
{
	// 入力情報取得用
	XINPUT_STATE XJoystate{};
	// パッド情報取得
	GetJoypadXInputState(DX_INPUT_PAD1, &XJoystate);

	// １６種類のボタン入力情報を代入する
	for (int i = 0; i < BUTTON_NUM; i++) {
		// 入力されていないなら飛ばす
		if (XJoystate.Buttons[i] == 0)continue;

		switch (i)
		{
		case 0:
			isPushcurrentJoy[static_cast<int>(PadInputState::UP)] = true;
			break;
		case 1:
			isPushcurrentJoy[static_cast<int>(PadInputState::DOWN)] = true;
			break;
		case 2:
			isPushcurrentJoy[static_cast<int>(PadInputState::LEFT)] = true;
			break;
		case 3:
			isPushcurrentJoy[static_cast<int>(PadInputState::RIGHT)] = true;
			break;
		case 4:
			isPushcurrentJoy[static_cast<int>(PadInputState::START)] = true;
			break;
		case 5:
			isPushcurrentJoy[static_cast<int>(PadInputState::BACK)] = true;
			break;
		case 6:
			isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKDOWN)] = true;
			break;
		case 7:
			isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKDOWN)] = true;
			break;
		case 8:
			isPushcurrentJoy[static_cast<int>(PadInputState::LB)] = true;
			break;
		case 9:
			isPushcurrentJoy[static_cast<int>(PadInputState::RB)] = true;
			break;
		case 12:
			isPushcurrentJoy[static_cast<int>(PadInputState::A)] = true;
			break;
		case 13:
			isPushcurrentJoy[static_cast<int>(PadInputState::B)] = true;
			break;
		case 14:
			isPushcurrentJoy[static_cast<int>(PadInputState::X)] = true;
			break;
		case 15:
			isPushcurrentJoy[static_cast<int>(PadInputState::Y)] = true;
			break;
		default:
			break;
		}
	}

	// 左右上下いずれかが入力されているなら十字キーが入力されていることに
	if (isPushcurrentJoy[static_cast<int>(PadInputState::UP)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::DOWN)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::LEFT)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::RIGHT)])
		isPushcurrentJoy[static_cast<int>(PadInputState::CROSS)] = true;

	// 左上入力されているか確認(左も上も入力されているなら)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LEFT)] &&
		isPushcurrentJoy[static_cast<int>(PadInputState::UP)])
		isPushcurrentJoy[static_cast<int>(PadInputState::UPLEFT)] = true;
	// 左下入力されているか確認(左も下も入力されているなら)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LEFT)] &&
		isPushcurrentJoy[static_cast<int>(PadInputState::DOWN)])
		isPushcurrentJoy[static_cast<int>(PadInputState::DOWNLEFT)] = true;
	// 右上入力されているか確認(右も上も入力されているなら)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RIGHT)] &&
		isPushcurrentJoy[static_cast<int>(PadInputState::UP)])
		isPushcurrentJoy[static_cast<int>(PadInputState::UPRIGHT)] = true;
	// 右下入力されているか確認(右も下も入力されているなら)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RIGHT)] &&
		isPushcurrentJoy[static_cast<int>(PadInputState::DOWN)])
		isPushcurrentJoy[static_cast<int>(PadInputState::DOWNRIGHT)] = true;

	// デッドラインを超えているなら入力されている判定に
	// 左スティック==============================================================
	if (XJoystate.ThumbLX < -JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKLEFT)] = true;
	else if (XJoystate.ThumbLX > JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKRIGHT)] = true;

	if (XJoystate.ThumbLY < -JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKDOWN)] = true;
	else if (XJoystate.ThumbLY > JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKUP)] = true;

	// 上下左右いずれかが入力差されているならスティックが入力されていることに
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKUP)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKDOWN)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKLEFT)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKRIGHT)])
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICK)] = true;

	// ==========================================================================

	// 右スティック==============================================================
	if (XJoystate.ThumbRX < -JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKLEFT)] = true;
	else if (XJoystate.ThumbRX > JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKRIGHT)] = true;

	if (XJoystate.ThumbRY < -JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKDOWN)] = true;
	else if (XJoystate.ThumbRY > JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKUP)] = true;

	// 上下左右いずれかが入力差されているならスティックが入力されていることに
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKUP)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKDOWN)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKLEFT)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKRIGHT)])
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICK)] = true;
	// ==========================================================================

	// 左スティックの角度計算(左スティックが入力されているなら計算)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LSTICK)])
		LStickDefeatRad = atan2f(static_cast<float>(XJoystate.ThumbLX), static_cast<float>(XJoystate.ThumbLY));

	// 右スティックの角度計算(右スティックが入力されているなら計算)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RSTICK)])
		RStickDefeatRad = atan2f(static_cast<float>(XJoystate.ThumbRX), static_cast<float>(XJoystate.ThumbRY));

	// 左スティックの倒している量計算
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LSTICK)])
		// VSizeを使って距離を計算
		LStickDefeatQuantity = VSize(VGet(static_cast<float>(XJoystate.ThumbLX), static_cast<float>(XJoystate.ThumbLY), 0.0f)) / XINPUT_STICK_MAX_QUANTITY;

	// 右スティックの倒している量計算
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RSTICK)])
		// VSizeを使って距離を計算
		RStickDefeatQuantity = VSize(VGet(static_cast<float>(XJoystate.ThumbRX), static_cast<float>(XJoystate.ThumbRY), 0.0f)) / XINPUT_STICK_MAX_QUANTITY;

	// LT押し込み判定
	if (XJoystate.LeftTrigger != 0) {
		isPushcurrentJoy[static_cast<int>(PadInputState::LT)] = true;
		// LT押し込み判定具合計算(0.0f~1.0f)
		LTPushingCondition = static_cast<float>(XJoystate.LeftTrigger) / static_cast<float>(TRIGER_MAX_VALUE);
	}

	// RT押し込み判定
	if (XJoystate.RightTrigger != 0) {
		isPushcurrentJoy[static_cast<int>(PadInputState::RT)] = true;
		// RT押し込み具合計算(0.0f~1.0f)
		RTPushingCondition = static_cast<float>(XJoystate.RightTrigger) / static_cast<float>(TRIGER_MAX_VALUE);
	}
}