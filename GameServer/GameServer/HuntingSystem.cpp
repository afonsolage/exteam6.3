#include "stdafx.h"
#include "HuntingSystem.h"
#include "../../Common/LCProtocol.h"
#include "GameMain.h"

CHuntingSystem g_HuntingSystem;

void CHuntingSystem::Init()
{

}

void CHuntingSystem::Load()
{
	if (!LoadSkillAttr())
	{
		MessageBoxA(0, HUNTING_SYSTEM_ATTR_FILE, "CRITICAL ERROR", 0);
		return;
	}
}

bool CHuntingSystem::LoadSkillAttr()
{
	FILE *file = fopen(gDirPath.GetNewPath(HUNTING_SYSTEM_ATTR_FILE), "r");

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