#pragma once
#include <DxLib.h>

// �v���C���[�f�[�^
class CPlayerData {
public:
	int m_iJumpCnt;		// �W�����v������
	int m_iDeathCnt;	// ���񂾉�
	int m_iClearStage;	// �X�e�[�W�N���A��

private:
	// CPlayerData�̃|�C���^��ÓI�ϐ��Ŏ���
	static CPlayerData* m_Instance;

	CPlayerData();
	~CPlayerData();

	// �R�s�[���֎~����
	CPlayerData operator == (const CPlayerData& other);

public:
	// ����������
	static void Init();

	// CPlayerData���擾
	static CPlayerData* GetInstance();

	// CPlayerData���폜
	static void DeleteInstance();

	//====================
	//   �擾�E�ݒ�֘A
	//====================

	// �W�����v�����񐔂��擾
	int GetJumpCnt();

	// ���񂾉񐔂��擾
	int GetDeathCnt();

	// �X�e�[�W�N���A�����擾
	int GetClearStage();

	//====================
	//      �@�֐�
	//====================

	// �W�����v�����񐔂����Z
	void AddJumpCnt();

	// ���񂾉񐔂����Z
	void AddDeathCnt();

	// �X�e�[�W�N���A�������Z
	void AddClearStage();
	
};