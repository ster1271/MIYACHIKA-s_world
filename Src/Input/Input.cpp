#include"input.h"

//���݃t���[���̃L�[���
char Input::currentKeyBuf[KEY_BUF_LEN];
//���݃t���[���̃}�E�X���
char Input::currentMouseBuf[MOUSE_BUF_LEN];

//�O�̃t���[���̃L�[���
char Input::preKeyBuf[KEY_BUF_LEN];
//�O�̃t���[���̃L�[���
char Input::preMouseBuf[MOUSE_BUF_LEN];

//���͐��䏉����
void Input::Init()
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}

	for (int index = 0; index < MOUSE_BUF_LEN; index++)
	{
		currentMouseBuf[index] = '\0';
		preMouseBuf[index] = '\0';
	}

	JoyPadInput::Init();
}

//���͐���X�e�b�v
//����Step��葁���Ă�
void Input::Step()
{
	//�O�t���[���̃L�[���ϐ��ɋL�^���Ă���
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		preKeyBuf[index] = currentKeyBuf[index];
	}

	for (int index = 0; index < MOUSE_BUF_LEN; index++)
	{
		preMouseBuf[index] = currentMouseBuf[index];
	}

	//���݂̃L�[�����擾
	GetHitKeyStateAll(currentKeyBuf);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		currentMouseBuf[MOUSE_INPUT_LEFT] = 1;
	}
	else
	{
		currentMouseBuf[MOUSE_INPUT_LEFT] = 0;
	}

	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		currentMouseBuf[MOUSE_INPUT_RIGHT] = 1;
	}
	else
	{
		currentMouseBuf[MOUSE_INPUT_RIGHT] = 0;
	}

	// �p�b�h���͏��
	JoyPadInput::Step();
}

// ���͏��܂Ƃ�=================================
bool Input::Conclusion(Type type)
{
	switch (type)
	{
	case Input::Type::MOVE_LEFT:
		if (Key::Down(KEY_INPUT_A) || JoyPadInput::Down(PadInputState::LSTICKLEFT))
			return true;
		break;
	case Input::Type::MOVE_RIGHT:
		if (Key::Down(KEY_INPUT_D) || JoyPadInput::Down(PadInputState::LSTICKRIGHT))
			return true;
		break;
	case Input::Type::MOVE_UP:
		if (Key::Down(KEY_INPUT_W) || JoyPadInput::Down(PadInputState::LSTICKUP))
			return true;
		break;
	case Input::Type::MOVE_DOWN:
		if (Key::Down(KEY_INPUT_S) || JoyPadInput::Down(PadInputState::LSTICKDOWN))
			return true;
		break;
	case Input::Type::INPUT_DASH:
		// �ړ��L�[�����ꂩ�����͂���Ă��Ă��_�b�V���L�[�������Ă���Ȃ�
		// �L�[�{�[�h
		if (Key::Down(KEY_INPUT_A) ||
			Key::Down(KEY_INPUT_D) ||
			Key::Down(KEY_INPUT_W) ||
			Key::Down(KEY_INPUT_S))
			if (Key::Down(KEY_INPUT_LSHIFT))
				return true;

		// �p�b�h
		if (JoyPadInput::Down(PadInputState::LSTICK) && JoyPadInput::Down(PadInputState::RB))
			return true;

		break;
	case Input::Type::JUMP:
		if (Key::Push(KEY_INPUT_SPACE) || JoyPadInput::Push(PadInputState::A))
			return true;
		break;
	case Input::Type::ATTACK:
		if (Mouse::Push(MOUSE_INPUT_LEFT) || JoyPadInput::Push(PadInputState::X))
			return true;
		break;
	case Input::Type::BOTTOLE:
		if (Mouse::Push(MOUSE_INPUT_RIGHT) || JoyPadInput::Push(PadInputState::Y))
			return true;
		break;
	case Input::Type::TAKE_CLUB:
		if (Key::Push(KEY_INPUT_1) || JoyPadInput::Push(PadInputState::LT))
			return true;
		break;
	case Input::Type::SELECT_OBJECT_DECREMENT:
		if (Key::Push(KEY_INPUT_Q) || JoyPadInput::Push(PadInputState::LEFT))
			return true;
		break;
	case Input::Type::SELECT_OBJECT_INCREMENT:
		if (Key::Push(KEY_INPUT_E) || JoyPadInput::Push(PadInputState::RIGHT))
			return true;
		break;
	case Input::Type::INSTALLATOPN:
		if (Key::Push(KEY_INPUT_F) || JoyPadInput::Push(PadInputState::B))
			return true;
		break;
	case Input::Type::DEMOLITION:
		if (Key::Push(KEY_INPUT_F) || JoyPadInput::Push(PadInputState::B))
			return true;
		break;
	case Input::Type::ENHANCEMENT:
		if (Key::Push(KEY_INPUT_C) || JoyPadInput::Push(PadInputState::LB))
			return true;
		break;
	case Input::Type::NEXT:
		if (Mouse::Push(MOUSE_INPUT_LEFT) || JoyPadInput::Push(PadInputState::X))
			return true;
		break;
	case Input::Type::HOLD_NEXT:
		if (Mouse::Keep(MOUSE_INPUT_LEFT) || JoyPadInput::Keep(PadInputState::X))
			return true;
		break;
	case Input::Type::RELEASE_NEXT:
		if (Mouse::Release(MOUSE_INPUT_LEFT) || JoyPadInput::Release(PadInputState::X))
			return true;
		break;
	case Input::Type::BACK:
		if (Mouse::Push(MOUSE_INPUT_RIGHT) || JoyPadInput::Push(PadInputState::B))
			return true;
		break;
	case Input::Type::END:
		if (Key::Push(KEY_INPUT_ESCAPE) || JoyPadInput::Push(PadInputState::BACK))
			return true;
		break;
	default:
		break;
	}
	return false;
}

