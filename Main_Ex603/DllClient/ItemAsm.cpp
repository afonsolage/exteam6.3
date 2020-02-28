#include "stdafx.h"
#include "Defines.h"
#include "Item.h"
#include "TMemory.h"
#include "ItemAsm.h"
#include "Console.h"
#include "ItemPrice.h"
#include "Interface.h"

bool g_bWingsActive = false;
DWORD g_dwWingsType;
DWORD g_dwWingsDamage;
DWORD g_dwWingsAbsord;

DWORD	AddWingsEffect_Buff;
float	Color[3];

// ----------------------------------------------------------------------------------------------
//=============================================
//	Разрешение кидать новые камни в вещи
//=============================================

DWORD AllowJewelsInsert_Buff;
DWORD AllowJewelsInsert_Buff2;
DWORD AllowJewelsInsert_Buff3;

Naked(AllowJewelsInsert)
{
	_asm
	{
		mov AllowJewelsInsert_Buff, edx
	}
	// ----
	if(		AllowJewelsInsert_Buff == ITEM(14, 14)
		||	gItem.IsCustomJewels(AllowJewelsInsert_Buff, false) )
	{
		_asm
		{
			mov AllowJewelsInsert_Buff, 0x008382C1
			jmp AllowJewelsInsert_Buff
		}
	}
	// ----
	_asm
	{
		mov AllowJewelsInsert_Buff, 0x0083826B
		jmp AllowJewelsInsert_Buff
	}
}
// ----------------------------------------------------------------------------------------------

//=============================================
//	Визуальный флаг камней
//=============================================
DWORD ReToJewelVisualFlag_Buff;

Naked(ReToJewelVisualFlag)
{
	_asm
	{
		mov ReToJewelVisualFlag_Buff, eax
	}
	// ----
	if(		ReToJewelVisualFlag_Buff == ITEM(14, 13)
		||	gItem.IsCustomJewels(ReToJewelVisualFlag_Buff, false) )
	{
		_asm
		{
			mov ReToJewelVisualFlag_Buff, 0x007DBD5A
			jmp ReToJewelVisualFlag_Buff
		}
	}
	// ----
	_asm
	{
		mov ReToJewelVisualFlag_Buff, 0x007DBD4C
		jmp ReToJewelVisualFlag_Buff
	}
}
// ----------------------------------------------------------------------------------------------
//=============================================
//	Добовление глов Эффекта
//=============================================
DWORD AddShineGlow_Buff;
Naked(AddShineGlow)
{
	_asm
	{
		mov AddShineGlow_Buff, eax
	}
	// ----
	if( gItem.IsCustomJewels(AddShineGlow_Buff, true) )
	{
		_asm
		{
			mov dword ptr ss:[ebp-4], 9
			mov AddShineGlow_Buff, 0x0060A3B0
			jmp AddShineGlow_Buff
		}
	}
	// ----
	if( AddShineGlow_Buff > 0x1E96 )
	{
		_asm
		{
			mov AddShineGlow_Buff, 0x0060A07F
			jmp AddShineGlow_Buff
		}
	}
	// ----
	_asm
	{
		mov AddShineGlow_Buff, 0x00609FF8
		jmp AddShineGlow_Buff
	}
}
// ----------------------------------------------------------------------------------------------

//=============================================
//	Цвет вещей на полу
//=============================================
DWORD DropTitleColor_Buff;
DWORD DropTitleColor_Buff2;
Naked(DropTitleColor)
{
	_asm
	{
		mov DropTitleColor_Buff2, eax
		mov eax, dword ptr ds:[ecx+0x30]
		mov DropTitleColor_Buff, eax
		mov eax, DropTitleColor_Buff2
	}
	// ----
	if(		DropTitleColor_Buff == ITEM2(14, 14)
		||	gItem.IsCustomJewels(DropTitleColor_Buff, true) )
	{
		_asm
		{
			mov DropTitleColor_Buff, 0x005F439E
			jmp DropTitleColor_Buff
		}
	}
	// ----
	_asm
	{
		mov DropTitleColor_Buff, 0x005F3F9E
		jmp DropTitleColor_Buff
	}
}


//=============================================
//	Разрешить бросать вещи в вещи выше доспехов
//=============================================
DWORD FixWingsJewelsInsert_Buff;
DWORD FixWingsJewelsInsert_Buff2;
DWORD FixWingsJewelsInsert_Buff3;
DWORD FixWingsJewelsInsert_Buff4;

Naked(FixWingsJewelsInsert)
{
	_asm
	{
		mov FixWingsJewelsInsert_Buff2, ecx

		mov FixWingsJewelsInsert_Buff3, edx
		mov ecx, dword ptr ss:[ebp-0x20]
		movsx edx, word ptr ds:[ecx]
		mov FixWingsJewelsInsert_Buff4, edx
		mov edx, FixWingsJewelsInsert_Buff3

		mov ecx, dword ptr ss:[ebp-0x3c]
		mov FixWingsJewelsInsert_Buff, ecx
		mov ecx, FixWingsJewelsInsert_Buff2
	}
	// ----
	if(		FixWingsJewelsInsert_Buff == 0x1887 
		||	gItem.IsWings2_5(FixWingsJewelsInsert_Buff, false) 
		||	gItem.IsWings4(FixWingsJewelsInsert_Buff, false) 
		||	gItem.IsWings5(FixWingsJewelsInsert_Buff, false)
		||	gItem.IsWings6(FixWingsJewelsInsert_Buff, false) 
		||	gItem.IsCustomJewels(FixWingsJewelsInsert_Buff4, false) )
	{
		_asm
		{
			mov FixWingsJewelsInsert_Buff, 0x00838365
			jmp FixWingsJewelsInsert_Buff
		}
	}
	// ----
	_asm
	{
		mov FixWingsJewelsInsert_Buff, 0x00838361
		jmp FixWingsJewelsInsert_Buff
	}
}

//=============================================
//	Fix Wings Exellent Glow
//=============================================
DWORD FixWingsExcellentGlow_Buff;
DWORD FixWingsLevelGlow_Buff;

Naked(FixWingsExcellentGlow)
{
	_asm
	{
		mov FixWingsExcellentGlow_Buff, ecx
		mov ecx, dword ptr ds:[FixWingsExcellentGlow_Buff + 0x30]
		mov FixWingsExcellentGlow_Buff, ecx
	}
	// ----
	if(		FixWingsExcellentGlow_Buff <= ITEM2(12, 50)
		||	gItem.IsCustomWings(FixWingsExcellentGlow_Buff, true) )
	{
		_asm
		{
			mov FixWingsExcellentGlow_Buff, 0x0060F325
			jmp FixWingsExcellentGlow_Buff
		}
	}
	// ----
	_asm
	{
		mov FixWingsExcellentGlow_Buff, 0x0060EE95
		jmp FixWingsExcellentGlow_Buff
	}
}
// ----------------------------------------------------------------------------------------------


DWORD FixWingsLevelGlow_Buff2;

Naked(FixWingsLevelGlow)
{
	_asm
	{
		mov FixWingsLevelGlow_Buff, ecx
		sub ecx, 0x1C9A
		mov FixWingsLevelGlow_Buff2, ecx
		mov dword ptr ss:[ebp-0x4ec], ecx
	}
	// ----
	if( gItem.IsCustomWings(FixWingsLevelGlow_Buff, true) )
	{
		_asm
		{
			mov dword ptr ss:[ebp-4], 0
		}
	}
	// ----
	if( FixWingsLevelGlow_Buff2 > 136 )
	{
		_asm
		{
			mov FixWingsLevelGlow_Buff, 0x0060A3B0
			jmp FixWingsLevelGlow_Buff
		}
	}
	else
	{
		_asm
		{
			mov FixWingsLevelGlow_Buff, 0x0060A06B
			jmp FixWingsLevelGlow_Buff
		}
	}
}
// ----------------------------------------------------------------------------------------------

DWORD FixWingsMoveList_Buff;

Naked(FixWingsMoveList)
{
	_asm
	{
		mov FixWingsMoveList_Buff, eax
	}
	// ----
	if( FixWingsMoveList_Buff == 0x1887 || gItem.IsCustomWings(FixWingsMoveList_Buff, false) )
	{
#ifdef exDEBUG_CODE
	//gConsole.Output(cGREEN,"Move");
#endif
		_asm
		{
			mov FixWingsMoveList_Buff, 0x00831996
			jmp FixWingsMoveList_Buff
		}
	}
	// ----
	_asm
	{
		mov FixWingsMoveList_Buff, 0x008319D5
		jmp FixWingsMoveList_Buff
	}
}
// ----------------------------------------------------------------------------------------------

DWORD WingsFixMoveKanturu_Buff;

