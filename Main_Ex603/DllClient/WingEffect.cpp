#include "stdafx.h"
#include "WingEffect.h"
#include "Item.h"
#include "Console.h"
#include "ReadScript.h"
#include "User.h"
#include "Defines.h"
#include "Object.h"
#include "TMemory.h"
#include "ItemAsm.h"
#include "Import.h"
#include "Debug.h"
#include "Console.h"
#include "Effect.h"
#include "DynamicEffect.h"

#if(CUSTOM_WINGSEFFECT)

CWingEffect g_WingEffect;

CWingEffect::CWingEffect()
{
	this->Init();
}

CWingEffect::~CWingEffect()
{
}

void CWingEffect::Init()
{
	this->m_Result = false;
	for(int n = 0; n < MAX_WING_EFFECT; n++)
	{
		this->m_EffectData[n].Index = -1;
		this->m_EffectData[n].ItemIndex = -1;
	}
}

void CWingEffect::Load()
{
	this->Init();

	this->Read(".\\Data\\Custom\\Configs\\WingEffect.txt");

	#if(CUSTOM_DINAMIC_EFFECT)

	gDynamicWingEffect.Load();

	#endif

	//SetRange((LPVOID)0x005666F7, 10, ASM::NOP);
	SetOp((LPVOID)0x005666F7, this->AddWingEffect, ASM::JMP);
}

void CWingEffect::Read(char* filename)
{
	SMDFile = fopen(filename, "r");

	if(!SMDFile)
	{
		MessageBox(pGameWindow, ".\\Data\\Custom\\Configs\\WingEffect.txt", "WingEffect.txt load error!", NULL);
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

		this->m_EffectData[n].Index = n;

		this->m_EffectData[n].ItemIndex = TokenNumber;	

		Token = GetToken();
		this->m_EffectData[n].EffectIndex = TokenNumber;

		Token = GetToken();
		this->m_EffectData[n].EffectValue = TokenNumber;

		Token = GetToken();
		this->m_EffectData[n].EffectLevel = TokenNumber;

		Token = GetToken();
		this->m_EffectData[n].ColorR = TokenNumber;

		Token = GetToken();
		this->m_EffectData[n].ColorG = TokenNumber;

		Token = GetToken();
		this->m_EffectData[n].ColorB = TokenNumber;

		Token = GetToken();
		this->m_EffectData[n].ColorSize = TokenNumber;

		Token = GetToken();
		this->m_EffectData[n].ColorMain = TokenNumber;

		Token = GetToken();
		this->m_EffectData[n].ColorSide = TokenNumber;
		
		n++;
	}

	this->m_CountStaticEffect = n;


	fclose(SMDFile);
}


__declspec(naked) void CWingEffect::AddWingEffect()
{
	static DWORD WingSetColorAddress1 = 0x0056EECF;
	static DWORD WingSetColorAddress2 = 0x00566701;

	_asm
	{
		MOV EAX, DWORD PTR SS:[EBP-0x70]
		PUSH EAX
		MOV ECX, DWORD PTR SS:[EBP-0x6C]
		PUSH ECX
		LEA EDX, DWORD PTR SS:[EBP-0x18]
		PUSH EDX
		MOV EAX, DWORD PTR SS:[EBP-0x68]
		PUSH EAX
		MOV ECX, DWORD PTR SS:[EBP-0x530]
		SUB ECX, ITEM_INTER
		PUSH ECX
		LEA ECX, g_WingEffect
		CALL [CWingEffect::SetWingEffect]

		#if(CUSTOM_DINAMIC_EFFECT)

		Test Eax,Eax
		Mov Eax,Dword Ptr Ss:[Ebp-0x70]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x6C]
		Push Ecx
		Lea Edx,Dword Ptr Ss:[Ebp-0x18]
		Push Edx
		Mov Eax,Dword Ptr Ss:[Ebp-0x68]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x530]
		Sub Ecx,ITEM_INTER
		Push Ecx
		Lea Ecx,gDynamicWingEffect
		Call [CDynamicWingEffect::SetDynamicEffect]

		#endif
	}
	
	if(g_WingEffect.m_Result)
	{
		_asm
		{
			JMP [WingSetColorAddress1]
		}
	}
	else
	{
		_asm
		{
			CMP DWORD PTR SS:[EBP-0x530], 0xA9D
			JMP [WingSetColorAddress2]
		}
	}
	

}

#define pAllowStaticEffect2		((void(__thiscall*)(LPVOID This, DWORD a2, DWORD a3, VAngle * a4, bool a5)) 0x545030)

int icons = false;

void CWingEffect::SetWingEffect(int ItemIndex, DWORD a, DWORD b, DWORD c, DWORD d)
{
	g_WingEffect.m_Result = false;

	if(!gItem.IsCustomWings(ItemIndex, false))
	{
		return;
	}
	
	//if(ItemIndex != 41 && ItemIndex != 44 )
	//{
	//	return;
	//}

	for(int n = 0; n < MAX_WING_EFFECT; n++)
	{
		if(this->m_EffectData[n].ItemIndex == ItemIndex)
		{
			float ItemColor[3];

			ItemColor[0] = this->m_EffectData[n].ColorR;

			ItemColor[1] = this->m_EffectData[n].ColorG;

			ItemColor[2] = this->m_EffectData[n].ColorB;

			pAllowStaticEffect((void*)a, &b, c, this->m_EffectData[n].EffectValue, this->m_EffectData[n].EffectLevel);

			pPlayStaticEffect(this->m_EffectData[n].EffectIndex, &b,this->m_EffectData[n].ColorSize, ItemColor, d, this->m_EffectData[n].ColorMain, (DWORD)this->m_EffectData[n].ColorSide);

			g_WingEffect.m_Result = true;
		}
	}
}

#endif