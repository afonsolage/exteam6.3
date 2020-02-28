#include "stdafx.h"
#include "DynamicEffect.h"
#include "ReadScript.h"
#include "Import.h"
#include "CreateEffect.h"

#if(CUSTOM_DINAMIC_EFFECT)

CDynamicWingEffect gDynamicWingEffect;


CDynamicWingEffect::CDynamicWingEffect()
{
	this->Init();
}

CDynamicWingEffect::~CDynamicWingEffect()
{
}

void CDynamicWingEffect::Init()
{
	for(int n=0;n < MAX_DYNAMIC_WING_EFFECT;n++)
	{
		this->m_DynamicData[n].Index = -1;
		this->m_DynamicData[n].ItemIndex = -1;
	}
}

void CDynamicWingEffect::Load()
{
	this->Init();

	this->Read(".\\Data\\Custom\\Configs\\DynamicEffect.txt");
}

void CDynamicWingEffect::Read(char* filename)
{
	SMDFile = fopen(filename, "r");

	if(!SMDFile)
	{
		MessageBox(pGameWindow, ".\\Data\\Custom\\Configs\\DynamicEffect.txt", "WingEffect.txt load error!", NULL);
		return;
	}

	int n = 0;

	while(true)
	{
		SMDToken Token = GetToken();

		if(Token == END || !strcmp(TokenString, "end"))
		{
			break;
		}

		this->m_DynamicData[n].Index = n;

		this->m_DynamicData[n].ItemIndex = TokenNumber;	

		Token = GetToken();
		this->m_DynamicData[n].EffectIndex = TokenNumber;

		Token = GetToken();
		this->m_DynamicData[n].EffectValue = TokenNumber;

		Token = GetToken();
		this->m_DynamicData[n].EffectLevel = TokenNumber;

		Token = GetToken();
		this->m_DynamicData[n].ColorR = TokenNumber;

		Token = GetToken();
		this->m_DynamicData[n].ColorG = TokenNumber;

		Token = GetToken();
		this->m_DynamicData[n].ColorB = TokenNumber;

		Token = GetToken();
		this->m_DynamicData[n].Effect1 = TokenNumber;

		Token = GetToken();
		this->m_DynamicData[n].Effect2 = TokenNumber;

		Token = GetToken();
		this->m_DynamicData[n].Effect = TokenNumber;
		
		n++;
	}

	this->m_CountDinamicEffect = n;

	fclose(SMDFile);
}

BOOL CDynamicWingEffect::SetDynamicEffect(int ItemIndex,DWORD a,DWORD b,DWORD c) // OK
{

	for(int n=0;n < MAX_DYNAMIC_WING_EFFECT;n++)
	{
		if(this->m_DynamicData[n].ItemIndex == ItemIndex)
		{
			float ItemColor[3];

			ItemColor[0] = this->m_DynamicData[n].ColorR;

			ItemColor[1] = this->m_DynamicData[n].ColorG;

			ItemColor[2] = this->m_DynamicData[n].ColorB;

			//((void(__thiscall*)(void*,DWORD,DWORD,DWORD,DWORD))0x00544E60)((void*)a,b,c,this->m_DynamicData[n].EffectValue,this->m_DynamicData[n].EffectLevel);
			//((void(*)(DWORD,DWORD,DWORD,float*,DWORD,float,DWORD))0x0074CBE0)(this->m_DynamicData[n].EffectIndex,b,c,ItemColor,this->m_DynamicData[n].Effect1,this->m_DynamicData[n].Effect,this->m_DynamicData[n].Effect2);
		
			pAllowStaticEffect((void*)a, &b, c, this->m_DynamicData[n].EffectValue, this->m_DynamicData[n].EffectLevel);
			pPlayDynamicEffect(this->m_DynamicData[n].EffectIndex,&b,c,ItemColor,this->m_DynamicData[n].Effect1,this->m_DynamicData[n].Effect,this->m_DynamicData[n].Effect2);
			//gCreateEffect.DynamicEffectEx(this->m_DynamicData[n].EffectIndex,&b,c,ItemColor,this->m_DynamicData[n].Effect1,this->m_DynamicData[n].Effect,this->m_DynamicData[n].Effect2);
		}
	}
	return 0;
}

#endif