Naked(WingsFixMoveKanturu)
{
	_asm
	{
		mov WingsFixMoveKanturu_Buff, ecx
	}
	// ----
	if(		gItem.IsCustomWings(WingsFixMoveKanturu_Buff, false)
		||	WingsFixMoveKanturu_Buff == 0x1887 )
	{
		_asm
		{
			mov WingsFixMoveKanturu_Buff, 0x00876E5E
			jmp WingsFixMoveKanturu_Buff
		}
	}
	// ----
	_asm
	{
		mov WingsFixMoveKanturu_Buff, 0x00876E50
		jmp WingsFixMoveKanturu_Buff
	}
}
// ----------------------------------------------------------------------------------------------

DWORD ItemLuckID;
DWORD ItemLuckReturnOn = 0x0058CF65;
DWORD ItemLuckReturnOff = 0x0058CF88;

Naked(WingsLuck)
{
	//_asm mov ItemLuckID, EDX
	//if(ItemLuckID == 0x18B4 || gItem.IsCustomWings(ItemLuckID, false)) _asm JMP ItemLuckReturnOn
	//else _asm JMP ItemLuckReturnOff

		_asm mov ItemLuckID, EDX
	if(ItemLuckID == 0x18B4 || gItem.IsCustomWings(ItemLuckID, false))
	{
			
			_asm 
			{ 
				MOV EDI,0x0058CF65
				JMP EDI
			}
	}
	else
	{
			_asm 
			{ 
				MOV EDI,0x0058CF88
				JMP EDI
			}
	}
}

// ----------------------------------------------------------------------------------------------

//WingsOptions
//0058D40A
//0058D4D7 NO
//0058D45A YES


DWORD ItemOptID;
DWORD ItemOptReturnOn = 0x0058D412;//0x0058D44D;// 0x0058D45A;
DWORD ItemOptReturnOff = 0x0058D44D;// 0x0058D4D7;	

Naked(WingsOptions)
{
	//_asm mov ItemOptID, EDX
	//_asm mov ItemOptID, ECX //DangeR Fix
	//if(ItemOptID == 0x1802 || gItem.IsCustomWings(ItemOptID, false)) _asm JMP ItemOptReturnOn
	//else _asm JMP ItemOptReturnOff

	_asm
	{
		MOV ItemOptID, ECX //DangeR Fix
	}
	// ----
	if(ItemOptID == 0x1802 || gItem.IsCustomWings(ItemOptID, false))
	{
	#ifdef exDEBUG_CODE
	//gConsole.Output(cGREEN,"Option");
#endif
		_asm
		{
			MOV EDI, 0x0058D412
			JMP EDI
		}
	}
	else 
	{
		_asm
		{
			MOV EDI, 0x0058D44D
			JMP EDI
		}
	}
}

// ----------------------------------------------------------------------------------------------

bool bWingSearch = false;
DWORD WingProcID = 0;
DWORD WingProcRetOn = 0x007E4C69;
DWORD WingProcRetOff = 0x007E4D69;
//0x007E4C5D
Naked(WingsProcentID)
{
	_asm MOV WingProcID, EDX

	bWingSearch = false;

	if(g_bWingsActive)
	{
		for(int i = 0; i < MAX_WINGS_ITEM; i++)
		{
			if(gProtocol.m_Wing[i].ItemType == WingProcID)
			{
				//SetByte((PVOID)(0x007E66CE + 3), gProtocol.m_Wing[i].Damage);
				//SetByte((PVOID)(0x007E66CE + 3), gProtocol.m_Wing[i].Absord);
				//if(WingProcID == 0x1A46)
				g_dwWingsType = WingProcID;
				g_dwWingsDamage = gProtocol.m_Wing[i].Damage;
				g_dwWingsAbsord = gProtocol.m_Wing[i].Absord;
				bWingSearch = true;
				//_asm JMP WingProcRetOn
				//else 
				_asm JMP WingProcRetOff
			}
		}
	}

	//_asm MOV WingProcID, EDX

	if(gItem.IsWings2_5(WingProcID,false)) SetByte((PVOID)(0x007E66CE + 3), 35);
	else if(gItem.IsWings4(WingProcID,false)) SetByte((PVOID)(0x007E66CE + 3), 45);
	else if(gItem.IsWings5(WingProcID,false)) SetByte((PVOID)(0x007E66CE + 3), 50);///Conflict
	else if(gItem.IsWings6(WingProcID,false)) SetByte((PVOID)(0x007E66CE + 3), 55);///Conflict
	else SetByte((PVOID)(0x007E66CE + 3), 39);
	
	if(WingProcID == 0x1A46) _asm JMP WingProcRetOn
	else _asm JMP WingProcRetOff
}

// ----------------------------------------------------------------------------------------------

DWORD dwPetLevel = 0;

void GetPetLevel(DWORD Line, char* Text, char* Text2, int Level)
{
	if(!strcmp(Text2, "Level"))
	{
		dwPetLevel = Level;

		pSetItemTextLine(Line, Text, Text2, Level);
	}
}

void SetWingsPercent(DWORD Line, char* Text, int Percent)
{
	if(!strcmp(Text, "Absorb %d%% additional damage"))
	{
		bool bSearchResult = false;

		if(g_bWingsActive)
		{
			for(int i = 0; i < MAX_WINGS_ITEM; i++)
			{
				if(6660 == gProtocol.m_Wing[i].ItemType)
				{
					bSearchResult = true;
					g_dwWingsAbsord = gProtocol.m_Wing[i].Absord;
					break;
				}
			}
		}
		
		if(bSearchResult == true)
		{
			pSetItemTextLine(Line, "Absorb %d%% additional damage", (dwPetLevel + g_dwWingsAbsord) / 2);
		}
		else
		{
			pSetItemTextLine(Line, "Absorb %d%% additional damage", Percent);
		}
	}
	else if(bWingSearch && !strcmp(Text, "Increases damage by %d%%"))
	{
		pSetItemTextLine(Line, "Increases damage by %d%%", 2 * gItemPrice.ShowItemLevel + g_dwWingsDamage);
	}
	else if(bWingSearch && !strcmp(Text, "Absorb %d%% of damage"))
	{
		pSetItemTextLine(Line, "Absorb %d%% of damage", 2 * gItemPrice.ShowItemLevel + g_dwWingsAbsord);
	}
	else
	{
		pSetItemTextLine(Line, Text, Percent);
	}
}


//DWORD WingProcentReturn = 0x007E6B5F;
//DWORD ProcCall = 0x009CF52A;
//Naked(WingsProcent)
//{
//	_asm MOV EDX,DWORD PTR SS:[EBP+0x24]
//
//	if(gItem.IsWings2_5(WingProcID,false)) _asm LEA EAX,[EDX+EDX+35]
//	else if(gItem.IsWings4(WingProcID,false)) _asm LEA EAX,[EDX+EDX+43]
//	else if(gItem.IsWings5(WingProcID,false)) _asm LEA EAX,[EDX+EDX+46]
//	else _asm LEA EAX,[EDX+EDX+39]
//
//	_asm
//	{
//		PUSH EAX
//		MOV ECX,DWORD PTR SS:[EBP+0x0C]
//		PUSH ECX                             ; Format
//		LEA EDX,[EBP-0x12C]
//		PUSH EDX                             ; Arg1
//		CALL ProcCall
//		ADD ESP,0x0C
//		JMP WingProcentReturn
//	}
//
//	//SetByte((PVOID)(0x007E66CE + 3), 27);
//}

//DWORD ItemMoveID;
//DWORD ItemMoveRetOn = 0x00831996;
//DWORD ItemMoveRetOff = 0;
//Naked(WingsMoveListFix)
//{
//	_asm CMP ECX, 0x1824
//
//	_asm MOV ItemMoveID, ECX
//	if(ItemMoveID == 0x1824 || gItem.IsCustomWings(ItemOptID, false)) _asm ItemMoveRetOn
//	else _asm ItemMoveRetOff
//	//CMP ECX, 0x1824
//}



//#define ItemArray 1171 //IS ITEMARRAY FOR MAIN 1.04d GMO
//#define ItemId(x, y) ((x * 512) + y)
//#define ObjectId(x, y) ((x * 512) + y + ItemArray)
//
////AND THIS FOR .CPP FILE XD:
//void __declspec(naked) WingsOfVortexEffect()
//{
//DWORD dwItem;
//_asm
//{
//MOV EAX, DWORD PTR SS:[EBP+0x0C]
//MOV dwItem, EAX
//// ----
//CMP dwItem,ObjectId(12,37)
//JE Return
//// ----
//CMP dwItem,ObjectId(12,180)
//JE Return
//// ----
//CMP dwItem,ObjectId(12,189)
//JE Return
//// ----
//Return:
//MOV EAX,0x0060C764
//JMP EAX
//}
//}
//
//
//void HookEffects()
//{
////SetNop(0x0060C75D, 5);
//	SetRange((LPVOID)0x0060C75D, 5, ASM::NOP);
////WriteJmp(0x0060C75D, (DWORD)&WingsOfVortexEffect);
//	SetOp((LPVOID)0x0060C75D, WingsOfVortexEffect, ASM::JMP);
//}

