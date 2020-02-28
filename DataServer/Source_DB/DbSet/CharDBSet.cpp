// CharDBSet.cpp: implementation of the CCharDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CharDBSet.h"
#include "..\\MainFrm.h"
#include "..\\ExLicense.h"
#include "..\\WzItemSerial.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

	/*strcpy(chBuffer, "SELECT AccountID,cLevel,Class,LevelUpPoint,Experience,Strength,Dexterity,Vitality,Energy,Money,Life,MaxLife,Mana,MaxMana,MapNumber,MapPosX,MapPosY,MapDir,PkCount,PkLevel,PkTime,CtlCode");	
	strcat(chBuffer, ",Leadership,ChatLimitTime,FruitPoint,DbVersion");
#if(S6E3)
	strcat(chBuffer, ",ExpandedInventory");
#endif
	strcat(chBuffer, ",PCPoint");	
	strcat(chBuffer, ",ExFreePoints");
	strcat(chBuffer, ",Resets");
	strcat(chBuffer, ",gr_res");
	strcat(chBuffer, ",ExQuestNum");
	strcat(chBuffer, ",ExQuestKill");
	strcat(chBuffer, ",PremiumTime");
	strcat(chBuffer, ",PremiumTimeType");
	strcat(chBuffer, ",ExCred");
	strcat(chBuffer, ",BanChat");
	strcat(chBuffer, ",BanPost");
	strcat(chBuffer, ",BanChar");
	strcat(chBuffer, ",ChaosBank");
	strcat(chBuffer, ",BlessBank");
	strcat(chBuffer, ",SoulBank");
	strcat(chBuffer, ",LifeBank");
	strcat(chBuffer, ",AutoParty");
	strcat(chBuffer, ",Zen");
	strcat(chBuffer, ",QuestNum");
	strcat(chBuffer, ",QuestKill_1");
	strcat(chBuffer, ",QuestKill_2");
	strcat(chBuffer, ",QuestKill_3");
	strcat(chBuffer, ",QuestKill_4");
	strcat(chBuffer, ",QuestKill_5");
	strcat(chBuffer, ",Brother");
	strcat(chBuffer, ",BMQuest_num");
	strcat(chBuffer, ",BMQuest_kill");
	strcat(chBuffer, ",BMQuest_start");
	strcat(chBuffer, ",BMDamageReflect");
	strcat(chBuffer, ",BMDamage");
	strcat(chBuffer, ",BMDefense");
	strcat(chBuffer, ",BMCriticalDamage");
	strcat(chBuffer, ",BMExcelentDamage");
	strcat(chBuffer, ",BMLife");
#if(CUSTOM_NPC_BUFFER==TRUE)
	strcat(chBuffer, ",ExpBuffTime");
	strcat(chBuffer, ",DamageBuffTime");
	strcat(chBuffer, ",DefenceBuffTime");
	strcat(chBuffer, ",BattleBuffTime");
	strcat(chBuffer, ",DropBuffTime");
	strcat(chBuffer, ",DoubleBuffTime");
#endif
#if(CUSTOM_SAVE_PT==1)
	strcat(chBuffer, ",PartyIndex");
#endif
	strcat(chBuffer, " FROM Character WHERE Name='%s'");
	qSql.Format(chBuffer, Name);*/

CCharDBSet::CCharDBSet()
{

}

CCharDBSet::~CCharDBSet()
{

}

