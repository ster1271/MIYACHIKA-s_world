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

	//初期化処理
	static void Init();

	//終了処理
	static void Fin();

	//全データ読み込み
	//※return 
	// -> true  = ロード成功
	// -> false = 1つ以上のデータがロード失敗
	static bool LoadAllData();

	//現在の再生時間取得
	static int GetSoundTime(SoundKind soundID);

	//総再生時間取得
	static int GetSoundAllTime(SoundKind soundID);

	//再生状態取得
	static bool IsPlay(SoundKind soundID);

	//再生開始時間設定
	static void SetStartTime(SoundKind soundID, int startTime);

	//ボリューム設定
	// 0.0f <= Volime <= 1.0f
	static void SetVolume(SoundKind soundID, float Volume);

	//サウンド再生
	static int Play(SoundKind soundID, int playType = DX_PLAYTYPE_BACK, bool isStart = true);

	//サウンド停止
	static int Stop(SoundKind soundID);

	//全サウンド停止
	static void StopAll();
};