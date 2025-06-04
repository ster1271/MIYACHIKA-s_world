#pragma once
#include <iostream>
#include <stdarg.h>

enum class FontType
{
	HGP�n�p�p�|�b�v��,
	HGP�n�p�p�|�b�v��24,
	HGP�n�p�p�|�b�v��32,
	HGP�n�p�p�|�b�v��64_20,
	HG���ȏ���_96,
	HG��������PRO,
	TAN_NIMBUS32,
	NIKKOYOU_SANS24,
	NIKKOYOU_SANS48,

	KindNum
};

constexpr char FONT_PATH[(int)FontType::KindNum][128] =
{
	"HGP�n�p�p�|�b�v��",
	"HGP�n�p�p�|�b�v��",
	"HGP�n�p�p�|�b�v��",
	"HGP�n�p�p�|�b�v��",
	"HG���ȏ���",
	"HG��������-PRO",
	"TAN - NIMBUS",
	"Nikkyou Sans",
	"Nikkyou Sans",
	//"�݂o�b�`�t�H���g",
	//"�����t�H���g",
	//"HGP�s����",
	//"HG�s����",
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