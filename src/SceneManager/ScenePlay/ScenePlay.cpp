#include "../../Collision/CollisionManager.h"
#include "../../Input/Input.h"
#include "ScenePlay.h"
#include "../../SoundManager/SoundManager.h"
#include "../../Font/Font.h"
#include "../../Debug/DebugString.h"

void ScenePlay::Init()
{
	cCreateMap.Init();
	cCreateMap.Load();
	cMap.Init();
	cMap.Load(CMap::MapID);
	cPlayer.Init(cMap.GetStartPos());
}

void ScenePlay::Step()
{	
	// �f�o�b�O�����\���p
	DebugString* dbgStr = DebugString::GetInstance();

	// ���{�^���ŃN���A��
	if (Input::Conclusion(Input::Type::NEXT))
		SceneBace::g_scene_ID = Clear_Scene;

	//�G�f�B�^�[��ʐ؂�ւ�
	if (Input::Key::Push(KEY_INPUT_LSHIFT))
	{
		if (!cCreateMap.GetIsEditer())
		{
			cCreateMap.SetIsEditer(true);
		}
		else
		{
			cCreateMap.SetIsEditer(false);
		}
	}

	if (cCreateMap.GetIsEditer())
	{
		cCreateMap.Step();
		return;
	}
	else
	{
		//�ʏ�v���C���[�h(�����ɏ�����ǉ����Ă�������)
		dbgStr->AddString(0, 0, FontType::HGP�n�p�p�|�b�v��24, WHITE, "�v���C�ł�");
		dbgStr->AddString(0, 24, FontType::HGP�n�p�p�|�b�v��24, WHITE, "LShift�ŃG�f�B�^�[���[�h�ɕύX");

		cPlayer.Step();
		cMap.Step();

		Collision();

		cPlayer.Update();
	}
}
void ScenePlay::Draw()
{
	if (cCreateMap.GetIsEditer())
	{
		cCreateMap.Draw();
	}
	else
	{
		cMap.Draw();
		cPlayer.Draw();
	}
}
void ScenePlay::Fin()
{
	cCreateMap.Exit();
	cMap.Exit();
	cPlayer.Fin();
}

void ScenePlay::Collision()
{
	CollisionManager::CheckHitPlayerToMap(cPlayer, cMap);
	CollisionManager::CheckHitPlayerToJumpBlock(cPlayer, cMap);
	CollisionManager::CheckHitPlayerToThorn(cPlayer, cMap);
	CollisionManager::CheckHitPlayerToGoal(cPlayer, cMap);
}
