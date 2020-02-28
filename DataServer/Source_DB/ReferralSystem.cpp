#include "stdafx.h"
#include "ReferralSystem.h"
#include "MainFrm.h"

#if(CUSTOM_REFERAL_SYSTEM)

CReferralSystem g_ReferralSystem;

CReferralSystem::CReferralSystem()
{
	memset(this->szTableName, 0, sizeof(this->szTableName));
	memset(this->szColumnName, 0, sizeof(this->szColumnName));
}

CReferralSystem::~CReferralSystem()
{
}

void CReferralSystem::Load()
{
	this->Read(".\\ReferralSystem.ini");
}

void CReferralSystem::Read(char* filename)
{
	GetPrivateProfileString("Referral", "TableName", "MEMB_INFO", this->szTableName, 64, filename);
	GetPrivateProfileString("Referral", "ColumnName", "RefferalName", this->szColumnName, 64, filename);
}

bool CReferralSystem::Connect()
{
	this->Load();

	bool Result = this->m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);
	Result = this->m_MEMBQuery.Connect(3, szDbConnectMemb, szDbConnectID, szDbConnectPass);

	if(Result)
	{
		this->CreateColumn();
	}

	return Result;
}

void CReferralSystem::CreateColumn()
{
		this->m_MEMBQuery.WriteLog = false;

		char szQuery[256];
		sprintf(szQuery, "ALTER TABLE [MEMB_INFO] ADD [%s] VARCHAR(10)", this->szColumnName);
		this->m_MEMBQuery.Exec(szQuery);
		this->m_MEMBQuery.Fetch();
		this->m_MEMBQuery.Clear();
		this->m_MEMBQuery.Exec("ALTER TABLE [MEMB_INFO] ADD [RefferalMaster] INT NOT NULL default(0)");
		this->m_MEMBQuery.Fetch();
		this->m_MEMBQuery.Clear();
		this->m_MEMBQuery.Exec("ALTER TABLE [MEMB_INFO] ADD [RefferalUser] INT NOT NULL default(0)");
		this->m_MEMBQuery.Fetch();
		this->m_MEMBQuery.Clear();

		this->m_MEMBQuery.WriteLog = true;
}

void CReferralSystem::GDReqMasterInfo(PMSG_GDREQ_REFERRAL_INFO* lpMsg, int uIndex)
{
	char szQuery[256];
	char szQuery2[256];
	int iTotal = 0;
	int iCount = 0;
	char szReferralAccount[REFERRAL_MAXDATA][11];
	memset(szReferralAccount, 0, sizeof(szReferralAccount));

	PMSG_DGANS_REFERRAL_MASTER_INFO pMsg;
	memset(&pMsg, 0, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xE1, 0x00, sizeof(pMsg));
	pMsg.aIndex = lpMsg->aIndex;
	pMsg.Result = true;

	char szName[11] = { 0 };
	memcpy(szName, lpMsg->Name, sizeof(szName));
	szName[10] = 0;

	sprintf(szQuery, "SELECT memb_guid, memb___id, RefferalMaster FROM MEMB_INFO WHERE %s = '%s' ORDER BY RefferalMaster, memb_guid", this->szColumnName, szName);

	if(this->m_MEMBQuery.Exec(szQuery) == FALSE)
	{
		pMsg.Result = false;
		this->m_MEMBQuery.Clear();
	}
	else
	{
		short i =  this->m_MEMBQuery.Fetch();

		int iPageCount = lpMsg->PageNumber * REFERRAL_MAXDATA;

		while(i != SQL_NO_DATA && i != SQL_NULL_DATA)
		{
			int iReturnCode = this->m_MEMBQuery.GetInt(1);

			if(iReturnCode < 0)
			{
				break;
			}

			if(iTotal >= iPageCount && iTotal < iPageCount + REFERRAL_MAXDATA)
			{
				this->m_MEMBQuery.GetStr("memb___id", szReferralAccount[iCount]);
				szReferralAccount[iCount][10] = 0;
				pMsg.Player[iCount].RefferalMaster = this->m_MEMBQuery.GetInt("RefferalMaster");

				iCount++;
			}

			iTotal++;

			i = this->m_MEMBQuery.Fetch();
		}

		this->m_MEMBQuery.Clear();
	}

	for(int i = 0; i < iCount; i++)
	{
		char szNoName[] = "NO Char";
		memcpy(pMsg.Player[i].RefferalName, szNoName, sizeof(szNoName));
		pMsg.Player[i].RefferalUserLevel = 0;
		pMsg.Player[i].RefferalUserReset = 0;
		pMsg.Player[i].RefferalUserGrand = 0;

		sprintf(szQuery, "SELECT TOP 1 Name, cLevel, Resets, gr_res FROM Character WHERE AccountID = '%s' ORDER BY gr_res DESC, Resets DESC, cLevel DESC, Name DESC", szReferralAccount[i]);

		if(this->m_DBQuery.Exec(szQuery) == FALSE || this->m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			this->m_DBQuery.Clear();
			continue;
		}

		char szTempName[11];
		memset(szTempName, 0, sizeof(szTempName));

		this->m_DBQuery.GetStr("Name", szTempName);
		int iLevel = this->m_DBQuery.GetInt("cLevel");
		int iReset = this->m_DBQuery.GetInt("Resets");
		int iGrand = this->m_DBQuery.GetInt("gr_res");

		this->m_DBQuery.Clear();

		szTempName[10] = 0;
		memcpy(pMsg.Player[i].RefferalName, szTempName, sizeof(szTempName));
		pMsg.Player[i].RefferalUserLevel = iLevel;
		pMsg.Player[i].RefferalUserReset = iReset;
		pMsg.Player[i].RefferalUserGrand = iGrand;
	}

	pMsg.Count = iCount;
	pMsg.TotalCount = iTotal;

	wsjServer.DataSend(uIndex, (char*)&pMsg, sizeof(pMsg));
}

