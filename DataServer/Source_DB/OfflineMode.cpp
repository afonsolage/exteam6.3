#include "StdAfx.h"
#include "OfflineMode.h"
#include "MainFrm.h"
#include "winutil.h"
#include "ServerPrc.h"

int iRestoreCount = 0;

COfflineMode g_OfflineMode;

COfflineMode::COfflineMode()
{
	this->m_RunActive = false;
	this->m_ConnectedUser = false;
	this->m_ConnectedTick = 0;
	this->m_bQueenQuery = false;
	this->m_users.clear();
}

COfflineMode::~COfflineMode()
{
}

bool COfflineMode::Connect()
{
	bool Result = this->m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);
	Result = this->m_AccountDBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);
	//Result = this->m_PasswordDBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);
	Result = this->m_PasswordDBQuery.Connect(3, szDbConnectMemb, szDbConnectID, szDbConnectPass);
	Result = this->m_MembStat.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);
	
	if(Result)
	{
		this->CreateTable();
	}

	return Result;
}

void COfflineMode::CreateTable()
{
	this->m_DBQuery.WriteLog = false;

	char szQuery[512] = "CREATE TABLE OfflineMode (Name VARCHAR(10), Status INT NOT NULL default(0), AttackData VARBINARY(8) NOT NULL default(0x00), ";
	strcat(szQuery, "ShopOpen INT NOT NULL default(0), ShopText VARCHAR(36), PriceData VARBINARY(581) NOT NULL default(0x00), CreditData VARBINARY(128) NOT NULL default(0x00), ServerCode INT NOT NULL default(0))");

	this->m_DBQuery.Exec(szQuery);
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("ALTER TABLE [OfflineMode] ADD [CreditData] VARBINARY(128) NOT NULL default(0x00)");
	this->m_DBQuery.Clear();

	this->m_DBQuery.WriteLog = true;
}

void COfflineMode::GDReqAllPlayer(int uIndex)
{
	this->m_users.clear();

	int iReturnCode = 0;

	//while(true)
	//{
	char szQuery[512] = { 0 };

	int ServerCode = gSObj[uIndex].ServerCode;//TEST Off SUB Restore

	sprintf(szQuery,"SELECT Name FROM OfflineMode WHERE Status = 1 AND ServerCode = %d", ServerCode);

	//this->m_DBQuery.Exec("SELECT Name FROM OfflineMode WHERE Status = 1");

	this->m_DBQuery.Exec(szQuery);

	short i = this->m_DBQuery.Fetch();

		while(i != SQL_NO_DATA && i != SQL_NULL_DATA)
		{
			/*if(this->m_DBQuery.GetInt(1) < 0)
			{
				break;
			}*/

			iReturnCode = this->m_DBQuery.GetInt(1);

			if(iReturnCode < 0)
			{
				break;
			}

			char szBuffer[256] = { 0 };
			char szAccountID[11] = { 0 };
			char szPassword[11] = { 0 };
			char szName[11] = { 0 };

			this->m_DBQuery.GetStr("Name", szName);

			sprintf(szBuffer, "SELECT AccountID FROM Character WHERE Name = '%s'", szName);
			if(!this->m_AccountDBQuery.Exec(szBuffer) || this->m_AccountDBQuery.Fetch() == SQL_NO_DATA)
			{
				this->m_AccountDBQuery.Clear();
				continue;
			}
			this->m_AccountDBQuery.GetStr("AccountID", szAccountID);
			this->m_AccountDBQuery.Clear();

			sprintf(szBuffer, "SELECT memb__pwd FROM MEMB_INFO WHERE memb___id = '%s'", szAccountID);
			if(!this->m_PasswordDBQuery.Exec(szBuffer) || this->m_PasswordDBQuery.Fetch() == SQL_NO_DATA)
			{
				this->m_PasswordDBQuery.Clear();
				continue;
			}
			this->m_PasswordDBQuery.GetStr("memb__pwd", szPassword);
			this->m_PasswordDBQuery.Clear();

			//PMSG_DGANS_OFFMODE_START pMsg;
			//pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x11, sizeof(pMsg));
			//memcpy(pMsg.AccountID, szAccountID, sizeof(szAccountID));
			//memcpy(pMsg.Password, szPassword, sizeof(szPassword));
			//memcpy(pMsg.Name, szName, sizeof(szName));
			//pMsg.TickCount = GetTickCount();
			//wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size); 

			OFFMODEUSER_DATA list;
			list.uIndex = uIndex;
			memcpy(list.AccountID, szAccountID, sizeof(szAccountID));
			memcpy(list.Password, szPassword, sizeof(szPassword));
			memcpy(list.Name, szName, sizeof(szName));
			this->m_users.push_back(list);
		
			i = this->m_DBQuery.Fetch();
		}

		this->m_DBQuery.Clear();
		//break;

	//}

	this->m_RunActive = true;
	iRestoreCount = 0;

	// ----
	/*
	this->m_DBQuery.Exec("DECLARE @Account VARCHAR(10); DECLARE @Name VARCHAR(10); SET @Name = (SELECT Name FROM OfflineMode WHERE Status = 1); SET @Account = (SELECT AccountID FROM Character WHERE Name = @Name); SELECT MEMB_INFO.memb___id, MEMB_INFO.memb__pwd,Character.Name FROM MEMB_INFO,Character WHERE MEMB_INFO.memb___id = @Account AND Character.Name = @Name");

	short i = this->m_DBQuery.Fetch();

	while(i != SQL_NO_DATA && i != SQL_NULL_DATA)
	{
		if(this->m_DBQuery.GetInt(1) < 0)
		{
			break;
		}

		char szAccountID[11] = { 0 };
		char szPassword[11] = { 0 };
		char szName[11] = { 0 };

		this->m_DBQuery.GetStr("memb___id", szAccountID);
		this->m_DBQuery.GetStr("memb__pwd", szPassword);
		this->m_DBQuery.GetStr("Name", szName);
		
		PMSG_DGANS_OFFMODE_START pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x01, sizeof(pMsg));
		memcpy(pMsg.AccountID, szAccountID, sizeof(szAccountID));
		memcpy(pMsg.Password, szPassword, sizeof(szPassword));
		memcpy(pMsg.Name, szName, sizeof(szName));
		pMsg.TickCount = GetTickCount();
		wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
		
		i = this->m_DBQuery.Fetch();
	}

	this->m_DBQuery.Clear();*/
}

