#pragma once
#include "../Common.h"

// �p�b�h���͏��
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
	LSTICK_PUSHING,			// ���X�e�B�b�N��������
	RSTICK_PUSHING,			// �E�X�e�B�b�N��������

	CROSS,		// �\��
	UP,			// ��
	UPRIGHT,	// �E��
	RIGHT,		// �E
	DOWNRIGHT,	// �E��
	DOWN,		// ��
	DOWNLEFT,	// ����
	LEFT,		// ��
	UPLEFT,		// ����

	LSTICK,			// ���X�e�B�b�N
	LSTICKLEFT,		// ���X�e�B�b�N��
	LSTICKRIGHT,	// ���X�e�B�b�N�E
	LSTICKUP,		// ���X�e�B�b�N��
	LSTICKDOWN,		// ���X�e�B�b�N��

	RSTICK,			// �E�X�e�B�b�N
	RSTICKLEFT,		// �E�X�e�B�b�N��
	RSTICKRIGHT,	// �E�X�e�B�b�N�E
	RSTICKUP,		// �E�X�e�B�b�N��
	RSTICKDOWN,		// �E�X�e�B�b�N��

	NUM,			// ����
};

class JoyPadInput
{
private:
	// ���X�e�B�b�N�̓|���Ă��郉�W�A���l
	static float LStickDefeatRad;
	// �E�X�e�B�b�N�̓|���Ă��郉�W�A���l
	static float RStickDefeatRad;

	// ���X�e�B�b�N�̓|���Ă����(0.0f~1.0f)
	static float LStickDefeatQuantity;
	// �E�X�e�B�b�N�̓|���Ă����(0.0f~1.0f)
	static float RStickDefeatQuantity;

	// LT�������݋(0.0f~1.0f)
	static float LTPushingCondition;
	// RT�������݋(0.0f~1.0f)
	static float RTPushingCondition;

	// ���݃t���[���̓��͏��
	static bool isPushcurrentJoy[static_cast<int>(PadInputState::NUM)];
	// �O�̃t���[���̓��͏��
	static bool isPushpreJoy[static_cast<int>(PadInputState::NUM)];

	// DInput�̓��͏��擾
	static void GetHitDPadStateAll();
	// XInput�̓��͏��擾
	static void GetHitXPadStateAll();
public:
	//���͐��䏉����
	static void Init();

	//���͐���X�e�b�v
	//����Step��葁���Ă�
	static void Step();

	//�������ꂽ�FPAD_INPUT_�`
	static bool Push(PadInputState key_code);

	//�����������Ă���FPAD_INPUT_�`
	static bool Keep(PadInputState key_code);

	//�������������ꂽ�FPAD_INPUT_�`
	static bool Release(PadInputState key_code);

	//�P���ɉ�����Ă��邩�FPAD_INPUT_�`
	static bool Down(PadInputState key_code);

	// �X�e�B�b�N�p�x�擾
	static float GetLSticRad() {return LStickDefeatRad;}
	static float GetRSticRad() {return RStickDefeatRad;}
	// �X�e�B�b�N���͗ʎ擾
	static float GetLSticQuantity() {return LStickDefeatQuantity;}
	static float GetRSticQuantity() {return RStickDefeatQuantity;}
	// LT�������݋�擾(0.0f~1.0f)
	static float GetLTPushingCondition(){ return LTPushingCondition; }
	// RT�������݋�擾(0.0f~1.0f)
	static float GetRTPushingCondition() { return RTPushingCondition; }
};