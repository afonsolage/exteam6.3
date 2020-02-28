#include "stdafx.h"
#include "DeBug.h"
#include "TMemory.h"
#include "Import.h"
#include "Console.h"
#include "Defines.h"
#include "Interface.h"
#include "Object.h"
#include "Protocol.h"
#include "Console.h"
#include "PersonalShopEx.h"
#include "PostItem.h"

#ifdef exDEBUG_CODE



//int __thiscall sub_83C7F0(char *this)
#define sub_83C7F0				((int(__thiscall*)(char *This)) 0x83C7F0)
//signed int __stdcall sub_83C360(signed int a1, int a2)
#define sub_83C360				((int(__stdcall*)(signed int a1, int a2)) 0x83C360)
//int __userpurge sub_7DA510@<eax>(char *this@<ecx>, int ebx0@<ebx>, int a3@<edi>, int a4@<esi>, int a2)
#define sub_7DA510				((int(*)(char *This, int ebx0, int a3, int a4, int a2)) 0x83C360)
///


DWORD ItemPacket = 0;


bool bDrawItem = false;
static MuObjectItemData * lpItem;

signed int __stdcall sub_83C270(signed int a1)
{
  signed int result; // eax@3

  if ( a1 < 0 || a1 >= 64 )
  {
    if ( a1 < 64 || a1 >= 96 )
    {
      if ( a1 < 96 || a1 >= 128 )
        result = 3;
      else
        result = 2;
    }
    else
    {
      result = 1;
    }
  }
  else
  {
    result = 0;
  }
  return result;
}

int ___83C330(int a1, int a2)
{
  if ( a2 > 0 )
    a1 += 8 * (4 * a2 - 4) + 64;
  return a1;
}

#define sub_861170				((int(__thiscall*)(LPVOID This)) 0x861170)
#define sub_82FBD0				((int(__thiscall*)(int This)) 0x82FBD0)

#define sub_861130				((int(__thiscall*)(LPVOID This)) 0x861130)
#define sub_847DC0				((int(__thiscall*)(int This)) 0x847DC0)

#define sub_861210				((int(__thiscall*)(LPVOID This)) 0x861210)
#define sub_859070				((int(__thiscall*)(int This)) 0x859070)

#define sub_84F910				((int(__thiscall*)(int This)) 0x84F910)

#define sub_8612B0				((int(__thiscall*)(LPVOID This)) 0x8612B0)
#define sub_8423C0				((int(__thiscall*)(int This)) 0x8423C0)

void DeBug_ConsoleItem()
{
	// -> Inventory
    LPVOID v101 = sub_860FC0();
    int v102 = sub_861110(v101);
    int v121 = sub_83BE10(v102);

	int iPos = 0;

	if(v121 != -1)
	{
		iPos = v121;

		if(v121 >= 128 + 12)
		{
			iPos = lpItem->PosX + 8 * lpItem->PosY + 12 + 128;
		}
		else if(v121 >= 96 + 12)
		{
			iPos = lpItem->PosX + 8 * lpItem->PosY + 12 + 96;
		}		
		else if(v121 >= 64 + 12)
		{
			iPos = lpItem->PosX + 8 * lpItem->PosY + 12 + 64;
		}
		else if(v121 >= 12)
		{
			iPos = lpItem->PosX + 8 * lpItem->PosY + 12;
		}

		gConsole.Output(cGREEN, "Inventory: %d", iPos);
		return;
	}
	
	// -> Chaos Mix
	LPVOID Mix = sub_860FC0();
	int Chaos = sub_861170(Mix);
	int iMixPos = sub_82FBD0(Chaos);

	if(iMixPos != -1)
	{
		iPos = lpItem->PosX + 8 * lpItem->PosY;
		gConsole.Output(cGREEN, "Chaos Mix: %d", iPos);
		return;
	}

	// -> Vault
	LPVOID iVau = sub_860FC0();
	int iVault = sub_861210(iVau);
	int iValPos = sub_859070(iVault);

	if(iValPos != -1)
	{
		iPos = lpItem->PosX + 8 * lpItem->PosY;

		if(iValPos >= 120)
		{
			iPos += 120;
		}
		
		gConsole.Output(cGREEN, "Vault: %d", iPos);
		return;
	}	

	// -> Personal Store
	LPVOID pCheck = sub_860FC0();
	int iCheck = sub_8612B0(pCheck);
	int iCheckPos = sub_8423C0(iCheck);

	if(iCheckPos != -1)
	{
		iPos = lpItem->PosX + 8 * lpItem->PosY + 204;
		gConsole.Output(cGREEN, "Personal Store: %d", iPos);
		return;
	}	

	// -> Dev Pos !!!
	/*LPVOID pDev = sub_860FC0();
	int iDev = sub_861130(pDev);
	int iDevPos = sub_847DC0(iDev);

	if(iDevPos != -1)
	{
		gConsole.Output(cGREEN, "Dev Pos: %d", iDevPos);
		return;
	}	*/

	// -> DEV Personal Store !!!
	/*LPVOID pPStore = sub_860FC0();
	int iStore = sub_8612D0(pPStore);
	int v16 = sub_84F910(iStore);
	{
		//LPVOID  v11 = (LPVOID)sub_8612D0(pWindowThis());
		//int v16 = sub_668930(v11) + 204;
		//int v16 = sub_84F910((int)v11);
		gConsole.Output(cGREEN, "Personal Store: %d", v16);
	}*/
	

	//ItemBmdStruct* ItemInfo = pGetItemBmdStruct(lpItem->ItemID);

	
}
#define DBI_GET_LEVEL(x)  ( ((x)>>3) )
void ChekcDrawBytes()
{
	//int __thiscall sub_7E1AC0(
	gConsole.Output(cGREEN, "AncientOption %d = %d :: Excellent = %d", (BYTE)lpItem->AncientOption, (BYTE)DBI_GET_LEVEL(lpItem->AncientOption), lpItem->ExcellentOption);

	
}