BOOL CCharDBSet::Connect()
{
	if( m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE )
	{
		MsgBox("Character DB Connect Fail");
		return FALSE;
	}

	if( m_MEMBQuery.Connect(3, szDbConnectMemb, szDbConnectID, szDbConnectPass) == FALSE )
	{
		MsgBox("Character DB Connect Fail");
		return FALSE;
	}

	

	if(CheckSP_WZ_CreateCharacterGetVersion() == FALSE)
	{
		MsgBox("Error : WZ_CreateChracter Stored Procedure Version : %d", m_CreateCharacterVer);
		return FALSE;
	}

	DefaultCreateCharacterAllDelete();

	DefaultCharacterCreate(DB_CLASS_TYPE_WIZARD);
	DefaultCharacterCreate(DB_CLASS_TYPE_KNIGHT);
	DefaultCharacterCreate(DB_CLASS_TYPE_ELF);
	DefaultCharacterCreate(DB_CLASS_TYPE_MAGUMSA);
	DefaultCharacterCreate(DB_CLASS_TYPE_DARKLORD);
	DefaultCharacterCreate(DB_CLASS_TYPE_SUMMONER);
#if(S6E3)
	DefaultCharacterCreate(DB_CLASS_TYPE_MONK);
#endif

	return TRUE;
}

BOOL CCharDBSet::GetCharacter(char *name)
{
	CString qSQL;
	char buffer[256];

	qSQL.Format("SELECT Name FROM Character WHERE Name='%s'", name);

	if(m_DBQuery.ExecGetStr(qSQL, buffer) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

int CCharDBSet::DeleteCharacter(char* AccoundID, char* CharacterID)
{
	if( strlen(CharacterID) < 1)
	{
		return 3;
	}

	CString qSql;

	qSql.Format("DELETE FROM Character WHERE AccountID='%s' AND Name='%s' ", AccoundID, CharacterID);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 2;
	}

	m_DBQuery.Clear();

	return 1;
}

int CCharDBSet::DeleteCharacter_DregInfo(char* CharacterID)
{
	CString qSql;

	qSql.Format("EXEC WZ_Delete_C_DregInfo '%s'", CharacterID);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 2;
	}

	m_DBQuery.Clear();

	return 1;
}

int CCharDBSet::CreateCharacter(CString accountId, CString Name, BYTE Class)
{
	CString qSql;

	int result = 3;

	qSql.Format("WZ_CreateCharacter '%s', '%s', '%d'", accountId, Name, Class);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return result;
	}

	if(m_DBQuery.Fetch() != SQL_NO_DATA)
	{
		result = m_DBQuery.GetInt(1);
	}

	m_DBQuery.Clear();

#ifdef FIX_INVENTORY_BUG
	//BYTE ClearInv[MAX_DBINVENTORY];
	//for(int n = 14; n < MAX_DBINVENTORY; n++)
	//{
	//	ClearInv[n] = 0xFF;
	//}
	//qSql.Format("UPDATE Character SET Inventory = ? WHERE Name = '%s'", Name);
	//m_DBQuery.WriteBlob(qSql, ClearInv, MAX_DBINVENTORY);
#endif

	BYTE ClearRage[152];
	for(int n = 0; n < 152; n++)
	{
		ClearRage[n] = 0x00;
	}
	qSql.Format("UPDATE Character SET RageSystem = ? WHERE Name = '%s'", Name);
	m_DBQuery.WriteBlob(qSql, ClearRage, 152);




	return result;
}

