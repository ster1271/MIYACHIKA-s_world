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

	//// ボタンの状態
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
	// 画像ハンドル
	int m_Hndl[GRAPH_TYPE_NUM];

	// タイトルロゴ座標
	float m_LogoPos[2];
	float m_LogoYSpeed;	// 速度
	int m_LogoBoundCnt;	// はねた回数
	bool m_isOffscreenBeen;	// 画面外に行ったか(行ったならタイトルを表示する)

	double m_ButtonExRate[SELECTABLE_GRAPH_TYPE_NUM];
	bool m_isButtonChangedExRate;

	double m_TitleRogoExRate;
	bool m_TitleRogoExRateUp;


	// 選択中画像
	SELECTABLE_GRAPH_TYPE m_SelectedGraph;
};