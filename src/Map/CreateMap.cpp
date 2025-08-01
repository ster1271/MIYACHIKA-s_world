#include "CreateMap.h"
#include "../Input/Input.h"
#include "../Debug/DebugString.h"

const char ERASE[256] = { "data/Bloak/消しゴム.png" };


//コンストラクタ
CreateMap::CreateMap()
{
	MouseX = MouseY = 0.0f;

	EraseHndl = -1;
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
	IsSetStart = false;
	IsSetGoal = false;
	IsEditer = false;
	In_Entry = false;
	IsFinish = false;
}

//デストラクタ
CreateMap::~CreateMap() {};

//初期化
void CreateMap::Init()
{
	MouseX = MouseY = 0.0f;

	EraseHndl = -1;
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
	IsSetStart = false;
	IsSetGoal = false;
	IsEditer = false;
	In_Entry = false;
	IsFinish = false;
}

//終了処理
void CreateMap::Exit()
{
	MouseX = MouseY = 0.0f;

	EraseHndl = -1;
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
	IsSetStart = false;
	IsSetGoal = false;
	IsEditer = false;
	In_Entry = false;
	IsFinish = false;
}

//読み込み
void CreateMap::Load()
{
	EraseHndl = LoadGraph(ERASE);
	for (int Index = 0; Index < MAPTIP_TYPE_NUM; Index++)
	{
		DataHndl[Index] = LoadGraph(MapTipFilePath[Index]);
	}
}

//描画
void CreateMap::Draw()
{
	//枠線と設置ブロック表示
	for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
	{
		for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
		{
			//枠線
			DrawBox(BASE_VALUE_X + IndexX * MAP_TIP_SIZE.x, BASE_VALUE_Y + IndexY * MAP_TIP_SIZE.y,
				BASE_VALUE_X + IndexX * MAP_TIP_SIZE.x + MAP_TIP_SIZE.x, BASE_VALUE_Y + IndexY * MAP_TIP_SIZE.y + MAP_TIP_SIZE.y,
				WHITE, false);

			//値が-1なら描画しない
			if (MapTipData[IndexY][IndexX] == MAPTIP_TYPE_NONE)
				continue;

			//設置したブロック
			DrawGraph(BASE_VALUE_X + IndexX * MAP_TIP_SIZE.x, BASE_VALUE_Y + IndexY * MAP_TIP_SIZE.y, DataHndl[MapTipData[IndexY][IndexX]], true);
		}
	}

	//消しゴム描画
	DrawRotaGraph(70, 150, 1.5f, -DX_PI_F / 4, EraseHndl, true, false);
	for (int Index = 0; Index < MAPTIP_TYPE_NUM; Index++)
	{
		//選択用ブロックの描画
		DrawRotaGraph(70, 210 + 60 * Index, 1.5f, 0.0f, DataHndl[Index], true, false);
	}

	//マウスに追従と選択ブロック描画
	if (SetBlockNum == -1)
	{
		DrawRotaGraph(650, 35, 1.5f, -DX_PI_F / 4, EraseHndl, true, false);
		DrawRotaGraph(MouseX + 5, MouseY + 5, 1.0f, -DX_PI_F / 4, EraseHndl, true, false);
	}
	else
	{
		DrawRotaGraph(650 , 35, 1.5f, 0.0f, DataHndl[SetBlockNum], true, false);
		DrawRotaGraph(MouseX, MouseY, 1.0f, 0.0f, DataHndl[SetBlockNum], true, false);
	}
}

//本処理
void CreateMap::Step()
{	
	// デバッグ文字表示用
	DebugString* dbgStr = DebugString::GetInstance();

	//マウス座標取得
	GetMousePoint(&MouseX, &MouseY);

	//設置するブロック選択処理
	SelectBlock();

	//ブロック設置処理
	SetBlock();

	//ブロック削除処理
	EraseBlock();

	//マップチップの保存処理
	SaveMapTip();

	dbgStr->AddString(0, 0, FontType::HGP創英角ポップ体24, WHITE, "エディターモードです");
	dbgStr->AddString(0, 24, FontType::HGP創英角ポップ体24, WHITE, "SHIFTでプレイシーン");
	dbgStr->AddString(0, 48, FontType::HGP創英角ポップ体24, WHITE, "LCtrl + Sで保存モードに");
	dbgStr->AddString(400, 24, FontType::HGP創英角ポップ体24, WHITE, "選択中のブロック：");
}


//設置するブロック選択処理
void CreateMap::SelectBlock()
{
	if (Input::Mouse::Keep(MOUSE_INPUT_LEFT))
	{
		for (int Index = 0; Index < MAPTIP_TYPE_NUM; Index++)
		{
			//マウス座標が選びたいブロックの範囲内なら
			if (CreateMap::WithinBox_Rota(MouseX, MouseY, VGet(70.0f, 210.0f + 60.0f * Index, 0.0f), 48, 48))
			{
				//選びたいブロックの番号を格納する
				SetBlockNum = Index;
			}
		}
	}

	if (Input::Mouse::Keep(MOUSE_INPUT_LEFT))
	{
		if (CreateMap::WithinBox_Rota(MouseX, MouseY, VGet(70.0f, 150.0f, 0.0f), 48, 48))
		{
			//選びたいブロックの番号を格納する(消しゴム)
			SetBlockNum = -1;
		}
	}
}


