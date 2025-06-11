#pragma once
#include "../SceneBace/SceneBace.h"

class SceneTitle :public SceneBace
{
public:
	// �I������摜�̎��
	enum SELECTABLE_GRAPH_TYPE {
		SELECTABLE_GRAPH_TYPE_START,
		SELECTABLE_GRAPH_TYPE_END,
		SELECTABLE_GRAPH_TYPE_NUM,
	};
	// �\������摜�̎��
	enum GRAPH_TYPE {
		GRAPH_TYPE_BACKGRAUND,
		GRAPH_TYPE_START,
		GRAPH_TYPE_END,
		GRAPH_TYPE_NUM
	};

	void Init();
	void Step();
	void Draw();
	void Fin();
private:
	// �摜�n���h��
	int m_Hndl[GRAPH_TYPE_NUM];

	// �I�𒆉摜
	SELECTABLE_GRAPH_TYPE m_SelectedGraph;
};