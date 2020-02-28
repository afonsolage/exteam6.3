#pragma once

#if(CUSTOM_DINAMIC_EFFECT)

#define MAX_DYNAMIC_WING_EFFECT 1000

struct DYNAMIC_WING_EFFECT_INFO
{
	int Index;
	int ItemIndex;
	int EffectIndex;
	int EffectValue;
	int EffectLevel;
	float ColorR;
	float ColorG;
	float ColorB;
	float Effect1;
	float Effect2;
	float Effect;
};

class CDynamicWingEffect
{
public:
		CDynamicWingEffect();
		~CDynamicWingEffect();

	void Init();
	void Load();
	void Read(char* filename);
	BOOL SetDynamicEffect(int ItemIndex, DWORD a,DWORD b,DWORD c);

	DYNAMIC_WING_EFFECT_INFO m_DynamicData[MAX_DYNAMIC_WING_EFFECT];
	int m_CountDinamicEffect;
};

extern CDynamicWingEffect gDynamicWingEffect;

#endif