BOOL CCharDBSet::DefaultCharacterCreate(BYTE classskin)
{
	CharacterInfo_Struct tCharInfo;
	BYTE defclass;
	int n;

	defclass = classskin >> 4;

	if(defclass > MAX_CLASSTYPE-1)
	{
		MsgBox("error-L3 : Class over value %s %d", __FILE__, __LINE__);
		defclass = CLASS_KNIGHT;
	}

	tCharInfo.Level = 1;
	tCharInfo.LevelUpPoint = 0;
	tCharInfo.Leadership = DCInfo.DefClass[defclass].Leadership;
	tCharInfo.Class = classskin;
	tCharInfo.Experience = DCInfo.DefClass[defclass].Experience;
	tCharInfo.Strength = DCInfo.DefClass[defclass].Strength;
	tCharInfo.Dexterity = DCInfo.DefClass[defclass].Dexterity;
	tCharInfo.Vitality = DCInfo.DefClass[defclass].Vitality;
	tCharInfo.Energy = DCInfo.DefClass[defclass].Energy;
	tCharInfo.Money = 0;
	tCharInfo.Life = DCInfo.DefClass[defclass].Life;
	tCharInfo.MaxLife = DCInfo.DefClass[defclass].MaxLife;
	tCharInfo.Mana = DCInfo.DefClass[defclass].Mana;
	tCharInfo.MaxMana = DCInfo.DefClass[defclass].MaxMana;
	tCharInfo.MapNumber = 0;
	tCharInfo.MapX = 182;
	tCharInfo.MapY = 128;
	tCharInfo.PkCount = 0;
	tCharInfo.PkLevel = PK_LEVEL_DEFAULT;
	tCharInfo.PkTime = 0;

	tCharInfo.ExpandedInventory = 0;
#ifdef FIX_INVENTORY_BUG
	for ( n = 0; n < MAX_DBINVENTORY; n++ )
	{
		tCharInfo.dbInventory[n] = 0xFF;
	}
#else
	for ( n = 0; n < ((MAX_INVENTORYMAP)+MAX_EQUIPMENT+MAX_PSHOP_SIZE); n++ )
	{
		memset(&tCharInfo.dbInventory[MAX_ITEMDBBYTE * n], 0xFF, MAX_ITEMDBBYTE);
	}
#endif
	for ( n = 0; n < MAX_MAGIC; n++ )
	{
		tCharInfo.dbMagicList[3 * n] = 0xFF;
		tCharInfo.dbMagicList[3 * n + 1] = 0;
		tCharInfo.dbMagicList[3 * n + 2] = 0;
	}
	
	for ( n = 0; n < MAX_QUEST; n++ )
	{
		tCharInfo.dbQuest[n] = 0xFF;
	}

	if(defclass == CLASS_WIZARD)
	{
		tCharInfo.dbMagicList[0] = AT_SKILL_ENERGYBALL;
	}

	if(defclass == CLASS_DARKLORD)
	{
		tCharInfo.dbMagicList[0] = AT_SKILL_SPEAR;
	}

	#if(FIX_ITEM_SERIAL)
	//CItem* lpItem = DCInfo.DefClass[defclass].Equipment;
	//lpItem->m_Number = gWzItemSerial.GetSerial();
	//ItemByteConvert16(tCharInfo.dbInventory, lpItem, MAX_EQUIPMENT+2);
	ItemByteConvert16(tCharInfo.dbInventory, DCInfo.DefClass[defclass].Equipment, MAX_EQUIPMENT+2);
	#else
	ItemByteConvert16(tCharInfo.dbInventory, DCInfo.DefClass[defclass].Equipment, MAX_EQUIPMENT+2);
	#endif

	DefaultCreateCharacterInsert(&tCharInfo);


	return TRUE;
}

void CCharDBSet::SetSP_WZ_CreateCharacterGetVersion(int version)
{
	m_CreateCharacterVer = version;
}

BOOL CCharDBSet::CheckSP_WZ_CreateCharacterGetVersion()
{
	CString qSql;
	int version = 0;

	qSql.Format("exec WZ_CreateCharacter_GetVersion");

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return FALSE;
	}

	if(m_DBQuery.Fetch() != SQL_NO_DATA)
	{
		version = m_DBQuery.GetInt(1);

		if(version == m_CreateCharacterVer)
		{
			m_DBQuery.Clear();
			return TRUE;
		}
	}

	m_DBQuery.Clear();

	return FALSE;
}

BOOL CCharDBSet::DefaultCreateCharacterAllDelete()
{
	if(m_DBQuery.Exec("DELETE FROM DefaultClassType") == FALSE)
	{
		LogAddTD("error-L3 : DELETE FROM DefaultClassType %s %d", __FILE__, __LINE__);
		return FALSE;
	}
	return TRUE;
}

