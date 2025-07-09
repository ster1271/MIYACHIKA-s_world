#include "Map.h"

const char MAP_DATA_NEME_PATH[MAX_LEN] = { "data/Bloak/MapDataTextName.txt" };	//マップの名前格納テキスト

//コンストラクタ
CMap::CMap()
{
	fp = nullptr;
	MapTipList.clear();
}

//デストラクタ
CMap::~CMap()
{
	Exit();
}


//初期化
void CMap::Init()
{
	fp = nullptr;
	MapTipList.clear();
}

//後処理
void CMap::Exit()
{
	fp = nullptr;
	MapTipList.clear();
}

//読み込み
void CMap::Load(int Index)
{
	LoadMap(Index);
}

//情報更新
void CMap::UpData()
{

}

//本処理
void CMap::Step()
{

}

//描画
void CMap::Draw()
{
	for (int MapIndex = 0; MapIndex != MapTipList.size(); MapIndex++)
	{
		DrawGraph(MapTipList[MapIndex].cPos.x, MapTipList[MapIndex].cPos.y,
			MapTipList[MapIndex].iHndl, true);
	}
}


//マップの読み込み
bool CMap::LoadMap(int Index)
{
	//ファイル名が取得できなかったら以下の処理をしない
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
			// 数値部分を読み込む
			char tmp = fgetc(fp);
			int FileNum = tmp - '0';

			//必要な情報を格納
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

			//リストに格納
			MapTipList.push_back(tmpInfo);


			FileIndexX++;

			//「,」を飛ばすために読み込みを実行
			tmp = fgetc(fp);

			//EOFの場合は読み込み終了
			if (tmp == EOF)
			{
				break;
			}

			// 改行コードの場合は保存先を変更する
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

// マップチップの種類を変更
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


//読み込むマップの名前取得
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
		//ファイル読み込み失敗時
		return false;
	}

	return true;
}
