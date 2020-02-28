#include "StdAfx.h"
#include "MapQuest.h"
#include "GameMain.h"
#include "..\\include\\Readscript.h"
#include "user.h"
#include "logproc.h"
#include "ExLicense.h"
#include "ExFunction.h"
#include "MapServerManager.h"

#if(CUSTOM_MAPQUEST)

CMapQuest g_MapQuest;

CMapQuest::CMapQuest()
{
	this->m_Data.clear();
	memset(this->m_MapKillCount, 0, sizeof(this->m_MapKillCount));
	memset(this->m_BossStart, 0, sizeof(this->m_BossStart));

	for(int m = 0; m < MAX_NUMBER_MAP; m++)
	{
		this->m_Boss[m].sPos = -1;
		this->m_Boss[m].sIndex = -1;

		for(int i = 0; i < 100; i++)
		{
			this->m_Monster[m][i].sPos = -1;
			this->m_Monster[m][i].sIndex = -1;
		}
	}
}

CMapQuest::~CMapQuest()
{
}

void CMapQuest::Load()
{
	if(!g_ExLicense.user.MapQuest)
	{
		return;
	}



	this->m_Data.clear();
	this->Read(gDirPath.GetNewPath("ExData\\MapQuest.ini"));
}

void CMapQuest::Read(char* filename)
{
	int Token;

	SMDFile = fopen(filename, "r");

	if( SMDFile == NULL )
	{
		MsgBox(lMsg.Get(MSGGET(0, 112)), filename);
		return;
	}

	while(true) 
	{
		Token = GetToken();

		if( Token == END)
		{
			break;
		}

		if( Token != NUMBER )
		{
			continue;
		}

		MAPQUEST_DATA list;
		
		list.MapNum = TokenNumber;

		Token = GetToken();
		list.MonsterCount = TokenNumber;

		Token = GetToken();
		list.BossClass = TokenNumber;

		Token = GetToken();
		list.BossX = TokenNumber;

		Token = GetToken();
		list.BossY = TokenNumber;

		Token = GetToken();
		list.OrcClass = TokenNumber;

		Token = GetToken();
		list.OrcCount = TokenNumber;

		this->m_Data.push_back(list);
	}

	fclose(SMDFile);	

	LogAddTD("[MapQuest] [%d] Quest loaded from list", this->m_Data.size());
}

void CMapQuest::MonsterKill(int aIndex, int aTargetIndex)
{
	if(!g_ExLicense.user.MapQuest)
	{
		return;
	}

	if ( !OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(aTargetIndex) )
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpMonster = &gObj[aTargetIndex];

	if ( MAX_MAP_RANGE(lpMonster->MapNumber) == FALSE ) 
	{
		return;
	}

	for( int i = 0; i < this->m_Data.size(); i++ )
	{
		MAPQUEST_DATA & quest = this->m_Data[i];

		if(lpMonster->MapNumber == quest.MapNum)
		{
			if(this->m_BossStart[lpMonster->MapNumber] == true)
			{
				if(lpMonster->Class == quest.BossClass)
				{
					this->m_BossStart[lpMonster->MapNumber] = false;
					this->m_MapKillCount[lpMonster->MapNumber] = 0;
					this->GCInfo(aIndex, true, this->m_MapKillCount[lpMonster->MapNumber], quest.MonsterCount);

					this->DelMonsterMap(lpMonster->MapNumber);
				}	
				else if(lpMonster->Class == quest.OrcClass)
				{
					this->DelMonster(aTargetIndex, lpMonster->MapNumber);
				}					
			}
			else 
			{
				this->m_MapKillCount[lpMonster->MapNumber]++;		
				if(this->m_MapKillCount[lpMonster->MapNumber] >= quest.MonsterCount)
				{
					this->AddBossEx(lpMonster->MapNumber, quest.BossClass, quest.BossX, quest.BossY, quest.OrcClass, quest.OrcCount);	
					//this->m_MapKillCount[lpMonster->MapNumber] = 0;
				}
				this->GCInfo(aIndex, true, this->m_MapKillCount[lpMonster->MapNumber], quest.MonsterCount);
			}
		}
	}
}

