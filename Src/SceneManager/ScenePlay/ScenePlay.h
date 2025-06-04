#pragma once
#include "../../Common.h"
#include "../SceneBace/SceneBace.h"

class ScenePlay :public SceneBace
{
private:

public:
	void Init();
	void Step();
	void Draw();
	void Fin();
};