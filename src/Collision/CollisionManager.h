#pragma once
#include "../Player/Player.h"
#include "../Map/Map.h"

class CollisionManager
{
public:
	// �v���C���[�ƃ}�b�v�Ƃ̓����蔻��
	static void CheckHitPlayerToMap(CPlayer& cPlayer, CMap& cMap);

	// �v���C���[�ƃW�����v�u���b�N�Ƃ̓����蔻��
	static void CheckHitPlayerToJumpBlock(CPlayer& cPlayer, CMap& cMap);

	// �v���C���[�ƂƂ��Ƃ̓����蔻��
	static void CheckHitPlayerToThorn(CPlayer& cPlayer, CMap& cMap);
};