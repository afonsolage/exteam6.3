#include "stdafx.h"
#include "CustomQuestSystem.h"
#include "user.h"
#include "GameMain.h"
#include "DSProtocol.h"
#include "ExFunction.h"
#include "logproc.h"
#include "ExUser.h"
//#include "BuffManagerEx.h"
#include "..\include\ReadScript.h"
#include "gObjMonster.h"
#include "MapClass.h"

CCustomQuestSystem g_CustomQuestSystem;

CCustomQuestSystem::CCustomQuestSystem(void)
{
}


CCustomQuestSystem::~CCustomQuestSystem(void)
{
}

void CCustomQuestSystem::Init()
{
	m_vUniqueQuests.clear();
	m_vDailyQuests.clear();
	m_vGuildQuests.clear();
	m_bEnabled = false;
	m_iNpcClass = 0;
}

void CCustomQuestSystem::Load()
{
	Init();

	m_bEnabled = (BOOL) GetPrivateProfileInt("Quest", "Enabled", 0, gDirPath.GetNewPath("Custom\\Quests\\Config.ini"));

	if (!m_bEnabled)
		return;

	m_iNpcClass = GetPrivateProfileInt("Quest", "NPC_CLASS", 0, gDirPath.GetNewPath("Custom\\Quests\\Config.ini"));

	LoadQuests(CQ_UNIQUE_QUEST, "Custom\\Quests\\Unique.txt");
	LoadQuests(CQ_DAILY_QUEST, "Custom\\Quests\\Daily.txt");
}

void CCustomQuestSystem::LoadQuests(int type, char* path)
{
	int Token;
	char* file_path = gDirPath.GetNewPath(path);

	SMDFile = fopen(file_path, "r");

	if( SMDFile == NULL )
	{
		MsgBox(lMsg.Get(MSGGET(0, 112)), file_path);
		return;
	}

	std::vector<CustomQuestData>& quests = FindQuestList(type);

	while(true)
	{
		Token = GetToken();

		if (Token == END)
		{
			break;
		}

		if ( Token != NUMBER )
		{
			break;
		}

		CustomQuestData data;
		memset(&data, 0, sizeof(data));

		data.id = (int)TokenNumber;

		Token = GetToken();
		data.NeedLevel = (int)TokenNumber;

		if (type == CQ_DAILY_QUEST)
		{
			Token = GetToken();
			data.MaxLevel = (int)TokenNumber;
		}

		Token = GetToken();
		data.NeedReset = (int)TokenNumber;

		Token = GetToken();
		strncpy(data.NameQuest, TokenString, 25);

		Token = GetToken();
		data.AllowDW = (BOOL)TokenNumber;

		Token = GetToken();
		data.AllowDK = (BOOL)TokenNumber;

		Token = GetToken();
		data.AllowELF = (BOOL)TokenNumber;

		Token = GetToken();
		data.AllowSUM = (BOOL)TokenNumber;

		Token = GetToken();
		data.AllowMG = (BOOL)TokenNumber;

		Token = GetToken();
		data.AllowDL = (BOOL)TokenNumber;

		Token = GetToken();
		data.AllowRF = (BOOL)TokenNumber;

		Token = GetToken();
		int session = (int)TokenNumber;

		if (session != 1)
		{
			break;
		}

		Token = GetToken();
		while (Token == NUMBER)
		{
			CustomQuestMission mission;
			mission.MobID = (int)TokenNumber;

			Token = GetToken();
			mission.MobCount = (int)TokenNumber;

			Token = GetToken();

			data.missions.emplace_back(mission);
		}

		Token = GetToken();
		session = (int)TokenNumber;

		if (session != 2)
		{
			break;
		}

		Token = GetToken();
		while (Token == NUMBER)
		{
			CustomQuestReward reward;
			reward.Type = (int)TokenNumber;

			Token = GetToken();
			reward.Count = (int)TokenNumber;

			if (reward.Type == RewardType::ITEM)
			{
				Token = GetToken();
				reward.ItemType = (int)TokenNumber;

				Token = GetToken();
				reward.ItemIdx = (int)TokenNumber;

				Token = GetToken();
				reward.ItemLvl = (int)TokenNumber;
			}

			Token = GetToken();

			data.rewards.emplace_back(reward);
		}

		Token = GetToken();

		quests.emplace_back(data);
	}

	fclose(SMDFile);
}

