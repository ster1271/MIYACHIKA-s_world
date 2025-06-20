#pragma once
#include "../Player/Player.h"
#include "../Map/Map.h"

class CollisionManager
{
public:
	// �v���C���[�ƃ}�b�v�Ƃ̓����蔻��
	static void CheckHitPlayerToMap(CPlayer& cPlayer, CMap& cMap);

	// 2�̍��W�����d�Ȃ��Ă���ʂ��擾
	static int GetOverlap(int iPosA, int iPosB);
};