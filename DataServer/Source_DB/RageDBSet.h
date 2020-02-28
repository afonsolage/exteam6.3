#pragma once

#include "Sprodef.h"

#include ".\\DbSet\\DBConBase.h"

struct DSQuerySend
{
	PBMSG_HEAD h;
	int aIndex;
	char AccountID[11];
	char Name[11];
};

struct DSRageUser
{
	PBMSG_HEAD h;
	int aIndex;
	char AccountID[11];
	char Name[11];
	bool bResult;
	unsigned short rLevel;
	unsigned short rPoints;
	unsigned int rExperience;
	unsigned char Damage;
	unsigned char FreePoints;
	unsigned char SummonPet;
	unsigned char WingsDamagePlus;
	unsigned char FinalMana;
	unsigned char IgnoreDefence;
	unsigned char ResetLevel;
	unsigned char Teleport;
	unsigned char CriticalDamageRate;
	unsigned char AbsordDamage;
	unsigned char PetDamageBonus;
	unsigned char FinalLife;
	unsigned char Strength;
	unsigned char DefenceRate;
	unsigned char FireDamage;
	unsigned char Energy;
	unsigned char Agility;
	unsigned char DoubleDamage;
	unsigned char FinalSD;
	unsigned char FinalDefence;
	unsigned char ZenDrop;
	unsigned char GuildBonus;
	unsigned char ReflectDamage;
	unsigned char ExellentDamageRate;
	unsigned char PvPBonusPlus;
	unsigned char MinDefence;
	unsigned char Experience;
	unsigned char StartSD;
	unsigned char PartyBonus;
	unsigned char IceDamage;
	unsigned char DistanceAttack;
	unsigned char AttackRate;
	unsigned char WeaponBonus;
	unsigned char ExellentDamage;
	unsigned char CriticalDamage;
};

struct DBRageUserSave
{
	PBMSG_HEAD h;
	char Name[11];
	unsigned short rLevel;
	unsigned short rPoints;
	unsigned int rExperience;
	unsigned char Damage;
	unsigned char FreePoints;
	unsigned char SummonPet;
	unsigned char WingsDamagePlus;
	unsigned char FinalMana;
	unsigned char IgnoreDefence;
	unsigned char ResetLevel;
	unsigned char Teleport;
	unsigned char CriticalDamageRate;
	unsigned char AbsordDamage;
	unsigned char PetDamageBonus;
	unsigned char FinalLife;
	unsigned char Strength;
	unsigned char DefenceRate;
	unsigned char FireDamage;
	unsigned char Energy;
	unsigned char Agility;
	unsigned char DoubleDamage;
	unsigned char FinalSD;
	unsigned char FinalDefence;
	unsigned char ZenDrop;
	unsigned char GuildBonus;
	unsigned char ReflectDamage;
	unsigned char ExellentDamageRate;
	unsigned char PvPBonusPlus;
	unsigned char MinDefence;
	unsigned char Experience;
	unsigned char StartSD;
	unsigned char PartyBonus;
	unsigned char IceDamage;
	unsigned char DistanceAttack;
	unsigned char AttackRate;
	unsigned char WeaponBonus;
	unsigned char ExellentDamage;
	unsigned char CriticalDamage;
};

class cRageSystem
{
public:
	cRageSystem();
	virtual ~cRageSystem();

	bool Connect();

	void SendRageUser(DSQuerySend *Recv, int aIndex);
	bool SelectRage(char* Name, BYTE* btRageData);
	void SaveRageSkill(DBRageUserSave* p);

	CQuery m_DBQuery;
};