//ブロック設置処理
void CreateMap::SetBlock()
{
	if (Input::Mouse::Keep(MOUSE_INPUT_LEFT))
	{	
		//選択ブロックが消しゴムなら処理しない
		if (SetBlockNum == MAPTIP_TYPE_NONE)
			return;

		for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
		{
			for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
			{
				//マウス座標がボックスの範囲内なら
				if (CreateMap::WithinBox(MouseX, MouseY, VGet((float)BASE_VALUE_X + IndexX * MAP_TIP_SIZE.x, (float)BASE_VALUE_Y + IndexY * MAP_TIP_SIZE.y, 0.0f),
					MAP_TIP_SIZE.x, MAP_TIP_SIZE.x))
				{

					//スタートとゴールは1個以上設置できないようにする
					if (IsSetStart && SetBlockNum == MAPTIP_TYPE_05 || 
						IsSetGoal && SetBlockNum == MAPTIP_TYPE_06)
						break;

					MapTipData[IndexY][IndexX] = SetBlockNum;

					//スタートかゴールを設置でフラグをtrueにする
					if (!IsSetStart && SetBlockNum == MAPTIP_TYPE_05)
					{
						IsSetStart = true;
					}
					else if(!IsSetGoal && SetBlockNum == MAPTIP_TYPE_06)
					{
						IsSetGoal = true;
					}
					return;
				}
			}
		}
		
	}
}

//ブロック削除処理
void CreateMap::EraseBlock()
{
	if (Input::Mouse::Keep(MOUSE_INPUT_LEFT))
	{
		//選択ブロックが消しゴムじゃないなら処理しない
		if (SetBlockNum != MAPTIP_TYPE_NONE)
			return;

		for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
		{
			for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
			{
				//マウス座標がボックスの範囲内なら
				if (CreateMap::WithinBox(MouseX, MouseY, VGet((float)BASE_VALUE_X + IndexX * MAP_TIP_SIZE.x, (float)BASE_VALUE_Y + IndexY * MAP_TIP_SIZE.y, 0.0f),
					MAP_TIP_SIZE.x, MAP_TIP_SIZE.x)) 
				{
					if (MapTipData[IndexY][IndexX] == MAPTIP_TYPE_05)
					{
						IsSetStart = false;
					}
					else if (MapTipData[IndexY][IndexX] == MAPTIP_TYPE_06)
					{
						IsSetGoal = false;
					}

					MapTipData[IndexY][IndexX] = -1;
				}
			}
		}
	}
}


//保存処理(text or CSV)
void CreateMap::SaveMapTip()
{
	FILE* fp = nullptr;
	string FilePath = "data/Bloak/MapDataFile/";		//ファイルを入れる場所
	string Extension = ".txt";							//拡張子

	if (Input::Key::Keep(KEY_INPUT_S) && Input::Key::Keep(KEY_INPUT_LCONTROL))
	{
		In_Entry = true;
	}

	if (In_Entry && !IsFinish)
	{
		DrawString(0, 0, "ファイル名作成中...", WHITE);
		DrawString(0, 16, "Enterで入力を終わる(正常に終了後、プレイシーンに戻る)", WHITE);
		DrawString(0, 32, "Escで入力をキャンセル", WHITE);

		char FileName[128];
		//キャンセルなら入力をやめる
		if (KeyInputSingleCharString(0, 55, 128, FileName, true) == 2)
		{
			In_Entry = false;
			return;
		}

		string TextName = FileName + Extension;
		//ファイルを開く(なければ新規作成
		fopen_s(&fp, "data/Bloak/MapDataTextName.txt", "a+");
		if (fp != nullptr)
		{
			//末尾に追加する
			fprintf(fp, "%s\n", TextName.c_str());
			fclose(fp);
		}

		//ファイルパスと名前と拡張子を結合する
		FilePath = FilePath + TextName;

		IsFinish = true;
	}

	//入力が終了していないなら以下の処理をしない
	if (!IsFinish)
		return;

	int IndexX = 0;
	int IndexY = 0;
	int SaveData[MAX_MAPTIP_Y][MAX_MAPTIP_X] = { 0 };

	
	for (int DataIndexY = 0; DataIndexY < MAX_MAPTIP_Y; DataIndexY++)
	{
		for (int DataIndexX = 0; DataIndexX < MAX_MAPTIP_X; DataIndexX++)
		{
			//別変数に値を渡す
			SaveData[DataIndexY][DataIndexX] = MapTipData[DataIndexY][DataIndexX];
		}
	}

	//ファイルを開く(ないなら新規作成)
	fopen_s(&fp, FilePath.c_str(), "w");

	while (true)
	{
		//配列の最後に到達したら「\0」を書き出し終了する
		if (IndexY == MAX_MAPTIP_Y)
		{
			fputc('\0', fp);
			break;
		}

		//文字コードに対応するように値を変更する
		int ConvertingValue = SaveData[IndexY][IndexX] + 48;

		//文字読み込み
		if (SaveData[IndexY][IndexX] != -1)
		{
			//数字の書き込み
			fputc(ConvertingValue, fp);
			IndexX++;
		}
		else
		{
			//-1の時は空白を書き込み
			fputc(' ', fp);
			IndexX++;
		}
		
	
		if (IndexX == MAX_MAPTIP_X)
		{
			//最大値に来たら改行する
			fputc('\n', fp);
			IndexY++;
			IndexX = 0;
		}
		else
		{
			//最大値ではないなら「,」を追加する
			fputc(',', fp);
		}
	}

	fclose(fp);
	IsFinish = false;
	In_Entry = false;
	SetIsEditer(false);
}


//マウス範囲内判定(DrawRota用)
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


//マウス範囲内判定(DrawGraph用)
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

