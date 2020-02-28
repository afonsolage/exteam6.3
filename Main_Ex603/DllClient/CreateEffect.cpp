#include "stdafx.h"
#include "Defines.h"
#include "Object.h"
#include "Item.h"
#include "CreateEffect.h"
#include "Skill.h"
#include "TMemory.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib") 

#if(DEV_EFFECT2)

cCreateEffect gCreateEffect;
float &WorldTime = *(float*)0x666C558; //
float &flt_7BC08A0 = *(float*)0x7BC08A0;

#define sub_545030 ((float(__thiscall*)(float *this, float *a2, float *a3, float *a4, char a5))0x545030)

float sub_4EC46D(float a1, float a2) //Main S13; Not here
{
	float v5;
	float v2 = a2 * 0.01745f;
	float v6 = (float)((int)(v2 * 1000.0f / a1 + timeGetTime()) % (int)(6283.185546875f / a1))* 0.001f * a1;

	if (v6 >= 3.14f)
	v5 = cosf(v6);
	else
	v5 = -cosf(v6);
	return (float)((v5 + 1.0f) * 0.5f);
}

void sub_92A1E9(vec3_t a1, float a2)
{
	float v1 = a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2];

	float v3 = sqrtf(v1);

	if (v3 < 0.000001f && v3 > -0.000001f)
	{
		a1[0] = 0.0;
		a1[1] = 0.0;
		a1[2] = 0.0;
	}
	else
	{
		float v2 = 1.0f / a2;

		a1[0] *= v2;
		a1[1] *= v2;
		a1[2] *= v2;
	}
}

//float sub_4EC46D(float a1, float a2) //Main S13; //Decompiled
//{
//    float v5;
//
//    float v2 = a2 * 0.01745f;
//    float v6 = (float)((int)(v2 * 1000.0f / a1 + GetLargeRand()) % (int)(6283.185546875f / a1))
//  * 0.001f
//  * a1;
//    if (v6 >= 3.14f)
//  v5 = cosf(v6);
//    else
//  v5 = -cosf(v6);
//    return (float)((v5 + 1.0f) * 0.5f);
//}
//
//void sub_92A1E9(vec3_t a1, float a2) //Decompiled
//{
//    float v1 = a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2];
//
//    float v3 = sqrtf(v1);
//
//    if (v3 < 0.000001f && v3 > -0.000001f)
//    {
//           a1[0] = 0.0;
//           a1[1] = 0.0;
//           a1[2] = 0.0;
//    }
//    else
//    {
//           float v2 = 1.0f / a2;
//
//           a1[0] *= v2;
//           a1[1] *= v2;
//           a1[2] *= v2;
//    }
//}

double sub_639050(float a1)
{
	double result; // st7

	if (a1 >= 0.0)
	result = a1;
	else
	result = -a1;
	return result;
}

