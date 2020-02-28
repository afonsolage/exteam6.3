#include "StdAfx.h"
#include "MainFrm.h"
#include "ExGDManager.h"

CExGDManager g_ExGDManager;

CExGDManager::CExGDManager()
{
}

CExGDManager::~CExGDManager()
{
}

bool CExGDManager::Connect()
{
	bool Result = this->m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);

	if(Result)
	{
		this->CreateTable();
	}

	Result = m_MEMBQuery.Connect(3, szDbConnectMemb, szDbConnectID, szDbConnectPass);

	if(!Result)
	{
		MsgBox("MEMB_INFO DB Connect Fail");
	}

	return Result;
}
// -------------------------------------------------------------------------------

void CExGDManager::CreateTable()
{
	this->m_DBQuery.WriteLog = false;
	//this->m_DBQuery.Exec("ALTER TABLE [GameServerInfo] ADD [LoraBattleWin] varchar(10)");
	//this->m_DBQuery.Fetch();
	//this->m_DBQuery.Clear();
	this->m_DBQuery.Exec("ALTER TABLE [Character] ADD [TvTKill] INT");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	this->m_DBQuery.Exec("ALTER TABLE [Character] ADD [MTBuffTime] INT");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();
	this->m_DBQuery.Exec("ALTER TABLE [Character] ADD [QTBuffTime] INT");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();

	this->m_DBQuery.WriteLog = true;
}
// -------------------------------------------------------------------------------

void CExGDManager::Protocol(BYTE protoNum, BYTE *aRecv, int uIndex)
{
	switch(protoNum)
	{
	case 0x00:
		this->DG_PartySearchLoad((PMSG_REQ_PARTYSEARCH_LOAD *)aRecv, uIndex);
		break;
	case 0x01:
		this->GD_PartySearchSave((PMSG_REQ_PARTYSEARCH_SAVE *)aRecv);
		break;
	case 0x02:
		this->DG_ExBuffLoad((PMSG_REQ_EXBUFF_LOAD *)aRecv, uIndex);
		break;
	case 0x03:
		this->GD_ExBuffSave((PMSG_REQ_EXBUFF_SAVE *)aRecv);
		break;
	case 0x04:
		this->DG_BMQuestLoad((PMSG_REQ_BMQUEST_LOAD *)aRecv, uIndex);
		break;
	case 0x05:
		this->GD_BMQuestSave((PMSG_REQ_BMQUEST_SAVE *)aRecv);
		break;
	case 0x06:
		this->DG_MonsterQuestLoad((PMSG_REQ_MONSTERQUEST_LOAD *)aRecv, uIndex);
		break;
	case 0x07:
		this->GD_MonsterQuestSave((PMSG_REQ_MONSTERQUEST_SAVE *)aRecv);
		break;
	case 0x08:
		this->DG_RageSystemLoad((PMSG_REQ_RAGESYSTEM_LOAD *)aRecv, uIndex);
		break;
	case 0x09:
		this->GD_RageSystemSave((PMSG_REQ_RAGESYSTEM_SAVE *)aRecv);
		break;
	case 0x0A:
		this->DG_CreateonBankLoad((PMSG_REQ_CREATEON_LOAD *)aRecv, uIndex);
		break;
	case 0x0B:
		this->GD_CreateonBankSave((PMSG_REQ_CREATEON_SAVE *)aRecv);
		break;
	case 0x0C:
		this->GD_TvTInfo((PMSG_TVTGD_INFO*)aRecv);
		break;
#if(SYSTEM_ACHIEVEMENTS)
	case 0x0D:
		this->DG_AchievementsLoad((PMSG_GDREQ_ACH_LOAD*)aRecv, uIndex);
		break;
	case 0x0E:
		this->GD_AchievementsSave((PMSG_GDREQ_ACH_SAVE*)aRecv);
		break;
#endif
	case 0x0F:
		this->GD_OfflineAfk((PMSG_REQ_OFFLINE_AFK*)aRecv);
		break;
	case 0x10:
		this->DG_VoteBuffLoad((PMSG_REQ_VOTEBUFF_LOAD *)aRecv, uIndex);
		break;
	case 0x11:
		this->GD_VoteBuffSave((PMSG_REQ_VOTEBUFF_SAVE *)aRecv);
		break;
	case 0x14:
		this->DG_ExQuestSystemLoad((PMSG_REQ_EXQUESTSYSTEM_LOAD *)aRecv, uIndex);
		break;
	case 0x15:
		this->GD_ExQuestSystemSave((PMSG_REQ_EXQUESTSYSTEM_SAVE *)aRecv);
		break;
	}
}
// -------------------------------------------------------------------------------

