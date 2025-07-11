#pragma once
#include "DxLib.h"

enum class SoundKind
{
	NONE=-1,
	PLAY_BGM,
	JANP,
	JANPBLOAK,
	LANDING,
	POTAL,
	THORN,
	MOVECURSOR,
	PAWERUP,
	BATTLE,

	KindNum
};

constexpr char SE_FILE_PATH[(int)SoundKind::KindNum][256] =
{
	"Data/Sound/PLAY_BGM.wav",
	"Data/Sound/se_janp.wav",
	"Data/Sound/se_janpbloak.wav",
	"Data/Sound/se_landing.wav",
	"Data/Sound/se_potal.wav",
	"Data/Sound/se_thorn.wav",
	"Data/Sound/MoveCursor.mp3",
	"Data/Sound/PawerUp.mp3",
	"Data/Sound/Battle.mp3"
};

class SoundManager
{
private:
	static int soundHandle[(int)SoundKind::KindNum];

public:
	SoundManager();
	~SoundManager();

	//����������
	static void Init();

	//�I������
	static void Fin();

	//�S�f�[�^�ǂݍ���
	//��return 
	// -> true  = ���[�h����
	// -> false = 1�ȏ�̃f�[�^�����[�h���s
	static bool LoadAllData();

	//���݂̍Đ����Ԏ擾
	static int GetSoundTime(SoundKind soundID);

	//���Đ����Ԏ擾
	static int GetSoundAllTime(SoundKind soundID);

	//�Đ���Ԏ擾
	static bool IsPlay(SoundKind soundID);

	//�Đ��J�n���Ԑݒ�
	static void SetStartTime(SoundKind soundID, int startTime);

	//�{�����[���ݒ�
	// 0.0f <= Volime <= 1.0f
	static void SetVolume(SoundKind soundID, float Volume);

	//�T�E���h�Đ�
	static int Play(SoundKind soundID, int playType = DX_PLAYTYPE_BACK, bool isStart = true);

	//�T�E���h��~
	static int Stop(SoundKind soundID);

	//�S�T�E���h��~
	static void StopAll();
};