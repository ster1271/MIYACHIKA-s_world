#include "CreateMap.h"
#include "../Input/Input.h"
#include "../Debug/DebugString.h"

//�R���X�g���N�^
CreateMap::CreateMap()
{
	SetBlockNum = -1;
	In_Entry = false;
	IsFinish = false;

	for (int Index = 0; Index < MAPTIP_TYPE_NUM; Index++)
	{
		DataHndl[Index] = -1;
	}

	for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
	{
		for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
		{
			MapTipData[IndexY][IndexX] = -1;
		}
	}
}

//�f�X�g���N�^
CreateMap::~CreateMap() {};

//������
void CreateMap::Init()
{
	for (int Index = 0; Index < MAPTIP_TYPE_NUM; Index++)
	{
		DataHndl[Index] = -1;
	}

	for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
	{
		for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
		{
			MapTipData[IndexY][IndexX] = -1;
		}
	}

	SetBlockNum = -1;
	In_Entry = false;
	IsFinish = false;
}

//�I������
void CreateMap::Exit()
{
	SetBlockNum = 0;
	In_Entry = false;
	IsFinish = false;
}

//�ǂݍ���
void CreateMap::Load()
{
	for (int Index = 0; Index < MAPTIP_TYPE_NUM; Index++)
	{
		DataHndl[Index] = LoadGraph(MapTipFilePath[Index]);
	}
}

//�`��
void CreateMap::Draw()
{
	//�g���Ɛݒu�u���b�N�\��
	for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
	{
		for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
		{
			DrawBox(MapX + IndexX * MAPTIP_SIZE, MapY + IndexY * MAPTIP_SIZE,
				MapX + IndexX * MAPTIP_SIZE + MAPTIP_SIZE, MapY + IndexY * MAPTIP_SIZE + MAPTIP_SIZE,
				WHITE, false);

			DrawGraph(MapX + IndexX * MAPTIP_SIZE, MapY + IndexY * MAPTIP_SIZE, DataHndl[MapTipData[IndexY][IndexX]], false);
		}
	}

	//�u���b�N�̎�ޕ`��
	for (int Index = 0; Index < MAPTIP_TYPE_NUM; Index++)
	{
		DrawRotaGraph(70, 150 + 60 * Index, 1.5f, 0.0f, DataHndl[Index], false, false);
	}
}

//����
void CreateMap::Step()
{	
	//�ݒu����u���b�N�I������
	SelectBlock();

	//�u���b�N�ݒu����
	SetBlock();

	//�u���b�N�폜����
	EraseBlock();

	SaveMapTip();
}


//�ݒu����u���b�N�I������
void CreateMap::SelectBlock()
{
	if (CMouse::IsMouseKeep(MOUSE_INPUT_LEFT))
	{
		for (int Index = 0; Index < MAPTIP_TYPE_NUM; Index++)
		{
			//�}�E�X���W���I�т����u���b�N�͈͓̔��Ȃ�
			if (CMouse::WithinBox_Rota(VGet(70.0f, 150.0f + 60.0f * Index, 0.0f), 48, 48))
			{
				//�I�т����u���b�N�̔ԍ����i�[����
				SetBlockNum = Index;
			}
		}
	}
}


//�u���b�N�ݒu����
void CreateMap::SetBlock()
{
	if (CMouse::IsMouseKeep(MOUSE_INPUT_LEFT))
	{
		for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
		{
			for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
			{
				//�}�E�X���W���{�b�N�X�͈͓̔��Ȃ�
				if (CMouse::WithinBox(VGet((float)MapX + IndexX * (float)MAPTIP_SIZE, (float)MapY + IndexY * (float)MAPTIP_SIZE, 0.0f),
					MAPTIP_SIZE, MAPTIP_SIZE))
				{
					MapTipData[IndexY][IndexX] = SetBlockNum;
				}
			}
		}
		
	}
}