bool CCustomQuestSystem::Dialog(int aIndex, int aNpcIndex)
{
	if (!m_bEnabled)
	{
		return false;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNpcIndex];

	if (lpNpc->Class != this->m_iNpcClass)
	{
		return false;
	}

	this->GC_MainInfo(lpUser);

	return true;
}

int CCustomQuestSystem::FindNextQuest(int type, LPOBJ lpUser)
{
	if (type == CQ_DAILY_QUEST && !IsDailyQuestAvailable(lpUser))
		return 0;

	std::vector<CustomQuestData>& quests = FindQuestList(type);
	
	for(int i = 0; i < quests.size(); i++)
	{
		if (lpUser->Level < quests[i].NeedLevel)
			continue;

		if (quests[i].MaxLevel > 0 && quests[i].MaxLevel < lpUser->Level)
			continue;

		if (type == CQ_DAILY_QUEST && lpUser->Level > quests[i].MaxLevel)
			continue;

		if (lpUser->Reset < quests[i].NeedReset)
			continue;

		switch (lpUser->Class)
		{
		case CLASS_WIZARD: if (quests[i].AllowDW == 0) continue; break;
		case CLASS_KNIGHT: if (quests[i].AllowDK == 0) continue; break;
		case CLASS_ELF: if (quests[i].AllowELF == 0) continue; break;
		case CLASS_SUMMONER: if (quests[i].AllowSUM == 0) continue; break;
		case CLASS_MAGUMSA: if (quests[i].AllowMG == 0) continue; break;
		case CLASS_DARKLORD: if (quests[i].AllowDL == 0) continue; break;
		case CLASS_MONK: if (quests[i].AllowRF == 0) continue; break;
		}

		return m_vUniqueQuests[i].id;
	}

	return 0;
}

bool CCustomQuestSystem::IsDailyQuestAvailable(LPOBJ lpUser)
{
	return lpUser->ExWQuestNum[CQ_DAILY_QUEST] < GetTodayDaysCount();
}

CustomQuestData CCustomQuestSystem::FindQuestData(int type, int id)
{
	CustomQuestData empty;
	memset(&empty, 0, sizeof(empty));

	std::vector<CustomQuestData>& quests = FindQuestList(type);

	for(int i = 0; i < quests.size(); i++)
	{
		if (quests[i].id == id)
			return quests[i];
	}

	return empty;
}