void CMapQuest::AddBoss(int Map, int BossClass, int BossX, int BossY, int OrcClass, int OrcCount)
{
	short BossIndex = gObjAddMonster(Map);

	if(!OBJMAX_RANGE(BossIndex))
	{
		return;
	}

	gObj[BossIndex].m_PosNum = (WORD)-1;
	gObj[BossIndex].MapNumber = Map;
	gObj[BossIndex].Dir = rand()%8;
	gObj[BossIndex].X = BossX;
	gObj[BossIndex].Y = BossY;
	gObj[BossIndex].TX = BossX;
	gObj[BossIndex].TY = BossY;
	gObj[BossIndex].m_OldX = BossX;
	gObj[BossIndex].m_OldY = BossY;
	gObj[BossIndex].StartX = BossX;
	gObj[BossIndex].StartY = BossY;
	gObj[BossIndex].MaxRegenTime = 0;
	gObj[BossIndex].Dir = rand()%8;
	gObj[BossIndex].RegenTime = GetTickCount();
	gObj[BossIndex].m_ActState.Emotion = 1;
	gObj[BossIndex].m_ActState.EmotionCount = 15;

	gObjSetMonster(BossIndex, BossClass);

	char szMsg[128];
	sprintf(szMsg,"[Map Quest] Boss %s in %s map", gObj[BossIndex].Name, exMapName(gObj[BossIndex].MapNumber));
	AllSendServerMsg(szMsg);

	this->m_BossStart[Map] = true;

	short X = BossX;
	short Y = BossY;

	for(int i = 0; i < OrcCount; i++)
	{
		int OrcIndex = gObjAddMonster(Map);

		if(!OBJMAX_RANGE(OrcIndex))
		{
			continue;
		}

		gMSetBase.GetBoxPosition(Map, (BossX - 5), (BossY - 5), (BossX + 5), (BossY + 5), X, Y);

		gObj[OrcIndex].m_PosNum = (WORD)-1;
		gObj[OrcIndex].MapNumber = Map;
		gObj[OrcIndex].Dir = rand()%8;
		gObj[OrcIndex].X = X;
		gObj[OrcIndex].Y = Y;
		gObj[OrcIndex].TX = X;
		gObj[OrcIndex].TY = Y;
		gObj[OrcIndex].m_OldX = X;
		gObj[OrcIndex].m_OldY = Y;
		gObj[OrcIndex].StartX = X;
		gObj[OrcIndex].StartY = Y;
		gObj[OrcIndex].MaxRegenTime = 0;
		gObj[OrcIndex].Dir = rand()%8;
		gObj[OrcIndex].RegenTime = GetTickCount();
		gObj[OrcIndex].m_ActState.Emotion = 1;
		gObj[OrcIndex].m_ActState.EmotionCount = 15;

		gObjSetMonster(OrcIndex, OrcClass);
	}
}

void CMapQuest::GCInfo(int aIndex, bool Show, int Count, int MaxCount)
{
	PMSG_DUNGEON_SYSTEM pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x71, sizeof(pMsg));
	pMsg.Show = Show;
	pMsg.Count = Count;
	pMsg.MaxCount = MaxCount;
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void CMapQuest::ReloadMonster()
{
	if(!g_ExLicense.user.MapQuest)
	{
		return;
	}

	//memset(this->m_BossStart, 0, sizeof(this->m_BossStart));
	//memset(this->m_MapKillCount, 0, sizeof(this->m_MapKillCount));

	for(int i = 0; i < this->m_Data.size(); i++)
	{
		MAPQUEST_DATA & quest = this->m_Data[i];

		int iMap = quest.MapNum;

		if(!MAX_MAP_RANGE(iMap))
		{
			continue;
		}

		if(this->m_BossStart[iMap] == true)
		{
			if(this->m_MapKillCount[iMap] >= quest.MonsterCount)
			{
				this->AddBossEx(iMap, quest.BossClass, quest.BossX, quest.BossY, quest.OrcClass, quest.OrcCount);	

			//	this->GCInfo(aIndex, true, this->m_MapKillCount[lpMonster->MapNumber], quest.MonsterCount);
			}
		}
	}


}

