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
		GRAPH_TYPE_TITLELOGO,
		GRAPH_TYPE_START,
		GRAPH_TYPE_LEAVE,
		GRAPH_TYPE_JUMP1,
		GRAPH_TYPE_JUMP2,
		GRAPH_TYPE_JUMP3,
		GRAPH_TYPE_COUNT1,
		GRAPH_TYPE_COUNT2,
		GRAPH_TYPE_COUNT3,
		GRAPH_TYPE_LOGOGB,
		GRAPH_TYPE_NUM
	};

	//// �{�^���̏��
	//enum BUTTON_STATUS {
	//	BUTTON_STATUS_NONE=-1,
	//	BUTTON_STATUS_LARGE,
	//	BUTTON_STATUS_SMALL,
	//	BUTTON_STATUS_NUM,
	//};

	void Init();
	void Step();
	void Draw();
	void Fin();
private:
	// �摜�n���h��
	int m_Hndl[GRAPH_TYPE_NUM];

	// �^�C�g�����S���W
	float m_LogoPos[2];
	float m_LogoYSpeed;	// ���x
	int m_LogoBoundCnt;	// �͂˂���
	bool m_isOffscreenBeen;	// ��ʊO�ɍs������(�s�����Ȃ�^�C�g����\������)

	double m_ButtonExRate[SELECTABLE_GRAPH_TYPE_NUM];
	bool m_isButtonChangedExRate;

	double m_TitleRogoExRate;
	bool m_TitleRogoExRateUp;


	// �I�𒆉摜
	SELECTABLE_GRAPH_TYPE m_SelectedGraph;
};