//sub_6D8F20(388, &v301, a1 + 264, &v297, 1, a1, -1, 0, 0, 0, 0.0, -1);	//Create Effect


LPVOID  F1_Thisv1;
DWORD   F1_Arg1v1;
DWORD   F1_Arg11v1;
DWORD   F1_Arg2v1;
DWORD   F2_Arg5v1;
DWORD   F3_Arg3v1;
//
LPVOID  F1_Thisv2;
DWORD   F1_Arg1v2;
DWORD   F1_Arg11v2;
DWORD   F1_Arg2v2;
DWORD   F2_Arg5v2;
DWORD   F3_Arg3v2;
//
LPVOID  F1_Thisv3;
DWORD   F1_Arg1v3;
DWORD   F1_Arg11v3;
DWORD   F1_Arg2v3;
DWORD   F2_Arg5v3;
DWORD   F3_Arg3v3;
//
LPVOID  F1_Thisv4;
DWORD   F1_Arg1v4;
DWORD   F1_Arg11v4;
DWORD   F1_Arg2v4;
DWORD   F2_Arg5v4;
DWORD   F3_Arg3v4;
//
LPVOID  F1_Thisv5;
DWORD   F1_Arg1v5;
DWORD   F1_Arg11v5;
DWORD   F1_Arg2v5;
DWORD   F2_Arg5v5;
DWORD   F3_Arg3v5;
//
LPVOID  F1_Thisv6;
DWORD   F1_Arg1v6;
DWORD   F1_Arg11v6;
DWORD   F1_Arg2v6;
DWORD   F2_Arg5v6;
DWORD   F3_Arg3v6;
//
LPVOID  F1_Thisv7;
DWORD   F1_Arg1v7;
DWORD   F1_Arg11v7;
DWORD   F1_Arg2v7;
DWORD   F2_Arg5v7;
DWORD   F3_Arg3v7;
//
LPVOID  F1_Thisv8;
DWORD   F1_Arg1v8;
DWORD   F1_Arg11v8;
DWORD   F1_Arg2v8;
DWORD   F2_Arg5v8;
DWORD   F3_Arg3v8;
//
LPVOID  F1_Thisv9;
DWORD   F1_Arg1v9;
DWORD   F1_Arg11v9;
DWORD   F1_Arg2v9;
DWORD   F2_Arg5v9;
DWORD   F3_Arg3v9;
//
LPVOID  F1_Thisv10;
DWORD   F1_Arg1v10;
DWORD   F1_Arg11v10;
DWORD   F1_Arg2v10;
DWORD   F2_Arg5v10;
DWORD   F3_Arg3v10;
//
LPVOID  F1_Thisv11;
DWORD   F1_Arg1v11;
DWORD   F1_Arg11v11;
DWORD   F1_Arg2v11;
DWORD   F2_Arg5v11;
DWORD   F3_Arg3v11;
//
LPVOID  F1_Thisv12;
DWORD   F1_Arg1v12;
DWORD   F1_Arg11v12;
DWORD   F1_Arg2v12;
DWORD   F2_Arg5v12;
DWORD   F3_Arg3v12;
//
LPVOID  F1_Thisv13;
DWORD   F1_Arg1v13;
DWORD   F1_Arg11v13;
DWORD   F1_Arg2v13;
DWORD   F2_Arg5v13;
DWORD   F3_Arg3v13;
//
LPVOID  F1_Thisv14;
DWORD   F1_Arg1v14;
DWORD   F1_Arg11v14;
DWORD   F1_Arg2v14;
DWORD   F2_Arg5v14;
DWORD   F3_Arg3v14;
//
LPVOID  F1_Thisv15;
DWORD   F1_Arg1v15;
DWORD   F1_Arg11v15;
DWORD   F1_Arg2v15;
DWORD   F2_Arg5v15;
DWORD   F3_Arg3v15;
//
LPVOID  F1_Thisv16;
DWORD   F1_Arg1v16;
DWORD   F1_Arg11v16;
DWORD   F1_Arg2v16;
DWORD   F2_Arg5v16;
DWORD   F3_Arg3v16;
//
LPVOID  F1_Thisv17;
DWORD   F1_Arg1v17;
DWORD   F1_Arg11v17;
DWORD   F1_Arg2v17;
DWORD   F2_Arg5v17;
DWORD   F3_Arg3v17;
//
LPVOID  F1_Thisv18;
DWORD   F1_Arg1v18;
DWORD   F1_Arg11v18;
DWORD   F1_Arg2v18;
DWORD   F2_Arg5v18;
DWORD   F3_Arg3v18;
//
LPVOID  F1_Thisv19;
DWORD   F1_Arg1v19;
DWORD   F1_Arg11v19;
DWORD   F1_Arg2v19;
DWORD   F2_Arg5v19;
DWORD   F3_Arg3v19;
//
LPVOID  F1_Thisv20;
DWORD   F1_Arg1v20;
DWORD   F1_Arg11v20;
DWORD   F1_Arg2v20;
DWORD   F2_Arg5v20;
DWORD   F3_Arg3v20;
//
LPVOID  F1_Thisv21;
DWORD   F1_Arg1v21;
DWORD   F1_Arg11v21;
DWORD   F1_Arg2v21;
DWORD   F2_Arg5v21;
DWORD   F3_Arg3v21;
//
LPVOID  F1_Thisv22;
DWORD   F1_Arg1v22;
DWORD   F1_Arg11v22;
DWORD   F1_Arg2v22;
DWORD   F2_Arg5v22;
DWORD   F3_Arg3v22;
//
LPVOID  F1_Thisv23;
DWORD   F1_Arg1v23;
DWORD   F1_Arg11v23;
DWORD   F1_Arg2v23;
DWORD   F2_Arg5v23;
DWORD   F3_Arg3v23;
//
LPVOID  F1_Thisv24;
DWORD   F1_Arg1v24;
DWORD   F1_Arg11v24;
DWORD   F1_Arg2v24;
DWORD   F2_Arg5v24;
DWORD   F3_Arg3v24;
// ----------------------------------------------------------------------------------------------
 
