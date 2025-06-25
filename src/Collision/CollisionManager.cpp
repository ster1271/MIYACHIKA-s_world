#include "Collision.h"
#include "CollisionManager.h"

// プレイヤーとマップとの当たり判定
void CollisionManager::CheckHitPlayerToMap(CPlayer& cPlayer, CMap& cMap)
{
	for (int MapTipIndex = 0; MapTipIndex != cMap.GetMapTipNum(); MapTipIndex++)
	{
		float PlayerPosX, PlayerPosY, PlayerOldPosX, PlayerOldPosY, PlayerSize;
		VECTOR MapPos, MapSIze;

		PlayerPosX = cPlayer.GetPosX();
		PlayerPosY = cPlayer.GetPosY();
		PlayerOldPosX = cPlayer.GetOldPosX();
		PlayerOldPosY = cPlayer.GetOldPosY();
		MapPos = cMap.GetPos(MapTipIndex);

		PlayerSize = cPlayer.GetSize();
		MapSIze = MAP_TIP_SIZE;

		// Y軸のみの判定
		if (Collision::IsHitRect2D(
			(int)PlayerOldPosX, (int)PlayerPosY, (int)PlayerSize, (int)PlayerSize,
			(int)MapPos.x, (int)MapPos.y, (int)MapSIze.x, (int)MapSIze.y))
		{
			// プレイヤーの上側が当たった時
			if (cPlayer.GetDir(PLAYER_UP))
			{
				int Overlap1 = (int)((MapPos.y + MapSIze.y) - PlayerPosY);
				cPlayer.HitMapY(PlayerPosY + Overlap1);
			}

			// プレイヤーの下側が当たった時
			if (cPlayer.GetDir(PLAYER_DOWN))
			{
				int Overlap2 = (int)((PlayerPosY + PlayerSize) - MapPos.y);
  				cPlayer.HitMapY(PlayerPosY - Overlap2);
				cPlayer.HitLowerSide();
			}
		}
		// X軸のみの判定
		if (Collision::IsHitRect2D(
			(int)PlayerPosX, (int)PlayerOldPosY, (int)PlayerSize, (int)PlayerSize,
			(int)MapPos.x, (int)MapPos.y, (int)MapSIze.x, (int)MapSIze.y))
		{
			// プレイヤーの左側が当たった時
			if (cPlayer.GetDir(PLAYER_LEFT))
			{
				int Overlap3 = (int)((MapPos.x + MapSIze.x) - PlayerPosX);
				cPlayer.HitMapX(PlayerPosX + Overlap3);
			}

			// プレイヤーの右側が当たった時
			if (cPlayer.GetDir(PLAYER_RIGHT))
			{
				int Overlap4 = (int)((PlayerPosX + PlayerSize) - MapPos.x);
				cPlayer.HitMapX(PlayerPosX - Overlap4);
			}
		}
	}
}