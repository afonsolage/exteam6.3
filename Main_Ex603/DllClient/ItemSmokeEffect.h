#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
// ----------------------------------------------------------------------------------------------

#define MAX_SMOKE_EFFECT 100
#define SMOKE_EFFECT_DIR "Data/Custom/Configs/ItemSmokeEffect.ini"
// ----------------------------------------------------------------------------------------------

struct SmokeEffect_DATA
{
	short Index;
	short Level;
	float Red;
	float Green;
	float Blue;
};
// ----------------------------------------------------------------------------------------------

class ItemSmokeEffect
{
public:
		 ItemSmokeEffect();
		 ~ItemSmokeEffect();
	// ----
	void ReadList(char * File);
	void Load();
	// ----
	DWORD SmokeItemType;
	DWORD SmokeRed;
	DWORD SmokeGreen;
	DWORD SmokeBlue;
	// ----
	int SmokeCount;
	SmokeEffect_DATA Data[MAX_SMOKE_EFFECT];
};
extern ItemSmokeEffect gItemSmokeEffect;
// ----------------------------------------------------------------------------------------------