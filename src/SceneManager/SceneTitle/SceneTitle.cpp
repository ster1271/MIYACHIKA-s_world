#include "DxLib.h"
#include "SceneTitle.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Debug/DebugString.h"
#include "../../SoundManager/SoundManager.h"
#include <cstdlib>

// ゲームやめるボタンやスタートボタンの大きさ
constexpr int BUTTON_SIZE[2] = { 320,108 };

// タイトルロゴの高さの下限
constexpr float TITLE_Y_POS_LOWER_LIMIT = 200.0f;

// タイトルロゴのジャンプ回数
constexpr int LOGO_JUMP_NUM = 3;

// タイトルロゴの重力
constexpr float LOGO_JUMP_GRAVITY = 0.4f;

// タイトルロゴのジャンプ力の高さ
constexpr float LOGO_JUMP_POWER[LOGO_JUMP_NUM] = {
	-10.0f,
	-12.0f,
	-16.0f,
};

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
	m_LogoPos[0] = static_cast<float>(HALF_SCREEN_SIZE_X);
	m_LogoPos[1] = TITLE_Y_POS_LOWER_LIMIT;
	m_isOffscreenBeen = false;

	m_LogoBoundCnt = 0;
	m_LogoYSpeed = LOGO_JUMP_POWER[m_LogoBoundCnt];
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

	if (m_LogoBoundCnt < LOGO_JUMP_NUM) {
		//m_LogoPos[0]++;
		m_LogoPos[1] += m_LogoYSpeed;
		m_LogoYSpeed += LOGO_JUMP_GRAVITY;
	}

	if (m_LogoPos[1] < -64) {
		m_isOffscreenBeen = true;
	}

	if (m_LogoPos[1] > TITLE_Y_POS_LOWER_LIMIT) {
		m_LogoPos[1] = TITLE_Y_POS_LOWER_LIMIT;
		m_LogoBoundCnt++;
		m_LogoYSpeed = LOGO_JUMP_POWER[m_LogoBoundCnt];
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
	int logopos[2] = { static_cast<int>(m_LogoPos[0]), static_cast<int>(m_LogoPos[1]) };
	DebugString* dbgstr = DebugString::GetInstance();

	if (!m_isOffscreenBeen) {
		dbgstr->AddFormatString(logopos[0] - 16, logopos[1], FontType::HGP創英角ポップ体64_20, WHITE, "%d", m_LogoBoundCnt + 1);
	}
	else {
		dbgstr->AddString(logopos[0] - 16 * 5, logopos[1], FontType::HGP創英角ポップ体64_20, WHITE, "Title");
	}

}
void SceneTitle::Fin()
{
}
