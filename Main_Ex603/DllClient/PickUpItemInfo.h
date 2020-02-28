#pragma once

#include "stdafx.h"
#include "Protocol.h"
#include "Object.h"
#include "PostItem.h"

#if(CUSTOM_PICKUP_ITEM_INFO)

#define pItemPosNum		*(int*)0xE61728

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
	void InfoSend();
	void InfoRecv(PMSG_ANS_PICKUP_INFO* lpMsg);
	void Draw();
	int CheckItemInfo(signed int a1);

	DWORD m_dwItemRecv;

	ObjectItem m_Data;
};

extern CPickUpItemInfo g_PickUpItemInfo;

#endif