////�������ꂽ
//bool Input::Push(Type type) 
//{
//	switch (type)
//	{
//	case Input::Type::MOVE_LEFT:
//		if (Key::Push(KEY_INPUT_A) || JoyPadInput::Push(PadInputState::LEFT))
//			return true;
//		break;
//	case Input::Type::MOVE_RIGHT:
//		if (Key::Push(KEY_INPUT_D) || JoyPadInput::Push(PadInputState::RIGHT))
//			return true;
//		break;
//	case Input::Type::MOVE_UP:
//		if (Key::Push(KEY_INPUT_W) || JoyPadInput::Push(PadInputState::UP))
//			return true;
//		break;
//	case Input::Type::MOVE_DOWN:
//		if (Key::Push(KEY_INPUT_S) || JoyPadInput::Push(PadInputState::DOWN))
//			return true;
//		break;
//	case Input::Type::INPUT_DASH:
//		if (Key::Push(KEY_INPUT_A) || JoyPadInput::Push(PadInputState::LEFT))
//			return true;
//
//		break;
//	case Input::Type::ATTACK:
//		break;
//	case Input::Type::INSTALLATOPN:
//		break;
//	case Input::Type::DEMOLITION:
//		break;
//	case Input::Type::NEXT:
//		break;
//	case Input::Type::BACK:
//		break;
//	case Input::Type::NUM:
//		break;
//	default:
//		break;
//	}
//	return false;
//}
////�����������Ă���
//bool Input::Keep(Type type)
//{
//	return false;
//}
//
////�������������ꂽ
//bool Input::Release(Type type)
//{
//	return false;
//}
//
////�P���ɉ�����Ă��邩
//bool Input::Down(Type type)
//{
//	return false;
//}
// =================================================


/*==========================================================
						�L�[�{�[�h
==========================================================*/

//�������ꂽ�FKEY_INPUT_�`
bool Input::Key::Push(int key_code)
{
	//�O�t���ŉ�����ĂȂ��@���@���t���ŉ�����Ă���
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1)
	{
		return true;
	}

	//������ĂȂ��̂� false
	return false;
}

//�����������Ă���FKEY_INPUT_�`
bool Input::Key::Keep(int key_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă���
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 1)
	{
		return true;
	}

	//������ĂȂ��̂� false
	return false;
}

//�������������ꂽ�FKEY_INPUT_�`
bool Input::Key::Release(int key_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă��Ȃ�
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0)
	{
		return true;
	}

	//������Ă�̂� false
	return false;
}

//=========================================================================================================

//�P���ɉ�����Ă��邩�FKEY_INPUT_�`
bool Input::Key::Down(int key_code)
{
	//���t���ŉ�����Ă���i�O�t���̏�Ԃ͊֌W�Ȃ��j
	if (currentKeyBuf[key_code] == 1)
	{
		return true;
	}

	return false;
}

/*==========================================================
							�}�E�X
==========================================================*/
//�������ꂽ�FMOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
bool Input::Mouse::Push(int key_code)
{
	//�O�t���ŉ�����ĂȂ��@���@���t���ŉ�����Ă���
	if (preMouseBuf[key_code] == 0 && currentMouseBuf[key_code] == 1)
	{
		return true;
	}

	//������ĂȂ��̂� false
	return false;
}

//�����������Ă���FMOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
bool Input::Mouse::Keep(int key_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă���
	if (preMouseBuf[key_code] == 1 && currentMouseBuf[key_code] == 1)
	{
		return true;
	}

	//������ĂȂ��̂� false
	return false;
}

//�������������ꂽ�FMOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
bool Input::Mouse::Release(int key_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă��Ȃ�
	if (preMouseBuf[key_code] == 1 && currentMouseBuf[key_code] == 0)
	{
		return true;
	}

	//������Ă�̂� false
	return false;
}

//=========================================================================================================

//�P���ɉ�����Ă��邩�FKEY_INPUT_�`
bool Input::Mouse::Down(int key_code)
{
	//���t���ŉ�����Ă���i�O�t���̏�Ԃ͊֌W�Ȃ��j
	if (preMouseBuf[key_code] == 1)
	{
		return true;
	}

	return false;
}
