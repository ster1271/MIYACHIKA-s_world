#pragma once
#include "SceneBace/SceneBace.h"

class SceneManager
{
private:
	SceneBace* scene;
public:
	SceneManager();
	~SceneManager() { Fin(); }

	// I—¹ˆ—
	void Fin();

	void Main();
};