#pragma once
#include "../../Common.h"
#include "../SceneBace/SceneBace.h"

#include "../../Player/Player.h"
#include "../../Map/Map.h"

class ScenePlay :public SceneBace
{
private:
	CPlayer cPlayer;
	CMap cMap;

public:
	void Init();
	void Step();
	void Draw();
	void Fin();

	void Collision();
};