void COfflineMode::GDReqOffCharacter(PMSG_GDREQ_OFFMODE_CHAR* lpMsg, int uIndex)
{
	char szAccountID[11] = { 0 };
	char szName[11] = { 0 };

	memcpy(szAccountID, lpMsg->AccountID, sizeof(szAccountID));
	memcpy(szName, lpMsg->Name, sizeof(szName));

	CharacterInfo_Struct CharObj = { 0 };
	SDHP_DBCHAR_INFORESULT pChar = { 0 };
	pChar.h.set((LPBYTE)&pChar, 0xEC, sizeof(SDHP_DBCHAR_INFORESULT));

	pChar.result = false;
	pChar.Number = lpMsg->Number;

	memcpy(pChar.AccountID, szAccountID, sizeof(szAccountID));
	memcpy(pChar.Name, szName, sizeof(szName));

	if(SpaceSyntexCheck(pChar.Name))
	{
		if(gCharDbSet.GetCharacter(szAccountID, pChar.Name, &CharObj))
		{
			pChar.result = true;
			pChar.Class = CharObj.Class;
			pChar.Level = LOWORD(CharObj.Level);
			pChar.LevelUpPoint = CharObj.LevelUpPoint;
			pChar.Exp = CharObj.Experience;
			pChar.NextExp = CharObj.NextExperience;
			pChar.Money = CharObj.Money;
			pChar.Str = CharObj.Strength;
			pChar.Dex = CharObj.Dexterity;
			pChar.Vit = CharObj.Vitality;
			pChar.Energy = CharObj.Energy;
			pChar.Life = (WORD)(CharObj.Life * 10.0);
			pChar.MaxLife = (WORD)(CharObj.MaxLife * 10.0);
			pChar.Mana = (WORD)(CharObj.Mana * 10.0);
			pChar.MaxMana = (WORD)(CharObj.MaxMana * 10.0);
			pChar.MapNumber = CharObj.MapNumber;
			pChar.MapX = CharObj.MapX;
			pChar.MapY = CharObj.MapY;
			pChar.Dir = CharObj.Dir;
			pChar.PkCount = CharObj.PkCount;
			pChar.PkLevel = CharObj.PkLevel;
			pChar.PkTime = CharObj.PkTime;
			pChar.CtlCode = CharObj.CtlCode;
			pChar.DbVersion = CharObj.DbVersion;
			pChar.Leadership = CharObj.Leadership;
			pChar.ChatLitmitTime = CharObj.ChatLitmitTime;
			pChar.iFruitPoint = CharObj.FruitPoint;
			pChar.PCPoint = CharObj.PCPoint;
			pChar.ExFreePoints = CharObj.ExFreePoints;
			pChar.Reset = CharObj.Reset;
			pChar.GReset = CharObj.GReset;
			pChar.ExQuestNum = CharObj.ExQuestNum;
			pChar.ExQuestKill = CharObj.ExQuestKill;
			pChar.PremiumTime = CharObj.PremiumTime;
#ifdef CONFLICT_PREM_TYPE
			pChar.PremiumTimeType = CharObj.PremiumTimeType;		
#endif
			pChar.ExCred = CharObj.ExCred;
			pChar.BanChat = CharObj.BanChat;
			pChar.BanPost = CharObj.BanPost;
			pChar.BanChar = CharObj.BanChar;
			pChar.ChaosBank = CharObj.ChaosBank;
			pChar.BlessBank = CharObj.BlessBank;
			pChar.SoulBank = CharObj.SoulBank;
			pChar.LifeBank = CharObj.LifeBank;
			pChar.MTDate = CharObj.MTDate;
			pChar.QTDate = CharObj.QTDate;
			pChar.AutoParty = CharObj.AutoParty;
			pChar.Zen = CharObj.Zen;
			memcpy(pChar.Brother, CharObj.Brother, MAX_IDSTRING);
			pChar.ExpandedInventory = CharObj.ExpandedInventory;
#if(CUSTOM_SAVE_PT==1)
			pChar.PartyIndex = CharObj.PartyIndex;
#endif
			memcpy(pChar.dbInventory, CharObj.dbInventory, MAX_DBINVENTORY);
			memcpy(pChar.dbMagicList, CharObj.dbMagicList, MAX_DBMAGIC);
			memcpy(pChar.dbQuest, CharObj.dbQuest, MAX_QUEST);
			
			gACDbSet.CurAccountCharacterSet(szAccountID, pChar.Name);

			pChar.ShowRanking = CharObj.ShowRanking;
			pChar.HuntingLevel = CharObj.HuntingLevel;
			pChar.HuntingPoints = CharObj.HuntingPoints;
			pChar.HuntingExp = CharObj.HuntingExp;
			memcpy(pChar.HuntingSkillLevel, CharObj.HuntingSkillLevel, HS_CNT);
		}
	}

	wsjServer.DataSend(uIndex, (char*)&pChar, sizeof(SDHP_DBCHAR_INFORESULT));

	if(pChar.result == true)
	{
		this->SelectData(uIndex, pChar.Number, pChar.Name);

		/*char szQuery[256] = { 0 };	
		sprintf(szQuery, "UPDATE MEMB_STAT SET ConnectStat = 1 WHERE memb___id = '%s'", szAccountID);
		this->m_MembStat.Exec(szQuery);
		this->m_MembStat.Clear();*/
	}
}

