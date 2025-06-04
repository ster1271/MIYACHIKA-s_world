#include "SoundManager.h"

int SoundManager::soundHandle[(int)SoundKind::KindNum];

SoundManager::SoundManager()
{
	for (int i = 0; i < (int)SoundKind::KindNum; i++)
	{
		soundHandle[i] = -1;
	}
}
SoundManager::~SoundManager()
{
	Fin();
}

void SoundManager::Init()
{
	for (int i = 0; i < (int)SoundKind::KindNum; i++)
	{
		soundHandle[i] = -1;
	}
}

void SoundManager::Fin()
{
	for (int i = 0; i < (int)SoundKind::KindNum; i++)
	{
		if (soundHandle[i] != -1)
		{
			DeleteSoundMem(soundHandle[i]);
			soundHandle[i] = -1;
		}
	}
}

bool SoundManager::LoadAllData()
{
	bool isAllDataSet = true;
	for (int i = 0; i < (int)SoundKind::KindNum; i++)
	{
		soundHandle[i] = LoadSoundMem(SE_FILE_PATH[i]);

		if(soundHandle[i] != -1) isAllDataSet = false;
	}

	return isAllDataSet;
}

int SoundManager::GetSoundTime(SoundKind soundID)
{
	return (int)GetSoundCurrentTime(soundHandle[(int)soundID]);
}

int SoundManager::GetSoundAllTime(SoundKind soundID)
{
	return (int)GetSoundTotalTime(soundHandle[(int)soundID]);
}

bool SoundManager::IsPlay(SoundKind soundID)
{
	return CheckSoundMem(soundHandle[(int)soundID]) == 1 ? true : false;
}

void SoundManager::SetStartTime(SoundKind soundID, int startTime)
{
	int Freq = GetFrequencySoundMem(soundHandle[(int)soundID]) * startTime / 1000;
	SetFrequencySoundMem(Freq, soundHandle[(int)soundID]);
}

void SoundManager::SetVolume(SoundKind soundID, float Volume)
{
	if (Volume < 0.f || Volume > 1.f) return;

	ChangeVolumeSoundMem((int)(255.f * Volume), soundHandle[(int)soundID]);
}

int SoundManager::Play(SoundKind soundID, int playType, bool isStart)
{
	return PlaySoundMem(soundHandle[(int)soundID], playType, isStart);
}

int SoundManager::Stop(SoundKind soundID)
{
	return StopSoundMem(soundHandle[(int)soundID]);
}

void SoundManager::StopAll()
{
	for (int i = 0; i < (int)SoundKind::KindNum; i++)
		StopSoundMem(soundHandle[i]);
}