#include "StdAfx.h"
#include "winutil.h"
#include "MainFrm.h"
#include "GuildBank.h"

CGuildBank g_GuildBank;

bool CGuildBank::Connect()
{
	bool Result = this->m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);

	if(Result)
	{
		this->CreateTable();
	}

	return Result;
}

void CGuildBank::CreateTable()
{
	char szQuery[1024];

	this->m_DBQuery.WriteLog = false;

	this->m_DBQuery.Exec("CREATE TABLE [dbo].[GuildWarehouse]([G_Name] [varchar](10) NOT NULL,[Items] [varbinary](3840) NULL, [Money] [int] NULL,[EndUseDate] [smalldatetime] NULL,[DbVersion] [tinyint] NULL,[pw] [smallint] NULL) ON [PRIMARY]");
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("ALTER TABLE [dbo].[GuildWarehouse] ADD  DEFAULT (0) FOR [Money]");
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("ALTER TABLE [dbo].[GuildWarehouse] ADD  DEFAULT (0) FOR [DbVersion]");
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("ALTER TABLE [dbo].[GuildWarehouse] ADD  DEFAULT (0) FOR [pw]");
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("alter table [GuildWarehouse] add [Items2] varbinary(3840)");
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("alter table [GuildWarehouse] add [Items3] varbinary(3840)");
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("alter table [GuildWarehouse] add [Items4] varbinary(3840)");
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("alter table [GuildWarehouse] add [Items5] varbinary(3840)");
	this->m_DBQuery.Clear();
		
	this->m_DBQuery.WriteLog = true;
}

void CGuildBank::DGGetGuildWarehouseList(int aIndex, SDHP_GETGUILDWAREHOUSEDB * aRecv)
{
	char szQuery[256];

	char szAccountID[11]={0};
	memcpy(szAccountID, aRecv->AccountID, 10);
	char Guild[11]={0};
	memcpy(Guild, aRecv->G_Name, 10);

	SDHP_GETUSERWAREHOUSEDB_SAVE pResult;

	memset(pResult.dbItems, -1, sizeof(pResult.dbItems));

	PHeadSetW((LPBYTE)&pResult, Protocol_GSRecv_GetGuildWarehouseList, sizeof(pResult));
	memcpy(pResult.AccountID, szAccountID, 10);
	pResult.aIndex = aRecv->aIndex;
	pResult.Number = aRecv->Number;//

	sprintf(szQuery, "SELECT G_Name FROM GuildWarehouse WHERE G_Name='%s'", Guild);

	BOOL bRet = this->m_DBQuery.Exec(szQuery);
	
	if(this->m_DBQuery.Fetch() == SQL_NO_DATA || bRet == FALSE)
	{
		this->m_DBQuery.Clear();

		sprintf(szQuery, "INSERT INTO GuildWarehouse (G_Name, Money, EndUseDate, DbVersion) VALUES ('%s',0, getdate(), 3)", Guild);

		this->m_DBQuery.Exec(szQuery);
		this->m_DBQuery.Fetch();
		this->m_DBQuery.Clear();

		SDHP_GETGUILDWAREHOUSEDB_RESULT pMsg;

		PHeadSetB((LPBYTE)&pMsg, Protocol_GSRecv_GetWarehouseNoItem, sizeof(pMsg));
		pMsg.aIndex = aRecv->aIndex;
		memcpy(pMsg.AccountID, szAccountID, 10);

		wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
		return;
	}

	this->m_DBQuery.Clear();

	sprintf(szQuery, "SELECT Money, DbVersion, pw FROM GuildWarehouse WHERE G_Name='%s'", Guild);

	this->m_DBQuery.Exec(szQuery);
	this->m_DBQuery.Fetch();

	pResult.Money = this->m_DBQuery.GetInt("Money");
	pResult.DbVersion = this->m_DBQuery.GetInt("DbVersion");
	pResult.pw = this->m_DBQuery.GetInt("pw");
	
	this->m_DBQuery.Clear();

	//wsprintf(szQuery, "SELECT Items FROM GuildWarehouse WHERE G_Name='%s'",Guild);	

	if (aRecv->Number == 0)
	{
		wsprintf(szQuery, "SELECT Items FROM GuildWarehouse WHERE G_Name='%s'",Guild);	
	}
	else if (aRecv->Number == 1)
	{
		wsprintf(szQuery, "SELECT Items2 FROM GuildWarehouse WHERE G_Name='%s'",Guild);	
	}
	else if (aRecv->Number == 2)
	{
		wsprintf(szQuery, "SELECT Items3 FROM GuildWarehouse WHERE G_Name='%s'",Guild);	
	}
	else if (aRecv->Number == 3)
	{
		wsprintf(szQuery, "SELECT Items4 FROM GuildWarehouse WHERE G_Name='%s'",Guild);	
	}
	else if (aRecv->Number == 4)
	{
		wsprintf(szQuery, "SELECT Items5 FROM GuildWarehouse WHERE G_Name='%s'",Guild);	
	}
	else
	{
		wsprintf(szQuery, "SELECT Items FROM GuildWarehouse WHERE G_Name='%s'",Guild);	
	}

	int	nRet = this->m_DBQuery.ReadBlob(szQuery, pResult.dbItems);

	if(nRet < 0)
	{
		memset(pResult.dbItems, -1, sizeof(pResult.dbItems));
	}
	
	this->m_DBQuery.Clear();

	wsjServer.DataSend(aIndex, (char*)&pResult, sizeof(pResult));
}