void CExGDManager::DG_PartySearchLoad(PMSG_REQ_PARTYSEARCH_LOAD *aRecv, int uIndex)
{
	CString qSql;
	char szName[11];
	memcpy(szName, aRecv->Name, sizeof(szName)-1);
	szName[10] = 0;

	PMSG_ANS_PARTYSEARCH_LOAD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x00, sizeof(pMsg));
	pMsg.aIndex = aRecv->aIndex;
	pMsg.bResult = true;
	qSql.Format("EXEC EX_PARTYSEARCH_LOAD '%s'", szName);
	int nRet = m_DBQuery.ReadBlob(qSql, pMsg.btPartySearch);

	if(nRet == 0)
	{
		for (int n = 0; n < PARTY_SEARCH_SIZE; n++)
		{
			pMsg.btPartySearch[n] = 0x00;
		}
	}
	else if(nRet == -1)
	{
		pMsg.bResult = false;
	}

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}
// -------------------------------------------------------------------------------

void CExGDManager::GD_PartySearchSave(PMSG_REQ_PARTYSEARCH_SAVE* aRecv)
{
	CString qSql;
	char szName[11];
	memcpy(szName, aRecv->Name, sizeof(szName)-1);
	szName[10] = 0;
	qSql.Format("EXEC EX_PARTYSEARCH_SAVE '%s', ?", szName);
	m_DBQuery.WriteBlob(qSql, aRecv->btPartySearch, PARTY_SEARCH_SIZE);
}
// -------------------------------------------------------------------------------

