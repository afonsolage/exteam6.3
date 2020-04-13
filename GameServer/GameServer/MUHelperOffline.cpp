#include "stdafx.h"
#include "MUHelperOffline.h"
#include "GameMain.h"
#include "logproc.h"
#include "ExUser.h"
#include "ExFunction.h"
#include "ObjUseSkill.h"

#include "MUHelper.h"

CMUHelperOffline g_MUHelperOffline;

void CMUHelperOffline::Load()
{
	this->Clear();

	auto path = gDirPath.GetNewPath("Skills\\SkillAreaInfo.txt");

	FILE *file = fopen(path, "r");

	if (file == NULL)
	{
		MessageBoxA(0, "Skills\\SkillAreaInfo.txt", "CRITICAL ERROR", 0);
		return;
	}

	char Buff[256];
	int Flag = 0;
	while (!feof(file))
	{
		fgets(Buff, 256, file);

		if (Buff[0] == '/' && Buff[1] == '/')
			continue;

		int skillCode;
		SKILL_AREA_TYPE type;
		int radius;
		char name[256];
		sscanf(Buff, "%d %d %d %s", &skillCode, &type, &radius, &name);

		this->m_skillsAreaInfo[skillCode] = { type, radius, name };
	}

	this->m_Loaded = true;
}

void CMUHelperOffline::Clear()
{
	this->m_states.clear();
	this->m_skillsAreaInfo.clear();

	this->m_Loaded = false;
}

OFFLINE_STATE* CMUHelperOffline::GetState(int aIndex)
{
	auto state = this->m_states.find(aIndex);
	if (state == this->m_states.end())
	{
		OFFLINE_STATE s = {};
		state = this->m_states.emplace(aIndex, s).first;
	}
	return &state->second;
}

void CMUHelperOffline::PacketToSettings(MUHELPER_SETTINGS_PACKET & packet, MUHELPER_SETTINGS & settings)
{
	settings.PickupJewel = packet.PickupJewel;
	settings.PickupSetItem = packet.PickupSetItem;
	settings.PickkupExcItem = packet.PickkupExcItem;
	settings.PickupZen = packet.PickupZen;
	settings.PickupExtra = packet.PickupExtra;
	settings.PickupRange = packet.PickupRange;
	settings.AttackRange = packet.AttackRange;
	settings.MaxDistance = packet.MaxDistance;
	settings.MainSkill = packet.MainSkill;
	settings.SubSkill1 = packet.SubSkill1;
	settings.SubSkill1Dur = packet.SubSkill1Dur;
	settings.SubSkill2 = packet.SubSkill2;
	settings.SubSkill2Dur = packet.SubSkill2Dur;
	settings.PartyBuffDur = packet.PartyBuffDur;
	settings.BuffSkill1 = packet.BuffSkill1;
	settings.BuffSkill2 = packet.BuffSkill2;
	settings.BuffSkill3 = packet.BuffSkill3;
	settings.HealBar = packet.HealBar;
	settings.PotionBar = packet.PotionBar;
	settings.PartyBar = packet.PartyBar;
	settings.DrainBar = packet.DrainBar;
	settings.PotionEnabled = packet.PotionEnabled;
	settings.HealSelf = packet.HealSelf;
	settings.CounterEnabled = packet.CounterEnabled;
	settings.OriginalPos = packet.OriginalPos;
	settings.ComboEnabled = packet.ComboEnabled;
	settings.BuffParty = packet.BuffParty;
	settings.HealParty = packet.HealParty;
	settings.BuffPartyDelay = packet.BuffPartyDelay;
	settings.DarkRavenEnabled = packet.DarkRavenEnabled;
	settings.BuffSelfEnabled = packet.BuffSelfEnabled;
	settings.SubSkill1Delay = packet.SubSkill1Delay;
	settings.SubSkill1Cond = packet.SubSkill1Cond;
	settings.SubSkill1PreCond = packet.SubSkill1PreCond;
	settings.SubSkill1SubCond = packet.SubSkill1SubCond;
	settings.SubSkill2Delay = packet.SubSkill2Delay;
	settings.SubSkill2Cond = packet.SubSkill2Cond;
	settings.SubSkill2PreCond = packet.SubSkill2PreCond;
	settings.SubSkill2SubCond = packet.SubSkill2SubCond;
	settings.RepairItem = packet.RepairItem;
	settings.PickupAllItems = packet.PickupAllItems;
	settings.PickupSeletectedItems = packet.PickupSeletectedItems;
	settings.RavenAttackMode = packet.RavenAttackMode;
	settings.ItemName1 = packet.ItemName1;
	settings.ItemName2 = packet.ItemName2;
	settings.ItemName3 = packet.ItemName3;
	settings.ItemName4 = packet.ItemName4;
	settings.ItemName5 = packet.ItemName5;
	settings.ItemName6 = packet.ItemName6;
	settings.ItemName7 = packet.ItemName7;
	settings.ItemName8 = packet.ItemName8;
	settings.ItemName9 = packet.ItemName9;
	settings.ItemName10 = packet.ItemName10;
	settings.ItemName11 = packet.ItemName11;
	settings.ItemName12 = packet.ItemName12;
}

