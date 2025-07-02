#pragma once
#include "../Common.h"
#include "../Map/Map.h"

class CreateMap
{
private:
	int MouseX, MouseY;

	int DataHndl[MAPTIP_TYPE_NUM];

	int MapTipData[MAX_MAPTIP_Y][MAX_MAPTIP_X];	//�S�̃}�b�v�ԍ��i�[�p
	int SetBlockNum;							//�I���u���b�N�ԍ�

	bool IsEditer;								//�G�f�B�^�[�����ǂ���
	bool In_Entry;								//���͒����ǂ���
	bool IsFinish;								//���͂��I���������ǂ���

public:
	int GetBlockNum() { return SetBlockNum; }
	bool GetIsEditer() { return IsEditer; }
	void SetIsEditer(bool IsTrue = true) { IsEditer = IsTrue; }

	//�R���X�g���N�^�E�f�X�g���N�^
	CreateMap();
	~CreateMap();

	//������
	void Init();

	//�I������
	void Exit();

	//�ǂݍ���
	void Load();

	//�`��
	void Draw();

	//����
	void Step();

	//�ݒu����u���b�N�I������
	void SelectBlock();

	//�u���b�N�ݒu����
	void SetBlock();

	//�u���b�N�폜����
	void EraseBlock();

	//�ۑ�����(text or CSV)
	void SaveMapTip();

	//DrawRota�p
	static bool WithinBox_Rota(int MousePosX, int MousePosY, VECTOR vPos, int WIDTH, int HEIGHT);

	//DrawGraph�p
	static bool WithinBox(int MousePosX, int MousePosY, VECTOR vPos, int WIDTH, int HEIGHT);
};




