#include "StdAfx.h"
#include "SpotReturn.h"
#include "MainFrm.h"
#include "ExLicense.h"
// ----------------------------------------------------------------------------------------------
#if(CUSTOM_RETURNSPOT==TRUE)
SpotReturn g_SpotReturn;
// ----------------------------------------------------------------------------------------------

SpotReturn::SpotReturn()
{
}
// ----------------------------------------------------------------------------------------------

SpotReturn::~SpotReturn()
{
}
// ----------------------------------------------------------------------------------------------

bool SpotReturn::Connect()
{
	return m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);
}
// ----------------------------------------------------------------------------------------------

void SpotReturn::GDStatus(PMSG_GD_SPOTSTATUS* lpMsg, int pIndex)
{
	if(!g_ExLicense.user.SpotReturn)
	{
		return;
	}

	if(!lpMsg)
	{
		return;
	}

	CString Query;

	BYTE Status = 0;
	char szName[10];
	ZeroMemory(szName, sizeof(szName));
	strncpy(szName, lpMsg->szCharName, 10);

	Query.Format("SELECT StatusSpot FROM Character WHERE Name = '%s'", szName);

	if(m_DBQuery.Exec(Query) == FALSE )
	{
		m_DBQuery.Clear();
		return;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return;
	}

	Status = m_DBQuery.GetInt("StatusSpot");

	m_DBQuery.Clear();

	PMSG_DG_SPOTSTATUS pMsg = { 0 };
	pMsg.h.set((LPBYTE)&pMsg, 0xE5, 0x00, sizeof(PMSG_DG_SPOTSTATUS));
	pMsg.GetStatus = Status;
	pMsg.Number = lpMsg->Number;
	memcpy(pMsg.szCharName, lpMsg->szCharName, 11);
	wsjServer.DataSend(pIndex, (char*)&pMsg, sizeof(pMsg));
}
// ----------------------------------------------------------------------------------------------

void SpotReturn::GDStatusUpdate(PMSG_GD_SPOTSTATUS_UPDATE* lpMsg)
{
	if(!g_ExLicense.user.SpotReturn)
	{
		return;
	}

	if(!lpMsg)
	{
		return;
	}

	CString qSql;

	char szName[10];
	ZeroMemory(szName, sizeof(szName));
	strncpy(szName, lpMsg->szCharName, 10);

	qSql.Format("UPDATE Character SET StatusSpot=%d WHERE Name = '%s'", lpMsg->GetStatus, szName);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return;
	}
}
// ----------------------------------------------------------------------------------------------


#endif