#pragma once
#include "DxLib.h"
#include "list"
#include "vector"
#include "crtdbg.h"

using namespace std;

// いろいろな色
const unsigned int BLACK	 = GetColor(0,   0,   0);	// 黒
const unsigned int RED		 = GetColor(255, 0,   0);	// 赤
const unsigned int GREEN	 = GetColor(0,   255, 0);	// 緑
const unsigned int BLUE		 = GetColor(0,   0,   255);	// 青
const unsigned int YELLOW	 = GetColor(255, 255, 0);	// 黄
const unsigned int LIGHTBLUE = GetColor(0,   255, 255);	// 水色
const unsigned int PURPLE	 = GetColor(255, 0,   255);	// 紫
const unsigned int WHITE	 = GetColor(255, 255, 255);	// 白

// スクリーンサイズ
constexpr int	SCREEN_SIZE_X = 1280;	// X方向の画面サイズを指定
constexpr int	SCREEN_SIZE_Y = 720;	// Y方向の画面サイズを指定

// 画面サイズ半分
constexpr int HALF_SCREEN_SIZE_X = SCREEN_SIZE_X / 2;
constexpr int HALF_SCREEN_SIZE_Y = SCREEN_SIZE_Y / 2;

// 角度をラジアンに変えるためのやつ
constexpr float CALC_ANGLE(float Rad) { return DX_PI_F * Rad / 180.0f; }