void __declspec (naked) ItemDrawInfoASM() 
{
	static DWORD dwJMPTrue = 0x007E3D1C;
	static DWORD dwJMPFalse = 0x007E5B73;
	static DWORD dwItem = 0; 
	static DWORD dwArg1 = 0; 
	static DWORD dwArg2 = 0;
	static DWORD dwArg3 = 0;
	static DWORD dwArg4 = 0;
	static DWORD dwArg5 = 0;
	static DWORD dwArg6 = 0;

	bDrawItem = false;

	__asm{ MOV dwItem, ECX }

	if(dwItem == -1)
	{
		__asm { JMP dwJMPFalse }
	}

	__asm
	{
		MOV EAX, DWORD PTR SS:[EBP+0x08]
		MOV dwArg3, EAX
		/// ----
		MOV EAX, DWORD PTR SS:[EBP+0x10]
		MOV dwArg4, EAX
		/// ----
		//MOV EAX, DWORD PTR SS:[EBP+0x12]
		//MOV dwArg2, EAX
		/// ----
		MOV EAX, DWORD PTR SS:[EBP+0x14]
		MOV dwArg5, EAX
		/// ----
		MOV EAX, DWORD PTR SS:[EBP+0x18]
		MOV dwArg6, EAX
	}

	lpItem = (MuObjectItemData*)dwArg4;

	//bDrawItem = true;

	//DeBug_ConsoleItem();
	//ChekcDrawBytes();

	//lpItem->Is380Item = 3;

	//ItemPacket

	//gConsole.Output(cGREEN, "ItemPacket : %d", (int)ItemPacket);

	//gConsole.Output(cGREEN, "%d : %d : %d : %d", dwArg3, dwArg4, dwArg5, dwArg6 );
	//gConsole.Output(cGREEN, "%d : %d : %d", lpItem->CurrentActiveSlotIndex, lpItem->PosX, lpItem->PosY);
	//ItemBmdStruct* ItemInfo = pGetItemBmdStruct(lpItem->ItemID);

	//gConsole.Output(cGREEN, "dwItem: %d, dwArg1: %d :: %d", dwItem, dwArg1, lpItem->ItemID);

	__asm { JMP dwJMPTrue }
}


int a3 = 0;

void DeBug_DrawItemPos()
{
	
	
//gConsole.Output(cGREEN, "%d", *(DWORD*)0xE60D28);
return;

    LPVOID v101 = sub_860FC0();
    int v102 = sub_861110(v101);
    int v121 = sub_83BE10(v102);

	if(v121 != -1)
	{		
		gConsole.Output(cGREEN, "%d", (char*)v102);
		return;
	}

	//char sub_4E0650()
}

