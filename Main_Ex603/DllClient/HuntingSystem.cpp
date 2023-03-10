#include "stdafx.h"
#include "HuntingSystem.h"
#include "ReadScript.h"
#include "Interface.h"
#include "User.h"
#include "Controller.h"
#include "..\..\Common\LCProtocol.h"

CHuntingSystem g_HuntingSystem;

void CHuntingSystem::Init()
{
	m_SkillsMap.clear();
	m_currentExp = 0;
	m_nextExp = 0;
	m_points = 0;
	m_level = 0;
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

void CHuntingSystem::DrawSkills()
{
	auto now = GetTickCount();

	for (auto i = 0; i < EHuntingSkill::eHS_CNT; i++)
	{
		auto skillObjIdx = eHS_OBJ_BASE + i;
		gInterface.DrawGUI(skillObjIdx);

		auto skill = &m_SkillsMap[(EHuntingSkill)i];

		if (skill->currentLevel == 0)
		{
			auto x = gInterface.Data[skillObjIdx].X;
			auto y = gInterface.Data[skillObjIdx].Y;
			auto w = gInterface.Data[skillObjIdx].Width;
			auto h = gInterface.Data[skillObjIdx].Height;

			pDrawColorButton(0x7880, x, y, w, h, NULL, NULL, Color4f(0, 0, 0, 150));
		}

		bool canLearnSkill = skill->currentLevel < MAX_HUNTING_SKILL_LEVEL;

		if (canLearnSkill)
		{
			auto reqPoints = skill->pointsNeeded[skill->currentLevel];
			canLearnSkill = m_points >= reqPoints;
		}

		if (canLearnSkill)
		{
			for (auto k = 0; k < MAX_HUNTING_SKILL_REQ_CNT; k++)
			{
				if (skill->requiredSkills[k] == 0xFF)
					continue;

				auto reqSkill = skill->requiredSkills[k];

				if (m_SkillsMap[(EHuntingSkill)reqSkill].currentLevel >= 2)
				{
					canLearnSkill = true;
					break;
				}
				else
				{
					canLearnSkill = false;
				}
			}

			if (canLearnSkill)
			{
				auto plusIconX = gInterface.Data[skillObjIdx].X + gInterface.Data[skillObjIdx].Width - 15;
				auto plusIconY = gInterface.Data[skillObjIdx].Y;
				auto plusIconW = 15;
				auto plusIconH = 15;

				auto delay = now - skill->clickTick;

				pDrawGUI(0x7AA4, plusIconX, plusIconY, plusIconW, plusIconH);

				if (gInterface.IsWorkZone(plusIconX, plusIconY, plusIconX + plusIconW, plusIconY + plusIconH))
				{
					skill->handOverPlusSkill = true;

					if (delay > 300)
					{
						if (gController.wMouse == WM_LBUTTONDOWN)
						{
							skill->plusSkillClick = true;
							TryLearnSkill(skill);
							skill->clickTick = now;
						}
					}
					else
					{
						skill->plusSkillClick = false;
					}

					auto btnColor = (skill->plusSkillClick) ? Color4f(0, 0, 0, 70) : Color4f(255, 255, 255, 70);
					pDrawColorButton(0x7880, plusIconX, plusIconY, plusIconW, plusIconH, NULL, NULL, btnColor);
				}
				else
				{
					skill->handOverPlusSkill = false;
					skill->plusSkillClick = false;
				}
			}
			else
			{
				skill->handOverPlusSkill = false;
				skill->plusSkillClick = false;
			}
		}
		else
		{
			skill->handOverPlusSkill = false;
			skill->plusSkillClick = false;
		}
	}
}

void CHuntingSystem::DrawTooltip()
{
	for (auto i = 0; i < EHuntingSkill::eHS_CNT; i++)
	{
		auto skill = &m_SkillsMap[(EHuntingSkill)i];
		auto skillObjIdx = eHS_OBJ_BASE + i;

		if (gInterface.IsWorkZoneObj(skillObjIdx))
		{
			if (!skill->handOverPlusSkill)
			{
				auto x = pCursorX;
				auto y = pCursorY;

				auto beginX = (pCursorX > 320) ? x - 200 : x + 45;
				auto beginY = (pCursorY > 350) ? y - 50 : y + 7;

				pDrawColorButton(NEWUI_BAR_SWITCH02, beginX, beginY, 270, 50, 0, 0, Color4f(0, 0, 0, 200));

				char tmp[256] = { 0 };
				sprintf(tmp, "%s (%d/%d)", skill->title.c_str(), skill->currentLevel, MAX_HUNTING_SKILL_LEVEL);
				gInterface.DrawFormat(eYellow, beginX, beginY + 3, 270, 3, tmp);
				gInterface.DrawFormat(eWhite, beginX + 5, beginY + 13, 270, 3, skill->description.c_str());
				gInterface.DrawFormat(eWhite, beginX + 5, beginY + 23, 270, 3, "Current Add: %d%%", skill->currentLevel * skill->IncPerLevel);

				if (skill->currentLevel < MAX_HUNTING_SKILL_LEVEL)
				{
					gInterface.DrawFormat(eShinyGreen, beginX + 5, beginY + 33, 270, 3, "Next Add: %d%%", (skill->currentLevel + 1) * skill->IncPerLevel);
					gInterface.DrawFormat(eShinyGreen, beginX + 5, beginY + 39, 270, 3, "Points Needed: %d", skill->pointsNeeded[skill->currentLevel]);
				}
				else
				{
					gInterface.DrawFormat(eExcellent, beginX + 5, beginY + 33, 270, 3, "Maximized");
				}
			}

			return;
		}
	}
}

void CHuntingSystem::DrawAdditionalAttributes()
{
	if (!gInterface.CheckWindow(ObjWindow::Character) 
		|| gInterface.CheckWindow(ObjWindow::FullMap) 
		|| gInterface.CheckWindowEx(ObjWindowsEx::exWinStatsAdvance))
		return;

	auto offset = (*(GLsizei*)MAIN_RESOLUTION_X < 1000) ? 12 : 0;

	gInterface.DrawFormat(ColorMacro::eGold, 468, 50, 50, 0, "Hunting Level: %d", m_level);

	if (m_attr.strength > 0)
		gInterface.DrawFormat(ColorMacro::eGold, 585, 125, 30, 3, "[+%d]", m_attr.strength);

	if (m_attr.dexterity > 0)
		gInterface.DrawFormat(ColorMacro::eGold, 585, 180, 30, 3, "[+%d]", m_attr.dexterity);

	if (m_attr.vitality > 0)
		gInterface.DrawFormat(ColorMacro::eGold, 585, 245, 30, 3, "[+%d]", m_attr.vitality);

	if (m_attr.energy > 0)
		gInterface.DrawFormat(ColorMacro::eGold, 585, 300, 30, 3, "[+%d]", m_attr.energy);

	if (m_attr.leadership > 0)
		gInterface.DrawFormat(ColorMacro::eGold, 585, 355, 30, 3, "[+%d]", m_attr.leadership);

	auto min = (int)((m_attr.minAtkLeft > 0 && m_attr.minAtkRight > 0) ? (m_attr.minAtkLeft * 0.5f + m_attr.minAtkRight * 0.5f) : m_attr.minAtkRight);
	auto max = (int)((m_attr.maxAtkLeft > 0 && m_attr.maxAtkRight > 0) ? (m_attr.maxAtkLeft * 0.5f + m_attr.maxAtkRight * 0.5f) : m_attr.maxAtkRight);

	if (m_attr.minAtkLeft > 0 || m_attr.minAtkRight > 0 || m_attr.damageRate > 0)
		gInterface.DrawFormat(ColorMacro::eGold, 575, 145 + offset, 60, 3, "[+%d~%d] (%d)", min, max, m_attr.damageRate);

	if (m_attr.minMagicDmg > 0 || m_attr.maxMagicDmg > 0)
		gInterface.DrawFormat(ColorMacro::eGold, 570, 332 + offset, 60, 3, "[+%d~%d]", m_attr.minMagicDmg, m_attr.maxMagicDmg);

	if (m_attr.defense > 0 || m_attr.defenseRate > 0)
		gInterface.DrawFormat(ColorMacro::eGold, 545 + offset, 198, 60, 3, "[+%d] (%d)", m_attr.defense, m_attr.defenseRate);


}

void CHuntingSystem::LoadImages()
{
	char tmp[256] = { 0 };

	for (auto i = 0; i < EHuntingSkill::eHS_CNT; i++)
	{
		sprintf(tmp, "%s\\skill%02d.tga", HUNTING_SYSTEM_IMG_PATH, i);

		gInterface.LoadImages(tmp, EHuntingImages::eHS_IMG_BASE + i, 0x2601, 0x2900, 1);
	}

	gInterface.LoadImages("Custom\\Interface\\Hunting\\bg.tga", EHuntingImages::eHS_IMG_BG, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Hunting\\close.tga", EHuntingImages::eHS_IMG_CLOSE, 0x2601, 0x2900, 1);
}

void CHuntingSystem::BindObjects()
{
	auto spacing = 20;
	gInterface.BindObject(eHS_OBJ_DMGRATE, eHS_IMG_DMGRATE, 40, 40, 380 + spacing, 70);
	gInterface.BindObject(eHS_OBJ_INCDMG, eHS_IMG_INCDMG, 40, 40, 380 + spacing, 130);
	gInterface.BindObject(eHS_OBJ_1HDMG, eHS_IMG_1HDMG, 40, 40, 320 + spacing, 190);
	gInterface.BindObject(eHS_OBJ_2HDMG, eHS_IMG_2HDMG, 40, 40, 380 + spacing, 190);
	gInterface.BindObject(eHS_OBJ_PETDMG, eHS_IMG_PETDMG, 40, 40, 440 + spacing, 190);
	gInterface.BindObject(eHS_OBJ_CRITDMG, eHS_IMG_CRITDMG, 40, 40, 380 + spacing, 250);
	gInterface.BindObject(eHS_OBJ_EXCDMG, eHS_IMG_EXCDMG, 40, 40, 380 + spacing, 310);
	gInterface.BindObject(eHS_OBJ_DBLDMG, eHS_IMG_DBLDMG, 40, 40, 320 + spacing, 370);
	gInterface.BindObject(eHS_OBJ_IGNDMG, eHS_IMG_IGNDMG, 40, 40, 440 + spacing, 370);

	spacing = 10;

	gInterface.BindObject(eHS_OBJ_DEFRATE, eHS_IMG_DEFRATE, 40, 40, 200 + spacing, 70);
	gInterface.BindObject(eHS_OBJ_INCDEF, eHS_IMG_INCDEF, 40, 40, 200 + spacing, 130);
	gInterface.BindObject(eHS_OBJ_SETDEF, eHS_IMG_SETDEF, 40, 40, 140 + spacing, 190);
	gInterface.BindObject(eHS_OBJ_SHLDDEF, eHS_IMG_SHLDDEF, 40, 40, 260 + spacing, 190);
	gInterface.BindObject(eHS_OBJ_DD, eHS_IMG_DD, 40, 40, 200 + spacing, 250);
	gInterface.BindObject(eHS_OBJ_INCHEAL, eHS_IMG_INCHEAL, 40, 40, 140 + spacing, 310);
	gInterface.BindObject(eHS_OBJ_INCAGGR, eHS_IMG_INCAGGR, 40, 40, 260 + spacing, 310);

	gInterface.BindObject(eHS_OBJ_INCSTR, eHS_IMG_INCSTR, 40, 40, 80, 70);
	gInterface.BindObject(eHS_OBJ_INCAGI, eHS_IMG_INCAGI, 40, 40, 80, 130);
	gInterface.BindObject(eHS_OBJ_INCVIT, eHS_IMG_INCVIT, 40, 40, 80, 190);
	gInterface.BindObject(eHS_OBJ_INCENE, eHS_IMG_INCENE, 40, 40, 80, 250);
	gInterface.BindObject(eHS_OBJ_INCCMD, eHS_IMG_INCCMD, 40, 40, 80, 310);
	gInterface.BindObject(eHS_OBJ_SPCDROP, eHS_IMG_SPCDROP, 40, 40, 80, 370);

	gInterface.BindObject(eHS_OBJ_BG, eHS_IMG_BG, *(GLsizei*)MAIN_RESOLUTION_X, *(GLsizei*)MAIN_RESOLUTION_Y, -1, -1);
	//gInterface.BindObject(eHS_OBJ_CLOSE, eHS_IMG_CLOSE, 36, 29, 600, 10);
}

void CHuntingSystem::DrawInterface()
{
	DrawAdditionalAttributes();

	if (!gInterface.CheckWindowEx(ObjWindowsEx::exWinHuntingSystem))
	{
		return;
	}

	pSetCursorFocus = true;

	gInterface.DrawGUI(eHS_OBJ_BG, 0, 0);
	gInterface.DrawFormat(eGold, 260, 23, 100, 3, "HUNTING SYSTEM");

	if (gInterface.IsWorkZoneObj(eHS_OBJ_CLOSE))
	{
		if (gController.wMouse == WM_LBUTTONDOWN)
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinHuntingSystem);
			return;
		}
	}

	//First Section on BG
	pDrawColorButton(0x7880, 68, 63, 64, 354, NULL, NULL, Color4f(100, 100, 100, 105));
	pDrawColorButton(0x7880, 70, 65, 60, 350, NULL, NULL, Color4f(0, 0, 0, 70));

	//Second Section on BG
	pDrawColorButton(0x7880, 138, 63, 184, 354, NULL, NULL, Color4f(100, 100, 100, 105));
	pDrawColorButton(0x7880, 140, 65, 180, 350, NULL, NULL, Color4f(0, 0, 0, 70));

	//Third Section on BG
	pDrawColorButton(0x7880, 328, 63, 184, 354, NULL, NULL, Color4f(100, 100, 100, 105));
	pDrawColorButton(0x7880, 330, 65, 180, 350, NULL, NULL, Color4f(0, 0, 0, 70));

	//Points Section
	pDrawColorButton(0x7880, 518, 63, 94, 74, NULL, NULL, Color4f(100, 100, 100, 105));
	pDrawColorButton(0x7880, 520, 65, 90, 70, NULL, NULL, Color4f(0, 0, 0, 70));

	auto offset = (*(GLsizei*)MAIN_RESOLUTION_X < 1000) ? 10 : 0;

	gInterface.DrawFormat(eWhite, 525, 70, 90, 0, "Current Level:");
	gInterface.DrawFormat(eYellow, 535 + offset, 70, 90, 3, "%d", m_level);

	gInterface.DrawFormat(eWhite, 525, 80, 90, 0, "Hunting Points:");
	gInterface.DrawFormat(eYellow, 535 + offset, 80, 90, 3, "%d", m_points);

	gInterface.DrawFormat(eWhite, 525, 90, 90, 0, "Current Exp:");
	gInterface.DrawFormat(eYellow, 535 + offset, 90, 90, 3, "%d", m_currentExp);

	gInterface.DrawFormat(eWhite, 525, 100, 90, 0, "Next Exp:");
	gInterface.DrawFormat(eYellow, 535 + offset, 100, 90, 3, "%d", m_nextExp);

	auto perc = (m_nextExp > 0) ? (m_currentExp / (double)m_nextExp) : 0;
	if (perc > 1)
		perc = 1;

	pDrawColorButton(0x7880, 525, 115, 80, 4, NULL, NULL, eWhite180);
	pDrawColorButton(0x7880, 525, 115, perc * 80, 4, NULL, NULL, eYellow);
	gInterface.DrawFormat(eYellow, 525, 120, 80, 3, "%0.2lf%%", (perc * 100));

	DrawInactiveConnections(); //First draw the inactive one
	DrawActiveConnections(); //Then draw the active ones, so the active overlay the inactive ones

	DrawSkills();
	DrawTooltip();
}

