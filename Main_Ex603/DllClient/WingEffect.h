#pragma once

#include "stdafx.h"

#if(CUSTOM_WINGSEFFECT)

#define MAX_WING_EFFECT			1000
#define MAX_DYNAMIC_WING_EFFECT	300

struct CUSTOM_WING_EFFECT_INFO
{
	int Index;
	int ItemIndex;
	int EffectIndex;
	int EffectValue;
	int EffectLevel;
	float ColorR;
	float ColorG;
	float ColorB;
	float ColorSize;
	float ColorMain;
	float ColorSide;
};

class CWingEffect
{
public:
		 CWingEffect();
		 ~CWingEffect();
	void Init();
	void Load();
	void Read(char* filename);
	static void AddWingEffect();
	void SetWingEffect(int ItemIndex, DWORD a, DWORD b, DWORD c, DWORD d);

	CUSTOM_WING_EFFECT_INFO m_EffectData[MAX_WING_EFFECT];
	int m_CountStaticEffect;

	bool m_Result;
};

extern CWingEffect g_WingEffect;

#endif