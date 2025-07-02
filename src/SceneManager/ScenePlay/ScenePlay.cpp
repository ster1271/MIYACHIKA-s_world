#include "../../Collision/CollisionManager.h"
#include "../../Input/Input.h"
#include "ScenePlay.h"
#include "../../SoundManager/SoundManager.h"
#include "../../Font/Font.h"
#include "../../Debug/DebugString.h"

void ScenePlay::Init()
{
	cMap.Init();
	cMap.Load(MAP_TYPE_00);
	cPlayer.Init(cMap.GetStartPos());
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
	cMap.Draw();
	cPlayer.Draw();
}
void ScenePlay::Fin()
{
	cMap.Exit();
	cPlayer.Fin();
}

void ScenePlay::Collision()
{
	CollisionManager::CheckHitPlayerToMap(cPlayer, cMap);
	CollisionManager::CheckHitPlayerToJumpBlock(cPlayer, cMap);
	CollisionManager::CheckHitPlayerToThorn(cPlayer, cMap);
}