void CGuildBank::GDSetGuildWarehouseList(SDHP_GETGUILDWAREHOUSEDB_SAVE * aRecv)
{
	char szQuery[256];
	char szAccountID[11]={0};
	memcpy(szAccountID, aRecv->AccountID, 10);
	char Guild[11]={0};
	memcpy(Guild, aRecv->G_Name, 10);

	sprintf(szQuery, "UPDATE GuildWarehouse SET Money=%d, pw=%d, DbVersion=%d WHERE G_Name='%s'",
		aRecv->Money, aRecv->pw, aRecv->DbVersion, Guild);

	this->m_DBQuery.Exec(szQuery);
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	//wsprintf(szQuery, "UPDATE GuildWarehouse SET Items=? WHERE G_Name='%s'", Guild);

	if (aRecv->Number == 0)
	{
		wsprintf(szQuery, "UPDATE GuildWarehouse SET Items=? WHERE G_Name='%s'", Guild);
	}
	else if (aRecv->Number == 1)
	{
		wsprintf(szQuery, "UPDATE GuildWarehouse SET Items2=? WHERE G_Name='%s'", Guild);
	}
	else if (aRecv->Number == 2)
	{
		wsprintf(szQuery, "UPDATE GuildWarehouse SET Items3=? WHERE G_Name='%s'", Guild);
	}
	else if (aRecv->Number == 3)
	{
		wsprintf(szQuery, "UPDATE GuildWarehouse SET Items4=? WHERE G_Name='%s'", Guild);
	}
	else if (aRecv->Number == 4)
	{
		wsprintf(szQuery, "UPDATE GuildWarehouse SET Items5=? WHERE G_Name='%s'", Guild);
	}
	else
	{
		wsprintf(szQuery, "UPDATE GuildWarehouse SET Items=? WHERE G_Name='%s'", Guild);
	}

	this->m_DBQuery.WriteBlob(szQuery, aRecv->dbItems, sizeof(aRecv->dbItems));
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();
}

void CGuildBank::GDDelGuildWarehouseList(SDHP_GETGUILDWAREHOUSEDB * aRecv)
{
	char szQuery[256];
	char szAccountID[11]={0};
	memcpy(szAccountID, aRecv->AccountID, 10);
	char Guild[11]={0};
	memcpy(Guild, aRecv->G_Name, 10);

	sprintf(szQuery, "DELETE FROM GuildWarehouse where G_Name='%s'", Guild);
	this->m_DBQuery.Exec(szQuery);
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();
}