BOOL CCharDBSet::DefaultCreateCharacterInsert(LPCharacterInfo_Struct lpObj)
{
	CString qSql;

	qSql.Format("INSERT INTO DefaultClassType (Level, Class, Strength, Dexterity, Vitality, Energy, Life, MaxLife, Mana, MaxMana, MapNumber, MapPosX, MapPosY, DbVersion, LevelUpPoint,Leadership)  VALUES (%d,%d,%d,%d,%d, %d, %f,%f,%f,%f, %d,%d,%d, %d, %d, %d)",
		lpObj->Level, lpObj->Class, lpObj->Strength, lpObj->Dexterity, lpObj->Vitality, lpObj->Energy, lpObj->Life, lpObj->MaxLife, lpObj->Mana, lpObj->MaxMana, lpObj->MapNumber, lpObj->MapX, lpObj->MapY, 3, lpObj->LevelUpPoint, lpObj->Leadership);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return FALSE;
	}

	qSql.Format("UPDATE DefaultClassType SET Inventory=? where Class=%d", lpObj->Class);
	m_DBQuery.WriteBlob(qSql, lpObj->dbInventory, MAX_DBINVENTORY);

	qSql.Format("UPDATE DefaultClassType SET MagicList=? where Class=%d", lpObj->Class);
	m_DBQuery.WriteBlob(qSql, lpObj->dbMagicList, MAX_DBMAGIC);

	qSql.Format("UPDATE DefaultClassType SET Quest=? where Class=%d", lpObj->Class);
	m_DBQuery.WriteBlob(qSql, lpObj->dbQuest, MAX_QUEST);

	return TRUE;
}

BYTE CCharDBSet::CurCharNameSave(char* Name)
{
	CString qSql;
	qSql.Format("INSERT INTO T_CurCharName (Name) VALUES('%s')", Name);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return 0x00;
	}

	return 0x01;
}

