#pragma once
#pragma once
#include "../SceneBace/SceneBace.h"
#include "../../Common.h"

class SceneClear :public SceneBace
{
public:
	// 表示する画像の種類
	enum GRAPH_TYPE {
		GRAPH_TYPE_BG,
		GRAPH_TYPE_BAR,
		GRAPH_TYPE_JUMP,
		GRAPH_TYPE_GOAL,
		GRAPH_TYPE_DEAD,
		GRAPH_TYPE_NUM,
	};

	// 表示するスコアの種類
	enum SCORE_TYPE {
		SCORE_TYPE_JUMP,
		SCORE_TYPE_CLEAR,
		SCORE_TYPE_DEAD,
		SCORE_TYPE_TOTAL,
		SCORE_TYPE_NUM,
	};
private:
	int m_Hndl[GRAPH_TYPE_NUM];	// 画像ハンドル
public:
	void Init();
	void Step();
	void Draw();
	void Fin();
};