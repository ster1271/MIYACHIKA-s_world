#pragma once
#include "SceneBace/SceneBace.h"

class SceneManager
{
private:
	SceneBace* scene;
public:
	SceneManager();
	~SceneManager() { Fin(); }

	// �I������
	void Fin();

	void Main();
};