#include "DxLib.h"
#include "SceneTitle.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Debug/DebugString.h"
#include "../../SoundManager/SoundManager.h"

void SceneTitle::Init()
{
	// フォントロード
	Font::Load();
}

void SceneTitle::Step()
{
	// デバッグ文字表示用
	DebugString* dbgStr = DebugString::GetInstance();
	dbgStr->AddString(0, 0, FontType::HGP創英角ポップ体24, WHITE, "タイトルです");
	dbgStr->AddString(0, 24, FontType::HGP創英角ポップ体24, WHITE, "左クリックもしくはコントローラ×ボタンでプレイに");

	// 次ボタンでプレイへ
	if (Input::Conclusion(Input::Type::NEXT))
		SceneBace::g_scene_ID = Play_Scene;
}
void SceneTitle::Draw()
{

}
void SceneTitle::Fin()
{
}