void CHuntingSystem::GCParseData(PMSG_HUNTING_DATA * pMsg)
{
	m_currentExp = pMsg->exp;
	m_nextExp = pMsg->nextExp;
	m_level = pMsg->level;
	m_points = pMsg->points;

	for (auto i = 0; i < EHuntingSkill::eHS_CNT; i++)
	{
		auto skill = &m_SkillsMap[(EHuntingSkill)i];
		skill->currentLevel = pMsg->skills[i];
	}
}

void CHuntingSystem::GCLearnSkillAnswer(PMSG_HUNTING_SKILL_ANS * pMsg)
{
	if (pMsg->skill == 0xFF)
		return;

	auto skill = &m_SkillsMap[(EHuntingSkill)pMsg->skill];
	skill->currentLevel = pMsg->newSkillLevel;

	m_points = pMsg->newPoints;
}

void CHuntingSystem::GCEarnExp(PMSG_HUNTING_EXP* pMsg)
{
	m_currentExp += pMsg->exp;
}

void CHuntingSystem::GCLevelUp(PMSG_HUNTING_LEVEL_UP* pMsg)
{
	m_level = pMsg->level;
	m_points = pMsg->points;
	m_nextExp = pMsg->nextExp;

	m_currentExp = 0;
}

void CHuntingSystem::GCAttr(PMSG_HUNTING_ADD_ATTR* pMsg)
{
	memcpy(&m_attr, &pMsg->addAttr, sizeof(HuntingAddAttr));
}

