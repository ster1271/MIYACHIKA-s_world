#pragma once
#include "../SceneBace/SceneBace.h"

class SceneClear :public SceneBace
{
private:

public:
	// •\Ž¦‚·‚é‰æ‘œ‚ÌŽí—Þ
	enum GRAPH_TYPE {
		GRAPH_TYPE_BG,
		GRAPH_TYPE_BLOCK,
		GRAPH_TYPE_THORN,
		GRAPH_TYPE_GOAL,
		GRAPH_TYPE_NUM,

	};
	void Init();
	void Step();
	void Draw();
	void Fin();
};