#include "../../Collision/CollisionManager.h"
#include "../../Input/Input.h"
#include "ScenePlay.h"
#include "../../SoundManager/SoundManager.h"
#include "../../Font/Font.h"
#include "../../Debug/DebugString.h"

void ScenePlay::Init()
{
}

void ScenePlay::Step()
{	
	// デバッグ文字表示用
	DebugString* dbgStr = DebugString::GetInstance();
	dbgStr->AddString(0, 0, FontType::HGP創英角ポップ体24, WHITE, "プレイです");
	dbgStr->AddString(0, 24, FontType::HGP創英角ポップ体24, WHITE, "左クリックもしくはコントローラ×ボタンでクリアに");
	// 次ボタンでクリアへ
	if (Input::Conclusion(Input::Type::NEXT))
		SceneBace::g_scene_ID = Clear_Scene;
}
void ScenePlay::Draw()
{
}
void ScenePlay::Fin()
{
}
