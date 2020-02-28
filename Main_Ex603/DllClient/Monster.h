#pragma once

#include "stdafx.h"
#include "Object.h"
// ----------------------------------------------------------------------------------------------

#define MAX_MONSTER		1024
#define MONSTER_MODEL	644
// ----------------------------------------------------------------------------------------------

#define pLoadMonsterBMD			((void(__cdecl*)(signed int a1, char* a2, char* a3, signed int a4)) 0x614D10)
#define pLoadMonsterTexture		((void(__cdecl*)(int a1, char* a2, int a3, signed int a4)) 0x614710)
#define pShowMonster			((double(__cdecl*)(int a1, int a2, int a3, int a4)) 0x580FC0)
#define pVieweObject			((int(__cdecl*)(int a1, signed int a2, unsigned __int8 a3, unsigned __int8 a4, float a5)) 0x57EEC0)
#define pLoadMonsterID			((int(__cdecl*)(signed int a1)) 0x61FDE0)
// ----------------------------------------------------------------------------------------------

struct Monster_DATA
{
	WORD ID;
	BYTE Type;
	char Name[25];
	char Dir[50];
	char Folder[50];
	char BMDFile[50];
	float Size;
};
// ----------------------------------------------------------------------------------------------

struct npcName_DATA  //-> Complete (size: 27)
{
	WORD	ObjectID;
	char	Name[25];
};
// ----------------------------------------------------------------------------------------------

class Monster
{
public:
	void			Load();
	void			ReadList(char * File);
	void			ReadName(char* File);
	// ----
	static void		LoadMonsterBMD(signed int ModelID, char* a2, char* a3, signed int a4);
	static void		LoadMonsterTexture(signed int ModelID, char* a2, int a3, int a4);
	static void		ShowMonster(int MonsterID, int a2, int a3, int a4);
	static void		SetMainAttribute(int ObjectPointer, int MonsterID);
	// ----
	char*			GetMonsterName(int MOBID);
	// ----
	npcName_DATA	name_data[MAX_MONSTER];
	int				iLoadedName;
private:
	NpcNameList		lpNpcName[MAX_MONSTER];
	Monster_DATA	Data[MAX_MONSTER];
	int				Count;
	// ----
}; extern Monster gMonster;
// ----------------------------------------------------------------------------------------------