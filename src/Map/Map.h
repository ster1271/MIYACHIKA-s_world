#pragma once
#include "../Common.h"

const VECTOR MAP_TIP_SIZE = VGet(32.0f, 32.0f, 0.0f);

//�}�b�v�f�[�^�̎��
enum MAP_TYPE
{
	MAP_TYPE_00,		//�X�e�[�W0
	MAP_TYPE_01,		//�X�e�[�W1
	MAP_TYPE_02,		//�X�e�[�W2

	MAP_MAX_NUM,		//�X�e�[�W�ő吔
};

//�}�b�v�f�[�^�̃t�@�C���p�X
static const char MapFilePath[MAP_MAX_NUM][256]
{
	"data/Bloak/Map.txt",
	"data/Bloak/Map.txt",
	"data/Bloak/Map.txt",
};

//�}�b�v�f�ރf�[�^�̎��
const enum MAPTIP_TYPE
{
	MAPTIP_TYPE_00,
	MAPTIP_TYPE_01,
	MAPTIP_TYPE_02,
	MAPTIP_TYPE_03,
	MAPTIP_TYPE_04,
	MAPTIP_TYPE_05,

	MAPTIP_TYPE_NUM,
};

//�}�b�v�f�ރf�[�^�̃t�@�C���p�X
static const char MapTipFilePath[MAPTIP_TYPE_NUM][256]
{
	"data/Bloak/Floor.png",
	"data/Bloak/JumpBlock1.png",
	"data/Bloak/JumpBlock2.png",
	"data/Bloak/JumpBlock3.png",
	"data/Bloak/Thorn.png",
	"data/Bloak/Goal.png",
};


class CMap
{
public:
	FILE* fp;

	struct MapTipInfo
	{
		VECTOR cPos;
		VECTOR cRotate;
		MAPTIP_TYPE Type_Id;
		int iHndl;
	};

	vector<MapTipInfo> MapTipList;		//�}�b�v�`�b�v���i�[���X�g

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CMap();
	~CMap();

	//������
	void Init();

	//�㏈��
	void Exit();

	//�ǂݍ���
	//�����F�}�b�v�f�[�^�̎��
	void Load(MAP_TYPE id);

	//���X�V
	void UpData();

	//�{����
	void Step();

	//�`��
	void Draw();

	//�}�b�v�̓ǂݍ���
	bool LoadMap(MAP_TYPE id);

	//====================
	//   �擾�E�ݒ�֘A
	//====================

	// �v���C���[�̍��W�擾
	VECTOR& GetPos(int iMapTipNum) { return MapTipList[iMapTipNum].cPos; }

	// �v���C���[�̑傫��
	int GetMapTipNum() { return MapTipList.size(); }
};