Naked(AddWingsEffect)
{
        _asm
        {
                mov AddWingsEffect_Buff, edx
                mov edx, dword ptr ss:[ebp-0x68]
                mov F1_Thisv1, edx
                mov F1_Thisv2, edx
                mov F1_Thisv3, edx
                mov F1_Thisv4, edx
                mov F1_Thisv5, edx
                mov F1_Thisv6, edx
                mov F1_Thisv7, edx
                mov F1_Thisv8, edx
                mov F1_Thisv9, edx
                mov F1_Thisv10, edx
                mov F1_Thisv11, edx
                mov F1_Thisv12, edx
                mov F1_Thisv13, edx
                mov F1_Thisv14, edx
                mov F1_Thisv15, edx
                mov F1_Thisv16, edx
                mov F1_Thisv17, edx
                mov F1_Thisv18, edx
                mov F1_Thisv19, edx
                mov F1_Thisv20, edx
                mov F1_Thisv21, edx
                mov F1_Thisv22, edx
                mov F1_Thisv23, edx
                mov F1_Thisv24, edx
                lea edx, [ebp-0x58]
                mov F1_Arg1v1, edx
                mov F1_Arg1v2, edx
                mov F1_Arg1v3, edx
                mov F1_Arg1v4, edx
                mov F1_Arg1v5, edx
                mov F1_Arg1v6, edx
                mov F1_Arg1v7, edx
                mov F1_Arg1v8, edx
                mov F1_Arg1v9, edx
                mov F1_Arg1v10, edx
                mov F1_Arg1v11, edx
                mov F1_Arg1v12, edx
                mov F1_Arg1v13, edx
                mov F1_Arg1v14, edx
                mov F1_Arg1v15, edx
                mov F1_Arg1v16, edx
                mov F1_Arg1v17, edx
                mov F1_Arg1v18, edx
                mov F1_Arg1v19, edx
                mov F1_Arg1v20, edx
                mov F1_Arg1v21, edx
                mov F1_Arg1v22, edx
                mov F1_Arg1v23, edx
                mov F1_Arg1v24, edx
                lea edx, [ebp-0x18]
                mov F1_Arg11v1, edx
                mov F1_Arg11v2, edx
                mov F1_Arg11v3, edx
                mov F1_Arg11v4, edx
                mov F1_Arg11v5, edx
                mov F1_Arg11v6, edx
                mov F1_Arg11v7, edx
                mov F1_Arg11v8, edx
                mov F1_Arg11v9, edx
                mov F1_Arg11v10, edx
                mov F1_Arg11v11, edx
                mov F1_Arg11v12, edx
                mov F1_Arg11v13, edx
                mov F1_Arg11v14, edx
                mov F1_Arg11v15, edx
                mov F1_Arg11v16, edx
                mov F1_Arg11v17, edx
                mov F1_Arg11v18, edx
                mov F1_Arg11v19, edx
                mov F1_Arg11v20, edx
                mov F1_Arg11v21, edx
                mov F1_Arg11v22, edx
                mov F1_Arg11v23, edx
                mov F1_Arg11v24, edx
                mov edx, dword ptr ss:[ebp-0x6c]
                mov F1_Arg2v1, edx
                mov F1_Arg2v2, edx
                mov F1_Arg2v3, edx
                mov F1_Arg2v4, edx
                mov F1_Arg2v5, edx
                mov F1_Arg2v6, edx
                mov F1_Arg2v7, edx
                mov F1_Arg2v8, edx
                mov F1_Arg2v9, edx
                mov F1_Arg2v10, edx
                mov F1_Arg2v11, edx
                mov F1_Arg2v12, edx
                mov F1_Arg2v13, edx
                mov F1_Arg2v14, edx
                mov F1_Arg2v15, edx
                mov F1_Arg2v16, edx
                mov F1_Arg2v17, edx
                mov F1_Arg2v18, edx
                mov F1_Arg2v19, edx
                mov F1_Arg2v20, edx
                mov F1_Arg2v21, edx
                mov F1_Arg2v22, edx
                mov F1_Arg2v23, edx
                mov F1_Arg2v24, edx
                fldz
                fstp dword ptr ss:[esp]
                mov edx, dword ptr ss:[ebp-0x70]
                mov F2_Arg5v1, edx
                mov F2_Arg5v2, edx
                mov F2_Arg5v3, edx
                mov F2_Arg5v4, edx
                mov F2_Arg5v5, edx
                mov F2_Arg5v6, edx
                mov F2_Arg5v7, edx
                mov F2_Arg5v8, edx
                mov F2_Arg5v9, edx
                mov F2_Arg5v10, edx
                mov F2_Arg5v11, edx
                mov F2_Arg5v12, edx
                mov F2_Arg5v13, edx
                mov F2_Arg5v14, edx
                mov F2_Arg5v15, edx
                mov F2_Arg5v16, edx
                mov F2_Arg5v17, edx
                mov F2_Arg5v18, edx
                mov F2_Arg5v19, edx
                mov F2_Arg5v20, edx
                mov F2_Arg5v21, edx
                mov F2_Arg5v22, edx
                mov F2_Arg5v23, edx
                mov F2_Arg5v24, edx
                mov edx, AddWingsEffect_Buff
    } 
     

    if (gItem.IsCustomWings(AddWingsEffect_Buff, true)) 
    { 
         
     	if( AddWingsEffect_Buff == ITEM2(12, 195) )
		{
						Color[0] = 1.0;
                        Color[1] = 0.75;
                        Color[2] = 0.62;
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 61, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v1, 0.5, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 42, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v2, 0.5, Color, F2_Arg5v2, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 60, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v3, 1.0, Color, F2_Arg5v3, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 41, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v4, 1.0, Color, F2_Arg5v4, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 63, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v5, 1.0, Color, F2_Arg5v5, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 44, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v6, 1.0, Color, F2_Arg5v6, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 42, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v7, 1.0, Color, F2_Arg5v7, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 59, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v8, 1.4, Color, F2_Arg5v8, 1.0, 0);
                        //// --
                        pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 40, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v8, 1.4, Color, F2_Arg5v8, 1.0, 0);
                        ////// ----
                        Color[0] = 0.3;
                        Color[1] = 0.3;
                        Color[2] = 1.0;
                        // --
                        pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 62, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v11, 2.6, Color, F2_Arg5v11, 1.0, 0);
                        //// --
                        pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 43, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v11, 2.6, Color, F2_Arg5v11, 1.0, 0);
                        //// ----
                        Color[0] = 0.6;
                        Color[1] = 0.45;
                        Color[2] = 1.0;
                        // --
                        pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 65, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v12, 1.4, Color, F2_Arg5v12, 1.0, 0);
                        //// --
                        pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 46, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v13, 1.4, Color, F2_Arg5v13, 1.0, 0);
                        // ----
                        Color[0] = 0.3;
                        Color[1] = 0.3;
                        Color[2] = 1.0;
                        //// --
                        pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 58, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v14, 2.0, Color, F2_Arg5v14, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 39, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v14, 2.0, Color, F2_Arg5v14, 1.0, 0);
                        ////// ----
                        Color[0] = 0.6;
                        Color[1] = 0.45;
                        Color[2] = 1.0;
                        // --
                        pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 64, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v16, 2.0, Color, F2_Arg5v16, 1.0, 0);
                        //// --
                        pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 32, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v17, 2.0, Color, F2_Arg5v17, 1.0, 0);
                        //// ----
                        Color[0] = 0.34;
                        Color[1] = 0.25;
                        Color[2] = 1.0;
                        // --
                    pAllowStaticEffect(F1_Thisv19, &F1_Arg11v19, F1_Arg2v19, 13, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v19, 2.0, Color, F2_Arg5v19, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv19, &F1_Arg11v19, F1_Arg2v19, 15, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v19, 2.0, Color, F2_Arg5v19, 1.0, 0);
                        //// --
                        pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 25, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v20, 2.0, Color, F2_Arg5v20, 1.0, 0);
                        //// --
                    pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 27, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v20, 2.0, Color, F2_Arg5v20, 1.0, 0);
                        //// --
                        pAllowStaticEffect(F1_Thisv22, &F1_Arg11v22, F1_Arg2v22, 3, 0);
                        pPlayStaticEffect(32002, &F1_Arg11v22, 0.5, Color, F2_Arg5v22, 1.0, 0);
 
			
			//Color[0] = 1.0;
			//Color[1] = 0.75;
			//Color[2] = 0.62;
			//// --
			//pAllowStaticEffect(F1_This, &F1_Arg11, F1_Arg2, 61, 0);
			//pPlayStaticEffect(32002, &F1_Arg11, 0.5, Color, F2_Arg5, 1.0, 0);
			//// --
			//pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 42, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v2, 0.5, Color, F2_Arg5v2, 1.0, 0);
			//// --
			//pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 60, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v3, 1.0, Color, F2_Arg5v3, 1.0, 0);
			//// --
			//pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 41, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v11, 1.0, Color, F2_Arg5v11, 1.0, 0);
			//// --
			//pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 63, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v17, 1.0, Color, F2_Arg5v17, 1.0, 0);
			////// --
			//pAllowStaticEffect(F1_Thisv19, &F1_Arg11v19, F1_Arg2v19, 44, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v19, 1.0, Color, F2_Arg5v19, 1.0, 0);
			////// --
			//pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 42, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v7, 1.0, Color, F2_Arg5v7, 1.0, 0);
			////// --

			////pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 40, 0);
			////pPlayStaticEffect(32002, &F1_Arg11v9, 1.4, Color, F2_Arg5v9, 1.0, 0);

			////pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 59, 0);
			////pPlayStaticEffect(32002, &F1_Arg11v12, 1.4, Color, F2_Arg5v12, 1.0, 0);
			//// --
		

			//// ----
			//Color[0] = 0.3;
			//Color[1] = 0.3;
			//Color[2] = 1.0;
			//// --
			//pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 62, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v10, 2.6, Color, F2_Arg5v10, 1.0, 0);
			////// --
			////pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 43, 0);
			////pPlayStaticEffect(32002, &F1_Arg11v11, 2.6, Color, F2_Arg5v11, 1.0, 0);
			//// ----
			//Color[0] = 0.6;
			//Color[1] = 0.45;
			//Color[2] = 1.0;
			//// --
			//pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 65, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v12, 1.4, Color, F2_Arg5v12, 1.0, 0);
			////// --
			//pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 46, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v13, 1.4, Color, F2_Arg5v13, 1.0, 0);
			//// ----
			//Color[0] = 0.3;
			//Color[1] = 0.3;
			//Color[2] = 1.0;
			//// --
			//pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 58, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v14, 2.0, Color, F2_Arg5v14, 1.0, 0);
			////// --
			//pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 39, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v15, 2.0, Color, F2_Arg5v15, 1.0, 0);
			////// ----
			//Color[0] = 0.6;
			//Color[1] = 0.45;
			//Color[2] = 1.0;
			////// --
			//pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 64, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v16, 2.0, Color, F2_Arg5v16, 1.0, 0);
			////// --
			////pAllowStaticEffect(F1_Thisv18, &F1_Arg11v18, F1_Arg2v18, 32, 0);
			////pPlayStaticEffect(32002, &F1_Arg11v18, 2.0, Color, F2_Arg5v18, 1.0, 0);
			////// ----
			//Color[0] = 0.34;
			//Color[1] = 0.25;
			//Color[2] = 1.0;
			//// --
			//pAllowStaticEffect(F1_Thisv24, &F1_Arg11v24, F1_Arg2v24, 13, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v24, 2.0, Color, F2_Arg5v24, 1.0, 0);
			//////// --
			//pAllowStaticEffect(F1_Thisv23, &F1_Arg11v23, F1_Arg2v23, 15, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v23, 2.0, Color, F2_Arg5v23, 1.0, 0);
			////// --
			//pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 25, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v20, 2.0, Color, F2_Arg5v20, 1.0, 0);
			////// --
			//F1_Thisv21 = F1_Thisv20;
			//pAllowStaticEffect(F1_Thisv21, &F1_Arg11v21, F1_Arg2v21, 27, 0);
			//pAllowStaticEffect(F1_Thisv21, &F1_Arg11v21, F1_Arg2v21, 27, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v21, 2.0, Color, F2_Arg5v21, 1.0, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v21, 2.0, Color, F2_Arg5v21, 1.0, 0);
			////// --
			//pAllowStaticEffect(F1_Thisv22, &F1_Arg11v22, F1_Arg2v22, 3, 0);
			//pPlayStaticEffect(32002, &F1_Arg11v22, 0.5, Color, F2_Arg5v22, 1.0, 0);

	
		}
		else if( AddWingsEffect_Buff == ITEM2(12, 196) )
		{

			/*Color[0] = 1.0;
                        Color[1] = 0.6;
                        Color[2] = 0.0;
                        // ----
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 47, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.6, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 24, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.6, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 31, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.6, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 40, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.6, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 8, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.6, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 17, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.6, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 46, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.6, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 23, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.6, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        Color[0] = 1.0;
                        Color[1] = 0.4;
                        Color[2] = 0.0;
                        // --
                       pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 35, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);
                        // --
                       pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 39, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);
                        //// --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 44, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 45, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);
                        //// --



                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 12, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 16, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);
                        // --
                      pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 21, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 22, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 61, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);
                        // --
                       pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 60, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 59, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 62, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);
                        // --
                       pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 55, 0);
                       pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);
                        //// --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 52, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 53, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 54, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.8, Color, F2_Arg5v1, 1.0, 0);

*/
		
						Color[0] = 1.0;
                        Color[1] = 0.6;
                        Color[2] = 0.0;
                        // ----
                        pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 47, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.6, Color, F2_Arg5v1, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 24, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v2, 0.6, Color, F2_Arg5v2, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 31, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v3, 0.6, Color, F2_Arg5v3, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 40, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v4, 0.6, Color, F2_Arg5v4, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 8, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v5, 0.6, Color, F2_Arg5v5, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 17, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v6, 0.6, Color, F2_Arg5v6, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 46, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v7, 0.6, Color, F2_Arg5v7, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 23, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v8, 0.6, Color, F2_Arg5v8, 1.0, 0);
                        // --
                        Color[0] = 1.0;
                        Color[1] = 0.4;
                        Color[2] = 0.0;
                        // --
                       pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 35, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v11, 0.8, Color, F2_Arg5v11, 1.0, 0);
                        // --
                       pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 39, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v12, 0.8, Color, F2_Arg5v12, 1.0, 0);
                        //// --
                        pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 44, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v11, 0.8, Color, F2_Arg5v11, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 45, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v12, 0.8, Color, F2_Arg5v12, 1.0, 0);
                        //// --



                        pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 12, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v13, 0.8, Color, F2_Arg5v13, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 16, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v14, 0.8, Color, F2_Arg5v14, 1.0, 0);
                        // --
                      pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 21, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v16, 0.8, Color, F2_Arg5v16, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 22, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v16, 0.8, Color, F2_Arg5v16, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 61, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v17, 0.8, Color, F2_Arg5v17, 1.0, 0);
                        // --
                       pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 60, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v17, 0.8, Color, F2_Arg5v17, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv19, &F1_Arg11v19, F1_Arg2v19, 59, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v19, 0.8, Color, F2_Arg5v19, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 62, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v20, 0.8, Color, F2_Arg5v20, 1.0, 0);
                        // --
                       pAllowStaticEffect(F1_Thisv22, &F1_Arg11v22, F1_Arg2v22, 55, 0);
                       pPlayStaticEffect(0x7D83, &F1_Arg11v22, 0.8, Color, F2_Arg5v22, 1.0, 0);
                        //// --
                        pAllowStaticEffect(F1_Thisv22, &F1_Arg11v22, F1_Arg2v22, 52, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v22, 0.8, Color, F2_Arg5v22, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv23, &F1_Arg11v23, F1_Arg2v23, 53, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v23, 0.8, Color, F2_Arg5v23, 1.0, 0);
                        // --
                        pAllowStaticEffect(F1_Thisv24, &F1_Arg11v24, F1_Arg2v24, 54, 0);
                        pPlayStaticEffect(0x7D83, &F1_Arg11v24, 0.8, Color, F2_Arg5v24, 1.0, 0);



                        // --
            //                    Color[0] = 0.9;
            //                    Color[1] = 0.2;
            //                    Color[2] = 0.1;
            //// ----
            //         /*           pAllowStaticEffect (F1_This, & F1_Arg11, F1_Arg2, 4, 0);
            //                    pPlayStaticEffect (0x7D03, & F1_Arg11, 2, Color, F2_Arg5, 2.0, 0);*/
            //// -
            //                 pAllowStaticEffect (F1_Thisv2, & F1_Arg11v2, F1_Arg2v2, 42, 0);
            //                  pPlayStaticEffect (0x7D03, & F1_Arg11v2, 2, Color, F2_Arg5v2, 2.0, 0);
            ////// -
            //                    pAllowStaticEffect (F1_Thisv3, & F1_Arg11v3, F1_Arg2v3, 27, 0);
            //                    pPlayStaticEffect (0x7D03, & F1_Arg11v3, 2, Color, F2_Arg5v3, 2.0, 0);
            //// -
            //                    pAllowStaticEffect (F1_Thisv4, & F1_Arg11v4, F1_Arg2v4, 21, 0);
            //                    pPlayStaticEffect (0x7D03, & F1_Arg11v4, 2, Color, F2_Arg5v4, 2.0, 0);
            //// -
            //                    pAllowStaticEffect (F1_Thisv5, & F1_Arg11v5, F1_Arg2v5, 53, 0);
            //                    pPlayStaticEffect (0x7D03, & F1_Arg11v5, 2, Color, F2_Arg5v5, 2.0, 0);
            //// -
            //              pAllowStaticEffect (F1_Thisv6, & F1_Arg11v6, F1_Arg2v6, 59, 0);
            //                  pPlayStaticEffect (0x7D03, & F1_Arg11v6, 2, Color, F2_Arg5v6, 2.0, 0);
            ////// -
            //                    pAllowStaticEffect (F1_Thisv7, & F1_Arg11v7, F1_Arg2v7, 5, 0);
            //                   pPlayStaticEffect (0x7D03, & F1_Arg11v7, 2, Color, F2_Arg5v7, 2.0, 0);
            ////// -
            //             //      pAllowStaticEffect (F1_Thisv8, & F1_Arg11v8, F1_Arg2v8, 28, 0);
            //               //    pPlayStaticEffect (0x7D03, & F1_Arg11v8, 2, Color, F2_Arg5v8, 2.0, 0);
            ////// -
            ////                    pAllowStaticEffect (F1_Thisv9, & F1_Arg11v9, F1_Arg2v9, 10, 0);
            ////                    pPlayStaticEffect (0x7D03, & F1_Arg11v9, 2, Color, F2_Arg5v9, 2.0, 0);
            ////// -
            ////                    pAllowStaticEffect (F1_Thisv10, & F1_Arg11v10, F1_Arg2v10, 33, 0);
            ////                    pPlayStaticEffect (0x7D03, & F1_Arg11v10, 2, Color, F2_Arg5v10, 2.0, 0);
			
               }

	

                       
		/*else if( AddWingsEffect_Buff == ITEM2(12, 186) )
		{
			Color[0] = 0.9;
			Color[1] = 0.0;
			Color[2] = 0.2;
		}
		else if( AddWingsEffect_Buff == ITEM2(12, 186) )
		{
			Color[0] = 0.9;
			Color[1] = 0.0;
			Color[2] = 0.2;
		}
		else if( AddWingsEffect_Buff == ITEM2(12, 186) )
		{
			Color[0] = 0.9;
			Color[1] = 0.0;
			Color[2] = 0.2;
		}
		else if( AddWingsEffect_Buff == ITEM2(12, 186) )
		{
			Color[0] = 0.9;
			Color[1] = 0.0;
			Color[2] = 0.2;
		}
		else if( AddWingsEffect_Buff == ITEM2(12, 186) )
		{
			Color[0] = 0.9;
			Color[1] = 0.0;
			Color[2] = 0.2;
		}*/
		// ----
		//pAllowStaticEffect(F1_This, &F1_Arg11, F1_Arg2, 1, 0);
		//pPlayStaticEffect(0x7D02, &F1_Arg11, 8.0, Color, F2_Arg5, 0.0, 0);
       
         
        _asm 
        { 
            mov AddWingsEffect_Buff, 0x0056CA63 
            jmp AddWingsEffect_Buff 
        } 
    }     
        // ---- 
    if( AddWingsEffect_Buff > 0x0A9D ) 
    { 
        _asm 
        { 
            mov AddWingsEffect_Buff, 0x005667BB 
            jmp AddWingsEffect_Buff 
        } 
    } 
    // ---- 
    _asm 
    { 
        mov AddWingsEffect_Buff, 0x00566707 
        jmp AddWingsEffect_Buff 
    } 
}  

