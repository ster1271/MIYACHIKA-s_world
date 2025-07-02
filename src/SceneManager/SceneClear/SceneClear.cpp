#include "DxLib.h"
#include "SceneClear.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Debug/DebugString.h"
//�}�b�v�f�ރf�[�^�̃t�@�C���p�X
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
	// �f�o�b�O�����\���p
	//DebugString* dbgStr = DebugString::GetInstance();
	//dbgStr->AddString(0, 0, FontType::HGP�n�p�p�|�b�v��24, WHITE, "�N���A�ł�");
	//dbgStr->AddString(0, 24, FontType::HGP�n�p�p�|�b�v��24, WHITE, "���N���b�N�������̓R���g���[���~�{�^���Ń^�C�g����");
	// ���{�^���Ń^�C�g����
	if (Input::Conclusion(Input::Type::NEXT))
		SceneBace::g_scene_ID = Title_Scene;
}
void SceneClear::Draw()
{
	// �Q�[���N���A�̕����ɕ\��

}
void SceneClear::Fin()
{
}