#include "DxLib.h"
#include "SceneTitle.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Debug/DebugString.h"
#include "../../SoundManager/SoundManager.h"
#include <cstdlib>

// �^�C�g���̖��O
constexpr char TITLE_NAME[] = "Hopin Popin";

// �Q�[����߂�{�^����X�^�[�g�{�^���̑傫��
constexpr int BUTTON_SIZE[2] = { 320,108 };

// �^�C�g�����S�̍����̉���
constexpr float TITLE_Y_POS_LOWER_LIMIT = 200.0f;

// �^�C�g�����S�̃W�����v��
constexpr int LOGO_JUMP_NUM = 3;

// �^�C�g�����S�̏d��
constexpr float LOGO_JUMP_GRAVITY = 0.4f;

// �{�^���̍ő�T�C�Y
constexpr double BUTTON_MAX_SIZE = 1.2f;

// �{�^���̃T�C�Y�ύX���x
constexpr double BUTTON_SIZE_CANGED_SPEED = 0.01f;

// �^�C�g�����S�̃W�����v�͂̍���
constexpr float LOGO_JUMP_POWER[LOGO_JUMP_NUM] = {
	-10.0f,
	-12.0f,
	-16.0f,
};

// �{�^���̈ʒu
constexpr int BUTTON_POS[SceneTitle::SELECTABLE_GRAPH_TYPE_NUM][2] = {
	{HALF_SCREEN_SIZE_X - BUTTON_SIZE[0] / 2,500},
	{HALF_SCREEN_SIZE_X - BUTTON_SIZE[0] / 2,650},
};

// �摜�̃p�X
constexpr char GRAPH_PATH[SceneTitle::GRAPH_TYPE_NUM][256] = {
	"data/Bloak/JumpBlock1.png",
	"data/Title/Title.png",
	"data/Title/Start.png",
	"data/Title/Leave.png",
	"data/Bloak/JumpBlock1.png",
	"data/Bloak/JumpBlock2.png",
	"data/Bloak/JumpBlock3.png",
	"data/Title/1.png",
	"data/Title/2.png",
	"data/Title/3.png",
	"data/Title/SelectBG.png",
};

void SceneTitle::Init()
{
	// �t�H���g���[�h
	Font::Load();
	m_SelectedGraph = SELECTABLE_GRAPH_TYPE_START;
	m_LogoPos[0] = static_cast<float>(HALF_SCREEN_SIZE_X);
	m_LogoPos[1] = TITLE_Y_POS_LOWER_LIMIT;
	m_isOffscreenBeen = false;

	m_LogoBoundCnt = 0;
	m_LogoYSpeed = LOGO_JUMP_POWER[m_LogoBoundCnt];
	for (int i = 0; i < SELECTABLE_GRAPH_TYPE_NUM; i++) {
		m_ButtonExRate[i] = 1.0f;
		if (i == m_SelectedGraph)m_ButtonExRate[i] = BUTTON_MAX_SIZE;
	}
	m_isButtonChangedExRate = false;

	for (int i = 0; i < GRAPH_TYPE_NUM; i++) {
		if (m_Hndl[i] == -1)continue;
		m_Hndl[i] = -1;
	}

	for (int i = 0; i < GRAPH_TYPE_NUM; i++) {
		if (m_Hndl[i] != -1)continue;
		m_Hndl[i] = LoadGraph(GRAPH_PATH[i]);
	}

	m_TitleRogoExRate = 0.0f;
	m_TitleRogoExRateUp = true;
}