void CMUHelperOffline::CheckAttack(LPOBJ lpObj, OFFLINE_STATE * lpState)
{
	auto now = GetTickCount();

	auto magicCode = lpState->settings.MainSkill;

	if (magicCode <= 0)
	{
		lpState->nextAction = m_Now + ONE_SECOND; //Avoid checking every tick
		return;
	}

	auto lpMagic = gObjGetMagicSearch(lpObj, magicCode);

	if (lpMagic == NULL)
	{
		LogAddC(2, "[MUHelperOffline] Invalid magic code %d on index %d", magicCode, lpObj->m_Index);
		lpState->nextAction = m_Now + ONE_SECOND; //Avoid checking every tick
		return;
	}

	auto distance = MagicDamageC.GetSkillDistance(magicCode);

	if (distance < 0)
	{
		LogAddC(2, "[MUHelperOffline] Invalid distance (%d) magic code %d on index %d", distance, magicCode, lpObj->m_Index);
		lpState->nextAction = m_Now + ONE_SECOND; //Avoid checking every tick
		return;
	}

	auto lpTargetObj = SearchTarget(lpObj, distance);

	if (lpTargetObj != NULL)
	{
		DoAttack(lpObj, lpState, lpTargetObj);
	}
	else
	{

	}
}

void CMUHelperOffline::DoAttack(LPOBJ lpObj, OFFLINE_STATE * lpState, LPOBJ lpTargetObj)
{
	auto magicCode = lpState->settings.SubSkill1;

	auto it = this->m_skillsAreaInfo.find(magicCode);

	auto interval = CalcAttackInterval(lpObj);

	if (it == this->m_skillsAreaInfo.end())
	{
		LogAddC(2, "[MUHelperOffline][%d] Failed to get target skill list. Area info not found for skill %d.", lpObj->m_Index, magicCode);
		return;
	}

	auto info = it->second;

	switch (info.type)
	{
	case SINGLE:
	{
		UseMagicAttack(lpObj->m_Index, magicCode, lpTargetObj->m_Index);
	}
	break;
	case DURATION:
	{
		int magicKey = (lpState->magicKey++ % MAX_DUR_MAGIC_KEY);
		UseMagicDurationAttack(lpObj->m_Index, magicCode, lpTargetObj->X, lpTargetObj->Y, lpObj->Dir, 0, lpTargetObj->m_Index, magicKey);
	}
	break;
	default:
	{
		auto targetList = GetTargetSkillList(lpObj, info, lpTargetObj);

		if (targetList.empty())
		{
			LogAddC(2, "[MUHelperOffline][%d] Unable to do attack. No target returned.", lpObj->m_Index);
			return;
		}

		for (int i = 0; i < targetList.size(); i++)
		{
			if (magicCode == AT_SKILL_EVIL)
			{
				auto hit = rand() % 100; //Evil spirit doesn't always hit all mobs. The chance is high for closer mobs
				auto dist = gObjCalDistance(lpObj, targetList[i]);
				if (hit < dist * 10) continue;
			}

			int delay = rand() % interval;
			gObjAddAttackProcMsgSendDelay(lpObj, 50, targetList[i]->m_Index, 300, magicCode, 0);
		}

		int magicKey = (lpState->magicKey++ % MAX_DUR_MAGIC_KEY);
		UseMagicDurationAttack(lpObj->m_Index, magicCode, lpTargetObj->X, lpTargetObj->Y, lpObj->Dir, 0, lpTargetObj->m_Index, magicKey);
	}
	break;
	}

	lpState->nextAction = m_Now + interval;
}

std::vector<LPOBJ> CMUHelperOffline::GetTargetSkillList(LPOBJ lpObj, SKILL_AREA_INFO skillInfo, LPOBJ lpTargetObj)
{
	auto result = std::vector<LPOBJ>();

	if (skillInfo.type == SINGLE || skillInfo.type == DURATION)
	{
		result.emplace_back(lpTargetObj);
	}
	else if (skillInfo.type == SELF_CIRCLE)
	{
		return ListTargetsTargetCircle(lpObj, lpObj, skillInfo.radius);
	}
	else if (skillInfo.type == TARGET_CIRCLE)
	{
		return ListTargetsTargetCircle(lpObj, lpTargetObj, skillInfo.radius);
	}

	return result;
}