void CCustomQuestSystem::GC_MainInfo(LPOBJ lpUser)
{
	GC_MainPacket pReq;
	memset(&pReq, 0, sizeof(pReq));

	pReq.h.set((LPBYTE)&pReq, 0xFA, 0xCC, sizeof(pReq));

	for (int t = 0; t < CQ_QUEST_TP_CNT; t++)
	{
		pReq.exQuest[t].b_End = false;
		pReq.exQuest[t].b_Level = true;
		pReq.exQuest[t].b_Reset = true;
		pReq.exQuest[t].b_accept = true;

		int cur_quest_id = lpUser->ExWQuestNum[t];

		//Fix possible erros with daily quest not started
		if (t == CQ_DAILY_QUEST && cur_quest_id < MAX_DAILY_QUEST_ID && !lpUser->ExWQuestStart[t])
		{
			cur_quest_id = 0;
			lpUser->ExWQuestNum[t] = 0;
		}

		if (cur_quest_id == 0 || (t == CQ_DAILY_QUEST && cur_quest_id > MAX_DAILY_QUEST_ID && IsDailyQuestAvailable(lpUser)))
		{
			cur_quest_id = FindNextQuest(t, lpUser);
		} 

		CustomQuestData data = FindQuestData(t, cur_quest_id);

		if (data.id == 0)
		{
			pReq.exQuest[t].b_End = true;
			continue;
		}

		if (data.NeedLevel > lpUser->Level)
		{
			pReq.exQuest[t].b_Level = false;
			pReq.exQuest[t].b_accept = false;
		}

		if (data.NeedReset > lpUser->Reset)
		{
			pReq.exQuest[t].b_Reset = false;
			pReq.exQuest[t].b_accept = false;
		}

		strncpy(pReq.exQuest[t].NameQuest, data.NameQuest, 25);
		pReq.exQuest[t].Start = lpUser->ExWQuestStart[t];
		pReq.exQuest[t].Number = lpUser->ExWQuestNum[t];
		pReq.exQuest[t].NeedLevel = data.NeedLevel;
		pReq.exQuest[t].NeedReset = data.NeedReset;
		pReq.exQuest[t].b_done = true;

		for (int i = 0; i < data.missions.size(); i++)
		{
			if (data.missions[i].MobCount > lpUser->ExWQuestCount[t][i])
			{
				pReq.exQuest[t].b_done = false;
				pReq.exQuest[t].b_Mission[i] = false;
			}
			else
			{
				pReq.exQuest[t].b_Mission[i] = true;
			}

			pReq.exQuest[t].Count[i] = lpUser->ExWQuestCount[t][i];
			pReq.exQuest[t].MissionType[i] = 1; //HUNTING;
			pReq.exQuest[t].MissionID[i] = data.missions[i].MobID;
			pReq.exQuest[t].MissionCount[i] = data.missions[i].MobCount;
		}

		for (int i = 0; i < data.rewards.size(); i++)
		{
			pReq.exQuest[t].RewardType[i] = data.rewards[i].Type;
			pReq.exQuest[t].RewardCount[i] = data.rewards[i].Count;
			pReq.exQuest[t].RewardItemType[i] = data.rewards[i].ItemType;
			pReq.exQuest[t].RewardItemIndex[i] = data.rewards[i].ItemIdx;
			pReq.exQuest[t].RewardItemLevel[i] = data.rewards[i].ItemLvl;
		}
	}
	DataSend(lpUser->m_Index, (LPBYTE)&pReq, sizeof(pReq));
}

void CCustomQuestSystem::CG_AcceptQuest(int aIndex, CG_CQAcceptDone* aRecv)
{
	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}	

	if(aRecv->Result != 0 && aRecv->Result != 1 && aRecv->Result != 2)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	int type = aRecv->Result;
	int cur_quest_id = lpUser->ExWQuestNum[type];
	
	if (cur_quest_id == 0 || (type == CQ_DAILY_QUEST && cur_quest_id > MAX_DAILY_QUEST_ID && IsDailyQuestAvailable(lpUser)))
	{
		cur_quest_id = FindNextQuest(type, lpUser);
		lpUser->ExWQuestNum[type] = cur_quest_id;
	}
	
	CustomQuestData data = FindQuestData(type, cur_quest_id);

	if( data.id == 0 || data.NeedLevel > lpUser->Level || data.NeedReset > lpUser->Reset 
		|| (data.MaxLevel > 0 && data.MaxLevel < lpUser->Level) )
	{
		LogAddC(2, "[ExWinQuestSystem] Error CG_AcceptQuest Result");
		return;
	}

	if(!lpUser->ExWQuestStart[type])
	{
		lpUser->ExWQuestStart[type] = true;
		this->GC_Start(aIndex, type, true);
	}
	else
	{
		this->RewardQuest(aIndex, type);
	}
}

void CCustomQuestSystem::GC_Start(int aIndex, int type, bool start)
{
	GC_CQStart pReq = { 0 };
	pReq.h.set((LPBYTE)&pReq, 0xFB, 0xC4, sizeof(pReq));
	pReq.Act = type;
	pReq.Start = start;
	DataSend(aIndex, (LPBYTE)&pReq, pReq.h.size);
}

