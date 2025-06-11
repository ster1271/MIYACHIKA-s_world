#include "DxLib.h"
#include "Font.h"

int Font::fontHandle[(int)FontType::KindNum];

enum class FONT_FILE_TYPE {
	//みつばっち,
	//数式,
	NIMBUS,
	NIKKOYOUSANS,

	TYPE_NUM
};

constexpr char FILE_PATH[static_cast<int>(FONT_FILE_TYPE::TYPE_NUM)][128] = {
	//".ttf/みつバッチフォントver1.ttf",
	//".ttf/数式フォントver1.5.ttf"
	"Data/.ttf/TAN-NIMBUS.ttf",
	"Data/.ttf/NikkyouSans-mLKax.ttf"
};


void Font::Init()
{
	for (int i = 0; i < (int)FontType::KindNum; i++) {
		if (fontHandle[i] == -1)continue;
		fontHandle[i] = -1;
	}
}

void Font::LoadFile()
{
	for (int i = 0; i < static_cast<int>(FONT_FILE_TYPE::TYPE_NUM); i++) {
		AddFontResourceEx(FILE_PATH[i], FR_PRIVATE, NULL);
	}
}

void Font::Load()
{
	for (int i = 0; i < (int)FontType::KindNum; i++) {
		if (fontHandle[i] != -1)continue;
		fontHandle[i] = CreateFontToHandle(FONT_PATH[i], FONT_SIZE[i], FONT_THICK[i]);
	}
}

void Font::Fin()
{
	for (int i = 0; i < static_cast<int>(FONT_FILE_TYPE::TYPE_NUM); i++) {
		RemoveFontResourceEx(FILE_PATH[i], FR_PRIVATE, NULL);
	}

	for (int i = 0; i < (int)FontType::KindNum; i++)
	{
		DeleteFontToHandle(fontHandle[i]);
	}
}