void SceneTitle::Step()
{
	// �f�o�b�O�����\���p
	//DebugString* dbgStr = DebugString::GetInstance();
	//dbgStr->AddString(0, 0, FontType::HGP�n�p�p�|�b�v��24, WHITE, "�^�C�g���ł�");
	//dbgStr->AddString(0, 24, FontType::HGP�n�p�p�|�b�v��24, WHITE, "���N���b�N�������̓R���g���[���~�{�^���Ńv���C��");

	if (m_TitleRogoExRateUp) {
		m_TitleRogoExRate += 0.01f;
		if (m_TitleRogoExRate > 0.5f) {
			m_TitleRogoExRateUp = false;
		}
	}
	else {
		m_TitleRogoExRate -= 0.01f;
		if (m_TitleRogoExRate < -0.5f) {
			m_TitleRogoExRateUp = true;
		}
	}

	//�㉺�őI����ς���
	if (m_LogoBoundCnt == LOGO_JUMP_NUM) {
		if (Input::Conclusion(Input::Type::MOVE_UP)) {
			m_SelectedGraph = static_cast<SELECTABLE_GRAPH_TYPE>(m_SelectedGraph - 1);
			if (m_SelectedGraph < SELECTABLE_GRAPH_TYPE_START) {
				m_SelectedGraph = SELECTABLE_GRAPH_TYPE_START;
			}
			else {
				m_isButtonChangedExRate = true;
			}
		}
		else if (Input::Conclusion(Input::Type::MOVE_DOWN)) {
			m_SelectedGraph = static_cast<SELECTABLE_GRAPH_TYPE>(m_SelectedGraph + 1);
			if (m_SelectedGraph > SELECTABLE_GRAPH_TYPE_END) {
				m_SelectedGraph = SELECTABLE_GRAPH_TYPE_END;
			}
			else {
				m_isButtonChangedExRate = true;
			}
		}
	}

	// �{�^���̃T�C�Y���ύX���Ȃ�ς��Ă��
	if (m_isButtonChangedExRate) {
		if (m_SelectedGraph == SELECTABLE_GRAPH_TYPE_START) {
			m_ButtonExRate[SELECTABLE_GRAPH_TYPE_START] += BUTTON_SIZE_CANGED_SPEED;
			m_ButtonExRate[SELECTABLE_GRAPH_TYPE_END] -= BUTTON_SIZE_CANGED_SPEED;
			if (m_ButtonExRate[SELECTABLE_GRAPH_TYPE_START] > BUTTON_MAX_SIZE &&
				m_ButtonExRate[SELECTABLE_GRAPH_TYPE_END] < 1.0f) {
				m_ButtonExRate[SELECTABLE_GRAPH_TYPE_START] = BUTTON_MAX_SIZE;
				m_ButtonExRate[SELECTABLE_GRAPH_TYPE_END] = 1.0f;
				m_isButtonChangedExRate = false;
			}
		}
		if (m_SelectedGraph == SELECTABLE_GRAPH_TYPE_END) {
			m_ButtonExRate[SELECTABLE_GRAPH_TYPE_START] -= BUTTON_SIZE_CANGED_SPEED;
			m_ButtonExRate[SELECTABLE_GRAPH_TYPE_END] += BUTTON_SIZE_CANGED_SPEED;
			if (m_ButtonExRate[SELECTABLE_GRAPH_TYPE_START] < 1.0f &&
				m_ButtonExRate[SELECTABLE_GRAPH_TYPE_END] > BUTTON_MAX_SIZE) {
				m_ButtonExRate[SELECTABLE_GRAPH_TYPE_START] = 1.0f;
				m_ButtonExRate[SELECTABLE_GRAPH_TYPE_END] = BUTTON_MAX_SIZE;
				m_isButtonChangedExRate = false;
			}
		}
	}

	// ���{�^���������ƑI�𒆂̂��̂Ō��ʂ�ς���
	if (m_LogoBoundCnt == LOGO_JUMP_NUM) {
		if (Input::Conclusion(Input::Type::NEXT) && m_LogoBoundCnt == LOGO_JUMP_NUM) {
			if (m_SelectedGraph == SELECTABLE_GRAPH_TYPE_START) {
				// �v���C�V�[����
				SceneBace::g_scene_ID = Play_Scene;
			}
			else if (m_SelectedGraph == SELECTABLE_GRAPH_TYPE_END) {
				// �Q�[�����I������
				exit(0); // �v���O�������I��
			}
		}
	}

	if (m_LogoBoundCnt < LOGO_JUMP_NUM) {
		m_LogoPos[1] += m_LogoYSpeed;
		m_LogoYSpeed += LOGO_JUMP_GRAVITY;
	}

	if (m_LogoPos[1] < -128&& !m_isOffscreenBeen) {
		m_isOffscreenBeen = true;
		m_LogoPos[1] = -640;
	}

	if (m_LogoBoundCnt < LOGO_JUMP_NUM) {
		if (m_LogoPos[1] > TITLE_Y_POS_LOWER_LIMIT) {
			m_LogoPos[1] = TITLE_Y_POS_LOWER_LIMIT;
			m_LogoBoundCnt++;
			m_LogoYSpeed = LOGO_JUMP_POWER[m_LogoBoundCnt];
		}
	}

	// ���{�^���Ńv���C��
	//if (Input::Conclusion(Input::Type::NEXT))
	//	SceneBace::g_scene_ID = Play_Scene;
}
void SceneTitle::Draw()
{
	// �{�^���̍��W
	int ButtonPos1[SELECTABLE_GRAPH_TYPE_NUM][2] = {
		{BUTTON_POS[SELECTABLE_GRAPH_TYPE_START][0] ,BUTTON_POS[SELECTABLE_GRAPH_TYPE_START][1]},
		{BUTTON_POS[SELECTABLE_GRAPH_TYPE_END][0] ,BUTTON_POS[SELECTABLE_GRAPH_TYPE_END][1]},
	};

	// �������񕶎��\��
	int logopos[2] = { static_cast<int>(m_LogoPos[0]), static_cast<int>(m_LogoPos[1]) };

	DebugString* dbgstr = DebugString::GetInstance();
	if (!m_isOffscreenBeen) {
		//DrawRotaGraph(logopos[0], logopos[1] + 32, 1.5f, 0.0f, m_Hndl[GRAPH_TYPE_COUNT1 + m_LogoBoundCnt], true);
	}
	else {
		string str = TITLE_NAME;
		int length = str.length();
		//dbgstr->AddFormatString(logopos[0] - 16 * length, logopos[1], FontType::HGP�n�p�p�|�b�v��64_20, WHITE, "%s", TITLE_NAME);
		//DrawGraph(logopos[0]-370, logopos[1]-64, m_Hndl[GRAPH_TYPE_TITLELOGO], true);

	//	DrawRotaGraph3(logopos[0]-370, logopos[1] - 64, logopos[0] - 370+768/2, logopos[1] - 64+128, 1.0f+ m_TitleRogoExRate, 1.0f- m_TitleRogoExRate, 0.0f, m_Hndl[GRAPH_TYPE_TITLELOGO], true);
		DrawRotaGraph3(logopos[0], logopos[1] - 256, 768/2, 128, 1.0f + m_TitleRogoExRate, 1.0f - m_TitleRogoExRate, 0.0f, m_Hndl[GRAPH_TYPE_TITLELOGO], true);
	}

	// �{�^���`��
	if (m_isOffscreenBeen) {
		// �I���摜
		DrawRotaGraph(HALF_SCREEN_SIZE_X, logopos[1] + 280 + 192 * m_SelectedGraph, m_ButtonExRate[m_SelectedGraph], 0.0f, m_Hndl[GRAPH_TYPE_LOGOGB], true);
		for (int GraphIndex = 0; GraphIndex < SELECTABLE_GRAPH_TYPE_NUM; GraphIndex++) {
			DrawRotaGraph(HALF_SCREEN_SIZE_X, logopos[1] + 280 + 192 * GraphIndex, m_ButtonExRate[GraphIndex], 0.0f, m_Hndl[GRAPH_TYPE_START + GraphIndex], true);
		}
		//DrawGraph(HALF_SCREEN_SIZE_X - 16, static_cast<int>(TITLE_Y_POS_LOWER_LIMIT) + 64, m_Hndl[GRAPH_TYPE_JUMP1 + m_LogoBoundCnt], true);
	}

	if (m_LogoBoundCnt < LOGO_JUMP_NUM&& !m_isOffscreenBeen) {
		DrawRotaGraph(logopos[0], logopos[1] + 32, 1.5f, 0.0f, m_Hndl[GRAPH_TYPE_COUNT1 + m_LogoBoundCnt], true);
		DrawGraph(HALF_SCREEN_SIZE_X - 16, static_cast<int>(TITLE_Y_POS_LOWER_LIMIT) + 64, m_Hndl[GRAPH_TYPE_JUMP1 + m_LogoBoundCnt], true);
	}

	//DrawRotaGraph3(HALF_SCREEN_SIZE_X/2, HALF_SCREEN_SIZE_Y, 0, 0,
	//	0.8f, 1.2f, 0.0f, m_Hndl[GRAPH_TYPE_TITLELOGO], true);
}
void SceneTitle::Fin()
{
}
