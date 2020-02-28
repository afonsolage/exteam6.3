#include "stdafx.h"
#include "TMemory.h"
#include "ItemPacket.h"
#include "Defines.h"
#include "Console.h"
#include "PostItem.h"
#include "Protocol.h"
#include "PersonalShopEx.h"
#include "ServerInfo.h"

#if(DEV_PACKET_ITEM)

CItemPacket g_ItemPacket;

CItemPacket::CItemPacket()
{

}

CItemPacket::~CItemPacket()
{

}

void CItemPacket::Load()
{
	//SetByte((LPVOID)(0x0063F491+2), 0x12);	// -> inventory Packet - 18 Old - 13
	//SetByte((LPVOID)(0x0063F835+2), 0x12);	// -> shop packet
	
	//SetOp((LPVOID)0x007E1AA7, this->ItemConvert, ASM::CALL);

	//SetOp((LPVOID)0x00521C49, this->HookEx, ASM::CALL);
	//SetOp((LPVOID)0x00521D9B, this->HookEx, ASM::CALL);
	//SetOp((LPVOID)0x00521E2D, this->HookEx, ASM::CALL);
	//SetOp((LPVOID)0x007D9FAC, this->HookEx, ASM::CALL);
	//SetOp((LPVOID)0x0083384E, this->HookEx, ASM::CALL);


	SetOp((LPVOID)0x005A06E3, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x005A0806, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x0079A906, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x0079A9CA, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x0079AAAE, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x007AFB6B, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x007AFC2D, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x007AFD0D, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x007EFDA3, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x007EFE41, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x0082F5FB, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x0082F6BE, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x0082F7A6, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x00837BD1, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x00837C39, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x00837D8C, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x00837DFA, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x008387F6, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x00838885, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x00838B53, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x00838C30, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x00838D0A, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x00838DC5, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x0083C54A, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x00841695, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x008581FA, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x0085856C, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x00858715, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x00858E36, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x00865375, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x00865547, this->MoveItem, ASM::CALL);
	SetOp((LPVOID)0x00865577, this->MoveItem, ASM::CALL);

	// -> PvP 

	//SetOp((LPVOID)0x00509B21, this->sub_4083F0, ASM::CALL);
	//SetOp((LPVOID)0x007E51D5, this->sub_4083F0, ASM::CALL);

	//SetRange((LPVOID)0x007E5243, ASM::NOP, 5);
	//SetByte((LPVOID)0x007E5232, 0xEB);

	SetOp((LPVOID)0x004084DE, this->PvPRankOptionASM, ASM::JMP);
	//SetOp((LPVOID)0x007E5227, this->GetPvPRankCount, ASM::CALL);
	//SetRange((LPVOID)0x007E5243, 5, ASM::NOP);
	//SetRange((LPVOID)0x007E524A, 5, ASM::NOP);
	//SetOp((LPVOID)0x007E525C, this->DrawPvPRankText, ASM::CALL);
	
	// -> Ancent
	//SetRange((LPVOID)0x004EC7D6, 5, ASM::NOP);
	//SetOp((LPVOID)0x004EC7D6, this->AncRank, ASM::CALL);
	SetOp((LPVOID)0x004EBC63, this->AncRank, ASM::CALL);
	SetOp((LPVOID)0x004EC097, this->AncRank, ASM::CALL);
	SetOp((LPVOID)0x004EC0E9, this->AncRank, ASM::CALL);
	SetOp((LPVOID)0x004EC7D6, this->AncRank, ASM::CALL);
	SetOp((LPVOID)0x004EC882, this->AncRank, ASM::CALL);

	// -> Socket
	//SetRange((LPVOID)0x007E5A20, 5, ASM::NOP);
	SetOp((LPVOID)0x009686BD, this->SocketRank, ASM::CALL);
	
}

int CItemPacket::sub_7E2110(int a1)
{
  return 32 * (*(BYTE *)(a1 + 5) & 0xF0) + *(BYTE *)a1 + 2 * (*(BYTE *)(a1 + 3) & 0x80);
}

