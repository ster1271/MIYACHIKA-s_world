#pragma once
#include "../SceneBace/SceneBace.h"
#include "../../Common.h"

class SceneClear :public SceneBace
{
public:
	// •\Ž¦‚·‚é‰æ‘œ‚ÌŽí—Þ
	enum GRAPH_TYPE {
		GRAPH_TYPE_BG,
		GRAPH_TYPE_BLOCK,
		GRAPH_TYPE_THORN,
		GRAPH_TYPE_GOAL,
		GRAPH_TYPE_NUM,

	};
private:
	struct Goal {
		int	m_Pos[2];
	};

	int m_Hndl[GRAPH_TYPE_NUM];	// ‰æ‘œƒnƒ“ƒhƒ‹

	vector<Goal> m_GoalVec;
public:
	void Init();
	void Step();
	void Draw();
	void Fin();
};