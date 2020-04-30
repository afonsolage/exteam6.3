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
#include "DarkSpirit.h"

CMUHelperOffline g_MUHelperOffline;

void CMUHelperOffline::Load()
{
	this->Clear();

	if (!g_CustomSystem.IsMUHelperOffline()) return;

	auto initPath = gDirPath.GetNewPath("Skills\\SkillAreaInfo.txt");

	m_enabled = GetPrivateProfileInt("LCMUHelperOffline", "Enabled", 0, initPath);
	m_firstChargeZen = GetPrivateProfileInt("LCMUHelperOffline", "FirstChargeZen", 1, initPath);
	m_chargeInterval = GetPrivateProfileInt("LCMUHelperOffline", "ChargeInterval", 5, initPath);
	m_pricePerLevel = GetPrivateProfileInt("LCMUHelperOffline", "PricePerLevel", 100, initPath);
	m_pricePerReset = GetPrivateProfileInt("LCMUHelperOffline", "PricePerReset", 20000, initPath);

	if (!m_enabled) return;

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
	if (!m_enabled) return;
	if (g_WaitOpen == true) return;
	if (m_allPlayersRequestSent) return;

	m_allPlayersRequestSent = true;

	PBMSG_HEAD2 pMsg;
	pMsg.set((LPBYTE)&pMsg, 0xEB, 0x24, sizeof(pMsg));
	cDBSMng.Send((char*)&pMsg, pMsg.size);
}

void CMUHelperOffline::DGRestorePlayer(PMSG_RESTORE_DATA * lpMsg)
{
	if (!m_enabled) return;

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
	if (!m_enabled) return FALSE;

	auto state = this->m_states.find(aIndex);
	if (state == this->m_states.end()) return FALSE;
	else return state->second.active;
}

BOOL CMUHelperOffline::IsOffline(int aIndex)
{
	if (!m_enabled) return FALSE;

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

	this->GDSavePlayerState(&gObj[aIndex]);
}

//void CMUHelperOffline::RestoreVP(int aIndex)
//{
//	LPOBJ lpObj = &gObj[aIndex];
//	gSendCharMapJoinResult(lpObj);
//	for (int n = 0; n < MAX_VIEWPORT; n++)
//	{
//		if (OBJMAX_RANGE(lpObj->VpPlayer[n].number) && lpObj->VpPlayer[n].state == 2)
//		{
//			if (lpObj->VpPlayer[n].type == OBJ_USER && !gObjIsConnected(lpObj->VpPlayer[n].index)) continue;
//
//			auto lpVpObj = &gObj[lpObj->VpPlayer[n].number];
//			if (lpVpObj->Live == 0) continue;
//
//			lpObj->VpPlayer[n].state = 1;
//		}
//	}
//	GCItemListSend(aIndex);
//}

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

