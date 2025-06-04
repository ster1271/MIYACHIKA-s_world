#include "FrameRate.h"
#include "../Font/Font.h"

float FrameRate::deltaTime;
ULONGLONG FrameRate::currentTime;
ULONGLONG FrameRate::lastFrateTime;
int FrameRate::count;
ULONGLONG FrameRate::calcFpsTime;
float FrameRate::fps;

void FrameRate::Init()
{
	deltaTime = 0.0f;
	currentTime = static_cast<ULONGLONG>(0);
	lastFrateTime = static_cast<ULONGLONG>(0);
	count = 0;
	calcFpsTime = static_cast<ULONGLONG>(0);
	fps = 0.0f;
}

bool FrameRate::Admin()
{
	Sleep(1);	//�V�X�e���ɏ�����Ԃ�

	//���݂̎��Ԃ��擾
	currentTime = GetNowSysPerformanceCount();

	//�ŏ��̃��[�v�Ȃ�
	// �i���o�[�t�H���g�f�[�^��������
	//���݂̎��Ԃ��AFPS�̌v�Z���������Ԃɐݒ�
	if (calcFpsTime == (ULONGLONG)0)
	{
		calcFpsTime = lastFrateTime = currentTime;
		fps = static_cast<float>(FRAME_RATE);
	}

	//���݂̎��Ԃ��A�O��̃t���[�������
	//FRAME_TIME�ȏ�o�߂��Ă����珈�������s����
	int work = static_cast<int>(currentTime - lastFrateTime);
	deltaTime = static_cast<float>(work) / 10000000.0f;
	if (deltaTime >= 0.05f)
	{
		deltaTime = 0.05f;
	}
	if (deltaTime * 10000.0f >= FRAME_TIME)
	{
		//�t���[�����s���̎��Ԃ��X�V
		lastFrateTime = currentTime;

		//�t���[�������J�E���g
		count++;

		return true;
	}

	return false;
}

void FrameRate::CalcFPS()
{
	//�O���FPS���v�Z�������Ԃ���̌o�ߎ��Ԃ����߂�
	ULONGLONG difTime = ConvSysPerformanceCountToMilliSeconds(currentTime - calcFpsTime);

	//�O���FPS���v�Z�������Ԃ���
	//1�b�ȏ�o�߂��Ă�����FPS���v�Z����
	if (difTime > 1000)
	{
		//�t���[���񐔂��~���b�ɍ��킹��
		//�����܂ŏo�������̂�float�ɃL���X�g
		float frameCount = (float)(count * 1000.0f);

		//FPS�����߂�
		//���z�̐��l�� 60000 / 1000 �� 60 �ƂȂ�	(FRAME_RATE = 60 �̏ꍇ)
		fps = frameCount / difTime;

		//�t���[�����[�g�J�E���g���N���A
		count = 0;

		//FPS���v�Z�������Ԃ��X�V
		calcFpsTime = currentTime;
	}
}

//FPS�\���i�f�o�b�N�p�j
void FrameRate::DrawFPS()
{
	DrawFormatStringToHandle(SCREEN_SIZE_X - DEFAULT_FONT_SIZE * 3, SCREEN_SIZE_Y - DEFAULT_FONT_SIZE,
		WHITE, Font::GetfontHandle(FontType::HGP�n�p�p�|�b�v��),
		"%.2f", fps);
	DrawFormatStringToHandle(0, SCREEN_SIZE_Y - DEFAULT_FONT_SIZE,
		WHITE, Font::GetfontHandle(FontType::HGP�n�p�p�|�b�v��),
		"%.5f", deltaTime);
}
