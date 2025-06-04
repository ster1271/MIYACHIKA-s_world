#include "DxLib.h"
#include "Input/Input.h"
#include "SoundManager/SoundManager.h"
#include "FrameRate/FrameRate.h"
#include "SceneManager/SceneManager.h"
#include "Font/Font.h"
#include "Debug/DebugString.h"
#include "Time/Time.h"

// Main�ł��Init���܂Ƃ߂�
void InitGame();
// Main�ł��Step���܂Ƃ߂�
void StepGame();
// Main�ł��Fin���܂Ƃ߂�
void FinGame();

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//�E�B���h�E�̏�Ԃ�ݒ�
	ChangeWindowMode(true);

	//��ʃT�C�Y��ݒ�
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//����������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//�`�悷��X�N���[���𗠂ɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	/*�ŏ��ɂP�x������鏈��*/
	InitGame();
	SceneManager scene;

	//�Q�[���̃��C�����[�v
	while (ProcessMessage() != -1)
	{
		if (FrameRate::Admin())
		{
			// �I���{�^�����͂ŏI��
			if (Input::Conclusion(Input::Type::END))
				break;


			//��ʂ�������
			ClearDrawScreen();

			// step�܂Ƃ�
			StepGame();

			//�E�B���h�E�̏�Ԃ�ݒ�
			if (Input::Key::Push(KEY_INPUT_LALT) && Input::Key::Push(KEY_INPUT_RETURN))
				ChangeWindowMode(true);

			// �V�[���}�l�[�W���[���C��
			scene.Main();

			//FPS�v�Z
			FrameRate::CalcFPS();

			// �f�o�b�O��������
			DebugString::GetInstance()->Step();

			//FPS�v�Z
			FrameRate::DrawFPS();

			// �f�o�b�O�����\��
			DebugString::GetInstance()->Draw();

			// 1���[�v�I��
			ScreenFlip();
		}
	}

	/*�Ō�ɂP�x������鏈��*/
	FinGame();

	//DxLib�̌㏈��
	DxLib_End();

	return 0;
}

void InitGame()
{
	Input::Init();
	SoundManager::Init();
	SoundManager::LoadAllData();
	Font::Init();
	Font::LoadFile();
	FrameRate::Init();
	Time::Init();
}

void StepGame()
{
	Input::Step();
	Time::Step();
}

void FinGame()
{
	SoundManager::Fin();
	Font::Fin();
	DebugString::GetInstance()->Fin();
	DebugString::GetInstance()->DeleteInstance();
}