void COfflineMode::CreateCharecter(char* Name)
{
	CString InsertQuery;
	InsertQuery.Format("INSERT INTO OfflineMode (Name, Status, AttackData, ShopOpen, ShopText, PriceData, CreditData, ServerCode) VALUES ('%s', 0, 0x00, 0, 'Sell', 0x00, 0x00, 0)", Name);
	this->m_DBQuery.Exec(InsertQuery);
	this->m_DBQuery.Clear();
}

void COfflineMode::SelectData(int uIndex, int Number, char* Name)
{
	PMSG_GDLOAD_OFFMODE_DATA pMsg = { 0 };
	pMsg.h.set((LPBYTE)&pMsg, 0xED, sizeof(pMsg));
	pMsg.Number = Number;

	char szQuery[256] = { 0 };
		
	sprintf(szQuery,"SELECT ShopOpen, ShopText FROM OfflineMode WHERE Name = '%s'", Name);

	if(!this->m_DBQuery.Exec(szQuery) || this->m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		this->m_DBQuery.Clear();
		//this->CreateCharecter(Name);	//need add insert query	
		return;
	}

	pMsg.PShopOpen = this->m_DBQuery.GetInt("ShopOpen");
	this->m_DBQuery.GetStr("ShopText", pMsg.PShopText);

	this->m_DBQuery.Clear();

	sprintf(szQuery, "SELECT AttackData FROM OfflineMode WHERE Name = '%s'", Name);

	if(this->m_DBQuery.ReadBlob(szQuery, pMsg.AttackData) == 0)
	{
		memset(pMsg.AttackData, 0, sizeof(pMsg.AttackData));
	}

	if(pMsg.PShopOpen)
	{
		sprintf(szQuery, "SELECT PriceData FROM OfflineMode WHERE Name = '%s'", Name);

		if(this->m_DBQuery.ReadBlob(szQuery, pMsg.PriceData) == 0)
		{
			memset(pMsg.PriceData, 0, sizeof(pMsg.PriceData));
		}

		sprintf(szQuery, "SELECT CreditData FROM OfflineMode WHERE Name = '%s'", Name);

		if(this->m_DBQuery.ReadBlob(szQuery, pMsg.CreditData) == 0)
		{
			memset(pMsg.CreditData, 0, sizeof(pMsg.CreditData));
		}
	}
	else
	{
		memset(pMsg.PriceData, 0, sizeof(pMsg.PriceData));
		memset(pMsg.CreditData, 0, sizeof(pMsg.CreditData));
	}

	wsjServer.DataSend(uIndex, (char*)&pMsg, sizeof(pMsg));
}

