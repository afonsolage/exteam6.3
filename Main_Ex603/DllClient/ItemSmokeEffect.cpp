#include "stdafx.h"
#include "ItemSmokeEffect.h"
#include "Defines.h"
#include "ReadScript.h"
#include "ExFunction.h"
#include "TMemory.h"
#include "Import.h"
#include "Console.h"
// ----------------------------------------------------------------------------------------------

ItemSmokeEffect gItemSmokeEffect;
// ----------------------------------------------------------------------------------------------

Naked(SetItemEffect)
{
	_asm
	{
		MOV gItemSmokeEffect.SmokeItemType, EAX
	}
	// ----
	if( gItemSmokeEffect.SmokeItemType == 0x1ABE)
	{
		_asm
		{
			MOV EDI, 0x0057AD8D
			JMP EDI
		}
	}
	else
	{
		for(int i = 0; i < gItemSmokeEffect.SmokeCount; i++)
		{
			if( gItemSmokeEffect.SmokeItemType == ITEM2(11,gItemSmokeEffect.Data[i].Index) && *(DWORD*)0x7BD0458 >= gItemSmokeEffect.Data[i].Level)
			{
				_asm
				{
					MOV EDI, 0x0057AD9A
					JMP EDI
				}
			}
		}
	}
	// ----
	_asm
	{
		MOV EDI, 0x0057B73B
		JMP EDI
	}
}
// ----------------------------------------------------------------------------------------------

Naked(SetColorEffect)
{
	_asm
	{
		MOV gItemSmokeEffect.SmokeItemType, EAX
	}
	// ----
	if( gItemSmokeEffect.SmokeItemType == 0x1ABE)
	{
		_asm
		{
			MOV ECX,DWORD PTR SS:[EBP+0x0C]
			FLD DWORD PTR DS:[0x0D23514]               ; FLOAT 0.6000000
			FSTP DWORD PTR DS:[ECX+0x9C]
			MOV EDX,DWORD PTR SS:[EBP+0x0C]
			FLD DWORD PTR DS:[0x0D23784]               ; FLOAT 0.3000000
			FSTP DWORD PTR DS:[EDX+0x0A0]
			MOV EAX,DWORD PTR SS:[EBP+0x0C]
			FLD DWORD PTR DS:[0x0D2351C]               ; FLOAT 0.4000000
			FSTP DWORD PTR DS:[EAX+0x0A4]
			// --
			MOV EDI, 0x0057AF2E
			JMP EDI
		}
	}
	else
	{
		for(int i = 0; i < gItemSmokeEffect.SmokeCount; i++)
		{
			if( gItemSmokeEffect.SmokeItemType == ITEM2(11,gItemSmokeEffect.Data[i].Index))
			{
				memcpy(&gItemSmokeEffect.SmokeRed, &gItemSmokeEffect.Data[i].Red, sizeof( float ));
				memcpy(&gItemSmokeEffect.SmokeGreen, &gItemSmokeEffect.Data[i].Green, sizeof( float ));
				memcpy(&gItemSmokeEffect.SmokeBlue, &gItemSmokeEffect.Data[i].Blue, sizeof( float ));
				// ----
				_asm
				{
					MOV ECX,DWORD PTR SS:[EBP+0x0C]
					FLD DWORD PTR DS:[gItemSmokeEffect.SmokeRed]
					FSTP DWORD PTR DS:[ECX+0x9C]
					MOV EDX,DWORD PTR SS:[EBP+0x0C]
					FLD DWORD PTR DS:[gItemSmokeEffect.SmokeGreen]
					FSTP DWORD PTR DS:[EDX+0x0A0]
					MOV EAX,DWORD PTR SS:[EBP+0x0C]
					FLD DWORD PTR DS:[gItemSmokeEffect.SmokeBlue]
					FSTP DWORD PTR DS:[EAX+0x0A4]
					// --
					MOV EDI, 0x0057AF2E
					JMP EDI
				}
			}
		}
	}
	// ----
	_asm
	{
		MOV EDI, 0x0057AF2E
		JMP EDI
	}
}
// ----------------------------------------------------------------------------------------------

ItemSmokeEffect::ItemSmokeEffect()
{
	this->SmokeItemType = 0;
	this->SmokeRed = 0;
	this->SmokeGreen = 0;
	this->SmokeBlue = 0;
	this->SmokeCount = 0;
	ZeroMemory(&Data,sizeof(Data));
}
// ----------------------------------------------------------------------------------------------

ItemSmokeEffect::~ItemSmokeEffect()
{

}
// ----------------------------------------------------------------------------------------------

void ItemSmokeEffect::Load()
{
	this->ReadList(SMOKE_EFFECT_DIR);
	// ----
	SetOp((LPVOID)0x0057AD82,SetItemEffect,ASM::JMP); 
	SetOp((LPVOID)0x0057AEFA,SetColorEffect,ASM::JMP);
}
// ----------------------------------------------------------------------------------------------

void ItemSmokeEffect::ReadList(char * File)
{
	int Token;
	// ----
	SMDFile = fopen(File, "r");
	// ----
	if (!SMDFile)
	{
		MessageBoxError("%s - file nor found", File);
		ExitProcess(0);
		return;
	}
	// ----
	this->SmokeCount = 0;
	// ----
	while(true)
	{
		Token = GetToken();
		// ----
		if( Token == END || !strcmp(TokenString, "end") )
		{
			break;
		}
		// ----
		if( this->SmokeCount >= MAX_SMOKE_EFFECT)
		{
			break;
		}
		// ----
		this->Data[this->SmokeCount].Index	= TokenNumber;
		// ----
		GetToken();
		this->Data[this->SmokeCount].Level	= TokenNumber;
		// ----
		GetToken();
		this->Data[this->SmokeCount].Red	= TokenNumber;
		// ----
		GetToken();
		this->Data[this->SmokeCount].Green	= TokenNumber;
		// ----
		GetToken();
		this->Data[this->SmokeCount].Blue	= TokenNumber;

		gConsole.Output(cGREEN, "%d %d %f %f %f", 
			this->Data[this->SmokeCount].Index,
			this->Data[this->SmokeCount].Level,
			this->Data[this->SmokeCount].Red,
			this->Data[this->SmokeCount].Green,
			this->Data[this->SmokeCount].Blue);
		// ----
		this->SmokeCount++;
	}
	fclose(SMDFile);	
}
// ----------------------------------------------------------------------------------------------