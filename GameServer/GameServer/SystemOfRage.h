#include "StdAfx.h"
#include "user.h"

//#ifdef _SYSTEM_OF_RAGE_

#define R_MAX_SKILL 36
#define R_MAX_LEVEL 10000

#define RAGE_DEBUG		0
#define RAGE_NEWSAVE	1

#define RAGE_SYSTEM_DIR "..\\Data\\ExData\\RageSystem.ini"



//#define DEBUG_RAGE 0

struct RageUser
{
	int LoadInfo;
	int rLevel;	//2
	int rPoints;	//4
	int rExperience;	//8
	int NextrExperience;	//HZ
	//---
	int Damage;	//10
	int FreePoints;//12
	int SummonPet;//14
	int WingsDamagePlus;//16
	int FinalMana;//18
	int IgnoreDefence;//20
	int ResetLevel;//
	int Teleport;//
	int CriticalDamageRate;//
	int AbsordDamage;//
	int PetDamageBonus;//
	//--- 2
	int FinalLife;//
	int Strength;//
	int DefenceRate;//
	int FireDamage;//
	int Energy;//
	int Agility;//
	int DoubleDamage;//
	int FinalSD;//
	int FinalDefence;//
	int ZenDrop;//
	int GuildBonus;//
	//--- 3
	int ReflectDamage;//
	int ExellentDamageRate;//
	int PvPBonusPlus;
	int MinDefence;//
	int Experience;//
	int StartSD;//
	int PartyBonus;//
	int IceDamage;//
	int DistanceAttack;//
	int AttackRate;//
	int WeaponBonus;//
	//--- 4
	int ExellentDamage;//
	int CriticalDamage;//
};

enum RageSkillID
{
	eSkill1 = 1,
	eSkill2,
	eSkill3,
	eSkill4,
	eSkill5,
	eSkill6,
	eSkill7,
	eSkill8,
	eSkill9,
	eSkill10,
	eSkill11,
	eSkill12,
	eSkill13,
	eSkill14,
	eSkill15,
	eSkill16,
	eSkill17,
	eSkill18,
	eSkill19,
	eSkill20,
	eSkill21,
	eSkill22,
	eSkill23,
	eSkill24,
	eSkill25,
	eSkill26,
	eSkill27,
	eSkill28,
	eSkill29,
	eSkill30,
	eSkill31,
	eSkill32,
	eSkill33,
	eSkill34,
	eSkill35,

	eSkillReset,
};

struct RageSkill
{
	char Name[50];
	int StartDamage;
	int MaxPoint;
	bool Percent;
	int PointNext;
};

// ----

struct ClickSend
{
	PBMSG_HEAD2 h;
	BYTE Click;
	WORD SkillID;
};

struct sRageUserSend
{
	PBMSG_HEAD2 h;
	int rLevel;
	int rPoints;
	int rExperience;
	//---
	int Damage;	//
	int FreePoints;//
	int SummonPet;//
	int WingsDamagePlus;//
	int FinalMana;//
	int IgnoreDefence;//
	int ResetLevel;//
	int Teleport;//
	int CriticalDamageRate;//
	int AbsordDamage;//
	int PetDamageBonus;//
	//--- 2
	int FinalLife;//
	int Strength;//
	int DefenceRate;//
	int FireDamage;//
	int Energy;//
	int Agility;//
	int DoubleDamage;//
	int FinalSD;//
	int FinalDefence;//
	int ZenDrop;//
	int GuildBonus;//
	//--- 3
	int ReflectDamage;//
	int ExellentDamageRate;//
	int PvPBonusPlus;//
	int MinDefence;//
	int Experience;//
	int StartSD;//
	int PartyBonus;//
	int IceDamage;//
	int DistanceAttack;//
	int AttackRate;//
	int WeaponBonus;//
	//--- 4
	int ExellentDamage;//
	int CriticalDamage;//
	//---
	int NextExp;
};

struct RageExpSend
{
	PBMSG_HEAD2 h;
	int Level;
	int Point;
	int Exp;
	int NextExp;
};

struct sRageTabSend
{
	PBMSG_HEAD2 h;
	int Num;
};

struct sConfigStruct
{
	PBMSG_HEAD2 h;
	BYTE SkillID;
	char Name[25];
	int Damage;
	int MaxPoint;
	int PointNext;
	BYTE Percent;
};
// ----
struct DSQuerySend
{
	PBMSG_HEAD h;
	int aIndex;
	char Name[11];
};

struct DSRageUser
{
	PBMSG_HEAD h;
	int aIndex;
	char Name[11];
	bool bResult;
	BYTE RageSystem[152];
};

struct DBRageUserSave
{
	PBMSG_HEAD h;
	char Name[11];
	BYTE RageSystem[152];
};

struct PMSG_REQ_RESETRAGE
{
	PBMSG_HEAD2 h;
	int ResetRageWCoin;
	int ResetRageCredit;
};

struct PMSG_ANS_RESETRAGE
{
	PBMSG_HEAD2 h;
	BYTE Result;
};

class cSystemOfRage
{
private:
	bool Enable;
	int MaxLevel;
	int AddExp;

	int TeleportMap;
	int TeleportX;
	int TeleportY;

	int CreateMob;
	int rPointLvl;

	int NextExp;
	int MobExpLvL;

	int NeedLevel;
	int NeedMasterLevel;

public:
	void Load();
	void LoadSkill(int ID, char *cName, int a1, int a2, int NextPoint, bool Percent);

	void FilterSkill(int aIndex, int SkillID);
	int ReturnPoint(int aIndex, int SkillID);
	int ReturnCalc(int aIndex, int SkillID, int Pw);
	

	void DataRecv(ClickSend *aRecv, int aIndex);
	void RecvActiveSkill(sRageTabSend *aRecv, int aIndex);

	void CalcCharacter(int aIndex);
	void CalcStats(int aIndex);

	void SummonPetSkill(int aIndex);
	void TeleportSkill(int aIndex);
	void DropZen (int aIndex, float & money);
	void ExpFunction(int aIndex, __int64 & exp);
	void AttackDefenceRate(int aIndex, int Target, float &Attack, float &Defence);
	void ExlCritDamage(int aIndex, int effect, int &AttackDamage);
	void AttackDamageRG(LPOBJ lpObj, LPOBJ lpTarget, int &dmg, bool bDamageReflect);

	void RageExpFunction(LPOBJ lpObj, LPOBJ TargetObj);

	void SendUser(int aIndex);

	void ConfigSend(int aIndex);

	void SendDataServer(int aIndex,char * NAme);
	void RecvDSProtocol(DSRageUser *aRecv);

	void RageConnect(int aIndex);

	void SendSaveData(int aIndex);
	void JewelsDropRate(LPOBJ lpObj, LPOBJ lpMobObj);

	bool GetActive();

	void RageClientSend();

	void NewDBSave(int aIndex, LPBYTE buf);
	void NewDBLoad(int aIndex, LPBYTE buf);

	// ----
	RageUser rUser[OBJMAX];
	RageSkill rSkill[R_MAX_SKILL];

	// -> Rage reset

	void CharacterZero(int aIndex);
	bool NpcDialog(int aIndex, int aNpcIndex);
	void CGRageReset(int aIndex, PMSG_ANS_RESETRAGE* lpMsg);

	void EvoRageReset(int aIndex);

	short m_sNPC_Class;
	BYTE m_btNPC_Map;
	BYTE m_btNPC_X;
	BYTE m_btNPC_Y;
	int m_ResetRageWCoin;
	int m_ResetRageCredit;

};
extern cSystemOfRage gSystemOfRage;

//#endif