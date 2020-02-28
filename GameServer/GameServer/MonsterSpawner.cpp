#include "StdAfx.h"
#include "MonsterSpawner.h"
#include "Functions.h"
#include "user.h"
#include "ExFunction.h"
#include "Message.h"
#include "ExLicense.h"

cMonsterSpawner gMonsterSpawner;

void cMonsterSpawner::Load()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,MONSTER_SPAWNER_DIR);
	

	FILE * file = fopen(MONSTER_SPAWNER_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,MONSTER_SPAWNER_DIR,"LOAD FILE ERROR",0);
		this->Enable = false;
	}

	char Buff[256];
	int Flag = 0;
	this->CountMobs = 0;
	for (int i = 0; i < MAX_MONSTER_SPAWNER; i++)
	{
		this->MonsterSpawn[i].ID = 0;
		this->MonsterSpawn[i].MapNumber = 0;
		this->MonsterSpawn[i].X = 0;
		this->MonsterSpawn[i].Y = 0;
		this->MonsterSpawn[i].WeekDay = 0;
		this->MonsterSpawn[i].TimeHour = 0;
		this->MonsterSpawn[i].TimeMin = 0;
		this->MonsterSpawn[i].Status = false;
	}
	while(!feof(file))
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;
		if(Flag == 1)
		{
			if(this->CountMobs == MAX_MONSTER_SPAWNER) break;
			int n[8];
			char str[100];
			sscanf(Buff, "%d %d %d %d %d %d %d \"%[^\"]\"", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &str);
			this->MonsterSpawn[this->CountMobs].ID = n[0];
			this->MonsterSpawn[this->CountMobs].MapNumber = n[1];
			this->MonsterSpawn[this->CountMobs].X = n[2];
			this->MonsterSpawn[this->CountMobs].Y = n[3];
			this->MonsterSpawn[this->CountMobs].WeekDay = n[4];
			this->MonsterSpawn[this->CountMobs].TimeHour = n[5];
			this->MonsterSpawn[this->CountMobs].TimeMin = n[6];
			strcpy(MonsterSpawn[this->CountMobs].Message,str);
			this->CountMobs++;
		}
	}
	fclose(file);
}

bool cMonsterSpawner::StartMonster(int Index)
{
	if (!this->Enable) return false;

	int result = gObjAddMonster(this->MonsterSpawn[Index].MapNumber);

	if((result >= 0 && result < OBJ_MAXMONSTER) && MonsterSpawn[Index].Status == false)
	{
		int iX = this->MonsterSpawn[Index].X;
		int iY = this->MonsterSpawn[Index].Y;

		if(g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ulasevich2))
		{
			iX = iX + (rand() % 80 - 40);
			iY = iY + (rand() % 80 - 40);
		}

		if(iX > 254)
		{
			iX = 254;
		}
		if(iY > 254)
		{
			iY = 254;
		}
		if(iX < 1)
		{
			iX = 1;
		}
		if(iY < 1)
		{
			iY = 1;
		}

		gObj[result].m_PosNum = (WORD)-1;
		gObj[result].MapNumber = this->MonsterSpawn[Index].MapNumber;
		gObj[result].X = iX;
		gObj[result].Y = iY;
		gObj[result].TX = iX;
		gObj[result].TY = iY;
		gObj[result].m_OldX = iX;
		gObj[result].m_OldY = iY;
		gObj[result].StartX = iX;
		gObj[result].StartY = iY;
		gObj[result].MaxRegenTime = 0;
		gObj[result].Dir = rand()%8;
		gObj[result].RegenTime = GetTickCount();

		gObj[result].m_ActState.Emotion       = 1;
		gObj[result].m_ActState.EmotionCount  = 15;

		gObjSetMonster(result,this->MonsterSpawn[Index].ID);
		MessaageAllGlobal(this->MonsterSpawn[Index].Message);
		MonsterSpawn[Index].Status = true;
		MonsterSpawn[Index].Index = result;
		return true;

	}
	else
	{
		return false;
	}
}
void cMonsterSpawner::KillMob(LPOBJ lpMobObj)
{
	int i;
	for (i = 0; i < this->CountMobs; i++)
	{
		if (MonsterSpawn[i].Status)
			if (MonsterSpawn[i].Index == lpMobObj->m_Index)
			{	
				MessaageAllGlobal("%s Kill in %s",lpMobObj->Name, exMapName(lpMobObj->MapNumber));
				MonsterSpawn[i].Status = false;
			}
	}
}

void cMonsterSpawner::TickTime()
{
	if (!this->Enable) return;
	SYSTEMTIME t;
	GetLocalTime(&t);
	int i;
	for (i = 0; i < this->CountMobs; i++)
	{
		if (this->MonsterSpawn[i].WeekDay == -1)
		{
			if(t.wHour == this->MonsterSpawn[i].TimeHour && t.wMinute == this->MonsterSpawn[i].TimeMin && t.wSecond == 00)
			{
				this->StartMonster(i);
			}
		}
		else
		{
			if(t.wDayOfWeek == this->MonsterSpawn[i].WeekDay && t.wHour == this->MonsterSpawn[i].TimeHour && t.wMinute == this->MonsterSpawn[i].TimeMin && t.wSecond == 00)
			{
				this->StartMonster(i);
			}
		}

	}
			
}