void CMapQuest::TeleportMap(int aIndex, int Map)
{
	if(!g_ExLicense.user.MapQuest)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex) || !MAX_MAP_RANGE(Map))
	{
		return;
	}

	bool Result = false;
	int MaxCount = 0;

	for(int i = 0; i < this->m_Data.size(); i++)
	{
		MAPQUEST_DATA & quest = this->m_Data[i];

		if(Map == quest.MapNum)
		{
			Result = true;
			MaxCount = quest.MonsterCount;
			break;
		}
	}

	this->GCInfo(aIndex, Result, this->m_MapKillCount[Map], MaxCount);
}

void CMapQuest::LoadMonsterPos()
{
	for( int n = 0; n < this->m_Data.size(); n++ )
	{
		MAPQUEST_DATA & quest = this->m_Data[n];

		if ( MAX_MAP_RANGE(quest.MapNum) == FALSE ) 
		{
			continue;
		}

		int iMobPos = this->GetMonsterPos(quest.BossClass, quest.MapNum, 0, 0);

		this->m_Boss[quest.MapNum].sIndex = -1;
		this->m_Boss[quest.MapNum].sPos = iMobPos;

		if(iMobPos >= 0)
		{
			for(int i = 0; i < quest.OrcCount; i++)
			{
				iMobPos = this->GetMonsterPos(quest.OrcClass, quest.MapNum, 0, 0);

				if(iMobPos >= 0)
				{
					this->m_Monster[quest.MapNum][i].sIndex = -1;
					this->m_Monster[quest.MapNum][i].sPos = iMobPos;
				}
			}

			this->m_MonsterPosLoaded = true;
		}
	}
}

int CMapQuest::GetMonsterPos(WORD Type, BYTE Map, BYTE X, BYTE Y)
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
	gMSetBase.m_Mp[gMSetBase.m_Count].m_Dis			= 5;	//0
	gMSetBase.m_Mp[gMSetBase.m_Count].m_Type		= Type;
	gMSetBase.m_Mp[gMSetBase.m_Count].m_MapNumber	= Map;
	gMSetBase.m_Mp[gMSetBase.m_Count].m_W			= X;
	gMSetBase.m_Mp[gMSetBase.m_Count].m_H			= Y;
	gMSetBase.m_Mp[gMSetBase.m_Count].m_X			= X;
	gMSetBase.m_Mp[gMSetBase.m_Count].m_Y			= Y;
	gMSetBase.m_Mp[gMSetBase.m_Count].m_ArrangeType = 2;	//3	1 0	//2<<
	gMSetBase.m_Mp[gMSetBase.m_Count].m_Dir			= 2;

	return gMSetBase.m_Count;
}

