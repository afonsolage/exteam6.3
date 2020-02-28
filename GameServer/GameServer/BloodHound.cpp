#include "StdAfx.h"

#ifdef BloodHoundEvent

#include "USER.h"
//#include "Defines.h"
//#include "Item.h"
#include "BloodHound.h"
#include "Message.h"
#include "user.h"
#include "Functions.h"
#include "ExFunction.h"
//#include "Utilits.h"
#include "DSProtocol.h"
#include "ExLicense.h"
#include "TimerEx.h"

cBloodHound BloodHound;

void cBloodHound::ReedConfig()
{
	for (int i=0;i<MAX_ITEMS_BH;i++)
	{
		sTime[i].Hour = 0;
		sTime[i].Minute = 0;

		sItem[i].Type = 0;
		sItem[i].Index = 0;
		sItem[i].Level = 0;
		sItem[i].Count = 0;

		iReward[i].Type = 0;
		iReward[i].Index = 0;
		iReward[i].Level = 0;
		iReward[i].Skill = 0;
		iReward[i].Luck = 0;
		iReward[i].Opt = 0;
		iReward[i].Exl = 0;
		iReward[i].Anc = 0;
	}

	this->Enable = 0;

	if(!g_ExLicense.user.BloodHound)
	{
		return;
	}

	this->Enable = GetPrivateProfileInt("Common","Enable",0,BLOODHOND_DIR);
	this->NPC = GetPrivateProfileInt("Common","NPC",0,BLOODHOND_DIR);
	this->NPC_Map = GetPrivateProfileInt("Common","NPC_Map",0,BLOODHOND_DIR);
	this->NPC_X = GetPrivateProfileInt("Common","NPC_X",0,BLOODHOND_DIR);
	this->NPC_Y = GetPrivateProfileInt("Common","NPC_Y",0,BLOODHOND_DIR);

	this->EventTime = GetPrivateProfileInt("Common","EventTime",0,BLOODHOND_DIR);

	this->StartEvent = false;

	FILE *file;
	file = fopen(BLOODHOND_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,BLOODHOND_DIR,"LOAD FILE ERROR",0);
		//ExitProcess(1);
		return;
	}
	char Buff[256];
	int Flag = 0;

	this->tCount = 0;
	this->sCount = 0;
	this->rCount = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(Ex_IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			int n[3];
			sscanf(Buff,"%d %d",&n[0],&n[1]);
			this->sTime[this->tCount].Hour = n[0];
			this->sTime[this->tCount].Minute = n[1];
			this->tCount++;
		}
		if(Flag == 2)
		{
			int n[5];
			char ItemName[50];
			sscanf(Buff,"%d %d %d %d \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&ItemName);
			this->sItem[this->sCount].Type  = n[0];
			this->sItem[this->sCount].Index = n[1];
			this->sItem[this->sCount].Level = n[2];
			this->sItem[this->sCount].Count  = n[3];
			sprintf(this->sItem[this->sCount].Name,"%s",ItemName);
			this->sCount++;
		}
		if(Flag == 3)
		{
			int n[8];
			sscanf(Buff,"%d %d %d %d %d %d %d %d",&n[0],&n[1],&n[2],&n[3],&n[4],&n[5],&n[6],&n[7]);
			this->iReward[this->rCount].Type= n[0];
			this->iReward[this->rCount].Index = n[1];
			this->iReward[this->rCount].Level = n[2];
			this->iReward[this->rCount].Skill = n[3];
			this->iReward[this->rCount].Luck = n[4];
			this->iReward[this->rCount].Opt = n[5];
			this->iReward[this->rCount].Exl = n[6];
			this->iReward[this->rCount].Anc = n[7];
			this->rCount++;
		}
	}
	fclose(file);
}

void cBloodHound::UserStart(int aIndex)
{
	this->UserCheck[aIndex] = false;
	this->UserEvent[aIndex] = false;
	this->iUserType[aIndex] = -1;
	this->iUserIndex[aIndex] = -1;
	this->iUserLevel[aIndex] = -1;
	this->iUserCount[aIndex] = -1;
	this->iUserName[aIndex][0] = NULL;
}

void cBloodHound::NPCClick(int aIndex,int aNPC)
{
	if(!this->Enable)	return;
	if(!this->StartEvent)	return;
	if(!this->UserCheck[aIndex]) return;

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNPC];
	if ((lpNpc->Class == this->NPC) && (lpNpc->MapNumber == this->NPC_Map) && (lpNpc->X == this->NPC_X) && (lpNpc->Y == this->NPC_Y))
	{
		if(this->UserEvent[aIndex] == false)
		{
			this->TakeJob(aIndex);
		}
		else
		{
			this->RunJob(aIndex);
		}
	}
}

