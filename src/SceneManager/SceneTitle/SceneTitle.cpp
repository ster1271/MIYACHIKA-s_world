#include "DxLib.h"
#include "SceneTitle.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Debug/DebugString.h"
#include "../../SoundManager/SoundManager.h"
#include <cstdlib>

// タイトルの名前
constexpr char TITLE_NAME[] = "Hopin Popin";

// ゲームやめるボタンやスタートボタンの大きさ
constexpr int BUTTON_SIZE[2] = { 320,108 };

// タイトルロゴの高さの下限
constexpr float TITLE_Y_POS_LOWER_LIMIT = 200.0f;

// タイトルロゴのジャンプ回数
constexpr int LOGO_JUMP_NUM = 3;

// タイトルロゴの重力
constexpr float LOGO_JUMP_GRAVITY = 0.4f;

// ボタンの最大サイズ
constexpr double BUTTON_MAX_SIZE = 1.2f;

// ボタンのサイズ変更速度
constexpr double BUTTON_SIZE_CANGED_SPEED = 0.01f;

// タイトルロゴのジャンプ力の高さ
constexpr float LOGO_JUMP_POWER[LOGO_JUMP_NUM] = {
	-10.0f,
	-12.0f,
	-16.0f,
};

// ボタンの位置
constexpr int BUTTON_POS[SceneTitle::SELECTABLE_GRAPH_TYPE_NUM][2] = {
	{HALF_SCREEN_SIZE_X - BUTTON_SIZE[0] / 2,500},
	{HALF_SCREEN_SIZE_X - BUTTON_SIZE[0] / 2,650},
};

// 画像のパス
constexpr char GRAPH_PATH[SceneTitle::GRAPH_TYPE_NUM][256] = {
	"data/Bloak/JumpBlock1.png",
	"data/Title/Title.png",
	"data/Title/Start.png",
	"data/Title/Leave.png",
	"data/Bloak/JumpBlock1.png",
	"data/Bloak/JumpBlock2.png",
	"data/Bloak/JumpBlock3.png",
	"data/Title/1.png",
	"data/Title/2.png",
	"data/Title/3.png",
	"data/Title/SelectBG.png",
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
	for (int i = 0; i < SELECTABLE_GRAPH_TYPE_NUM; i++) {
		m_ButtonExRate[i] = 1.0f;
		if (i == m_SelectedGraph)m_ButtonExRate[i] = BUTTON_MAX_SIZE;
	}
	m_isButtonChangedExRate = false;

	for (int i = 0; i < GRAPH_TYPE_NUM; i++) {
		if (m_Hndl[i] == -1)continue;
		m_Hndl[i] = -1;
	}

	for (int i = 0; i < GRAPH_TYPE_NUM; i++) {
		if (m_Hndl[i] != -1)continue;
		m_Hndl[i] = LoadGraph(GRAPH_PATH[i]);
	}

	m_TitleRogoExRate = 0.0f;
	m_TitleRogoExRateUp = true;
}