void CMUHelperOffline::ChargeZen(LPOBJ lpObj, OFFLINE_STATE * lpState)
{
	if (lpState->nextZenBilling == 0)
	{
		if (this->m_firstChargeZen)
			lpState->nextZenBilling = m_Now + ONE_MINNUTE;
		else
			lpState->nextZenBilling = m_Now + (ONE_MINNUTE * this->m_chargeInterval);

		return;
	}
	else if (m_Now > lpState->nextZenBilling)
	{
		auto charge = (lpObj->Level + lpObj->MLevel) * this->m_pricePerLevel + lpObj->Reset * this->m_pricePerReset;

		if (lpObj->Money < charge)
		{
			Stop(lpObj->m_Index);

			if (!IsOffline(lpObj->m_Index))
				GCServerMsgStringSend("No Zen left. Stopping Helper", lpObj->m_Index, 0);

			return;
		}
		else
		{
			lpObj->Money -= charge;

			if (!IsOffline(lpObj->m_Index))
			{
				char tmp[256] = { 0 };
				sprintf(tmp, "%d Zen charged from Helper", charge);
				GCServerMsgStringSend(tmp, lpObj->m_Index, 0);
				GCMoneySend(lpObj->m_Index, lpObj->Money);
			}

			lpState->nextZenBilling = m_Now + (ONE_MINNUTE * this->m_chargeInterval);
		}
	}
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

void CMUHelperOffline::CheckPet(LPOBJ lpObj, OFFLINE_STATE * lpState)
{
	if (lpObj->Class != CLASS_DARKLORD || lpState->settings.DarkRavenEnabled == FALSE || m_Now < lpState->nextCheckPet) return;

	auto lpSpirit = &gDarkSpirit[lpObj->m_Index];
	auto mode = lpSpirit->m_ActionMode;

	switch (lpState->settings.RavenAttackMode)
	{
	case 0:
		if (mode != CDarkSpirit::ePetItem_Mode::PetItem_Mode_Normal) lpSpirit->SetMode(CDarkSpirit::ePetItem_Mode::PetItem_Mode_Normal, -1);
		break;
	case 1:
		if (mode != CDarkSpirit::ePetItem_Mode::PetItem_Mode_Attack_Random) lpSpirit->SetMode(CDarkSpirit::ePetItem_Mode::PetItem_Mode_Attack_Random, -1);
		break;
	default:
		if (mode != CDarkSpirit::ePetItem_Mode::PetItem_Mode_Attack_WithMaster) lpSpirit->SetMode(CDarkSpirit::ePetItem_Mode::PetItem_Mode_Attack_WithMaster, -1);
		break;
	}

	lpState->nextCheckPet = m_Now + ONE_SECOND;
}

void CMUHelperOffline::CheckRepair(LPOBJ lpObj, OFFLINE_STATE * lpState)
{
	if (m_Now < lpState->nextCheckRepair) return;

	ItemDurRepaire(lpObj, 0xFF);

	lpState->nextCheckRepair = m_Now + ONE_MINNUTE; //Check once every minute is enought
}

BOOL CMUHelperOffline::CheckHeal(LPOBJ lpObj, OFFLINE_STATE * lpState)
{
	if (lpObj->Class == CLASS_ELF && lpState->settings.HealSelf == TRUE)
	{
		auto lpMagicInfo = gObjGetMagicSearch(lpObj, AT_SKILL_HEALING);

		if (lpMagicInfo == NULL) return FALSE;

		auto hpRate = lpObj->Life / (float)lpObj->MaxLife;
		auto bar = lpState->settings.HealBar / (float)MAX_BAR;

		if (hpRate <= bar)
		{
			UseMagicAttack(lpObj->m_Index, AT_SKILL_HEALING, lpObj->m_Index);
			lpState->nextAction = m_Now + HALF_SECOND;
			return TRUE;
		}

		if (lpObj->PartyNumber >= 0)
		{
			auto partyNum = lpObj->PartyNumber;

			if (partyNum < 0) return 0;

			auto nearbyMembers = gParty.GetNearMembers(lpObj->m_Index);

			for (auto it = nearbyMembers.begin(); it != nearbyMembers.end(); it++)
			{
				if (!gObjIsConnected(*it)) continue;

				auto lpMember = &gObj[*it];

				auto hpRate = lpMember->Life / (float)lpMember->MaxLife;
				auto bar = lpState->settings.PartyBar / (float)MAX_BAR;

				if (hpRate > bar) return FALSE;

				UseMagicAttack(lpObj->m_Index, AT_SKILL_HEALING, lpMember->m_Index);

				lpState->nextAction = m_Now + HALF_SECOND;

				return TRUE;
			}
		}
	}
	else if (lpObj->Class == CLASS_SUMMONER && lpState->settings.HealSelf == TRUE)
	{
		auto lpMagicInfo = gObjGetMagicSearch(lpObj, AT_SKILL_DRAINLIFE);

		if (lpMagicInfo == NULL) return FALSE;

		auto hpRate = lpObj->Life / (float)lpObj->MaxLife;
		auto bar = lpState->settings.DrainBar / (float)MAX_BAR;

		lpState->useDrainLife = hpRate <= bar;
	}

	return FALSE;
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
			PRINT_DEBUG_LINE("PICKINGUP");
			return TRUE;
		}
		else
		{
			int moveTime = MoveTo(lpObj, lpState, lpState->lpTargetItem->px, lpState->lpTargetItem->py); //Move to item

			if (moveTime > 0)
			{
				lpState->nextAction = m_Now + moveTime;
				lpState->playerState = PLAYER_STATE::MOVING_PICKUP;
				PRINT_DEBUG_LINE("MOVING_PICKUP");
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
		PRINT_DEBUG_LINE("STANDING");
		return TRUE;
	}
	break;
	}

	return FALSE;
}

