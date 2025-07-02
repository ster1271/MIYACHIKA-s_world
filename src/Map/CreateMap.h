#pragma once
#include "../Common.h"
#include "../Map/Map.h"

class CreateMap
{
private:
	int MouseX, MouseY;

	int DataHndl[MAPTIP_TYPE_NUM];

	int MapTipData[MAX_MAPTIP_Y][MAX_MAPTIP_X];	//全体マップ番号格納用
	int SetBlockNum;							//選択ブロック番号

	bool IsEditer;								//エディター中かどうか
	bool In_Entry;								//入力中かどうか
	bool IsFinish;								//入力が終了したかどうか

public:
	int GetBlockNum() { return SetBlockNum; }
	bool GetIsEditer() { return IsEditer; }
	void SetIsEditer(bool IsTrue = true) { IsEditer = IsTrue; }

	//コンストラクタ・デストラクタ
	CreateMap();
	~CreateMap();

	//初期化
	void Init();

	//終了処理
	void Exit();

	//読み込み
	void Load();

	//描画
	void Draw();

	//処理
	void Step();

	//設置するブロック選択処理
	void SelectBlock();

	//ブロック設置処理
	void SetBlock();

	//ブロック削除処理
	void EraseBlock();

	//保存処理(text or CSV)
	void SaveMapTip();

	//DrawRota用
	static bool WithinBox_Rota(int MousePosX, int MousePosY, VECTOR vPos, int WIDTH, int HEIGHT);

	//DrawGraph用
	static bool WithinBox(int MousePosX, int MousePosY, VECTOR vPos, int WIDTH, int HEIGHT);
};