void CHuntingSystem::DrawInactiveConnections()
{
	auto color = eBlack;

	if (m_SkillsMap[eHS_INCDEF].currentLevel == 0)
	{
		//DEFRATE to DEF connection
		pDrawColorButton(0x7880, 230, 95, 4, 40, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_SETDEF].currentLevel == 0)
	{
		//DEF to SET connection
		pDrawColorButton(0x7880, 230, 165, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 190, 205, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_SHLDDEF].currentLevel == 0)
	{
		//DEF to SHIELD connection
		pDrawColorButton(0x7880, 230, 165, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 230, 205, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_DD].currentLevel == 0 || m_SkillsMap[eHS_SHLDDEF].currentLevel == 0)
	{
		//SHIELD to DD connection
		pDrawColorButton(0x7880, 290, 225, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 250, 265, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_DD].currentLevel == 0 || m_SkillsMap[eHS_SETDEF].currentLevel == 0)
	{
		//SET to DD connection
		pDrawColorButton(0x7880, 170, 225, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 170, 265, 44, 4, NULL, NULL, color);

	}

	if (m_SkillsMap[eHS_INCHEAL].currentLevel == 0)
	{
		//DD to HEAL connection
		pDrawColorButton(0x7880, 230, 285, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 190, 325, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_INCAGGR].currentLevel == 0)
	{
		//DD to AGGR connection
		pDrawColorButton(0x7880, 230, 285, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 230, 325, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_INCDMG].currentLevel == 0)
	{
		//DMG RATE to DMG connection
		pDrawColorButton(0x7880, 420, 95, 4, 40, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_2HDMG].currentLevel == 0)
	{
		//DMG TO 2HDMG connection
		pDrawColorButton(0x7880, 420, 155, 4, 40, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_1HDMG].currentLevel == 0)
	{
		//DMG TO 1HDMG connection
		pDrawColorButton(0x7880, 360, 155, 44, 4, NULL, NULL, color);
		pDrawColorButton(0x7880, 360, 155, 4, 44, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_PETDMG].currentLevel == 0)
	{
		//DMG TO PETDMG connection
		pDrawColorButton(0x7880, 440, 155, 44, 4, NULL, NULL, color);
		pDrawColorButton(0x7880, 480, 155, 4, 44, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_CRITDMG].currentLevel == 0 || m_SkillsMap[eHS_2HDMG].currentLevel == 0)
	{
		//2HDMG TO CRIT connection
		pDrawColorButton(0x7880, 420, 215, 4, 40, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_CRITDMG].currentLevel == 0 || m_SkillsMap[eHS_1HDMG].currentLevel == 0)
	{
		//1HDMG TO CRIT connection
		pDrawColorButton(0x7880, 360, 225, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 360, 265, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_CRITDMG].currentLevel == 0 || m_SkillsMap[eHS_PETDMG].currentLevel == 0)
	{
		//PETDMG TO CRIT connection
		pDrawColorButton(0x7880, 480, 225, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 440, 265, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_EXCDMG].currentLevel == 0)
	{
		//CRIT TO EXC connection
		pDrawColorButton(0x7880, 420, 285, 4, 40, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_DBLDMG].currentLevel == 0)
	{
		//EXC to DBL connection
		pDrawColorButton(0x7880, 420, 345, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 380, 385, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_IGNDMG].currentLevel == 0)
	{
		//EXC TO IGN connection
		pDrawColorButton(0x7880, 420, 345, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 420, 385, 44, 4, NULL, NULL, color);
	}
}

