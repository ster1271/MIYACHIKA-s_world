#include "DxLib.h"
#include "SceneClear.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Debug/DebugString.h"
//�\������S�[���̐�
constexpr int GOAL_NUM = 20;

// �S�[���\�����W
constexpr int GOAL_POS[GOAL_NUM][2] = {
	{10,-10},
	{2,2},
	{2,2},
	{2,2},
	{2,2},
	{2,2},
	{2,2},
	{2,2},
	{2,2},
	{2,2},
};

//�}�b�v�f�ރf�[�^�̃t�@�C���p�X
static const char GRAPH_PATH[SceneClear::GRAPH_TYPE_NUM][256]
{
	"data/Clear/BG.png",
	"data/Bloak/Block.png",
	"data/Bloak/Thorn.png",
	//"data/Clear/BG.png",
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

	m_GoalVec.resize(GOAL_NUM);
	for (auto& goal : m_GoalVec) {
		goal.m_Pos[0] = GetRand(SCREEN_SIZE_X) + HALF_SCREEN_SIZE_X;
		goal.m_Pos[1] = -(GetRand(SCREEN_SIZE_Y)+32);
	}
}
void SceneClear::Step()
{
	// �f�o�b�O�����\���p
	//DebugString* dbgStr = DebugString::GetInstance();
	//dbgStr->AddString(0, 0, FontType::HGP�n�p�p�|�b�v��24, WHITE, "�N���A�ł�");
	//dbgStr->AddString(0, 24, FontType::HGP�n�p�p�|�b�v��24, WHITE, "���N���b�N�������̓R���g���[���~�{�^���Ń^�C�g����");
	for (auto& goal : m_GoalVec) {
		goal.m_Pos[0] -= 4;
		goal.m_Pos[1] += 4;
		if (goal.m_Pos[0]<-32 || goal.m_Pos[1]>SCREEN_SIZE_Y+32) {
			goal.m_Pos[0] = GetRand(SCREEN_SIZE_X) + HALF_SCREEN_SIZE_X;
			goal.m_Pos[1] = -(GetRand(SCREEN_SIZE_Y) + 32);
		}
	}
	// ���{�^���Ń^�C�g����
	if (Input::Conclusion(Input::Type::NEXT))
		SceneBace::g_scene_ID = Title_Scene;
}
void SceneClear::Draw()
{
	// �Q�[���N���A�̕����ɕ\��
	DrawGraph(0, 0, m_Hndl[GRAPH_TYPE_BG], true);


	for (auto& goal : m_GoalVec) {
		DrawGraph(goal.m_Pos[0], goal.m_Pos[1], m_Hndl[GRAPH_TYPE_GOAL], true);
	}
}
void SceneClear::Fin()
{
}