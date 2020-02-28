#include "StdAfx.h"
#include "Marriage.h"
#include "MainFrm.h"

CMarriage g_Marriage;

CMarriage::CMarriage()
{
}

CMarriage::~CMarriage()
{
}

bool CMarriage::Connect()
{
	bool Result = m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);

	if(Result)
	{
		this->CreateTable();
	}

	return Result;
}

void CMarriage::CreateTable()
{
	m_DBQuery.WriteLog = false;
	m_DBQuery.Exec("CREATE TABLE Marriage(Name1 varchar(10), Name2 varchar(10))");
	m_DBQuery.Fetch();
	m_DBQuery.Clear();
	m_DBQuery.WriteLog = true;
}

void CMarriage::GDLoad(PMSG_REQ_MARRIAGE_LOAD* aRecv, int uIndex)
{
	CString Query;

	char szName[11];
	memcpy(szName, aRecv->szName, sizeof(szName)-1);
	szName[10] = 0;

	if(aRecv->bClass == 0)
	{
		Query.Format("SELECT * FROM Marriage WHERE Name1 = '%s'", szName);
	}
	else
	{
		Query.Format("SELECT * FROM Marriage WHERE Name2 = '%s'", szName);
	}

	if(m_DBQuery.Exec(Query) == FALSE || m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return;
	}	

	PMSG_ANS_MARRIAGE_LOAD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x00, sizeof(pMsg));
	pMsg.aIndex = aRecv->aIndex;

	if(aRecv->bClass == 0)
	{
		m_DBQuery.GetStr("Name2", pMsg.szMarriageName);
	}
	else
	{
		m_DBQuery.GetStr("Name1", pMsg.szMarriageName);
	}

	m_DBQuery.Clear();
	
	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CMarriage::GDInset(PMSG_REQ_MARRIAGE_INSERT* aRecv, int uIndex)
{
	CString InsertQuery;

	PMSG_ANS_MARRIAGE_INSERT pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x01, sizeof(pMsg));
	pMsg.bResult = true;
	pMsg.aIndex1 = aRecv->aIndex1;
	pMsg.aIndex2 = aRecv->aIndex2;

	char szName1[11];
	memcpy(szName1, aRecv->szName1, sizeof(szName1)-1);
	szName1[10] = 0;

	char szName2[11];
	memcpy(szName2, aRecv->szName2, sizeof(szName2)-1);
	szName2[10] = 0;

	InsertQuery.Format("INSERT INTO Marriage (Name1, Name2) VALUES ('%s', '%s')", szName1, szName2);

	if(!m_DBQuery.Exec(InsertQuery))
	{
		LogAdd("[%s] Failed to insert new values", __FUNCTION__);
		pMsg.bResult = false;
	}

	m_DBQuery.Clear();	

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CMarriage::GDDelete(PMSG_REQ_MARRIAGE_DELETE* aRecv, int uIndex)
{
	if(strlen(aRecv->szName) < 1)
	{
		return;
	}

	CString qSql;

	PMSG_ANS_MARRIAGE_DELETE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x02, sizeof(pMsg));
	pMsg.aIndex = aRecv->aIndex;
	pMsg.bResult = true;

	char szName[11];
	memcpy(szName, aRecv->szName, sizeof(szName)-1);
	szName[10] = 0;

	if(aRecv->bClass == 0)
	{
		qSql.Format("DELETE FROM Marriage WHERE Name1='%s'", szName);
	}
	else
	{
		qSql.Format("DELETE FROM Marriage WHERE Name2='%s'", szName);
	}

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		pMsg.bResult = false;
		LogAdd("[%s] Failed to delete new values", __FUNCTION__);
	}

	m_DBQuery.Clear();

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}