//�u���b�N�폜����
void CreateMap::EraseBlock()
{
	if (CMouse::IsMouseKeep(MOUSE_INPUT_LEFT))
	{
		//�I���u���b�N�������S������Ȃ��Ȃ珈�����Ȃ�
		if (SetBlockNum != 0)
			return;

		for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
		{
			for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
			{
				//�}�E�X���W���{�b�N�X�͈͓̔��Ȃ�
				if (CMouse::WithinBox(VGet((float)MapX + IndexX * (float)MAPTIP_SIZE, (float)MapY + IndexY * (float)MAPTIP_SIZE, 0.0f),
					MAPTIP_SIZE, MAPTIP_SIZE))
				{
					MapTipData[IndexY][IndexX] = -1;
				}
			}
		}
	}
}


//�ۑ�����(text or CSV)
void CreateMap::SaveMapTip()
{
	FILE* fp = nullptr;
	string FilePath = "data/Map/MapDataFile/";		//�t�@�C��������ꏊ
	string Extension = ".txt";						//�g���q

	if (CInput::IsKeyKeep(KEY_INPUT_S) && CInput::IsKeyKeep(KEY_INPUT_LCONTROL))
	{
		In_Entry = true;
	}

	if (In_Entry && !IsFinish)
	{
		DrawString(0, 0, "�t�@�C�����쐬��...", WHITE);
		DrawString(0, 16, "Enter�œ��͂��I���", WHITE);
		DrawString(0, 32, "Esc�œ��͂��L�����Z��", WHITE);

		char FileName[128];
		//�L�����Z���Ȃ���͂���߂�
		if (KeyInputSingleCharString(0, 55, 128, FileName, true) == 2)
		{
			In_Entry = false;
			return;
		}

		string TextName = FileName + Extension;
		//�t�@�C�����J��(�Ȃ���ΐV�K�쐬
		fopen_s(&fp, "data/Map/MapDataTextName.txt", "a+");
		if (fp != nullptr)
		{
			//�����ɒǉ�����
			fprintf(fp, "%s\n", TextName.c_str());
			fclose(fp);
		}

		//�t�@�C���p�X�Ɩ��O�Ɗg���q����������
		FilePath = FilePath + TextName;

		IsFinish = true;
	}

	//���͂��I�����Ă��Ȃ��Ȃ�ȉ��̏��������Ȃ�
	if (!IsFinish)
		return;

	int IndexX = 0;
	int IndexY = 0;
	int SaveData[MAX_MAPTIP_Y][MAX_MAPTIP_X] = { 0 };

	
	for (int DataIndexY = 0; DataIndexY < MAX_MAPTIP_Y; DataIndexY++)
	{
		for (int DataIndexX = 0; DataIndexX < MAX_MAPTIP_X; DataIndexX++)
		{
			//�ʕϐ��ɒl��n��
			SaveData[DataIndexY][DataIndexX] = MapTipData[DataIndexY][DataIndexX];

			//������� - 1��0�ɕύX������
			if (SaveData[DataIndexY][DataIndexX] == -1)
			{
				SaveData[DataIndexY][DataIndexX] = 0;
			}
		}
	}

	//�t�@�C�����J��(�Ȃ��Ȃ�V�K�쐬)
	fopen_s(&fp, FilePath.c_str(), "w");

	while (true)
	{
		//�z��̍Ō�ɓ��B������u\0�v�������o���I������
		if (IndexY == MAX_MAPTIP_Y)
		{
			fputc('\0', fp);
			break;
		}

		//�����R�[�h�ɑΉ�����悤�ɒl��ύX����
		int ConvertingValue = SaveData[IndexY][IndexX] + 48;

		//�����ǂݍ���
		fputc(ConvertingValue, fp);
		IndexX++;
	
		if (IndexX == MAX_MAPTIP_X)
		{
			//�ő�l�ɗ�������s����
			fputc('\n', fp);
			IndexY++;
			IndexX = 0;
		}
		else
		{
			//�ő�l�ł͂Ȃ��Ȃ�u,�v��ǉ�����
			fputc(',', fp);
		}
	}

	fclose(fp);
	IsFinish = false;
	In_Entry = false;
	SetIsEditer(false);
}