BOOL CMUHelperOffline::CheckMoving(LPOBJ lpObj, OFFLINE_STATE * lpState)
{
	switch (lpState->playerState)
	{
	case MOVING_BACK:
	{
		if (lpObj->PathCount == 0)
		{
			lpState->playerState = PLAYER_STATE::STANDING;
			PRINT_DEBUG_LINE("STANDING");
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
				PRINT_DEBUG_LINE("STANDING");
			}
		}
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
		PRINT_DEBUG_LINE("STANDING");
		return TRUE;
	}
	break;
	case MOVING_ATTACK:
	{
		if (lpObj->PathCount > 0)
		{
			//lpState->nextAction = m_Now + T100MS_SECOND;
			return TRUE;
		}

		int interval = 0;

		if (lpState->lpTargetObj != NULL && lpState->lpTargetObj->Live == true && lpState->lpTargetObj->RegenOk == 0)
		{
			auto distance = GetMagicDistance(lpState->targetMagicCode);

			if (gObjCalDistance(lpObj, lpState->lpTargetObj) <= distance)
			{
				interval = DoAttack(lpObj, lpState, lpState->lpTargetObj, lpState->targetMagicCode);

				if (interval == 0)
				{
					interval = ONE_SECOND; //Some error happened.
					lpState->playerState = PLAYER_STATE::STANDING;
					PRINT_DEBUG_LINE("STANDING");
				}
				else
				{
					lpState->playerState = PLAYER_STATE::ATTACKING;
					PRINT_DEBUG_LINE("ATTACKING");
				}
			}
			else //Target moved, lets search right now for another one;
			{
				lpState->playerState = PLAYER_STATE::STANDING;
				PRINT_DEBUG_LINE("STANDING");
				return FALSE;
			}
		}
		else
		{
			interval = HALF_SECOND;
			lpState->playerState = PLAYER_STATE::STANDING;
			PRINT_DEBUG_LINE("STANDING");
		}

		lpState->nextAction = m_Now + interval;
		return TRUE;
	}
	break;
	case ATTACKING:
	case STANDING:
	{

		//Avoid stopping a combo to return to spot
		if (lpState->playerState == PLAYER_STATE::ATTACKING && lpObj->Class == CLASS_KNIGHT
			&& lpState->settings.ComboEnabled == TRUE && lpState->comboNextSkillIndex > 0 && lpState->comboStartTime + COMBO_TIMEOUT >= m_Now)
			return FALSE;

		if (lpObj->PathCount == 0 && lpState->settings.OriginalPos == TRUE)
		{
			auto dist = gObjCalDistance(lpObj->X, lpObj->Y, lpState->originX, lpState->originY);

			if (dist > lpState->settings.MaxDistance)
			{
				int moveTime = MoveTo(lpObj, lpState, lpState->originX, lpState->originY);
				if (moveTime > 0)
				{
					lpState->playerState = PLAYER_STATE::MOVING_BACK;
					lpState->nextAction = m_Now + moveTime;
					PRINT_DEBUG_LINE("MOVING_BACK");
					return TRUE;
				}
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

		if (lpState->settings.BuffSkill1 > 0 && lpState->settings.BuffSkill1 < 0xFFFF && DoSelfBuff(lpObj, lpState->settings.BuffSkill1))
		{
			interval = ONE_SECOND;
		}
		else if (lpState->settings.BuffSkill2 > 0 && lpState->settings.BuffSkill2 < 0xFFFF && DoSelfBuff(lpObj, lpState->settings.BuffSkill2))
		{
			interval = ONE_SECOND;
		}
		else if (lpState->settings.BuffSkill3 > 0 && lpState->settings.BuffSkill3 < 0xFFFF && DoSelfBuff(lpObj, lpState->settings.BuffSkill3))
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

BOOL CMUHelperOffline::CheckAttack(LPOBJ lpObj, OFFLINE_STATE * lpState, std::set<int> excludeTargets)
{
	auto lpMagic = GetMagicInfo(lpObj, lpState);

	if (lpMagic == NULL)
	{
		lpState->nextAction = m_Now + ONE_SECOND;
		lpState->playerState = PLAYER_STATE::STANDING;
		PRINT_DEBUG_LINE("STANDING");
		return FALSE;
	}

	auto magicCode = lpMagic->m_Skill;

	lpState->playerState = PLAYER_STATE::STANDING;
	PRINT_DEBUG_LINE("STANDING");
	auto interval = HALF_SECOND;
	auto distance = lpState->settings.AttackRange;
	auto lpTargetObj = SearchTargetNearby(lpObj, distance, excludeTargets);

	if (lpTargetObj != NULL)
	{
		distance = GetMagicDistance(magicCode);

		if (distance < 0)
		{
			LogAddC(2, "[MUHelperOffline] Invalid distance (%d) magic code %d on index %d", distance, magicCode, lpObj->m_Index);
			lpState->nextAction = m_Now + ONE_SECOND; //Avoid checking every tick
			lpState->playerState = PLAYER_STATE::STANDING;
			PRINT_DEBUG_LINE("STANDING");
			return TRUE;
		}

		auto targetDistance = gObjCalDistance(lpObj, lpTargetObj);

		if (targetDistance <= distance)
		{
			interval = DoAttack(lpObj, lpState, lpTargetObj, magicCode);

			if (interval == 0)
				interval = ONE_SECOND; //Some error happened.
			else
				lpState->playerState = PLAYER_STATE::ATTACKING;
			PRINT_DEBUG_LINE("ATTACKING");
		}
		else
		{
			auto minDistance = targetDistance - distance;

			auto direction = gObjCalDirection(lpObj, lpTargetObj);
			auto walkX = (int)(minDistance * std::get<0>(direction));
			auto walkY = (int)(minDistance * std::get<1>(direction));

			auto moveTime = this->MoveTo(lpObj, lpState, lpObj->X + walkX, lpObj->Y + walkY);

			if (moveTime > 0)
			{
				lpState->lpTargetObj = lpTargetObj;
				lpState->targetMagicCode = magicCode;
				lpState->nextAction = m_Now + QUARTER_SECOND;
				lpState->playerState = PLAYER_STATE::MOVING_ATTACK;
				PRINT_DEBUG_LINE("MOVING_ATTACK");
				return TRUE;
			}
			else
			{
				excludeTargets.insert(lpTargetObj->m_Index);
				return CheckAttack(lpObj, lpState, excludeTargets);
			}
		}
	}

	lpState->nextAction = m_Now + interval;

	return TRUE;
}

int CMUHelperOffline::GetMagicDistance(int magicCode)
{
	//Don't know why but Inferno has a 0 distance attack
	if (magicCode == AT_SKILL_INFERNO || magicCode == AT_SKILL_HELL)
	{
		return 2;
	}
	else
	{
		return MagicDamageC.GetSkillDistance(magicCode);
	}
}

DWORD CMUHelperOffline::DoAttack(LPOBJ lpObj, OFFLINE_STATE * lpState, LPOBJ lpTargetObj, int magicCode)
{
	auto it = this->m_skillsAreaInfo.find(magicCode);

	if (it == this->m_skillsAreaInfo.end())
	{
		LogAddC(2, "[MUHelperOffline][%d] Failed to get target skill list. Skill area info not found for magic %d.", lpObj->m_Index, magicCode);
		return 0;
	}

	if (!lpObj->SkillDelay.CanUse(magicCode))
		return HALF_SECOND;

	auto info = it->second;

	auto interval = CalcAttackInterval(lpObj, info);

	if (interval <= 0)
		interval = 50; //Maximum attack speed is 20 attacks per seconds, which is pretty high, don't you think?

	DoLookAt(lpObj, lpTargetObj);

	switch (info.type)
	{
	case SINGLE:
	{
		UseMagicAttack(lpObj->m_Index, magicCode, lpTargetObj->m_Index);

		switch (magicCode)
		{
		case AT_SKILL_SWORD1:
		case AT_SKILL_SWORD2:
		case AT_SKILL_SWORD3:
		case AT_SKILL_SWORD4:
		case AT_SKILL_SWORD5:
			gObjSetPosition(lpObj->m_Index, lpTargetObj->X, lpTargetObj->Y);
			break;
		}


	}
	break;
	case DURATION:
	{
		int magicKey = (lpState->magicKey++ % MAX_DUR_MAGIC_KEY);
		auto angle = (int)(gObjUseSkill.GetAngle(lpObj->X, lpObj->Y, lpTargetObj->X, lpTargetObj->Y) / 360.0f * 255);
		UseMagicDurationAttack(lpObj->m_Index, magicCode, lpTargetObj->X, lpTargetObj->Y, lpObj->Dir, angle, lpTargetObj->m_Index, magicKey);
	}
	break;
	default:
	{
		auto targetList = GetTargetSkillList(lpObj, info, lpTargetObj);

		if (targetList.empty())
		{
			LogAddC(2, "[MUHelperOffline][%d] Unable to do attack. No target returned. Type: [%d]", lpObj->m_Index, info.type);
			return 0;
		}

		std::map<int, int> dup;
		for (auto x : targetList) ++dup[x->m_Index];

		for (auto x : dup)
		{
			if (x.second > 1)
			{
				int b = 0;
			}
		}


		ApplyDamage(targetList, magicCode, lpObj, interval, lpState, lpTargetObj);
	}
	break;
	}

	if (lpObj->Class == CLASS_KNIGHT && lpState->settings.ComboEnabled == TRUE && magicCode == lpState->settings.MainSkill)
	{
		lpState->comboStartTime = m_Now;
	}
	else if (magicCode == lpState->settings.SubSkill1)
	{
		lpState->lastSubSkill1Use = m_Now;
	}
	else if (magicCode == lpState->settings.SubSkill2)
	{
		lpState->lastSubSkill2Use = m_Now;
	}

	return interval;
}

void CMUHelperOffline::ApplyDamage(std::vector<LPOBJ> &targetList, const WORD &magicCode, const LPOBJ &lpObj, int interval, OFFLINE_STATE * lpState, const LPOBJ &lpTargetObj)
{
	switch (magicCode)
	{
	case AT_SKILL_EVIL:
	{
		for (int i = 0; i < targetList.size(); i++)
		{
			auto hit = rand() % 100; //Evil spirit doesn't always hit all mobs. The chance is high for closer mobs
			auto dist = gObjCalDistance(lpObj, targetList[i]);
			if (hit < dist * 5) continue;

			int delay = 1000 + (rand() % (interval * 3));

			LPOBJ lpTarget = &gObj[targetList[i]->m_Index];

			//This field is used originally to check hack on players, but since this is a monster, we can use it safely
			if (lpTarget->m_SumLastAttackTime > m_Now) continue;

			lpTarget->m_SumLastAttackTime = GetTickCount() + HALF_SECOND;

			gObjAddAttackProcMsgSendDelay(lpObj, 50, targetList[i]->m_Index, delay, magicCode, 0);
		}
	}
	break;
	default:
	{
		for (int i = 0; i < targetList.size(); i++)
		{
			gObjAddAttackProcMsgSendDelay(lpObj, 50, targetList[i]->m_Index, 300, magicCode, 0);
		}
	}
	}
	auto angle = (BYTE)((gObjUseSkill.GetAngle(lpTargetObj->X, lpTargetObj->Y, lpObj->X, lpObj->Y) / 360.0f) * 255);

	int magicKey = (lpState->magicKey++ % MAX_DUR_MAGIC_KEY);
	UseMagicDurationAttack(lpObj->m_Index, magicCode, lpTargetObj->X, lpTargetObj->Y, angle, 0, lpTargetObj->m_Index, magicKey);

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

				if (pos != 0xFF)
				{
					GCInventoryItemOneSend(lpObj->m_Index, pos);
				}
			}
		}
	}

	return TRUE;
}

struct PMSG_ACTIONRESULT
{
	PBMSG_HEAD h;
	BYTE NumberH;
	BYTE NumberL;
	BYTE Dir;
	BYTE ActionNumber;
	BYTE TargetNumberH;
	BYTE TargetNumberL;
};

void CMUHelperOffline::DoLookAt(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	auto oldDir = lpObj->Dir;
	lpObj->Dir = GetPathPacketDirPos(lpTargetObj->X - lpObj->X, lpTargetObj->Y - lpObj->Y);

	if (oldDir == lpObj->Dir)
		return;

	PMSG_ACTIONRESULT pResult = { 0 };

	PHeadSetB((LPBYTE)&pResult, 0x18, sizeof(pResult));
	pResult.ActionNumber = 0x7a;
	pResult.NumberH = SET_NUMBERH(lpObj->m_Index);
	pResult.NumberL = SET_NUMBERL(lpObj->m_Index);
	pResult.Dir = lpObj->Dir;
	pResult.TargetNumberH = SET_NUMBERH(lpTargetObj->m_Index);
	pResult.TargetNumberL = SET_NUMBERL(lpTargetObj->m_Index);

	for (int n = 0; n < MAX_VIEWPORT; n++)
	{
		if (lpObj->VpPlayer2[n].type == OBJ_USER)
		{
			if (lpObj->VpPlayer2[n].state != 0 && lpObj->VpPlayer2[n].state != 0x10 && lpObj->VpPlayer2[n].state != 0x08)
			{
				DataSend(lpObj->VpPlayer2[n].number, (LPBYTE)&pResult, pResult.h.size);
			}
		}
	}

	DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);
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
	else if (skillInfo.type == DIR_CONE)
	{
		return ListTargetsDirCone(lpObj, lpTargetObj, skillInfo.radius);
	}
	else if (skillInfo.type == DIR_LINEAR)
	{
		return ListTargetsDirLinear(lpObj, lpTargetObj, skillInfo.radius);
	}
	else if (skillInfo.type == DIR_SEMI_CIRCLE)
	{
		return ListTargetsDirSemiCircle(lpObj, lpTargetObj, skillInfo.radius);
	}

	return result;
}