std::vector<LPOBJ> CMUHelperOffline::ListTargetsTargetCircle(LPOBJ lpObj, LPOBJ lpTarget, int maxDist, int maxTargets)
{
	auto result = std::vector<LPOBJ>();

	for (int i = 0; i < MAX_VIEWPORT_MONSTER; i++)
	{
		auto lpVp = &lpObj->VpPlayer2[i];

		if (lpVp->state == 0) continue;
		else if (!OBJMAX_RANGE(lpVp->number)) continue;
		else if (lpVp->type != OBJ_MONSTER) continue;

		auto lpTargetObj = &gObj[lpVp->number];

		if (lpTargetObj->Live == 0) continue;

		auto dist = gObjCalDistance(lpTarget, lpTargetObj);

		if (dist <= maxDist)
		{
			result.emplace_back(lpTargetObj);
			maxTargets--;

			if (maxTargets <= 0)
				break;
		}
	}

	return result;
}

LPOBJ CMUHelperOffline::SearchTarget(LPOBJ lpObj, int maxDist)
{
	auto selTargetDist = maxDist;
	LPOBJ selTargetObj = NULL;

	for (int i = 0; i < MAX_VIEWPORT_MONSTER; i++)
	{
		auto lpVp = &lpObj->VpPlayer2[i];

		if (lpVp->state == 0) continue;
		else if (!OBJMAX_RANGE(lpVp->number)) continue;
		else if (lpVp->type != OBJ_MONSTER) continue;

		auto lpTargetObj = &gObj[lpVp->number];

		if (lpTargetObj->Live == 0) continue;

		auto dist = gObjCalDistance(lpObj, lpTargetObj);

		if (dist < selTargetDist || (dist == selTargetDist && selTargetObj == NULL))
		{
			selTargetDist = dist;
			selTargetObj = lpTargetObj;
		}
	}

	return selTargetObj;
}

int CMUHelperOffline::CalcAttackInterval(LPOBJ lpObj)
{
	auto speed = max(lpObj->m_AttackSpeed, lpObj->m_MagicSpeed);

	return (int)(50000.0f / (float)speed);
}

void CMUHelperOffline::Tick()
{
	m_Now = GetTickCount();

	for (int n = OBJ_STARTUSERINDEX; n < OBJMAX; n++)
	{
		if (OBJMAX_RANGE(n) == FALSE) continue;
		else if (!gObjIsConnectedEx(n)) continue;

		LPOBJ lpUser = &gObj[n];

		if (lpUser->Connected != PLAYER_PLAYING) continue;
		else if (lpUser->Live == 0) continue;

		this->Tick(lpUser);
	}
}

void CMUHelperOffline::MacroRes(int aIndex, MUHELPER_SETTINGS_PACKET settings)
{
	auto lpState = GetState(aIndex);

	PacketToSettings(settings, lpState->settings);

	lpState->settings_state = SETTINGS_STATE::RECEIVED;
}

void CMUHelperOffline::MacroSave(int aIndex, LPBYTE settingsBuffer)
{
	if (settingsBuffer == NULL)
		return;

	auto lpState = GetState(aIndex);

	if (!lpState->active)
		return;

	MUHELPER_SETTINGS_PACKET packet;
	memcpy(&packet, settingsBuffer, sizeof(packet));

	PacketToSettings(packet, lpState->settings);
}

void CMUHelperOffline::Start(int aIndex)
{
	auto lpState = GetState(aIndex);

	g_MUHelper.ReqMacro(aIndex, true);
	lpState->settings_state == SETTINGS_STATE::REQUESTED;
	lpState->active = true;
}

void CMUHelperOffline::Stop(int aIndex)
{
	auto lpState = GetState(aIndex);

	if (lpState->active == false)
		return;

	lpState->active = false;
	lpState->nextAction = 0;
}

void CMUHelperOffline::Tick(LPOBJ lpObj)
{
	auto lpState = GetState(lpObj->m_Index);

	if (lpState->active == false)
		return;
	else if (lpState->nextAction > m_Now)
		return;

	if (lpState->settings_state == SETTINGS_STATE::NONE)
	{
		g_MUHelper.ReqMacro(lpObj->m_Index, true);
		lpState->settings_state == SETTINGS_STATE::REQUESTED;
		return;
	}
	else if (lpState->settings_state == SETTINGS_STATE::REQUESTED)
	{
		return;
	}

	if (g_ExUser.InSafeZone(lpObj->m_Index))
	{
		lpState->active = false;
		return;
	}

	CheckAttack(lpObj, lpState);
}