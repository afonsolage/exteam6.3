#include "StdAfx.h"
#include "BanSystem.h"
#include "MainFrm.h"

#if(DEV_BANSYSTEM)

CBanSystem g_BanSystem;

CBanSystem::CBanSystem()
{
}

CBanSystem::~CBanSystem()
{
}

bool CBanSystem::Connect()
{
	bool Result = this->m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);

	if(Result)
	{
		this->CreateTable();
	}

	return Result;
}

void CBanSystem::CreateTable()
{
	this->m_DBQuery.WriteLog = false;

	char szQuery[512] = "CREATE TABLE BanSystem (Name VARCHAR(10), Hdd INT NOT NULL default(0), Time INT NOT NULL default(0), Type INT NOT NULL default(0))";

	this->m_DBQuery.Exec(szQuery);
	this->m_DBQuery.Clear();

	this->m_DBQuery.WriteLog = true;
}

void CBanSystem::SelectTable(PMSG_REQ_BANSYSTEM* lpMsg, int pIndex)
{
	this->m_HddData.clear();
	
	char szQuery[512] = { 0 };

	sprintf(szQuery,"SELECT Name, Hdd, Time, Type FROM BanSystem");

	this->m_DBQuery.Exec(szQuery);

	short i = this->m_DBQuery.Fetch();

	while(i != SQL_NO_DATA && i != SQL_NULL_DATA)
	{
		int iReturnCode = this->m_DBQuery.GetInt(1);

		if(iReturnCode < 0)
		{
			break;
		}

		char szName[11] = { 0 };
		this->m_DBQuery.GetStr("Name", szName);

		BANHDD_DATA list;
		memcpy(list.Name, szName, sizeof(szName));
		list.Hdd = this->m_DBQuery.GetInt("Hdd");
		list.Time = this->m_DBQuery.GetInt("Time");
		list.Type = this->m_DBQuery.GetInt("Type");
		this->m_HddData.push_back(list);
		
		i = this->m_DBQuery.Fetch();
	}

	this->m_DBQuery.Clear();

	for(int i = 0; i < this->m_HddData.size(); i++)
	{
		BANHDD_DATA & ritem = this->m_HddData[i];

		PMSG_SELECT_BANSYSTEM pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x20, sizeof(pMsg));
		memcpy(pMsg.Name, ritem.Name, sizeof(pMsg.Name));
		pMsg.Hdd = ritem.Hdd;
		pMsg.Time = ritem.Time;
		pMsg.Type = ritem.Type;
		wsjServer.DataSend(pIndex, (char*)&pMsg, pMsg.h.size);
	}
}

void CBanSystem::Insert(PMSG_INSERT_BANSYSTEM* lpMsg)
{
	char szQuery[256] = { 0 };	

	sprintf(szQuery,"SELECT Name, Hdd, Time, Type FROM BanSystem FROM Name = '%s'", lpMsg->Name);

	if(!this->m_DBQuery.Exec(szQuery) || this->m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		this->m_DBQuery.Clear();

		sprintf(szQuery, "INSERT INTO BanSystem (Name, Hdd, Time, Type) VALUES ('%s', %u, %d, %d)", lpMsg->Name, lpMsg->Hdd, lpMsg->Time, lpMsg->Type);
		this->m_DBQuery.Exec(szQuery);
		this->m_DBQuery.Clear();
	}
	else
	{
		this->m_DBQuery.Clear();

		sprintf(szQuery, "UPDATE BanSystem SET Hdd = '%u', Time = %d, Type = %d WHERE Name = '%s'", lpMsg->Hdd, lpMsg->Time, lpMsg->Type, lpMsg->Name);
		this->m_DBQuery.Exec(szQuery);
		this->m_DBQuery.Clear();
	}
}

void CBanSystem::Delete(PMSG_DELETE_BANSYSTEM* lpMsg)
{
	char szQuery[256] = { 0 };	
	sprintf(szQuery, "DELETE FROM BanSystem WHERE Name = '%s'", lpMsg->Name);
	this->m_DBQuery.Exec(szQuery);
	this->m_DBQuery.Clear();
}


#endif

