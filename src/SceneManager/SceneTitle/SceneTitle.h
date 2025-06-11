#pragma once
#include "../SceneBace/SceneBace.h"

class SceneTitle :public SceneBace
{
public:
	// 選択する画像の種類
	enum SELECTABLE_GRAPH_TYPE {
		SELECTABLE_GRAPH_TYPE_START,
		SELECTABLE_GRAPH_TYPE_END,
		SELECTABLE_GRAPH_TYPE_NUM,
	};
	// 表示する画像の種類
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
	// 画像ハンドル
	int m_Hndl[GRAPH_TYPE_NUM];

	// 選択中画像
	SELECTABLE_GRAPH_TYPE m_SelectedGraph;
};