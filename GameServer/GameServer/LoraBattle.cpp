#include "StdAfx.h"
#include "LoraBattle.h"
#include "user.h"
#include "Message.h"
#include "ExUser.h"
#include "Functions.h"
#include "DSProtocol.h"
#include "ExFunction.h"
#include "ExLicense.h"
#include "TimerEx.h"

cLoraBattle LoraBattle;

cLoraBattle::cLoraBattle()
{
	for(int i=OBJ_STARTUSERINDEX; i<OBJMAX; i++)
	{
		KillSocer[i] = 0;
		m_PK_Level[i] = 0;
	}

	Start = false;
	MaxSocer	 = 0;
}

cLoraBattle::~cLoraBattle()
{

}

void cLoraBattle::LoadConfigs()
{

	Enable = GetPrivateProfileInt("Common","Enable",1,LORABATTLE_DIR);
	
	if(!g_ExLicense.user.LoraBattle)
	{
		Enable = 0;
	}

	if(!Enable)
		return;
	//Configs
	GetPrivateProfileStringA("Common", "MGS","[Lora Battle] Start after 1 minute",MSG,sizeof(MSG),LORABATTLE_DIR);
	RewardItem = GetPrivateProfileInt("Reward","RewardItem",1,LORABATTLE_DIR);

	RewardWCoinC = GetPrivateProfileInt("Reward","RewardWCoinC",0,LORABATTLE_DIR);
	RewardWCoinP = GetPrivateProfileInt("Reward","RewardWCoinP",0,LORABATTLE_DIR);
	RewardGoblin = GetPrivateProfileInt("Reward","RewardGoblin",0,LORABATTLE_DIR);
	RewardExCred = GetPrivateProfileInt("Reward","RewardExCred",0,LORABATTLE_DIR);

	RewardItemDropType	= GetPrivateProfileInt("Reward","RewardItemDropType",12,LORABATTLE_DIR);
	RewardItemDropID		= GetPrivateProfileInt("Reward","RewardItemDropID",15,LORABATTLE_DIR);
	RewardItemDropLevel	= GetPrivateProfileInt("Reward","RewardItemDropLevel",0,LORABATTLE_DIR);
	RewardItemDropSkill	= GetPrivateProfileInt("Reward","RewardItemDropSkill",0,LORABATTLE_DIR);
	RewardItemDropLuck	= GetPrivateProfileInt("Reward","RewardItemDropLuck",0,LORABATTLE_DIR);
	RewardItemDropOpt	= GetPrivateProfileInt("Reward","RewardItemDropOpt",0,LORABATTLE_DIR);
	RewardItemDropExcOpt	= GetPrivateProfileInt("Reward","RewardItemDropExcOpt",0,LORABATTLE_DIR);
	RewardItemDropAncOpt	= GetPrivateProfileInt("Reward","RewardItemDropAncOpt",0,LORABATTLE_DIR);

	Fallen_DROP = GetPrivateProfileInt("Fallen","Fallen_DROP",1,LORABATTLE_DIR);

	FallenItemDropType	= GetPrivateProfileInt("Fallen","FallenItemDropType",12,LORABATTLE_DIR);
	FallenItemDropID		= GetPrivateProfileInt("Fallen","FallenItemDropID",15,LORABATTLE_DIR);
	FallenItemDropLevel	= GetPrivateProfileInt("Fallen","FallenItemDropLevel",0,LORABATTLE_DIR);
	FallenItemDropSkill	= GetPrivateProfileInt("Fallen","FallenItemDropSkill",0,LORABATTLE_DIR);
	FallenItemDropLuck	= GetPrivateProfileInt("Fallen","FallenItemDropLuck",0,LORABATTLE_DIR);
	FallenItemDropOpt	= GetPrivateProfileInt("Fallen","FallenItemDropOpt",0,LORABATTLE_DIR);
	FallenItemDropExcOpt	= GetPrivateProfileInt("Fallen","FallenItemDropExcOpt",0,LORABATTLE_DIR);
	FallenItemDropAncOpt	= GetPrivateProfileInt("Fallen","FallenItemDropAncOpt",0,LORABATTLE_DIR);


	//for(int i=OBJ_STARTUSERINDEX; i<OBJMAX; i++)
	//{
	//	KillSocer[i] = 0;
	//	m_PK_Level[i] = 0;
	//}

	//if(Start == false)
	//{
	//	Start = false;
	//	MaxSocer	 = 0;
	//}

	FILE *file = fopen(LORABATTLE_DIR,"r");

	if(file == NULL)
	{
		MessageBoxA(0,"LoraBattleEvent.ini Load Error","CRITICAL ERROR",0);
		//ExitProcess(1);
		this->Enable = 0;
		return;
	}

	char Buff[256];
	int Flag = 0;

	Count = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(Ex_IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			Time[Count].StrHour	= 0;
			Time[Count].StrMin	= 0;
			Time[Count].Hour	= 0;
			Time[Count].Min		= 0;
			Time[Count].EndHour	= 0;
			Time[Count].EndMin	= 0;

			int n[7];
			sscanf(Buff, "%d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5]);
			Time[Count].StrHour	= n[0];
			Time[Count].StrMin	= n[1];
			Time[Count].Hour	= n[2];
			Time[Count].Min		= n[3];;
			Time[Count].EndHour	= n[4];
			Time[Count].EndMin	= n[5];
			Count++;
		}
	}
	fclose(file);
}
void cLoraBattle::Start1min()
{
	MessaageAllGlobal("%s",MSG);
}

