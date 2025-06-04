#include "DebugString.h"
#include "cstdarg"
#include "cstdio"
#include "windows.h"
#include "../Input/Input.h"

DebugString* DebugString::m_Instance = nullptr;
// 文字列の長さ
constexpr int CHAR_SIZE = 512;
// リストのサイズ
constexpr int TEXT_INFO_SIZE = 50;

// コンストラクタ
DebugString::DebugString()
{
	// リストの初期化
	m_TextInfoList.resize(TEXT_INFO_SIZE);
	for (TextInfo& value : m_TextInfoList)
		value.isUse = false;

	DebugFlag = false;
}

// デストラクタ
DebugString::~DebugString()
{
}

// 定義作成
DebugString DebugString::operator=(const DebugString& other)
{
	return DebugString();
}

// DebugStringを取得
DebugString* DebugString::GetInstance()
{
	// まだ作成されていないなら
	if (m_Instance == nullptr)
		m_Instance = new DebugString;

	return m_Instance;
}

// DebugStringを削除
void DebugString::DeleteInstance()
{
	//nullptrでないなら削除
	if (m_Instance != nullptr) {
		delete m_Instance;
		m_Instance = nullptr;	// 削除nullptr代入
	}
}

// デバッグ文言データを追加
void DebugString::AddString(int _x, int _y, FontType type, unsigned int color, string _string)
{
	TextInfo value = { _x,_y,type,_string,color,true };
	AddTextInfo(value);
}

void DebugString::AddFormatString(int _x, int _y, FontType type, unsigned int color, const char* format, ...)
{
	// フォーマット済み文字列を格納するバッファ
	char buffer[CHAR_SIZE];

	// 可変引数を処理
	va_list args;
	va_start(args, format);
	// フォーマット済みの文字列を作成
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	TextInfo value = { _x,_y,type,buffer,color,true };
	AddTextInfo(value);
}

// 出力ログ
void DebugString::DrawLogString(string _string)
{
	_string += "\n";
	OutputDebugString(_string.c_str());
}

void DebugString::DrawLogFormatString(const char* format, ...)
{
	// フォーマット済み文字列を格納するバッファ
	char buffer[CHAR_SIZE];

	// 可変引数を処理
	va_list args;
	va_start(args, format);
	// フォーマット済みの文字列を作成
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	DrawLogString(buffer);
}

// 通常処理
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

// 描画
void DebugString::Draw()
{
	for (TextInfo& value : m_TextInfoList) {
		if (value.isUse) {
			DrawFormatStringToHandle(value.x, value.y, value.Color, Font::GetfontHandle(value.type), value.debugString.c_str());
			// 表示したら未使用にする
			value.isUse = false;
		}
	}
}

// 終了時処理
void DebugString::Fin()
{	
	m_TextInfoList.clear();
}

// listにデータを追加
void DebugString::AddTextInfo(TextInfo _textinfo)
{
	for (TextInfo& value : m_TextInfoList) {
		if (!value.isUse) {
			// データを追加
			value = _textinfo;
			return;
		}
	}
}