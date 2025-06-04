#pragma once
#include "../JoyPad/JoyPad.h"

constexpr int KEY_BUF_LEN = 256;
constexpr int MOUSE_BUF_LEN = 3;

class Input
{
private:
	//���݃t���[���̃L�[���
	static char currentKeyBuf[KEY_BUF_LEN];
	//���݃t���[���̃}�E�X���
	static char currentMouseBuf[MOUSE_BUF_LEN];

	//�O�̃t���[���̃L�[���
	static char preKeyBuf[KEY_BUF_LEN];
	//�O�̃t���[���̃}�E�X���
	static char preMouseBuf[MOUSE_BUF_LEN];

public:
	enum class Type{
		// �v���C���[�֘A
		MOVE_LEFT,	// ���ړ�
		MOVE_RIGHT,	// �E�ړ�
		MOVE_UP,	// ��ړ�
		MOVE_DOWN,	// ���ړ�
		INPUT_DASH,	// �_�b�V��(�ړ��L�[��������Ă���)
		JUMP,		// �W�����v
		ATTACK,		// �U���{�^��
		BOTTOLE,	// �r�U��
		TAKE_CLUB,	// �����ւ�
		SELECT_OBJECT_DECREMENT,	// �I���I�u�W�F�N�g�ύX(���Z)
		SELECT_OBJECT_INCREMENT,	// �I���I�u�W�F�N�g�ύX(���Z)
		INSTALLATOPN,	// �ݒu
		DEMOLITION,		// �폜
		ENHANCEMENT,	// ����

		// �V�X�e��
		NEXT,		// ���ɐi��
		HOLD_NEXT,	// ���ɐi��(������)
		RELEASE_NEXT,	// ���ɐi��(����)
		BACK,		// �O�ɖ߂�
		END,		// �Q�[���I��

		NUM,
	};
	//���͐��䏉����
	static void Init();

	//���͐���X�e�b�v
	//����Step��葁���Ă�
	static void Step();

	// ���͏��܂Ƃ�=================================
	static bool Conclusion(Type type);
	
	////�������ꂽ
	//static bool Push(Type type);
	////�����������Ă���
	//static bool Keep(Type type);
	////�������������ꂽ
	//static bool Release(Type type);
	////�P���ɉ�����Ă��邩
	//static bool Down(Type type);
	
	// =================================================

//private:
	/*==========================================================
							�L�[�{�[�h
	==========================================================*/
	class Key
	{
	public:
		//�������ꂽ�FKEY_INPUT_�`
		static bool Push(int key_code);

		//�����������Ă���FKEY_INPUT_�`
		static bool Keep(int key_code);

		//�������������ꂽ�FKEY_INPUT_�`
		static bool Release(int key_code);

		//=======================================

		//�P���ɉ�����Ă��邩�FKEY_INPUT_�`
		static bool Down(int key_code);
	};


	/*==========================================================
								�}�E�X
	==========================================================*/
	class Mouse
	{
	public:
		//�������ꂽ�FMOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
		static bool Push(int key_code);

		//�����������Ă���FMOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
		static bool Keep(int key_code);

		//�������������ꂽ�FMOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
		static bool Release(int key_code);

		//=======================================

		//�������������ꂽ�FMOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
		static bool Down(int key_code);
	};
};