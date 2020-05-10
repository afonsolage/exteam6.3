#include "StdAfx.h"
#include "PandoraBoxEvent.h"

#include "Functions.h"
#include "Message.h"
#include "DSProtocol.h"
#include "ExUser.h"
#include "ExFunction.h"
#include "TimerEx.h"
#include "ExLicense.h"
#include "GameMain.h"
#include "BuffManager.h"

cPandoraBoxEvent gPandoraBoxEvent;

void cPandoraBoxEvent::Init()
{
	this->Started = false;
	this->EventTimeSecond = 0;
	this->CountCord = 0;
	this->CountTimes = 0;
	this->CountReward = 0;
	this->ActiveMap = 0;
	this->Started = false;
	this->EventTime = 0;
	this->EventTimeSecond = 0;
	this->Announcing = false;
	this->AnnounceCount = 0;
	this->MaxAnnounceCount = 0;
	this->FirstFootprintTimeout = 0;
	this->PlayerFootprintInterval = 0;

	this->RewardCredits = 0;
	this->RewardWcoinC = 0;
	this->RewardWcoinP = 0;
	this->RewardGoblinPoints = 0;

	for (int i = 0; i < PAN_EVENT_MAX_CORD; i++)
	{
		Cords[i].Map = 0;
		Cords[i].X = 0;
		Cords[i].Y = 0;
	}
	for (int i = 0; i < PAN_EVENT_MAX_TIME; i++)
	{
		Times[i].Hour = 0;
		Times[i].Min = 0;
	}
	for(int i = 0; i < PAN_EVENT_MAX_REWARD_ITEM; i++)
	{
		this->Reward[i].Type	= 0;
		this->Reward[i].Index	= 0;
		this->Reward[i].Level	= 0;
		this->Reward[i].Skill	= 0;
		this->Reward[i].Luck	= 0;
		this->Reward[i].Opt		= 0;
		this->Reward[i].Exl		= 0;
		this->Reward[i].Anc		= 0;
	}
}

void cPandoraBoxEvent::Load()
{
	this->Init();
	this->Enable = (gNonPK) ? false : GetPrivateProfileInt("ExTeam","Enable",0,PANDORA_EVENT_DIR);
	
	if (!this->Enable)
	{
		return;
	}
	
	this->EventTime = GetPrivateProfileInt("ExTeam","EventTime",10,PANDORA_EVENT_DIR);
	this->MaxAnnounceCount = GetPrivateProfileInt("ExTeam", "AnnounceCount", 10, PANDORA_EVENT_DIR);;
	this->FirstFootprintTimeout = GetPrivateProfileInt("ExTeam", "FirstFootprintTimeout", 10, PANDORA_EVENT_DIR);;
	this->PlayerFootprintInterval = GetPrivateProfileInt("ExTeam", "PlayerFootprintInterval", 10, PANDORA_EVENT_DIR);;

	this->RewardCredits = GetPrivateProfileInt("ExTeam","RewardCredits",0,PANDORA_EVENT_DIR);
	this->RewardWcoinC = GetPrivateProfileInt("ExTeam","RewardWcoinC",0,PANDORA_EVENT_DIR);
	this->RewardWcoinP = GetPrivateProfileInt("ExTeam","RewardWcoinP",0,PANDORA_EVENT_DIR);
	this->RewardGoblinPoints = GetPrivateProfileInt("ExTeam","RewardGoblinPoints",0,PANDORA_EVENT_DIR);

	FILE *file = fopen(PANDORA_EVENT_DIR,"r");

	if(file == NULL)
	{
		this->Enable = 0;
		return;
	}

	char Buff[256];
	int Flag = 0;

	while(!feof(file))
	{
		fgets(Buff,256,file);	
		if(Ex_IsBadFileLine(Buff, Flag))	
			continue;

		if(Flag == 1)
		{
			int n[3];
			sscanf(Buff, "%d %d %d",&n[0],&n[1],&n[2]);

			this->Cords[this->CountCord].Map	= n[0];
			this->Cords[this->CountCord].X		= n[1];
			this->Cords[this->CountCord].Y		= n[2];

			this->CountCord++;

			if (this->CountCord >= PAN_EVENT_MAX_CORD)
			{
				break;
			}
		}
		if(Flag == 2)
		{
			int n[2];
			sscanf(Buff, "%d %d",&n[0],&n[1]);

			this->Times[this->CountTimes].Hour	= n[0];
			this->Times[this->CountTimes].Min	= n[1];

			this->CountTimes++;

			if (this->CountTimes >= PAN_EVENT_MAX_TIME)
			{
				break;
			}
		}
		if(Flag == 3)
		{
			int n[8];
			sscanf(Buff, "%d %d %d %d %d %d %d %d",&n[0],&n[1],&n[2],&n[3],&n[4],&n[5],&n[6],&n[7]);

			this->Reward[this->CountReward].Type		= n[0];
			this->Reward[this->CountReward].Index		= n[1];
			this->Reward[this->CountReward].Level		= n[2];
			this->Reward[this->CountReward].Skill		= n[3];
			this->Reward[this->CountReward].Luck		= n[4];
			this->Reward[this->CountReward].Opt		= n[5];
			this->Reward[this->CountReward].Exl		= n[6];
			this->Reward[this->CountReward].Anc		= n[7];
			
			
			if(this->Reward[this->CountReward].Skill) this->Reward[this->CountReward].Skill = 1;
			if(this->Reward[this->CountReward].Luck) this->Reward[this->CountReward].Luck = 1;

			this->CountReward++;

			if (this->CountReward >= PAN_EVENT_MAX_REWARD_ITEM)
			{
				break;
			}
		}
	}
	fclose(file);
}
void cPandoraBoxEvent::Announce()
{
	this->Announcing = true;
	if (AnnounceCount > 0)
	{
		MessaageAllGlobal("[Pandora Event] Will start in %d minute(s)", AnnounceCount);
		AnnounceCount--;
	}
	else
	{
		this->Announcing = false;
		Start();
	}
}