void CreateItemEffect(int lpModel, int ItemID, vec3_t Light, float Alpha, int ItemLevel, int NewOption, int a10, int a11, int RenderType)
{
	pSetItemEffect(lpModel, ItemID, Light, Alpha, ItemLevel, NewOption, a10, a11, RenderType);

	LPVOID Model = pGetModel(pModelThis(), ItemID);
	vec3_t p;
	vec3_t Bone;
	vec3_t Color;
	vec3_t WorldPos;

	Vector(0.0f, 0.0f, 0.0f, p);
	Vector(WorldPos[0], WorldPos[1], WorldPos[2], WorldPos);//ok

	switch (ItemID)
	{
		case ITEM2(12, 196): //wing of Conqueror
		{
			int BoneID1[4] = { 14, 19, 37 ,42 };
			if (*(BYTE*)(oUserPreviewStruct + 120)) //Is character moving
			{
				float v213 = sub_4EC46D(10.0f, 0.0);

				if (v213 > 0.800000011920929f) // <- Change here may 0.4,0.5 is best	//original - 0.800000011920929f
				{
					Vector(1.0f, 0.55000001f, 0.050000001f, Color);
					for (int i = 0; i < 4; i++)
					{
						pAllowPlayEffect(Model, Bone, lpModel, BoneID1[i], 0);
						WorldPos[0] = Bone[0] - WorldPos[0];
						WorldPos[1] = Bone[1] - WorldPos[1];
						WorldPos[2] = Bone[2] - WorldPos[2];
						sub_92A1E9(WorldPos, WorldPos[2]);
						WorldPos[0] -= (0.25f - (float)(GetLargeRand() % 50) / 100.0f);
						WorldPos[2] -= (0.25f - (float)(GetLargeRand() % 50) / 100.0f);
						//WorldPos[0] = WorldPos[0] - (0.25f - (float)(GetLargeRand() % 50) / 100.0f);
						//WorldPos[2] = (float)0.0 - (0.25f - (float)(GetLargeRand() % 50) / 100.0f);
						gCreateEffect.DynamicEffectEx(32290, Bone, WorldPos, Color, 17, 1.5f, &*(ObjectModel*)*(DWORD*)lpModel);
					}
				}

			}

			float v266 = sub_4EC46D(-2.0, 0.0);

			if (v266 <= 0.800000011920929)
			{
				if (v266 < 0.6000000238418579)
					v266 = 0.60000002;
			}
			else
			{
				v266 = 0.80000001;
			}

			Vector(v266 * 1.0, v266 * 0.6000000238418579, 0.0f, Color);
			pQuickPlayStaticEffect(Model, 32842, 47, 0.60000002f, Color, lpModel);
			pQuickPlayStaticEffect(Model, 32842, 24, 0.60000002f, Color, lpModel);
			pQuickPlayStaticEffect(Model, 32842, 31, 0.60000002f, Color, lpModel);
			pQuickPlayStaticEffect(Model, 32842, 40, 0.60000002f, Color, lpModel);
			pQuickPlayStaticEffect(Model, 32842, 8, 0.60000002f, Color, lpModel);
			pQuickPlayStaticEffect(Model, 32842, 17, 0.60000002f, Color, lpModel);
			pQuickPlayStaticEffect(Model, 32842, 46, 1.2f, Color, lpModel);
			pQuickPlayStaticEffect(Model, 32842, 23, 1.2f, Color, lpModel);

			Vector(1.0f, 0.15000001f, 0.050000001f, Color);
			float rFloat = (double)(GetLargeRand() % 10) / 50.0 + 0.2000000029802322f;

			int BoneID2[8] = { 35, 39 ,44, 45, 12, 16, 21, 22 };
			for (int i = 0; i < 8; i++)
			{
				pQuickPlayStaticEffect(Model, 0x7E92, BoneID2[i], 0.40000001f + rFloat, Color, lpModel);
			}

			int BoneID3[7] = { 61, 59, 62, 55, 52, 53, 54 };
			for (int i = 0; i < 7; i++)
			{
				pQuickPlayStaticEffect(Model, 0x7E92, BoneID3[i], 0.2f + rFloat, Color,lpModel);
			}
		}
		break;
		// ----
		case ITEM2(12, 195):
		{
			float WorldTime = (0.10f - (float)(GetLargeRand() % 50) / 100.0f);
			float ft1 = WorldTime * 0.5f + 1.8f;
			float ft2 = WorldTime * 0.5f + 2.5f;

			int BoneID[22] = { 61,42,60,41,63,44,42,59,40,62,43,65,46,58,39,64,45,13,15,25,27,3 };

			Vector(0.34f, 0.25f, 1.0f, Color);

			for (int x = 0; x < 22; x++)
			{
				pQuickPlayStaticEffect(Model, 32002, BoneID[x], ft1, Color ,lpModel);
				if (x >= 22 - 5)
				{
					pQuickPlayStaticEffect(Model, 32842, BoneID[x], (0.5 + 0), Color, lpModel);
				}
			}

			for (int i12 = 0; i12 < 4; ++i12)
			{
				float v134 = sub_4EC46D(2.0, 90.0f);
				float v135 = 1.0 - v134;
				v135 = v135 * 3.0;
				float ft3 = v134 * 0.300000011920929;

				Vector(v135 * 1.0f, v135 * 0.6000000238418579f, v135 * 0.4000000059604645f, Color);

				pQuickPlayStaticEffect(Model, 32781, 14, ft3, Color, lpModel);
				pQuickPlayStaticEffect(Model, 32781, 26, ft3, Color, lpModel);
			}

			int BoneID2[8] = { 65,46,59,40,11,12,23,24 };
			Vector(0.0f, 0.0f, 0.0f, Color);

			for (int i13 = 0; i13 < 8; i13++)
			{
				pAllowPlayEffect(Model, Bone, lpModel, BoneID2[i13], 0);
				WorldPos[0] = Bone[0] - WorldPos[0];
				WorldPos[1] = Bone[1] - WorldPos[1];
				WorldPos[2] = Bone[2] - WorldPos[2];

				if (!((signed int)GetLargeRand() % 10))
				{
					//sub_545030(Model, &flt_7BC08A0[12 * *(&v202 + i13)], &v237, &v188, 1);
					//Type,Position,Angle,Light,SubType,Owner,PKKey,Skill,Scale,SkillSerial,SkillAngle,SkillHotKey
					if (i13 >= 8 / 2)
					CreateEffect(299, Bone, WorldPos, Color, 2, lpModel, -1, 0, 0.005, 0, 0, -1);	//299
					else//2
					CreateEffect(299, Bone, WorldPos, Color, 1, lpModel, -1, 0, 0.005, 0, 0, -1);	//299
				}
			}
		}
		break;
		// ----
		case ITEM2(12, 188):// Wings of Life
		{
			int BoneID[22] = { 8,9,19,21,29,37,6,11,18,22,5,10,17,20,27,35,7,16,28,36,44,50 };

			float v97 = WorldTime * 0.002000000094994903f;
			float v98 = cosf(v97);
			float v1263 = sub_639050(v98);

			for (int i10 = 0; i10 < 22; ++i10)
			{
				if (i10 >= 6)
				{
					Vector(v1263*1.0f, v1263*0.1000000014901161f, v1263*0.1000000014901161f, Color);
					if (i10 < 6 || i10 >= 10)
					{

						if (i10 < 10 || i10 >= 16)
						{
							if (i10 >= 16 && i10 < 22)
							{
								pQuickPlayStaticEffect(Model, 32002, BoneID[i10], 0.80000001f, Color, lpModel);
							}
						}
						else
						{
							pQuickPlayStaticEffect(Model, 32002, BoneID[i10], 1.0f, Color, lpModel);
						}
					}
					else
					{
						pQuickPlayStaticEffect(Model, 32002, BoneID[i10], 1.6f, Color, lpModel);
					}
				}
				else
				{
					Vector(v1263*1.0f, v1263 * 0.6499999761581421f, 0.0, Color);
					pQuickPlayStaticEffect(Model, 32002, BoneID[i10], 1.0999999f, Color, lpModel);
				}
			}
		}
		break;
		// ----
		case ITEM2(12, 186)://Wings of chaos
		{
			float v89 = WorldTime * 0.002000000094994903f;
			float v90 = cosf(v89);
			float v308 = sub_639050(v90);

			Vector(v308 + 0.300000011920929f, v308 + 0.300000011920929f, v308 + 0.300000011920929f, Color);
			pQuickPlayStaticEffect(Model, 32501, 43, 0.40000001f, Color, lpModel);

			float v91 = WorldTime * 0.05000000074505806f;
			float v93 = cosf(v91);
			v308 = sub_639050(v93);

			Vector(v308 + 0.300000011920929f, v308 + 0.300000011920929f, v308 + 0.300000011920929f, Color);
			pQuickPlayStaticEffect(Model, 32836, 43, 0.60000002f, Color, lpModel);

			Vector(1.0, 0.30000001, 1.0, Color);
			pQuickPlayStaticEffect(Model, 32783, 43, 0.2f, Color, lpModel);

			Vector(1.0, 1.0, 1.0, Color);
			pQuickPlayStaticEffect(Model, 32836, 43, 0.15000001f, Color, lpModel);
		}
		break;
		// ----
		case ITEM2(12, 187):
		{
			float v96 = WorldTime * 0.001000000047497451f;
			float v97 = cosf(v96);
			float v304 = sub_639050(v97) * 0.4000000059604645f;

			Vector((v304 + 0.5f) / 2.0f,
			(v304 + 0.5f) / 2.0f,
			(v304 + 0.5f) / 2.0f, Color);

			pQuickPlayStaticEffect(Model, 32836, 8, 0.80000001f, Color, lpModel);
			pQuickPlayStaticEffect(Model, 32836, 16, 0.80000001f, Color, lpModel);
			pQuickPlayStaticEffect(Model, 32231, 8, 0.60000002f, Color, lpModel);
			pQuickPlayStaticEffect(Model, 32231, 16, 0.60000002f, Color, lpModel);

			Vector(v304 + 0.5, v304 + 0.5, v304 + 0.5, Color);
			pQuickPlayStaticEffect(Model, 32231, 20, 0.60000002f, Color, lpModel);
			pQuickPlayStaticEffect(Model, 32231, 24, 0.60000002f, Color, lpModel);
		}
		break;
	}
}

