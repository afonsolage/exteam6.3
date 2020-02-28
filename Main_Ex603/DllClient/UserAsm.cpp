#include "stdafx.h"
#include "Defines.h"
#include "User.h"
#include "UserAsm.h"
#include "TMemory.h"
#include "Configs.h"
#include "ExLicense.h"
#include "ExText.h"

DWORD CharacterInfoExtern_Buff;
char CharacterInfoExtern_LevelBuff[40];

int ReturnUserLevel()
{
	lpCharObj lpPlayer = pUserObjectStruct;
	return lpPlayer->Level;
}

Naked(CharacterInfoExtern)
{
	if(gGRANDRESET)
	{
		sprintf(CharacterInfoExtern_LevelBuff, g_ExText.GetText(21), ReturnUserLevel(), gObjUser.Reset,gObjUser.GReset);
	}
	else
	{
		sprintf(CharacterInfoExtern_LevelBuff, g_ExText.GetText(22), ReturnUserLevel(), gObjUser.Reset);
	}

	_asm
	{
		lea eax, CharacterInfoExtern_LevelBuff
		push eax
		// ----
		mov CharacterInfoExtern_Buff, 0x0077FB85
		jmp CharacterInfoExtern_Buff
	}
}

DWORD OnClicker = 0x0095CE01;
DWORD OffClicker = 0x0095CD76;
Naked(HelperLevel)
{
	if(ReturnUserLevel() > gHelperLevel) _asm JMP OnClicker;
	else _asm JMP OffClicker;
}

DWORD asmHelperMessage = 0x0095CD9A;
Naked(HelperMessage)
{
	_asm
	{
		push gHelperLevel
		push 0x0DF5
		JMP asmHelperMessage
	}
}

void __declspec(naked) IllusionTemplFix()
{
	static DWORD dwSkill;
	static DWORD dwEAX;
	static DWORD dwJMPON = 0x0086FF58;
	static DWORD dwJMPOFF = 0x00870172;

	_asm
	{
		MOV dwEAX, EAX
		MOV EAX, DWORD PTR SS:[EBP-0x1C]
		MOV dwSkill, EAX
	}

	if(dwSkill == 210 || dwSkill == 212)
	{
		//*(BYTE*)0x8793381 = 0;

		_asm
		{
			MOV EAX, dwEAX
			JMP dwJMPON
		}
	}
	else
	{
		*(BYTE*)0x8793381 = 0;

		_asm
		{
			MOV EAX, dwEAX
			JMP dwJMPOFF
		}
	}
}

void LoadUserAsm()
{
	SetOp((LPVOID)0x0077FB7E, (LPVOID)CharacterInfoExtern, ASM::JMP);
	SetOp((LPVOID)0x0095CD6D, (LPVOID)HelperLevel, ASM::JMP);
	SetOp((LPVOID)0x0095CD93, (LPVOID)HelperMessage, ASM::JMP);
	SetByte((LPVOID)0x0064CBD1, 0xEB);//Help Is Active Message Disable

	SetRange((LPVOID)0x0086FF4C, 7, ASM::NOP);
	SetOp((LPVOID)0x0086FF4C, (LPVOID)IllusionTemplFix, ASM::JMP);
	
}
