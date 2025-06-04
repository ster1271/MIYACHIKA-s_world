#include "DxLib.h"
#include "Input/Input.h"
#include "SoundManager/SoundManager.h"
#include "FrameRate/FrameRate.h"
#include "SceneManager/SceneManager.h"
#include "Font/Font.h"
#include "Debug/DebugString.h"
#include "Time/Time.h"

// MainでやるInitをまとめる
void InitGame();
// MainでやるStepをまとめる
void StepGame();
// MainでやるFinをまとめる
void FinGame();

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//ウィンドウの状態を設定
	ChangeWindowMode(true);

	//画面サイズを設定
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//描画するスクリーンを裏に設定
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	/*最初に１度だけやる処理*/
	InitGame();
	SceneManager scene;

	//ゲームのメインループ
	while (ProcessMessage() != -1)
	{
		if (FrameRate::Admin())
		{
			// 終了ボタン入力で終了
			if (Input::Conclusion(Input::Type::END))
				break;


			//画面を初期化
			ClearDrawScreen();

			// stepまとめ
			StepGame();

			//ウィンドウの状態を設定
			if (Input::Key::Push(KEY_INPUT_LALT) && Input::Key::Push(KEY_INPUT_RETURN))
				ChangeWindowMode(true);

			// シーンマネージャーメイン
			scene.Main();

			//FPS計算
			FrameRate::CalcFPS();

			// デバッグ文言処理
			DebugString::GetInstance()->Step();

			//FPS計算
			FrameRate::DrawFPS();

			// デバッグ文言表示
			DebugString::GetInstance()->Draw();

			// 1ループ終了
			ScreenFlip();
		}
	}

	/*最後に１度だけやる処理*/
	FinGame();

	//DxLibの後処理
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