void cPandoraBoxEvent::TickTime()
{
	if (!this->Enable) return;

	SYSTEMTIME time;
	GetLocalTime(&time);
	if (this->Started)
	{
		if ((this->EventTime * 60) > this->EventTimeSecond )
		{
			this->EventTimeSecond++;
			this->FootprintSecond++;
		}
		else
		{
			this->End();
		}

		if (FootprintSecond > this->FirstFootprintTimeout && this->ActivePlayer == -1 && this->BoxIndex != -1)
		{
			MessaageAllGlobal("[Pandora Event] The box seems to be at X: %d, Y: %d", this->BoxSpawnedCoords.X, this->BoxSpawnedCoords.Y);
			FootprintSecond = 0;
		}
		else if (this->BoxIndex == -1 && this->ActivePlayer != -1 && FootprintSecond % this->PlayerFootprintInterval == 0)
		{
			if (!gObjIsConnected(this->ActivePlayer))
			{
				CordsBox RandCord = Cords[rand() % this->CountCord];
				this->RespawnBox(RandCord);

				MessaageAllGlobal("[Pandora Event] old box owner vanished! Box respawned somewhere!");
			}
			else
			{
				LPOBJ lpObj = &gObj[this->ActivePlayer];

				MessaageAllGlobal("[Pandora Event] Someone saw %s at X: %d, Y: %d", lpObj->Name, lpObj->X, lpObj->Y);
			}
		}
	}
#if(NEWTIMEREX)
	else if(g_TimerEx.GetSecond() == 00)
#else
	else if(time.wSecond == 00)
#endif
	{
		if (this->Announcing)
		{
			this->Announce();
		}
		else
		{
			for(int i = 0; i < this->CountTimes; i++)
			{
				if(Times[i].Hour == time.wHour && Times[i].Min == time.wMinute)
				{
					this->AnnounceCount = this->MaxAnnounceCount;
					this->Announce();
					break;
				}
			}
		}
	}
}
void cPandoraBoxEvent::Start()
{
	if (!this->Enable) return;

	this->Started = true;
	srand(time(NULL));
	CordsBox RandCord = Cords[rand()%this->CountCord];
	
	MessaageAllGlobal("[Pandora Event] Started");
	this->RespawnBox(RandCord);
}
void cPandoraBoxEvent::End()
{
	 if (!this->Enable) return;

	 this->EventTimeSecond = 0;
	 this->FootprintSecond = 0;
	 this->Prize();
	 this->Started = false;
	 LPOBJ lpObj = &gObj[this->ActivePlayer];
	 gObjDel(this->BoxIndex);
	 this->BoxIndex = -1;
	 lpObj->m_Change = -1;
	 lpObj->m_PK_Level = this->ActivePlayerPkLevel;
	 gObjRemoveBuffEffect(lpObj, AT_ICE);
	 gObjViewportListProtocolCreate(lpObj);
	 this->ActivePlayer = -1;
	 MessaageAllGlobal("[Pandora Event] End Win %s", lpObj->Name);
}

