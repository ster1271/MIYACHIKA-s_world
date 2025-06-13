#include "Map.h"

const float BASE_VALUE = 96.0f;

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
void CMap::Load(MAP_TYPE id)
{
	LoadMap(id);
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
			MapTipList[MapIndex].iHndl, false);
	}
}


//�}�b�v�̓ǂݍ���
bool CMap::LoadMap(MAP_TYPE id)
{
	MapTipInfo tmpInfo;

	fopen_s(&fp, MapFilePath[id], "r");

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
			tmpInfo.cPos = VGet((float)FileIndexX * MAP_TIP_SIZE.x, BASE_VALUE + (float)FileIndexY * MAP_TIP_SIZE.y, MAP_TIP_SIZE.z);
			tmpInfo.cRotate = VECTOR_ZERO;
			tmpInfo.Type_Id = (MAPTIP_TYPE)FileNum;
			tmpInfo.iHndl = LoadGraph(MapTipFilePath[FileNum]);

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