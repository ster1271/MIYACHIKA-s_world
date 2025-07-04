#pragma once

// �v���C���[�̉摜���
enum PLAYER_IMAGE_TYPE {
	PLAYER_FRONT,			// �O�������Ă���
	PLAYER_JUMP,			// �W�����v���Ă���
	PLAYER_WALK_A,			// �����Ă���A
	PLAYER_WALK_B,			// �����Ă���B
};
// �v���C���[�̉摜��ޑ���
static const int PLAYER_IMAGE_TYPE_NUM = 4;

// �v���C���[�̏��
enum class PLAYER_STATE {
	FRONT,		// �O�������Ă���
	JUMP,		// �W�����v���Ă���
	WALK		// �����Ă���
};

class CPlayerAnimation {
private:
	PLAYER_STATE m_PlayerID;		// �v���C���[ID

	int m_iHndl[PLAYER_IMAGE_TYPE_NUM];	// �摜�n���h��
	float m_fPlayerPosX;				// �v���C���[X���W
	float m_fPlayerPosY;				// �v���C���[Y���W
	int m_iChangeCnt;					// �ϊ��J�E���g
	bool m_CurrentImageTypeA;			// ���݂̉摜�^�C�v��A��
	bool m_Right;						// �E�������Ă���

public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CPlayerAnimation();
	~CPlayerAnimation();

	// ������
	void Init(float fPosX, float fPosY);
	// �ʏ폈��
	void Step();
	// �`�揈��
	void Draw();
	// �I������
	void Fin();

	// �X�V����
	void Update(float fPosX, float fPosY);

	//====================
	//      �@�֐�
	//====================

	// �v���C���[ID��ύX
	void ChangeID(PLAYER_STATE PlayerID) { m_PlayerID = PlayerID; }

	// �v���C���[���E�������Ă��邩
	void isRight(bool isRight) { m_Right = isRight; }

	//====================
	//   �擾�E�ݒ�֘A
	//====================

	// �v���C���[ID���擾
	PLAYER_STATE GetID() { return m_PlayerID; }
};
