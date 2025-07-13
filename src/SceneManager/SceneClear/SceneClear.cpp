#include "DxLib.h"
#include "SceneClear.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Debug/DebugString.h"
#include "../../Player/PlayerData.h"
//�\������S�[���̐�
constexpr int GOAL_NUM = 20;

// ���U���g�o�[�̈ړ����x
constexpr int BAR_SPEED = 20;

// ���U���g�o�[�̍ŏI�ʒu(����)
constexpr int BAR_PYOS[SceneClear::SCORE_TYPE_NUM] = {
	200,
	320,
	440,
	620
};

// ���U���g�\������
constexpr char BAR_CHAR[SceneClear::SCORE_TYPE_NUM][256] = {
	"�N���A��   :",
	"�W�����v�� :",
	"���񂾉�   :",
	"�����X�R�A   :"
};

//�}�b�v�f�ރf�[�^�̃t�@�C���p�X
static const char GRAPH_PATH[SceneClear::GRAPH_TYPE_NUM][256]
{
	"data/Clear/BG.png",
	"data/Clear/Bar.png",
	"data/Clear/Jump.png",
	"data/Clear/Goal.png",
	"data/Clear/Dead.png",
};

// �X�R�A�{��
constexpr int SCORE_MAG[SceneClear::SCORE_TYPE_NUM] = {
	1000,
	-10,
	-50,
	0,
};



