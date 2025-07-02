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
	cMap.Load(MAP_TYPE_00);
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
		//�G�f�B�^�[���[�h
		dbgStr->AddString(0, 0, FontType::HGP�n�p�p�|�b�v��24, WHITE, "�G�f�B�^�[���[�h�ł�");
		dbgStr->AddString(0, 24, FontType::HGP�n�p�p�|�b�v��24, WHITE, "SHIFT�Ńv���C�V�[��");
		dbgStr->AddFormatString(0, 48, FontType::HGP�n�p�p�|�b�v��24, WHITE, "�I�𒆂̃u���b�N�ԍ��F%d", cCreateMap.GetBlockNum());
		cCreateMap.Step();
		return;
	}
	else
	{
		//�ʏ�v���C���[�h(�����ɏ�����ǉ����Ă�������)
		dbgStr->AddString(0, 0, FontType::HGP�n�p�p�|�b�v��24, WHITE, "�v���C�ł�");
		dbgStr->AddString(0, 24, FontType::HGP�n�p�p�|�b�v��24, WHITE, "���N���b�N�������̓R���g���[���~�{�^���ŃN���A��");

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
}
