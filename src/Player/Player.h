#pragma once

// �v���C���[�̈ړ�����
enum PLAYER_DIRECTION {
	PLAYER_UP,				// ��Ɉړ�
	PLAYER_DOWN,			// ���Ɉړ�
	PLAYER_LEFT,			// ���Ɉړ�
	PLAYER_RIGHT,			// �E�Ɉړ�

	PLAYER_DIRECTION_NUM	// �v���C���[�̈ړ������̑���
};

// �v���C���[�̃W�����v�p���[
enum PLAYER_JUMP_POWER
{
	JUMP_POWER_1,			// �W�����v�̃p���[1
	JUMP_POWER_2,			// �W�����v�̃p���[2
	JUMP_POWER_3,			// �W�����v�̃p���[3

	PLAYER_JUMP_POWER_NUM	// �W�����v�̃p���[����
};

// �v���C���[�̑傫��
const float PLAYER_SIZE = 32.0f;

class CPlayer {
private:
	int m_iHndl;		// �摜�n���h��
	float m_fPosX;		// X���W
	float m_fPosY;		// Y���W
	float m_fOldPosX;	// �ړ��O��X���W
	float m_fOldPosY;	// �ړ��O��Y���W
	float m_fSpeed;		// ���x
	float m_fYSpeed;	// Y�������x

	// �v���C���[�̂ǂ̕����ɐi��ł��邩
	bool m_bDir[PLAYER_DIRECTION_NUM];

	// �W�����v��
	PLAYER_JUMP_POWER m_eJumpPower;

public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CPlayer();
	~CPlayer();

	void Init();	// ������
	void Step();	// �ʏ폈��
	void Draw();	// �`�揈��
	void Fin();		// �I������

	// �X�V����
	void Update();

	//====================
	//      �@�֐�
	//====================
	
	// �ړ�����
	void Move();

	// �W�����v����
	void Jump();

	// �v���C���[�̕���
	void Direction();

	// �}�b�v�ɓ���������
	void HitMapX(float fOverlap);
	void HitMapY(float fOverlap);

	// �㑤�ɓ���������
	void HitUpperSide();

	// �����ɓ���������
	void HitLowerSide();

	// �v���C���[�̃W�����v�p���[��ς���
	void SetJumpPower(PLAYER_JUMP_POWER JumpPower);

	//====================
	//   �擾�E�ݒ�֘A
	//====================

	// �v���C���[�̍��W�擾
	float& GetPosX() { return m_fPosX; }
	float& GetPosY() { return m_fPosY; }

	// �v���C���[�̈ړ��O�̍��W�擾
	float GetOldPosX() { return m_fOldPosX; }
	float GetOldPosY() { return m_fOldPosY; }

	// �v���C���[�̑傫��
	float GetSize() { return PLAYER_SIZE; }

	// �v���C���[�̈ړ��������擾
	bool GetDir(PLAYER_DIRECTION DirID) { return m_bDir[DirID]; }

	// �v���C���[�̍��W��ݒ�
	void SetPos(float fPosX, float fPosY)
	{
		m_fPosX = fPosX;
		m_fPosY = fPosY;
	}
};
