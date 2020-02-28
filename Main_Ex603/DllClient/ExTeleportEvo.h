#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Protocol.h"

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

class ExTeleportEvo
{
public:
	ExTeleportEvo();
	~ExTeleportEvo();
	void Init();
	void Load();

	void LoadImages();
	void BindImages();
	void Draw();

	void GCWindows(PMSG_GC_TELEPORTWINEVO* aRecv);
	void CGResult(BYTE num);
	void Button(DWORD Event);
	void SpeedCalc(int number, int &countplus);
	char* ActiveText(int status);
	void CGDialog();

	int ClickPage;
	int LenCount;

	ExTeleportDATAEVO data[MAXEXTELEPORT];
	int iLoadedCount;
};
// ----------------------------------------------------------------------------------------------
extern ExTeleportEvo g_ExTeleportEvo;
// ----------------------------------------------------------------------------------------------

#endif