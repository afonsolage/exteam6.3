#pragma once

#if(CUSTOM_PICKUP_ITEM_INFO)

#include "..\\common\\zzzitem.h"
#include "..\\common\\winutil.h"

struct PMSG_REQ_PICKUP_INFO
{
	PBMSG_HEAD2 h;
	DWORD ItemNum;
};

struct PMSG_ANS_PICKUP_INFO
{
	PBMSG_HEAD2 h;
	BYTE result;
	short Type;
	float Durability;
	BYTE Data[MAX_ITEM_INFO];
};

class CPickUpItemInfo
{
public:
		CPickUpItemInfo();
		~CPickUpItemInfo();

	void Init();
	void Load();
	void InfoRecv(PMSG_REQ_PICKUP_INFO* lpMsg, int aIndex);
};

extern CPickUpItemInfo g_PickUpItemInfo;

#endif