void cLoraBattle::StartEvent()
{
	for(int j=OBJ_STARTUSERINDEX; j<OBJMAX; j++)
	{
		LPOBJ lpObj = &gObj[j];
		m_PK_Level[j] = lpObj->m_PK_Level;
	}

	Start = true;
	MessaageAllGlobal("[Lora Battle] Event Started!");
}

void cLoraBattle::EndEvent()
{
	Start = false;
	for(int j=OBJ_STARTUSERINDEX; j<OBJMAX; j++)
	{
		//MaxSocer = KillSocer[j];
		if(KillSocer[j] > MaxSocer)
		{
			MaxSocer = KillSocer[j];
			MaxIndex = j;
		}
	}

	int TotalWin = 0;

	for(int l=OBJ_STARTUSERINDEX; l<OBJMAX; l++)
	{
		if(KillSocer[l] == 0)
			continue;

		if(MaxSocer == KillSocer[l])
		{
			LPOBJ lpObj = &gObj[l];
			if(lpObj->Connected == PLAYER_PLAYING)
			{
				TotalWin++;
			}
		}
	}

	if(TotalWin == 1)
	{
		for(int l=OBJ_STARTUSERINDEX; l<OBJMAX; l++)
		{
			if(KillSocer[l] == 0)
				continue;

			if(MaxSocer == KillSocer[l])
			{
				LPOBJ lpObj = &gObj[l];
				if(lpObj->Connected == PLAYER_PLAYING)
				{
					MessaageAllGlobal("[Lora Battle] Win %s !",lpObj->Name);
					Reward(l);
				}
			}
		}
	}
	else
	{
		MessaageAllGlobal("[Lora Battle] Total Win %d, No Reward!", TotalWin);
	}
	
 	MessaageAllGlobal("[Lora Battle] Event End!");

	for(int i=OBJ_STARTUSERINDEX; i<OBJMAX; i++)
	{
		LPOBJ lpObj = &gObj[i];
		KillSocer[i] = 0;
		
		
	}

	MaxSocer	 = 0;
}

void cLoraBattle::TickTime()
{
	if(!Enable) return;
	SYSTEMTIME time;
	GetLocalTime(&time);

#if(NEWTIMEREX)
	if(g_TimerEx.GetSecond() == 00)
#else
	if(time.wSecond == 00)
#endif
	{
		for(int i = 0; i < Count; i++)
		{
			if(Time[i].StrHour == time.wHour && Time[i].StrMin == time.wMinute)
			{

				Start1min();
			}

			else if(Time[i].Hour == time.wHour && Time[i].Min == time.wMinute)
			{

				StartEvent();
			}
			else if(Time[i].EndHour == time.wHour && Time[i].EndMin == time.wMinute)
			{

				EndEvent();
			}
		}
	}
}

