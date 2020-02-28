#include "StdAfx.h"
#include "AccountSecurity.h"
#include "MainFrm.h"

CAccountSecurity g_AccountSecurity;

CAccountSecurity::CAccountSecurity()
{
}

CAccountSecurity::~CAccountSecurity()
{
}

bool CAccountSecurity::Connect()
{
	bool Result = this->m_MEMBQuery.Connect(3, szDbConnectMemb, szDbConnectID, szDbConnectPass);

	if(!Result)
	{
		MsgBox("MEMB_INFO DB Connect Fail");
	}
	else
	{
		this->m_MEMBQuery.WriteLog = false;

		this->m_MEMBQuery.Exec("ALTER TABLE [MEMB_INFO] ADD [ActivePCID] INT NOT NULL default(0)");
		this->m_MEMBQuery.Fetch();
		this->m_MEMBQuery.Clear();
		this->m_MEMBQuery.Exec("ALTER TABLE [MEMB_INFO] ADD [ProtectPCID] BIGINT NOT NULL default(0)");
		this->m_MEMBQuery.Fetch();
		this->m_MEMBQuery.Clear();
		this->m_MEMBQuery.Exec("ALTER TABLE [MEMB_INFO] ADD [SecretNumber] INT NOT NULL default(0)");
		this->m_MEMBQuery.Fetch();
		this->m_MEMBQuery.Clear();
		this->m_MEMBQuery.Exec("ALTER TABLE [MEMB_INFO] ADD [AccountData] VARBINARY(10)");
		this->m_MEMBQuery.Fetch();
		this->m_MEMBQuery.Clear();

		this->m_MEMBQuery.WriteLog = true;
	}

	return Result;
}

void CAccountSecurity::Protocol(BYTE protoNum, BYTE *aRecv, int uIndex)
{
	switch(protoNum)
	{
	case 0x00:
		this->GDReqLoad((PMSG_REQ_ACC_DATABASE_LOAD *)aRecv, uIndex);
		break;
	case 0x01:
		this->GDReqSave((PMSG_REQ_ACC_DATABASE_SAVE *)aRecv, uIndex);
		break;
	}
}

void CAccountSecurity::GDReqLoad(PMSG_REQ_ACC_DATABASE_LOAD* lpMsg, int uIndex)
{
	char szQuery[256];
	char szAccount[11];
	BYTE btBufferOption[10];

	memset(btBufferOption, 0, sizeof(btBufferOption));

	PMSG_ANS_ACC_DATABASE_LOAD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEF, 0x00, sizeof(pMsg));
	pMsg.Result = true;
	pMsg.aIndex = lpMsg->aIndex;

	szAccount[10] = 0;
	memcpy(szAccount, lpMsg->Account, sizeof(szAccount)-1);

	sprintf(szQuery, "SELECT ActivePCID, ProtectPCID, SecretNumber FROM MEMB_INFO WHERE memb___id = '%s'", szAccount);

	if(this->m_MEMBQuery.Exec(szQuery) == FALSE || this->m_MEMBQuery.Fetch() == SQL_NO_DATA)
	{
		pMsg.Result = false;
		this->m_MEMBQuery.Clear();
	}

	if(pMsg.Result == true)
	{
		pMsg.ActivePCID = this->m_MEMBQuery.GetInt("ActivePCID");
		pMsg.ProtectPCID = this->m_MEMBQuery.GetInt64("ProtectPCID");
		pMsg.SecretNumber = this->m_MEMBQuery.GetInt("SecretNumber");	
		this->m_MEMBQuery.Clear();
	}

	sprintf(szQuery, "SELECT AccountData FROM MEMB_INFO WHERE memb___id = '%s'", szAccount);

	this->m_MEMBQuery.ReadBlob(szQuery, btBufferOption);

	pMsg.OnlyMyPC = btBufferOption[0];
	pMsg.Trade = btBufferOption[1];
	pMsg.Inventory = btBufferOption[2];
	pMsg.Werehouse = btBufferOption[3];
	pMsg.DisconnectFriend = btBufferOption[4];
	pMsg.SellChar = btBufferOption[5];

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);

}

void CAccountSecurity::GDReqSave(PMSG_REQ_ACC_DATABASE_SAVE* lpMsg, int uIndex)
{
	char szQuery[256];
	char szAccount[11];
	BYTE btBufferOption[10];

	memset(btBufferOption, 0, sizeof(btBufferOption));

	btBufferOption[0] = lpMsg->OnlyMyPC;
	btBufferOption[1] = lpMsg->Trade;
	btBufferOption[2] = lpMsg->Inventory;
	btBufferOption[3] = lpMsg->Werehouse;
	btBufferOption[4] = lpMsg->DisconnectFriend;
	btBufferOption[5] = lpMsg->SellChar;

	PMSG_ANS_ACC_DATABASE_SAVE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEF, 0x01, sizeof(pMsg));
	pMsg.aIndex = lpMsg->aIndex;
	pMsg.Result = true;

	szAccount[10] = 0;
	memcpy(szAccount, lpMsg->Account, sizeof(szAccount)-1);

	sprintf(szQuery, "UPDATE MEMB_INFO SET ActivePCID = %d, ProtectPCID = %u, SecretNumber = %d WHERE memb___id = '%s'", lpMsg->ActivePCID, lpMsg->ProtectPCID, lpMsg->SecretNumber, szAccount);

	if(this->m_MEMBQuery.Exec(szQuery) == FALSE)
	{
		pMsg.Result = false;
	}

	sprintf(szQuery, "UPDATE MEMB_INFO SET AccountData = ? WHERE memb___id = '%s'", szAccount);

	this->m_MEMBQuery.WriteBlob(szQuery, btBufferOption, 10);

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}