//#endif

#if(RF_NEW_GLOV)

#define oBattleGloveGlow_Hook		0x005F91C2

#define sub_50D810_Addr		((int(__thiscall*)(int a1, int a2, int a3, int a4)) 0x50D810)
#define sub_512D50_Addr		((void*(__thiscall*)(void* a1)) 0x512D50)
#define sub_513C60_Addr		((char*(__thiscall*)(char *This, void *a2, int a3)) 0x513C60)
#define sub_5135F0_Addr		((char*(__thiscall*)(DWORD *This, int a2, int a3)) 0x5135F0)
#define sub_512D60_Addr		((void(*)()) 0x512D60)

void GlovesAssoc(char *This)
{
	sub_50D810_Addr((int)(This + 92), ITEM2(0, 53), GLOV2, GLOV1);
	void* v2 = sub_512D50_Addr(This + 92);
	char* v3 = sub_513C60_Addr(This, v2, (int)(This + 92));
	sub_5135F0_Addr((DWORD *)This + 15, (int)This, (int)v3);
	sub_512D60_Addr();

	sub_50D810_Addr((int)(This + 92), ITEM2(0, 54), GLOV4, GLOV3);
	v2 = sub_512D50_Addr(This + 92);
	v3 = sub_513C60_Addr(This, v2, (int)(This + 92));
	sub_5135F0_Addr((DWORD *)This + 15, (int)This, (int)v3);
	sub_512D60_Addr();
}

