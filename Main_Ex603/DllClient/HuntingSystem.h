#pragma once

#define MAX_HUNTING_SKILL_LEVEL	5
#define MAX_HUNTING_SKILL_REQ_CNT 3

#define HUNTING_SYSTEM_DESC_FILE ".\\Data\\Custom\\Configs\\Hunting\\SkillDescription.txt"
#define HUNTING_SYSTEM_NAMES_FILE ".\\Data\\Custom\\Configs\\Hunting\\SkillNames.txt"
#define HUNTING_SYSTEM_ATTR_FILE ".\\Data\\Custom\\Configs\\Hunting\\SkillAttr.txt"
#define HUNTING_SYSTEM_IMG_PATH "Custom\\Interface\\Hunting"

#include "Protocol.h"

#include <map>

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
	WORD		exp;
};

struct PMSG_HUNTING_LEVEL_UP
{
	PBMSG_HEAD2	h;
	WORD		level;
	WORD		points;
	DWORD		nextExp;
};

enum EHuntingImages
{
	eHS_IMG_BASE = 308600,

	eHS_IMG_DMGRATE = eHS_IMG_BASE,
	eHS_IMG_INCDMG,
	eHS_IMG_1HDMG,
	eHS_IMG_2HDMG,
	eHS_IMG_PETDMG,
	eHS_IMG_CRITDMG,
	eHS_IMG_EXCDMG,
	eHS_IMG_DBLDMG,
	eHS_IMG_IGNDMG,
	eHS_IMG_DEFRATE,
	eHS_IMG_INCDEF,
	eHS_IMG_SETDEF,
	eHS_IMG_SHLDDEF,
	eHS_IMG_DD,
	eHS_IMG_INCHEAL,
	eHS_IMG_INCAGGR,
	eHS_IMG_INCSTR,
	eHS_IMG_INCAGI,
	eHS_IMG_INCVIT,
	eHS_IMG_INCENE,
	eHS_IMG_INCCMD,
	eHS_IMG_SPCDROP,

	eHS_IMG_BG,
	eHS_IMG_CLOSE,
};



struct HuntingSkill
{
	EHuntingSkill type;
	std::string title;
	std::string description;
	BYTE pointsNeeded[MAX_HUNTING_SKILL_LEVEL];
	BYTE requiredSkills[MAX_HUNTING_SKILL_REQ_CNT];
	BYTE currentLevel;
	BYTE IncPerLevel;

	bool handOverPlusSkill;
	bool plusSkillClick;
	DWORD clickTick;
};

class CHuntingSystem
{
public:
	void Init();

	void Load();

	void LoadImages();
	void BindObjects();

	void DrawInterface();

	void GCParseData(PMSG_HUNTING_DATA* pMsg);
	void GCLearnSkillAnswer(PMSG_HUNTING_SKILL_ANS* pMsg);
	void GCEarnExp(PMSG_HUNTING_EXP* pMsg);
	void GCLevelUp(PMSG_HUNTING_LEVEL_UP* pMsg);

private:
	bool LoadSkillAttr();
	bool LoadSkillDesc();
	bool LoadSkillName();

	void DrawSkills();
	void DrawTooltip();

	void DrawInactiveConnections();
	void DrawActiveConnections();

	void TryLearnSkill(HuntingSkill* skill);

	std::map<EHuntingSkill, HuntingSkill> m_SkillsMap;

	WORD m_level;
	DWORD m_currentExp;
	DWORD m_nextExp;
	WORD m_points;

};

extern CHuntingSystem g_HuntingSystem;