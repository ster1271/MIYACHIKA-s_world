#include "../../Collision/CollisionManager.h"
#include "../../Input/Input.h"
#include "ScenePlay.h"
#include "../../SoundManager/SoundManager.h"
#include "../../Font/Font.h"
#include "../../Debug/DebugString.h"

void ScenePlay::Init()
{
	cPlayer.Init();
	cMap.Init();
	cMap.Load(MAP_TYPE_00);
}

void ScenePlay::Step()
{	
	// �f�o�b�O�����\���p
	DebugString* dbgStr = DebugString::GetInstance();
	dbgStr->AddString(0, 0, FontType::HGP�n�p�p�|�b�v��24, WHITE, "�v���C�ł�");
	dbgStr->AddString(0, 24, FontType::HGP�n�p�p�|�b�v��24, WHITE, "���N���b�N�������̓R���g���[���~�{�^���ŃN���A��");

	cPlayer.Step();
	cMap.Step();

	Collision();

	cPlayer.Update();

	// ���{�^���ŃN���A��
	if (Input::Conclusion(Input::Type::NEXT))
		SceneBace::g_scene_ID = Clear_Scene;
}
void ScenePlay::Draw()
{
	cPlayer.Draw();
	cMap.Draw();
}
void ScenePlay::Fin()
{
	cPlayer.Fin();
	cMap.Exit();
}

void ScenePlay::Collision()
{
	CollisionManager::CheckHitPlayerToMap(cPlayer, cMap);
}