char *CItemPacket::ItemConvert(LPVOID This, unsigned __int8 a2, unsigned __int8 a3, char a4, char a5, char a6, char a7, char a8, char a9, int a10)
{
  DWORD *v11; // [esp+0h] [ebp-18h]
  signed int j; // [esp+8h] [ebp-10h]
  signed int i; // [esp+Ch] [ebp-Ch]
  char *v14; // [esp+10h] [ebp-8h]
  __int16 v15; // [esp+14h] [ebp-4h]

  v11 = (DWORD *)This;
  v14 = (char *)sub_9CFF45(107);
  sub_9CF4B0((signed int)v14, 0, 0x6Bu);
  v15 = a3 + (a2 << 9);
  *(DWORD *)(v14 + 62) = sub_7E2020(v11);
  *(WORD *)v14 = v15;
  v14[22] = a5;
  v14[23] = a6;
  v14[24] = a7;
  v14[97] = (a8 & 2) >> 1 > 0;
  v14[98] = (a8 & 4) >> 2 > 0;
  v14[73] = 16 * (a8 & 8) >> 7 > 0;
  *(WORD *)(v14 + 69) = (a9 & 0xF0) >> 4;
  *(WORD *)(v14 + 71) = a9 & 0xF;
  if ( a10 )
  {
    v14[79] = 5;
    for ( i = 0; i < 5; ++i )
      v14[i + 74] = *(BYTE *)(i + a10);
    for ( j = 0; j < 5; ++j )
    {
      if ( *(unsigned __int8 *)(j + a10) == 255 )
      {
        v14[79] = j;
        break;
      }
      if ( *(unsigned __int8 *)(j + a10) == 254 )
      {
        v14[j + 80] = -1;
      }
      else
      {
        v14[j + 80] = *(unsigned __int8 *)(j + a10) % 50;
        v14[j + 85] = *(unsigned __int8 *)(j + a10) / 50 + 1;
      }
    }
    if ( sub_967FB0((signed __int16 *)v14) )
    {
      v14[90] = a9;
      *(WORD *)(v14 + 69) = 0;
      *(WORD *)(v14 + 71) = 0;
    }
    else
    {
      v14[90] = -1;
    }
  }
  else
  {
    v14[79] = 0;
  }
  v14[96] = 0;
  *(DWORD *)(v14 + 103) = 1;
  sub_7E2150((int)v14, a4, a6, a7);
  sub_7E22F0(v11 + 1, (int)&v14);
  return v14;
}

int CItemPacket::Hook(LPVOID This, LPVOID lp)
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
    v3 = g_ItemPacket.sub_7E2110((int)lp);
    v4 = *((BYTE *)lp + 5);
    v5 = *((BYTE *)lp + 6);
    v7 = *((BYTE *)lp + 7);
    v8 = *((BYTE *)lp + 8);
    v9 = *((BYTE *)lp + 9);
    v10 = *((BYTE *)lp + 10);
    v11 = *((BYTE *)lp + 11);

	result = (int)g_ItemPacket.ItemConvert(
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

int CItemPacket::HookEx(LPVOID This, LPVOID lp)
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
    v3 = g_ItemPacket.sub_7E2110((int)lp);
    v4 = *((BYTE *)lp + 5);
    v5 = *((BYTE *)lp + 6);
    v7 = *((BYTE *)lp + 7);
    v8 = *((BYTE *)lp + 8);
    v9 = *((BYTE *)lp + 9);
    v10 = *((BYTE *)lp + 10);
    v11 = *((BYTE *)lp + 11);

	result = (int)g_ItemPacket.ItemConvert(
               v6,
               (signed int)v3 >> 9,
               v3,
               *((BYTE *)lp + 1),
               *((BYTE *)lp + 2),
               *((BYTE *)lp + 3),
               *((BYTE *)lp + 4),
               v4,
               v5,
              (int)&v7);
  }

  BYTE Byte[5];

  Byte[0] = *((BYTE *)lp + 12);
  Byte[1] = *((BYTE *)lp + 13);
  Byte[2] = *((BYTE *)lp + 14);
  Byte[3] = *((BYTE *)lp + 15);
  Byte[4] = *((BYTE *)lp + 16);

 MuObjectItemData * lpItem = (MuObjectItemData*)result;

 //lpItem->SocketOption[0] = 1;
 //lpItem->SocketOption[1] = 1;
 //lpItem->SocketOption[2] = 1;
 //lpItem->SocketOption[3] = 1;
 //lpItem->SocketOption[4] = 1;
 //==
 //lpItem->SocketSphereLevel[0] = 1;
 //lpItem->SocketSphereLevel[1] = 1;
 //lpItem->SocketSphereLevel[2] = 1;
 //lpItem->SocketSphereLevel[3] = 1;
 //lpItem->SocketSphereLevel[4] = 1;
 //Unknown79 = 5;

  //gConsole.Output(cGREEN, "Item %d : 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X",
	 // lpItem->ItemID,
	 // Byte[0], Byte[1], Byte[2], Byte[3], Byte[4]);

  return result;
}

