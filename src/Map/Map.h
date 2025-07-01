#pragma once
#include "../Common.h"

const VECTOR MAP_TIP_SIZE = VGet(32.0f, 32.0f, 0.0f);
// 35
// 

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
	"data/Bloak/Map1.txt",
	"data/Bloak/Map2.txt",
	"data/Bloak/Map3.txt",
};

//マップ素材データの種類
const enum MAPTIP_TYPE
{
	MAPTIP_TYPE_NONE = -1,

	MAPTIP_TYPE_00,		// ブロック
	MAPTIP_TYPE_01,		// ジャンプブロック1
	MAPTIP_TYPE_02,		// ジャンプブロック2
	MAPTIP_TYPE_03,		// ジャンプブロック3
	MAPTIP_TYPE_04,		// とげ
	MAPTIP_TYPE_05,		// ゴール

	MAPTIP_TYPE_NUM,
};

//マップ素材データのファイルパス
static const char MapTipFilePath[MAPTIP_TYPE_NUM][256]
{
	"data/Bloak/Block.png",
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

	// マップチップの種類を変更
	void ChangeTypeID(int iMapTipNum);

	//====================
	//   取得・設定関連
	//====================

	// マップチップの座標取得
	VECTOR& GetPos(int iMapTipNum) { return MapTipList[iMapTipNum].cPos; }
	// マップチップの種類取得
	MAPTIP_TYPE& GetTypeID(int iMapTipNum) { return MapTipList[iMapTipNum].Type_Id; }

	// プレイヤーの大きさ
	int GetMapTipNum() { return MapTipList.size(); }
};
