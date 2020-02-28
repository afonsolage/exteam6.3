#include "StdAfx.h"
#include "PandoraBoxEvent.h"

#include "Functions.h"
#include "Message.h"
#include "DSProtocol.h"
#include "ExUser.h"
#include "ExFunction.h"
#include "TimerEx.h"
#include "ExLicense.h"

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
	this->Enable = GetPrivateProfileInt("ExTeam","Enable",0,PANDORA_EVENT_DIR);
	if (!this->Enable)
	{
		return;
	}
	
	this->EventTime = GetPrivateProfileInt("ExTeam","EventTime",10,PANDORA_EVENT_DIR);
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
		}
		else
		{
			this->End();
		}
	}
#if(NEWTIMEREX)
	else if(g_TimerEx.GetSecond() == 00)
#else
	else if(time.wSecond == 00)
#endif
	{
		for(int i = 0; i < this->CountTimes; i++)
		{
			if(Times[i].Hour == time.wHour && Times[i].Min == time.wMinute)
			{
				this->Start();
				break;
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
	 this->Prize();
	 this->Started = false;
	 LPOBJ lpObj = &gObj[this->ActivePlayer];
	 gObjDel(this->BoxIndex);
	 this->BoxIndex = -1;
	 lpObj->m_Change = -1;
	 lpObj->m_PK_Level = this->ActivePlayerPkLevel;
	 gObjViewportListProtocolCreate(lpObj);
	 this->ActivePlayer = -1;
	 MessaageAllGlobal("[Pandora Event] End Win %s", lpObj->Name);
}

void cPandoraBoxEvent::RespawnBox(CordsBox RandCord)
{
	if (!this->Enable) return;

	this->ActiveMap = RandCord.Map;

	
#ifdef RANDOM_BOX_CORD_PANDORA
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
		gObj[result].m_PosNum = (WORD)-1;
		gObj[result].MapNumber = this->ActiveMap;
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
	MessaageAllGlobal("[Pandora Event] Map: %s X: %d Y: %d", exMapName(lpObj->MapNumber), lpObj->X, lpObj->Y);
	gObjDel(this->BoxIndex);
	this->BoxIndex = -1;

	return true;
}
void cPandoraBoxEvent::Player(LPOBJ lpObj)
{
	
	if (this->ActivePlayer != -1)
	{
		LPOBJ lpOldObj = &gObj[this->ActivePlayer];
		/*
			Меняем обратно
		*/
		lpOldObj->m_Change = -1;
		lpOldObj->m_PK_Level = this->ActivePlayerPkLevel;
		gObjViewportListProtocolCreate(lpOldObj);
	}

	this->ActivePlayerPkLevel = lpObj->m_PK_Level;
	lpObj->m_PK_Level = 6;
	lpObj->m_Change = 404;
	gObjViewportListProtocolCreate(lpObj);

	this->ActivePlayer = lpObj->m_Index;
	/*
		Меняем вид персонажа
	*/
}
bool cPandoraBoxEvent::ProcessKill(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if(!this->Enable)return false;
	if(!this->Started)return false;
	if (lpTargetObj->m_Index != this->ActivePlayer)
	{
		return false;
	}
	this->Player(lpObj);

	//MessaageAllGlobal("[Pandora Event] %s Capture Box in Map: %s X: %d Y: %d", lpObj->Name, exMapName(lpObj->MapNumber), lpObj->X, lpObj->Y);	
	MessaageAllGlobal("[Pandora Event] %s Capture Box", lpObj->Name);	
	MessaageAllGlobal("[Pandora Event] Map: %s X: %d Y: %d", exMapName(lpObj->MapNumber), lpObj->X, lpObj->Y);

	return true;
}
void cPandoraBoxEvent::Prize()
{
	if(!this->Enable)return;
	if(!this->Started)return;
	if (this->ActivePlayer == -1) return;

	LPOBJ lpObj = &gObj[this->ActivePlayer];
	
	if(this->CountReward > 0)
	{
		int Ran = rand()%this->CountReward;

		int NewExl = 0;
		int NewAnc = 0;

		int DropItem = ITEMGET(this->Reward[Ran].Type,this->Reward[Ran].Index);

		if(Reward[Ran].Exl > 0)
			NewExl = GenExcOpt(Reward[Ran].Exl);

		if(Reward[Ran].Anc == 5 || Reward[Ran].Anc == 10)
			NewAnc = Reward[Ran].Anc;

		ItemSerialCreateSend(lpObj->m_Index,lpObj->MapNumber,lpObj->X,lpObj->Y,DropItem,this->Reward[Ran].Level,0,
			this->Reward[Ran].Skill,this->Reward[Ran].Luck,this->Reward[Ran].Opt,lpObj->m_Index,NewExl,NewAnc);
		
	}

	if(this->RewardWcoinC > 0)
	{
			lpObj->GameShop.WCoinC += this->RewardWcoinC;
			gGameShop.GDSaveUserInfo(lpObj->m_Index);
			MessageChat(lpObj->m_Index,"~[Pandora Event]: Reward : %d WCoinC",this->RewardWcoinC);
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