int __stdcall sub_7E2110(int a1)
{
  return 32 * (*(BYTE *)(a1 + 5) & 0xF0) + *(BYTE *)a1 + 2 * (*(BYTE *)(a1 + 3) & 0x80);
}

//int __thiscall sub_7E1AC0(void *this, unsigned __int8 a2, unsigned __int8 a3, char a4, char a5, char a6, char a7, char a8, char a9, int a10)
//#define sub_7E1AC0 ((int(__thiscall*)(void *This, unsigned __int8 a2, unsigned __int8 a3, char a4, char a5, char a6, char a7, char a8, char a9, int a10)) 0x7E1AC0)
/*
WORD *__thiscall ItemByteConvert(void *this, unsigned __int8 a2, unsigned __int8 a3, char a4, char a5, char a6, char a7, char a8, char a9, int a10)
{
  void *v10; // ST10_4@1
  signed int j; // [sp+8h] [bp-10h]@15
  signed int i; // [sp+Ch] [bp-Ch]@12
  WORD *v14; // [sp+10h] [bp-8h]@1
  __int16 v15; // [sp+14h] [bp-4h]@1

  v10 = this;
  v14 = sub_9CFF45(107);
  sub_9CF4B0(v14, 0, 107);
  v15 = a3 + (a2 << 9);
  *(DWORD *)(v14 + 31) = sub_7E2020(v10);
  *v14 = v15;
  *((_BYTE *)v14 + 22) = a5;
  *((_BYTE *)v14 + 23) = a6;
  *((_BYTE *)v14 + 24) = a7;
  *((_BYTE *)v14 + 97) = (a8 & 2) >> 1 > 0;
  *((_BYTE *)v14 + 98) = (a8 & 4) >> 2 > 0;
  *((_BYTE *)v14 + 73) = 16 * (a8 & 8) >> 7 > 0;
  *(WORD *)((char *)v14 + 69) = (a9 & 0xF0) >> 4;
  *(WORD *)((char *)v14 + 71) = a9 & 0xF;
  if ( a10 )
  {
    *((_BYTE *)v14 + 79) = 5;
    for ( i = 0; i < 5; ++i )
      *((_BYTE *)v14 + i + 74) = *(_BYTE *)(i + a10);
    for ( j = 0; j < 5; ++j )
    {
      if ( *(_BYTE *)(j + a10) == 255 )
      {
        *((_BYTE *)v14 + 79) = j;
        break;
      }
      if ( *(_BYTE *)(j + a10) == 254 )
      {
        *((_BYTE *)v14 + j + 80) = -1;
      }
      else
      {
        *((_BYTE *)v14 + j + 80) = *(_BYTE *)(j + a10) % 50;
        *((_BYTE *)v14 + j + 85) = *(_BYTE *)(j + a10) / 50 + 1;
      }
    }
    if ( sub_967FB0(v14) )
    {
      *((_BYTE *)v14 + 90) = a9;
      *(WORD *)((char *)v14 + 69) = 0;
      *(WORD *)((char *)v14 + 71) = 0;
    }
    else
    {
      *((_BYTE *)v14 + 90) = -1;
    }
  }
  else
  {
    *((_BYTE *)v14 + 79) = 0;
  }
  *((_BYTE *)v14 + 96) = 0;
  *(DWORD *)((char *)v14 + 103) = 1;
  sub_7E2150(v14, a4, a6, a7);
  sub_7E22F0(&v14);
  return v14;
}
*/
int ItemRecv(void *This, void *lp)
{
  int result; // eax@2
  unsigned __int16 v3; // ST2C_2@3
  char v4; // ST33_1@3
  char v5; // ST2B_1@3
  void *v6; // [sp+0h] [bp-1Ch]@1
  char v7; // [sp+14h] [bp-8h]@3	//char v7
  char v8; // [sp+15h] [bp-7h]@3
  char v9; // [sp+16h] [bp-6h]@3
  char v10; // [sp+17h] [bp-5h]@3
  char v11; // [sp+18h] [bp-4h]@3

  v6 = This;
  if ( IsBadReadPtr(lp, 7) )
  {
    result = 0;
  }
  else
  {
    v3 = sub_7E2110((int)lp);
    v4 = *((BYTE *)lp + 5);
    v5 = *((BYTE *)lp + 6);
    v7 = *((BYTE *)lp + 7);
    v8 = *((BYTE *)lp + 8);
    v9 = *((BYTE *)lp + 9);
    v10 = *((BYTE *)lp + 10);
    v11 = *((BYTE *)lp + 11);
    result = sub_7E1AC0(
               v6,
               (signed int)v3 >> 9,
               v3,
               *((BYTE *)lp + 1),
               *((BYTE *)lp + 2),
               *((BYTE *)lp + 3),
               *((BYTE *)lp + 4),
               v4,
               v5,
              (int)&v7);//v7);	//(int)&v7);
  }
  return result;
}


