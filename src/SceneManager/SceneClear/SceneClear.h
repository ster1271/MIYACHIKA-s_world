#pragma once
#include "../SceneBace/SceneBace.h"

class SceneClear :public SceneBace
{
public:
	// �\������摜�̎��
	enum GRAPH_TYPE {
		GRAPH_TYPE_BG,
		GRAPH_TYPE_BLOCK,
		GRAPH_TYPE_THORN,
		GRAPH_TYPE_GOAL,
		GRAPH_TYPE_NUM,

	};
private:
	int m_Hndl[GRAPH_TYPE_NUM];	// �摜�n���h��
public:
	void Init();
	void Step();
	void Draw();
	void Fin();
};