void SceneClear::Init()
{
	for (int i = 0; i < GRAPH_TYPE_NUM; i++) {
		if (m_Hndl[i] == -1)continue;
		m_Hndl[i] = -1;
	}

	for (int i = 0; i < GRAPH_TYPE_NUM; i++) {
		if (m_Hndl[i] != -1)continue;
		m_Hndl[i] = LoadGraph(GRAPH_PATH[i]);
	}


	for (int i = 0; i < SCORE_TYPE_NUM;i++) {
		m_ResultPos[i].m_Pos[0] = SCREEN_SIZE_X;
		m_ResultPos[i].m_Pos[1] = BAR_PYOS[i];
		m_ResultPos[i].m_isMoving = false;
		m_ResultPos[i].m_isChangeScore = false;
		m_ResultPos[i].m_DrawScore = 0;
	}
	m_ResultPos[0].m_isMoving = true;
	m_Score = CPlayerData::GetInstance()->GetClearStage() * SCORE_MAG[0]
		+ CPlayerData::GetInstance()->GetJumpCnt() * SCORE_MAG[1]
		+ CPlayerData::GetInstance()->GetDeathCnt() * SCORE_MAG[2];
	//m_GoalVec.resize(GOAL_NUM);
	//for (auto& goal : m_GoalVec) {
	//	goal.m_Pos[0] = GetRand(SCREEN_SIZE_X) + HALF_SCREEN_SIZE_X;
	//	goal.m_Pos[1] = -(GetRand(SCREEN_SIZE_Y)+32);
	//}
}
void SceneClear::Step()
{
	// �f�o�b�O�����\���p
	//DebugString* dbgStr = DebugString::GetInstance();
	//dbgStr->AddString(0, 0, FontType::HGP�n�p�p�|�b�v��24, WHITE, "�N���A�ł�");
	//dbgStr->AddString(0, 24, FontType::HGP�n�p�p�|�b�v��24, WHITE, "���N���b�N�������̓R���g���[���~�{�^���Ń^�C�g����");

	for (int i = 0; i < SCORE_TYPE_NUM; i++) {
		if (m_ResultPos[i].m_isMoving) {
			m_ResultPos[i].m_Pos[0] -= BAR_SPEED;
			if (m_ResultPos[i].m_Pos[0] < HALF_SCREEN_SIZE_X - 480) {
				m_ResultPos[i].m_Pos[0] = HALF_SCREEN_SIZE_X - 480;
				m_ResultPos[i].m_isMoving = false;
				m_ResultPos[i].m_isChangeScore = true;
			}
		}
	}

	for (int i = 0; i < SCORE_TYPE_NUM; i++) {
		if (m_ResultPos[i].m_isChangeScore) {
			switch (i)
			{
			case 0:
				m_ResultPos[i].m_DrawScore += 24;
				if (m_ResultPos[i].m_DrawScore > CPlayerData::GetInstance()->GetClearStage() * SCORE_MAG[0]) {
					m_ResultPos[i].m_DrawScore = CPlayerData::GetInstance()->GetClearStage() * SCORE_MAG[0];
					m_ResultPos[i].m_isChangeScore = false;
					m_ResultPos[i + 1].m_isMoving = true;
				}
				break;
			case 1:
				m_ResultPos[i].m_DrawScore-=4;
				if (m_ResultPos[i].m_DrawScore < CPlayerData::GetInstance()->GetJumpCnt() * SCORE_MAG[1]) {
					m_ResultPos[i].m_DrawScore = CPlayerData::GetInstance()->GetJumpCnt() * SCORE_MAG[1];
					m_ResultPos[i].m_isChangeScore = false;
					m_ResultPos[i + 1].m_isMoving = true;
				}
				break;
			case 2:
				m_ResultPos[i].m_DrawScore-=2;
				if (m_ResultPos[i].m_DrawScore < CPlayerData::GetInstance()->GetDeathCnt() * SCORE_MAG[2]) {
					m_ResultPos[i].m_DrawScore = CPlayerData::GetInstance()->GetDeathCnt() * SCORE_MAG[2];
					m_ResultPos[i].m_isChangeScore = false;
					m_ResultPos[i + 1].m_isMoving = true;
				}
				break;
			case 3:
				if (m_Score < 0) {
					m_ResultPos[i].m_DrawScore -= 24;
					if (m_ResultPos[i].m_DrawScore < m_Score) {
						m_ResultPos[i].m_DrawScore = m_Score;
						m_ResultPos[i].m_isChangeScore = false;
					}
				}
				else {
					m_ResultPos[i].m_DrawScore += 24;
					if (m_ResultPos[i].m_DrawScore > m_Score) {
						m_ResultPos[i].m_DrawScore = m_Score;
						m_ResultPos[i].m_isChangeScore = false;
					}
				}
				break;
			default:
				break;
			}

			if (m_ResultPos[i].m_Pos[0] < HALF_SCREEN_SIZE_X - 480) {
				m_ResultPos[i].m_Pos[0] = HALF_SCREEN_SIZE_X - 480;
				m_ResultPos[i].m_isMoving = false;
				m_ResultPos[i].m_isChangeScore = true;
			}
		}
	}

	// ���{�^���Ń^�C�g����
	if (Input::Conclusion(Input::Type::NEXT))
		SceneBace::g_scene_ID = Title_Scene;
}
void SceneClear::Draw()
{
	// �Q�[���N���A�̕����ɕ\��
	DrawGraph(0, 0, m_Hndl[GRAPH_TYPE_BG], true);

	for (int i = 0; i < SCORE_TYPE_NUM; i++) {
		DrawGraph(m_ResultPos[i].m_Pos[0], BAR_PYOS[i],  m_Hndl[GRAPH_TYPE_BAR], true);
		int Cnt = 0;
		switch (i)
		{
		case 0:
			Cnt = CPlayerData::GetInstance()->GetClearStage();
			DebugString::GetInstance()->AddFormatString(m_ResultPos[i].m_Pos[0] + 400, BAR_PYOS[i] + 16,
				FontType::HGP�n�p�p�|�b�v��32, BLACK, "�~ 1000pt = %d", m_ResultPos[i].m_DrawScore);
			break;
		case 1:
			Cnt = CPlayerData::GetInstance()->GetJumpCnt();
			DebugString::GetInstance()->AddFormatString(m_ResultPos[i].m_Pos[0] + 400, BAR_PYOS[i] + 16,
				FontType::HGP�n�p�p�|�b�v��32, BLACK, "�~ -10pt  = %d", m_ResultPos[i].m_DrawScore);
			break;
		case 2:
			Cnt = CPlayerData::GetInstance()->GetDeathCnt();
			DebugString::GetInstance()->AddFormatString(m_ResultPos[i].m_Pos[0] + 400, BAR_PYOS[i] + 16,
				FontType::HGP�n�p�p�|�b�v��32, BLACK, "�~ -50pt  = %d", m_ResultPos[i].m_DrawScore);
			break;
		case 3:
			Cnt = m_ResultPos[i].m_DrawScore;
			break;
		default:
			break;
		}
		DebugString::GetInstance()->AddFormatString(m_ResultPos[i].m_Pos[0] + 16, BAR_PYOS[i]+16,
			FontType::HGP�n�p�p�|�b�v��32, BLACK, "%s %d ", BAR_CHAR[i], Cnt);
	}
}
void SceneClear::Fin()
{
	CPlayerData::DeleteInstance();
}