void CMapQuest::AddBossEx(int Map, int BossClass, int BossX, int BossY, int OrcClass, int OrcCount)
{
	if(this->m_Boss[Map].sPos == -1)
	{
		return;
	}

	short BossIndex = gObjAddMonster(Map);

	if(!OBJMAX_RANGE(BossIndex))
	{
		return;
	}

	this->m_Boss[Map].sIndex = BossIndex;

	gObj[BossIndex].m_PosNum = this->m_Boss[Map].sPos;
	gObj[BossIndex].MapNumber = Map;
	gObj[BossIndex].Dir = rand()%8;
	gObj[BossIndex].X = BossX;
	gObj[BossIndex].Y = BossY;
	gObj[BossIndex].TX = BossX;
	gObj[BossIndex].TY = BossY;
	gObj[BossIndex].m_OldX = BossX;
	gObj[BossIndex].m_OldY = BossY;
	gObj[BossIndex].StartX = BossX;
	gObj[BossIndex].StartY = BossY;
	gObj[BossIndex].MaxRegenTime = 0;
	gObj[BossIndex].Dir = rand()%8;
	gObj[BossIndex].RegenTime = GetTickCount();
	gObj[BossIndex].m_ActState.Emotion = 1;
	gObj[BossIndex].m_ActState.EmotionCount = 15;

	gObjSetMonster(BossIndex, BossClass);

	char szMsg[128];
	sprintf(szMsg,"[Map Quest] Boss %s in %s map", gObj[BossIndex].Name, exMapName(gObj[BossIndex].MapNumber));
	AllSendServerMsg(szMsg);

	this->m_BossStart[Map] = true;

	short X = BossX;
	short Y = BossY;

	for(int i = 0; i < 100; i++)
	{
		if(this->m_Monster[Map][i].sPos == -1)
		{
			continue;
		}

		int OrcIndex = gObjAddMonster(Map);

		if(!OBJMAX_RANGE(OrcIndex))
		{
			continue;
		}

		this->m_Monster[Map][i].sIndex = OrcIndex;

		gMSetBase.GetBoxPosition(Map, (BossX - 5), (BossY - 5), (BossX + 5), (BossY + 5), X, Y);
		
		gObj[OrcIndex].m_PosNum = this->m_Monster[Map][i].sPos;
		gObj[OrcIndex].MapNumber = Map;
		gObj[OrcIndex].Dir = rand()%8;
		gObj[OrcIndex].X = X;
		gObj[OrcIndex].Y = Y;
		gObj[OrcIndex].TX = X;
		gObj[OrcIndex].TY = Y;
		gObj[OrcIndex].m_OldX = X;
		gObj[OrcIndex].m_OldY = Y;
		gObj[OrcIndex].StartX = X;
		gObj[OrcIndex].StartY = Y;
		gObj[OrcIndex].MaxRegenTime = 0;
		gObj[OrcIndex].Dir = rand()%8;
		gObj[OrcIndex].RegenTime = GetTickCount();
		gObj[OrcIndex].m_ActState.Emotion = 1;
		gObj[OrcIndex].m_ActState.EmotionCount = 15;

		gObjSetMonster(OrcIndex, OrcClass);
	}
}

void CMapQuest::DelMonster(int aIndex, int Map)
{
	if(this->m_Boss[Map].sIndex == aIndex)
	{
		gObjDel(aIndex);
		this->m_Boss[Map].sIndex = -1;
		return;
	}

	for(int i = 0; i < 100; i++)
	{
		if(this->m_Monster[Map][i].sIndex == aIndex)
		{
			gObjDel(aIndex);
			this->m_Monster[Map][i].sIndex = -1;
			return;
		}
	}
}

void CMapQuest::DelMonsterMap(int Map)
{
	if(OBJMAX_RANGE(this->m_Boss[Map].sIndex))
	{
		gObjDel(this->m_Boss[Map].sIndex);
		this->m_Boss[Map].sIndex = -1;
	}
	
	for(int i = 0; i < 100; i++)
	{
		if(OBJMAX_RANGE(this->m_Monster[Map][i].sIndex))
		{
			gObjDel(this->m_Monster[Map][i].sIndex);
			this->m_Monster[Map][i].sIndex = -1;
		}
	}
}

bool CMapQuest::GetMapMonster(int aPos)
{
//	int iPos = gObj[aIndex].m_Pos;

	//if(OBJMAX_RANGE(aIndex))
	if(aPos != -1)
	{
		for(int m = 0; m < MAX_NUMBER_MAP; m++)
		{
			if(this->m_Boss[m].sPos == aPos)
			{
				return true;
			}

			for(int i = 0; i < 100; i++)
			{
				if(this->m_Monster[m][i].sPos == aPos)
				{
					return true;
				}
			}
		}
	}

	return false;
}

#endif