#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Protocol.h"

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

class ExTeleport
{
public:
	ExTeleport();
	~ExTeleport();
	void Init();
	void Load();

	void LoadImages();
	void BindImages();
	void Draw();

	void GCWindows(PMSG_GC_TELEPORTWIN* aRecv);
	void CGResult(BYTE num);
	void Button(DWORD Event);
	void SpeedCalc(int number, int &countplus);
	char* ActiveText(int status);
	int ClickPage;
	int LenCount;

	ExTeleportDATA data[MAXEXTELEPORT];
	int iLoadedCount;
};
// ----------------------------------------------------------------------------------------------
extern ExTeleport g_ExTeleport;
// ----------------------------------------------------------------------------------------------

#endif