std::vector<LPOBJ> CMUHelperOffline::ListTargetsTargetCircle(LPOBJ lpObj, LPOBJ lpTarget, int maxDist, int maxTargets)
{
	auto result = std::vector<LPOBJ>();

	for (int i = 0; i < MAX_VIEWPORT_MONSTER; i++)
	{
		auto lpVp = &lpObj->VpPlayer[i];

		if (lpVp->state != 2) continue;
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

std::vector<LPOBJ> CMUHelperOffline::ListTargetsDirCone(LPOBJ lpObj, LPOBJ lpTarget, int maxDist, int maxTargets)
{
	auto result = std::vector<LPOBJ>();
	auto angle = (int)(gObjUseSkill.GetAngle(lpObj->X, lpObj->Y, lpTarget->X, lpTarget->Y) / 360.0f * 255);
	SkillFrustrum(angle, lpObj->m_Index);

	for (int i = 0; i < MAX_VIEWPORT_MONSTER; i++)
	{
		auto lpVp = &lpObj->VpPlayer[i];

		if (lpVp->state != 2) continue;
		else if (!OBJMAX_RANGE(lpVp->number)) continue;
		else if (lpVp->type != OBJ_MONSTER) continue;

		auto lpTargetObj = &gObj[lpVp->number];

		if (lpTargetObj->Live == 0) continue;

		auto dist = gObjCalDistance(lpObj, lpTargetObj);

		if (/*dist <= maxDist && SkillTestFrustrum(lpTargetObj->X, lpTargetObj->Y, lpObj->m_Index)*/ lpTargetObj == lpTarget)
		{
			result.emplace_back(lpTargetObj);
			maxTargets--;

			if (maxTargets <= 0)
				break;
		}
	}

	return result;
}

std::vector<LPOBJ> CMUHelperOffline::ListTargetsDirLinear(LPOBJ lpObj, LPOBJ lpTarget, int maxDist, int maxTargets)
{
	auto result = std::vector<LPOBJ>();
	auto angle = (int)(gObjUseSkill.GetAngle(lpObj->X, lpObj->Y, lpTarget->X, lpTarget->Y) / 360.0f * 255);
	gObjUseSkill.SkillFrustrum3(lpObj->m_Index, angle, 1.5f, 6, 1.5f, 0);

	for (int i = 0; i < MAX_VIEWPORT_MONSTER; i++)
	{
		auto lpVp = &lpObj->VpPlayer[i];

		if (lpVp->state != 2) continue;
		else if (!OBJMAX_RANGE(lpVp->number)) continue;
		else if (lpVp->type != OBJ_MONSTER) continue;

		auto lpTargetObj = &gObj[lpVp->number];

		if (lpTargetObj->Live == 0) continue;

		auto dist = gObjCalDistance(lpTarget, lpTargetObj);

		if (dist <= maxDist && SkillTestFrustrum(lpTargetObj->X, lpTargetObj->Y, lpObj->m_Index))
		{
			result.emplace_back(lpTargetObj);
			maxTargets--;

			if (maxTargets <= 0)
				break;
		}
	}

	return result;
}

std::vector<LPOBJ> CMUHelperOffline::ListTargetsDirSemiCircle(LPOBJ lpObj, LPOBJ lpTarget, int maxDist, int maxTargets)
{
	auto result = std::vector<LPOBJ>();
	auto angle = (int)(gObjUseSkill.GetAngle(lpObj->X, lpObj->Y, lpTarget->X, lpTarget->Y) / 360.0f * 255);

	gObjUseSkill.SkillFrustrum3(lpObj->m_Index, angle, 2, 3, 4, 0);

	for (int i = 0; i < MAX_VIEWPORT_MONSTER; i++)
	{
		auto lpVp = &lpObj->VpPlayer[i];

		if (lpVp->state != 2) continue;
		else if (!OBJMAX_RANGE(lpVp->number)) continue;
		else if (lpVp->type != OBJ_MONSTER) continue;

		auto lpTargetObj = &gObj[lpVp->number];

		if (lpTargetObj->Live == 0) continue;

		auto dist = gObjCalDistance(lpTarget, lpTargetObj);

		if (dist <= maxDist && SkillTestFrustrum(lpTargetObj->X, lpTargetObj->Y, lpObj->m_Index))
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

LPOBJ CMUHelperOffline::SearchTargetNearby(LPOBJ lpObj, int maxDist, std::set<int> excludeTargets)
{
	if (maxDist <= 0)
		maxDist = 1;

	auto selTargetDist = maxDist;
	LPOBJ selTargetObj = NULL;

	for (int i = 0; i < MAX_VIEWPORT; i++)
	{
		auto lpVp = &lpObj->VpPlayer[i];

		if (lpVp->state != 2) continue;
		else if (!OBJMAX_RANGE(lpVp->number)) continue;
		else if (lpVp->type != OBJ_MONSTER) continue;
		else if (!excludeTargets.empty() && excludeTargets.find(lpVp->number) != excludeTargets.end()) continue;

		auto lpTargetObj = &gObj[lpVp->number];

		if (lpTargetObj->Live == 0) continue;

		auto dist = gObjCalDistance(lpObj, lpTargetObj);

		if (dist <= selTargetDist || (dist == selTargetDist && selTargetObj == NULL))
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

	if (lpMapItem->m_Type == ITEMGET(14, 15))
	{
		return settings.PickupZen;
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

			std::vector<std::string> words;
			boost::split(words, name, boost::is_space());

			bool match = true;

			for (auto it = words.begin(); it != words.end(); it++)
			{
				std::string itemName = lpMapItem->GetName();
				if (itemName.find(*it) == std::string::npos)
				{
					match = false;
					break;
				}
			}

			if (match)
				return TRUE;
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

CMagicInf * CMUHelperOffline::GetMagicInfo(LPOBJ lpObj, OFFLINE_STATE* lpState)
{
	auto magicCode = 0;
	
	if (lpObj->Class == CLASS_SUMMONER && lpState->useDrainLife)
	{
		magicCode = AT_SKILL_DRAINLIFE;
	}
	else
	{
		magicCode = GetSettingsMagic(lpObj, lpState);
	}

	if (magicCode <= 0 || magicCode >= 0xFFFF)
	{
		lpState->nextAction = m_Now + ONE_SECOND; //Avoid checking every tick
		lpState->playerState = PLAYER_STATE::STANDING;
		PRINT_DEBUG_LINE("STANDING");
		return NULL;
	}

	auto lpMagic = gObjGetMagicSearch(lpObj, magicCode);

	if (lpMagic == NULL)
	{
		LogAddC(2, "[MUHelperOffline] Invalid magic code %d on index %d", magicCode, lpObj->m_Index);
		lpState->nextAction = m_Now + ONE_SECOND; //Avoid checking every tick
		lpState->playerState = PLAYER_STATE::STANDING;
		
		PRINT_DEBUG_LINE("STANDING");
		
		return NULL;
	}

	return lpMagic;
}

int CMUHelperOffline::GetSettingsMagic(LPOBJ lpObj, OFFLINE_STATE* lpState)
{
	if (lpObj->Class == CLASS_KNIGHT && lpState->settings.ComboEnabled == 1
		&& lpState->settings.MainSkill > 0 && lpState->settings.MainSkill < 0xFFFF
		&& lpState->settings.SubSkill1 > 0 && lpState->settings.SubSkill1 < 0xFFFF
		&& lpState->settings.SubSkill2 > 0 && lpState->settings.SubSkill2 < 0xFFFF)
	{
		if (m_Now >= lpState->comboStartTime + COMBO_TIMEOUT)
			lpState->comboNextSkillIndex = 0;

		auto comboIdx = lpState->comboNextSkillIndex;

		lpState->comboNextSkillIndex = (lpState->comboNextSkillIndex + 1) % COMBO_SKILL_COUNT;

		switch (comboIdx)
		{
		case 0:
			return lpState->settings.MainSkill;
		case 1:
			return lpState->settings.SubSkill1;
		default:
			return lpState->settings.SubSkill2;
		}

	}

	if (lpState->settings.SubSkill1 > 0 && lpState->settings.SubSkill1 < 0xFFFF)
	{
		if (lpState->settings.SubSkill1Delay == TRUE && (m_Now - lpState->lastSubSkill1Use) >= (lpState->settings.SubSkill1Dur * ONE_SECOND))
		{
			return lpState->settings.SubSkill1;
		}
		else if (lpState->settings.SubSkill1Cond == TRUE)
		{
			auto distance = MagicDamageC.GetSkillDistance(lpState->settings.SubSkill1);

			if (distance <= 0)
				distance = 1;

			auto targets = ListTargetsTargetCircle(lpObj, lpObj, distance);

			if (targets.size() >= (lpState->settings.SubSkill1SubCond + 2)) //Number of monsters starts in 2, so lets add 1
				return lpState->settings.SubSkill1;
		}
	}
	
	if (lpState->settings.SubSkill2 > 0 && lpState->settings.SubSkill2 < 0xFFFF)
	{
		if (lpState->settings.SubSkill2Delay == TRUE && (m_Now - lpState->lastSubSkill2Use) >= (lpState->settings.SubSkill2Dur * ONE_SECOND))
		{
			return lpState->settings.SubSkill2;
		}
		else if (lpState->settings.SubSkill2Cond == TRUE)
		{
			auto distance = MagicDamageC.GetSkillDistance(lpState->settings.SubSkill2);

			if (distance <= 0)
				distance = 1;

			auto targets = ListTargetsTargetCircle(lpObj, lpObj, distance);

			if (targets.size() >= (lpState->settings.SubSkill2SubCond + 2)) //Number of monsters starts in 2, so lets add 1
				return lpState->settings.SubSkill2;
		}
	}
	
	if (lpState->settings.MainSkill > 0)
	{
		return lpState->settings.MainSkill;
	}

	return 0;
}

int CMUHelperOffline::CalcAttackInterval(LPOBJ lpObj, SKILL_AREA_INFO skillInfo)
{
	auto speed = max(lpObj->m_AttackSpeed, lpObj->m_MagicSpeed);
	auto diff = abs(skillInfo.interval - speed);
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
		if (!IsActive(n)) continue;

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

	if (lpState->active) return;

	LPOBJ lpObj = &gObj[aIndex];

	g_MUHelper.ReqMacro(aIndex, true);
	lpState->settingsState == SETTINGS_STATE::REQUESTED;
	lpState->active = true;
	lpState->originX = lpObj->X;
	lpState->originY = lpObj->Y;
	lpState->nextAction = GetTickCount() + (ONE_SECOND); //Wait a little delay before starting
	lpState->nextZenBilling = 0;

	if (lpState->offline == false)
	{
		//lpState->shouldDestroyVP = true; //Destroy the main version
		lpState->shouldCreateVP = true; //Create the dummy version

		GDSavePlayerState(lpObj);

		MUHELPEROFF_ACTION pMsg;
		pMsg.Action = true;
		pMsg.h.set((LPBYTE)&pMsg, LC_HEADER, LC_MUHELPER_OFF_ACTION, sizeof(MUHELPEROFF_ACTION));
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
	}
}

void CMUHelperOffline::Stop(int aIndex)
{
	auto lpState = GetState(aIndex);

	if (lpState->active == false) return;

	if (lpState->offline == false)
	{
		LPOBJ lpObj = &gObj[aIndex];

		lpState->shouldDestroyVP = true; //destroy the dummy
		//lpState->shouldCreateVP = true; //create the main version;
		lpState->shouldClearState = true;

		MUHELPEROFF_ACTION pMsg;
		pMsg.Action = false;
		pMsg.h.set((LPBYTE)&pMsg, LC_HEADER, LC_MUHELPER_OFF_ACTION, sizeof(MUHELPEROFF_ACTION));
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);

		gObjSetPosition(aIndex, lpState->originX, lpState->originY);
	}
	else
	{
		lpState->active = false;
		GDSavePlayerState(&gObj[aIndex]);
	}
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

	if (lpState->offline)
	{
		lpObj->CheckTick = m_Now;
		lpObj->CheckSumTime = 0;
	}

	if (lpObj->Live == 0 // Dead
		|| g_ExUser.InSafeZone(lpObj->m_Index) // On safe zone
		|| lpObj->RegenOk != 0 // Respawn
		|| lpObj->Teleport != 0 // Teleport
		)
	{
		if (lpState->offline)
		{
			lpState->nextAction = m_Now + ONE_SECOND;
			return;
		}
		else
		{
			Stop(lpObj->m_Index);
		}
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

	ChargeZen(lpObj, lpState);

	CheckPotions(lpObj, lpState);
	CheckPet(lpObj, lpState);
	CheckRepair(lpObj, lpState);

	if (lpState->nextAction > m_Now) return;

	if (CheckHeal(lpObj, lpState)) return;
	if (CheckBuffs(lpObj, lpState)) return;
	if (CheckItems(lpObj, lpState)) return;
	if (CheckMoving(lpObj, lpState)) return;
	if (CheckAttack(lpObj, lpState)) return;
}