void cPandoraBoxEvent::RespawnBox(CordsBox RandCord)
{
	if (!this->Enable) return;

	this->ActiveMap = RandCord.Map;

	
#if(RANDOM_BOX_CORD_PANDORA)
	BYTE cX = 0;
	BYTE cY = 0;
	bool randomRespawnCords = false;
	if (g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ConflictNoCustom) || g_ExLicense.CheckUser(eExUB::ulasevich2))
	{
		randomRespawnCords = gObjGetRandomFreeArea(RandCord.Map, (BYTE &)cX, (BYTE &)cY, 0, 0, 255, 255, 100);
	}
#endif

	int result = gObjAddMonster(this->ActiveMap);

	if(result >= 0 && result < OBJ_MAXMONSTER)
	{
		this->BoxSpawnedCoords = RandCord;
		this->FootprintSecond = 0;

		gObj[result].m_PosNum = (WORD)-1;
		gObj[result].MapNumber = this->ActiveMap;
#if(RANDOM_BOX_CORD_PANDORA)
		if (randomRespawnCords && cX != 0 && cY != 0)
		{
			gObj[result].X = cX;
			gObj[result].Y = cY;
			gObj[result].TX = cX;
			gObj[result].TY = cY;
			gObj[result].m_OldX = cX;
			gObj[result].m_OldY = cY;
			gObj[result].StartX = cX;
			gObj[result].StartY = cY;

		}
		else
#endif
		{
			gObj[result].X = RandCord.X;
			gObj[result].Y = RandCord.Y;
			gObj[result].TX = RandCord.X;
			gObj[result].TY = RandCord.Y;
			gObj[result].m_OldX = RandCord.X;
			gObj[result].m_OldY = RandCord.Y;
			gObj[result].StartX = RandCord.X;
			gObj[result].StartY = RandCord.Y;
		}
		gObj[result].MaxRegenTime = 0;
		gObj[result].Dir = rand()%8;
		gObj[result].RegenTime = GetTickCount();

		gObj[result].m_ActState.Emotion       = 1;
		gObj[result].m_ActState.EmotionCount  = 15;

		gObjSetMonster(result,542);

		this->BoxIndex = result;	

	}

}
bool cPandoraBoxEvent::BoxClick(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (!this->Enable) return false;
	else if (!this->Started) return false;
	else if (this->ActiveMap != lpNpc->MapNumber) return false;
	else if (lpNpc->m_Index != this->BoxIndex) return false;
	
	this->Player(lpObj);

	MessaageAllGlobal("[Pandora Event] %s Capture Box", lpObj->Name);	
	MessaageAllGlobal("[Pandora Event] X: %d Y: %d", lpObj->X, lpObj->Y);
	gObjDel(this->BoxIndex);
	this->BoxIndex = -1;
	this->BoxSpawnedCoords = {};

	return true;
}

