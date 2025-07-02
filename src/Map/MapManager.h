#pragma once
#include "../Map/Map.h"
#include "../Goal/Goal.h"
#include "../JumpBlock/JumpBlock.h"
#include "../Needle/Needle.h"

class CMapManager
{
private:
	CMap cMap;
	CGoal cGoal;
	vector<CJumpBlock*> JumpBlockList;
	vector<CNeedle*> NeedleList;

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CMapManager();
	~CMapManager();


	CMap GetMapClass() { return cMap; }
	CGoal GetGoalClass() { return cGoal; }
	vector<CJumpBlock*> GetJumpBlockList() { return JumpBlockList; }
	vector<CNeedle*> GetNeedleList() { return NeedleList; }


	//������
	void Init();

	//�f�[�^�ǂݍ���
	void Load();

	//����
	void Step();

	//�`��
	void Draw();

	//�I������
	void Exit();

};