void CHuntingSystem::DrawActiveConnections()
{
	auto color = eShinyGreen;

	if (m_SkillsMap[eHS_INCDEF].currentLevel > 0)
	{
		//DEFRATE to DEF connection
		pDrawColorButton(0x7880, 230, 95, 4, 40, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_SETDEF].currentLevel > 0)
	{
		//DEF to SET connection
		pDrawColorButton(0x7880, 230, 165, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 190, 205, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_SHLDDEF].currentLevel > 0)
	{
		//DEF to SHIELD connection
		pDrawColorButton(0x7880, 230, 165, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 230, 205, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_DD].currentLevel > 0 && m_SkillsMap[eHS_SHLDDEF].currentLevel > 0)
	{
		//SHIELD to DD connection
		pDrawColorButton(0x7880, 290, 225, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 250, 265, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_DD].currentLevel > 0 && m_SkillsMap[eHS_SETDEF].currentLevel > 0)
	{
		//SET to DD connection
		pDrawColorButton(0x7880, 170, 225, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 170, 265, 44, 4, NULL, NULL, color);

	}

	if (m_SkillsMap[eHS_INCHEAL].currentLevel > 0)
	{
		//DD to HEAL connection
		pDrawColorButton(0x7880, 230, 285, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 190, 325, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_INCAGGR].currentLevel > 0)
	{
		//DD to AGGR connection
		pDrawColorButton(0x7880, 230, 285, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 230, 325, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_INCDMG].currentLevel > 0)
	{
		//DMG RATE to DMG connection
		pDrawColorButton(0x7880, 420, 95, 4, 40, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_2HDMG].currentLevel > 0)
	{
		//DMG TO 2HDMG connection
		pDrawColorButton(0x7880, 420, 155, 4, 40, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_1HDMG].currentLevel > 0)
	{
		//DMG TO 1HDMG connection
		pDrawColorButton(0x7880, 360, 155, 44, 4, NULL, NULL, color);
		pDrawColorButton(0x7880, 360, 155, 4, 44, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_PETDMG].currentLevel > 0)
	{
		//DMG TO PETDMG connection
		pDrawColorButton(0x7880, 440, 155, 44, 4, NULL, NULL, color);
		pDrawColorButton(0x7880, 480, 155, 4, 44, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_CRITDMG].currentLevel > 0 && m_SkillsMap[eHS_2HDMG].currentLevel > 0)
	{
		//2HDMG TO CRIT connection
		pDrawColorButton(0x7880, 420, 215, 4, 40, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_CRITDMG].currentLevel > 0 && m_SkillsMap[eHS_1HDMG].currentLevel > 0)
	{
		//1HDMG TO CRIT connection
		pDrawColorButton(0x7880, 360, 225, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 360, 265, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_CRITDMG].currentLevel > 0 && m_SkillsMap[eHS_PETDMG].currentLevel > 0)
	{
		//PETDMG TO CRIT connection
		pDrawColorButton(0x7880, 480, 225, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 440, 265, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_EXCDMG].currentLevel > 0)
	{
		//CRIT TO EXC connection
		pDrawColorButton(0x7880, 420, 285, 4, 40, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_DBLDMG].currentLevel > 0)
	{
		//EXC to DBL connection
		pDrawColorButton(0x7880, 420, 345, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 380, 385, 44, 4, NULL, NULL, color);
	}

	if (m_SkillsMap[eHS_IGNDMG].currentLevel > 0)
	{
		//EXC TO IGN connection
		pDrawColorButton(0x7880, 420, 345, 4, 40, NULL, NULL, color);
		pDrawColorButton(0x7880, 420, 385, 44, 4, NULL, NULL, color);
	}
}

void CHuntingSystem::TryLearnSkill(HuntingSkill* skill)
{
	if (skill->type != 0xFF && skill->currentLevel < MAX_HUNTING_SKILL_LEVEL && m_points > 0)
	{
		PMSG_HUNTING_SKILL_REQ req = { 0 };
		req.h.set((LPBYTE)&req, LC_HEADER, LC_HUNTING_SKILL, sizeof(req));
		req.skill = skill->type;

		gProtocol.DataSend((LPBYTE)&req, req.h.size);
	}
}