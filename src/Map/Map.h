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
	"data/play/map/Map00.txt",
	"data/play/map/Map01.txt",
	"data/play/map/Map02.txt",
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
	MAPTIP_TYPE_06,

	MAPTIP_TYPE_NUM,
};

//�}�b�v�f�ރf�[�^�̃t�@�C���p�X
static const char MapTipFilePath[MAPTIP_TYPE_NUM][256]
{
	"data/play/map/MapTip00.png",
	"data/play/map/MapTip01.png",
	"data/play/map/MapTip02.png",
	"data/play/map/MapTip03.png",
	"data/play/map/MapTip04.png",
	"data/play/map/MapTip05.png",
	"data/play/map/MapTip06.png",
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
};
