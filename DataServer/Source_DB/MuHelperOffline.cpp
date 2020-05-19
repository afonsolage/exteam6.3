#include "stdafx.h"
#include "MuHelperOffline.h"
#include "ServerPrc.h"
#include "MainFrm.h"

CMUHelperOffline g_MUHelperOffline;

bool CMUHelperOffline::Connect()
{
	bool Result = this->m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);

	if (Result)
	{
		this->CreateTable();
	}

	return Result;
}

void CMUHelperOffline::CreateTable()
{
	this->m_DBQuery.WriteLog = false;

	char szQuery[512] = "CREATE TABLE MUHelperOffline ( AccountID VARCHAR(10) NOT NULL, Name	VARCHAR(10) NOT NULL, Active	TINYINT		NOT NULL DEFAULT 0, Offline TINYINT		NOT NULL DEFAULT 0)";

	this->m_DBQuery.Exec(szQuery);
	this->m_DBQuery.Clear();

	this->m_DBQuery.WriteLog = true;
}

void CMUHelperOffline::GDReqAllData(int uIndex)
{
	int ServerCode = gSObj[uIndex].ServerCode;

	char szQuery[512] = { 0 };
	sprintf(szQuery, "EXEC MUHELPER_OFFLINE_RESTORE %d", ServerCode);

	this->m_DBQuery.Exec(szQuery);

	short i = this->m_DBQuery.Fetch();

	while (i != SQL_NO_DATA && i != SQL_NULL_DATA)
	{
		int iReturnCode = this->m_DBQuery.GetInt(1);

		if (iReturnCode < 0)
		{
			break;
		}

		MUHELPEROFF_RESTORE_DATA data = { 0 };
		this->m_DBQuery.GetStr("AccountID", data.AccountID);
		this->m_DBQuery.GetStr("memb__pwd", data.Password);
		this->m_DBQuery.GetStr("Name", data.Name);
		data.PcID = (DWORD)this->m_DBQuery.GetInt("PcID");
		data.StartTime = (DWORD)this->m_DBQuery.GetInt("StartTime");
		data.ServerIndex = uIndex;

		this->m_restoreStack.push(data);

		i = this->m_DBQuery.Fetch();
	}

	this->m_DBQuery.Clear();
}

void CMUHelperOffline::DGSendRestoreData(MUHELPEROFF_RESTORE_DATA data)
{
	PMSG_RESTORE_DATA pMsg = { 0 };
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x24, sizeof(pMsg));
	memcpy(pMsg.AccountID, data.AccountID, MAX_IDSTRING);
	memcpy(pMsg.Password, data.Password, MAX_IDSTRING);
	memcpy(pMsg.Name, data.Name, MAX_IDSTRING);
	pMsg.PcID = data.PcID;
	pMsg.StartTime = data.StartTime;

	wsjServer.DataSend(data.ServerIndex, (char*)&pMsg, pMsg.h.size);
}

void CMUHelperOffline::Tick()
{
	if (this->m_restoreStack.empty()) return;

	auto now = GetTickCount();

	if (m_nextTick > now) return;

	DGSendRestoreData(this->m_restoreStack.front());
	this->m_restoreStack.pop();

	m_nextTick = now + RESTORE_INTERVAL;
}

void CMUHelperOffline::GDReqUpdateData(PMSG_SAVE_MUHELPEROFF_DATA * lpMsg, int uIndex)
{
	int ServerCode = gSObj[uIndex].ServerCode;

	char szQuery[512] = { 0 };
	sprintf(szQuery, "EXEC MUHELPER_OFFLINE_SAVE '%s','%s',%d,%d,%d,%d,%d", lpMsg->data.AccountID, lpMsg->data.Name, lpMsg->data.Active, lpMsg->data.PcID, lpMsg->data.StartTime, lpMsg->data.Offline, ServerCode);

	this->m_DBQuery.Exec(szQuery);
	this->m_DBQuery.Clear();
}
