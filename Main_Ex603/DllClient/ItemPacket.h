#pragma once

#if(DEV_PACKET_ITEM)

#include "Protocol.h"

#define MAX_ITEM_INFO 12// + 5

#define sub_7E19C0 ((int(__thiscall*)(LPVOID This, LPVOID lp)) 0x7E19C0)	//__thiscall
#define sub_7E1AC0 ((int(__thiscall*)(LPVOID This, unsigned __int8 a2, unsigned __int8 a3, char a4, char a5, char a6, char a7, char a8, char a9, int a10)) 0x7E1AC0)

//int __cdecl sub_9CFF45(int a1)
#define sub_9CFF45 ((int(__cdecl*)(int a1)) 0x9CFF45)	//OK
//_BYTE *__cdecl sub_9CF4B0(_BYTE *a1, int a2, unsigned int a3)
//#define sub_9CF4B0 ((BYTE *(__cdecl*)(BYTE *a1, int a2, unsigned int a3)) 0x9CF4B0)	//OK
#define sub_9CF4B0 ((int(__cdecl*)(signed int a1, int a2, unsigned int a)) 0x9CF4B0)	//OK
//unsigned int __thiscall sub_7E2020(int this)
#define sub_7E2020 ((unsigned int(__thiscall*)(/*int This*/DWORD *This)) 0x7E2020)
//int __stdcall sub_967FB0(WORD *a1)
#define sub_967FB0 ((int(__stdcall*)(/*WORD *a1*/signed __int16 *a1)) 0x967FB0)
#define sub_967FB0_ ((int(__stdcall*)(WORD *a1)) 0x967FB0)
//char __stdcall sub_7E2150(int a1, char a2, char a3, char a4)
#define sub_7E2150 ((char(__stdcall*)(int a1, char a2, char a3, char a4)) 0x7E2150)
//int __stdcall sub_7E22F0(int a1)
//#define sub_7E22F0 ((int *(__stdcall*)(int a1)) 0x7E22F0)
//int *__userpurge sub_7E22F0@<eax>(int ecx0@<ecx>, int a2@<ebx>, int a3@<edi>, int a4@<esi>, int a1)
//DWORD *__thiscall sub_7E22F0(void *this, int a1)
#define sub_7E22F0 ((DWORD*(__thiscall*)(LPVOID This, int a1)) 0x7E22F0)

// ===============

////void *__thiscall sub_404B40(void This)
//#define sub_404B40 ((LPVOID(__thiscall*)(LPVOID This)) 0x404B40)
////_WORD *__thiscall sub_404B90(void *this, char a2, char a3)
//#define sub_404B90 ((WORD *(__thiscall*)(LPVOID This, char a2, char a3)) 0x404B40)
////_WORD *__thiscall sub_4050D0(_WORD *this, char a2)
//#define sub_4050D0 ((WORD *(__thiscall*)(WORD *This, char a2)) 0x4050D0)
////signed int __thiscall sub_404D70(_WORD *this, int a2, int a3)
////#define sub_404D70 ((int(__thiscall*)(int a1, FARPROC (__stdcall *a2)(HMODULE hModule, LPCSTR lpProcName), int a3, int a4, int a5, int a6)) 0x404D70)
////void sub_404B60()
//#define sub_404B60 ((void(*)()) 0x404B60)
////FARPROC (__stdcall *a1)(HMODULE hModule, LPCSTR lpProcName), int a2, int a3, char a4, char a5, signed __int16 *a6, char a7, char a8


struct PMSG_INVENTORYITEMMOVE
{
	PBMSG_HEAD h;
	BYTE sFlag;	// 3
	BYTE source_item_num;	// 4
	BYTE sItemInfo[MAX_ITEM_INFO];	// 5
	BYTE tFlag;	// C
	BYTE target_item_num;	// D
};

class CItemPacket
{
public:
		CItemPacket();
		~CItemPacket();
	void Load();
	int __stdcall sub_7E2110(int a1);
	static char* __thiscall ItemConvert(LPVOID This, unsigned __int8 a2, unsigned __int8 a3, char a4, char a5, char a6, char a7, char a8, char a9, int a10);
	static int __thiscall Hook(LPVOID This, LPVOID lp);
	static int __thiscall HookEx(LPVOID This, LPVOID lp);
	static bool MoveItem(char a4, char a5, signed __int16 *a6, char a7, char a8);

	static void __thiscall sub_4083F0(PBYTE This, int a2, int a3);
	static void PvPRankOptionASM();
	static int GetPvPRankCount();
	static BYTE *DrawPvPRankText(BYTE *a1, char *a2, unsigned int a3);

	static int AncRank(char* Line, unsigned __int8 OptionType, unsigned __int8 OptionValue, int a4);
	//static void SocketRank(char *This, int a2, int a3, int a4);
	static int SocketRank(int a1, int a2, float a3);

	char m_PvPOpt[2][64];
	int m_PvPCount;

};

extern CItemPacket g_ItemPacket;

#endif