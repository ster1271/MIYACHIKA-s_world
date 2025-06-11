#include "DxLib.h"
#include "SceneTitle.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Debug/DebugString.h"
#include "../../SoundManager/SoundManager.h"

void SceneTitle::Init()
{
	// �t�H���g���[�h
	Font::Load();
}

void SceneTitle::Step()
{
	// �f�o�b�O�����\���p
	DebugString* dbgStr = DebugString::GetInstance();
	dbgStr->AddString(0, 0, FontType::HGP�n�p�p�|�b�v��24, WHITE, "�^�C�g���ł�");
	dbgStr->AddString(0, 24, FontType::HGP�n�p�p�|�b�v��24, WHITE, "���N���b�N�������̓R���g���[���~�{�^���Ńv���C��");

	// ���{�^���Ńv���C��
	if (Input::Conclusion(Input::Type::NEXT))
		SceneBace::g_scene_ID = Play_Scene;
}
void SceneTitle::Draw()
{

}
void SceneTitle::Fin()
{
}
