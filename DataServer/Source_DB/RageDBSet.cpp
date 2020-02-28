#include "StdAfx.h"
#include "RageDBSet.h"
#include "winutil.h"
#include "MainFrm.h"

cRageSystem::cRageSystem()
{
}

cRageSystem::~cRageSystem()
{
}

bool cRageSystem::Connect()
{
	return m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);
}

void cRageSystem::SendRageUser(DSQuerySend * Recv, int aIndex)
{
	//DSRageUser rSend;
	//rSend.h.c = PMHC_BYTE;
	//rSend.h.size = sizeof(DSRageUser);
	//rSend.h.headcode = 0xE0;
	//rSend.Result = 1;

	//rSend.aIndex = Recv->aIndex;

	//char szAccountId[11];
	//char Name[11];

	//szAccountId[MAX_IDSTRING] = '\0';
	//Name[MAX_IDSTRING] = '\0';

	//memcpy(Name, Recv->Name, MAX_IDSTRING);
	//memcpy(szAccountId, Recv->Accaunt, MAX_IDSTRING);

	//rSend.Accaunt[MAX_IDSTRING] = '\0';
	//memcpy(rSend.Accaunt, szAccountId, MAX_IDSTRING);

	//if ( SpaceSyntexCheck(Name) == FALSE )
	//{
	//	rSend.Result = 0;
	//}

	//if ( this->SelectRage(szAccountId,Name,&rSend) == FALSE )
	//{
	//	rSend.Result = 0;
	//}

	//wsjServer.DataSend(aIndex, (char*)&rSend, rSend.h.size);
}

bool cRageSystem::SelectRage(char* Name, BYTE* btRageData)
{
	return false;
	//CString qSql;

	//qSql.Format("SELECT * FROM RageSystem WHERE Name = '%s'", Name);

	//if( !m_DBQuery.Exec(qSql) || m_DBQuery.Fetch() == SQL_NO_DATA )
	//{
	//	m_DBQuery.Clear();
	//	// ----
	//	LogAddC(LOGC_RED,"[%s] Failed to select values [Next: INSERT]", __FUNCTION__);

	//	char NextSQLpq[1024] = "INSERT INTO RageSystem (Accaunt,Name,RageLevel,RagePoint,RageExp,Damage,FreePoints,SummonPet,WingsDamagePlus,FinalMana,IgnoreDefence,ResetLevel,Teleport,CriticalDamageRate,AbsordDamage,PetDamageBonus,FinalLife,Strength,DefenceRate,";
	//		strcat(NextSQLpq,"FireDamage,Energy,Agility,DoubleDamage,FinalSD,FinalDefence,ZenDrop,GuildBonus,ReflectDamage,ExellentDamageRate,PvPBonusPlus,MinDefence,Experience,StartSD,PartyBonus,IceDamage,DistanceAttack,AttackRate,");
	//		strcat(NextSQLpq,"WeaponBonus,ExellentDamage,CriticalDamage)");
	//		strcat(NextSQLpq,"VALUES ('%s','%s',1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)");

	//	qSql.Format(NextSQLpq,Name);

	//	if( !m_DBQuery.Exec(qSql) )
	//	{
	//		LogAddC(LOGC_RED,"[%s] Failed to insert new values", __FUNCTION__);
	//		m_DBQuery.Clear();
	//		return FALSE;
	//	}
	//	m_DBQuery.Clear();

	//	qSql.Format("SELECT * FROM RageSystem WHERE Accaunt = '%s' AND Name = '%s'",Accaunt,Name);

	//	if( !m_DBQuery.Exec(qSql) || m_DBQuery.Fetch() == SQL_NO_DATA )
	//	{
	//		m_DBQuery.Clear();
	//		LogAddC(LOGC_RED,"[%s] Failed to select values [Next: Return]", __FUNCTION__);
	//		return FALSE;
	//	}
	//}
	//else
	//{
	//	Recv->rLevel = m_DBQuery.GetInt("RageLevel");
	//	Recv->rPoints = m_DBQuery.GetInt("RagePoint");
	//	Recv->rExperience = m_DBQuery.GetInt("RageExp");
	//	Recv->Damage = m_DBQuery.GetInt("Damage");	
	//	Recv->FreePoints = m_DBQuery.GetInt("FreePoints");
	//	Recv->SummonPet = m_DBQuery.GetInt("SummonPet");
	//	Recv->WingsDamagePlus = m_DBQuery.GetInt("WingsDamagePlus");
	//	Recv->FinalMana = m_DBQuery.GetInt("FinalMana");
	//	Recv->IgnoreDefence = m_DBQuery.GetInt("IgnoreDefence");
	//	Recv->ResetLevel = m_DBQuery.GetInt("ResetLevel");
	//	Recv->Teleport = m_DBQuery.GetInt("Teleport");
	//	Recv->CriticalDamageRate = m_DBQuery.GetInt("CriticalDamageRate");
	//	Recv->AbsordDamage = m_DBQuery.GetInt("AbsordDamage");
	//	Recv->PetDamageBonus = m_DBQuery.GetInt("PetDamageBonus");
	//	Recv->FinalLife = m_DBQuery.GetInt("FinalLife");
	//	Recv->Strength = m_DBQuery.GetInt("Strength");
	//	Recv->DefenceRate = m_DBQuery.GetInt("DefenceRate");
	//	Recv->FireDamage = m_DBQuery.GetInt("FireDamage");
	//	Recv->Energy = m_DBQuery.GetInt("Energy");
	//	Recv->Agility = m_DBQuery.GetInt("Agility");
	//	Recv->DoubleDamage = m_DBQuery.GetInt("DoubleDamage");
	//	Recv->FinalSD = m_DBQuery.GetInt("FinalSD");
	//	Recv->FinalDefence = m_DBQuery.GetInt("FinalDefence");
	//	Recv->ZenDrop = m_DBQuery.GetInt("ZenDrop");
	//	Recv->GuildBonus = m_DBQuery.GetInt("GuildBonus");
	//	Recv->ReflectDamage = m_DBQuery.GetInt("ReflectDamage");
	//	Recv->ExellentDamageRate = m_DBQuery.GetInt("ExellentDamageRate");
	//	Recv->PvPBonusPlus = m_DBQuery.GetInt("PvPBonusPlus");
	//	Recv->MinDefence = m_DBQuery.GetInt("MinDefence");
	//	Recv->Experience = m_DBQuery.GetInt("Experience");
	//	Recv->StartSD = m_DBQuery.GetInt("StartSD");
	//	Recv->PartyBonus = m_DBQuery.GetInt("PartyBonus");
	//	Recv->IceDamage = m_DBQuery.GetInt("IceDamage");
	//	Recv->DistanceAttack = m_DBQuery.GetInt("DistanceAttack");
	//	Recv->AttackRate = m_DBQuery.GetInt("AttackRate");
	//	Recv->WeaponBonus = m_DBQuery.GetInt("WeaponBonus");
	//	Recv->ExellentDamage = m_DBQuery.GetInt("ExellentDamage");
	//	Recv->CriticalDamage = m_DBQuery.GetInt("CriticalDamage");

	//	m_DBQuery.Clear();
	//}
}

