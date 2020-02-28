#include "StdAfx.h"
#include "MainFrm.h"
#include "ExWebManager.h"
#include "ServerPrc.h"

CExWebManager g_ExWebManager;

CExWebManager::CExWebManager()
{

}

CExWebManager::~CExWebManager()
{

}

bool CExWebManager::Connect()
{
	bool Result = this->m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);

	Result = m_MEMBQuery.Connect(3, szDbConnectMemb, szDbConnectID, szDbConnectPass);

	if(!Result)
	{
		MsgBox("MEMB_INFO DB Connect Fail");
	}

	return Result;
}

void CExWebManager::Protocol(BYTE protoNum, BYTE *aRecv, int uIndex)
{
	//LogAddC(2, "%s", (char*)aRecv);
	switch(protoNum)
	{
	case 0x00:
		this->GameShopUpdate((GAMESHOP_WEB_UPDATE *)aRecv, uIndex);
		break;
	case 0x01:
		this->CreditsUpdate((CREDIT_WEB_UPDATE *)aRecv, uIndex);
		break;
	}
}

void CExWebManager::GameShopUpdate(GAMESHOP_WEB_UPDATE* lpMsg, int uIndex)
{
	bool Result = false;
	char szQuery[256];

	sprintf(szQuery, "UPDATE GameShopPoint SET WCoinC = %d, WCoinP = %d, GoblinPoint = %d WHERE AccountID = '%s'", 
		lpMsg->WCoinC, lpMsg->WCoinP, lpMsg->GoblinPoint, lpMsg->AccountID);

	if(this->m_DBQuery.Exec(szQuery))
	{
		if(this->m_DBQuery.GetAffectCount() > 0)
		{
			Result = true;
		}
	}

	this->m_DBQuery.Clear();

	wsjServer.DataSend(uIndex, (char*)&Result, sizeof(Result));

	if(!Result)
	{
		return;
	}

	GAMESHOP_WEB_UPDATE pMsg = { 0 };
	pMsg.h.set((LPBYTE)&pMsg, 0xEE, 0x00, sizeof(pMsg));
	memcpy(pMsg.AccountID, lpMsg->AccountID, MAX_IDSTRING);
	pMsg.WCoinC = lpMsg->WCoinC;
	pMsg.WCoinP = lpMsg->WCoinP;
	pMsg.GoblinPoint = lpMsg->GoblinPoint;

	for(int i = 0; i < MAX_SERVEROBJECT; i++)
    {
		if(gSObj[i].Connected != 0 && uIndex != i)
		{
			wsjServer.DataSend(i, (char*)&pMsg, pMsg.h.size);
		}
    }
}

void CExWebManager::CreditsUpdate(CREDIT_WEB_UPDATE* lpMsg, int uIndex)
{
	bool Result = false;
	char szQuery[256];

	sprintf(szQuery, "UPDATE MEMB_INFO SET ExCredit = %d WHERE memb___id = '%s'", 
		lpMsg->Credit, lpMsg->AccountID);

	//if(this->m_DBQuery.Exec(szQuery))
	//{
	//	if(this->m_DBQuery.GetAffectCount() > 0)
	//	{
	//		Result = true;
	//	}
	//}

	//this->m_DBQuery.Clear();

	if(this->m_MEMBQuery.Exec(szQuery))
	{
		if(this->m_MEMBQuery.GetAffectCount() > 0)
		{
			Result = true;
		}
	}

	this->m_MEMBQuery.Clear();

	

	wsjServer.DataSend(uIndex, (char*)&Result, sizeof(Result));

	if(!Result)
	{
		return;
	}

	CREDIT_WEB_UPDATE pMsg = { 0 };
	pMsg.h.set((LPBYTE)&pMsg, 0xEE, 0x01, sizeof(pMsg));
	memcpy(pMsg.AccountID, lpMsg->AccountID, MAX_IDSTRING);
	pMsg.Credit = lpMsg->Credit;

	for(int i = 0; i < MAX_SERVEROBJECT; i++)
    {
		if(gSObj[i].Connected != 0 && uIndex != i)
		{
			wsjServer.DataSend(i, (char*)&pMsg, pMsg.h.size);
		}
    }
}

void CExWebManager::ReqCredit(CREDIT_WEB_REQ* lpMsg)
{
	CREDIT_WEB_REQ pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEE, 0x02, sizeof(pMsg));


}