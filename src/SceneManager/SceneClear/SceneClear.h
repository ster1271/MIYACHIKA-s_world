#pragma once
#pragma once
#include "../SceneBace/SceneBace.h"
#include "../../Common.h"

class SceneClear :public SceneBace
{
public:
	// �\������摜�̎��
	enum GRAPH_TYPE {
		GRAPH_TYPE_BG,
		GRAPH_TYPE_BAR,
		GRAPH_TYPE_JUMP,
		GRAPH_TYPE_GOAL,
		GRAPH_TYPE_DEAD,
		GRAPH_TYPE_NUM,
	};

	// �\������X�R�A�̎��
	enum SCORE_TYPE {
		SCORE_TYPE_CLEAR,
		SCORE_TYPE_JUMP,
		SCORE_TYPE_DEAD,
		SCORE_TYPE_TOTAL,
		SCORE_TYPE_NUM,
	};

	// ���U���g�\���p
	struct REDULT_INFO {
		int m_Pos[2];
		bool m_isMoving;
		bool m_isChangeScore;
		int m_DrawScore;	// �\������Ƃ��Ɏg��
		int m_FinalScore;	// �ŏI�I�ȃX�R�A
	};
private:
	int m_Hndl[GRAPH_TYPE_NUM];	// �摜�n���h��

	REDULT_INFO m_ResultPos[SCORE_TYPE_NUM];	// ���U���g�\��

	int m_Score;
public:
	void Init();
	void Step();
	void Draw();
	void Fin();
};