BYTE CCharDBSet::SaveCharacter(char* Name, LPCharacterInfo_Struct lpObj)
{
	CString qSql;

	char chBrother[11];
	chBrother[MAX_IDSTRING] = '\0';
	memcpy(chBrother,lpObj->Brother,10);

	//qSql.Format("EXEC EX_CHARACTER_SAVE '%s','%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
	//Name, chBrother, lpObj->Level, (int)lpObj->Class, lpObj->LevelUpPoint, lpObj->Experience, (int)lpObj->Strength, (int)lpObj->Dexterity, (int)lpObj->Vitality, (int)lpObj->Energy,
	//(int)lpObj->Money, (int)lpObj->Life, (int)lpObj->MaxLife, (int)lpObj->Mana, (int)lpObj->MaxMana, (int)lpObj->MapNumber, (int)lpObj->MapX, (int)lpObj->MapY, (int)lpObj->Dir,
	//lpObj->PkCount, lpObj->PkLevel, lpObj->PkTime, (int)lpObj->Leadership, (int)lpObj->ChatLitmitTime, lpObj->FruitPoint, (short)lpObj->ExpandedInventory,
	////----
	//lpObj->PCPoint, lpObj->ExFreePoints, lpObj->Reset, lpObj->GReset, lpObj->ExQuestNum, lpObj->ExQuestKill, lpObj->PremiumTime, lpObj->PremiumTimeType, (int)lpObj->ExCred, lpObj->BanChat,
	//lpObj->BanPost, lpObj->BanChar, lpObj->ChaosBank, lpObj->BlessBank, lpObj->SoulBank, lpObj->LifeBank, (int)lpObj->AutoParty, lpObj->Zen, lpObj->PartyIndex,
	////----
	//lpObj->MTDate, lpObj->QTDate);

	qSql.Format("EXEC EX_CHARACTER_SAVE '%s','%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
	Name, chBrother, lpObj->Level, (int)lpObj->Class, lpObj->LevelUpPoint, lpObj->Experience, (int)lpObj->Strength, (int)lpObj->Dexterity, (int)lpObj->Vitality, (int)lpObj->Energy,
	(int)lpObj->Money, (int)lpObj->Life, (int)lpObj->MaxLife, (int)lpObj->Mana, (int)lpObj->MaxMana, (int)lpObj->MapNumber, (int)lpObj->MapX, (int)lpObj->MapY, (int)lpObj->Dir,
	lpObj->PkCount, lpObj->PkLevel, lpObj->PkTime, (int)lpObj->Leadership, (int)lpObj->ChatLitmitTime, lpObj->FruitPoint, (short)lpObj->ExpandedInventory,
	//----
	lpObj->PCPoint, lpObj->ExFreePoints, lpObj->Reset, lpObj->GReset, lpObj->ExQuestNum, lpObj->ExQuestKill, lpObj->PremiumTime, lpObj->PremiumTimeType, (int)lpObj->ExCred, lpObj->BanChat,
	lpObj->BanPost, lpObj->BanChar, lpObj->ChaosBank, lpObj->BlessBank, lpObj->SoulBank, lpObj->LifeBank, (int)lpObj->AutoParty, lpObj->Zen, lpObj->PartyIndex);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 0x00;
	}
	m_DBQuery.Clear();

	// ==== >

	//char szAccountID[MAX_IDSTRING];
	//char szQouery[256];
	//sprintf(szQouery, "SELECT AccountID FROM Character WHERE Name = '%s'", Name);

	//if(m_MEMBQuery.Exec(qSql) == FALSE)
	//{
	//	m_MEMBQuery.Clear();
	//	return 0x00;
	//}

	//m_DBQuery.GetStr("AccountID", szAccountID);

	//m_MEMBQuery.Clear();

	//qSql.Format("EXEC EX_MEMB_INFO_SAVE '%s',%d,%d,%d,%d", Name, lpObj->PremiumTime, (int)lpObj->ExCred, lpObj->MTDate, lpObj->QTDate);

	//if(m_MEMBQuery.Exec(qSql) == FALSE)
	//{
	//	m_MEMBQuery.Clear();
	//	return 0x00;
	//}
	//m_MEMBQuery.Clear();

	// ==== !


	qSql.Format("UPDATE Character SET Inventory=? WHERE Name='%s'", Name);
	m_DBQuery.WriteBlob(qSql, lpObj->dbInventory, MAX_DBINVENTORY);

	qSql.Format("UPDATE Character SET MagicList=? WHERE Name='%s'", Name);
	m_DBQuery.WriteBlob(qSql, lpObj->dbMagicList, MAX_DBMAGIC);

	qSql.Format("UPDATE Character SET Quest=? WHERE Name='%s'", Name);
	m_DBQuery.WriteBlob(qSql, lpObj->dbQuest, MAX_QUEST);

	// => Fix

	char szQouery[256];

	sprintf(szQouery, "EX_MEMB_INFO_SAVE '%s',%d,%d,%d,%d,%d", 
		lpObj->AccountID, lpObj->PremiumTime, (int)lpObj->ExCred, lpObj->MTDate, lpObj->QTDate, lpObj->DonateCredit); 

	if(this->m_MEMBQuery.Exec(szQouery) == FALSE)
	{
		this->m_MEMBQuery.Clear();
		return 0x00;
	}

	this->m_MEMBQuery.Clear();

	// -> PCPoint

	if(g_ExLicense.CheckUser(eExUB::NSGames))
	{
		sprintf(szQouery, "UPDATE MEMB_INFO SET PCPoint = %d WHERE memb___id = '%s'", lpObj->PCPoint, lpObj->AccountID);	

		if(this->m_MEMBQuery.Exec(szQouery) == FALSE)
		{
			this->m_MEMBQuery.Clear();
			return 0x00;
		}

		this->m_MEMBQuery.Clear();
	}

	return 0x01;
}

