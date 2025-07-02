#include "Collision.h"
#include "CollisionManager.h"

// プレイヤー初期座標
const float INIT_POS_X = (float)(SCREEN_SIZE_X / 2);
const float INIT_POS_Y = (float)(SCREEN_SIZE_Y / 2);

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

		if (cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_00)
		{
			// Y軸のみの判定
			if (Collision::IsHitRect2D(
				(int)PlayerOldPosX, (int)PlayerPosY, (int)PlayerSize, (int)PlayerSize,
				(int)MapPos.x, (int)MapPos.y, (int)MapSIze.x, (int)MapSIze.y))
			{
				// プレイヤーの上側が当たった時の処理
				if (cPlayer.GetDir(PLAYER_UP))
				{
					int Overlap1 = (int)((MapPos.y + MapSIze.y) - PlayerPosY);
					cPlayer.HitMapY(PlayerPosY + Overlap1);
					cPlayer.HitUpperSide();
				}

				// プレイヤーの下側が当たった時の処理
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
				// プレイヤーの左側が当たった時の処理
				if (cPlayer.GetDir(PLAYER_LEFT))
				{
					cPlayer.HitMapX(PlayerOldPosX);
				}

				// プレイヤーの右側が当たった時の処理
				if (cPlayer.GetDir(PLAYER_RIGHT))
				{
					cPlayer.HitMapX(PlayerOldPosX);
				}
			}
		}
	}
}

// プレイヤーとジャンプブロックとの当たり判定
void CollisionManager::CheckHitPlayerToJumpBlock(CPlayer& cPlayer, CMap& cMap)
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
		
		if (cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_01 ||
			cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_02 ||
			cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_03)
		{
			// Y軸のみの判定
			if (Collision::IsHitRect2D(
				(int)PlayerOldPosX, (int)PlayerPosY, (int)PlayerSize, (int)PlayerSize,
				(int)MapPos.x, (int)MapPos.y, (int)MapSIze.x, (int)MapSIze.y))
			{
				// プレイヤーの上側が当たった時の処理
				if (cPlayer.GetDir(PLAYER_UP))
				{
					int Overlap1 = (int)((MapPos.y + MapSIze.y) - PlayerPosY);
					cPlayer.HitMapY(PlayerPosY + Overlap1);

					if (cPlayer.GetDelay())
					{
						cPlayer.HitJumpBlockUpperSide();
					}
				}

				// プレイヤーの下側が当たった時の処理
				if (cPlayer.GetDir(PLAYER_DOWN))
				{
					int Overlap2 = (int)((PlayerPosY + PlayerSize) - MapPos.y);
					cPlayer.HitMapY(PlayerPosY - Overlap2);
					if (cPlayer.GetDelay())
					{
						if (cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_01)
						{
							cPlayer.HitJumpBlock(JUMP_POWER_1);
						}
						if (cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_02)
						{
							cPlayer.HitJumpBlock(JUMP_POWER_2);
						}
						if (cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_03)
						{
							cPlayer.HitJumpBlock(JUMP_POWER_3);
						}
						cMap.ChangeTypeID(MapTipIndex);
					}
				}
			}
			// X軸のみの判定
			if (Collision::IsHitRect2D(
				(int)PlayerPosX, (int)PlayerOldPosY, (int)PlayerSize, (int)PlayerSize,
				(int)MapPos.x, (int)MapPos.y, (int)MapSIze.x, (int)MapSIze.y))
			{
				// プレイヤーの左側が当たった時の処理
				if (cPlayer.GetDir(PLAYER_LEFT))
				{
					cPlayer.HitMapX(PlayerOldPosX);
					if (cPlayer.GetDelay())
					{
						if (cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_01)
						{
							cPlayer.HitJumpBlock(JUMP_POWER_1);
						}
						if (cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_02)
						{
							cPlayer.HitJumpBlock(JUMP_POWER_2);
						}
						if (cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_03)
						{
							cPlayer.HitJumpBlock(JUMP_POWER_3);
						}
						cMap.ChangeTypeID(MapTipIndex);
					}
				}

				// プレイヤーの右側が当たった時の処理
				if (cPlayer.GetDir(PLAYER_RIGHT))
				{
					cPlayer.HitMapX(PlayerOldPosX);
					if (cPlayer.GetDelay())
					{
						if (cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_01)
						{
							cPlayer.HitJumpBlock(JUMP_POWER_1);
						}
						if (cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_02)
						{
							cPlayer.HitJumpBlock(JUMP_POWER_2);
						}
						if (cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_03)
						{
							cPlayer.HitJumpBlock(JUMP_POWER_3);
						}
						cMap.ChangeTypeID(MapTipIndex);
					}
				}
			}
		}
	}
}

