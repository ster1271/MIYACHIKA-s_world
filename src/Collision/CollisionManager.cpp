#include "Collision.h"
#include "CollisionManager.h"

// �v���C���[�ƃ}�b�v�Ƃ̓����蔻��
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

		// X��
		// �v���C���[�̉E��������������
		if (PlayerPosX + PlayerSize >= MapPos.x)
		{
			cPlayer.HitMapCalc_X(-1.0f);
		}
		// �v���C���[�̍���������������
		if (PlayerPosX <= MapPos.x + MapSIze.x)
		{
			cPlayer.HitMapCalc_X(1.0f);
		}

		// Y��
		// �v���C���[�̉���������������
		if (PlayerPosY + PlayerSize >= MapPos.y)
		{
			cPlayer.HitMapCalc_Y(-1.0f);
		}
		// �v���C���[�̏㑤������������
		if (PlayerPosY <= MapPos.y + MapSIze.y)
		{
			cPlayer.HitMapCalc_Y(1.0f);
		}
	}
}
