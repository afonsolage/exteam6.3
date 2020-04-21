#include "stdafx.h"
#include "MUHelperOffline.h"
#include "GameMain.h"
#include "logproc.h"
#include "ExUser.h"
#include "ExFunction.h"
#include "ObjUseSkill.h"
#include "gObjMonster.h"
#include "CustomSystem.h"
#include "logproc.h"
#include "PartyClass.h"
#include "../common/winutil.h"
#include "MUHelper.h"
#include "DSProtocol.h"
#include "DBSockMng.h"
#include <boost/algorithm/string.hpp>
#include "SProtocol.h"

CMUHelperOffline g_MUHelperOffline;

void CMUHelperOffline::Load()
{
	this->Clear();

	if (!g_CustomSystem.IsMUHelperOffline()) return;

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
		int interval;
		char name[256];
		sscanf(Buff, "%d %d %d %d %s", &skillCode, &type, &interval, &radius, &name);

		this->m_skillsAreaInfo[skillCode] = { type, interval, radius, name };
	}

	this->m_Loaded = true;
}

void CMUHelperOffline::Clear()
{
	this->m_skillsAreaInfo.clear();

	this->m_Loaded = false;
}

void CMUHelperOffline::RequestAllPlayers()
{
	if (!m_Loaded) return;
	if (g_WaitOpen == true) return;
	if (m_allPlayersRequestSent) return;
	
	m_allPlayersRequestSent = true;

	PBMSG_HEAD2 pMsg;
	pMsg.set((LPBYTE)&pMsg, 0xEB, 0x24, sizeof(pMsg));
	cDBSMng.Send((char*)&pMsg, pMsg.size);
}

void CMUHelperOffline::DGRestorePlayer(PMSG_RESTORE_DATA * lpMsg)
{
	if (!m_Loaded) return;

	//Check if Player is already connected
	for (int i = OBJ_MAXMONSTER; i < OBJMAX; i++)
	{
		LPOBJ sObj = &gObj[i];

		if (sObj->Connected < PLAYER_LOGGED) continue;

		if (boost::iequals(lpMsg->AccountID, sObj->AccountID)
			&& boost::iequals(lpMsg->Password, sObj->Pass))
		{
			GDSavePlayerState(sObj);
			return;
		}
	}

	auto aIndex = GetFreeIndex();

	if (aIndex == -2)
	{
		LogAddC(2, "[MUHelperOffline][%s][%s] Unable to restore character. Server is full!", lpMsg->AccountID, lpMsg->Name);
		return;
	}
	else if (aIndex == -1) return;
	else if (gObj[aIndex].Connected == PLAYER_PLAYING) return;
	else if (gObjAdd(INVALID_SOCKET, "127.0.0.1", aIndex) == -1) return;

	LPOBJ lpObj = &gObj[aIndex];
	
	GJPUserClose(lpObj->AccountID);

	strncpy(gObj[aIndex].Name, lpMsg->Name, MAX_IDSTRING);
	strncpy(gObj[aIndex].AccountID, lpMsg->AccountID, MAX_IDSTRING);

	BuxConvert(lpMsg->AccountID, MAX_IDSTRING);
	BuxConvert(lpMsg->Password, MAX_IDSTRING);

	SDHP_IDPASS spMsg = { 0 };
	PHeadSetB((LPBYTE)&spMsg, 0x01, sizeof(spMsg));
	spMsg.Number = aIndex;
	memcpy(spMsg.Id, lpMsg->AccountID, sizeof(spMsg.Id));
	memcpy(spMsg.Pass, lpMsg->Password, sizeof(spMsg.Pass));
	strcpy(spMsg.IpAddress, gObj[aIndex].Ip_addr);
	gObj[aIndex].CheckTick = GetTickCount();
	gObj[aIndex].CheckTick2 = GetTickCount();
	gObj[aIndex].ConnectCheckTime = GetTickCount();
	gObj[aIndex].CheckSpeedHack = true;
	gObj[aIndex].LoginMsgSnd = 1;
	gObj[aIndex].LoginMsgCount = 1;
	gObj[aIndex].m_cAccountItemBlock = 0;
	gObj[aIndex].ukn_30 = 0;
	
	

	auto state = GetState(aIndex);
	state->offReconectState = OFF_AUTH_REQ;
	state->active = true;
	state->offline = true;

	wsJServerCli.DataSend((char*)&spMsg, spMsg.h.size);
	LogAddTD("join send : (%d)%s", aIndex, gObj[aIndex].AccountID);

	lpObj->m_bMapSvrMoveReq = false;
	lpObj->m_sPrevMapSvrCode = -1;
	lpObj->m_sDestMapNumber = -1;
	lpObj->m_btDestX = 0;
	lpObj->m_btDestY = 0;
}