void CExGDManager::DG_ExBuffLoad(PMSG_REQ_EXBUFF_LOAD *aRecv, int uIndex)
{
	PMSG_ANS_EXBUFF_LOAD pMsg;
	ZeroMemory(&pMsg, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x02, sizeof(pMsg));

	CString qSql;
	char szName[11];
	memcpy(szName, aRecv->Name, sizeof(szName)-1);
	szName[10] = 0;

	qSql.Format("EXEC EX_BUFF_LOAD '%s'", szName);

	pMsg.aIndex = aRecv->aIndex;
	pMsg.bResult = true;

	if(m_DBQuery.Exec(qSql) == FALSE || m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		pMsg.bResult = false;
	}

	if(pMsg.bResult)
	{
		pMsg.ExpBuffTime = m_DBQuery.GetInt("ExpBuffTime");
		pMsg.DamageBuffTime = m_DBQuery.GetInt("DamageBuffTime");
		pMsg.DefenceBuffTime = m_DBQuery.GetInt("DefenceBuffTime");
		pMsg.BattleBuffTime = m_DBQuery.GetInt("BattleBuffTime");
		pMsg.DropBuffTime = m_DBQuery.GetInt("DropBuffTime");
		pMsg.DoubleBuffTime = m_DBQuery.GetInt("DoubleBuffTime");
		m_DBQuery.Clear();
	}

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CExGDManager::GD_ExBuffSave(PMSG_REQ_EXBUFF_SAVE* aRecv)
{
	CString qSql;
	char szName[11];
	memcpy(szName, aRecv->Name, sizeof(szName)-1);
	szName[10] = 0;
	qSql.Format("EXEC EX_BUFF_SAVE '%s', %d, %d, %d, %d, %d, %d", 
		szName, aRecv->ExpBuffTime, aRecv->DamageBuffTime, aRecv->DefenceBuffTime, aRecv->BattleBuffTime, aRecv->DropBuffTime, aRecv->DoubleBuffTime);
	m_DBQuery.Exec(qSql);
	m_DBQuery.Clear();
}
// -------------------------------------------------------------------------------

void CExGDManager::DG_BMQuestLoad(PMSG_REQ_BMQUEST_LOAD *aRecv, int uIndex)
{
	PMSG_ANS_BMQUEST_LOAD pMsg;
	ZeroMemory(&pMsg, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x04, sizeof(pMsg));

	CString qSql;
	char szName[11];
	memcpy(szName, aRecv->Name, sizeof(szName)-1);
	szName[10] = 0;

	qSql.Format("EXEC EX_BMQUEST_LOAD '%s'", szName);

	pMsg.aIndex = aRecv->aIndex;
	pMsg.bResult = true;

	if(m_DBQuery.Exec(qSql) == FALSE || m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		pMsg.bResult = false;
	}

	if(pMsg.bResult)
	{
		pMsg.BMQuest_num = m_DBQuery.GetInt("BMQuest_num");
		pMsg.BMQuest_kill = m_DBQuery.GetInt("BMQuest_kill");
		pMsg.BMQuest_start = m_DBQuery.GetInt("BMQuest_start");
		pMsg.BMDamageReflect = m_DBQuery.GetInt("BMDamageReflect");
		pMsg.BMDamage = m_DBQuery.GetInt("BMDamage");
		pMsg.BMDefense = m_DBQuery.GetInt("BMDefense");
		pMsg.BMCriticalDamage = m_DBQuery.GetInt("BMCriticalDamage");
		pMsg.BMExcelentDamage = m_DBQuery.GetInt("BMExcelentDamage");
		pMsg.BMLife = m_DBQuery.GetInt("BMLife");

		m_DBQuery.Clear();
	}

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CExGDManager::GD_BMQuestSave(PMSG_REQ_BMQUEST_SAVE* aRecv)
{
	CString qSql;
	char szName[11];
	memcpy(szName, aRecv->Name, sizeof(szName)-1);
	szName[10] = 0;
	qSql.Format("EXEC EX_BMQUEST_SAVE '%s', %d, %d, %d, %d, %d, %d, %d, %d, %d", 
		szName, aRecv->BMQuest_num, aRecv->BMQuest_kill, aRecv->BMQuest_start, aRecv->BMDamageReflect, aRecv->BMDamage, aRecv->BMDefense, aRecv->BMCriticalDamage, 
		aRecv->BMExcelentDamage, aRecv->BMLife);
	m_DBQuery.Exec(qSql);
	m_DBQuery.Clear();
}
// -------------------------------------------------------------------------------

void CExGDManager::DG_MonsterQuestLoad(PMSG_REQ_MONSTERQUEST_LOAD *aRecv, int uIndex)
{
	PMSG_ANS_MONSTERQUEST_LOAD pMsg;
	ZeroMemory(&pMsg, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x06, sizeof(pMsg));

	CString qSql;
	char szName[11];
	memcpy(szName, aRecv->Name, sizeof(szName)-1);
	szName[10] = 0;
	
	qSql.Format("EXEC EX_MONSTERQUEST_LOAD '%s'", szName);

	pMsg.aIndex = aRecv->aIndex;
	pMsg.bResult = true;

	if(m_DBQuery.Exec(qSql) == FALSE || m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		pMsg.bResult = false;
	}

	if(pMsg.bResult)
	{
		pMsg.QuestNum = m_DBQuery.GetInt("QuestNum");
		pMsg.QuestKill_1 = m_DBQuery.GetInt("QuestKill_1");
		pMsg.QuestKill_2 = m_DBQuery.GetInt("QuestKill_2");
		pMsg.QuestKill_3 = m_DBQuery.GetInt("QuestKill_3");
		pMsg.QuestKill_4 = m_DBQuery.GetInt("QuestKill_4");
		pMsg.QuestKill_5 = m_DBQuery.GetInt("QuestKill_5");

		m_DBQuery.Clear();
	}

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CExGDManager::GD_MonsterQuestSave(PMSG_REQ_MONSTERQUEST_SAVE *aRecv)
{
	CString qSql;
	char szName[11];
	memcpy(szName, aRecv->Name, sizeof(szName)-1);
	szName[10] = 0;
	qSql.Format("EXEC EX_MONSTERQUEST_SAVE '%s', %d, %d, %d, %d, %d, %d", 
		szName, (int)aRecv->QuestNum, aRecv->QuestKill_1, aRecv->QuestKill_2, aRecv->QuestKill_3, aRecv->QuestKill_4, aRecv->QuestKill_5);
	m_DBQuery.Exec(qSql);
	m_DBQuery.Clear();
}
// -------------------------------------------------------------------------------

void CExGDManager::DG_RageSystemLoad(PMSG_REQ_RAGESYSTEM_LOAD *aRecv, int uIndex)	//незабыть обнуление рейджа
{
	CString qSql;

	char szAccountID[11];
	memcpy(szAccountID, aRecv->AccountID, sizeof(szAccountID)-1);
	szAccountID[10] = 0;

	char szName[11];
	memcpy(szName, aRecv->Name, sizeof(szName)-1);
	szName[10] = 0;

	PMSG_ANS_RAGESYSTEM_LOAD pMsg;
	ZeroMemory(&pMsg, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x08, sizeof(pMsg));
	pMsg.aIndex = aRecv->aIndex;
	pMsg.bResult = true;

	qSql.Format("EXEC EX_RAGELOAD_NEW '%s', '%s'", szAccountID, szName);

	if(m_DBQuery.Exec(qSql) == FALSE || m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();

		qSql.Format("EXEC EX_RAGEINSERT_NEW '%s', '%s'", szAccountID, szName);
		if(!m_DBQuery.Exec(qSql))
		{
			pMsg.bResult = false;
		}
		m_DBQuery.Clear();

		pMsg.rLevel = 1;
		pMsg.rPoints = 0;
		pMsg.rExperience = 0;
		pMsg.Damage = 0;	
		pMsg.FreePoints = 0;
		pMsg.SummonPet = 0;
		pMsg.WingsDamagePlus = 0;
		pMsg.FinalMana = 0;
		pMsg.IgnoreDefence = 0;
		pMsg.ResetLevel = 0;
		pMsg.Teleport = 0;
		pMsg.CriticalDamageRate = 0;
		pMsg.AbsordDamage = 0;
		pMsg.PetDamageBonus = 0;
		pMsg.FinalLife = 0;
		pMsg.Strength = 0;
		pMsg.DefenceRate = 0;
		pMsg.FireDamage = 0;
		pMsg.Energy = 0;
		pMsg.Agility = 0;
		pMsg.DoubleDamage = 0;
		pMsg.FinalSD = 0;
		pMsg.FinalDefence = 0;
		pMsg.ZenDrop = 0;
		pMsg.GuildBonus = 0;
		pMsg.ReflectDamage = 0;
		pMsg.ExellentDamageRate = 0;
		pMsg.PvPBonusPlus = 0;
		pMsg.MinDefence = 0;
		pMsg.Experience = 0;
		pMsg.StartSD = 0;
		pMsg.PartyBonus = 0;
		pMsg.IceDamage = 0;
		pMsg.DistanceAttack = 0;
		pMsg.AttackRate = 0;
		pMsg.WeaponBonus = 0;
		pMsg.ExellentDamage = 0;
		pMsg.CriticalDamage = 0;
	}
	else
	{
		pMsg.rLevel = m_DBQuery.GetInt("RageLevel");
		pMsg.rPoints = m_DBQuery.GetInt("RagePoint");
		pMsg.rExperience = m_DBQuery.GetInt("RageExp");
		pMsg.Damage = m_DBQuery.GetInt("Damage");	
		pMsg.FreePoints = m_DBQuery.GetInt("FreePoints");
		pMsg.SummonPet = m_DBQuery.GetInt("SummonPet");
		pMsg.WingsDamagePlus = m_DBQuery.GetInt("WingsDamagePlus");
		pMsg.FinalMana = m_DBQuery.GetInt("FinalMana");
		pMsg.IgnoreDefence = m_DBQuery.GetInt("IgnoreDefence");
		pMsg.ResetLevel = m_DBQuery.GetInt("ResetLevel");
		pMsg.Teleport = m_DBQuery.GetInt("Teleport");
		pMsg.CriticalDamageRate = m_DBQuery.GetInt("CriticalDamageRate");
		pMsg.AbsordDamage = m_DBQuery.GetInt("AbsordDamage");
		pMsg.PetDamageBonus = m_DBQuery.GetInt("PetDamageBonus");
		pMsg.FinalLife = m_DBQuery.GetInt("FinalLife");
		pMsg.Strength = m_DBQuery.GetInt("Strength");
		pMsg.DefenceRate = m_DBQuery.GetInt("DefenceRate");
		pMsg.FireDamage = m_DBQuery.GetInt("FireDamage");
		pMsg.Energy = m_DBQuery.GetInt("Energy");
		pMsg.Agility = m_DBQuery.GetInt("Agility");
		pMsg.DoubleDamage = m_DBQuery.GetInt("DoubleDamage");
		pMsg.FinalSD = m_DBQuery.GetInt("FinalSD");
		pMsg.FinalDefence = m_DBQuery.GetInt("FinalDefence");
		pMsg.ZenDrop = m_DBQuery.GetInt("ZenDrop");
		pMsg.GuildBonus = m_DBQuery.GetInt("GuildBonus");
		pMsg.ReflectDamage = m_DBQuery.GetInt("ReflectDamage");
		pMsg.ExellentDamageRate = m_DBQuery.GetInt("ExellentDamageRate");
		pMsg.PvPBonusPlus = m_DBQuery.GetInt("PvPBonusPlus");
		pMsg.MinDefence = m_DBQuery.GetInt("MinDefence");
		pMsg.Experience = m_DBQuery.GetInt("Experience");
		pMsg.StartSD = m_DBQuery.GetInt("StartSD");
		pMsg.PartyBonus = m_DBQuery.GetInt("PartyBonus");
		pMsg.IceDamage = m_DBQuery.GetInt("IceDamage");
		pMsg.DistanceAttack = m_DBQuery.GetInt("DistanceAttack");
		pMsg.AttackRate = m_DBQuery.GetInt("AttackRate");
		pMsg.WeaponBonus = m_DBQuery.GetInt("WeaponBonus");
		pMsg.ExellentDamage = m_DBQuery.GetInt("ExellentDamage");
		pMsg.CriticalDamage = m_DBQuery.GetInt("CriticalDamage");

		m_DBQuery.Clear();
	}

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CExGDManager::GD_RageSystemSave(PMSG_REQ_RAGESYSTEM_SAVE *aRecv)
{
	CString qSql;

	char szAccountID[11];
	memcpy(szAccountID, aRecv->AccountID, sizeof(szAccountID)-1);
	szAccountID[10] = 0;

	char szName[11];
	memcpy(szName, aRecv->Name, sizeof(szName)-1);
	szName[10] = 0;

	qSql.Format("EXEC EX_RAGESAVE_NEW '%s','%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
		szAccountID,
		szName,
		aRecv->rLevel,
		aRecv->rPoints,
		aRecv->rExperience,
		aRecv->Damage,
		aRecv->FreePoints,
		aRecv->SummonPet,
		aRecv->WingsDamagePlus,
		aRecv->FinalMana,
		aRecv->IgnoreDefence,
		aRecv->ResetLevel,
		aRecv->Teleport,
		aRecv->CriticalDamageRate,
		aRecv->AbsordDamage,
		aRecv->PetDamageBonus,
		aRecv->FinalLife,
		aRecv->Strength,
		aRecv->DefenceRate,
		aRecv->FireDamage,
		aRecv->Energy,
		aRecv->Agility,
		aRecv->DoubleDamage,
		aRecv->FinalSD,
		aRecv->FinalDefence,
		aRecv->ZenDrop,
		aRecv->GuildBonus,
		aRecv->ReflectDamage,
		aRecv->ExellentDamageRate,
		aRecv->PvPBonusPlus,
		aRecv->MinDefence,
		aRecv->Experience,
		aRecv->StartSD,
		aRecv->PartyBonus,
		aRecv->IceDamage,
		aRecv->DistanceAttack,
		aRecv->AttackRate,
		aRecv->WeaponBonus,
		aRecv->ExellentDamage,
		aRecv->CriticalDamage);

	m_DBQuery.Exec(qSql);
	m_DBQuery.Clear();
}
// -------------------------------------------------------------------------------

void CExGDManager::DG_CreateonBankLoad(PMSG_REQ_CREATEON_LOAD *aRecv, int uIndex)
{
	PMSG_ANS_CREATEON_LOAD pMsg;
	ZeroMemory(&pMsg, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x0A, sizeof(pMsg));

	CString qSql;
	char szName[11];
	memcpy(szName, aRecv->szName, sizeof(szName)-1);
	szName[10] = 0;

	qSql.Format("EXEC EX_CREATEON_LOAD '%s'", szName);

	pMsg.aIndex = aRecv->aIndex;

	if(m_DBQuery.Exec(qSql) == FALSE || m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return;
	}

	pMsg.iCreateon = m_DBQuery.GetInt("CreateonBank");

	pMsg.iGuardian = m_DBQuery.GetInt("GuardianBank");
	pMsg.iHarmony = m_DBQuery.GetInt("HarmonyBank");
	pMsg.iLowStone = m_DBQuery.GetInt("LowStoneBank");
	pMsg.iHighStone = m_DBQuery.GetInt("HighStoneBank");
	pMsg.iGemStone = m_DBQuery.GetInt("GemStoneBank");

	m_DBQuery.Clear();

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CExGDManager::GD_CreateonBankSave(PMSG_REQ_CREATEON_SAVE* aRecv)
{
	CString qSql;
	char szName[11];
	memcpy(szName, aRecv->szName, sizeof(szName)-1);
	szName[10] = 0;
	qSql.Format("EXEC EX_CREATEON_SAVE '%s', %d, %d, %d, %d, %d, %d", 
	szName, aRecv->iCreateon, aRecv->iGuardian, aRecv->iHarmony, aRecv->iLowStone, aRecv->iHighStone, aRecv->iGemStone);
	m_DBQuery.Exec(qSql);
	m_DBQuery.Clear();
}
// -------------------------------------------------------------------------------

void CExGDManager::GD_TvTInfo(PMSG_TVTGD_INFO* aRecv)
{
	char szSql[128] = { 0 };
	char szName[11] = { 0 };
	memcpy(szName, aRecv->Name, 10);
	sprintf(szSql, "UPDATE Character SET TvTKill = %d WHERE Name = '%s'", aRecv->KillCount, szName);
	this->m_DBQuery.Exec(szSql);
	this->m_DBQuery.Clear();
}
// -------------------------------------------------------------------------------

void CExGDManager::DG_AchievementsLoad(PMSG_GDREQ_ACH_LOAD* aRecv, int uIndex)
{
	PMSG_DGANS_ACH_LOAD pMsg;
	ZeroMemory(&pMsg, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x0C, sizeof(pMsg));

	CString qSql;
	char szName[11];
	memcpy(szName, aRecv->szName, sizeof(szName)-1);
	szName[10] = 0;

	pMsg.aIndex = aRecv->aIndex;
	pMsg.bResult = true;

	qSql.Format("EXEC ACHIEVEMENTS_LOAD '%s'", szName);

	if(m_DBQuery.Exec(qSql) == FALSE || m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		pMsg.bResult = false;
	}
	else
	{
		pMsg.usr.i1_MonsterKill = m_DBQuery.GetInt("i1_MonsterKill");
		pMsg.usr.i2_GoldenKill = m_DBQuery.GetInt("i2_GoldenKill");
		pMsg.usr.i3_KalimaMonserKill = m_DBQuery.GetInt("i3_KalimaMonserKill");
		pMsg.usr.i4_WhiteWizardKill = m_DBQuery.GetInt("i4_WhiteWizardKill");
		pMsg.usr.i5_PlayerKill = m_DBQuery.GetInt("i5_PlayerKill");
		pMsg.usr.i6_RedDragonKill = m_DBQuery.GetInt("i6_RedDragonKill");
		pMsg.usr.i7_OrcKill = m_DBQuery.GetInt("i7_OrcKill");
		pMsg.usr.i8_KillGateBC = m_DBQuery.GetInt("i8_KillGateBC");
		pMsg.usr.i9_TakePartInCC = m_DBQuery.GetInt("i9_TakePartInCC");
		pMsg.usr.i10_WinningTheCC = m_DBQuery.GetInt("i10_WinningTheCC");
		pMsg.usr.i11_OnlineTime = m_DBQuery.GetInt("i11_OnlineTime");
		pMsg.usr.i12_PickUpJewels = m_DBQuery.GetInt("i12_PickUpJewels");
		pMsg.usr.i13_UsedJewels = m_DBQuery.GetInt("i13_UsedJewels");
		pMsg.usr.i14_SuccessChaosMix = m_DBQuery.GetInt("i14_SuccessChaosMix");
		pMsg.usr.i15_FailedChaosMix = m_DBQuery.GetInt("i15_FailedChaosMix");
		pMsg.usr.i16_PickUpZen = m_DBQuery.GetInt("i16_PickUpZen");
		pMsg.usr.i17_PickUpExellent = m_DBQuery.GetInt("i17_PickUpExellent");
		pMsg.usr.i18_PickUpAncent = m_DBQuery.GetInt("i18_PickUpAncent");
		pMsg.usr.i19_DuelWin = m_DBQuery.GetInt("i19_DuelWin");
		pMsg.usr.i20_LevelUp = m_DBQuery.GetInt("i20_LevelUp");
		pMsg.usr.i21_ResetUp = m_DBQuery.GetInt("i21_ResetUp");
		pMsg.usr.i22_KanturuBossKill = m_DBQuery.GetInt("i22_KanturuBossKill");
		pMsg.usr.i23_Monster100LvlKill = m_DBQuery.GetInt("i23_Monster100LvlKill");
		pMsg.usr.i24_MootopVote = m_DBQuery.GetInt("i24_MootopVote");
		pMsg.usr.i25_PhonomanKill = m_DBQuery.GetInt("i25_PhonomanKill");
		pMsg.usr.i26_CryWolfEventMonster = m_DBQuery.GetInt("i26_CryWolfEventMonster");
		pMsg.usr.i27_HellMainKill = m_DBQuery.GetInt("i27_HellMainKill");
		pMsg.usr.i28_KillInSelf_Defense = m_DBQuery.GetInt("i28_KillInSelf_Defense");
		pMsg.usr.i29_SelupanKill = m_DBQuery.GetInt("i29_SelupanKill");
		pMsg.usr.i30_KundunKill = m_DBQuery.GetInt("i30_KundunKill");
		pMsg.usr.i31_KillStatueBC = m_DBQuery.GetInt("i31_KillStatueBC");
		pMsg.usr.i32_CompleteBC = m_DBQuery.GetInt("i32_CompleteBC");
		pMsg.usr.i33_GrandResetUp = m_DBQuery.GetInt("i33_GrandResetUp");
		pMsg.usr.i34_BlueRabbitKiller = m_DBQuery.GetInt("i34_BlueRabbitKiller");
		pMsg.usr.i35_HappyPouchesKiller = m_DBQuery.GetInt("i35_HappyPouchesKiller");
		pMsg.usr.i36_PheonixKill = m_DBQuery.GetInt("i36_PheonixKill");
		pMsg.usr.i37_KanturuMonsterKill = m_DBQuery.GetInt("i37_KanturuMonsterKill");
		pMsg.usr.i38_MovePlayerFromSwitch = m_DBQuery.GetInt("i38_MovePlayerFromSwitch");
		pMsg.usr.i39_WithstandSwitch10min = m_DBQuery.GetInt("i39_WithstandSwitch10min");
		pMsg.usr.i40_MovePlayerFromCrown = m_DBQuery.GetInt("i40_MovePlayerFromCrown");
		pMsg.usr.i41_WinSiege = m_DBQuery.GetInt("i41_WinSiege");
		pMsg.usr.i42_KillCastleSiegeNPC = m_DBQuery.GetInt("i42_KillCastleSiegeNPC");
		pMsg.usr.i43_KillPlayerCastleSiege = m_DBQuery.GetInt("i43_KillPlayerCastleSiege");
		pMsg.usr.i44_KillErohim = m_DBQuery.GetInt("i44_KillErohim");
		pMsg.usr.i45_BuyDonateShopItem = m_DBQuery.GetInt("i45_BuyDonateShopItem");
		pMsg.usr.i46_GuildWarWin = m_DBQuery.GetInt("i46_GuildWarWin");
		pMsg.usr.i47_PartyNoobLevelUp = m_DBQuery.GetInt("i47_PartyNoobLevelUp");
		pMsg.usr.i48_PickUpRena = m_DBQuery.GetInt("i48_PickUpRena");
		pMsg.usr.i49_PickUpLuckyCoins = m_DBQuery.GetInt("i49_PickUpLuckyCoins");
		pMsg.usr.i50_OfflineAttackTime = m_DBQuery.GetInt("i50_OfflineAttackTime");
	}

	m_DBQuery.Clear();

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CExGDManager::GD_AchievementsSave(PMSG_GDREQ_ACH_SAVE* aRecv)
{
	CString qSql;
	char szName[11];
	szName[10] = 0;
	memcpy(szName, aRecv->szName, sizeof(szName)-1);

	qSql.Format("EXEC ACHIEVEMENTS_SAVE '%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
		szName,
		aRecv->usr.i1_MonsterKill,
		aRecv->usr.i2_GoldenKill,
		aRecv->usr.i3_KalimaMonserKill,
		aRecv->usr.i4_WhiteWizardKill,
		aRecv->usr.i5_PlayerKill,
		aRecv->usr.i6_RedDragonKill,
		aRecv->usr.i7_OrcKill,
		aRecv->usr.i8_KillGateBC,
		aRecv->usr.i9_TakePartInCC,
		aRecv->usr.i10_WinningTheCC,
		aRecv->usr.i11_OnlineTime,
		aRecv->usr.i12_PickUpJewels,
		aRecv->usr.i13_UsedJewels,
		aRecv->usr.i14_SuccessChaosMix,
		aRecv->usr.i15_FailedChaosMix,
		aRecv->usr.i16_PickUpZen,
		aRecv->usr.i17_PickUpExellent,
		aRecv->usr.i18_PickUpAncent,
		aRecv->usr.i19_DuelWin,
		aRecv->usr.i20_LevelUp,
		aRecv->usr.i21_ResetUp,
		aRecv->usr.i22_KanturuBossKill,
		aRecv->usr.i23_Monster100LvlKill,
		aRecv->usr.i24_MootopVote,
		aRecv->usr.i25_PhonomanKill,
		aRecv->usr.i26_CryWolfEventMonster,
		aRecv->usr.i27_HellMainKill,
		aRecv->usr.i28_KillInSelf_Defense,
		aRecv->usr.i29_SelupanKill,
		aRecv->usr.i30_KundunKill,
		aRecv->usr.i31_KillStatueBC,
		aRecv->usr.i32_CompleteBC,
		aRecv->usr.i33_GrandResetUp,
		aRecv->usr.i34_BlueRabbitKiller,
		aRecv->usr.i35_HappyPouchesKiller,
		aRecv->usr.i36_PheonixKill,
		aRecv->usr.i37_KanturuMonsterKill,
		aRecv->usr.i38_MovePlayerFromSwitch,
		aRecv->usr.i39_WithstandSwitch10min,
		aRecv->usr.i40_MovePlayerFromCrown,
		aRecv->usr.i41_WinSiege,
		aRecv->usr.i42_KillCastleSiegeNPC,
		aRecv->usr.i43_KillPlayerCastleSiege,
		aRecv->usr.i44_KillErohim,
		aRecv->usr.i45_BuyDonateShopItem,
		aRecv->usr.i46_GuildWarWin,
		aRecv->usr.i47_PartyNoobLevelUp,
		aRecv->usr.i48_PickUpRena,
		aRecv->usr.i49_PickUpLuckyCoins,
		aRecv->usr.i50_OfflineAttackTime);

	m_DBQuery.Exec(qSql);
	m_DBQuery.Clear();
}
// -------------------------------------------------------------------------------

void CExGDManager::GD_OfflineAfk(PMSG_REQ_OFFLINE_AFK* lpMsg)
{
	char szQuery[256];
	char szName[11];
	szName[10] = 0;
	memcpy(szName, lpMsg->Name, sizeof(szName)-1);

	if(lpMsg->ConnectType == 0)
	{
		if(lpMsg->OfflineType == 0)
		{
			// off trade user connect
			sprintf(szQuery, "EXEC OFFTRADE_CONNECT '%s'", szName);
			m_DBQuery.Exec(szQuery);
			m_DBQuery.Clear();
		}
		else if(lpMsg->OfflineType == 1)
		{
			// off exp user connect
			sprintf(szQuery, "EXEC OFFAFK_CONNECT '%s'", szName);
			m_DBQuery.Exec(szQuery);
			m_DBQuery.Clear();
		}
	}
	else if(lpMsg->ConnectType == 1)
	{
		if(lpMsg->OfflineType == 0)
		{
			// off trade user dc
			sprintf(szQuery, "EXEC OFFTRADE_DISCONNECT '%s'", szName);
			m_DBQuery.Exec(szQuery);
			m_DBQuery.Clear();
		}
		else if(lpMsg->OfflineType == 1)
		{
			// off exp user dc
			sprintf(szQuery, "EXEC OFFAFK_DISCONNECT '%s'", szName);
			m_DBQuery.Exec(szQuery);
			m_DBQuery.Clear();
		}
	}
}

// -------------------------------------------------------------------------------

void CExGDManager::DG_VoteBuffLoad(PMSG_REQ_VOTEBUFF_LOAD *aRecv, int uIndex)
{
	PMSG_ANS_VOTEBUFF_LOAD pMsg;
	ZeroMemory(&pMsg, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x0D, sizeof(pMsg));

	CString qSql;
	char szName[11];
	memcpy(szName, aRecv->szName, sizeof(szName)-1);
	szName[10] = 0;

	qSql.Format("EXEC EX_VOTEBUFF_LOAD '%s'", szName);

	pMsg.aIndex = aRecv->aIndex;

	if(m_DBQuery.Exec(qSql) == FALSE || m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return;
	}

	pMsg.MTBuffTime = m_DBQuery.GetInt("MTBuffTime");
	pMsg.QTBuffTime = m_DBQuery.GetInt("QTBuffTime");
	m_DBQuery.Clear();

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CExGDManager::GD_VoteBuffSave(PMSG_REQ_VOTEBUFF_SAVE* aRecv)
{
	CString qSql;
	char szName[11];
	memcpy(szName, aRecv->szName, sizeof(szName)-1);
	szName[10] = 0;
	qSql.Format("EXEC EX_VOTEBUFF_SAVE '%s', %d, %d", szName, aRecv->MTBuffTime, aRecv->QTBuffTime);
	m_DBQuery.Exec(qSql);
	m_DBQuery.Clear();
}
// -------------------------------------------------------------------------------

void CExGDManager::DG_ExQuestSystemLoad(PMSG_REQ_EXQUESTSYSTEM_LOAD *aRecv, int uIndex)
{
	PMSG_ANS_EXQUESTSYSTEM_LOAD pMsg;
	ZeroMemory(&pMsg, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x13, sizeof(pMsg));

	CString qSql;
	char szName[11];
	memcpy(szName, aRecv->Name, sizeof(szName)-1);
	szName[10] = 0;

	pMsg.aIndex = aRecv->aIndex;
	pMsg.bResult = true;

	qSql.Format("EXEC EX_EXQUESTSYSTEM_LOAD '%s'", szName);

	if(m_DBQuery.Exec(qSql) == FALSE || m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		pMsg.bResult = false;
	}
	else
	{
		pMsg.ExWQuestStart[0]    = m_DBQuery.GetInt("ExQuestStart_1");
		pMsg.ExWQuestNum[0]      = m_DBQuery.GetInt("ExQuestNum_1");
		pMsg.ExWQuestCount[0][0] = m_DBQuery.GetInt("ExQuestCount1_1");
		pMsg.ExWQuestCount[0][1] = m_DBQuery.GetInt("ExQuestCount2_1");
		pMsg.ExWQuestCount[0][2] = m_DBQuery.GetInt("ExQuestCount3_1");
		pMsg.ExWQuestCount[0][3] = m_DBQuery.GetInt("ExQuestCount4_1");
		pMsg.ExWQuestCount[0][4] = m_DBQuery.GetInt("ExQuestCount5_1");

		pMsg.ExWQuestStart[1]    = m_DBQuery.GetInt("ExQuestStart_2");
		pMsg.ExWQuestNum[1]      = m_DBQuery.GetInt("ExQuestNum_2");
		pMsg.ExWQuestCount[1][0] = m_DBQuery.GetInt("ExQuestCount1_2");
		pMsg.ExWQuestCount[1][1] = m_DBQuery.GetInt("ExQuestCount2_2");
		pMsg.ExWQuestCount[1][2] = m_DBQuery.GetInt("ExQuestCount3_2");
		pMsg.ExWQuestCount[1][3] = m_DBQuery.GetInt("ExQuestCount4_2");
		pMsg.ExWQuestCount[1][4] = m_DBQuery.GetInt("ExQuestCount5_2");

		pMsg.ExWQuestStart[2]    = m_DBQuery.GetInt("ExQuestStart_3");
		pMsg.ExWQuestNum[2]      = m_DBQuery.GetInt("ExQuestNum_3");
		pMsg.ExWQuestCount[2][0] = m_DBQuery.GetInt("ExQuestCount1_3");
		pMsg.ExWQuestCount[2][1] = m_DBQuery.GetInt("ExQuestCount2_3");
		pMsg.ExWQuestCount[2][2] = m_DBQuery.GetInt("ExQuestCount3_3");
		pMsg.ExWQuestCount[2][3] = m_DBQuery.GetInt("ExQuestCount4_3");
		pMsg.ExWQuestCount[2][4] = m_DBQuery.GetInt("ExQuestCount5_3");
	}

	m_DBQuery.Clear();

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CExGDManager::GD_ExQuestSystemSave(PMSG_REQ_EXQUESTSYSTEM_SAVE *aRecv)
{
	CString qSql;
	char szName[11];
	memcpy(szName, aRecv->Name, sizeof(szName)-1);
	szName[10] = 0;
	qSql.Format("EXEC EX_EXQUESTSYSTEM_SAVE '%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", szName,
		aRecv->ExWQuestStart[0], aRecv->ExWQuestNum[0], aRecv->ExWQuestCount[0][0], aRecv->ExWQuestCount[0][1], aRecv->ExWQuestCount[0][2], aRecv->ExWQuestCount[0][3], aRecv->ExWQuestCount[0][4],
		aRecv->ExWQuestStart[1], aRecv->ExWQuestNum[1], aRecv->ExWQuestCount[1][0], aRecv->ExWQuestCount[1][1], aRecv->ExWQuestCount[1][2], aRecv->ExWQuestCount[1][3], aRecv->ExWQuestCount[1][4],
		aRecv->ExWQuestStart[2], aRecv->ExWQuestNum[2], aRecv->ExWQuestCount[2][0], aRecv->ExWQuestCount[2][1], aRecv->ExWQuestCount[2][2], aRecv->ExWQuestCount[2][3], aRecv->ExWQuestCount[2][4]);
	m_DBQuery.Exec(qSql);
	m_DBQuery.Clear();
}
// -------------------------------------------------------------------------------