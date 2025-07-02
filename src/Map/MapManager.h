#pragma once
#include "../Map/Map.h"
#include "../Goal/Goal.h"
#include "../JumpBlock/JumpBlock.h"
#include "../Needle/Needle.h"

class CMapManager
{
private:
	CMap cMap;
	CGoal cGoal;
	vector<CJumpBlock*> JumpBlockList;
	vector<CNeedle*> NeedleList;

public:
	//コンストラクタ・デストラクタ
	CMapManager();
	~CMapManager();


	CMap GetMapClass() { return cMap; }
	CGoal GetGoalClass() { return cGoal; }
	vector<CJumpBlock*> GetJumpBlockList() { return JumpBlockList; }
	vector<CNeedle*> GetNeedleList() { return NeedleList; }


	//初期化
	void Init();

	//データ読み込み
	void Load();

	//処理
	void Step();

	//描画
	void Draw();

	//終了処理
	void Exit();

};
