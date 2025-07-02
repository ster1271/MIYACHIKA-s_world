#include "DxLib.h"
#include "SceneClear.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Debug/DebugString.h"
//マップ素材データのファイルパス
static const char GRAPH_PATH[SceneClear::GRAPH_TYPE_NUM][256]
{
	"data/Bloak/Block.png",
	"data/Bloak/Block.png",
	"data/Bloak/Thorn.png",
	"data/Bloak/Goal.png",
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

}
void SceneClear::Fin()
{
}