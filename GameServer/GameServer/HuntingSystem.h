#pragma once

#define MAX_HUNTING_SKILL_LEVEL	5
#define MAX_HUNTING_SKILL_REQ_CNT 3

#define HUNTING_SYSTEM_ATTR_FILE "Custom\\Hunting\\SkillAttr.txt"

struct PMSG_HUNTING_DATA
{
	PBMSG_HEAD2	h;
	WORD		level;
	WORD		points;
	DWORD		exp;
	DWORD		nextExp;
	BYTE		skills[EHuntingSkill::eHS_CNT];
};

struct PMSG_HUNTING_SKILL_REQ
{
	PBMSG_HEAD2	h;
	BYTE		skill;
};

struct PMSG_HUNTING_SKILL_ANS
{
	PBMSG_HEAD2	h;
	BYTE		skill;
	BYTE		newSkillLevel;
	BYTE		newPoints;
};

struct PMSG_HUNTING_EXP
{
	PBMSG_HEAD2	h;
	DWORD		exp;
};

struct PMSG_HUNTING_LEVEL_UP
{
	PBMSG_HEAD2	h;
	WORD		level;
	WORD		points;
	DWORD		exp;
	DWORD		nextExp;
};

enum EHuntingSkill
{
	eHS_DMGRATE,
	eHS_INCDMG,
	eHS_1HDMG,
	eHS_2HDMG,
	eHS_PETDMG,
	eHS_CRITDMG,
	eHS_EXCDMG,
	eHS_DBLDMG,
	eHS_IGNDMG,

	eHS_DEFRATE,
	eHS_INCDEF,
	eHS_SETDEF,
	eHS_SHLDDEF,
	eHS_DD,
	eHS_INCHEAL,
	eHS_INCAGGR,

	eHS_INCSTR,
	eHS_INCAGI,
	eHS_INCVIT,
	eHS_INCENE,
	eHS_INCCMD,
	eHS_SPCDROP,

	eHS_CNT,
};

struct HuntingSkill
{
	EHuntingSkill type;
	BYTE pointsNeeded[MAX_HUNTING_SKILL_LEVEL];
	BYTE requiredSkills[MAX_HUNTING_SKILL_REQ_CNT];
	BYTE IncPerLevel;
};

class CHuntingSystem
{
public:
	void Init();
	void Load();

private:
	bool LoadSkillAttr();

	std::map<EHuntingSkill, HuntingSkill> m_SkillsMap;
};


extern CHuntingSystem g_HuntingSystem;