void __declspec (naked) BattleGloveGlow() 
{
    static DWORD dwBattleGlovesGlow_Pointer;
    static DWORD dwBattleGlovesGlow_Buffer;
    static DWORD dwBattleGlovesNewGlow_Buffer;
    static DWORD dwBattleGlovesGlow_Jump = 0x005F94E8;

    static BOOL bBattleGlovesGlow_Switcher = FALSE;

    _asm 
	{
        MOV dwBattleGlovesGlow_Pointer, EAX
    }

    if ( dwBattleGlovesGlow_Pointer == ITEM2 ( 0, 35 ) ) 
	{
        bBattleGlovesGlow_Switcher = TRUE;
    }

    else if ( dwBattleGlovesGlow_Pointer == ITEM2 ( 0, 53 ) || dwBattleGlovesGlow_Pointer == ITEM2 ( 0, 54 )) 
	{
        bBattleGlovesGlow_Switcher = FALSE;

        _asm 
		{
            MOV DWORD PTR SS:[EBP-0x4], 0x2C
            JMP dwBattleGlovesGlow_Jump
        }
    }

    if ( bBattleGlovesGlow_Switcher == TRUE ) 
	{
        _asm 
		{
            MOV dwBattleGlovesGlow_Buffer, 0x005F91C9
            JMP dwBattleGlovesGlow_Buffer
        }
    }
    else 
	{
        _asm 
		{
            MOV dwBattleGlovesGlow_Buffer, 0x005F91D5
            JMP dwBattleGlovesGlow_Buffer
        }
    }
}

__declspec(naked) void RFItemAddInventoryPos()
{
	static DWORD IsRFItem = 0;
    static DWORD RFPosition = 0x005CD084;
    static DWORD NextRFPosition = 0x005CD086;

    _asm 
	{
        mov ecx, dword ptr ss : [ebp + 0x8]
        mov dword ptr ss : [ebp + 0x8], ecx
        mov IsRFItem, ecx
    }

    if ( IsRFItem == 0x04B3 ) 
	{
        _asm {jmp RFPosition}
    }
    //else if ( IsRFItem == ITEM2 ( 0, 114 ) )
	else if ( IsRFItem == ITEM2 ( 0, 53 ) || IsRFItem == ITEM2 ( 0, 54 )) 
	{
        _asm {jmp RFPosition}
    }
    else 
	{
        _asm {jmp NextRFPosition}
    }
}

#endif

void InitItemAsm()
{
#if(RF_NEW_GLOV)

	SetRange ((LPVOID)0x005CD07D, 7, ASM::NOP );
	SetOp((LPVOID)0x005CD07D, &RFItemAddInventoryPos, ASM::JMP);

	SetOp((LPVOID)(0x50D840+0xC5), &GlovesAssoc, ASM::CALL);

    SetRange ((LPVOID)oBattleGloveGlow_Hook, 7, ASM::NOP );
	SetOp((LPVOID)oBattleGloveGlow_Hook, &BattleGloveGlow, ASM::JMP);

#endif
	//HookEffects();
#ifdef ADD_NEW_EFFECT_WINGS
	SetRange((LPVOID)0x005666F7, 10, ASM::NOP);
	SetOp((LPVOID)0x005666F7, AddWingsEffect, ASM::JMP);
#endif

	SetRange((LPVOID)0x005F3F91, 13, ASM::NOP);
	SetOp((LPVOID)0x005F3F91, DropTitleColor, ASM::JMP);
	// ----
	SetRange((LPVOID)0x00609FF2, 6, ASM::NOP);
	SetOp((LPVOID)0x00609FF2, AddShineGlow, ASM::JMP);
	// ----
	SetRange((LPVOID)0x007DBD45, 7, ASM::NOP);
	SetOp((LPVOID)0x007DBD45, ReToJewelVisualFlag, ASM::JMP);
	// ----
	SetRange((LPVOID)0x00838263, 8, ASM::NOP);
	SetOp((LPVOID)0x00838263, AllowJewelsInsert, ASM::JMP);

	SetRange((LPVOID)0x00838358, 9, ASM::NOP);
	SetOp((LPVOID)0x00838358, FixWingsJewelsInsert, ASM::JMP);

	//Wings
	if(CUSTOM_WINGSEFFECT == 0)
	{
		SetRange((LPVOID)0x005666F7, 10, ASM::NOP);
		SetOp((LPVOID)0x005666F7, AddWingsEffect, ASM::JMP);
	}


	SetRange((LPVOID)0x0060EE88, 7, ASM::NOP);
	SetOp((LPVOID)0x0060EE88, FixWingsExcellentGlow, ASM::JMP);

	SetRange((LPVOID)0x0060A04F, 28, ASM::NOP);
	SetOp((LPVOID)0x0060A04F, FixWingsLevelGlow, ASM::JMP);

	SetRange((LPVOID)0x00876E48, 8, ASM::NOP);
	SetOp((LPVOID)0x00876E48, WingsFixMoveKanturu, ASM::JMP);

	// ----

	SetRange((LPVOID)0x0058CF5D, 6, ASM::NOP);
	SetOp((LPVOID)0x0058CF5D, WingsLuck, ASM::JMP);

	SetRange((LPVOID)0x0058D40A, 6, ASM::NOP);
	SetOp((LPVOID)0x0058D40A, WingsOptions, ASM::JMP);
#ifdef NEWWINGS6
	SetByte((PVOID)(0x0058CCE1 + 2), 0xFF);	//Wings Exellent Options	//0xC4
#else
	SetByte((PVOID)(0x0058CCE1 + 2), 0xC2);	//Wings Exellent Options
#endif

	SetRange((LPVOID)0x007E4C5D, 6, ASM::NOP);
	SetOp((LPVOID)0x007E4C5D, WingsProcentID, ASM::JMP);

	//SetRange((LPVOID)0x007E66CE, 5, ASM::NOP);
	//SetOp((LPVOID)0x007E66CB, WingsProcent, ASM::JMP);	
#ifdef NEWWINGS6
	SetByte((PVOID)(0x0083192F + 1), 0xFF);	//Wings Move List Fix	0xCF
#else
	SetByte((PVOID)(0x0083192F + 1), 0xC2);	//Wings Move List Fix
#endif

	SetOp((LPVOID)0x007E66DE, SetWingsPercent, ASM::CALL);
	SetOp((LPVOID)0x007E66BE, SetWingsPercent, ASM::CALL);
	SetOp((LPVOID)0x007E66FE, SetWingsPercent, ASM::CALL);
	SetOp((LPVOID)0x007E671E, SetWingsPercent, ASM::CALL);
	SetOp((LPVOID)0x007E673E, SetWingsPercent, ASM::CALL);
	SetOp((LPVOID)0x007E675E, SetWingsPercent, ASM::CALL);
	SetOp((LPVOID)0x007E677E, SetWingsPercent, ASM::CALL);
		
	SetOp((LPVOID)0x007E679D, SetWingsPercent, ASM::CALL);
	
	SetOp((LPVOID)0x004FA662, SetWingsPercent, ASM::CALL);

	SetOp((LPVOID)0x004FA1F6, GetPetLevel, ASM::CALL);
		
	//SetOp((LPVOID)iRFGlovesAddInventoryPos, WingsProcentID, ASM::JMP);
		
	//SetOp((LPVOID)0x007E4CCD, SetWingsPercent, ASM::CALL);
	//SetOp((LPVOID)0x007E4D17, SetWingsPercent, ASM::CALL);



}



