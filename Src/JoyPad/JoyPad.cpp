#include "JoyPad.h"
#include "../Debug/DebugString.h"

// �\���{�^���̊p�x�{��
constexpr int CROSS_INPUT_INFO_MAG = 4500;
// �{�^���̐�
constexpr int BUTTON_NUM = 16;
// XInput���̃W���C�X�e�B�b�N�̃f�b�h���C��
constexpr int JOYSTICK_DEADLINE = 2000;
// �g���K�[���͍ő�l
constexpr int TRIGER_MAX_VALUE = 255;

// XInput���̃W���C�X�e�B�b�N�ő�l
constexpr float XINPUT_STICK_MAX_QUANTITY = 65536;
// DInput���̃W���C�X�e�B�b�N�ő�l
constexpr float DINPUT_STICK_MAX_QUANTITY = 1000;

// ���X�e�B�b�N�̓|���Ă��郉�W�A���l
float JoyPadInput::LStickDefeatRad;
// �E�X�e�B�b�N�̓|���Ă��郉�W�A���l
float JoyPadInput::RStickDefeatRad;

// ���X�e�B�b�N�̓|���Ă����
float JoyPadInput::LStickDefeatQuantity;
// �E�X�e�B�b�N�̓|���Ă����
float JoyPadInput::RStickDefeatQuantity;

// LT�������݋(0.0f~1.0f)
float JoyPadInput::LTPushingCondition;
// RT�������݋(0.0f~1.0f)
float JoyPadInput::RTPushingCondition;

// ���݃t���[���̓��͏��
bool JoyPadInput::isPushcurrentJoy[static_cast<int>(PadInputState::NUM)];
// �O�̃t���[���̓��͏��
bool JoyPadInput::isPushpreJoy[static_cast<int>(PadInputState::NUM)];

// ������
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

// ���t���[�����s���鏈��
void JoyPadInput::Step()
{
	// �O�t���[���̃p�b�h���ϐ��ɋL�^���Ă���
	for (int i = 0; i < static_cast<int>(PadInputState::NUM); i++)
		isPushpreJoy[i] = isPushcurrentJoy[i];

	// ���t���[���̏������ׂ�false��
	for (int i = 0; i < static_cast<int>(PadInputState::NUM); i++)
		isPushcurrentJoy[i] = false;

	// �������݋�͂��ׂă��Z�b�g
	LTPushingCondition = 0.0f;
	RTPushingCondition = 0.0f;
	LStickDefeatRad = 0.0f;
	RStickDefeatRad = 0.0f;

	// ���͏��擾
	// XInput�Ȃ炱����
	if (CheckJoypadXInput(DX_INPUT_PAD1))
		GetHitXPadStateAll();
	// DInput�Ȃ炱����
	else
		GetHitDPadStateAll();
}

//�������ꂽ�FPadInputState::�`
bool JoyPadInput::Push(PadInputState key_code)
{
	//�O�t���ŉ�����ĂȂ��@���@���t���ŉ�����Ă���

	int StateIndex = static_cast<int>(key_code);

	//�O�t���ŉ�����ĂȂ��@���@���t���ŉ�����Ă���
	if (!isPushpreJoy[StateIndex] && isPushcurrentJoy[StateIndex])
		return true;

	//������ĂȂ��̂� false
	return false;
}

//�����������Ă���FPadInputState::�`
bool JoyPadInput::Keep(PadInputState key_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă���

	int StateIndex = static_cast<int>(key_code);

	if (isPushpreJoy[StateIndex]&& isPushcurrentJoy[StateIndex])
		return true;

	return false;
}

//�������������ꂽ�FPadInputState::�`
bool JoyPadInput::Release(PadInputState key_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă��Ȃ�

	int StateIndex = static_cast<int>(key_code);

	if (isPushpreJoy[StateIndex] && !isPushcurrentJoy[StateIndex])
		return true;

	return false;
}

//�P���ɉ�����Ă��邩�FPadInputState::�`
bool JoyPadInput::Down(PadInputState key_code)
{
	//���t���ŉ�����Ă���i�O�t���̏�Ԃ͊֌W�Ȃ��j
	int StateIndex = static_cast<int>(key_code);

	if (isPushcurrentJoy[StateIndex])
		return true;

	return false;
}

