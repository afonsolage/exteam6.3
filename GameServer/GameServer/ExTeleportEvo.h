#pragma once
// ----------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "..\include\prodef.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_EX_TELEPORT_EVO==TRUE)
// ----------------------------------------------------------------------------------------------

#define MAXEXTELEPORT	10
// ----------------------------------------------------------------------------------------------

struct ExTeleportDataEVO
{
	BYTE result;
	BYTE map;
	BYTE x;
	BYTE y;
	WORD min_level;
	WORD max_level;
	BYTE ok_level;
	WORD min_reset;
	WORD max_reset;
	BYTE ok_reset;
	WORD min_grand;
	WORD max_grand;
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
	BYTE EmptyInv;
	BYTE ok_EmptyInv;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_GC_TELEPORTWINEVO
{
	PWMSG_HEAD2	h;
	BYTE count;
	ExTeleportDataEVO tdata[MAXEXTELEPORT];
};
// ----------------------------------------------------------------------------------------------

struct PMSG_CG_TELEPORTWINRESEVO
{
	PBMSG_HEAD2	h;
	BYTE result;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_CG_DIALOGEVO
{
	PBMSG_HEAD2	h;
	BYTE result;
};
// ----------------------------------------------------------------------------------------------

struct ExTeleportDATAEVO
{
	BYTE map;
	BYTE x;
	BYTE y;
	WORD min_level;
	WORD max_level;
	WORD min_reset;
	WORD max_reset;
	WORD min_grand;
	WORD max_grand;
	BYTE premium;
	DWORD zen;
	WORD bonus;
	WORD credit;
	BYTE Master;
	BYTE EmptyInv;
};
// ----------------------------------------------------------------------------------------------

class ExTeleportEvo
{
public:
	ExTeleportEvo();
	~ExTeleportEvo();
	void Init();
	void Load();
	void Read(char* File);
	bool Dialog(int aUserIndex, int aNpcIndex);
	void Timer();
	bool Check(int aUserIndex);
	void GCWindows(int aUserIndex);
	void CGResult(PMSG_CG_TELEPORTWINRESEVO* aRecv, int aUserIndex);
	void CGDialog(PMSG_CG_DIALOGEVO* lpMsg, int aUserIndex);

	bool Enable;
	int NPC_Class;
	int NPC_Map;
	int NPC_X;
	int NPC_Y;
	int iLoadedCount;
	ExTeleportDATAEVO data[MAXEXTELEPORT];
	
};
// ----------------------------------------------------------------------------------------------
extern ExTeleportEvo g_ExTeleportEvo;
// ----------------------------------------------------------------------------------------------
#endif