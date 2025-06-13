#include "Collision.h"
#include "CollisionManager.h"

// プレイヤーとマップとの当たり判定
void CollisionManager::CheckHitPlayerToMap(CPlayer& cPlayer, CMap& cMap)
{
	for (int MapTipIndex = 0; MapTipIndex != cMap.GetMapTipNum(); MapTipIndex++)
	{
		float PlayerPosX, PlayerPosY, PlayerSize;
		VECTOR MapPos, MapSIze;

		PlayerPosX = cPlayer.GetPosX();
		PlayerPosY = cPlayer.GetPosY();
		MapPos = cMap.GetPos(MapTipIndex);

		PlayerSize = cPlayer.GetSize();
		MapSIze = MAP_TIP_SIZE;

		// X軸
		// プレイヤーの右側が当たった時
		if (PlayerPosX + PlayerSize >= MapPos.x)
		{
			cPlayer.HitMapCalc_X(-1.0f);
		}
		// プレイヤーの左側が当たった時
		if (PlayerPosX <= MapPos.x + MapSIze.x)
		{
			cPlayer.HitMapCalc_X(1.0f);
		}

		// Y軸
		// プレイヤーの下側が当たった時
		if (PlayerPosY + PlayerSize >= MapPos.y)
		{
			cPlayer.HitMapCalc_Y(-1.0f);
		}
		// プレイヤーの上側が当たった時
		if (PlayerPosY <= MapPos.y + MapSIze.y)
		{
			cPlayer.HitMapCalc_Y(1.0f);
		}
	}
}
