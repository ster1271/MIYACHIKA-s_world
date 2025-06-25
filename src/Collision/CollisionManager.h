#pragma once
#include "../Player/Player.h"
#include "../Map/Map.h"

class CollisionManager
{
public:
	// プレイヤーとマップとの当たり判定
	static void CheckHitPlayerToMap(CPlayer& cPlayer, CMap& cMap);
};