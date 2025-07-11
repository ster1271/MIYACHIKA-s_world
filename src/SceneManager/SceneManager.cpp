#include "../Common.h"
#include "DxLib.h"
#include "SceneClear/SceneClear.h"
#include "SceneManager.h"
#include "ScenePlay/ScenePlay.h"
#include "SceneTitle/SceneTitle.h"
#include "../SoundManager/SoundManager.h"

int SceneBace::g_scene_ID;

SceneManager::SceneManager()
{
	scene = nullptr;
	SceneBace::g_scene_ID = Title_Scene;
}

// 終了処理
void SceneManager::Fin()
{
	scene->Fin();

	if (scene == nullptr)return;

	delete scene;
}

void SceneManager::Main()
{
	switch (SceneBace::g_scene_ID) {
	case Title_Scene: {
		if (scene != nullptr) {
			scene->Fin();
			delete scene;
		}
		scene = new SceneTitle;
		scene->Init();
		SceneBace::g_scene_ID = Loop_Scene;
		break;
	}
	case Play_Scene: {
		if (scene != nullptr) {
			scene->Fin();
			delete scene;
		}
		scene = new ScenePlay;
		scene->Init();
		SoundManager::Play(SoundKind::PLAY_BGM, DX_PLAYTYPE_LOOP); //プレイ画面用BGM
		SceneBace::g_scene_ID = Loop_Scene;
		break;
	}
	case Clear_Scene: {
		if (scene != nullptr) {
			scene->Fin();
			delete scene;
		}
		scene = new SceneClear;
		scene->Init();
		SceneBace::g_scene_ID = Loop_Scene;
		break;
	}
	}

	if (scene != nullptr) {
		scene->Step();
		scene->Draw();
	}
}