BOOL CCharDBSet::GetCharacter(char* szAccountID, char* Name, LPCharacterInfo_Struct lpObj)
{
	CString qSql;
	qSql.Format("EXEC EX_CHARACTER_LOAD '%s'",Name);

	if(m_DBQuery.Exec(qSql) == FALSE || m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	m_DBQuery.GetStr("AccountID", lpObj->AccountID);
	if(strcmp(lpObj->AccountID, szAccountID) != 0)
	{
		LogAddC(LOGC_RED, "error-L1 :캐릭터의 계정과 요청한 계정이 맞지않다.%s %s", lpObj->AccountID, szAccountID);
		m_DBQuery.Clear();
		return FALSE;
	}

	lpObj->Level = m_DBQuery.GetInt("cLevel");
	lpObj->Class = m_DBQuery.GetInt("Class");
	lpObj->LevelUpPoint = m_DBQuery.GetInt("LevelUpPoint");
	lpObj->Experience = m_DBQuery.GetInt("Experience");
	lpObj->Strength = m_DBQuery.GetInt("Strength");
	lpObj->Dexterity = m_DBQuery.GetInt("Dexterity");
	lpObj->Vitality = m_DBQuery.GetInt("Vitality");
	lpObj->Energy = m_DBQuery.GetInt("Energy");
	lpObj->Money = m_DBQuery.GetInt("Money");
	lpObj->Life = m_DBQuery.GetFloat("Life");
	lpObj->MaxLife = m_DBQuery.GetFloat("MaxLife");
	lpObj->Mana = m_DBQuery.GetFloat("Mana");
	lpObj->MaxMana = m_DBQuery.GetFloat("MaxMana");
	lpObj->MapNumber = m_DBQuery.GetInt("MapNumber");
	lpObj->MapX = m_DBQuery.GetInt("MapPosX");
	lpObj->MapY = m_DBQuery.GetInt("MapPosY");
	lpObj->Dir = m_DBQuery.GetInt("MapDir");
	lpObj->PkCount = m_DBQuery.GetInt("PkCount");
	lpObj->PkLevel = m_DBQuery.GetInt("PkLevel");
	lpObj->PkTime = m_DBQuery.GetInt("PkTime");
	lpObj->ExpandedInventory = m_DBQuery.GetInt("ExpandedInventory");
	lpObj->PCPoint = m_DBQuery.GetInt("PCPoint");
	lpObj->ExFreePoints = m_DBQuery.GetInt("ExFreePoints");
	lpObj->Reset = m_DBQuery.GetInt("Resets");
	lpObj->GReset = m_DBQuery.GetInt("gr_res");
	lpObj->ExQuestNum = m_DBQuery.GetInt("ExQuestNum");
	lpObj->ExQuestKill = m_DBQuery.GetInt("ExQuestKill");
	lpObj->PremiumTime = m_DBQuery.GetInt("PremiumTime");
	lpObj->PremiumTimeType = m_DBQuery.GetInt("PremiumTimeType");
	lpObj->ExCred = m_DBQuery.GetFloat("ExCred");
	lpObj->BanChat = m_DBQuery.GetInt("BanChat");
	lpObj->BanPost = m_DBQuery.GetInt("BanPost");
	lpObj->BanChar = m_DBQuery.GetInt("BanChar");
	lpObj->ChaosBank = m_DBQuery.GetInt("ChaosBank");
	lpObj->BlessBank = m_DBQuery.GetInt("BlessBank");
	lpObj->SoulBank = m_DBQuery.GetInt("SoulBank");
	lpObj->LifeBank = m_DBQuery.GetInt("LifeBank");
	lpObj->AutoParty = m_DBQuery.GetInt("AutoParty");
	lpObj->Zen = m_DBQuery.GetInt("Zen");	
	lpObj->PartyIndex = m_DBQuery.GetInt("PartyIndex");

	m_DBQuery.GetStr("Brother", lpObj->Brother);

	int ctlcode = m_DBQuery.GetInt("CtlCode");
	if(ctlcode < 0) ctlcode = 0;

	int dbversion = m_DBQuery.GetInt("DbVersion");
	if(dbversion < 0) dbversion = 0;

	int leadership = m_DBQuery.GetInt("Leadership");
	if(leadership < 0) leadership = 0;

	int ChatLitmitTime = m_DBQuery.GetInt("ChatLimitTime");
	if(ChatLitmitTime < 0) ChatLitmitTime = 0;

	int iFruitPoint = m_DBQuery.GetInt("FruitPoint");
	if(iFruitPoint < 0) lpObj->FruitPoint = 0;

	lpObj->Leadership = leadership;
	lpObj->ChatLitmitTime = ChatLitmitTime;
	lpObj->CtlCode = ctlcode;
	lpObj->DbVersion = dbversion;
	lpObj->FruitPoint = iFruitPoint;
	lpObj->FruitPoint = iFruitPoint;

	m_DBQuery.Clear();
	// ----
	qSql.Format("SELECT Inventory FROM Character WHERE Name='%s'", Name);
	int nRet = m_DBQuery.ReadBlob(qSql, lpObj->dbInventory);
	if(nRet == 0)
	{
		for(int n = 0; n < MAX_DBINVENTORY; n++)
		{
			lpObj->dbInventory[n] = 0xFF;
		}
	}
	else if(nRet == -1)
	{
		return FALSE;
	}
	else if(nRet == 760)
	{
		for(int n = 760; n < MAX_DBINVENTORY; n++)
		{
			lpObj->dbInventory[n] = 0xFF;
		}
	}
	else if(nRet > 0 && nRet < MAX_DBINVENTORY)
	{
		for(int n = nRet; n < MAX_DBINVENTORY; n++)
		{
			lpObj->dbInventory[n] = 0xFF;
		}
	}
#ifndef FIX_INVENTORY_BUG
	if(lpObj->Level == 1 && lpObj->Reset == 0 && lpObj->GReset == 0)
	{
		for(int n = 760; n < MAX_DBINVENTORY; n++)
		{
			lpObj->dbInventory[n] = 0xFF;
		}
	}
#endif
	// ----
	qSql.Format("SELECT MagicList FROM Character WHERE Name='%s'", Name);
	nRet = m_DBQuery.ReadBlob(qSql, lpObj->dbMagicList);
	if(nRet == 0)
	{
		for (int n = 0; n < MAX_MAGIC; n++ )
		{
			lpObj->dbMagicList[3 * n] = 0xFF;
			lpObj->dbMagicList[3 * n + 1] = 0;
			lpObj->dbMagicList[3 * n + 2] = 0;
		}
	}
	else if(nRet == -1)
	{
		return FALSE;
	}
	else if(nRet > 0 && nRet < MAX_DBMAGIC)
	{
		int n = nRet;
		while(n < MAX_DBMAGIC)
		{
			lpObj->dbMagicList[n] = 0xFF;
			lpObj->dbMagicList[n + 1] = 0;
			lpObj->dbMagicList[n + 2] = 0;
			n += 3;
		}
	}
	// ----
	qSql.Format("SELECT Quest FROM Character WHERE Name='%s'", Name);
	nRet = m_DBQuery.ReadBlob(qSql, lpObj->dbQuest);
	if(nRet == 0)
	{
		for (int n = 0; n < MAX_QUEST; n++)
		{
			lpObj->dbQuest[n] = 0xFF;
		}
	}
	else if(nRet == -1)
	{
		return FALSE;
	}
	// ----
	qSql.Format("EXEC EX_MEMB_INFO_LOAD '%s'", szAccountID);

	if(m_MEMBQuery.Exec(qSql) == FALSE || m_MEMBQuery.Fetch() == SQL_NO_DATA)
	{
		m_MEMBQuery.Clear();
		return FALSE;
	}

	lpObj->ExCred = m_MEMBQuery.GetInt("ExCredit");
	lpObj->MTDate = m_MEMBQuery.GetInt("MTDate");
	lpObj->QTDate = m_MEMBQuery.GetInt("QTDate");

	if(g_ExLicense.CheckUser(eExUB::drynea))
	{
		lpObj->PremiumTime = m_MEMBQuery.GetInt("PremiumTime");
	}

	lpObj->DonateCredit = m_MEMBQuery.GetInt("DonateCredit");

	m_MEMBQuery.Clear();

	//

	// -> PCPoint

	if(g_ExLicense.CheckUser(eExUB::NSGames))
	{
		char szQouery[256];

		sprintf(szQouery, "SELECT PCPoint FROM MEMB_INFO WHERE memb___id = '%s'", szAccountID);	

		if(this->m_MEMBQuery.Exec(szQouery) == FALSE || this->m_MEMBQuery.Fetch() == SQL_NO_DATA)
		{
			this->m_MEMBQuery.Clear();
			return FALSE;
		}

		lpObj->PCPoint = m_MEMBQuery.GetInt("PCPoint");

		this->m_MEMBQuery.Clear();
	}
	
	// ----

	return TRUE;
}

BOOL CCharDBSet::SaveItem(char* Name, BYTE* ItemBuf)
{
	CString qSql;
	
	qSql.Format("UPDATE Character SET DbVersion=3 where Name = '%s'", Name);
	
	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return FALSE;
	}

	qSql.Format("UPDATE Character SET Inventory=? where Name='%s'", Name);
	m_DBQuery.WriteBlob(qSql, ItemBuf, MAX_DBINVENTORY);

	return TRUE;
}