// DInput�̓��͏��擾
void JoyPadInput::GetHitDPadStateAll()
{
	// ���͏��擾�p
	DINPUT_JOYSTATE DJoystate{};
	// �p�b�h���擾
	GetJoypadDirectInputState(DX_INPUT_PAD1, &DJoystate);

	// �����
	for (int i = 0; i < static_cast<int>(PadInputState::NUM); i++) {
		// �R�[�h����
		PadInputState key_code = static_cast<PadInputState>(i);
		// ���̃{�^����������Ă��邩
		bool isPushed = false;

		// ���E�X�e�B�b�N�֌W�m�F
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

		// ������Ă��Ȃ����Ƃ����������Ȃ��΂�
		if (!isPushed) 
			// �\���̎w��̕�����������Ă��邩
			if (PadInputState::UP <= key_code && key_code <= PadInputState::UPLEFT)
				if (DJoystate.POV[0] == (static_cast<int>(key_code) - static_cast<int>(PadInputState::UP)) * CROSS_INPUT_INFO_MAG)
					isPushed = true;

		// ������Ă��Ȃ����Ƃ����������Ȃ��΂�
		if (!isPushed) {
			// ���E�X�e�B�b�N�\���{�^���ȊO�Ȃ�
			if (PadInputState::X <= key_code && key_code <= PadInputState::RSTICKDOWN)
				if (DJoystate.Buttons[static_cast<int>(key_code)] != 0)
					isPushed = true;
		}

		isPushcurrentJoy[i] = isPushed;
	}

	// �X�e�B�b�N���㉺���E�����ꂩ�����͍�����Ă���Ȃ���͂���Ă��邱�Ƃ�
	// ���X�e�B�b�N
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKUP)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKDOWN)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKLEFT)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKRIGHT)])
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICK)] = true;
	// ���X�e�B�b�N
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKUP)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKDOWN)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKLEFT)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKRIGHT)])
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICK)] = true;

	// ���X�e�B�b�N�̊p�x�v�Z(���X�e�B�b�N�����͂���Ă���Ȃ�v�Z)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LSTICK)])
		LStickDefeatRad = atan2f(static_cast<float>(DJoystate.X), static_cast<float>(-DJoystate.Y));

	// �E�X�e�B�b�N�̊p�x�v�Z(�E�X�e�B�b�N�����͂���Ă���Ȃ�v�Z)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RSTICK)])
		RStickDefeatRad = atan2f(static_cast<float>(DJoystate.Z), static_cast<float>(-DJoystate.Rz));

	// ���X�e�B�b�N�̓|���Ă���ʌv�Z
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LSTICK)])
		// VSize���g���ċ������v�Z
		LStickDefeatQuantity = VSize(VGet(static_cast<float>(DJoystate.X), static_cast<float>(-DJoystate.Y), 0.0f)) / DINPUT_STICK_MAX_QUANTITY;

	// �E�X�e�B�b�N�̓|���Ă���ʌv�Z
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RSTICK)])
		// VSize���g���ċ������v�Z
		RStickDefeatQuantity = VSize(VGet(static_cast<float>(DJoystate.Z), static_cast<float>(-DJoystate.Rz), 0.0f)) / DINPUT_STICK_MAX_QUANTITY;

	// LT�������݋���
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LT)])
		LTPushingCondition = 1.0f;

	// RT�������݋���
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RT)])
		RTPushingCondition = 1.0f;
}