void CReferralSystem::GDReqMasterUpdate(PMSG_GD_REFERRAL_MASTER_UPDATE* lpMsg, int uIndex)
{
	char szQuery[256];
	char szTempAccount[11];

	PMSG_GDANS_REFERRAL_MASTER_UPDATE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x15, sizeof(pMsg));
	pMsg.aIndex = lpMsg->aIndex;
	pMsg.Number = lpMsg->Number;
	pMsg.Result = true;
	
	char szRefId[11] = { 0 };
	memcpy(szRefId, lpMsg->RefferalName, sizeof(szRefId));
	szRefId[10] = 0;

	char szName[11] = { 0 };
	memcpy(szName, lpMsg->Name, sizeof(szName));
	szName[10] = 0;

	sprintf(szQuery, "SELECT AccountID FROM Character WHERE Name = '%s'", szRefId);

	if(this->m_DBQuery.Exec(szQuery) == FALSE || this->m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		pMsg.Result = false;
		this->m_DBQuery.Clear();
	}
	else
	{
		memset(szTempAccount, 0, sizeof(szTempAccount));
		this->m_DBQuery.GetStr("AccountID", szTempAccount);	
		this->m_DBQuery.Clear();
	}

	sprintf(szQuery, "UPDATE MEMB_INFO SET RefferalMaster = RefferalMaster + 1 WHERE memb___id = '%s' AND %s = '%s'", szTempAccount, this->szColumnName, szName);
	pMsg.Result = this->m_MEMBQuery.Exec(szQuery);

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CReferralSystem::GDReqUserInfo(PMSG_GDREQ_REFERRAL_USER_INFO* lpMsg, int uIndex)
{
	char szQuery[256];
	char szReferralAccount[11];
	memset(szReferralAccount, 0, sizeof(szReferralAccount));

	PMSG_DGANS_REFERRAL_USER_INFO pMsg;
	memset(&pMsg, 0, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x16, sizeof(pMsg));
	pMsg.aIndex = lpMsg->aIndex;
	pMsg.Result = false;

	char szName[11] = { 0 };
	memcpy(szName, lpMsg->Name, sizeof(szName));
	szName[10] = 0;

	sprintf(szQuery, "SELECT %s, RefferalUser FROM MEMB_INFO WHERE memb___id = '%s'", this->szColumnName, szName);

	if(this->m_MEMBQuery.Exec(szQuery) == FALSE || this->m_MEMBQuery.Fetch() == SQL_NO_DATA)
	{
		pMsg.Result = false;
	}
	else
	{
		this->m_MEMBQuery.GetStr(this->szColumnName, szReferralAccount);
		szReferralAccount[10] = 0;

		if(strlen(szReferralAccount) >= 4)
		{
			pMsg.Result = true;
		}

		pMsg.RefferalUser = this->m_MEMBQuery.GetInt("RefferalUser");
	}

	this->m_MEMBQuery.Clear();

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CReferralSystem::GDReqUserUpdate(PMSG_GD_REFERRAL_USER_UPDATE* lpMsg, int uIndex)
{
	char szQuery[256];

	PMSG_GDANS_REFERRAL_USER_UPDATE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x17, sizeof(pMsg));
	pMsg.aIndex = lpMsg->aIndex;
	pMsg.Result = true;

	char szRefId[11] = { 0 };
	memcpy(szRefId, lpMsg->RefferalName, sizeof(szRefId));
	szRefId[10] = 0;

	sprintf(szQuery, "UPDATE MEMB_INFO SET RefferalUser = RefferalUser + 1 WHERE memb___id = '%s'", szRefId);

	pMsg.Result = this->m_MEMBQuery.Exec(szQuery);

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CReferralSystem::UpdateState(char* Name)
{
	char szQuery[256];

	sprintf(szQuery, "UPDATE MEMB_INFO SET RefferalMaster = 1, RefferalUser = 1 WHERE memb___id = '%s' AND RefferalMaster = 0 AND RefferalUser = 0", Name);

	this->m_MEMBQuery.Exec(szQuery);
	this->m_MEMBQuery.Clear();
}

#endif