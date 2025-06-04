#include "DebugString.h"
#include "cstdarg"
#include "cstdio"
#include "windows.h"
#include "../Input/Input.h"

DebugString* DebugString::m_Instance = nullptr;
// ������̒���
constexpr int CHAR_SIZE = 512;
// ���X�g�̃T�C�Y
constexpr int TEXT_INFO_SIZE = 50;

// �R���X�g���N�^
DebugString::DebugString()
{
	// ���X�g�̏�����
	m_TextInfoList.resize(TEXT_INFO_SIZE);
	for (TextInfo& value : m_TextInfoList)
		value.isUse = false;

	DebugFlag = false;
}

// �f�X�g���N�^
DebugString::~DebugString()
{
}

// ��`�쐬
DebugString DebugString::operator=(const DebugString& other)
{
	return DebugString();
}

// DebugString���擾
DebugString* DebugString::GetInstance()
{
	// �܂��쐬����Ă��Ȃ��Ȃ�
	if (m_Instance == nullptr)
		m_Instance = new DebugString;

	return m_Instance;
}

// DebugString���폜
void DebugString::DeleteInstance()
{
	//nullptr�łȂ��Ȃ�폜
	if (m_Instance != nullptr) {
		delete m_Instance;
		m_Instance = nullptr;	// �폜nullptr���
	}
}

// �f�o�b�O�����f�[�^��ǉ�
void DebugString::AddString(int _x, int _y, FontType type, unsigned int color, string _string)
{
	TextInfo value = { _x,_y,type,_string,color,true };
	AddTextInfo(value);
}

void DebugString::AddFormatString(int _x, int _y, FontType type, unsigned int color, const char* format, ...)
{
	// �t�H�[�}�b�g�ςݕ�������i�[����o�b�t�@
	char buffer[CHAR_SIZE];

	// �ψ���������
	va_list args;
	va_start(args, format);
	// �t�H�[�}�b�g�ς݂̕�������쐬
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	TextInfo value = { _x,_y,type,buffer,color,true };
	AddTextInfo(value);
}

// �o�̓��O
void DebugString::DrawLogString(string _string)
{
	_string += "\n";
	OutputDebugString(_string.c_str());
}

void DebugString::DrawLogFormatString(const char* format, ...)
{
	// �t�H�[�}�b�g�ςݕ�������i�[����o�b�t�@
	char buffer[CHAR_SIZE];

	// �ψ���������
	va_list args;
	va_start(args, format);
	// �t�H�[�}�b�g�ς݂̕�������쐬
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	DrawLogString(buffer);
}

// �ʏ폈��
void DebugString::Step()
{
	if (Input::Key::Push(KEY_INPUT_G)) {
		if (DebugFlag)
			DebugFlag = false;
		else
			DebugFlag = true;
	}

	if (DebugFlag) {
		for (TextInfo& value : m_TextInfoList)
			value.isUse = false;
	}
}

// �`��
void DebugString::Draw()
{
	for (TextInfo& value : m_TextInfoList) {
		if (value.isUse) {
			DrawFormatStringToHandle(value.x, value.y, value.Color, Font::GetfontHandle(value.type), value.debugString.c_str());
			// �\�������疢�g�p�ɂ���
			value.isUse = false;
		}
	}
}

// �I��������
void DebugString::Fin()
{	
	m_TextInfoList.clear();
}

// list�Ƀf�[�^��ǉ�
void DebugString::AddTextInfo(TextInfo _textinfo)
{
	for (TextInfo& value : m_TextInfoList) {
		if (!value.isUse) {
			// �f�[�^��ǉ�
			value = _textinfo;
			return;
		}
	}
}