// -> ITEM MOVE PACKET



//void __ItemMove(LPVOID This, int a2, int a3, char a4, char a5, signed __int16 *a6, char a7, char a8)
//{
//	
//	BYTE v35 = 0;
//	BYTE v42 = 0;
//
//  if ( *((BYTE *)a6 + 73) )
//    v35 = (*a6 >> 5) & 0xF0 | 8;
//  else
//    v35 = (*a6 >> 5) & 0xF0;
//  if ( *((BYTE *)a6 + 97) == 1 )
//    v35 |= 2u;
//  if ( *((BYTE *)a6 + 98) == 1 )
//    v35 |= 4u;
//  if ( sub_967FB0(a6) )
//    v42 = *((BYTE *)a6 + 90);
//  else
//    v42 = *((BYTE *)a6 + 71) + 16 * *((BYTE *)a6 + 69);
//
//	PMSG_INVENTORYITEMMOVE pMsg;
//	pMsg.h.set((LPBYTE)&pMsg, 0xC1, 0x24);
//	pMsg.sFlag = a4;
//	pMsg.source_item_num = a5;
//	pMsg.sItemInfo[0] = *a6 & 0xFF;
//	pMsg.sItemInfo[1] = *(DWORD*)(a6 + 1) & 0xFF;
//	pMsg.sItemInfo[2] = *((BYTE *)a6 + 22);
//	pMsg.sItemInfo[3] = *((BYTE *)a6 + 23);
//	pMsg.sItemInfo[4] = *((BYTE *)a6 + 24);
//	pMsg.sItemInfo[5] = v35;
//	pMsg.sItemInfo[6] = v42;
//	pMsg.sItemInfo[7] = *((BYTE *)a6 + 74);
//	pMsg.sItemInfo[8] = *((BYTE *)a6 + 75);
//	pMsg.sItemInfo[9] = *((BYTE *)a6 + 76);
//	pMsg.sItemInfo[10] = *((BYTE *)a6 + 77);
//	pMsg.sItemInfo[11] = *((BYTE *)a6 + 78);
//	pMsg.tFlag = a7;
//	pMsg.target_item_num = a8;
//
//	gProtocol.DataSend((LPBYTE)&pMsg, sizeof(pMsg));
//
//}



