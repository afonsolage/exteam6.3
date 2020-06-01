#pragma once

#include "StdAfx.h"
#include "user.h"

#define PANDORA_EVENT_DIR	"..\\Data\\ExData\\Events\\PandoraBox.ini"

#define PAN_EVENT_MAX_CORD 300
#define PAN_EVENT_MAX_TIME 20
#define PAN_EVENT_MAX_REWARD_ITEM 100

/*	
	Кординаты возможных точек появления сундука
*/
struct CordsBox
{
	int X;
	int Y;
	int Map;
};
/*
	Время появления сундуку
*/
struct TimePandora
{
	int Hour;
	int Min;
};
struct PandoraRewardDrop
{
	int Type;
	int Index;
	int Level;
	int Skill;
	int Luck;
	int Opt;
	int Exl;
	int Anc;
};
class cPandoraBoxEvent
{
public:
	void Init();
	void Load();
	void Announce();
	void Start();
	void End();
	void TickTime();
	void RespawnBox(CordsBox RandCord);
	bool BoxClick(LPOBJ lpNpc, LPOBJ lpObj);
	BOOL Player(LPOBJ lpObj);
	bool ProcessKill(LPOBJ lpObj, LPOBJ lpTargetObj);
	void Prize();
	bool PkCheck(LPOBJ lpObj, LPOBJ lpTarget);
	bool BlockTeleport(int aIndex);
	void CloseClient(int aIndex);

	void TickOwner();

	int ActivePlayer;
	bool Started;
	bool Announcing;
//private:
	bool Enable;
	CordsBox Cords[PAN_EVENT_MAX_CORD];
	int CountCord;
	TimePandora Times[PAN_EVENT_MAX_TIME];
	int CountTimes;
	PandoraRewardDrop Reward[PAN_EVENT_MAX_REWARD_ITEM];
	int CountReward;
	int JewelDropRate;
	int ActiveMap;
	int EventTime;
	
	CordsBox BoxSpawnedCoords;

	int EventTimeSecond;
	int FootprintSecond;

	int AnnounceCount;
	int MaxAnnounceCount;
	int FirstFootprintTimeout;
	int PlayerFootprintInterval;
	int ActivePlayerPkLevel;
	int ActivePlayerMoveSpeed;

	int BoxIndex;

	int RewardCredits;
	int RewardWcoinC;
	int RewardWcoinP;
	int RewardGoblinPoints;
};
extern cPandoraBoxEvent gPandoraBoxEvent;