void cLoraBattle::BattleKillSocer(int aIndex,int aIndex2)
{
	LPOBJ lpObj = &gObj[aIndex];	
	LPOBJ lpTargetObj = &gObj[aIndex2];	
	if(lpObj->MapNumber == 0 && lpObj->X >= 137 && lpObj->X <= 144 && lpObj->Y >= 124 && lpObj->Y <= 131)
	{
		KillSocer[aIndex]++;
		MsgNormal(aIndex,"[LoraBattle] Killed: %d",KillSocer[aIndex]);
		if(Fallen_DROP)
		{
			ItemSerialCreateSend(aIndex,lpObj->MapNumber,lpObj->X,lpObj->Y,ITEMGET(this->FallenItemDropType,this->FallenItemDropID),
					this->FallenItemDropLevel,0, this->FallenItemDropSkill,this->FallenItemDropLuck,
					this->FallenItemDropOpt,aIndex,this->FallenItemDropExcOpt,this->FallenItemDropAncOpt);	
		}
	}
}

void cLoraBattle::Reward(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];	
	if(this->RewardWCoinC > 0)
	{
			lpObj->GameShop.WCoinC += this->RewardWCoinC;
			gGameShop.GDSaveUserInfo(aIndex);
			MessageChat(aIndex,"~[WCoinC]: LoraBattle Event Reward : %d",this->RewardWCoinC);
	}

	if(this->RewardWCoinP > 0)
	{
			lpObj->GameShop.WCoinP += this->RewardWCoinP;
			gGameShop.GDSaveUserInfo(aIndex);
			MessageChat(aIndex,"~[WCoinP]: LoraBattle Event Reward: %d",this->RewardWCoinP);
	}

	if(this->RewardGoblin > 0)
	{
			lpObj->GameShop.GoblinPoint += this->RewardGoblin;
			gGameShop.GDSaveUserInfo(aIndex);
			MessageChat(aIndex,"~[Goblin]: LoraBattle Event Reward: %d",this->RewardGoblin);
	}

	if(this->RewardExCred > 0)
	{
			lpObj->ExCred += this->RewardExCred;
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
			ExUserDataSend(aIndex);
			MessageChat(aIndex,"~[Credit]: Online Bonus: %d",this->RewardExCred);
	}

	if(RewardItem)
	{
		ItemSerialCreateSend(aIndex,lpObj->MapNumber,lpObj->X,lpObj->Y,ITEMGET(this->RewardItemDropType,this->RewardItemDropID),
					this->RewardItemDropLevel,0, this->RewardItemDropSkill,this->RewardItemDropLuck,
					this->RewardItemDropOpt,aIndex,this->RewardItemDropExcOpt,this->RewardItemDropAncOpt);
	}

	
	ExFireCracker(aIndex,lpObj->X,lpObj->Y);
}
bool cLoraBattle::PkCheck(LPOBJ lpObj, LPOBJ lpTarget)
{
	if(!this->Enable)return true;
	if(!this->Start)return true;
	if(this->BattleRing[lpObj->m_Index] == true && this->BattleRing[lpTarget->m_Index] == true) return false;
	return true;
}
int cLoraBattle::ReturnStatus(int aIndex, int TargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[TargetIndex];
	if(lpTargetObj->MapNumber == 0 && lpTargetObj->X >= 137 && lpTargetObj->X <= 144 && lpTargetObj->Y >= 124 && lpTargetObj->Y <= 131)
	{
		return 6;
	}
	else if(lpObj->MapNumber == 0 && lpObj->X >= 137 && lpObj->X <= 144 && lpObj->Y >= 124 && lpObj->Y <= 131)
	{
		return 6;
	}
	/*
	if(lpTargetObj->MapNumber == 0 && lpTargetObj->X >= 118 && lpTargetObj->X <= 153 && lpTargetObj->Y >= 110 && lpTargetObj->Y <= 150)
	{
		return 6;
	}
	else if(lpObj->MapNumber == 0 && lpObj->X >= 118 && lpObj->X <= 153 && lpObj->Y >= 110 && lpObj->Y <= 150)
	{
		return 6;
	}
	*/
	else
	{
		return (int)lpTargetObj->m_PK_Level;
	}

}
bool cLoraBattle::CheckStartEvent()
{
	if(!this->Enable || !this->Start)return false;
	return true;
}