bool CItemPacket::MoveItem(char a4, char a5, signed __int16 *a6, char a7, char a8)
{
	//return sub_5BD850(a4, a5, (int)a6, a7, a8);











  if ( *(BYTE*)0x81F6BEF || !a6 )
    return 0;
	*(BYTE*)0x81F6BEF = 1;

	BYTE v35 = 0;
	BYTE v42 = 0;

  if ( *((BYTE *)a6 + 73) )
    v35 = (*a6 >> 5) & 0xF0 | 8;
  else
    v35 = (*a6 >> 5) & 0xF0;
  if ( *((BYTE *)a6 + 97) == 1 )
    v35 |= 2u;
  if ( *((BYTE *)a6 + 98) == 1 )
    v35 |= 4u;
  if ( sub_967FB0(a6) )
    v42 = *((BYTE *)a6 + 90);
  else
    v42 = *((BYTE *)a6 + 71) + 16 * *((BYTE *)a6 + 69);

	PMSG_INVENTORYITEMMOVE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0x24, sizeof(pMsg));
	pMsg.sFlag = a4;
	pMsg.source_item_num = a5;
	pMsg.sItemInfo[0] = *a6 & 0xFF;
	pMsg.sItemInfo[1] = *(DWORD*)(a6 + 1) & 0xFF;
	pMsg.sItemInfo[2] = *((BYTE *)a6 + 22);
	pMsg.sItemInfo[3] = *((BYTE *)a6 + 23);
	pMsg.sItemInfo[4] = *((BYTE *)a6 + 24);
	pMsg.sItemInfo[5] = v35;
	pMsg.sItemInfo[6] = v42;
	pMsg.sItemInfo[7] = *((BYTE *)a6 + 74);
	pMsg.sItemInfo[8] = *((BYTE *)a6 + 75);
	pMsg.sItemInfo[9] = *((BYTE *)a6 + 76);
	pMsg.sItemInfo[10] = *((BYTE *)a6 + 77);
	pMsg.sItemInfo[11] = *((BYTE *)a6 + 78);
	pMsg.tFlag = a7;
	pMsg.target_item_num = a8;

	gProtocol.DataSend((LPBYTE)&pMsg, sizeof(pMsg));

	return 1;






  //char v9; // ST34_1
  //char v10; // ST30_1
  //char v11; // ST2C_1
  //char v12; // ST28_1
  //char v13; // ST24_1
  //char v14; // ST20_1
  //char v15; // ST18_1
  //char v16; // ST14_1
  //char v17; // ST10_1
  //int v18; // ST0C_4
  //__int16 v19; // ST08_2
  //unsigned __int16 *v20; // eax
  //unsigned __int16 *v21; // eax
  //unsigned __int16 *v22; // eax
  //unsigned __int16 *v23; // eax
  //unsigned __int16 *v24; // eax
  //unsigned __int16 *v25; // eax
  //unsigned __int16 *v26; // eax
  //unsigned __int16 *v27; // eax
  //unsigned __int16 *v28; // eax
  //unsigned __int16 *v29; // eax
  //unsigned __int16 *v30; // eax
  //unsigned __int16 *v31; // eax
  //unsigned __int16 *v32; // eax
  //unsigned __int16 *v33; // eax
  //unsigned __int16 *v34; // eax
  //char v35; // [esp+3h] [ebp-825h]
  //__m128i v36[128]; // [esp+4h] [ebp-824h]
  //char v37; // [esp+810h] [ebp-18h]
  //char v38; // [esp+811h] [ebp-17h]
  //char v39; // [esp+812h] [ebp-16h]
  //char v40; // [esp+813h] [ebp-15h]
  //char v41; // [esp+814h] [ebp-14h]
  //char v42; // [esp+81Bh] [ebp-Dh]
  //int v43; // [esp+824h] [ebp-4h]

  //if ( *(BYTE*)0x81F6BEF || !a6 )
  //  return 0;
  //*(BYTE*)0x81F6BEF = 1;
  //sub_404B40(v36);
  //v43 = 0;
  //sub_404B90(v36, 193, 36);
  //if ( *((BYTE *)a6 + 73) )
  //  v35 = (*a6 >> 5) & 0xF0 | 8;
  //else
  //  v35 = (*a6 >> 5) & 0xF0;
  //if ( *((BYTE *)a6 + 97) == 1 )
  //  v35 |= 2u;
  //if ( *((BYTE *)a6 + 98) == 1 )
  //  v35 |= 4u;
  //if ( sub_967FB0(a6) )
  //  v42 = *((BYTE *)a6 + 90);
  //else
  //  v42 = *((BYTE *)a6 + 71) + 16 * *((BYTE *)a6 + 69);
  //v37 = *((BYTE *)a6 + 74);
  //v38 = *((BYTE *)a6 + 75);
  //v39 = *((BYTE *)a6 + 76);
  //v40 = *((BYTE *)a6 + 77);
  //v41 = *((BYTE *)a6 + 78);
  //v9 = v41;
  //v10 = v40;
  //v11 = v39;
  //v12 = v38;
  //v13 = v37;
  //v14 = v42;
  //v15 = *((BYTE *)a6 + 24);
  //v16 = *((BYTE *)a6 + 23);
  //v17 = *((BYTE *)a6 + 22);
  //v18 = *(DWORD *)(a6 + 1) & 0xFF;
  //v19 = *a6 & 0xFF;
  //v20 = sub_4050D0((unsigned __int16 *)v36, a4);
  //v21 = sub_4050D0(v20, a5);
  //v22 = sub_4050D0(v21, v19);
  //v23 = sub_4050D0(v22, v18);
  //v24 = sub_4050D0(v23, v17);
  //v25 = sub_4050D0(v24, v16);
  //v26 = sub_4050D0(v25, v15);
  //v27 = sub_4050D0(v26, v35);
  //v28 = sub_4050D0(v27, v14);
  //v29 = sub_4050D0(v28, v13);
  //v30 = sub_4050D0(v29, v12);
  //v31 = sub_4050D0(v30, v11);
  //v32 = sub_4050D0(v31, v10);
  //v33 = sub_4050D0(v32, v9);
  //v34 = sub_4050D0(v33, a7);
  //sub_4050D0(v34, a8);
  //sub_404D70((int)v36, a1, a2, a3, 1, 0);
  //v43 = -1;
  //sub_404B60();
  //return 1;
}


