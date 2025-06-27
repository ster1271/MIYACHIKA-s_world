#pragma once
#include "../Player/Player.h"
#include "../Map/Map.h"

class CollisionManager
{
public:
	// プレイヤーとマップとの当たり判定
	static void CheckHitPlayerToMap(CPlayer& cPlayer, CMap& cMap);

	// プレイヤーとジャンプブロックとの当たり判定
	static void CheckHitPlayerToJumpBlock(CPlayer& cPlayer, CMap& cMap);

	// プレイヤーととげとの当たり判定
	static void CheckHitPlayerToThorn(CPlayer& cPlayer, CMap& cMap);
};