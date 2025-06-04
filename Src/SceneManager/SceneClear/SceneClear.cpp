#include "DxLib.h"
#include "SceneClear.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Debug/DebugString.h"

void SceneClear::Init()
{
}
void SceneClear::Step()
{
	// �f�o�b�O�����\���p
	DebugString* dbgStr = DebugString::GetInstance();
	dbgStr->AddString(0, 0, FontType::HGP�n�p�p�|�b�v��24, WHITE, "�N���A�ł�");
	dbgStr->AddString(0, 24, FontType::HGP�n�p�p�|�b�v��24, WHITE, "���N���b�N�������̓R���g���[���~�{�^���Ń^�C�g����");
	// ���{�^���Ń^�C�g����
	if (Input::Conclusion(Input::Type::NEXT))
		SceneBace::g_scene_ID = Title_Scene;
}
void SceneClear::Draw()
{
}
void SceneClear::Fin()
{
}