//#define sub_7E19C0 ((int(*)(void *This, void *lp)) 0x7E19C0)	//__thiscall

//WORD *__thiscall sub_7E19C0(void *this, void *lp)

//int ItemPacketConvert(void *This, void *lp)	//sub_7E19C0
//{
//	//gConsole.Output(cGREEN, "lp %d", *(BYTE*)lp + 6);
//
//	//WriteMemory(lp, 0, 12);
//
//	int iResult = sub_7E19C0(This, lp);
//
//	//DWORD dwAddress = ((DWORD)lp + 6);
//
//	//printf("dwAddress %d\n", dwAddress);
//
//	//ItemPacket = iResult;
////	ItemPacket = *((BYTE*)dwAddress);
//
//	//__try
//	//{
//	//	wResult = sub_7E19C0(This, lp);
//
//	//	//ItemPacket = *((BYTE *)lp + 5);
//
//	//	//gConsole.Output(cGREEN, "ItemPacket : %d", (BYTE)ItemPacket);
//	//}
//	//__except (EXCEPTION_EXECUTE_HANDLER)
//	//{
//	//}
//
//	return iResult;
//}

//#define sub_7E19C0 ((int(*)(void *lp)) 0x7E19C0)	//__thiscall

//int Hook7E19C0(void *lp)
//{
//	return sub_7E19C0(lp);
//}

//int __thiscall (naked) ItemPacketConvert()
//{
//	ItemPacket = *((BYTE*)lp + 5);
//
//	return sub_7E19C0(This, lp);
//}

//struct HOOKCLASS_DATA
//{
//	static int __thiscall ItemPacketConvert(void *This, void *lp);
//};





static int __fastcall ItemPacketConvert(void *This, void *lp)	//sub_7E19C0
{
	ItemPacket = *((BYTE*)lp + 5);

	return sub_7E19C0(This, lp);
}


void DeBugLoad()
{

	//SetOp((LPVOID)0x0083BEA2, (LPVOID)ItemHookPosASM, ASM::JMP);
	SetOp((LPVOID)0x007E3D13, (LPVOID)ItemDrawInfoASM, ASM::JMP);

	//SetOp((LPVOID)0x00521C49, (LPVOID)&ItemPacketConvert, ASM::CALL);
	//SetOp((LPVOID)0x00521D9B, (LPVOID)&ItemPacketConvert, ASM::CALL);
	//SetOp((LPVOID)0x00521E2D, (LPVOID)&ItemPacketConvert, ASM::CALL);
	//SetOp((LPVOID)0x0083384E, (LPVOID)&ItemPacketConvert, ASM::CALL);

	g_HookClass.Load();
}

// =================

CHookClass g_HookClass;

void CHookClass::Load()
{
	SetByte((LPVOID)(0x0063F491+2), 0x12);	// -> Packet - 18 Old - 13

	SetOp((LPVOID)0x00521C49, this->Hook, ASM::CALL);
	SetOp((LPVOID)0x00521D9B, this->Hook, ASM::CALL);
	SetOp((LPVOID)0x00521E2D, this->Hook, ASM::CALL);
	SetOp((LPVOID)0x007D9FAC, this->HookEx, ASM::CALL);
	SetOp((LPVOID)0x0083384E, this->Hook, ASM::CALL);
}

