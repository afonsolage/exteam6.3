#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "protocol.h"
// ----------------------------------------------------------------------------------------------

struct GC_OPEN_SEND
{
	PBMSG_HEAD2 h;
	BYTE Result;
};
// ----------------------------------------------------------------------------------------------

struct AutoParty_DATA
{
	WORD Index;
	char Name[11];
	WORD Level;
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

class PartySearch
{
public:
	// -> Load
	void Init();
	void Load();
	void LoadImages();
	void BindImages();
	// Draw Interface
	void DrawMaster();
	void DrawUser();
	// -> Controller
	void Button(DWORD Event);
	// -> Protocol
	void GC_Recv(LPBYTE aRecv);
	void GC_InfoRecv(CG_AutoPartyInfo* aRecv);
	void CG_SendOpenUserList();

	bool Active;

	// -> User
	bool InfoDraw;
	float InfoX;
	float InfoY;
	int InfoUP;

	int Page;
	int MaxParty;

	// -> Master
	bool ActiveSystem;
	short MaxLevel;
	bool bAllClass;
	bool bOnlyOneClass;
	bool bDarkWizard;
	bool bDarkKnight;
	bool bElf;
	bool bMagicGladiator;
	bool bDarkLord;
	bool bSummoner;

	AutoParty_DATA Party[200];
};
extern PartySearch g_PartySearch;
// ----------------------------------------------------------------------------------------------