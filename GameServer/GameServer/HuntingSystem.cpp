#include "stdafx.h"
#include "HuntingSystem.h"
#include "../../Common/LCProtocol.h"
#include "GameMain.h"
#include "logproc.h"

CHuntingSystem g_HuntingSystem;

void CHuntingSystem::Init()
{
	m_SkillsMap.clear();
	m_NextExpMap.clear();
	m_MobExpMap.clear();

	m_Loaded = false;
}

void CHuntingSystem::Load()
{
	if (!LoadSkillAttr())
	{
		MessageBoxA(0, HUNTING_SYSTEM_ATTR_FILE, "CRITICAL ERROR", 0);
		return;
	}

	if (!LoadNextExp())
	{
		MessageBoxA(0, HUNTING_SYSTEM_EXP_TABLE, "CRITICAL ERROR", 0);
		return;
	}

	if (!LoadMobExp())
	{
		MessageBoxA(0, HUNTING_SYSTEM_MOB_EXP, "CRITICAL ERROR", 0);
		return;
	}

	m_Loaded = true;
}

void CHuntingSystem::UserConnect(int aIndex)
{
	if (!m_Loaded) return;

	if (!gObjIsConnected(aIndex)) return;

	LPOBJ lpObj = &gObj[aIndex];

	PMSG_HUNTING_DATA pMsg = { 0 };
	pMsg.h.set((LPBYTE)&pMsg, LC_HEADER, LC_HUNTING_DATA, sizeof(pMsg));
	pMsg.level = lpObj->m_HuntingLevel;
	pMsg.points = lpObj->m_HuntingPoints;
	pMsg.exp = lpObj->m_HuntingExp;

	pMsg.nextExp = m_NextExpMap[lpObj->m_HuntingLevel + 1];

	memcpy(pMsg.skills, lpObj->m_HuntingSkillLevel, sizeof(pMsg.skills));
}

void CHuntingSystem::CGSkillReq(PMSG_HUNTING_SKILL_REQ * lpMsg, int aIndex)
{
	if (!gObjIsConnected(aIndex))
	{
		LOG_ERROR("Not connected %d", aIndex);
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if (lpMsg->skill == 0xFF || lpMsg->skill >= eHS_CNT)
	{
		LOG_ERROR("[%d][%s][%s] Invalid skill idx received: %d", aIndex, lpObj->AccountID, lpObj->Name, lpMsg->skill);
		return;
	}

	auto skill = m_SkillsMap.find((EHuntingSkill)lpMsg->skill);

	if (skill == m_SkillsMap.end())
	{
		LOG_ERROR("[%d][%s][%s] No skill found for index: %d", aIndex, lpObj->AccountID, lpObj->Name, lpMsg->skill);
		return;
	}

	auto currentSkillLevel = lpObj->m_HuntingSkillLevel[lpMsg->skill];

	if (currentSkillLevel >= MAX_HUNTING_SKILL_LEVEL)
	{
		LOG_ERROR("[%d][%s][%s] Skill already on max level: %d", aIndex, lpObj->AccountID, lpObj->Name, lpMsg->skill);
		return;
	}

	auto reqPoints = skill->second.requiredSkills[currentSkillLevel + 1];

	if (lpObj->m_HuntingPoints < reqPoints)
	{
		LOG_ERROR("[%d][%s][%s] Not enought points to learn skill: %d", aIndex, lpObj->AccountID, lpObj->Name, lpMsg->skill);
		return;
	}

	lpObj->m_HuntingPoints -= reqPoints;
	lpObj->m_HuntingSkillLevel[lpMsg->skill]++;

	PMSG_HUNTING_SKILL_ANS pMsg = { 0 };
	pMsg.h.set((LPBYTE)&pMsg, LC_HEADER, LC_HUNTING_SKILL, sizeof(pMsg));
	pMsg.skill = lpMsg->skill;
	pMsg.newPoints = lpObj->m_HuntingPoints;
	pMsg.newSkillLevel = lpObj->m_HuntingSkillLevel[lpMsg->skill];

	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void CHuntingSystem::MobKilled(int aIndex, int mobIndex)
{
	if (!gObjIsConnected(aIndex))
	{
		LOG_ERROR("Not connected %d", aIndex);
		return;
	}

	auto mobExp = m_MobExpMap.find(mobIndex);

	if (mobExp == m_MobExpMap.end())
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	auto nextExp = m_NextExpMap.find(lpObj->m_HuntingLevel + 1);

	if (lpObj->m_HuntingExp + mobExp->second >= nextExp->second) //LevelUP
	{
		lpObj->m_HuntingLevel++;
		lpObj->m_HuntingPoints++;
		lpObj->m_HuntingExp = 0;

		auto newLvlNextExp = m_NextExpMap.find(lpObj->m_HuntingLevel + 1);

		if (newLvlNextExp == m_NextExpMap.end())
		{
			LOG_ERROR("No NextExp found for level %d", lpObj->m_HuntingLevel + 1);
			return;
		}

		PMSG_HUNTING_LEVEL_UP pMsg = { 0 };
		pMsg.h.set((LPBYTE)&pMsg, LC_HEADER, LC_HUNTING_LEVEL_UP, sizeof(pMsg));
		pMsg.level = lpObj->m_HuntingLevel;
		pMsg.points = lpObj->m_HuntingPoints;
		pMsg.nextExp = newLvlNextExp->second;

		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);

		MsgOutput(aIndex, "[Hunting System] Level UP!", mobExp->second);
	}
	else
	{
		lpObj->m_HuntingExp += mobExp->second;

		PMSG_HUNTING_EXP pMsg = { 0 };
		pMsg.h.set((LPBYTE)&pMsg, LC_HEADER, LC_HUNTING_EXP, sizeof(pMsg));
		pMsg.exp = mobExp->second;
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);

		MsgOutput(aIndex, "[Hunting System] %d Exp", mobExp->second);
	}
}

float CHuntingSystem::GetSkillIncValue(int aIndex, EHuntingSkill skill)
{
	if (gObjIsConnected(aIndex))
	{
		LPOBJ lpObj = &gObj[aIndex];

		auto skillIt = m_SkillsMap.find(skill);

		if (skillIt == m_SkillsMap.end())
		{
			LOG_ERROR("No Skill found for index %d", skill);
			return 0.0f;
		}

		auto totalInc = lpObj->m_HuntingSkillLevel[skill] * skillIt->second.IncPerLevel;

		return totalInc / 100.0f;
	}

	return 0.0f;
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

bool CHuntingSystem::LoadNextExp()
{
	FILE *file = fopen(gDirPath.GetNewPath(HUNTING_SYSTEM_EXP_TABLE), "r");

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

		int level;
		long exp;

		sscanf(Buff, "%d %ld", &level, &exp);

		if (level < 0)
		{
			return false;
		}

		m_NextExpMap[level] = exp;
	}

	fclose(file);

	return true;
}

bool CHuntingSystem::LoadMobExp()
{
	FILE *file = fopen(gDirPath.GetNewPath(HUNTING_SYSTEM_MOB_EXP), "r");

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

		int mobId;
		int exp;

		sscanf(Buff, "%d %d", &mobId, &exp);

		if (mobId < 0)
		{
			return false;
		}

		m_MobExpMap[mobId] = exp;
	}

	fclose(file);

	return true;
}
