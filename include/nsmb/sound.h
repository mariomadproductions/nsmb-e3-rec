#pragma once

#include "nsmb/vector.h"

typedef enum {
	Surround,
	Headphones,
	Stereo
} SoundMode;

extern SoundMode soundMode;

#ifdef __cplusplus
extern "C"
{
#endif

	void ClearSoundHeap();
	void Music_LoadSeq(int seqNo);
	void Music_LoadSoundset(int sndsetNo);
	void Music_ClearAndLoadSeqWithSoundset(int seqNo, int sndsetNo);
	void Music_PlaySeq(int seqNo, int sndsetNo);
	void Music_StopSeq(int fadeFrame);
	void Music_PauseSeq(int seqNo);
	void Music_StartMusicNumber(int seqNo);
	void Music_ResetVars();

	int Music_GetLevelSeqNo(int playerNumber);

	void Music_LoadLevelSeqs();
	void Music_LoadToadHouseLevelSeqs();
	void Music_LoadLevelMusic();

	void PlaySNDEffect(int sndNo, Vec3* pos);
	void PlaySNDEffect2(int sndNo, Vec3* pos);
	void PlaySNDEffect3(int sndNo, Vec3* pos);

	void SetSoundMode(SoundMode SoundMode);

	static inline void Music_LoadSeqs(int* seqNos) {
		for (int i = 0; seqNos[i] != -1; i++)
			Music_LoadSeq(seqNos[i]);
	}

#ifdef __cplusplus
}
#endif