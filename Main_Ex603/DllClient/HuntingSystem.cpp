#include "stdafx.h"
#include "HuntingSystem.h"
#include "ReadScript.h"
#include "Interface.h"

CHuntingSystem g_HuntingSystem;

void CHuntingSystem::Init()
{
	m_SkillsMap.clear();
}

void CHuntingSystem::Load()
{
	if (!LoadSkillAttr() || !LoadSkillDesc() || !LoadSkillName())
	{
		MessageBoxA(0, "CORRUPTED FILES. REINSTALL YOUR CLIENT.", "CRITICAL ERROR", 0);
		exit(1);
	}

	BindObjects();
}

bool CHuntingSystem::LoadSkillAttr()
{
	FILE *file = fopen(HUNTING_SYSTEM_ATTR_FILE, "r");

	if (file == NULL)
	{
		return false;
	}

	char Buff[2048] = { 0 };

	int Flag = 0;
	while (!feof(file))
	{
		fgets(Buff, 2568, file);

		if (Buff[0] == '/' && Buff[1] == '/')
			continue;

		int id;
		int incPts;
		int lvl1Pts;
		int lvl2Pts;
		int lvl3Pts;
		int lvl4Pts;
		int lvl5Pts;
		int req1Skill;
		int	req2Skill;
		int req3Skill;

		sscanf(Buff, "%d %d %d %d %d %d %d %d %d %d",
			&id, &incPts, &lvl1Pts, &lvl2Pts, &lvl3Pts, &lvl4Pts, &lvl5Pts, &req1Skill, &req2Skill, &req3Skill);

		if (id < 0 || id >= EHuntingSkill::eHS_CNT)
		{
			return false;
		}

		auto skillId = (EHuntingSkill)id;
		HuntingSkill skill = {};
		skill.type = skillId;
		skill.IncPerLevel = incPts;
		skill.pointsNeeded[0] = lvl1Pts;
		skill.pointsNeeded[1] = lvl2Pts;
		skill.pointsNeeded[2] = lvl3Pts;
		skill.pointsNeeded[3] = lvl4Pts;
		skill.pointsNeeded[4] = lvl5Pts;
		skill.requiredSkills[0] = req1Skill;
		skill.requiredSkills[1] = req2Skill;
		skill.requiredSkills[2] = req3Skill;

		m_SkillsMap[skillId] = skill;
	}

	fclose(file);

	return true;
}

bool CHuntingSystem::LoadSkillDesc()
{
	FILE *file = fopen(HUNTING_SYSTEM_DESC_FILE, "r");

	if (file == NULL)
	{
		return false;
	}

	char Buff[2048] = { 0 };

	int Flag = 0;
	while (!feof(file))
	{
		fgets(Buff, 2568, file);

		if (Buff[0] == '/' && Buff[1] == '/')
			continue;

		int id;
		char desc[1024];

		sscanf(Buff, "%d %[^\t\n]", &id, &desc);

		if (id < 0 || id >= EHuntingSkill::eHS_CNT) return false;

		auto skillId = (EHuntingSkill)id;
		auto skill = m_SkillsMap.find(skillId);

		if (skill == m_SkillsMap.end()) return false;

		skill->second.description = desc;
	}

	fclose(file);

	return true;
}

bool CHuntingSystem::LoadSkillName()
{
	FILE *file = fopen(HUNTING_SYSTEM_NAMES_FILE, "r");

	if (file == NULL)
	{
		return false;
	}

	char Buff[2048] = { 0 };

	int Flag = 0;
	while (!feof(file))
	{
		fgets(Buff, 2568, file);

		if (Buff[0] == '/' && Buff[1] == '/')
			continue;

		int id;
		char desc[1024];

		sscanf(Buff, "%d %[^\t\n]", &id, &desc);

		if (id < 0 || id >= EHuntingSkill::eHS_CNT) return false;

		auto skillId = (EHuntingSkill)id;
		auto skill = m_SkillsMap.find(skillId);

		if (skill == m_SkillsMap.end()) return false;

		skill->second.title = desc;
	}

	fclose(file);

	return true;
}