void SceneTitle::Step()
{
	// デバッグ文字表示用
	//DebugString* dbgStr = DebugString::GetInstance();
	//dbgStr->AddString(0, 0, FontType::HGP創英角ポップ体24, WHITE, "タイトルです");
	//dbgStr->AddString(0, 24, FontType::HGP創英角ポップ体24, WHITE, "左クリックもしくはコントローラ×ボタンでプレイに");

	if (m_TitleRogoExRateUp) {
		m_TitleRogoExRate += 0.01f;
		if (m_TitleRogoExRate > 0.5f) {
			m_TitleRogoExRateUp = false;
		}
	}
	else {
		m_TitleRogoExRate -= 0.01f;
		if (m_TitleRogoExRate < -0.5f) {
			m_TitleRogoExRateUp = true;
		}
	}

	//上下で選択を変える
	if (m_LogoBoundCnt == LOGO_JUMP_NUM) {
		if (Input::Conclusion(Input::Type::MOVE_UP)) {
			m_SelectedGraph = static_cast<SELECTABLE_GRAPH_TYPE>(m_SelectedGraph - 1);
			if (m_SelectedGraph < SELECTABLE_GRAPH_TYPE_START) {
				m_SelectedGraph = SELECTABLE_GRAPH_TYPE_START;
			}
			else {
				m_isButtonChangedExRate = true;
			}
		}
		else if (Input::Conclusion(Input::Type::MOVE_DOWN)) {
			m_SelectedGraph = static_cast<SELECTABLE_GRAPH_TYPE>(m_SelectedGraph + 1);
			if (m_SelectedGraph > SELECTABLE_GRAPH_TYPE_END) {
				m_SelectedGraph = SELECTABLE_GRAPH_TYPE_END;
			}
			else {
				m_isButtonChangedExRate = true;
			}
		}
	}

	// ボタンのサイズが変更中なら変えてやる
	if (m_isButtonChangedExRate) {
		if (m_SelectedGraph == SELECTABLE_GRAPH_TYPE_START) {
			m_ButtonExRate[SELECTABLE_GRAPH_TYPE_START] += BUTTON_SIZE_CANGED_SPEED;
			m_ButtonExRate[SELECTABLE_GRAPH_TYPE_END] -= BUTTON_SIZE_CANGED_SPEED;
			if (m_ButtonExRate[SELECTABLE_GRAPH_TYPE_START] > BUTTON_MAX_SIZE &&
				m_ButtonExRate[SELECTABLE_GRAPH_TYPE_END] < 1.0f) {
				m_ButtonExRate[SELECTABLE_GRAPH_TYPE_START] = BUTTON_MAX_SIZE;
				m_ButtonExRate[SELECTABLE_GRAPH_TYPE_END] = 1.0f;
				m_isButtonChangedExRate = false;
			}
		}
		if (m_SelectedGraph == SELECTABLE_GRAPH_TYPE_END) {
			m_ButtonExRate[SELECTABLE_GRAPH_TYPE_START] -= BUTTON_SIZE_CANGED_SPEED;
			m_ButtonExRate[SELECTABLE_GRAPH_TYPE_END] += BUTTON_SIZE_CANGED_SPEED;
			if (m_ButtonExRate[SELECTABLE_GRAPH_TYPE_START] < 1.0f &&
				m_ButtonExRate[SELECTABLE_GRAPH_TYPE_END] > BUTTON_MAX_SIZE) {
				m_ButtonExRate[SELECTABLE_GRAPH_TYPE_START] = 1.0f;
				m_ButtonExRate[SELECTABLE_GRAPH_TYPE_END] = BUTTON_MAX_SIZE;
				m_isButtonChangedExRate = false;
			}
		}
	}

	// 次ボタンを押すと選択中のもので結果を変える
	if (m_LogoBoundCnt == LOGO_JUMP_NUM) {
		if (Input::Conclusion(Input::Type::NEXT) && m_LogoBoundCnt == LOGO_JUMP_NUM) {
			if (m_SelectedGraph == SELECTABLE_GRAPH_TYPE_START) {
				// プレイシーンへ
				SceneBace::g_scene_ID = Play_Scene;
			}
			else if (m_SelectedGraph == SELECTABLE_GRAPH_TYPE_END) {
				// ゲームを終了する
				exit(0); // プログラムを終了
			}
		}
	}

	if (m_LogoBoundCnt < LOGO_JUMP_NUM) {
		m_LogoPos[1] += m_LogoYSpeed;
		m_LogoYSpeed += LOGO_JUMP_GRAVITY;
	}

	if (m_LogoPos[1] < -128&& !m_isOffscreenBeen) {
		m_isOffscreenBeen = true;
		m_LogoPos[1] = -640;
	}

	if (m_LogoBoundCnt < LOGO_JUMP_NUM) {
		if (m_LogoPos[1] > TITLE_Y_POS_LOWER_LIMIT) {
			m_LogoPos[1] = TITLE_Y_POS_LOWER_LIMIT;
			m_LogoBoundCnt++;
			m_LogoYSpeed = LOGO_JUMP_POWER[m_LogoBoundCnt];
		}
	}

	// 次ボタンでプレイへ
	//if (Input::Conclusion(Input::Type::NEXT))
	//	SceneBace::g_scene_ID = Play_Scene;
}
void SceneTitle::Draw()
{
	// ボタンの座標
	int ButtonPos1[SELECTABLE_GRAPH_TYPE_NUM][2] = {
		{BUTTON_POS[SELECTABLE_GRAPH_TYPE_START][0] ,BUTTON_POS[SELECTABLE_GRAPH_TYPE_START][1]},
		{BUTTON_POS[SELECTABLE_GRAPH_TYPE_END][0] ,BUTTON_POS[SELECTABLE_GRAPH_TYPE_END][1]},
	};

	// いったん文字表示
	int logopos[2] = { static_cast<int>(m_LogoPos[0]), static_cast<int>(m_LogoPos[1]) };

	DebugString* dbgstr = DebugString::GetInstance();
	if (!m_isOffscreenBeen) {
		//DrawRotaGraph(logopos[0], logopos[1] + 32, 1.5f, 0.0f, m_Hndl[GRAPH_TYPE_COUNT1 + m_LogoBoundCnt], true);
	}
	else {
		string str = TITLE_NAME;
		int length = str.length();
		//dbgstr->AddFormatString(logopos[0] - 16 * length, logopos[1], FontType::HGP創英角ポップ体64_20, WHITE, "%s", TITLE_NAME);
		//DrawGraph(logopos[0]-370, logopos[1]-64, m_Hndl[GRAPH_TYPE_TITLELOGO], true);

	//	DrawRotaGraph3(logopos[0]-370, logopos[1] - 64, logopos[0] - 370+768/2, logopos[1] - 64+128, 1.0f+ m_TitleRogoExRate, 1.0f- m_TitleRogoExRate, 0.0f, m_Hndl[GRAPH_TYPE_TITLELOGO], true);
		DrawRotaGraph3(logopos[0], logopos[1] - 256, 768/2, 128, 1.0f + m_TitleRogoExRate, 1.0f - m_TitleRogoExRate, 0.0f, m_Hndl[GRAPH_TYPE_TITLELOGO], true);
	}

	// ボタン描画
	if (m_isOffscreenBeen) {
		// 選択画像
		DrawRotaGraph(HALF_SCREEN_SIZE_X, logopos[1] + 280 + 192 * m_SelectedGraph, m_ButtonExRate[m_SelectedGraph], 0.0f, m_Hndl[GRAPH_TYPE_LOGOGB], true);
		for (int GraphIndex = 0; GraphIndex < SELECTABLE_GRAPH_TYPE_NUM; GraphIndex++) {
			DrawRotaGraph(HALF_SCREEN_SIZE_X, logopos[1] + 280 + 192 * GraphIndex, m_ButtonExRate[GraphIndex], 0.0f, m_Hndl[GRAPH_TYPE_START + GraphIndex], true);
		}
		//DrawGraph(HALF_SCREEN_SIZE_X - 16, static_cast<int>(TITLE_Y_POS_LOWER_LIMIT) + 64, m_Hndl[GRAPH_TYPE_JUMP1 + m_LogoBoundCnt], true);
	}

	if (m_LogoBoundCnt < LOGO_JUMP_NUM&& !m_isOffscreenBeen) {
		DrawRotaGraph(logopos[0], logopos[1] + 32, 1.5f, 0.0f, m_Hndl[GRAPH_TYPE_COUNT1 + m_LogoBoundCnt], true);
		DrawGraph(HALF_SCREEN_SIZE_X - 16, static_cast<int>(TITLE_Y_POS_LOWER_LIMIT) + 64, m_Hndl[GRAPH_TYPE_JUMP1 + m_LogoBoundCnt], true);
	}

	//DrawRotaGraph3(HALF_SCREEN_SIZE_X/2, HALF_SCREEN_SIZE_Y, 0, 0,
	//	0.8f, 1.2f, 0.0f, m_Hndl[GRAPH_TYPE_TITLELOGO], true);
}
void SceneTitle::Fin()
{
}