#define hook_409A20 ((DWORD *(__thiscall*)(LPVOID This)) 0x409A20)	
#define hook_9CF4B0 ((signed int(__cdecl*)(signed int a1, int a2, unsigned int a3)) 0x9CF4B0)	
#define hook_402320 ((int(__thiscall*)(LPVOID This, int a1)) 0x402320)
#define hook_9CF52A ((signed int(*)(LPVOID a1, int a2, ...)) 0x9CF52A)
#define hook_409B10 ((int(__thiscall*)(LPVOID This, int a1)) 0x409B10)
#define hook_408720 ((int(__thiscall*)(LPVOID This, int a2)) 0x408720)
#define hook_409AD0 ((BYTE*(__thiscall*)(LPVOID This)) 0x409AD0)


#define HOOK_4083F0 ((void(__thiscall*)(unsigned __int8 *This, int a2, int a3)) 0x4083F0)

void CItemPacket::sub_4083F0(PBYTE This, int a2, int a3)
{
	//gConsole.Output(cGREEN, (char*)*(DWORD*)a2); 

	//HOOK_4083F0(This, a2, a3);

	//return;

	//gConsole.Output(cGREEN, (char*)*(DWORD*)a2); 

	//return;

	//PBYTE pAddress = This;
	//int iTextLine = 0;
	////BYTE v23[28];
	//BYTE v23[28];
	//int v27;
	//BYTE v22[103];
	//BYTE v21;

 //  // hook_409A20(&v23);
 //   v27 = 0;
 //   v21 = 0;
 //   //hook_9CF4B0((signed int)&v22, 0, 99);

 //   iTextLine = hook_402320((LPVOID)0x8128ADC, 2190);

 //   hook_9CF52A(&v21, iTextLine);

 //   hook_409B10(&v23, (int)&v21);
 //   hook_408720((LPVOID)&a2, (int)&v23);
 //   v27 = -1;



    //hook_409AD0((LPVOID)v23);
	//delete []v23;
	//sprintf(btTemp, (char*)iTextLine);

	//gConsole.Output(cGREEN, (char*)iTextLine); 

	// ==================

  PBYTE pAddress = This;
  int iOptNum =  0 ;
  int iOptValue =  0 ;
  int iTextLine = 0;

  g_ItemPacket.m_PvPCount = 0;

  for (int  i = 0; i < 2; i++ )
  {
	iOptValue = 0;

    if ( i )
    {
      iOptNum = pAddress[16 * a3 + 8];
      iOptValue = *(WORD*)&pAddress[16 * a3 + 10];
    }
    else
    {
      iOptNum = pAddress[16 * a3 + 4];
      iOptValue = *(WORD*)&pAddress[16 * a3 + 6];
    }

	iOptValue = iOptValue * 5;

    switch (iOptNum)
    {
      case 1:
        iTextLine = hook_402320((LPVOID)0x8128ADC, 2184);
        break;
      case 2:
        iTextLine = hook_402320((LPVOID)0x8128ADC, 2185); 
        break;
      case 3:
        iTextLine = hook_402320((LPVOID)0x8128ADC, 2186);
       // hook_9CF52A(&v19, v8, iValue);
		//gConsole.Output(cGREEN, (char*)iTextLine, iOptValue); 
        break;
      case 4:
        iTextLine = hook_402320((LPVOID)0x8128ADC, 2187);
       // hook_9CF52A(&v19, v10, iValue);
		//gConsole.Output(cGREEN, (char*)iTextLine, iOptValue); 
        break;
      case 5:
        iTextLine = hook_402320((LPVOID)0x8128ADC, 2188);
       // hook_9CF52A(&v19, v12, iValue);
		gConsole.Output(cGREEN, (char*)iTextLine, iOptValue); 
        break;
      case 6:
        iTextLine = hook_402320((LPVOID)0x8128ADC, 2189);
       // hook_9CF52A(&v19, v14, iValue);
		//gConsole.Output(cGREEN, (char*)iTextLine, iOptValue); 
        break;
      case 7:
        iTextLine = hook_402320((LPVOID)0x8128ADC, 2190);
       // hook_9CF52A(&v19, iLine);
		//gConsole.Output(cGREEN, (char*)iTextLine); 
        break;
      case 8:
        iTextLine = hook_402320((LPVOID)0x8128ADC, 2191);
        //hook_9CF52A(&v19, iLine, iValue);
		//gConsole.Output(cGREEN, (char*)iTextLine, iOptValue); 
        break;
      default:
        break;
    }

	sprintf(g_ItemPacket.m_PvPOpt[i], (char*)iTextLine, iOptValue);

	g_ItemPacket.m_PvPCount++;

	//gConsole.Output(cGREEN, "[%d] %s",  iOptNum, (char*)iTextLine); 

	//hook_9CF52A(&v21, iTextLine, iOptValue);
//
//	__try
	//{
		//char v21 = 0;
		//hook_9CF52A(&v21, iTextLine, iOptValue);
	//}
	//__except (EXCEPTION_EXECUTE_HANDLER) {}
	
	//gConsole.Output(cGREEN, (char*)iLine, v24); 

    //v16 = v24;
    //v17 = hook_402320((LPVOID)0x8128ADC, 2191);
    //hook_9CF52A(&v19, v17, v16);

	
    //v16 = v24;
    //v17 = hook_402320((LPVOID)0x8128ADC, 2191);

	//char szTemp[128];
	//sprintf(szTemp, (char*)v17, v24);
	//gConsole.Output(cGREEN, szTemp); 

   //hook_9CF52A(&v19, v17, v16);

    //v3 = v24;
    //int v4 = sub_402320(2184);
  // hook_9CF52A(v19, v4, v24);
	//v3 = v24;
 // int v4 = hook_402320((LPVOID)0x8128ADC, 2184);
 // hook_9CF52A(&v19, v4, v3);

	//char szTemp[128];
	//sprintf(szTemp, (char*)v4, v3);

	//int v4 = hook_402320((LPVOID)0x8128ADC, 2184);
	//gConsole.Output(cGREEN, (char*)v4, v24); 

    //hook_409B10(&v19);
    //hook_408720((LPVOID)a2, (int)&v21);
    //v26 = -1;
    //hook_409AD0((LPVOID)v22);
  }
}

