#include "Map.h"

const char MAP_DATA_NEME_PATH[MAX_LEN] = { "data/Bloak/MapDataTextName.txt" };	//�}�b�v�̖��O�i�[�e�L�X�g

//�R���X�g���N�^
CMap::CMap()
{
	fp = nullptr;
	MapTipList.clear();
}

//�f�X�g���N�^
CMap::~CMap()
{
	Exit();
}


//������
void CMap::Init()
{
	fp = nullptr;
	MapTipList.clear();
}

//�㏈��
void CMap::Exit()
{
	fp = nullptr;
	MapTipList.clear();
}

//�ǂݍ���
void CMap::Load(int Index)
{
	LoadMap(Index);
}

//���X�V
void CMap::UpData()
{

}

//�{����
void CMap::Step()
{

}

//�`��
void CMap::Draw()
{
	for (int MapIndex = 0; MapIndex != MapTipList.size(); MapIndex++)
	{
		DrawGraph(MapTipList[MapIndex].cPos.x, MapTipList[MapIndex].cPos.y,
			MapTipList[MapIndex].iHndl, true);
	}
}


//�}�b�v�̓ǂݍ���
bool CMap::LoadMap(int Index)
{
	//�t�@�C�������擾�ł��Ȃ�������ȉ��̏��������Ȃ�
	if (!GetMapName(Index))
		return false;

	fp = nullptr;
	MapTipInfo tmpInfo;

	fopen_s(&fp, Path.c_str(), "r");

	if (fp != nullptr)
	{
		int FileIndexX = 0;
		int FileIndexY = 0;

		while(true)
		{
			// ���l������ǂݍ���
			char tmp = fgetc(fp);
			int FileNum = tmp - '0';

			//�K�v�ȏ����i�[
			tmpInfo.cPos = VGet(BASE_VALUE_X + (float)FileIndexX * MAP_TIP_SIZE.x, BASE_VALUE_Y + (float)FileIndexY * MAP_TIP_SIZE.y, MAP_TIP_SIZE.z);
			tmpInfo.cRotate = VGet(0.0f, 0.0f, 0.0f);
			tmpInfo.Type_Id = (MAPTIP_TYPE)FileNum;
			tmpInfo.iHndl = -1;
			if (tmpInfo.Type_Id >= 0)
				tmpInfo.iHndl = LoadGraph(MapTipFilePath[FileNum]);

			if (tmpInfo.Type_Id == MAPTIP_TYPE_05)
			{
				cStartPos = tmpInfo.cPos;
			}

			//���X�g�Ɋi�[
			MapTipList.push_back(tmpInfo);


			FileIndexX++;

			//�u,�v���΂����߂ɓǂݍ��݂����s
			tmp = fgetc(fp);

			//EOF�̏ꍇ�͓ǂݍ��ݏI��
			if (tmp == EOF)
			{
				break;
			}

			// ���s�R�[�h�̏ꍇ�͕ۑ����ύX����
			if (tmp == '\n')
			{
				FileIndexY++;
				FileIndexX = 0;
			}
		}
		fclose(fp);
		return true;
	}
	else
	{
		return false;
	}
}

// �}�b�v�`�b�v�̎�ނ�ύX
void CMap::ChangeTypeID(int iMapTipNum)
{
	if (MapTipList[iMapTipNum].Type_Id == MAPTIP_TYPE_01)
	{
		MapTipList[iMapTipNum].Type_Id = MAPTIP_TYPE_02;
		MapTipList[iMapTipNum].iHndl = LoadGraph(MapTipFilePath[MAPTIP_TYPE_02]);
	}
	else if (MapTipList[iMapTipNum].Type_Id == MAPTIP_TYPE_02)
	{
		MapTipList[iMapTipNum].Type_Id = MAPTIP_TYPE_03;
		MapTipList[iMapTipNum].iHndl = LoadGraph(MapTipFilePath[MAPTIP_TYPE_03]);
	}
	else if (MapTipList[iMapTipNum].Type_Id == MAPTIP_TYPE_03)
	{
		MapTipList[iMapTipNum].Type_Id = MAPTIP_TYPE_01;
		MapTipList[iMapTipNum].iHndl = LoadGraph(MapTipFilePath[MAPTIP_TYPE_01]);
	}
}


//�ǂݍ��ރ}�b�v�̖��O�擾
bool CMap::GetMapName(int MapIndex)
{
	fp = nullptr;
	Path = "data/Bloak/MapDataFile/";

	fopen_s(&fp, MAP_DATA_NEME_PATH, "r");

	if (fp != nullptr)
	{
		char TextName[MAX_LEN] = { 0 };
		unsigned int NameSize = (unsigned int)sizeof(TextName);

		int cnt = 0;
		while (cnt <= MapIndex)
		{
			fscanf_s(fp, "%s", TextName, NameSize);
			cnt++;
		}
		Path = Path + (string)TextName;

		fclose(fp);
	}
	else
	{
		//�t�@�C���ǂݍ��ݎ��s��
		return false;
	}

	return true;
}