// プレイヤーととげとの当たり判定
void CollisionManager::CheckHitPlayerToThorn(CPlayer& cPlayer, CMap& cMap)
{
	for (int MapTipIndex = 0; MapTipIndex != cMap.GetMapTipNum(); MapTipIndex++)
	{
		float PlayerPosX, PlayerPosY, PlayerOldPosX, PlayerOldPosY, PlayerSize;
		VECTOR MapPos, StartPosSIze, MapSIze;

		PlayerPosX = cPlayer.GetPosX();
		PlayerPosY = cPlayer.GetPosY();
		PlayerOldPosX = cPlayer.GetOldPosX();
		PlayerOldPosY = cPlayer.GetOldPosY();
		MapPos = cMap.GetPos(MapTipIndex);
		StartPosSIze = cMap.GetStartPos();

		PlayerSize = cPlayer.GetSize();
		MapSIze = MAP_TIP_SIZE;

		if (cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_04)
		{
			// Y軸のみの判定
			if (Collision::IsHitRect2D(
				(int)PlayerOldPosX, (int)PlayerPosY, (int)PlayerSize, (int)PlayerSize,
				(int)MapPos.x, (int)MapPos.y, (int)MapSIze.x, (int)MapSIze.y))
			{
				// プレイヤーの上側が当たった時の処理
				if (cPlayer.GetDir(PLAYER_UP))
				{
					int Overlap1 = (int)((MapPos.y + MapSIze.y) - PlayerPosY);
					cPlayer.HitMapY(PlayerPosY + Overlap1);
					cPlayer.SetPos(StartPosSIze.x, StartPosSIze.y);
				}

				// プレイヤーの下側が当たった時の処理
				if (cPlayer.GetDir(PLAYER_DOWN))
				{
					int Overlap2 = (int)((PlayerPosY + PlayerSize) - MapPos.y);
					cPlayer.HitMapY(PlayerPosY - Overlap2);
					cPlayer.SetPos(StartPosSIze.x, StartPosSIze.y);
				}
			}
			// X軸のみの判定
			if (Collision::IsHitRect2D(
				(int)PlayerPosX, (int)PlayerOldPosY, (int)PlayerSize, (int)PlayerSize,
				(int)MapPos.x, (int)MapPos.y, (int)MapSIze.x, (int)MapSIze.y))
			{
				// プレイヤーの左側が当たった時の処理
				if (cPlayer.GetDir(PLAYER_LEFT))
				{
					int Overlap3 = (int)((MapPos.x + MapSIze.x) - PlayerPosX);
					cPlayer.HitMapX(PlayerPosX + Overlap3);
					cPlayer.SetPos(StartPosSIze.x, StartPosSIze.y);
				}

				// プレイヤーの右側が当たった時の処理
				if (cPlayer.GetDir(PLAYER_RIGHT))
				{
					int Overlap4 = (int)((PlayerPosX + PlayerSize) - MapPos.x);
					cPlayer.HitMapX(PlayerPosX - Overlap4);
					cPlayer.SetPos(StartPosSIze.x, StartPosSIze.y);
				}
			}
		}
	}
}

// プレイヤーとゴールとの当たり判定
void CollisionManager::CheckHitPlayerToGoal(CPlayer& cPlayer, CMap& cMap)
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

		if (cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_05)
		{
			if (Collision::IsHitRect2D(
				(int)PlayerPosX, (int)PlayerPosY, (int)PlayerSize, (int)PlayerSize,
				(int)MapPos.x, (int)MapPos.y, (int)MapSIze.x, (int)MapSIze.y))
			{
				
			}
		}
	}
}