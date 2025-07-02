#include "MapManager.h"


//コンストラクタ・デストラクタ
CMapManager::CMapManager()
{

}

CMapManager::~CMapManager()
{

}

//初期化
void CMapManager::Init()
{
	cMap.Init();
	cGoal.Init();

	for (int Index = 0; Index != JumpBlockList.size(); Index++)
	{
		JumpBlockList[Index]->Init();
	}

	for (int Index = 0; Index != NeedleList.size(); Index++)
	{
		NeedleList[Index]->Init();
	}
}

//データ読み込み
void CMapManager::Load()
{
	cMap.Load();

	for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
	{
		for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
		{
			if (cMap.GetMapTip(IndexX, IndexY) != GOAL)
				continue;

			cGoal.Init(MapX + IndexX * MAPTIP_SIZE, MapY + IndexY * MAPTIP_SIZE);
			cGoal.Load();
			break;
		}
	}

	//ジャンプブロックの読み込み
	for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
	{
		for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
		{
			if (cMap.GetMapTip(IndexX,IndexY) != JUMP_BLOCK_01 && cMap.GetMapTip(IndexX, IndexY) != JUMP_BLOCK_02 &&
				cMap.GetMapTip(IndexX, IndexY) != JUMP_BLOCK_03)
				continue;

			CJumpBlock* TMP = new CJumpBlock;
			TMP->Init();
			TMP->Load();
			TMP->Init(MapX + IndexX * MAPTIP_SIZE, MapY + IndexY * MAPTIP_SIZE, cMap.GetMapTip(IndexX, IndexY) -1);
			JumpBlockList.push_back(TMP);
		}
	}

	//トゲの読み込み
	for (int IndexY = 0; IndexY < MAX_MAPTIP_Y; IndexY++)
	{
		for (int IndexX = 0; IndexX < MAX_MAPTIP_X; IndexX++)
		{
			if (cMap.GetMapTip(IndexX, IndexY) != NEEDLE)
				continue;

			CNeedle* TMP = new CNeedle;
			TMP->Init();
			TMP->Load();
			TMP->Init(MapX + IndexX * MAPTIP_SIZE, MapY + IndexY * MAPTIP_SIZE);
			NeedleList.push_back(TMP);
		}
	}
}

//処理
void CMapManager::Step()
{
	cMap.Step();
	cGoal.Step();

	for (int Index = 0; Index != JumpBlockList.size(); Index++)
	{
		JumpBlockList[Index]->Step();
	}

	for (int Index = 0; Index != NeedleList.size(); Index++)
	{
		NeedleList[Index]->Step();
	}
}

//描画
void CMapManager::Draw()
{
	cMap.Draw();
	cGoal.Draw();

	for (int Index = 0; Index != JumpBlockList.size(); Index++)
	{
		JumpBlockList[Index]->Draw();
	}

	for (int Index = 0; Index != NeedleList.size(); Index++)
	{
		NeedleList[Index]->Draw();
	}
}

//終了処理
void CMapManager::Exit()
{
	cMap.Exit();
	cGoal.Exit();

	for (int Index = 0; Index != JumpBlockList.size(); Index++)
	{
		JumpBlockList[Index]->Exit();
	}

	for (int Index = 0; Index != NeedleList.size(); Index++)
	{
		NeedleList[Index]->Exit();
	}
}