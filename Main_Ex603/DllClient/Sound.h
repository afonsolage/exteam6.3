#pragma once

#include "stdafx.h"

#if(CUSTOM_SOUND==TRUE)

#define pPlayStop				((int(__cdecl*)(int a1, int a2))0x6D6D00)
#define pLoadSoundWav			((int(*)())0x62FBC0)

enum eSoundObectID
{
	eSound_LORABATTLESTART = 1000,
	eSOUND_TEAM_VS_TEAM,
};

class CSound
{
public:
	CSound();
	~CSound();

	void Load();
	static int LoadWav();
	void Play(int ID);
	void Stop(int ID);
};
extern CSound g_Sound;

#endif