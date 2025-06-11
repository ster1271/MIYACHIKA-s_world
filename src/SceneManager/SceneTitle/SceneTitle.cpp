#include "DxLib.h"
#include "SceneTitle.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Debug/DebugString.h"
#include "../../SoundManager/SoundManager.h"
#include <cstdlib>

// ゲームやめるボタンやスタートボタンの大きさ
constexpr int BUTTON_SIZE[2] = { 320,108 };

// ボタンの位置
constexpr int BUTTON_POS[SceneTitle::SELECTABLE_GRAPH_TYPE_NUM][2] = {
	{HALF_SCREEN_SIZE_X - BUTTON_SIZE[0] / 2,400},
	{HALF_SCREEN_SIZE_X - BUTTON_SIZE[0] / 2,550},
};

void SceneTitle::Init()
{
	// フォントロード
	Font::Load();
	m_SelectedGraph = SELECTABLE_GRAPH_TYPE_START;
}

void SceneTitle::Step()
{
	// デバッグ文字表示用
	DebugString* dbgStr = DebugString::GetInstance();
	dbgStr->AddString(0, 0, FontType::HGP創英角ポップ体24, WHITE, "タイトルです");
	dbgStr->AddString(0, 24, FontType::HGP創英角ポップ体24, WHITE, "左クリックもしくはコントローラ×ボタンでプレイに");

	//上下で選択を変える
	if (Input::Conclusion(Input::Type::MOVE_UP)) {
		m_SelectedGraph = static_cast<SELECTABLE_GRAPH_TYPE>(m_SelectedGraph - 1);
		if (m_SelectedGraph < SELECTABLE_GRAPH_TYPE_START) {
			m_SelectedGraph = SELECTABLE_GRAPH_TYPE_START;
		}
	}
	else if (Input::Conclusion(Input::Type::MOVE_DOWN)) {
		m_SelectedGraph = static_cast<SELECTABLE_GRAPH_TYPE>(m_SelectedGraph + 1);
		if (m_SelectedGraph > SELECTABLE_GRAPH_TYPE_END) {
			m_SelectedGraph = SELECTABLE_GRAPH_TYPE_END;
		}
	}

	// 次ボタンを押すと選択中のもので結果を変える
	if (Input::Conclusion(Input::Type::NEXT)) {
		if (m_SelectedGraph == SELECTABLE_GRAPH_TYPE_START) {
			// プレイシーンへ
			SceneBace::g_scene_ID = Play_Scene;
		}
		else if (m_SelectedGraph == SELECTABLE_GRAPH_TYPE_END) {
			// ゲームを終了する
			exit(0); // プログラムを終了
		}
	}

	// 次ボタンでプレイへ
	//if (Input::Conclusion(Input::Type::NEXT))
	//	SceneBace::g_scene_ID = Play_Scene;
}
void SceneTitle::Draw()
{
	// ボタンの左上の座標と右下の座標
	int ButtonPos1[SELECTABLE_GRAPH_TYPE_NUM][2] = { 
		{BUTTON_POS[SELECTABLE_GRAPH_TYPE_START][0] ,BUTTON_POS[SELECTABLE_GRAPH_TYPE_START][1]},
		{BUTTON_POS[SELECTABLE_GRAPH_TYPE_END][0] ,BUTTON_POS[SELECTABLE_GRAPH_TYPE_END][1]},
	};
	int ButtonPos2[SELECTABLE_GRAPH_TYPE_NUM][2] = {
		{ButtonPos1[SELECTABLE_GRAPH_TYPE_START][0] + BUTTON_SIZE[0] - 1 ,ButtonPos1[SELECTABLE_GRAPH_TYPE_START][1] + BUTTON_SIZE[1] - 1 },
		{ButtonPos1[SELECTABLE_GRAPH_TYPE_END][0] + BUTTON_SIZE[0] - 1 ,ButtonPos1[SELECTABLE_GRAPH_TYPE_END][1] + BUTTON_SIZE[1] - 1 },
	};

	// ボタン描画
	for (int GraphIndex = 0; GraphIndex < SELECTABLE_GRAPH_TYPE_NUM; GraphIndex++) {
		DrawBox(ButtonPos1[GraphIndex][0], ButtonPos1[GraphIndex][1], ButtonPos2[GraphIndex][0], ButtonPos2[GraphIndex][1], WHITE, false);
	}

	// 選択画像
	// 太くする
	for (int ThickIndex = 1; ThickIndex < 5; ThickIndex++) {
		DrawBox(ButtonPos1[m_SelectedGraph][0] - ThickIndex, ButtonPos1[m_SelectedGraph][1] - ThickIndex,
			ButtonPos2[m_SelectedGraph][0] + ThickIndex, ButtonPos2[m_SelectedGraph][1] + ThickIndex, RED, false);
	}

	// いったん文字表示
}
void SceneTitle::Fin()
{
}
