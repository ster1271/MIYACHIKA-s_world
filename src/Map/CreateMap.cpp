#include "CreateMap.h"
#include "../Input/Input.h"
#include "../Debug/DebugString.h"

const char ERASE[256] = { "data/Bloak/�����S��.png" };

//�R���X�g���N�^
CreateMap::CreateMap()
{
	MouseX = MouseY = 0.0f;

	for (int Index = 0; Index < MAPTIP_TYPE_NUM; Index++)
	{
		DataHndl[Index] = -1;
	}
	EraseHndl = -1;

	for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
	{
		for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
		{
			MapTipData[IndexY][IndexX] = -1;
		}
	}

	SetBlockNum = -1;
	IsEditer = false;
	In_Entry = false;
	IsFinish = false;
}

//�f�X�g���N�^
CreateMap::~CreateMap() {};

//������
void CreateMap::Init()
{
	MouseX = MouseY = 0.0f;

	for (int Index = 0; Index < MAPTIP_TYPE_NUM; Index++)
	{
		DataHndl[Index] = -1;
	}
	EraseHndl = -1;

	for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
	{
		for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
		{
			MapTipData[IndexY][IndexX] = -1;
		}
	}

	SetBlockNum = -1;
	IsEditer = false;
	In_Entry = false;
	IsFinish = false;
}

//�I������
void CreateMap::Exit()
{
	MouseX = MouseY = 0.0f;

	MouseX = MouseY = 0.0f;

	for (int Index = 0; Index < MAPTIP_TYPE_NUM; Index++)
	{
		DataHndl[Index] = -1;
	}
	EraseHndl = -1;

	for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
	{
		for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
		{
			MapTipData[IndexY][IndexX] = -1;
		}
	}

	SetBlockNum = -1;
	IsEditer = false;
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

	EraseHndl = LoadGraph(ERASE);
}

//�`��
void CreateMap::Draw()
{
	//�g���Ɛݒu�u���b�N�\��
	for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
	{
		for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
		{
			DrawBox(BASE_VALUE_X + IndexX * MAP_TIP_SIZE.x, BASE_VALUE_Y + IndexY * MAP_TIP_SIZE.y,
				BASE_VALUE_X + IndexX * MAP_TIP_SIZE.x + MAP_TIP_SIZE.x, BASE_VALUE_Y + IndexY * MAP_TIP_SIZE.y + MAP_TIP_SIZE.y,
				WHITE, false);

			if (MapTipData[IndexY][IndexX] == MAPTIP_TYPE_NONE)
				continue;

			DrawGraph(BASE_VALUE_X + IndexX * MAP_TIP_SIZE.x, BASE_VALUE_Y + IndexY * MAP_TIP_SIZE.y, DataHndl[MapTipData[IndexY][IndexX]], false);
		}
	}

	//�u���b�N�̎�ޕ`��
	for (int Index = 0; Index < MAPTIP_TYPE_NUM; Index++)
	{
		DrawRotaGraph(70, 210 + 60 * Index, 1.5f, 0.0f, DataHndl[Index], false, false);
	}

	DrawRotaGraph(70, 150, 1.5f, 0.0f, EraseHndl, false, false);
}

//����
void CreateMap::Step()
{	
	// �f�o�b�O�����\���p
	DebugString* dbgStr = DebugString::GetInstance();

	GetMousePoint(&MouseX, &MouseY);

	//�ݒu����u���b�N�I������
	SelectBlock();

	//�u���b�N�ݒu����
	SetBlock();

	//�u���b�N�폜����
	EraseBlock();

	SaveMapTip();

	//�G�f�B�^�[���[�h

	dbgStr->AddString(0, 0, FontType::HGP�n�p�p�|�b�v��24, WHITE, "�G�f�B�^�[���[�h�ł�");
	dbgStr->AddString(0, 24, FontType::HGP�n�p�p�|�b�v��24, WHITE, "SHIFT�Ńv���C�V�[��");
	dbgStr->AddFormatString(0, 48, FontType::HGP�n�p�p�|�b�v��24, WHITE, "�I�𒆂̃u���b�N�ԍ��F%d", cCreateMap.GetBlockNum());
}


