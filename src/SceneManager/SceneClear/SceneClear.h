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
		SCORE_TYPE_CLEAR,
		SCORE_TYPE_JUMP,
		SCORE_TYPE_DEAD,
		SCORE_TYPE_TOTAL,
		SCORE_TYPE_NUM,
	};

	// リザルト表示用
	struct REDULT_INFO {
		int m_Pos[2];
		bool m_isMoving;
		bool m_isChangeScore;
		int m_DrawScore;	// 表示するときに使う
		int m_FinalScore;	// 最終的なスコア
	};
private:
	int m_Hndl[GRAPH_TYPE_NUM];	// 画像ハンドル

	REDULT_INFO m_ResultPos[SCORE_TYPE_NUM];	// リザルト表示

	int m_Score;
public:
	void Init();
	void Step();
	void Draw();
	void Fin();
};