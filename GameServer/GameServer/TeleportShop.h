#pragma once

#include "StdAfx.h"
#include "protocol.h"

#if(TELEPORT_SHOP==TRUE)

#define TELEPORT_SHOP_DIR	"..\\Data\\ExData\\Events\\TeleportShop.ini"
// -------------------------------------------------------------------------------

struct TELEPORT_SHOP_TIME
{
	int Hour;
	int Min;
};
// -------------------------------------------------------------------------------

struct GC_SHOP_CLOSE	
{
	PBMSG_HEAD2 h;
	BYTE Close;
};
// -------------------------------------------------------------------------------

class TeleportShop
{
public:
	void Init();
	void Load();
	void TickTime();
	void EventStart();
	void EventEnd();
	void GC_CloseWindowShop();

	bool Enable;
	int EventTime;
	int Teleport_NPC;
	int Teleport_Map;
	int Teleport_X;
	int Teleport_Y;
	char MessageStart[100];
	char MessageEnd[100];

	int IndexNPC;

	int Tick;
	bool Start;
	
	TELEPORT_SHOP_TIME DataTime[10];
	int TimeLoaded;
};
extern TeleportShop g_TeleportShop;
// -------------------------------------------------------------------------------
#endif