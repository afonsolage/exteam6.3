#pragma once
// ----------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "..\include\prodef.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_EX_TELEPORT==TRUE)
// ----------------------------------------------------------------------------------------------

#define MAXEXTELEPORT	10
// ----------------------------------------------------------------------------------------------

struct ExTeleportData
{
	BYTE result;
	BYTE map;
	BYTE x;
	BYTE y;
	WORD level;
	BYTE ok_level;
	WORD reset;
	BYTE ok_reset;
	WORD grand;
	BYTE ok_grand;
	BYTE premium;
	BYTE ok_premium;
	DWORD zen;
	BYTE ok_zen;
	WORD bonus;
	BYTE ok_bonus;
	WORD credit;
	BYTE ok_credit;
	BYTE Master;
	BYTE ok_Master;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_GC_TELEPORTWIN
{
	PWMSG_HEAD2	h;
	BYTE count;
	ExTeleportData tdata[MAXEXTELEPORT];
};
// ----------------------------------------------------------------------------------------------

struct PMSG_CG_TELEPORTWINRES
{
	PBMSG_HEAD2	h;
	BYTE result;
};
// ----------------------------------------------------------------------------------------------

struct ExTeleportDATA
{
	BYTE map;
	BYTE x;
	BYTE y;
	WORD level;
	WORD reset;
	WORD grand;
	BYTE premium;
	DWORD zen;
	WORD bonus;
	WORD credit;
	BYTE Master;
};
// ----------------------------------------------------------------------------------------------

class ExTeleport
{
public:
	ExTeleport();
	~ExTeleport();
	void Init();
	void Load();
	void Read(char* File);
	bool Dialog(int aUserIndex, int aNpcIndex);
	void Timer();
	bool Check(int aUserIndex);
	void GCWindows(int aUserIndex);
	void CGResult(PMSG_CG_TELEPORTWINRES* aRecv, int aUserIndex);

	bool Enable;
	int NPC_Class;
	int NPC_Map;
	int NPC_X;
	int NPC_Y;
	int iLoadedCount;
	ExTeleportDATA data[MAXEXTELEPORT];
	
};
// ----------------------------------------------------------------------------------------------
extern ExTeleport g_ExTeleport;
// ----------------------------------------------------------------------------------------------
#endif