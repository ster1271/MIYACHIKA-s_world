#pragma once
#include "../Common.h"
#include "../Font/Font.h"
#include "string"

class DebugString {
private:
	DebugString();
	~DebugString();
	// �f�o�b�O�����\���\����
	struct TextInfo {
		int				x;				// �\�����W:X
		int				y;				// �\�����W:Y
		FontType		type;			// �t�H���g�^�C�v
		string			debugString;	// ����
		unsigned int	Color;			// �F
		bool			isUse;			// �g�p�t���O
	};

	// �R�s�[���֎~�ɂ���
	DebugString(const DebugString& other);
	DebugString operator = (const DebugString& other);
	// DebugString�̃|�C���^��ÓI�ϐ��Ŏ���
	static DebugString* m_Instance;
	// �f�o�b�O�����\���t���O�ݒ�
	bool DebugFlag;
public:
	// DebugString���擾
	static DebugString* GetInstance();
	// DebugString���폜
	static void DeleteInstance();

	// �f�o�b�O�����f�[�^��ǉ�
	void AddString(int _x, int _y, FontType type, unsigned int color, string _string);
	void AddFormatString(int _x, int _y, FontType type, unsigned int color, const char* format, ...);

	// �o�̓��O
	void DrawLogString(string _string);
	void DrawLogFormatString(const char* format, ...);
	// �ʏ폈��
	void Step();
	// �`��
	void Draw();
	// �I��������
	void Fin();
private:
	// �f�o�b�O�����\���p���X�g
	list<TextInfo>m_TextInfoList;

	// list�Ƀf�[�^��ǉ�
	void AddTextInfo(TextInfo _textinfo);
};