DYNAMIC_EFFECT_INFO *m_DynamicEffectInfo = (DYNAMIC_EFFECT_INFO*)0x8907508;

int cCreateEffect::DynamicEffectEx(DWORD ModelID, vec3_t VecPos, vec3_t WorldPos, vec3_t Color, int SubEffectID, float Scale, ObjectModel* lpModel)
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
		case 32587: //Texture ID Main Season 13 -- Effectshiny06.jpg
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
		// ----
		case 32355:
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
		// ----
		case 32290:
		if (lpEffect->SubEffectID)
		{
			switch (lpEffect->SubEffectID)
			{
			case 0x11://for wings of conqueror
				lpEffect->Unknown68 = (float)(GetLargeRand() % 360);
				lpEffect->Unknown60 = 25;
				lpEffect->Scale = Scale;
				break;
			}
		}
		else
		{
			lpEffect->Unknown60 = 20;
			lpEffect->Unknown84.Z = (GetLargeRand() % 5 + 2);
		}
		//lpEffect->Unknown68 = (double)(GetLargeRand() % 360);
		//lpEffect->Scale = (double)(GetLargeRand() % 10 + 10) * 0.01999999955296516;
		// --
		lpEffect->VecPos.X = (double)(GetLargeRand() % 40) - 20.0 + lpEffect->VecPos.X;
		lpEffect->VecPos.Y = (double)(GetLargeRand() % 40) - 20.0 + lpEffect->VecPos.Y;
		lpEffect->VecPos.Z = (double)(GetLargeRand() % 20) - 10.0 + lpEffect->VecPos.Z;
		break;
		// ----
		case 32289: //Texture ID Main Season 13 -- Effect\\shiny06.jpg
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

void cCreateEffect::Load()
{
	//SetCompleteHook(0xE8, 0x0061041C, &CreateItemEffect);
	//SetCompleteHook(0xE8, 0x00610466, &CreateItemEffect);
	//SetCompleteHook(0xE8, 0x005666C1, &CreateItemEffect);

	SetOp((LPVOID)0x0061041C, (LPVOID)CreateItemEffect, ASM::CALL);
	SetOp((LPVOID)0x00610466, (LPVOID)CreateItemEffect, ASM::CALL);
	SetOp((LPVOID)0x005666C1, (LPVOID)CreateItemEffect, ASM::CALL);
}

#endif