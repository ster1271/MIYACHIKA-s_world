#include "../../Collision/CollisionManager.h"
#include "../../Input/Input.h"
#include "ScenePlay.h"
#include "../../SoundManager/SoundManager.h"
#include "../../Font/Font.h"
#include "../../Debug/DebugString.h"

void ScenePlay::Init()
{
	cCreateMap.Init();
	cCreateMap.Load();
	cMap.Init();
	cMap.Load(CMap::MapID);
	cPlayer.Init(cMap.GetStartPos());
}

void ScenePlay::Step()
{	
	// デバッグ文字表示用
	DebugString* dbgStr = DebugString::GetInstance();

	// 次ボタンでクリアへ
	if (Input::Conclusion(Input::Type::NEXT))
		SceneBace::g_scene_ID = Clear_Scene;

	//エディター画面切り替え
	if (Input::Key::Push(KEY_INPUT_LSHIFT))
	{
		if (!cCreateMap.GetIsEditer())
		{
			cCreateMap.SetIsEditer(true);
		}
		else
		{
			cCreateMap.SetIsEditer(false);
		}
	}

	if (cCreateMap.GetIsEditer())
	{
		cCreateMap.Step();
		return;
	}
	else
	{
		//通常プレイモード(ここに処理を追加してください)
		dbgStr->AddString(0, 0, FontType::HGP創英角ポップ体24, WHITE, "プレイです");
		dbgStr->AddString(0, 24, FontType::HGP創英角ポップ体24, WHITE, "LShiftでエディターモードに変更");

		cPlayer.Step();
		cMap.Step();

		Collision();

		cPlayer.Update();
	}
}
void ScenePlay::Draw()
{
	if (cCreateMap.GetIsEditer())
	{
		cCreateMap.Draw();
	}
	else
	{
		cMap.Draw();
		cPlayer.Draw();
	}
}
void ScenePlay::Fin()
{
	cCreateMap.Exit();
	cMap.Exit();
	cPlayer.Fin();
}

void ScenePlay::Collision()
{
	CollisionManager::CheckHitPlayerToMap(cPlayer, cMap);
	CollisionManager::CheckHitPlayerToJumpBlock(cPlayer, cMap);
	CollisionManager::CheckHitPlayerToThorn(cPlayer, cMap);
	CollisionManager::CheckHitPlayerToGoal(cPlayer, cMap);
}
