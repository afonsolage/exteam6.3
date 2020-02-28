#include "StdAfx.h"
#include "GameMain.h"
#include "MonsterTime.h"
#include "logproc.h"
#include "..\\include\\ReadScript.h"
#include "MapServerManager.h"
#include "TimerEx.h"
#include "ExFunction.h"
#include "ExLicense.h"
#include "BossRewardItem.h"

#if(DEV_MONSTERTIME)

CMonsterTime g_MonsterTime;

CMonsterTime::CMonsterTime()
{
	this->Init();
}

CMonsterTime::~CMonsterTime()
{
}

void CMonsterTime::Init()
{
	this->m_Enable = 0;
	this->m_LoadCount = 0;
	this->m_LoadPos = 0;

	this->m_Loaded = 0;

	memset(this->m_Info, 0, sizeof(this->m_Info));
	memset(this->m_Data, -1, sizeof(this->m_Data));
}

void CMonsterTime::Load()
{
	if(this->m_Loaded)
	{
		return;
	}

	this->m_LoadCount = 0;

	this->m_Loaded = 0;

	memset(this->m_Info, 0, sizeof(this->m_Info));

	this->Read(gDirPath.GetNewPath("ExData\\MonsterTime.ini"));
}

void CMonsterTime::Read(char* filename)
{
	SMDFile = fopen(filename, "r");

	if(SMDFile == NULL)
	{
		LogAdd(lMsg.Get(MSGGET(1, 198)), filename);
		return;
	}

	SMDToken Token;

	int iType = -1;

	while(true)
	{
		Token = GetToken();

        if(Token == END)
		{
            break;
		}

		iType = (int)TokenNumber;

		if(iType < 0 || iType > 1)
		{
			break;
		}

		while(true)
		{
			if(iType == 0)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				this->m_Enable = (int)TokenNumber;
			}
			else if(iType == 1)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				this->m_Info[this->m_LoadCount].Class = TokenNumber;

				Token = GetToken();
				this->m_Info[this->m_LoadCount].MapNumber = TokenNumber;

				Token = GetToken();
				this->m_Info[this->m_LoadCount].MapX = TokenNumber;

				Token = GetToken();
				this->m_Info[this->m_LoadCount].MapY = TokenNumber;

				Token = GetToken();
				this->m_Info[this->m_LoadCount].Day = TokenNumber;

				Token = GetToken();
				this->m_Info[this->m_LoadCount].Hour = TokenNumber;

				Token = GetToken();
				this->m_Info[this->m_LoadCount].Minute = TokenNumber;

				this->m_LoadCount++;
			}
		}
	}

	fclose(SMDFile);

	LogAdd("%s file load!", filename);

	this->m_Loaded = 1;
}

void CMonsterTime::Run()
{
	if(!this->m_Enable)
	{
		return;
	}

	SYSTEMTIME systime;
	GetLocalTime(&systime);

	for(int i = 0; i < this->m_LoadCount; i++)
	{
		if(g_TimerEx.GetSecond() == 0)
		{
			if(this->m_Info[i].Day == -1 || this->m_Info[i].Day == systime.wDay)
			{
				if(this->m_Info[i].Hour == systime.wHour && this->m_Info[i].Minute == systime.wMinute)
				{
					if(this->m_Data[i].Index == -1)
					{
						this->AddMonster(i, this->m_Info[i].MapNumber);
					}
				}		
			}
		}
	}
}

void CMonsterTime::LoadMonsterPos()
{
	if(!this->m_Enable)
	{
		return;
	}

	for(int i = 0; i < this->m_LoadCount; i++)
	{
		if(this->m_Data[i].Index == -1)
		{
			int iPos = this->GetMonsterPos(this->m_Info[i].Class, this->m_Info[i].MapNumber, this->m_Info[i].MapX, this->m_Info[i].MapY);

			if(iPos >= 0)
			{
				this->m_Data[i].Class = this->m_Info[i].Class;
				this->m_Data[i].Index = -1;
				this->m_Data[i].Pos = iPos;
			}
		}
	}

	this->m_LoadPos = true;
}

int CMonsterTime::GetMonsterPos(WORD Type, BYTE Map, BYTE X, BYTE Y)
{
	if(gMSetBase.m_Count >= OBJ_MAXMONSTER-1)
	{
		MsgBox("Monster attribute max over %s %d", __FILE__, __LINE__);
		return -1;
	}

	if(g_MapServerManager.CheckMapCanMove(Map) == FALSE)
	{
		LogAddC(3,"[AttackerAdd] No need to load monster for map %d [%d,%d,%d]",Map,Type,X,Y);
		return -1;
	}

	gMSetBase.m_Count++;
	gMSetBase.m_Mp[gMSetBase.m_Count].m_Dis			= 5;
	gMSetBase.m_Mp[gMSetBase.m_Count].m_Type		= Type;
	gMSetBase.m_Mp[gMSetBase.m_Count].m_MapNumber	= Map;
	gMSetBase.m_Mp[gMSetBase.m_Count].m_W			= X;
	gMSetBase.m_Mp[gMSetBase.m_Count].m_H			= Y;
	gMSetBase.m_Mp[gMSetBase.m_Count].m_X			= X;
	gMSetBase.m_Mp[gMSetBase.m_Count].m_Y			= Y;
	gMSetBase.m_Mp[gMSetBase.m_Count].m_ArrangeType = 0;
	gMSetBase.m_Mp[gMSetBase.m_Count].m_Dir			= rand() % 8;

	return gMSetBase.m_Count;
}

void CMonsterTime::AddMonster(int Num, int Map)
{
	int iMobIndex = gObjAddMonster(Map);

	if(iMobIndex < 0 || iMobIndex > OBJ_MAXMONSTER)
	{
		return;
	}

	this->m_Data[Num].Index = iMobIndex;

	gObjSetPosMonster(this->m_Data[Num].Index, this->m_Data[Num].Pos);
	gObjSetMonster(this->m_Data[Num].Index, this->m_Data[Num].Class);

	LPMONSTER_ATTRIBUTE lpMonsterAttr = gMAttr.GetAttr(this->m_Data[Num].Class);

	char szMsg[128];
	sprintf(szMsg, "Attack %s in %s", lpMonsterAttr->m_Name, exMapName(Map));
	AllSendServerMsg(szMsg);
}

void CMonsterTime::DieMonster(int aIndex, int aMonsterIndex)
{
	if(!this->m_Enable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(aMonsterIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpMonster = &gObj[aMonsterIndex];

	for(int i = 0; i < MAX_MONSTERTIME; i++)
	{
		if(aMonsterIndex == this->m_Data[i].Index)
		{
			LPMONSTER_ATTRIBUTE lpMonsterAttr = gMAttr.GetAttr(lpMonster->Class);

			char szMsg[128];
			sprintf(szMsg, "%s killed %s in %s", lpMonsterAttr->m_Name, lpUser->Name, exMapName(lpMonster->MapNumber));
			AllSendServerMsg(szMsg);

#ifdef BOSS_REWARD_ITEM
			if(gBossRewardItem.ProccessItemDrop(lpMonster))
				return;
#endif
			gObjDel(this->m_Data[i].Index);
			this->m_Data[i].Index = -1;
			
			return;
		}
	}
}

void CMonsterTime::ReloadMonster()
{
	//if(!this->m_Enable)
	//{
	//	return;
	//}

	//for(int i = 0; i < MAX_MONSTERTIME; i++)
	//{
	//	if(this->m_Data[i].Index == -1)
	//	{
	//		continue;
	//	}

	//	this->AddMonster(i, false);
	//}
}

#endif