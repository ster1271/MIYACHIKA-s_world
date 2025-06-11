#pragma once
#include "DxLib.h"
#include "list"
#include "vector"
#include "crtdbg.h"

using namespace std;

// ���낢��ȐF
const unsigned int BLACK	 = GetColor(0,   0,   0);	// ��
const unsigned int RED		 = GetColor(255, 0,   0);	// ��
const unsigned int GREEN	 = GetColor(0,   255, 0);	// ��
const unsigned int BLUE		 = GetColor(0,   0,   255);	// ��
const unsigned int YELLOW	 = GetColor(255, 255, 0);	// ��
const unsigned int LIGHTBLUE = GetColor(0,   255, 255);	// ���F
const unsigned int PURPLE	 = GetColor(255, 0,   255);	// ��
const unsigned int WHITE	 = GetColor(255, 255, 255);	// ��

// �X�N���[���T�C�Y
constexpr int	SCREEN_SIZE_X = 1280;	// X�����̉�ʃT�C�Y���w��
constexpr int	SCREEN_SIZE_Y = 720;	// Y�����̉�ʃT�C�Y���w��

// ��ʃT�C�Y����
constexpr int HALF_SCREEN_SIZE_X = SCREEN_SIZE_X / 2;
constexpr int HALF_SCREEN_SIZE_Y = SCREEN_SIZE_Y / 2;

// �p�x�����W�A���ɕς��邽�߂̂��
constexpr float CALC_ANGLE(float Rad) { return DX_PI_F * Rad / 180.0f; }
