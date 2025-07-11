#include "DxLib.h"
#include "SceneClear.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Debug/DebugString.h"
//表示するゴールの数
constexpr int GOAL_NUM = 20;




//マップ素材データのファイルパス
static const char GRAPH_PATH[SceneClear::GRAPH_TYPE_NUM][256]
{
	"data/Clear/BG.png",
	"data/Clear/Bar.png",
	"data/Clear/Jump.png",
	"data/Clear/Goal.png",
	"data/Clear/Dead.png",
};

void SceneClear::Init()
{
	for (int i = 0; i < GRAPH_TYPE_NUM; i++) {
		if (m_Hndl[i] == -1)continue;
		m_Hndl[i] = -1;
	}

	for (int i = 0; i < GRAPH_TYPE_NUM; i++) {
		if (m_Hndl[i] != -1)continue;
		m_Hndl[i] = LoadGraph(GRAPH_PATH[i]);
	}

	//m_GoalVec.resize(GOAL_NUM);
	//for (auto& goal : m_GoalVec) {
	//	goal.m_Pos[0] = GetRand(SCREEN_SIZE_X) + HALF_SCREEN_SIZE_X;
	//	goal.m_Pos[1] = -(GetRand(SCREEN_SIZE_Y)+32);
	//}
}
void SceneClear::Step()
{
	// デバッグ文字表示用
	//DebugString* dbgStr = DebugString::GetInstance();
	//dbgStr->AddString(0, 0, FontType::HGP創英角ポップ体24, WHITE, "クリアです");
	//dbgStr->AddString(0, 24, FontType::HGP創英角ポップ体24, WHITE, "左クリックもしくはコントローラ×ボタンでタイトルに");

	// 次ボタンでタイトルへ
	if (Input::Conclusion(Input::Type::NEXT))
		SceneBace::g_scene_ID = Title_Scene;
}
void SceneClear::Draw()
{
	// ゲームクリアの文字に表示
	DrawGraph(0, 0, m_Hndl[GRAPH_TYPE_BG], true);
}
void SceneClear::Fin()
{
}