void CCustomQuestSystem::RewardQuest(int aIndex, int type)
{
	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}	

	LPOBJ lpUser = &gObj[aIndex];

	int cur_quest_id = lpUser->ExWQuestNum[type];
	CustomQuestData data = FindQuestData(type, cur_quest_id);

	if (data.id == 0 || data.missions.size() == 0 || data.rewards.size() == 0)
	{
		LogAddC(2, "[CustomQuestSystem] Failed to reward! No mission found for quest id %d", cur_quest_id);
		return;
	}

	bool completed = true;
	for (int i = 0; i < data.missions.size(); i++)
	{
		if (data.missions[i].MobCount > lpUser->ExWQuestCount[type][i])
			completed = false;
	}

	if (!completed)
	{
		LogAddC(2, "[CustomQuestSystem] Failed to reward! Missions not completed at quest id %d", cur_quest_id);
		return;
	}

	for (int i = 0; i < data.missions.size(); i++)
	{
		lpUser->ExWQuestCount[type][i] = 0;
	}

	for (int i = 0; i < data.rewards.size(); i++)
	{
		if(!MAX_MAP_RANGE(lpUser->MapNumber))
		{
			return;
		}

		if (data.rewards[i].Type == RewardType::ZEN)
		{	
			MapC[lpUser->MapNumber].MoneyItemDrop(data.rewards[i].Count, lpUser->X, lpUser->Y);
		}
		else if (data.rewards[i].Type == RewardType::ITEM)
		{
			for(int c = 0; c < data.rewards[i].Count; c++)
			{
				ItemSerialCreateSend(aIndex, lpUser->MapNumber, lpUser->X, lpUser->Y, ITEMGET(data.rewards[i].ItemType, data.rewards[i].ItemIdx),
					data.rewards[i].ItemLvl, 0, 0, 0, 0, lpUser->m_Index, 0, 0);
			}
		}
	}

	if (type == CQ_DAILY_QUEST)
		lpUser->ExWQuestNum[type] = GetTodayDaysCount();
	else
		lpUser->ExWQuestNum[type]++;

	lpUser->ExWQuestStart[type] = false;
	this->GC_MainInfo(lpUser);
}

void CCustomQuestSystem::UserConnect(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	GC_CQMiniInfo pReq = { 0 };
	pReq.h.set((LPBYTE)&pReq, 0xFA, 0xCD, sizeof(pReq));

	for(int t = 0; t < CQ_QUEST_TP_CNT; t++)
	{
		int cur_quest_id = lpUser->ExWQuestNum[t];

		if (cur_quest_id == 0)
		{
			cur_quest_id = FindNextQuest(t, lpUser);
		}

		CustomQuestData data = FindQuestData(t, cur_quest_id);

		strncpy(pReq.cqQuest[t].NameQuest, data.NameQuest, 25);
		pReq.cqQuest[t].Start = lpUser->ExWQuestStart[t];

		for(int i = 0; i < data.missions.size(); i++)
		{
			pReq.cqQuest[t].ExWQuestCount[i] = lpUser->ExWQuestCount[t][i];
			pReq.cqQuest[t].MissionType[i] = 1; //Hunting;
			pReq.cqQuest[t].MissionID[i] = data.missions[i].MobID;
			pReq.cqQuest[t].MissionCount[i] = data.missions[i].MobCount;
		}
	}
	DataSend(aIndex, (LPBYTE)&pReq, sizeof(pReq));
}

void CCustomQuestSystem::GC_MiniInfoEx(int aIndex, int type, int mission)
{
	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}

	GC_CQMiniInfoEx exSend = { 0 };
	exSend.h.set((LPBYTE)&exSend, 0xFB, 0xC3, sizeof(exSend));

	exSend.a = type;
	exSend.m = mission;

	DataSend(aIndex, (LPBYTE)&exSend, exSend.h.size);
}

bool CCustomQuestSystem::MonsterKiller(int aIndexMonster, int aIndexUser)
{
	if (!this->m_bEnabled)
		return false;

	LPOBJ lpUser = &gObj[aIndexUser];
	LPOBJ lpMonster = &gObj[aIndexMonster];

	for (int t = 0; t < CQ_QUEST_TP_CNT; t++)
	{
		if (!lpUser->ExWQuestStart[t])
			continue;

		int cur_quest_id = lpUser->ExWQuestNum[t];
		CustomQuestData data = FindQuestData(t, cur_quest_id);

		if (data.id == 0)
			continue;

		for(int i = 0; i < data.missions.size(); i++)
		{
			if (data.missions[i].MobCount > lpUser->ExWQuestCount[t][i])
			{
				if (data.missions[i].MobID == lpMonster->Class)
				{
					lpUser->ExWQuestCount[t][i]++;
					this->GC_MiniInfoEx(aIndexUser, t, i);
					return true;
				}
			}
		}
	}
	return false;
}