#include "Collision.h"
#include "CollisionManager.h"
#include "../SceneManager/SceneBace/SceneBace.h"

// �v���C���[�ƃ}�b�v�Ƃ̓����蔻��
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
			// Y���݂̂̔���
			if (Collision::IsHitRect2D(
				(int)PlayerOldPosX, (int)PlayerPosY, (int)PlayerSize, (int)PlayerSize,
				(int)MapPos.x, (int)MapPos.y, (int)MapSIze.x, (int)MapSIze.y))
			{
				// �v���C���[�̏㑤�������������̏���
				if (cPlayer.GetDir(PLAYER_UP))
				{
					int Overlap1 = (int)((MapPos.y + MapSIze.y) - PlayerPosY);
					cPlayer.HitMapY(PlayerPosY + Overlap1);
					cPlayer.HitUpperSide();
				}

				// �v���C���[�̉����������������̏���
				if (cPlayer.GetDir(PLAYER_DOWN))
				{
					int Overlap2 = (int)((PlayerPosY + PlayerSize) - MapPos.y);
					cPlayer.HitMapY(PlayerPosY - Overlap2);
					cPlayer.HitLowerSide();
				}
			}
			// X���݂̂̔���
			if (Collision::IsHitRect2D(
				(int)PlayerPosX, (int)PlayerOldPosY, (int)PlayerSize, (int)PlayerSize,
				(int)MapPos.x, (int)MapPos.y, (int)MapSIze.x, (int)MapSIze.y))
			{
				// �v���C���[�̍����������������̏���
				if (cPlayer.GetDir(PLAYER_LEFT))
				{
					cPlayer.HitMapX(PlayerOldPosX);
				}

				// �v���C���[�̉E���������������̏���
				if (cPlayer.GetDir(PLAYER_RIGHT))
				{
					cPlayer.HitMapX(PlayerOldPosX);
				}
			}
		}
	}
}

// �v���C���[�ƃW�����v�u���b�N�Ƃ̓����蔻��
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
			// Y���݂̂̔���
			if (Collision::IsHitRect2D(
				(int)PlayerOldPosX, (int)PlayerPosY, (int)PlayerSize, (int)PlayerSize,
				(int)MapPos.x, (int)MapPos.y, (int)MapSIze.x, (int)MapSIze.y))
			{
				// �v���C���[�̏㑤�������������̏���
				if (cPlayer.GetDir(PLAYER_UP))
				{
					int Overlap1 = (int)((MapPos.y + MapSIze.y) - PlayerPosY);
					cPlayer.HitMapY(PlayerPosY + Overlap1);

					if (cPlayer.GetDelay())
					{
						cPlayer.HitJumpBlockUpperSide();
						cMap.ChangeTypeID(MapTipIndex);
					}
				}

				// �v���C���[�̉����������������̏���
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
			// X���݂̂̔���
			if (Collision::IsHitRect2D(
				(int)PlayerPosX, (int)PlayerOldPosY, (int)PlayerSize, (int)PlayerSize,
				(int)MapPos.x, (int)MapPos.y, (int)MapSIze.x, (int)MapSIze.y))
			{
				// �v���C���[�̍����������������̏���
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

				// �v���C���[�̉E���������������̏���
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

// �v���C���[�ƂƂ��Ƃ̓����蔻��
void CollisionManager::CheckHitPlayerToThorn(CPlayer& cPlayer, CMap& cMap)
{
	for (int MapTipIndex = 0; MapTipIndex != cMap.GetMapTipNum(); MapTipIndex++)
	{
		float PlayerPosX, PlayerPosY, PlayerOldPosX, PlayerOldPosY, PlayerSize;
		VECTOR MapPos, StartPos, MapSIze;

		float num = 20.0f;

		PlayerPosX = cPlayer.GetPosX() + (num / 2);
		PlayerPosY = cPlayer.GetPosY() + (num / 2);
		MapPos = cMap.GetPos(MapTipIndex);
		StartPos = cMap.GetStartPos();

		PlayerSize = cPlayer.GetSize() - num;
		MapSIze = MAP_TIP_SIZE;

		if (cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_04)
		{
			if (Collision::IsHitRect2D(
				(int)PlayerPosX, (int)PlayerPosY, (int)PlayerSize, (int)PlayerSize,
				(int)MapPos.x, (int)MapPos.y, (int)MapSIze.x, (int)MapSIze.y))
			{
				cPlayer.HitThorn(StartPos.x, StartPos.y);
			}
		}
	}
}

// �v���C���[�ƃS�[���Ƃ̓����蔻��
void CollisionManager::CheckHitPlayerToGoal(CPlayer& cPlayer, CMap& cMap)
{
	for (int MapTipIndex = 0; MapTipIndex != cMap.GetMapTipNum(); MapTipIndex++)
	{
		float PlayerPosX, PlayerPosY, PlayerSize;
		VECTOR MapPos, StartPos, MapSIze;

		PlayerPosX = cPlayer.GetPosX();
		PlayerPosY = cPlayer.GetPosY();
		MapPos = cMap.GetPos(MapTipIndex);

		PlayerSize = cPlayer.GetSize();
		MapSIze = MAP_TIP_SIZE;

		if (cMap.GetTypeID(MapTipIndex) == MAPTIP_TYPE_06)
		{
			if (Collision::IsHitRect2D(
				(int)PlayerPosX, (int)PlayerPosY, (int)PlayerSize, (int)PlayerSize,
				(int)MapPos.x, (int)MapPos.y, (int)MapSIze.x, (int)MapSIze.y))
			{
				cMap.Exit();
				CMap::MapID += 1;

				if (CMap::MapID == MAP_MAX_NUM)
				{
					SceneBace::g_scene_ID = Clear_Scene;
				}

				cMap.LoadMap(CMap::MapID);

				StartPos = cMap.GetStartPos();
				cPlayer.HitGoal(StartPos.x, StartPos.y);
			}
		}
	}
}