__declspec(naked) void CItemPacket::PvPRankOptionASM()
{
	static DWORD dwOptNum ;
	static DWORD dwOptValue;

	static DWORD dwDefault = 0x0040861F;
	static DWORD dwSwitch = 0x004084E4;

	__asm
	{
		MOV EAX,DWORD PTR SS:[EBP-0xA4]
		MOV dwOptNum, EAX
		MOV EAX,DWORD PTR SS:[EBP-0x10]
		MOV dwOptValue, EAX
	}

	if(dwOptNum > 7)
	{
		__asm
		{
			JMP dwDefault
		}
	}

	dwOptValue = dwOptValue * 10;

	__asm
	{
		MOV EAX, dwOptValue
		MOV DWORD PTR SS:[EBP-0x10], EAX
		JMP dwSwitch
	}
}

int CItemPacket::GetPvPRankCount()
{
	return g_ItemPacket.m_PvPCount;
}

#define sub_9D04E0 ((BYTE*(__cdecl*)(BYTE *a1, char *a2, unsigned int a3)) 0x9D04E0)

BYTE * CItemPacket::DrawPvPRankText(BYTE *a1, char *a2, unsigned int a3)
{
	//sprintf(g_ItemPacket.m_PvPOpt[i], (char*)iTextLine, iOptValue);

	//gConsole.Output(cGREEN, "%s %d", a2, a3); 

	return sub_9D04E0(a1, g_ItemPacket.m_PvPOpt[0], a3);

	
}

//int __stdcall sub_4EA2D0(int a1, unsigned __int8 a2, unsigned __int8 a3, int a4)
//#define sub_4EA2D0 ((int(__stdcall*)(int a1, unsigned __int8 a2, unsigned __int8 a3, int a4)) 0x4EA2D0)
#define sub_4EA2D0 ((int(__stdcall*)(char* Line, unsigned __int8 OptionType, unsigned __int8 OptionValue, int a4)) 0x4EA2D0)

int CItemPacket::AncRank(char* Line, unsigned __int8 OptionType, unsigned __int8 OptionValue, int a4)
{
	OptionValue += 1;

	return sub_4EA2D0(Line, OptionType, OptionValue, a4);
}

#define sub_968660 ((void(__thiscall*)(char *This, int a2, int a3, int a4)) 0x968660)

//void CItemPacket::SocketRank(char *This, int a2, int a3, int a4)
//{
//	sub_968660(This, a2, a3, a4);
//}

#define sub_968550 ((int(__stdcall*)(int a1, int a2, float a3)) 0x968550)

int CItemPacket::SocketRank(int a1, int a2, float a3)
{
	a3 += 3;

	return sub_968550(a1, a2, a3);
}
#endif