void CMUHelperOffline::GDSavePlayerState(LPOBJ lpObj)
{
	PMSG_SAVE_MUHELPEROFF_DATA pMsg = { 0 };
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x23, sizeof(pMsg));
	memcpy(pMsg.data.AccountID, lpObj->AccountID, MAX_IDSTRING);
	memcpy(pMsg.data.Name, lpObj->Name, MAX_IDSTRING);
	pMsg.data.Active = IsActive(lpObj->m_Index);
	pMsg.data.Offline = IsOffline(lpObj->m_Index);

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CMUHelperOffline::GDReqCharInfo(int aIndex)
{
	auto state = GetState(aIndex);

	if (state->offReconectState != OFF_AUTH_REQ)
	{
		return;
	}

	state->offReconectState = OFF_CHAR_REQ;

	if (gObjIsConnected(aIndex))
		return;

	LPOBJ lpObj = &gObj[aIndex];

	char szName[MAX_IDSTRING + 1] = { 0 };

	memcpy(szName, lpObj->Name, MAX_IDSTRING);
	BuxConvert(szName, MAX_ACCOUNT_LEN);

	SDHP_DBCHARINFOREQUEST pMsg = { 0 };
	PHeadSetB((LPBYTE)&pMsg, 0x06, sizeof(pMsg));
	memcpy(pMsg.Name, szName, MAX_ACCOUNT_LEN);
	strncpy(pMsg.AccountID, lpObj->AccountID, MAX_IDSTRING);
	pMsg.Number = lpObj->m_Index;

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

BOOL CMUHelperOffline::IsActive(int aIndex)
{
	if (!m_Loaded) return FALSE;

	auto state = this->m_states.find(aIndex);
	if (state == this->m_states.end()) return FALSE;
	else return state->second.active;
}

BOOL CMUHelperOffline::IsOffline(int aIndex)
{
	if (!m_Loaded) return FALSE;

	auto state = this->m_states.find(aIndex);
	if (state == this->m_states.end()) return FALSE;
	else return state->second.active && state->second.offline;
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

void CMUHelperOffline::ClearState(int aIndex)
{
	auto state = this->m_states.find(aIndex);
	if (state == this->m_states.end())
	{
		return;
	}
	this->m_states[aIndex] = {};

	if (!gObjIsConnected(aIndex))
		return;

	LPOBJ lpObj = &gObj[aIndex];

	gSendCharMapJoinResult(lpObj);
	for (int n = 0; n < MAX_VIEWPORT; n++)
	{
		if (OBJMAX_RANGE(lpObj->VpPlayer[n].number) && lpObj->VpPlayer[n].state == 2)
		{
			if (lpObj->VpPlayer[n].type == OBJ_USER && !gObjIsConnected(lpObj->VpPlayer[n].index)) continue;

			auto lpVpObj = &gObj[lpObj->VpPlayer[n].number];
			if (lpVpObj->Live == 0) continue;

			lpObj->VpPlayer[n].state = 1;
		}
	}
	GCItemListSend(aIndex);
}

void CMUHelperOffline::PacketToSettings(MUHELPER_SETTINGS_PACKET & packet, MUHELPER_SETTINGS & settings)
{
	settings.PickupJewel = packet.PickupJewel;
	settings.PickupSetItem = packet.PickupSetItem;
	settings.PickupExcItem = packet.PickupExcItem;
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
	settings.ItemNames[0] = packet.ItemName1;
	settings.ItemNames[1] = packet.ItemName2;
	settings.ItemNames[2] = packet.ItemName3;
	settings.ItemNames[3] = packet.ItemName4;
	settings.ItemNames[4] = packet.ItemName5;
	settings.ItemNames[5] = packet.ItemName6;
	settings.ItemNames[6] = packet.ItemName7;
	settings.ItemNames[7] = packet.ItemName8;
	settings.ItemNames[8] = packet.ItemName9;
	settings.ItemNames[9] = packet.ItemName10;
	settings.ItemNames[10] = packet.ItemName11;
	settings.ItemNames[11] = packet.ItemName12;
}

void CMUHelperOffline::CheckPotions(LPOBJ lpObj, OFFLINE_STATE * lpState)
{
	if (lpState->useManaPotion && m_Now > lpState->nextCheckManaPotion)
	{
		lpState->useManaPotion = false;
		lpState->nextCheckManaPotion = m_Now;

		for (auto it = m_manaPotions.begin(); it != m_manaPotions.end(); it++)
		{
			auto pos = -1;
			auto item = SearchItemInventory(lpObj, *it, 0, pos);

			if (item == NULL)
				continue;
			
			gUseManaPotion(item, lpObj->m_Index, pos);
			return;
		}

		//Since we didn't find any potion, we don't need to check every second for potion
		//let's save some CPU by checking again some seconds later
		lpState->nextCheckManaPotion = m_Now + NO_POTION_DELAY;
	}

	if (lpState->settings.PotionEnabled && m_Now > lpState->nextCheckHPPotion)
	{
		auto hpRate = lpObj->Life / (float)lpObj->MaxLife;
		auto bar = lpState->settings.PotionBar / (float)MAX_BAR;

		if (hpRate > bar)
		{
			lpState->nextCheckHPPotion = m_Now + HP_POTION_CHECK_DELAY;
			return;
		}

		for (auto it = m_HPPotions.begin(); it != m_HPPotions.end(); it++)
		{
			auto pos = -1;
			auto item = SearchItemInventory(lpObj, *it, 0, pos);

			if (item == NULL)
				continue;

			gUseHPPotion(item, lpObj->m_Index, pos);
			lpState->nextCheckHPPotion = m_Now + HP_POTION_USE_DELAY;
			return;
		}

		//Since we didn't find any potion, we don't need to check every second for potion
		//let's save some CPU by checking again some seconds later
		lpState->nextCheckHPPotion = m_Now + HP_POTION_USE_DELAY;
	}
}

BOOL CMUHelperOffline::CheckHeal(LPOBJ lpObj, OFFLINE_STATE * lpState)
{
	if (lpObj->Class != CLASS_ELF || lpState->settings.HealSelf == FALSE) return FALSE;

	auto hpRate = lpObj->Life / (float)lpObj->MaxLife;
	auto bar = lpState->settings.HealBar / (float)MAX_BAR;

	if (hpRate > bar) return FALSE;

	UseMagicAttack(lpObj->m_Index, AT_SKILL_HEALING, lpObj->m_Index);

	lpState->nextAction = m_Now + HALF_SECOND;

	return TRUE;
}

BOOL CMUHelperOffline::CheckItems(LPOBJ lpObj, OFFLINE_STATE * lpState)
{
	switch (lpState->playerState)
	{
	case STANDING:
	case ATTACKING:
	case MOVING_BACK:
	case BUFFING:
	{
		SearchItemNearby(lpObj, MAX_ITEM_DISTANCE, lpState);

		if (lpState->lpTargetItem == NULL)
		{
			return FALSE; //No item to pickup
		}

		auto distance = gObjCalDistance(lpObj->X, lpObj->Y, lpState->lpTargetItem->px, lpState->lpTargetItem->py);

		if (distance <= MAX_PICKUP_DISTANCE)
		{
			//Since we are on server side, we need to add a few ms to give others players a chance to see and get the item
			lpState->nextAction = m_Now + (rand() % HALF_SECOND);
			lpState->playerState = PLAYER_STATE::PICKINGUP;
			return TRUE;
		}
		else
		{
			int moveTime = MoveTo(lpObj, lpState, lpState->lpTargetItem->px, lpState->lpTargetItem->py); //Move to item

			if (moveTime > 0)
			{
				lpState->nextAction = m_Now + moveTime;
				lpState->playerState = PLAYER_STATE::MOVING_PICKUP;
				return TRUE;
			}
		}
	}
	break;
	case PICKINGUP:
	{
		DoPickup(lpObj, lpState);
		lpState->nextAction = m_Now + ONE_SECOND;
		lpState->playerState = PLAYER_STATE::STANDING;
		return TRUE;
	}
	break;
	case MOVING_PICKUP:
	{
		if (lpObj->PathCount > 0)
		{
			lpState->nextAction = m_Now + QUARTER_SECOND;
			return TRUE;
		}

		if (lpState->lpTargetItem != NULL && lpState->lpTargetItem->Give == false && lpState->lpTargetItem->live == true)
		{
			DoPickup(lpObj, lpState);
		}

		lpState->playerState = PLAYER_STATE::STANDING; //Lets stand again so we can check for more itens or get back to spot
		return TRUE;
	}
	break;
	}

	return FALSE;
}

BOOL CMUHelperOffline::CheckReturn(LPOBJ lpObj, OFFLINE_STATE * lpState)
{
	switch (lpState->playerState)
	{
	case MOVING_BACK:
	{
		if (lpObj->PathCount == 0)
		{
			lpState->playerState = PLAYER_STATE::STANDING;
		}
		else
		{
			int moveTime = MoveTo(lpObj, lpState, lpState->originX, lpState->originY);
			if (moveTime > 0)
			{
				lpState->nextAction = m_Now + moveTime;
			}
			else
			{
				lpState->playerState = PLAYER_STATE::STANDING;
			}
		}
		return TRUE;
	}
	break;
	case STANDING:
	{
		if (lpObj->PathCount == 0 && (lpObj->X != lpState->originX || lpObj->Y != lpState->originY))
		{
			int moveTime = MoveTo(lpObj, lpState, lpState->originX, lpState->originY);
			if (moveTime > 0)
			{
				lpState->playerState = PLAYER_STATE::MOVING_BACK;
				lpState->nextAction = m_Now + moveTime;
			}
		}
	}
	break;
	}

	return FALSE;
}

BOOL CMUHelperOffline::CheckBuffs(LPOBJ lpObj, OFFLINE_STATE * lpState)
{
	if (lpState->settings.BuffSelfEnabled && lpObj->PartyNumber < 0 && m_Now > lpState->nextCheckSelfBuff)
	{
		int interval = 0;
		
		if (lpState->settings.BuffSkill1 > 0 && DoSelfBuff(lpObj, lpState->settings.BuffSkill1))
		{
			interval = ONE_SECOND;
		}
		else if (lpState->settings.BuffSkill2 > 0 && DoSelfBuff(lpObj, lpState->settings.BuffSkill2))
		{
			interval = ONE_SECOND;
		}
		else if (lpState->settings.BuffSkill3 > 0 && DoSelfBuff(lpObj, lpState->settings.BuffSkill3))
		{
			interval = ONE_SECOND;
		}

		if (interval > 0)
		{
			lpState->nextAction = m_Now + interval;
			lpState->playerState = PLAYER_STATE::BUFFING;
			return TRUE;
		}

		lpState->nextCheckSelfBuff = m_Now + HALF_SECOND;
	}
	
	if (lpState->settings.BuffParty && m_Now > lpState->nextCheckPartyBuff)
	{
		int interval = 0;

		if (lpState->settings.BuffSkill1 > 0 
			&& this->m_skillPartyBuffs.find(lpState->settings.BuffSkill1) != this->m_skillPartyBuffs.cend()
			&& DoPartyBuff(lpObj, lpState, lpState->settings.BuffSkill1))
		{
			interval = HALF_SECOND;
		}
		else if (lpState->settings.BuffSkill2 > 0
			&& this->m_skillPartyBuffs.find(lpState->settings.BuffSkill2) != this->m_skillPartyBuffs.cend()
			&& DoPartyBuff(lpObj, lpState, lpState->settings.BuffSkill2))
		{
			interval = HALF_SECOND;
		}
		else if (lpState->settings.BuffSkill3 > 0
			&& this->m_skillPartyBuffs.find(lpState->settings.BuffSkill3) != this->m_skillPartyBuffs.cend()
			&& DoPartyBuff(lpObj, lpState, lpState->settings.BuffSkill3))
		{
			interval = HALF_SECOND;
		}

		if (interval > 0)
		{
			lpState->nextAction = m_Now + interval;
			lpState->playerState = PLAYER_STATE::BUFFING;
			return TRUE;
		}

		lpState->nextCheckPartyBuff = m_Now + lpState->settings.BuffPartyDelay;
	}

	return FALSE;
}

BOOL CMUHelperOffline::CheckAttack(LPOBJ lpObj, OFFLINE_STATE * lpState)
{
	auto magicCode = lpState->settings.MainSkill;

	if (magicCode <= 0)
	{
		lpState->nextAction = m_Now + ONE_SECOND; //Avoid checking every tick
		lpState->playerState = PLAYER_STATE::STANDING;
		return TRUE;
	}

	auto lpMagic = gObjGetMagicSearch(lpObj, magicCode);

	if (lpMagic == NULL)
	{
		LogAddC(2, "[MUHelperOffline] Invalid magic code %d on index %d", magicCode, lpObj->m_Index);
		lpState->nextAction = m_Now + ONE_SECOND; //Avoid checking every tick
		lpState->playerState = PLAYER_STATE::STANDING;
		return TRUE;
	}

	auto distance = MagicDamageC.GetSkillDistance(magicCode);

	if (distance < 0)
	{
		LogAddC(2, "[MUHelperOffline] Invalid distance (%d) magic code %d on index %d", distance, magicCode, lpObj->m_Index);
		lpState->nextAction = m_Now + ONE_SECOND; //Avoid checking every tick
		lpState->playerState = PLAYER_STATE::STANDING;
		return TRUE;
	}

	auto lpTargetObj = SearchTargetNearby(lpObj, distance);

	auto interval = HALF_SECOND;
	lpState->playerState = PLAYER_STATE::STANDING;

	if (lpTargetObj != NULL)
	{
		interval = DoAttack(lpObj, lpState, lpTargetObj);

		if (interval == 0)
			interval = ONE_SECOND; //Some error happened.
		else
			lpState->playerState = PLAYER_STATE::ATTACKING;
	}

	lpState->nextAction = m_Now + interval;
	return TRUE;
}

DWORD CMUHelperOffline::DoAttack(LPOBJ lpObj, OFFLINE_STATE * lpState, LPOBJ lpTargetObj)
{
	auto magicCode = lpState->settings.MainSkill;

	auto it = this->m_skillsAreaInfo.find(magicCode);

	if (it == this->m_skillsAreaInfo.end())
	{
		LogAddC(2, "[MUHelperOffline][%d] Failed to get target skill list. Area info not found for skill %d.", lpObj->m_Index, magicCode);
		return 0;
	}

	auto info = it->second;

	auto interval = CalcAttackInterval(lpObj, info);

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
			return 0;
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

	return interval;
}

DWORD CMUHelperOffline::DoPickup(LPOBJ lpObj, OFFLINE_STATE * lpState)
{
	if (lpState->lpTargetItem == NULL || lpState->lpTargetItem->Give == true || lpState->lpTargetItem->live == false)
		return FALSE;

	if (lpState->lpTargetItem->m_Type == ITEMGET(14, 15))
	{
		if (MapC[lpObj->MapNumber].ItemGive(lpObj->m_Index, lpState->targetItemIdx, false) == FALSE)
			return FALSE;

		if (!gObjCheckMaxZen(lpObj->m_Index, lpState->lpTargetItem->m_BuyMoney))
		{
			if (lpObj->Money < MAX_ZEN)
			{
				lpObj->Money = MAX_ZEN;
				return TRUE;
			}
		}
		else
		{
			int totalMoney = lpState->lpTargetItem->m_BuyMoney;

			if (ShareZenParty && lpObj->PartyNumber >= 0)
			{
				std::vector<int> nearMembers = gParty.GetNearMembers(lpObj->m_Index);

				int count = nearMembers.size();

				if (count > 0)
				{
					int shareZen = totalMoney / count;

					for (int n = 0; n < nearMembers.size(); n++)
					{
						int memberIdx = nearMembers[n];
						CollectZen(memberIdx, shareZen);
					}
				}
			}
			else
			{
				CollectZen(lpObj->m_Index, totalMoney);
			}
		}
	}
	else
	{
		BYTE result = gObjInventoryInsertItemTemp(lpObj, lpState->lpTargetItem);
		if (result != 0xFF)
		{
			if (MapC[lpObj->MapNumber].ItemGive(lpObj->m_Index, lpState->targetItemIdx, false) == TRUE)
			{
				BYTE pos = ::gObjInventoryInsertItem(lpObj->m_Index, lpState->lpTargetItem);
				if (pos != 0xFF)
				{
					::GCSendGetItemInfoForParty(lpObj->m_Index, lpState->lpTargetItem);
				}
			}
		}
	}

	return TRUE;
}

BOOL CMUHelperOffline::DoSelfBuff(LPOBJ lpObj, WORD skillNumber)
{
	auto skillEffect = GetSkillEffect(skillNumber);

	if (skillEffect <= 0)
	{
		LogAddC(2, "[MUHelperOffline][%d] Unable to do Self Buff. Skill effect not found for skill %d.", lpObj->m_Index, skillNumber);
		return FALSE;
	}

	auto secondsLeft = gObjGetActiveEffectTimeLeft(lpObj, skillEffect);

	if (secondsLeft < MIN_SECOND_REBUFF)
	{
		UseMagicAttack(lpObj->m_Index, skillNumber, lpObj->m_Index);
		return TRUE;
	}

	return FALSE;
}

BOOL CMUHelperOffline::DoPartyBuff(LPOBJ lpObj, OFFLINE_STATE * lpState, WORD skillNumber)
{
	auto skillEffect = GetSkillEffect(skillNumber);

	if (skillEffect <= 0)
	{
		LogAddC(2, "[MUHelperOffline][%d] Unable to do Party Buff. Skill effect not found for skill %d.", lpObj->m_Index, skillNumber);
		return FALSE;
	}

	auto partyNum = lpObj->PartyNumber;

	if (partyNum < 0) return 0;

	auto nearbyMembers = gParty.GetNearMembers(lpObj->m_Index);

	for (int i = 0; i < nearbyMembers.size(); i++)
	{
		if (!gObjIsConnected(nearbyMembers[i]))
			continue;

		LPOBJ lpPartyMember = &gObj[nearbyMembers[i]];

		auto secondsLeft = gObjGetActiveEffectTimeLeft(lpPartyMember, skillEffect);

		if (secondsLeft < MIN_SECOND_REBUFF)
		{
			UseMagicAttack(lpObj->m_Index, skillNumber, lpPartyMember->m_Index);
			return TRUE;
		}
	}

	return FALSE;
}

WORD CMUHelperOffline::MoveTo(LPOBJ lpObj, OFFLINE_STATE* lpState, int x, int y)
{
	int MoveTime = 0;
	if (lpObj->PathDir[lpObj->PathCur] % 2 == 0)
	{
		MoveTime = (int)((lpObj->m_MoveSpeed)*(double)1.3);
	}
	else
	{
		MoveTime = lpObj->m_MoveSpeed;
	}

	lpObj->MTX = x;
	lpObj->MTY = y;

	if (PathFindMoveMsgSend(lpObj))
	{
		int lastX = lpObj->X;
		int lastY = lpObj->Y;
		int dist = 0;
		for (int i = 0; i < 15; i++)
		{
			int x = lpObj->PathX[i];
			int y = lpObj->PathY[i];

			if (x == 0 && y == 0)
				break;

			dist += gObjCalDistance(lastX, lastY, x, y);

			lastX = x;
			lastY = y;
		}

		lpState->moveFailedCount = 0;
		return dist * MoveTime;
	}

	if (lpState->moveFailedCount > MAX_MOVE_FAILED_COUNT)
	{
		LogAddC(2, "[MUHelperOffline][%d] Failed to move to positon %d %d. Forcing move.", lpObj->m_Index, x, y);
		gObjSetPosition(lpObj->m_Index, x, y);
		lpState->moveFailedCount = 0;
	}

	return 0;
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

int CMUHelperOffline::GetSkillEffect(int skill)
{
	const auto it = this->m_skillBuffMap.find(skill);
	if (it == this->m_skillBuffMap.end())
		return -1;

	return it->second;
}

LPOBJ CMUHelperOffline::SearchTargetNearby(LPOBJ lpObj, int maxDist)
{
	auto selTargetDist = maxDist;
	LPOBJ selTargetObj = NULL;

	for (int i = 0; i < MAX_VIEWPORT; i++)
	{
		auto lpVp = &lpObj->VpPlayer[i];

		if (lpVp->state != 2) continue;
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

BOOL CMUHelperOffline::SearchItemNearby(LPOBJ lpObj, int maxDist, OFFLINE_STATE * lpState)
{
	auto mapNumber = lpObj->MapNumber;
	CMapItem* nearbyOne = NULL;
	auto nearbyDist = maxDist;
	auto nearbyIdx = 0;

	for (int i = 0; i < MAX_VIEWPORT; i++)
	{
		auto lpVp = &lpObj->VpPlayer[i];

		if (lpVp->type != 5) continue; 
		else if (lpVp->state != 2) continue;

		auto lpMapItem = &MapC[mapNumber].m_cItem[lpVp->number];

		if (lpMapItem->IsItem() == TRUE && lpMapItem->Give == false && lpMapItem->live == true && m_Now - lpMapItem->m_Time > HALF_SECOND)
		{
			int dis = gObjCalDistance(lpObj->X, lpObj->Y, lpMapItem->px, lpMapItem->py);

			if (dis > MAX_ITEM_DISTANCE)
			{
				continue;
			}

			if (gLootingTime > 0
				&& lpMapItem->m_UserIndex != -1
				&& lpMapItem->m_UserIndex != lpObj->m_Index
				&& lpMapItem->m_LootTime > this->m_Now)
			{
				continue;
			}

			if (lpMapItem->m_QuestItem != false
				&& !g_QuestInfo.CountQuestItemInInventory(lpObj->m_Index, lpMapItem->m_Type, lpMapItem->m_Level))
			{
				continue;
			}

			if (ShouldPickupItem(lpMapItem, lpState->settings) && dis < nearbyDist)
			{
				nearbyOne = lpMapItem;
				nearbyDist = dis;
				nearbyIdx = lpVp->number;
			}
		}
	}

	lpState->lpTargetItem = nearbyOne;
	lpState->targetItemIdx = nearbyIdx;

	return lpState->lpTargetItem != NULL;
}

BOOL CMUHelperOffline::ShouldPickupItem(CMapItem * lpMapItem, MUHELPER_SETTINGS & settings)
{
	if (settings.PickupAllItems)
	{
		return TRUE;
	}

	if (settings.PickupJewel &&
		(lpMapItem->m_Type == ITEMGET(12, 15) ||
			lpMapItem->m_Type == ITEMGET(14, 13) ||
			lpMapItem->m_Type == ITEMGET(14, 14) ||
			lpMapItem->m_Type == ITEMGET(14, 16) ||
			lpMapItem->m_Type == ITEMGET(14, 22) ||
			lpMapItem->m_Type == ITEMGET(14, 31) ||
			lpMapItem->m_Type == ITEMGET(14, 42)))
	{
		return TRUE;
	}

	if (settings.PickupZen && lpMapItem->m_Type == ITEMGET(14, 15))
	{
		return TRUE;
	}

	if (settings.PickupExcItem && lpMapItem->IsExtItem())
	{
		return TRUE;
	}

	if (settings.PickupSetItem && lpMapItem->IsSetItem())
	{
		return TRUE;
	}

	if (settings.PickupExtra)
	{
		//TODO: Add this

		for (auto i = 0; i < MAX_SETTINGS_ITEMS; i++)
		{
			auto& name = settings.ItemNames[i];

			if (name.empty()) continue;


		}
	}

	return FALSE;
}

CItem * CMUHelperOffline::SearchItemInventory(LPOBJ lpObj, int type, int level, int& outPos)
{
	for (int n = INVETORY_WEAR_SIZE; n < MAIN_INVENTORY_SIZE; n++)
	{
		if (lpObj->pInventory[n].IsItem() == TRUE 
			&& lpObj->pInventory[n].m_Type == type 
			&& lpObj->pInventory[n].m_Level == level)
		{
			outPos = n;
			return &lpObj->pInventory[n];
		}
	}
	outPos = -1;
	return NULL;
}

int CMUHelperOffline::CalcAttackInterval(LPOBJ lpObj, SKILL_AREA_INFO skillInfo)
{
	auto speed = max(lpObj->m_AttackSpeed, lpObj->m_MagicSpeed);
	auto diff = abs(skillInfo.interval - (speed * 0.8f));
	auto rate = diff / (float)skillInfo.interval; //The higher the speed, the lower the rate

	return (int)(rate * diff);
}

int CMUHelperOffline::GetFreeIndex()
{
	if (gDisconnect == 1)
	{
		return -1;
	}

	if (gObjTotalUser >= gServerMaxUser)
	{
		return -2;
	}

	int totalcount = 0;
	int count = gObjCount;

	while (gObj[count].Connected != PLAYER_EMPTY)
	{
		count++;

		if (count >= OBJMAX)
		{
			count = OBJ_STARTUSERINDEX;
		}

		totalcount++;

		if (totalcount >= OBJMAXUSER)
		{
			return -1;
		}
	}

	return count;
}

void CMUHelperOffline::Tick()
{
	if (!m_Loaded) return;

	m_Now = GetTickCount();

	for (int n = OBJ_STARTUSERINDEX; n < OBJMAX; n++)
	{
		if (OBJMAX_RANGE(n) == FALSE) continue;
		else if (!gObjIsConnectedEx(n)) continue;

		LPOBJ lpUser = &gObj[n];

		if (lpUser->Connected != PLAYER_PLAYING) continue;

		this->Tick(lpUser);
	}
}

void CMUHelperOffline::MacroRes(int aIndex, MUHELPER_SETTINGS_PACKET settings)
{
	auto lpState = GetState(aIndex);

	PacketToSettings(settings, lpState->settings);

	lpState->settingsState = SETTINGS_STATE::RECEIVED;
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

	LPOBJ lpObj = &gObj[aIndex];

	g_MUHelper.ReqMacro(aIndex, true);
	lpState->settingsState == SETTINGS_STATE::REQUESTED;
	lpState->active = true;
	lpState->originX = lpObj->X;
	lpState->originY = lpObj->Y;
	lpState->shouldDestroyVP = true; //Destroy the main version
	lpState->shouldCreateVP = true; //Create the dummy version

	GDSavePlayerState(lpObj);
}

void CMUHelperOffline::Stop(int aIndex)
{
	auto lpState = GetState(aIndex);

	if (lpState->active == false)
		return;

	if (lpState->offline == false)
	{
		lpState->shouldDestroyVP = true; //destroy the dummy
		lpState->shouldClearState = true; //clear after destroying dummie
	}
	else
	{
		ClearState(aIndex);
	}

	GDSavePlayerState(&gObj[aIndex]);
}

void CMUHelperOffline::SwitchOffline(int aIndex)
{
	auto lpState = GetState(aIndex);
	if (lpState->active)
	{
		lpState->offline = true;
	}

	GDSavePlayerState(&gObj[aIndex]);
}

void CMUHelperOffline::SwitchOnline(int aIndex)
{

}

void CMUHelperOffline::NoMana(int aIndex)
{
	auto lpState = GetState(aIndex);

	if (lpState->active == false)
		return;

	lpState->useManaPotion = true;
}

void CMUHelperOffline::Tick(LPOBJ lpObj)
{
	auto lpState = GetState(lpObj->m_Index);

	if (lpState->active == false)
		return;
	
	if (lpObj->Live == 0 || g_ExUser.InSafeZone(lpObj->m_Index))
	{
		Stop(lpObj->m_Index);
		return;
	}

	if (lpState->settingsState == SETTINGS_STATE::NONE)
	{
		g_MUHelper.ReqMacro(lpObj->m_Index, true);
		lpState->settingsState == SETTINGS_STATE::REQUESTED;
		return;
	}
	else if (lpState->settingsState == SETTINGS_STATE::REQUESTED)
	{
		return;
	}

	lpObj->CheckTick = m_Now;
	lpObj->CheckSumTime = m_Now;

	CheckPotions(lpObj, lpState);

	if (CheckHeal(lpObj, lpState)) return;
	if (CheckBuffs(lpObj, lpState)) return;
	if (CheckItems(lpObj, lpState)) return;
	if (CheckReturn(lpObj, lpState)) return;
	if (CheckAttack(lpObj, lpState)) return;
}