// XInput�̓��͏��擾
void JoyPadInput::GetHitXPadStateAll()
{
	// ���͏��擾�p
	XINPUT_STATE XJoystate{};
	// �p�b�h���擾
	GetJoypadXInputState(DX_INPUT_PAD1, &XJoystate);

	// �P�U��ނ̃{�^�����͏���������
	for (int i = 0; i < BUTTON_NUM; i++) {
		// ���͂���Ă��Ȃ��Ȃ��΂�
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

	// ���E�㉺�����ꂩ�����͂���Ă���Ȃ�\���L�[�����͂���Ă��邱�Ƃ�
	if (isPushcurrentJoy[static_cast<int>(PadInputState::UP)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::DOWN)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::LEFT)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::RIGHT)])
		isPushcurrentJoy[static_cast<int>(PadInputState::CROSS)] = true;

	// ������͂���Ă��邩�m�F(����������͂���Ă���Ȃ�)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LEFT)] &&
		isPushcurrentJoy[static_cast<int>(PadInputState::UP)])
		isPushcurrentJoy[static_cast<int>(PadInputState::UPLEFT)] = true;
	// �������͂���Ă��邩�m�F(�����������͂���Ă���Ȃ�)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LEFT)] &&
		isPushcurrentJoy[static_cast<int>(PadInputState::DOWN)])
		isPushcurrentJoy[static_cast<int>(PadInputState::DOWNLEFT)] = true;
	// �E����͂���Ă��邩�m�F(�E��������͂���Ă���Ȃ�)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RIGHT)] &&
		isPushcurrentJoy[static_cast<int>(PadInputState::UP)])
		isPushcurrentJoy[static_cast<int>(PadInputState::UPRIGHT)] = true;
	// �E�����͂���Ă��邩�m�F(�E���������͂���Ă���Ȃ�)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RIGHT)] &&
		isPushcurrentJoy[static_cast<int>(PadInputState::DOWN)])
		isPushcurrentJoy[static_cast<int>(PadInputState::DOWNRIGHT)] = true;

	// �f�b�h���C���𒴂��Ă���Ȃ���͂���Ă��锻���
	// ���X�e�B�b�N==============================================================
	if (XJoystate.ThumbLX < -JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKLEFT)] = true;
	else if (XJoystate.ThumbLX > JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKRIGHT)] = true;

	if (XJoystate.ThumbLY < -JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKDOWN)] = true;
	else if (XJoystate.ThumbLY > JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKUP)] = true;

	// �㉺���E�����ꂩ�����͍�����Ă���Ȃ�X�e�B�b�N�����͂���Ă��邱�Ƃ�
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKUP)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKDOWN)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKLEFT)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICKRIGHT)])
		isPushcurrentJoy[static_cast<int>(PadInputState::LSTICK)] = true;

	// ==========================================================================

	// �E�X�e�B�b�N==============================================================
	if (XJoystate.ThumbRX < -JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKLEFT)] = true;
	else if (XJoystate.ThumbRX > JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKRIGHT)] = true;

	if (XJoystate.ThumbRY < -JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKDOWN)] = true;
	else if (XJoystate.ThumbRY > JOYSTICK_DEADLINE)
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKUP)] = true;

	// �㉺���E�����ꂩ�����͍�����Ă���Ȃ�X�e�B�b�N�����͂���Ă��邱�Ƃ�
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKUP)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKDOWN)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKLEFT)] ||
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICKRIGHT)])
		isPushcurrentJoy[static_cast<int>(PadInputState::RSTICK)] = true;
	// ==========================================================================

	// ���X�e�B�b�N�̊p�x�v�Z(���X�e�B�b�N�����͂���Ă���Ȃ�v�Z)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LSTICK)])
		LStickDefeatRad = atan2f(static_cast<float>(XJoystate.ThumbLX), static_cast<float>(XJoystate.ThumbLY));

	// �E�X�e�B�b�N�̊p�x�v�Z(�E�X�e�B�b�N�����͂���Ă���Ȃ�v�Z)
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RSTICK)])
		RStickDefeatRad = atan2f(static_cast<float>(XJoystate.ThumbRX), static_cast<float>(XJoystate.ThumbRY));

	// ���X�e�B�b�N�̓|���Ă���ʌv�Z
	if (isPushcurrentJoy[static_cast<int>(PadInputState::LSTICK)])
		// VSize���g���ċ������v�Z
		LStickDefeatQuantity = VSize(VGet(static_cast<float>(XJoystate.ThumbLX), static_cast<float>(XJoystate.ThumbLY), 0.0f)) / XINPUT_STICK_MAX_QUANTITY;

	// �E�X�e�B�b�N�̓|���Ă���ʌv�Z
	if (isPushcurrentJoy[static_cast<int>(PadInputState::RSTICK)])
		// VSize���g���ċ������v�Z
		RStickDefeatQuantity = VSize(VGet(static_cast<float>(XJoystate.ThumbRX), static_cast<float>(XJoystate.ThumbRY), 0.0f)) / XINPUT_STICK_MAX_QUANTITY;

	// LT�������ݔ���
	if (XJoystate.LeftTrigger != 0) {
		isPushcurrentJoy[static_cast<int>(PadInputState::LT)] = true;
		// LT�������ݔ����v�Z(0.0f~1.0f)
		LTPushingCondition = static_cast<float>(XJoystate.LeftTrigger) / static_cast<float>(TRIGER_MAX_VALUE);
	}

	// RT�������ݔ���
	if (XJoystate.RightTrigger != 0) {
		isPushcurrentJoy[static_cast<int>(PadInputState::RT)] = true;
		// RT�������݋�v�Z(0.0f~1.0f)
		RTPushingCondition = static_cast<float>(XJoystate.RightTrigger) / static_cast<float>(TRIGER_MAX_VALUE);
	}
}