//�ݒu����u���b�N�I������
void CreateMap::SelectBlock()
{
	if (Input::Mouse::Keep(MOUSE_INPUT_LEFT))
	{
		for (int Index = 0; Index < MAPTIP_TYPE_NUM; Index++)
		{
			//�}�E�X���W���I�т����u���b�N�͈͓̔��Ȃ�
			if (CreateMap::WithinBox_Rota(MouseX, MouseY, VGet(70.0f, 210.0f + 60.0f * Index, 0.0f), 48, 48))
			{
				//�I�т����u���b�N�̔ԍ����i�[����
				SetBlockNum = Index;
			}
		}
	}

	if (Input::Mouse::Keep(MOUSE_INPUT_LEFT))
	{
		if (CreateMap::WithinBox_Rota(MouseX, MouseY, VGet(70.0f, 150.0f, 0.0f), 48, 48))
		{
			//�I�т����u���b�N�̔ԍ����i�[����
			SetBlockNum = -1;
		}
	}
}


//�u���b�N�ݒu����
void CreateMap::SetBlock()
{
	if (Input::Mouse::Keep(MOUSE_INPUT_LEFT))
	{
		for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
		{
			for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
			{
				//�}�E�X���W���{�b�N�X�͈͓̔��Ȃ�
				if (CreateMap::WithinBox(MouseX, MouseY, VGet((float)BASE_VALUE_X + IndexX * MAP_TIP_SIZE.x, (float)BASE_VALUE_Y + IndexY * MAP_TIP_SIZE.y, 0.0f),
					MAP_TIP_SIZE.x, MAP_TIP_SIZE.x))
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
	if (Input::Mouse::Keep(MOUSE_INPUT_LEFT))
	{
		//�I���u���b�N�������S������Ȃ��Ȃ珈�����Ȃ�
		if (SetBlockNum != -1)
			return;

		for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
		{
			for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
			{
				//�}�E�X���W���{�b�N�X�͈͓̔��Ȃ�
				if (CreateMap::WithinBox(MouseX, MouseY, VGet((float)BASE_VALUE_X + IndexX * MAP_TIP_SIZE.x, (float)BASE_VALUE_Y + IndexY * MAP_TIP_SIZE.y, 0.0f),
					MAP_TIP_SIZE.x, MAP_TIP_SIZE.x)) 
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
	string FilePath = "data/Bloak/MapDataFile/";		//�t�@�C��������ꏊ
	string Extension = ".txt";							//�g���q

	if (Input::Key::Keep(KEY_INPUT_S) && Input::Key::Keep(KEY_INPUT_LCONTROL))
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
		fopen_s(&fp, "data/Bloak/MapDataTextName.txt", "a+");
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
		if (SaveData[IndexY][IndexX] != -1)
		{
			//�����̏�������
			fputc(ConvertingValue, fp);
			IndexX++;
		}
		else
		{
			//-1�̎��͋󔒂���������
			fputc(' ', fp);
			IndexX++;
		}
		
	
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


//�}�E�X�͈͓�����(DrawRota�p)
bool CreateMap::WithinBox_Rota(int MousePosX, int MousePosY, VECTOR vPos, int WIDTH, int HEIGHT)
{
	if (MousePosX < vPos.x + WIDTH / 2 && MousePosX > vPos.x - WIDTH / 2)
	{
		if (MousePosY < vPos.y + HEIGHT / 2 && MousePosY > vPos.y - HEIGHT / 2)
		{
			return true;
		}
	}

	return false;
}


//�}�E�X�͈͓�����(DrawGraph�p)
bool CreateMap::WithinBox(int MousePosX, int MousePosY, VECTOR vPos, int WIDTH, int HEIGHT)
{
	if (MousePosX > vPos.x && MousePosX < vPos.x + WIDTH)
	{
		if (MousePosY > vPos.y && MousePosY < vPos.y + HEIGHT)
		{
			return true;
		}
	}

	return false;
}