int CHookClass::Hook(LPVOID This, LPVOID lp)
{
	//*((BYTE*)lp + 5) = 0;
	//*((BYTE*)lp + 6) = 0;

	//int iResult = sub_7E19C0(This, lp);

	ItemPacket++;// = iResult;	//*((BYTE*)lp + 5);

	//gConsole.Output(cGREEN, "CHookClass::Hook: %d", ItemPacket);

	//return iResult;

  int result; // eax@2
  unsigned __int16 v3; // ST2C_2@3
  char v4; // ST33_1@3
  char v5; // ST2B_1@3
  void *v6; // [sp+0h] [bp-1Ch]@1
  char v7; // [sp+14h] [bp-8h]@3	//char v7
  char v8; // [sp+15h] [bp-7h]@3
  char v9; // [sp+16h] [bp-6h]@3
  char v10; // [sp+17h] [bp-5h]@3
  char v11; // [sp+18h] [bp-4h]@3

 // memset(&lp, 0, 12);
 //*((BYTE *)lp + 4) = 0;

  v6 = This;
  if ( IsBadReadPtr(lp, 7) )
  {
    result = 0;
  }
  else
  {
    v3 = sub_7E2110((int)lp);
    v4 = *((BYTE *)lp + 5);
    v5 = *((BYTE *)lp + 6);
    v7 = *((BYTE *)lp + 7);
    v8 = *((BYTE *)lp + 8);
    v9 = *((BYTE *)lp + 9);
    v10 = *((BYTE *)lp + 10);
    v11 = *((BYTE *)lp + 11);

    result = sub_7E1AC0(
               v6,
               (signed int)v3 >> 9,
               v3,
               *((BYTE *)lp + 1),
               *((BYTE *)lp + 2),
               *((BYTE *)lp + 3),
               *((BYTE *)lp + 4),
               v4,
               v5,
              (int)&v7);//v7);	//(int)&v7);
  }

  ItemPacket = result;

  gConsole.Output(cGREEN, "ItemPacket : 0x%08X size", ItemPacket);

  return result;
}

int CHookClass::HookEx(LPVOID This, LPVOID lp)
{
	//*((BYTE*)lp + 5) = 0;
	//*((BYTE*)lp + 6) = 0;

	//int iResult = sub_7E19C0(This, lp);

	ItemPacket++;// = iResult;	//*((BYTE*)lp + 5);

	//gConsole.Output(cGREEN, "CHookClass::Hook: %d", ItemPacket);

	//return iResult;

  int result; // eax@2
  unsigned __int16 v3; // ST2C_2@3
  char v4; // ST33_1@3
  char v5; // ST2B_1@3
  void *v6; // [sp+0h] [bp-1Ch]@1
  char v7; // [sp+14h] [bp-8h]@3	//char v7
  char v8; // [sp+15h] [bp-7h]@3
  char v9; // [sp+16h] [bp-6h]@3
  char v10; // [sp+17h] [bp-5h]@3
  char v11; // [sp+18h] [bp-4h]@3

 // memset(&lp, 0, 12);
 //*((BYTE *)lp + 4) = 0;

  v6 = This;
  if ( IsBadReadPtr(lp, 7) )
  {
    result = 0;
  }
  else
  {
    v3 = sub_7E2110((int)lp);
    v4 = *((BYTE *)lp + 5);
    v5 = *((BYTE *)lp + 6);
    v7 = *((BYTE *)lp + 7);
    v8 = *((BYTE *)lp + 8);
    v9 = *((BYTE *)lp + 9);
    v10 = *((BYTE *)lp + 10);
    v11 = *((BYTE *)lp + 11);

    result = sub_7E1AC0(
               v6,
               (signed int)v3 >> 9,
               v3,
               *((BYTE *)lp + 1),
               *((BYTE *)lp + 2),
               *((BYTE *)lp + 3),
               *((BYTE *)lp + 4),
               v4,
               v5,
              (int)&v7);//v7);	//(int)&v7);
  }

  ItemPacket = result;

  BYTE Byte[5];

  Byte[0] = *((BYTE *)lp + 12);
  Byte[1] = *((BYTE *)lp + 13);
  Byte[2] = *((BYTE *)lp + 14);
  Byte[3] = *((BYTE *)lp + 15);
  Byte[4] = *((BYTE *)lp + 16);

  MuObjectItemData * lpItem = (MuObjectItemData*)result;

  gConsole.Output(cGREEN, "Item %d : 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X",
	  lpItem->ItemID,
	  Byte[0], Byte[1], Byte[2], Byte[3], Byte[4]);

  return result;
}

#endif