void CHuntingSystem::LoadImages()
{
	char tmp[256] = { 0 };
	
	for (auto i = 0; i < EHuntingSkill::eHS_CNT; i++)
	{
		sprintf(tmp, "%s\\skill%02d.tga", HUNTING_SYSTEM_IMG_PATH, i);

		gInterface.LoadImages(tmp, EHuntingImages::eHS_IMG_BASE + (i * 2), 0x2601, 0x2900, 1);

		sprintf(tmp, "%s\\skill%02d_g.tga", HUNTING_SYSTEM_IMG_PATH, i);

		gInterface.LoadImages(tmp, EHuntingImages::eHS_IMG_BASE + (i * 2) + 1, 0x2601, 0x2900, 1);
	}
}

void CHuntingSystem::BindObjects()
{
	gInterface.BindObject(eHS_OBJ_DMGRATE, eHS_IMG_DMGRATE, 40, 40, 380, 60);
	gInterface.BindObject(eHS_OBJ_INCDMG, eHS_IMG_INCDMG, 40, 40, 380, 120);
	gInterface.BindObject(eHS_OBJ_1HDMG, eHS_IMG_1HDMG, 40, 40, 320, 180);
	gInterface.BindObject(eHS_OBJ_2HDMG, eHS_IMG_2HDMG, 40, 40, 380, 180);
	gInterface.BindObject(eHS_OBJ_PETDMG, eHS_IMG_PETDMG, 40, 40, 440, 180);
	gInterface.BindObject(eHS_OBJ_CRITDMG, eHS_IMG_CRITDMG, 40, 40, 380, 240);
	gInterface.BindObject(eHS_OBJ_EXCDMG, eHS_IMG_EXCDMG, 40, 40, 380, 300);
	gInterface.BindObject(eHS_OBJ_DBLDMG, eHS_IMG_DBLDMG, 40, 40, 380, 360);
	gInterface.BindObject(eHS_OBJ_IGNDMG, eHS_IMG_IGNDMG, 40, 40, 380, 420);

	gInterface.BindObject(eHS_OBJ_DEFRATE, eHS_IMG_DEFRATE, 40, 40, 200, 60);
	gInterface.BindObject(eHS_OBJ_INCDEF, eHS_IMG_INCDEF, 40, 40, 200, 120);
	gInterface.BindObject(eHS_OBJ_SETDEF, eHS_IMG_SETDEF, 40, 40, 140, 180);
	gInterface.BindObject(eHS_OBJ_SHLDDEF, eHS_IMG_SHLDDEF, 40, 40, 260, 180);
	gInterface.BindObject(eHS_OBJ_DD, eHS_IMG_DD, 40, 40, 200, 240);
	gInterface.BindObject(eHS_OBJ_INCHEAL, eHS_IMG_INCHEAL, 40, 40, 140, 300);
	gInterface.BindObject(eHS_OBJ_INCAGGR, eHS_IMG_INCAGGR, 40, 40, 140, 300);

	gInterface.BindObject(eHS_OBJ_INCSTR, eHS_IMG_INCSTR, 40, 40, 80, 60);
	gInterface.BindObject(eHS_OBJ_INCAGI, eHS_IMG_INCAGI, 40, 40, 80, 120);
	gInterface.BindObject(eHS_OBJ_INCVIT, eHS_IMG_INCVIT, 40, 40, 80, 180);
	gInterface.BindObject(eHS_OBJ_INCENE, eHS_IMG_INCENE, 40, 40, 80, 240);
	gInterface.BindObject(eHS_OBJ_INCCMD, eHS_IMG_INCCMD, 40, 40, 80, 300);
	gInterface.BindObject(eHS_OBJ_SPCDROP, eHS_IMG_SPCDROP, 40, 40, 80, 360);
}

void CHuntingSystem::DrawInterface()
{
	if (!gInterface.CheckWindowEx(ObjWindowsEx::exWinHuntingSystem))
	{
		return;
	}

	pSetCursorFocus = true;

	//TODO: Draw bg, close icon, skills and rest
}
