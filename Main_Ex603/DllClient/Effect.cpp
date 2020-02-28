#include "stdafx.h"
#include "Defines.h"
#include "Object.h"
#include "Import.h"
#include "Skill.h"
#include "Effect.h"
#include "TMemory.h"
#include "CreateEffect.h"

#if(DEV_EFFECT)

cEffect  gEffect;

DYNAMIC_EFFECT_INFO *m_DynamicEffectInfo = (DYNAMIC_EFFECT_INFO*)0x8905508;

int cEffect::DynamicEffectEx(DWORD ModelID, vec3_t VecPos, vec3_t WorldPos, vec3_t Color, int SubEffectID, float Scale, ObjectModel* lpModel)
{
	DYNAMIC_EFFECT_INFO *lpEffect;

	for (int i = 0; i < 3000; ++i)
	{
		lpEffect = &m_DynamicEffectInfo[i];
		if (!lpEffect->Enable)
			break;
	}

	if (!lpEffect)
	{
		return 0;
	}

	lpEffect->Enable = 1;
	lpEffect->EffectID = ModelID;
	lpEffect->TextureID = ModelID;
	lpEffect->SubEffectID = SubEffectID;
	lpEffect->VecPos.X = VecPos[0];
	lpEffect->VecPos.Y = VecPos[1];
	lpEffect->VecPos.Z = VecPos[2];
	lpEffect->VecPos2.X = VecPos[0];
	lpEffect->VecPos2.Y = VecPos[1];
	lpEffect->VecPos2.Z = VecPos[2];
	lpEffect->Color.X = Color[0];
	lpEffect->Color.Y = Color[1];
	lpEffect->Color.Z = Color[2];
	lpEffect->Scale = Scale;
	lpEffect->Unknown80 = 0.0;
	lpEffect->Unknown60 = 2;
	lpEffect->Unknown72 = 0;
	lpEffect->m_Owner = lpModel;
	lpEffect->Unknown68 = 0.0;
	lpEffect->Unknown76 = 1;
	lpEffect->WorldPos.X = WorldPos[0];
	lpEffect->WorldPos.Y = WorldPos[1];
	lpEffect->WorldPos.Z = WorldPos[2];
	lpEffect->Unknown84.X = 0.0;
	lpEffect->Unknown84.Y = 0.0;
	lpEffect->Unknown84.Z = 0.0;

	switch (lpEffect->EffectID)
	{
	case 32587: //Texture ID Main Season 13 -- Effect\\shiny06.jpg
	if (lpEffect->SubEffectID)
	{
	if (lpEffect->SubEffectID > 0 && lpEffect->SubEffectID <= 3)
	{
	lpEffect->Unknown60 = GetLargeRand() % 11 + 20;
	lpEffect->Unknown56 = 0.0;
	lpEffect->Unknown68 = (float)(GetLargeRand() % 180);
	lpEffect->Scale = Scale - (float)(GetLargeRand() % 6) * (Scale / 10.0f);

	switch (lpEffect->SubEffectID)
	{
	case 1:
	lpEffect->VecPos.X = (float)(GetLargeRand() % 31) - 15.0f + lpEffect->VecPos.X;
	lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) - 15.0f + lpEffect->VecPos.Y;
	lpEffect->VecPos.Z = (float)(GetLargeRand() % 21) + 12.0f + lpEffect->VecPos.Z;
	break;
	case 2:
	lpEffect->VecPos.X = (float)(GetLargeRand() % 31) / 30.0f * 40.0f - 20.0f + lpEffect->VecPos.X;
	lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) / 30.0f * 40.0f - 20.0f + lpEffect->VecPos.Y;
	lpEffect->VecPos.Z = (float)(GetLargeRand() % 24) + 14.0f + lpEffect->VecPos.Z;
	break;
	case 3:
	lpEffect->VecPos.X = (float)(GetLargeRand() % 31) / 30.0f * 70.0f - 35.0f + lpEffect->VecPos.X;
	lpEffect->VecPos.Y = (float)(GetLargeRand() % 31) / 30.0f * 70.0f - 35.0f + lpEffect->VecPos.Y;
	lpEffect->VecPos.Z = (float)(GetLargeRand() % 30) + 20.0f + lpEffect->VecPos.Z;
	break;
	}
	}
	else
	{
	switch (lpEffect->SubEffectID)
	{
	case 4:

	break;
	case 6:
	lpEffect->Unknown60 = 15;
	lpEffect->Unknown68 = (float)(GetLargeRand() % 360);
	lpEffect->Unknown84.X = (float)-(GetLargeRand() % 2 - 1);
	lpEffect->Unknown84.Y = (float)-(GetLargeRand() % 4);
	lpEffect->Unknown84.Z = (float)-(GetLargeRand() % 4);
	break;
	case 7:
	lpEffect->Scale = (float)(GetLargeRand() % 8 + 1) * 0.1 * Scale;
	lpEffect->Unknown60 = GetLargeRand() % 20 + 20;
	lpEffect->Unknown56 = 1.0f;
	lpEffect->Unknown68 = (float)(GetLargeRand() % 180);
	break;
	}
	}
	}
	else
	{
	lpEffect->Unknown60 = 18;
	lpEffect->WorldPos.X = 45.0;
	}
	break; //return i; <---
	}

	return 0; 
}

void cEffect::Load()
{
	//SetOp((LPVOID)0x0061041C, (LPVOID)gEffect.DynamicEffectEx, ASM::CALL);
	//SetOp((LPVOID)0x00610466, (LPVOID)gEffect.DynamicEffectEx, ASM::CALL);
	//SetOp((LPVOID)0x005666C1, (LPVOID)gEffect.DynamicEffectEx, ASM::CALL);

	//gCreateEffect.Load();
}




#endif