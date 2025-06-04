#pragma once
#include <iostream>
#include <stdarg.h>

enum class FontType
{
	HGP創英角ポップ体,
	HGP創英角ポップ体24,
	HGP創英角ポップ体32,
	HGP創英角ポップ体64_20,
	HG教科書体_96,
	HG正楷書体PRO,
	TAN_NIMBUS32,
	NIKKOYOU_SANS24,
	NIKKOYOU_SANS48,

	KindNum
};

constexpr char FONT_PATH[(int)FontType::KindNum][128] =
{
	"HGP創英角ポップ体",
	"HGP創英角ポップ体",
	"HGP創英角ポップ体",
	"HGP創英角ポップ体",
	"HG教科書体",
	"HG正楷書体-PRO",
	"TAN - NIMBUS",
	"Nikkyou Sans",
	"Nikkyou Sans",
	//"みつバッチフォント",
	//"数式フォント",
	//"HGP行書体",
	//"HG行書体",
};

constexpr int FONT_SIZE[(int)FontType::KindNum] =
{
	16,
	24,
	32,
	64,
	96,
	64,
	32,
	24,
	48,
};

constexpr int FONT_THICK[(int)FontType::KindNum] =
{
	-1,
	-1,
	-1,
	20,
	-1,
	-1,
	-1,
	-1,
	-1,
};

class Font
{
private:
	static int fontHandle[(int)FontType::KindNum];

public:
	static void Init();
	static void LoadFile();
	static void Load();
	static void Fin();

	static int GetfontHandle(FontType font) { return fontHandle[(int)font]; }
};