#include "../../Collision/CollisionManager.h"
#include "../../Input/Input.h"
#include "ScenePlay.h"
#include "../../SoundManager/SoundManager.h"
#include "../../Font/Font.h"
#include "../../Debug/DebugString.h"

void ScenePlay::Init()
{
	cPlayer.Init();
	cMap.Init();
	cMap.Load(MAP_TYPE_00);
}

void ScenePlay::Step()
{	
	// デバッグ文字表示用
	DebugString* dbgStr = DebugString::GetInstance();
	dbgStr->AddString(0, 0, FontType::HGP創英角ポップ体24, WHITE, "プレイです");
	dbgStr->AddString(0, 24, FontType::HGP創英角ポップ体24, WHITE, "左クリックもしくはコントローラ×ボタンでクリアに");

	cPlayer.Step();
	cMap.Step();

	Collision();

	cPlayer.Update();

	// 次ボタンでクリアへ
	if (Input::Conclusion(Input::Type::NEXT))
		SceneBace::g_scene_ID = Clear_Scene;
}
void ScenePlay::Draw()
{
	cPlayer.Draw();
	cMap.Draw();
}
void ScenePlay::Fin()
{
	cPlayer.Fin();
	cMap.Exit();
}

void ScenePlay::Collision()
{
	CollisionManager::CheckHitPlayerToMap(cPlayer, cMap);
}
