#include "stdafx.h"
#include ".\\DbSet\\DBConBase.h"
#include "..\\include\\prodef.h"
//#include "winutil.h"
#include "MainFrm.h"
#include "ItemMarket.h"

#if(DEV_PLAYERSHOP)

CItemMarket g_ItemMarket;

CItemMarket::CItemMarket()
{
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

bool CItemMarket::Connect()
{
	bool Result = this->m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);

	if(Result)
	{
		//this->CreateTable();

		bool Result = this->m_DBItem.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);
	}

	return Result;
}

void CItemMarket::CreateTable()
{
	this->m_DBQuery.WriteLog = false;

	//this->m_DBQuery.Exec("ALTER TABLE [GameServerInfo] ADD [LoraBattleWin] varchar(10)");
	//this->m_DBQuery.Fetch();
	//this->m_DBQuery.Clear();

	//this->m_DBQuery.Exec("ALTER TABLE [Character] ADD [TvTKill] INT");
	//this->m_DBQuery.Fetch();
	//this->m_DBQuery.Clear();

	this->m_DBQuery.WriteLog = true;
}

void CItemMarket::Protocol(BYTE protoNum, BYTE *aRecv, int uIndex)
{
	switch(protoNum)
	{
	case 0x00:
		this->ReqItemList((SDHP_REQ_MARKET_ITEM *)aRecv, uIndex);
		break;
	case 0x01:
		this->SellItem((SDHP_SELL_MARKET_ITEM *)aRecv, uIndex);
		break;
	case 0x02:
		this->BuyItem((SDHP_BUY_MARKET_ITEM *)aRecv, uIndex);
		break;
	}
}

void CItemMarket::ReqItemList(SDHP_REQ_MARKET_ITEM* lpMsg, int uIndex)
{
	//if(!lpMsg->Result)
	//{
	//	return;
	//}
	
	char szQuery[256];
	int iReturnCode = 0;
	int iCount = 0;

	SDHP_ANS_MARKET_ITEM pMsg;
	memset(&pMsg, 0, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xEC, 0x00, sizeof(pMsg));
	pMsg.Result = 1;
	pMsg.aIndex = lpMsg->aIndex;
	
	sprintf(szQuery, "SELECT TOP %d id, name, price FROM ItemMarketData ORDER BY id DESC", MARKET_ITEM_MAX); // <<== Arg

	if(!this->m_DBQuery.Exec(szQuery))
	{
		this->m_DBQuery.Clear();
		pMsg.Result = 0;
	}	
	else
	{
		short sqlReturn = this->m_DBQuery.Fetch();

		while(sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
		{
			iReturnCode = this->m_DBQuery.GetInt(1);

			if(iReturnCode < 0)
			{
				break;
			}

			pMsg.Data[iCount].Name[10] = 0;

			this->m_DBQuery.GetStr("name", pMsg.Data[iCount].Name);

			pMsg.Data[iCount].Price = this->m_DBQuery.GetInt("price");

			// --

			int id = this->m_DBQuery.GetInt("id");

			sprintf(szQuery, "SELECT item FROM ItemMarketData WHERE id = %d", id);

			int	nRet = this->m_DBItem.ReadBlob(szQuery, pMsg.Data[iCount].Item);

			if(nRet < 0)
			{
				memset(pMsg.Data[iCount].Item, -1, sizeof(pMsg.Data[iCount].Item));
			}

			// --

			iCount++;

			if(iCount >= MARKET_ITEM_MAX)
			{
				break;
			}

			sqlReturn = this->m_DBQuery.Fetch();
		}

		this->m_DBQuery.Clear();
	}

	wsjServer.DataSend(uIndex, (char*)&pMsg, sizeof(pMsg));
}

void CItemMarket::SellItem(SDHP_SELL_MARKET_ITEM* lpMsg, int uIndex)
{
	char szQuery[256];

	sprintf(szQuery, "INSERT INTO ItemMarketData (account, name, price, date, status) VALUES ('%s', '%s', %d, '%s', %d)", 
		"ACCOUNT", "NAME", 0, 0, 0);

	this->m_DBQuery.Exec(szQuery);
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	SDHP_ANS_MARKET_ITEM pMsg;
	memset(&pMsg, 0, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xEC, 0x01, sizeof(pMsg));
	pMsg.Result = 1;
	pMsg.aIndex = lpMsg->aIndex;
	wsjServer.DataSend(uIndex, (char*)&pMsg, sizeof(pMsg));
}

void CItemMarket::BuyItem(SDHP_BUY_MARKET_ITEM* lpMsg, int uIndex)
{
	char szQuery[256];

	int iResult = lpMsg->Result;

	if(iResult)
	{
		sprintf(szQuery, "DELETE FROM Character WHERE account='%s' AND name='%s' AND id = %d",
			"ACCOUNT", "NAME", 0);

		if(!this->m_DBQuery.Exec(szQuery))
		{
			iResult = 0;
		}

		this->m_DBQuery.Clear();
	}

	SDHP_ANS_MARKET_ITEM pMsg;
	memset(&pMsg, 0, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xEC, 0x02, sizeof(pMsg));
	pMsg.Result = iResult;
	pMsg.aIndex = lpMsg->aIndex;
	wsjServer.DataSend(uIndex, (char*)&pMsg, sizeof(pMsg));

}

#endif