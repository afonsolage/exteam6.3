#include "stdafx.h"
#include "PickUpItemInfo.h"
#include "..\\common\\winutil.h"
#include "GameMain.h"
#include "ExLicense.h"

#if(CUSTOM_PICKUP_ITEM_INFO)

CPickUpItemInfo g_PickUpItemInfo;

CPickUpItemInfo::CPickUpItemInfo()
{
}

CPickUpItemInfo::~CPickUpItemInfo()
{
}

void CPickUpItemInfo::Init()
{
}

void CPickUpItemInfo::Load()
{
	this->Init();
}

void CPickUpItemInfo::InfoRecv(PMSG_REQ_PICKUP_INFO* lpMsg, int aIndex)
{
	if(!g_ExLicense.user.PickUpItemInfo)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	PMSG_ANS_PICKUP_INFO pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xBF, sizeof(pMsg));

	int item_num = lpMsg->ItemNum;

	if ( MAX_ITEM_TYPE_RANGE(item_num) == FALSE )
	{
		pMsg.result = 0;
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	int map_num = gObj[aIndex].MapNumber;

	if ( MAX_MAP_RANGE(map_num) == FALSE )
	{
		pMsg.result = 0;
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	CMapItem * lpItem = &MapC[map_num].m_cItem[item_num];

	pMsg.result = 1;

	pMsg.Type = lpItem->m_Type;
	pMsg.Durability = lpItem->m_Durability;

	ItemByteConvert((LPBYTE)&pMsg.Data[0], 
		lpItem->m_Type, 
		lpItem->m_Option1, 
		lpItem->m_Option2,	
		lpItem->m_Option3, 
		(BYTE)lpItem->m_Level, 
		(BYTE)lpItem->m_Durability, 
		lpItem->m_NewOption, 
		lpItem->m_SetOption, 
		lpItem->m_JewelOfHarmonyOption, 
		lpItem->m_ItemOptionEx, 
		lpItem->m_SocketOption, 
		(BYTE)lpItem->m_SocketOptionIndex, 0);

	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}


#endif