//0058CF5D -> проверка на лайф
//JMP SHORT 0058CF88 - No Item
//0058CF65 -> Yes Item

/*
zahvat id krilev : 007E4C5D
vivod procentov: 007E66CE
*/


//007E66CE

/*
Wings Move List Fix
CPU Disasm
Address   Hex dump              Command                              Comments
00831921  |.  81F9 24180000     CMP ECX,1824
00831927  |.  7C 0D             JL SHORT 00831936
00831929  |.  8B55 D8           MOV EDX,DWORD PTR SS:[LOCAL.10]
*/



/*
LPVOID  F1_Thisv1;
DWORD   F1_Arg1v1;
DWORD   F1_Arg11v1;
DWORD   F1_Arg2v1;
DWORD   F2_Arg5v1;
DWORD   F3_Arg3v1;
//
LPVOID  F1_Thisv2;
DWORD   F1_Arg1v2;
DWORD   F1_Arg11v2;
DWORD   F1_Arg2v2;
DWORD   F2_Arg5v2;
DWORD   F3_Arg3v2;
//
LPVOID  F1_Thisv3;
DWORD   F1_Arg1v3;
DWORD   F1_Arg11v3;
DWORD   F1_Arg2v3;
DWORD   F2_Arg5v3;
DWORD   F3_Arg3v3;
//
LPVOID  F1_Thisv4;
DWORD   F1_Arg1v4;
DWORD   F1_Arg11v4;
DWORD   F1_Arg2v4;
DWORD   F2_Arg5v4;
DWORD   F3_Arg3v4;
//
LPVOID  F1_Thisv5;
DWORD   F1_Arg1v5;
DWORD   F1_Arg11v5;
DWORD   F1_Arg2v5;
DWORD   F2_Arg5v5;
DWORD   F3_Arg3v5;
//
LPVOID  F1_Thisv6;
DWORD   F1_Arg1v6;
DWORD   F1_Arg11v6;
DWORD   F1_Arg2v6;
DWORD   F2_Arg5v6;
DWORD   F3_Arg3v6;
//
LPVOID  F1_Thisv7;
DWORD   F1_Arg1v7;
DWORD   F1_Arg11v7;
DWORD   F1_Arg2v7;
DWORD   F2_Arg5v7;
DWORD   F3_Arg3v7;
//
LPVOID  F1_Thisv8;
DWORD   F1_Arg1v8;
DWORD   F1_Arg11v8;
DWORD   F1_Arg2v8;
DWORD   F2_Arg5v8;
DWORD   F3_Arg3v8;
//
LPVOID  F1_Thisv9;
DWORD   F1_Arg1v9;
DWORD   F1_Arg11v9;
DWORD   F1_Arg2v9;
DWORD   F2_Arg5v9;
DWORD   F3_Arg3v9;
//
LPVOID  F1_Thisv10;
DWORD   F1_Arg1v10;
DWORD   F1_Arg11v10;
DWORD   F1_Arg2v10;
DWORD   F2_Arg5v10;
DWORD   F3_Arg3v10;
//
LPVOID  F1_Thisv11;
DWORD   F1_Arg1v11;
DWORD   F1_Arg11v11;
DWORD   F1_Arg2v11;
DWORD   F2_Arg5v11;
DWORD   F3_Arg3v11;
//
LPVOID  F1_Thisv12;
DWORD   F1_Arg1v12;
DWORD   F1_Arg11v12;
DWORD   F1_Arg2v12;
DWORD   F2_Arg5v12;
DWORD   F3_Arg3v12;
//
LPVOID  F1_Thisv13;
DWORD   F1_Arg1v13;
DWORD   F1_Arg11v13;
DWORD   F1_Arg2v13;
DWORD   F2_Arg5v13;
DWORD   F3_Arg3v13;
//
LPVOID  F1_Thisv14;
DWORD   F1_Arg1v14;
DWORD   F1_Arg11v14;
DWORD   F1_Arg2v14;
DWORD   F2_Arg5v14;
DWORD   F3_Arg3v14;
//
LPVOID  F1_Thisv15;
DWORD   F1_Arg1v15;
DWORD   F1_Arg11v15;
DWORD   F1_Arg2v15;
DWORD   F2_Arg5v15;
DWORD   F3_Arg3v15;
//
LPVOID  F1_Thisv16;
DWORD   F1_Arg1v16;
DWORD   F1_Arg11v16;
DWORD   F1_Arg2v16;
DWORD   F2_Arg5v16;
DWORD   F3_Arg3v16;
//
LPVOID  F1_Thisv17;
DWORD   F1_Arg1v17;
DWORD   F1_Arg11v17;
DWORD   F1_Arg2v17;
DWORD   F2_Arg5v17;
DWORD   F3_Arg3v17;
//
LPVOID  F1_Thisv18;
DWORD   F1_Arg1v18;
DWORD   F1_Arg11v18;
DWORD   F1_Arg2v18;
DWORD   F2_Arg5v18;
DWORD   F3_Arg3v18;
//
LPVOID  F1_Thisv19;
DWORD   F1_Arg1v19;
DWORD   F1_Arg11v19;
DWORD   F1_Arg2v19;
DWORD   F2_Arg5v19;
DWORD   F3_Arg3v19;
//
LPVOID  F1_Thisv20;
DWORD   F1_Arg1v20;
DWORD   F1_Arg11v20;
DWORD   F1_Arg2v20;
DWORD   F2_Arg5v20;
DWORD   F3_Arg3v20;
//
LPVOID  F1_Thisv21;
DWORD   F1_Arg1v21;
DWORD   F1_Arg11v21;
DWORD   F1_Arg2v21;
DWORD   F2_Arg5v21;
DWORD   F3_Arg3v21;
//
LPVOID  F1_Thisv22;
DWORD   F1_Arg1v22;
DWORD   F1_Arg11v22;
DWORD   F1_Arg2v22;
DWORD   F2_Arg5v22;
DWORD   F3_Arg3v22;
//
LPVOID  F1_Thisv23;
DWORD   F1_Arg1v23;
DWORD   F1_Arg11v23;
DWORD   F1_Arg2v23;
DWORD   F2_Arg5v23;
DWORD   F3_Arg3v23;
//
LPVOID  F1_Thisv24;
DWORD   F1_Arg1v24;
DWORD   F1_Arg11v24;
DWORD   F1_Arg2v24;
DWORD   F2_Arg5v24;
DWORD   F3_Arg3v24;
//


Naked(AddWingsEffect)
{
_asm
{
mov AddWingsEffect_Buff, edx
mov edx, dword ptr ss:[ebp-0x68]
mov F1_Thisv1, edx
mov F1_Thisv2, edx
mov F1_Thisv3, edx
mov F1_Thisv4, edx
mov F1_Thisv5, edx
mov F1_Thisv6, edx
mov F1_Thisv7, edx
mov F1_Thisv8, edx
mov F1_Thisv9, edx
mov F1_Thisv10, edx
mov F1_Thisv11, edx
mov F1_Thisv12, edx
mov F1_Thisv13, edx
mov F1_Thisv14, edx
mov F1_Thisv15, edx
mov F1_Thisv16, edx
mov F1_Thisv17, edx
mov F1_Thisv18, edx
mov F1_Thisv19, edx
mov F1_Thisv20, edx
mov F1_Thisv21, edx
mov F1_Thisv22, edx
mov F1_Thisv23, edx
mov F1_Thisv24, edx
lea edx, [ebp-0x58]
mov F1_Arg1v1, edx
mov F1_Arg1v2, edx
mov F1_Arg1v3, edx
mov F1_Arg1v4, edx
mov F1_Arg1v5, edx
mov F1_Arg1v6, edx
mov F1_Arg1v7, edx
mov F1_Arg1v8, edx
mov F1_Arg1v9, edx
mov F1_Arg1v10, edx
mov F1_Arg1v11, edx
mov F1_Arg1v12, edx
mov F1_Arg1v13, edx
mov F1_Arg1v14, edx
mov F1_Arg1v15, edx
mov F1_Arg1v16, edx
mov F1_Arg1v17, edx
mov F1_Arg1v18, edx
mov F1_Arg1v19, edx
mov F1_Arg1v20, edx
mov F1_Arg1v21, edx
mov F1_Arg1v22, edx
mov F1_Arg1v23, edx
mov F1_Arg1v24, edx
lea edx, [ebp-0x18]
mov F1_Arg11v1, edx
mov F1_Arg11v2, edx
mov F1_Arg11v3, edx
mov F1_Arg11v4, edx
mov F1_Arg11v5, edx
mov F1_Arg11v6, edx
mov F1_Arg11v7, edx
mov F1_Arg11v8, edx
mov F1_Arg11v9, edx
mov F1_Arg11v10, edx
mov F1_Arg11v11, edx
mov F1_Arg11v12, edx
mov F1_Arg11v13, edx
mov F1_Arg11v14, edx
mov F1_Arg11v15, edx
mov F1_Arg11v16, edx
mov F1_Arg11v17, edx
mov F1_Arg11v18, edx
mov F1_Arg11v19, edx
mov F1_Arg11v20, edx
mov F1_Arg11v21, edx
mov F1_Arg11v22, edx
mov F1_Arg11v23, edx
mov F1_Arg11v24, edx
mov edx, dword ptr ss:[ebp-0x6c]
mov F1_Arg2v1, edx
mov F1_Arg2v2, edx
mov F1_Arg2v3, edx
mov F1_Arg2v4, edx
mov F1_Arg2v5, edx
mov F1_Arg2v6, edx
mov F1_Arg2v7, edx
mov F1_Arg2v8, edx
mov F1_Arg2v9, edx
mov F1_Arg2v10, edx
mov F1_Arg2v11, edx
mov F1_Arg2v12, edx
mov F1_Arg2v13, edx
mov F1_Arg2v14, edx
mov F1_Arg2v15, edx
mov F1_Arg2v16, edx
mov F1_Arg2v17, edx
mov F1_Arg2v18, edx
mov F1_Arg2v19, edx
mov F1_Arg2v20, edx
mov F1_Arg2v21, edx
mov F1_Arg2v22, edx
mov F1_Arg2v23, edx
mov F1_Arg2v24, edx
fldz
fstp dword ptr ss:[esp]
mov edx, dword ptr ss:[ebp-0x70]
mov F2_Arg5v1, edx
mov F2_Arg5v2, edx
mov F2_Arg5v3, edx
mov F2_Arg5v4, edx
mov F2_Arg5v5, edx
mov F2_Arg5v6, edx
mov F2_Arg5v7, edx
mov F2_Arg5v8, edx
mov F2_Arg5v9, edx
mov F2_Arg5v10, edx
mov F2_Arg5v11, edx
mov F2_Arg5v12, edx
mov F2_Arg5v13, edx
mov F2_Arg5v14, edx
mov F2_Arg5v15, edx
mov F2_Arg5v16, edx
mov F2_Arg5v17, edx
mov F2_Arg5v18, edx
mov F2_Arg5v19, edx
mov F2_Arg5v20, edx
mov F2_Arg5v21, edx
mov F2_Arg5v22, edx
mov F2_Arg5v23, edx
mov F2_Arg5v24, edx
mov edx, AddWingsEffect_Buff
}

// ----
if( gItem.IsCustomWings(AddWingsEffect_Buff, true) )
{
if( AddWingsEffect_Buff == ITEM2(12, 180) )
{
Color[0] = 1.0;
Color[1] = 0.75;
Color[2] = 0.62;
// --
pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 61, 0);
pPlayStaticEffect(32376, &F1_Arg11v1, 0.5, Color, F2_Arg5v1, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 42, 0);
pPlayStaticEffect(32376, &F1_Arg11v2, 0.5, Color, F2_Arg5v2, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 60, 0);
pPlayStaticEffect(32376, &F1_Arg11v3, 1.0, Color, F2_Arg5v3, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 41, 0);
pPlayStaticEffect(32376, &F1_Arg11v4, 1.0, Color, F2_Arg5v4, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 63, 0);
pPlayStaticEffect(32376, &F1_Arg11v5, 1.0, Color, F2_Arg5v5, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 44, 0);
pPlayStaticEffect(32376, &F1_Arg11v6, 1.0, Color, F2_Arg5v6, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 42, 0);
pPlayStaticEffect(32376, &F1_Arg11v7, 1.0, Color, F2_Arg5v7, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 59, 0);
pPlayStaticEffect(32376, &F1_Arg11v8, 1.4, Color, F2_Arg5v8, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 40, 0);
pPlayStaticEffect(32376, &F1_Arg11v9, 1.4, Color, F2_Arg5v9, 1.0, 0);
// ----
Color[0] = 0.3;
Color[1] = 0.3;
Color[2] = 1.0;
// --
pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 62, 0);
pPlayStaticEffect(32376, &F1_Arg11v10, 2.6, Color, F2_Arg5v10, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 43, 0);
pPlayStaticEffect(32376, &F1_Arg11v11, 2.6, Color, F2_Arg5v11, 1.0, 0);
// ----
Color[0] = 0.6;
Color[1] = 0.45;
Color[2] = 1.0;
// --
pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 65, 0);
pPlayStaticEffect(32376, &F1_Arg11v12, 1.4, Color, F2_Arg5v12, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 46, 0);
pPlayStaticEffect(32376, &F1_Arg11v13, 1.4, Color, F2_Arg5v13, 1.0, 0);
// ----
Color[0] = 0.3;
Color[1] = 0.3;
Color[2] = 1.0;
// --
pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 58, 0);
pPlayStaticEffect(32376, &F1_Arg11v14, 2.0, Color, F2_Arg5v14, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 39, 0);
pPlayStaticEffect(32376, &F1_Arg11v15, 2.0, Color, F2_Arg5v15, 1.0, 0);
// ----
Color[0] = 0.6;
Color[1] = 0.45;
Color[2] = 1.0;
// --
pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 64, 0);
pPlayStaticEffect(32376, &F1_Arg11v16, 2.0, Color, F2_Arg5v16, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 32, 0);
pPlayStaticEffect(32376, &F1_Arg11v17, 2.0, Color, F2_Arg5v17, 1.0, 0);
// ----
Color[0] = 0.34;
Color[1] = 0.25;
Color[2] = 1.0;
// --
pAllowStaticEffect(F1_Thisv18, &F1_Arg11v18, F1_Arg2v18, 13, 0);
pPlayStaticEffect(32376, &F1_Arg11v18, 2.0, Color, F2_Arg5v18, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv19, &F1_Arg11v19, F1_Arg2v19, 15, 0);
pPlayStaticEffect(32376, &F1_Arg11v19, 2.0, Color, F2_Arg5v19, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 25, 0);
pPlayStaticEffect(32376, &F1_Arg11v20, 2.0, Color, F2_Arg5v20, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv21, &F1_Arg11v21, F1_Arg2v21, 27, 0);
pPlayStaticEffect(32376, &F1_Arg11v21, 2.0, Color, F2_Arg5v21, 1.0, 0);
// --
pAllowStaticEffect(F1_Thisv22, &F1_Arg11v22, F1_Arg2v22, 3, 0);
pPlayStaticEffect(32376, &F1_Arg11v22, 0.5, Color, F2_Arg5v22, 1.0, 0);

}
// ----
_asm
{
mov AddWingsEffect_Buff, 0x0056CA63
jmp AddWingsEffect_Buff
}
}
// ----
if( AddWingsEffect_Buff > 0x0A9D )
{
_asm
{
mov AddWingsEffect_Buff, 0x005667BB
jmp AddWingsEffect_Buff
}
}
// ----
_asm
{
mov AddWingsEffect_Buff, 0x00566707
jmp AddWingsEffect_Buff
}
}

SetRange((LPVOID)0x005666F7, 10, ASM::NOP);
SetOp((LPVOID)0x005666F7, AddWingsEffect, ASM::JMP);
*/