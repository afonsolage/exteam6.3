#include "stdafx.h"
#include "..\\include\\prodef.h"
#include "DBSockMng.h"
#include "giocp.h"
#include "..\\common\\zzzitem.h"
#include "ItemMarket.h"

#if(DEV_PLAYERSHOP)

CItemMarket g_ItemMarket;

CItemMarket::CItemMarket()
{
	this->Init();
}

CItemMarket::~CItemMarket()
{
}

void CItemMarket::Init()
{

}

void CItemMarket::Load()
{

}

void CItemMarket::Protocol(BYTE protoNum, BYTE *aRecv)
{
	switch(protoNum)
	{
	case 0x00:
		this->RecvItemList((SDHP_ANS_MARKET_ITEM *) aRecv);
		break;
	case 0x01:
		this->SellResult((SDHP_SELL_MARKET_RESULT*) aRecv);
		break;
	case 0x02:
		this->BuyResult((SDHP_BUY_MARKET_RESULT*) aRecv);
		break;
	}
}

void CItemMarket::ReqItemList(int aIndex, int NumPage)
{
	SDHP_REQ_MARKET_ITEM pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEC, 0x00, sizeof(pMsg));
	pMsg.Result = 1;
	pMsg.Page = NumPage;
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CItemMarket::RecvItemList(SDHP_ANS_MARKET_ITEM* lpMsg)
{
	int aIndex = lpMsg->aIndex;
	
	CItem lpItem[MARKET_ITEM_MAX];
	BYTE btItem[MAX_ITEM_INFO];

	PMSG_SEND_MARKET_ITEM pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xBF, sizeof(pMsg));

	//BYTE btSockOpt[5] = {0xFE,0xFE,0xFE,0xFE,0xFE};
	//lpItem.Convert(lpMsg->Type,lpMsg->Op1, lpMsg->Op2, lpMsg->Op3,lpMsg->NewOption, lpMsg->SetOption,0, btSockOpt, 0xFF, 0, CURRENT_DB_VERSION);

	//ItemByteConvert16((LPBYTE)pCSave.dbInventory , lpObj->pInventory, INVENTORY_SIZE);
	//ItemByteConvert16((LPBYTE)&pMsg.Info, gObj[aIndex].pWarehouse, WAREHOUSE_SIZE);


	//ItemByteConvert((LPBYTE)&ItemInfo[0], lpItem[0]);

	//pMsg.result = 1;
	//pMsg.Type = lpItem->m_Type;
	//pMsg.Durability = lpItem->m_Durability;

	//ItemByteConvert((LPBYTE)&pMsg.Data[0], 
	//	lpItem->m_Type, 
	//	lpItem->m_Option1, 
	//	lpItem->m_Option2,	
	//	lpItem->m_Option3, 
	//	(BYTE)lpItem->m_Level, 
	//	(BYTE)lpItem->m_Durability, 
	//	lpItem->m_NewOption, 
	//	lpItem->m_SetOption, 
	//	lpItem->m_JewelOfHarmonyOption, 
	//	lpItem->m_ItemOptionEx, 
	//	lpItem->m_SocketOption, 
	//	(BYTE)lpItem->m_SocketOptionIndex, 0);

	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

// ----

void CItemMarket::SellItem(int aIndex)
{
	SDHP_REQ_MARKET_ITEM pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEC, 0x00, sizeof(pMsg));
	pMsg.Result = 1;
	pMsg.aIndex = aIndex;
	pMsg.Page = 0;
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}


void CItemMarket::SellResult(SDHP_SELL_MARKET_RESULT* lpMsg)
{

}

// ----

void CItemMarket::BuyItem(int aIndex)
{
	SDHP_REQ_MARKET_ITEM pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEC, 0x00, sizeof(pMsg));
	pMsg.Result = 1;
	pMsg.aIndex = aIndex;
	pMsg.Page = 0;
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}


void CItemMarket::BuyResult(SDHP_BUY_MARKET_RESULT* lpMsg)
{

}


#endif