BOOL cPandoraBoxEvent::Player(LPOBJ lpObj)
{
	if (lpObj->Type == OBJ_USER)
	{
		if (this->ActivePlayer != -1)
		{
			LPOBJ lpOldObj = &gObj[this->ActivePlayer];
			lpOldObj->m_Change = -1;
			lpOldObj->m_PK_Level = this->ActivePlayerPkLevel;
			gObjRemoveBuffEffect(lpObj, AT_ICE);
			gObjViewportListProtocolCreate(lpOldObj);
		}

		this->ActivePlayerPkLevel = lpObj->m_PK_Level;
		this->ActivePlayerMoveSpeed = lpObj->m_MoveSpeed;

		lpObj->m_Change = 404;
		lpObj->m_PK_Level = 6;
		gObjApplyBuffEffectDuration(lpObj, AT_ICE, 0, 0, 0, 0, -10);
		gObjViewportListProtocolCreate(lpObj);

		this->ActivePlayer = lpObj->m_Index;

		return TRUE;
	}
	else //Some something else killed the player, let's respawn the pandora box
	{
		CordsBox RandCord = Cords[rand() % this->CountCord];
		this->RespawnBox(RandCord);
	}
}
bool cPandoraBoxEvent::ProcessKill(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if(!this->Enable)return false;
	if(!this->Started)return false;
	
	if (lpTargetObj->m_Index != this->ActivePlayer)
	{
		return false;
	}

	std::string oldOwner = "Pandora Owner";

	if (gObjIsConnected(this->ActivePlayer))
	{
		oldOwner = gObj[this->ActivePlayer].Name;
	}

	if (this->Player(lpObj))
	{
		MessaageAllGlobal("[Pandora Event] %s Capture Box", lpObj->Name);	
		MessaageAllGlobal("[Pandora Event] Map: %s X: %d Y: %d", exMapName(lpObj->MapNumber), lpObj->X, lpObj->Y);
	}
	else
	{
		MessaageAllGlobal("[Pandora Event] %s Died! Box respawned somewhere!", oldOwner.c_str());
	}

	return true;
}
void cPandoraBoxEvent::Prize()
{
	if(!this->Enable)return;
	if(!this->Started)return;
	if (this->ActivePlayer == -1) return;

	LPOBJ lpObj = &gObj[this->ActivePlayer];
	
	for (int i = 0; i < this->CountReward; i++)
	{
		int NewExl = 0;
		int NewAnc = 0;

		int DropItem = ITEMGET(this->Reward[i].Type,this->Reward[i].Index);

		if(Reward[i].Exl > 0)
			NewExl = GenExcOpt(Reward[i].Exl);

		if(Reward[i].Anc == 5 || Reward[i].Anc == 10)
			NewAnc = Reward[i].Anc;

		ItemSerialCreateSend(lpObj->m_Index,lpObj->MapNumber,lpObj->X,lpObj->Y,DropItem,this->Reward[i].Level,0,
			this->Reward[i].Skill,this->Reward[i].Luck,this->Reward[i].Opt,lpObj->m_Index,NewExl,NewAnc);
	}

	if(this->RewardWcoinC > 0)
	{
			lpObj->GameShop.WCoinC += this->RewardWcoinC;
			gGameShop.GDSaveUserInfo(lpObj->m_Index);
			MessageChat(lpObj->m_Index,"~[Pandora Event]: Reward : %d LCoins",this->RewardWcoinC);
	}

	if(this->RewardWcoinP > 0)
	{
			lpObj->GameShop.WCoinP += this->RewardWcoinP;
			gGameShop.GDSaveUserInfo(lpObj->m_Index);
			MessageChat(lpObj->m_Index,"~[Pandora Event]: Reward: %d WCoinP",this->RewardWcoinP);
	}

	if(this->RewardGoblinPoints > 0)
	{
			lpObj->GameShop.GoblinPoint += this->RewardGoblinPoints;
			gGameShop.GDSaveUserInfo(lpObj->m_Index);
			MessageChat(lpObj->m_Index,"~[Pandora Event]: Reward: %d Goblin",this->RewardGoblinPoints);
	}

	if(this->RewardCredits > 0)
	{
			lpObj->ExCred += this->RewardCredits;
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
			ExUserDataSend(lpObj->m_Index);
			MessageChat(RewardCredits,"~[Pandora Event]: Bonus: %d Credit",this->RewardCredits);
	}

}
bool cPandoraBoxEvent::PkCheck(LPOBJ lpObj, LPOBJ lpTarget)
{
	if(!this->Enable)return true;
	if(!this->Started)return true;
	if(lpTarget->m_Index == this->ActivePlayer) return false;
	if(lpObj->m_Index == this->ActivePlayer) return false;
	return true;
}
bool cPandoraBoxEvent::BlockTeleport(int aIndex)
{
	if(!this->Enable)return true;
	if (!this->Started)return true;

	LPOBJ lpObj = &gObj[aIndex];
	if(this->ActivePlayer == lpObj->m_Index)
	{
		MessageChat(lpObj->m_Index,"~[Pandora Event]: Teleport Block");
		return false;
	}
	return true;
}

void cPandoraBoxEvent::CloseClient(int aIndex)
{
	if(!this->Enable)return;
	if (!this->Started)return;
	if ( aIndex < 0 || aIndex > OBJMAX-1)
	{
		return;
	}
	if (aIndex == this->ActivePlayer)
	{
		LPOBJ lpObj = &gObj[aIndex];
		lpObj->m_PK_Level = this->ActivePlayerPkLevel;

		CordsBox RandCord = Cords[rand()%this->CountCord];
		
		MessaageAllGlobal("[Pandora Event] Player Exit. Box Respawn Again.");	
		this->RespawnBox(RandCord);
		this->ActivePlayer = -1;
	}
}