void cBloodHound::TakeJob(int aIndex)
{
	//OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	srand(time(NULL));
	int n = rand()%this->sCount;
	
	this->UserEvent[aIndex] = true;
	this->iUserType[aIndex] = this->sItem[n].Type;
	this->iUserIndex[aIndex] = this->sItem[n].Index;
	this->iUserLevel[aIndex] = this->sItem[n].Level;
	this->iUserCount[aIndex] = this->sItem[n].Count;
	strcpy(this->iUserName[aIndex],this->sItem[n].Name);

	MessageChat(aIndex,"[BloodHound] Need: %s+%d Count: %d",this->sItem[n].Name,this->sItem[n].Level,this->sItem[n].Count);
}
void cBloodHound::RunJob(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	int NeedType = this->iUserType[aIndex];
	int NeedIndex = this->iUserIndex[aIndex];
	int NeedLevel = this->iUserLevel[aIndex];
	int NeedCount = this->iUserCount[aIndex];

	if(gObjGetItemCountInInventory(aIndex,ITEMGET(NeedType,NeedIndex),NeedLevel) < NeedCount)
	{
		if(this->iUserLevel[aIndex] == 0)
			MessageChat(aIndex,"[BloodHound] Need: %s Count: %d",this->iUserName[aIndex],this->iUserCount[aIndex]);
		else
			MessageChat(aIndex,"[BloodHound] Need: %s+%d Count: %d",this->iUserName[aIndex],this->iUserLevel[aIndex],this->iUserCount[aIndex]);
		return;
	}

	gObjDeleteItemsCount(aIndex,ITEMGET(NeedType,NeedIndex),NeedLevel,NeedCount);

	srand(time(NULL));
	int n = rand()%this->rCount;

	int Type = ITEMGET(iReward[n].Type,iReward[n].Index);
	int iLevel = iReward[n].Level;
	int iSkill	= iReward[n].Skill;
	int iLuck	= iReward[n].Luck;
	int iOpt = iReward[n].Opt;
	int iExe	= GenExcOpt(iReward[n].Exl);
	int iAnc	= 0;

	if(iReward[n].Anc == 5 || iReward[n].Anc == 10)
	{
		iAnc = iReward[n].Anc;
	}

	ItemSerialCreateSend(aIndex,lpUser->MapNumber,lpUser->X,lpUser->Y,Type,iLevel,0,iSkill,iLuck,iOpt,aIndex,iExe,iAnc);

	this->UserEvent[aIndex] = false;
	this->iUserType[aIndex] = -1;
	this->iUserIndex[aIndex] = -1;
	this->iUserLevel[aIndex] = -1;
	this->iUserCount[aIndex] = -1;
	this->iUserName[aIndex][0] = NULL;
}

void cBloodHound::Times()
{
	if(!this->Enable)
		return;

	if(this->StartEvent == true)
	{
		this->TickEvent++;
		if(this->TickEvent >= this->EventTime)
		{
			this->StartEvent = false;
			this->TickEvent = 0;
			for(int i=OBJ_MAXMONSTER; i<OBJMAX; i++)
			{
				this->UserCheck[i] = false;
				this->UserEvent[i] = false;
				this->iUserType[i] = -1;
				this->iUserIndex[i] = -1;
				this->iUserLevel[i] = -1;
				this->iUserCount[i] = -1;
				this->iUserName[i][0] = NULL;
			}
			
			MessaageAllGlobal("[BloodHound] End!");
		}
		return;
	}

	SYSTEMTIME t;
	GetLocalTime(&t);

#if(NEWTIMEREX)
	if(g_TimerEx.GetSecond() == 00)
#else
	if(t.wSecond == 00)
#endif
	{
		for(int i = 0; i < this->tCount; i++)
		{
			if(this->sTime[i].Hour == t.wHour && this->sTime[i].Minute == t.wMinute)
			{
				this->StartEvent = true;
				for(int i=OBJ_MAXMONSTER; i<OBJMAX; i++)
				{
					LPOBJ lpUser = &gObj[i];
					if(gObj->Connected != PLAYER_PLAYING)
						continue;
					this->UserCheck[i] = true;
				}
				MessaageAllGlobal("[BloodHound] Start!");

				return;
			}
		}
	}
}

#endif