void cRageSystem::SaveRageSkill(DBRageUserSave *p)
{
	//if ( strlen(p->Name) < 1 )
	//{
	//	LogAdd("error-L2 : Name is zero %s %d", __FILE__, __LINE__);
	//	return;
	//}
	//
	//char szName[11];
	//char szAccountId[11];

	//szAccountId[MAX_IDSTRING] = '\0';
	//szName[MAX_IDSTRING] = '\0';

	//memcpy(szName, p->Name, MAX_IDSTRING);
	//memcpy(szAccountId, p->Accaunt, MAX_IDSTRING);

	//CString qSql;

	//char chBuffer[4024] = "UPDATE RageSystem SET RageLevel=%d, RagePoint=%d, RageExp=%d, Damage=%d, FreePoints=%d, SummonPet=%d, WingsDamagePlus=%d, FinalMana=%d, IgnoreDefence=%d, ResetLevel=%d, Teleport=%d, CriticalDamageRate=%d, AbsordDamage=%d, PetDamageBonus=%d, FinalLife=%d, Strength=%d, DefenceRate=%d, FireDamage=%d, ";

	//strcat(chBuffer, " Energy=%d, ");
	//strcat(chBuffer, " Agility=%d,  ");
	//strcat(chBuffer, " DoubleDamage=%d, ");
	//strcat(chBuffer, " FinalSD=%d, ");
	//strcat(chBuffer, " FinalDefence=%d, ");
	//strcat(chBuffer, " ZenDrop=%d, ");
	//strcat(chBuffer, " GuildBonus=%d, ");

	//strcat(chBuffer, " ReflectDamage=%d, ");
	//strcat(chBuffer, " ExellentDamageRate=%d ");
	//strcat(chBuffer, ", PvPBonusPlus=%d ");	//ExAdd Resets
	//strcat(chBuffer, ", MinDefence=%d ");	//ExAdd GResets
	//strcat(chBuffer, ", Experience=%d ");	//GensNumber
	//strcat(chBuffer, ", StartSD=%d ");	//GensRang
	//strcat(chBuffer, ", PartyBonus=%d ");	//GensExp
	//strcat(chBuffer, ", IceDamage=%d ");	//GensReward
	//strcat(chBuffer, ", DistanceAttack=%d ");
	//strcat(chBuffer, ", AttackRate=%d ");
	//strcat(chBuffer, ",WeaponBonus=%d ");
	//strcat(chBuffer, ",ExellentDamage=%d ");
	//strcat(chBuffer, ",CriticalDamage=%d ");
	//strcat(chBuffer, " WHERE Accaunt = '%s' AND Name = '%s'");

	//qSql.Format(chBuffer,p->rLevel,p->rPoints,p->rExperience,p->Damage,p->FreePoints,p->SummonPet,p->WingsDamagePlus,p->FinalMana,p->IgnoreDefence,p->ResetLevel,p->Teleport,
	//	p->CriticalDamageRate,p->AbsordDamage,p->PetDamageBonus,p->FinalLife,p->Strength,p->DefenceRate,p->FireDamage,
	//	p->Energy,
	//	p->Agility,
	//	p->DoubleDamage,
	//	p->FinalSD,
	//	p->FinalDefence,
	//	p->ZenDrop,
	//	p->GuildBonus,
	//	p->ReflectDamage,
	//	p->ExellentDamageRate,
	//	p->PvPBonusPlus,
	//	p->MinDefence,
	//	p->Experience,
	//	p->StartSD,
	//	p->PartyBonus,
	//	p->IceDamage,
	//	p->DistanceAttack,
	//	p->AttackRate,
	//	p->WeaponBonus,
	//	p->ExellentDamage,
	//	p->CriticalDamage,
	//	szAccountId,
	//	szName
	//	);

	////LogAddC(LOGC_BLUE,"p->Name: %s", p->Name);

	//if(m_DBQuery.Exec(qSql) == FALSE)
	//{
	//	return;
	//}

	//m_DBQuery.Clear();
}