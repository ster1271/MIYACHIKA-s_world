#include "DxLib.h"
#include "SceneTitle.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Debug/DebugString.h"
#include "../../SoundManager/SoundManager.h"
#include <cstdlib>

// �Q�[����߂�{�^����X�^�[�g�{�^���̑傫��
constexpr int BUTTON_SIZE[2] = { 320,108 };

// �^�C�g�����S�̍����̉���
constexpr float TITLE_Y_POS_LOWER_LIMIT = 200.0f;

// �^�C�g�����S�̃W�����v��
constexpr int LOGO_JUMP_NUM = 3;

// �^�C�g�����S�̏d��
constexpr float LOGO_JUMP_GRAVITY = 0.4f;

// �^�C�g�����S�̃W�����v�͂̍���
constexpr float LOGO_JUMP_POWER[LOGO_JUMP_NUM] = {
	-10.0f,
	-12.0f,
	-16.0f,
};

// �{�^���̈ʒu
constexpr int BUTTON_POS[SceneTitle::SELECTABLE_GRAPH_TYPE_NUM][2] = {
	{HALF_SCREEN_SIZE_X - BUTTON_SIZE[0] / 2,400},
	{HALF_SCREEN_SIZE_X - BUTTON_SIZE[0] / 2,550},
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
}

void SceneTitle::Step()
{
	// �f�o�b�O�����\���p
	DebugString* dbgStr = DebugString::GetInstance();
	dbgStr->AddString(0, 0, FontType::HGP�n�p�p�|�b�v��24, WHITE, "�^�C�g���ł�");
	dbgStr->AddString(0, 24, FontType::HGP�n�p�p�|�b�v��24, WHITE, "���N���b�N�������̓R���g���[���~�{�^���Ńv���C��");

	//�㉺�őI����ς���
	if (Input::Conclusion(Input::Type::MOVE_UP)) {
		m_SelectedGraph = static_cast<SELECTABLE_GRAPH_TYPE>(m_SelectedGraph - 1);
		if (m_SelectedGraph < SELECTABLE_GRAPH_TYPE_START) {
			m_SelectedGraph = SELECTABLE_GRAPH_TYPE_START;
		}
	}
	else if (Input::Conclusion(Input::Type::MOVE_DOWN)) {
		m_SelectedGraph = static_cast<SELECTABLE_GRAPH_TYPE>(m_SelectedGraph + 1);
		if (m_SelectedGraph > SELECTABLE_GRAPH_TYPE_END) {
			m_SelectedGraph = SELECTABLE_GRAPH_TYPE_END;
		}
	}

	// ���{�^���������ƑI�𒆂̂��̂Ō��ʂ�ς���
	if (Input::Conclusion(Input::Type::NEXT)) {
		if (m_SelectedGraph == SELECTABLE_GRAPH_TYPE_START) {
			// �v���C�V�[����
			SceneBace::g_scene_ID = Play_Scene;
		}
		else if (m_SelectedGraph == SELECTABLE_GRAPH_TYPE_END) {
			// �Q�[�����I������
			exit(0); // �v���O�������I��
		}
	}

	if (m_LogoBoundCnt < LOGO_JUMP_NUM) {
		//m_LogoPos[0]++;
		m_LogoPos[1] += m_LogoYSpeed;
		m_LogoYSpeed += LOGO_JUMP_GRAVITY;
	}

	if (m_LogoPos[1] < -64) {
		m_isOffscreenBeen = true;
	}

	if (m_LogoPos[1] > TITLE_Y_POS_LOWER_LIMIT) {
		m_LogoPos[1] = TITLE_Y_POS_LOWER_LIMIT;
		m_LogoBoundCnt++;
		m_LogoYSpeed = LOGO_JUMP_POWER[m_LogoBoundCnt];
	}

	// ���{�^���Ńv���C��
	//if (Input::Conclusion(Input::Type::NEXT))
	//	SceneBace::g_scene_ID = Play_Scene;
}
void SceneTitle::Draw()
{
	// �{�^���̍���̍��W�ƉE���̍��W
	int ButtonPos1[SELECTABLE_GRAPH_TYPE_NUM][2] = { 
		{BUTTON_POS[SELECTABLE_GRAPH_TYPE_START][0] ,BUTTON_POS[SELECTABLE_GRAPH_TYPE_START][1]},
		{BUTTON_POS[SELECTABLE_GRAPH_TYPE_END][0] ,BUTTON_POS[SELECTABLE_GRAPH_TYPE_END][1]},
	};
	int ButtonPos2[SELECTABLE_GRAPH_TYPE_NUM][2] = {
		{ButtonPos1[SELECTABLE_GRAPH_TYPE_START][0] + BUTTON_SIZE[0] - 1 ,ButtonPos1[SELECTABLE_GRAPH_TYPE_START][1] + BUTTON_SIZE[1] - 1 },
		{ButtonPos1[SELECTABLE_GRAPH_TYPE_END][0] + BUTTON_SIZE[0] - 1 ,ButtonPos1[SELECTABLE_GRAPH_TYPE_END][1] + BUTTON_SIZE[1] - 1 },
	};

	// �{�^���`��
	for (int GraphIndex = 0; GraphIndex < SELECTABLE_GRAPH_TYPE_NUM; GraphIndex++) {
		DrawBox(ButtonPos1[GraphIndex][0], ButtonPos1[GraphIndex][1], ButtonPos2[GraphIndex][0], ButtonPos2[GraphIndex][1], WHITE, false);
	}

	// �I���摜
	// ��������
	for (int ThickIndex = 1; ThickIndex < 5; ThickIndex++) {
		DrawBox(ButtonPos1[m_SelectedGraph][0] - ThickIndex, ButtonPos1[m_SelectedGraph][1] - ThickIndex,
			ButtonPos2[m_SelectedGraph][0] + ThickIndex, ButtonPos2[m_SelectedGraph][1] + ThickIndex, RED, false);
	}

	// �������񕶎��\��
	int logopos[2] = { static_cast<int>(m_LogoPos[0]), static_cast<int>(m_LogoPos[1]) };
	DebugString* dbgstr = DebugString::GetInstance();

	if (!m_isOffscreenBeen) {
		dbgstr->AddFormatString(logopos[0] - 16, logopos[1], FontType::HGP�n�p�p�|�b�v��64_20, WHITE, "%d", m_LogoBoundCnt + 1);
	}
	else {
		dbgstr->AddString(logopos[0] - 16 * 5, logopos[1], FontType::HGP�n�p�p�|�b�v��64_20, WHITE, "Title");
	}

}
void SceneTitle::Fin()
{
}