void COfflineMode::UpdateData(PMSG_GDSAVE_OFFMODE_DATA* lpMsg, int uIndex)
{
	char szQuery[256] = { 0 };
	//sprintf(szQuery, "UPDATE OfflineMode SET Status = %d, ShopOpen = %d, ShopText = '%s' WHERE Name = '%s'", lpMsg->Status, lpMsg->PShopOpen, lpMsg->PShopText, lpMsg->Name);
	char szPSName[36] = { 0 };
	memcpy(szPSName, lpMsg->PShopText, sizeof(szPSName));
	int ServerCode = gSObj[uIndex].ServerCode;//TEST Off SUB Restore
	int iMaxLen = strlen(szPSName);

	for(int i = 0; i < iMaxLen; i++)
	{
		if(szPSName[i] == (char)"'")
		{
			szPSName[i] = (char)" ";
		}
		if(szPSName[i] == (char)"\'")
		{
			szPSName[i] = (char)" ";
		}
		if(szPSName[i] == (char)"%")
		{
			szPSName[i] = (char)" ";
		}
		if(szPSName[i] == (char)";")
		{
			szPSName[i] = (char)" ";
		}
	}

	sprintf(szQuery, "EXEC EX_OFFLINEMODE_SAVE '%s', %d, %d, '%s', %d", lpMsg->Name, lpMsg->Status, lpMsg->PShopOpen, szPSName, ServerCode);

	if(!this->m_DBQuery.Exec(szQuery))
	{
		/*this->CreateCharecter(lpMsg->Name);
		if(!this->m_DBQuery.Exec(szQuery))
		{
			*/
		
		return;
	}

	sprintf(szQuery, "UPDATE OfflineMode SET AttackData = ? WHERE Name = '%s'", lpMsg->Name);
	this->m_DBQuery.WriteBlob(szQuery, lpMsg->AttackData, OFFLINEMODE_DBMAX);

	sprintf(szQuery, "UPDATE OfflineMode SET PriceData = ? WHERE Name = '%s'", lpMsg->Name);
	this->m_DBQuery.WriteBlob(szQuery, lpMsg->PriceData, OFFLINEMODE_DBPRICE);

	sprintf(szQuery, "UPDATE OfflineMode SET CreditData = ? WHERE Name = '%s'", lpMsg->Name);
	this->m_DBQuery.WriteBlob(szQuery, lpMsg->CreditData, OFFLINEMODE_DBCREDIT);
}

void COfflineMode::UpdateStatus(PMSG_GDREQ_OFFMODE_STATUS* lpMsg, int uIndex)
{
	char szQuery[256] = { 0 };	
	int ServerCode = gSObj[uIndex].ServerCode;//TEST Off SUB Restore
	sprintf(szQuery, "UPDATE OfflineMode SET Status = %d, ServerCode = %d WHERE Name = '%s'", lpMsg->Status, ServerCode, lpMsg->Name);
	this->m_DBQuery.Exec(szQuery);
}

void COfflineMode::Run()
{
	if(!this->m_RunActive)
	{
		return;
	}

	DWORD ConnectTime = GetTickCount() - this->m_ConnectedTick;

	//if(ConnectTime > 5000)
	if(ConnectTime > 1000)
	{
		this->m_ConnectedUser = false;
		this->m_ConnectedTick = 0;
	}

	if(this->m_ConnectedUser)
	{
		return;
	}

	std::vector<OFFMODEUSER_DATA>::iterator it = this->m_users.begin(); 

	if(it != this->m_users.end())
	//if(iRestoreCount < this->m_users.size())
	{
		//if(gSObj[it->uIndex].Connected != 0)
		{
			PMSG_DGANS_OFFMODE_START pMsg;
			pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x11, sizeof(pMsg));
			memcpy(pMsg.AccountID, it->AccountID, sizeof(it->AccountID));
			memcpy(pMsg.Password, it->Password, sizeof(it->Password));
			memcpy(pMsg.Name, it->Name, sizeof(it->Name));
			pMsg.TickCount = GetTickCount();
			wsjServer.DataSend(it->uIndex, (char*)&pMsg, pMsg.h.size);

			this->m_users.erase(this->m_users.begin());

			this->m_ConnectedUser = true;
			this->m_ConnectedTick = GetTickCount();

			iRestoreCount++;
		}
	}
	else
	{
		this->m_RunActive = false;
	}


}