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

		if (Collision::IsHitRect2D(
			(int)PlayerPosX, (int)PlayerPosY, (int)PlayerSize, (int)PlayerSize,
			(int)MapPos.x, (int)MapPos.y, (int)MapSIze.x, (int)MapSIze.y))
		{
			// プレイヤーの上側が当たった時
			if (cPlayer.GetDir(PLAYER_UP))
			{
				int Overlap1 = GetOverlap((int)PlayerPosY, (int)(MapPos.y + MapSIze.y));
				cPlayer.SetPosY(PlayerOldPosY);
			}

			// プレイヤーの下側が当たった時
			if (cPlayer.GetDir(PLAYER_DOWN))
			{
				int Overlap2 = GetOverlap((int)MapPos.y, (int)(PlayerPosY + PlayerSize));
				cPlayer.SetPosY(PlayerOldPosY);
			}

			// プレイヤーの左側が当たった時
			if (cPlayer.GetDir(PLAYER_LEFT))
			{
				int Overlap3 = GetOverlap((int)PlayerPosX, (int)(MapPos.x + MapSIze.x));
				cPlayer.SetPosX(PlayerOldPosX);
			}

			// プレイヤーの右側が当たった時
			if (cPlayer.GetDir(PLAYER_RIGHT))
			{
				int Overlap4 = GetOverlap((int)MapPos.x, (int)(PlayerPosX + PlayerSize));
				cPlayer.SetPosX(PlayerOldPosX);
			}
		}
	}
}

// 2つの座標がか重なっている量を取得
int CollisionManager::GetOverlap(int iPosA, int iPosB)
{
	int ret = iPosA - iPosB;
	return abs(ret);
}