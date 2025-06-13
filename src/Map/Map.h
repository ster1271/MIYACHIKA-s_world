#pragma once
#include "../Common.h"

const VECTOR MAP_TIP_SIZE = VGet(32.0f, 32.0f, 0.0f);

//マップデータの種類
enum MAP_TYPE
{
	MAP_TYPE_00,		//ステージ0
	MAP_TYPE_01,		//ステージ1
	MAP_TYPE_02,		//ステージ2

	MAP_MAX_NUM,		//ステージ最大数
};

//マップデータのファイルパス
static const char MapFilePath[MAP_MAX_NUM][256]
{
	"data/play/map/Map00.txt",
	"data/play/map/Map01.txt",
	"data/play/map/Map02.txt",
};

//マップ素材データの種類
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

//マップ素材データのファイルパス
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

	vector<MapTipInfo> MapTipList;		//マップチップ情報格納リスト

public:
	//コンストラクタ・デストラクタ
	CMap();
	~CMap();

	//初期化
	void Init();

	//後処理
	void Exit();

	//読み込み
	//引数：マップデータの種類
	void Load(MAP_TYPE id);

	//情報更新
	void UpData();

	//本処理
	void Step();

	//描画
	void Draw();

	//マップの読み込み
	bool LoadMap(MAP_TYPE id);
};