int CCharDBSet::CharServerMove(char* Name)
{
	CString qSql;

	qSql.Format("SP_CHARACTER_TRANSFER '%s'", Name);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		LogAddC(LOGC_BLUE,"SP_CHARACTER_TRANSFER error return #1");
		return 1;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		LogAddC(LOGC_BLUE,"SP_CHARACTER_TRANSFER error return #2");
		m_DBQuery.Clear();
		return 1;
	}

	int error = m_DBQuery.GetInt(1);

	m_DBQuery.Clear();

	LogAddC(LOGC_BLUE,"SP_CHARACTER_TRANSFER result %d", error);

	if(error != 0)
	{
		return error;
	}

	return 0;
}

int CCharDBSet::ChangeName(char* AccountId, char* OldName, char* NewName)
{
	int result = 0;
	CString qSql;

	qSql.Format("WZ_ChangeCharacterName '%s', '%s', '%s'", AccountId, OldName, NewName);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 5;
	}

	if(m_DBQuery.Fetch() != SQL_NO_DATA)
	{
		result = m_DBQuery.GetInt(1);
	}

	m_DBQuery.Clear();
	
	return result;
}

int CCharDBSet::GetCharacterID(char* chName, char* chUserID)
{
	CString qSql;

	qSql.Format("SELECT AccountID FROM Character WHERE Name = '%s'", chName);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 1;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return 2;
	}

	char chBuffer[MAX_IDSTRING+1];

	m_DBQuery.GetStr(1, chBuffer);

	memcpy(chUserID, chBuffer, MAX_IDSTRING+1);

	m_DBQuery.Clear();

	return 0;
}

