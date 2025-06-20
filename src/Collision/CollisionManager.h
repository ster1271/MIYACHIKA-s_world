#pragma once
#include "../Player/Player.h"
#include "../Map/Map.h"

class CollisionManager
{
public:
	// プレイヤーとマップとの当たり判定
	static void CheckHitPlayerToMap(CPlayer& cPlayer, CMap& cMap);

	// 2つの座標がか重なっている量を取得
	static int GetOverlap(int iPosA, int iPosB);
};