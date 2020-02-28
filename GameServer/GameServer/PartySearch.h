#pragma once
// ----------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "..\include\prodef.h"
#if(CUSTOM_PARTY_SEARCH==TRUE)
// ----------------------------------------------------------------------------------------------

#define PARTY_SEARCH_SIZE	11
// ----------------------------------------------------------------------------------------------

struct AutoParty_DATA
{
	WORD Index;
	char Name[11];
	short Level;
	BYTE Map;
	BYTE X;
	BYTE Y;
	BYTE dw;
	BYTE dk;
	BYTE ee;
	BYTE mg;
	BYTE dl;
	BYTE su;
	BYTE rf;
	BYTE Count;
};
// ----------------------------------------------------------------------------------------------

struct CG_AutoPartyInfo
{
	PBMSG_HEAD2 h;
	BYTE ActiveSystem;
	WORD MaxLevel;
	BYTE bAllClass;
	BYTE bOnlyOneClass;
	BYTE bDarkWizard;
	BYTE bDarkKnight;
	BYTE bElf;
	BYTE bMagicGladiator;
	BYTE bDarkLord;
	BYTE bSummoner;
};
// ----------------------------------------------------------------------------------------------

struct CG_PartyRecv
{
	PBMSG_HEAD2 h;
	WORD UserIndex;
};
// ----------------------------------------------------------------------------------------------

struct GC_LoadPartySearch
{
	PBMSG_HEAD2 h;
	WORD MaxLevel;
};
// ----------------------------------------------------------------------------------------------

class PartySearch
{
public:
	void Init();
	void Load();
	void Read(char* File);

	bool NPC_Dialod(int aIndex, int aNpcIndex);

	void Search(int aIndex);
	void CG_RecvInfo(int aIndex, CG_AutoPartyInfo* Recv);
	void CG_RecvPartyUser(int aIndex, CG_PartyRecv* Recv);

	void SaveBinary(int aIndex, LPBYTE buf);
	void LoadBinary(int aIndex, LPBYTE buf);

	void GC_InfoSend(int aIndex);

	bool ActiveSystem;
	int NPC_CLASS;
	int NPC_MAP;
	int NPC_X;
	int NPC_Y;

	AutoParty_DATA Party[200];
};
extern PartySearch g_PartySearch;
// ----------------------------------------------------------------------------------------------


#endif