DWORD CCharDBSet::GetCharacterClass(char* chName)
{
	CString qSql;
	DWORD dwReturn = 0;

	qSql.Format("SELECT Class FROM Character WHERE Name = '%s'", chName);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return -1;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return -2;
	}

	dwReturn = m_DBQuery.GetInt(1);

	m_DBQuery.Clear();

	return dwReturn;
}

void CCharDBSet::SaveMacroInfo(char* szAccountID, char* Name, BYTE* lpMacroInfo)
{
	CString qSql;

	qSql.Format("EXEC WZ_MACROINFO_SAVE '%s', '%s', ?", szAccountID, Name);
	m_DBQuery.WriteBlob(qSql, lpMacroInfo, 256);
}

BOOL CCharDBSet::LoadMacroInfo(char* szAccountID, char* Name, BYTE* lpMacroInfo)
{
	CString qSql;

	qSql.Format("EXEC WZ_MACROINFO_LOAD '%s', '%s'", szAccountID, Name);
	int nRet = m_DBQuery.ReadBlob(qSql, lpMacroInfo);

	if(nRet == 0)
	{
		for(int n = 0; n < 256; n++)
		{
			lpMacroInfo[n] = 0xFF;
		}
	}
	else if(nRet == -1)
	{
		return FALSE;
	}

	return TRUE;
}

