#include "stdafx.h"
#include "Sound.h"
//#include "LoraBattle.h"
#include "TMemory.h"
#include "Import.h"

#if(CUSTOM_SOUND==TRUE)

CSound g_Sound;

CSound::CSound()
{
}

CSound::~CSound()
{
}

void CSound::Load()
{
	SetRange((LPVOID)0x0063402B, 5, ASM::NOP);	
	SetOp((LPVOID)0x0063402B, this->LoadWav, ASM::CALL);
}

int CSound::LoadWav()
{
	pLoadSoundWav();
	return pLoadWavSound(eSOUND_TEAM_VS_TEAM, "Data\\Custom\\Sound\\Machinimasound.wav", 0, 0);
}

void CSound::Play(int ID)
{
	pPlayStop(ID, 1);
	pPlayWavSound(ID, 0, 0);
}

void CSound::Stop(int ID)
{
	pPlayStop(ID, 1);
}


#endif