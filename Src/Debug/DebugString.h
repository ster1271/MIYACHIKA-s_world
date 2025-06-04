#pragma once
#include "../Common.h"
#include "../Font/Font.h"
#include "string"

class DebugString {
private:
	DebugString();
	~DebugString();
	// デバッグ文言表示構造体
	struct TextInfo {
		int				x;				// 表示座標:X
		int				y;				// 表示座標:Y
		FontType		type;			// フォントタイプ
		string			debugString;	// 文言
		unsigned int	Color;			// 色
		bool			isUse;			// 使用フラグ
	};

	// コピーを禁止にする
	DebugString(const DebugString& other);
	DebugString operator = (const DebugString& other);
	// DebugStringのポインタを静的変数で持つ
	static DebugString* m_Instance;
	// デバッグ文言表示フラグ設定
	bool DebugFlag;
public:
	// DebugStringを取得
	static DebugString* GetInstance();
	// DebugStringを削除
	static void DeleteInstance();

	// デバッグ文言データを追加
	void AddString(int _x, int _y, FontType type, unsigned int color, string _string);
	void AddFormatString(int _x, int _y, FontType type, unsigned int color, const char* format, ...);

	// 出力ログ
	void DrawLogString(string _string);
	void DrawLogFormatString(const char* format, ...);
	// 通常処理
	void Step();
	// 描画
	void Draw();
	// 終了時処理
	void Fin();
private:
	// デバッグ文言表示用リスト
	list<TextInfo>m_TextInfoList;

	// listにデータを追加
	void AddTextInfo(TextInfo _textinfo);
};