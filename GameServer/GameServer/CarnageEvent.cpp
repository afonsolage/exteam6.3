#include "StdAfx.h"
#include "CarnageEvent.h"
#include "..\\include\\ReadScript.h"
#include "logproc.h"
#include "GameMain.h"
#include "BloodCastle.h"
#include "MapServerManager.h"
#include "DSProtocol.h"
#include "Functions.h"
#include "ExLicense.h"

#if(EVENT_CARNAGE)

CCarnageEvent g_CarnageEvent;

CCarnageEvent::CCarnageEvent()
{
	this->m_EventStatus = 0;
	this->m_EventStage = 0;
	this->m_TickCount = 0;
	this->m_TickRemain = 0;
	this->m_TickWait = 0;

	this->m_Enable = 0;
	this->m_MapNumber = 0;
	this->m_MapX = 0;
	this->m_MapY = 0;
	this->m_OpenTime = 0;
	this->m_PlayTime = 0;
	this->m_EndTime = 0;

	this->m_NpcClass = 0;
	this->m_NpcMap = 0;
	this->m_NpcX = 0;
	this->m_NpcY = 0;

	this->m_TicketType = 0;
	this->m_TicketIndex = 0;
	this->m_TicketLevel = 0;

	this->m_RewardItemCount = 0;
	this->m_RewardAncentRate = 0;

	this->m_MonsterCount = 0;

	this->m_TimeData.clear();
	this->m_MonsterData.clear();
	this->m_ItemData.clear();
	
	for(int i = 0; i < CARNAGE_MONSTER_MAX; i++)
	{
		this->m_MonsterBase[i].Stage  = -1;
		this->m_MonsterBase[i].Type  = -1;
		this->m_MonsterBase[i].aIndex = -1;
		this->m_MonsterBase[i].Pos	 = -1;
		this->m_MonsterBase[i].Class  = -1;
	}
}

CCarnageEvent::~CCarnageEvent()
{
}

void CCarnageEvent::Load()
{
	if(this->m_EventStatus == eCARNAGE_STATUS_WAIT || this->m_EventStatus == eCARNAGE_STATUS_START)
	{
		return;
	}

	this->m_Enable = 0;

	if(!g_ExLicense.CheckUser(eExUB::Local)  &&
	   !g_ExLicense.CheckUser(eExUB::Gredy)  &&
	   !g_ExLicense.CheckUser(eExUB::Gredy2) &&
	   !g_ExLicense.CheckUser(eExUB::GredyLocal) &&
	   !g_ExLicense.CheckUser(eExUB::Artem) &&
	   !g_ExLicense.CheckUser(eExUB::Artem2) &&
	   !g_ExLicense.CheckUser(eExUB::ulasevich) &&
	    !g_ExLicense.CheckUser(eExUB::ulasevich2))
	{
		return;
	}
	
	this->m_MapNumber = 0;
	this->m_MapX = 0;
	this->m_MapY = 0;
	this->m_OpenTime = 0;
	this->m_PlayTime = 0;
	this->m_EndTime = 0;

	this->m_NpcClass = 0;
	this->m_NpcMap = 0;
	this->m_NpcX = 0;
	this->m_NpcY = 0;

	this->m_TicketType = 0;
	this->m_TicketIndex = 0;
	this->m_TicketLevel = 0;

	this->m_RewardItemCount = 0;
	this->m_RewardAncentRate = 0;

	this->m_TimeData.clear();
	this->m_MonsterData.clear();
	this->m_ItemData.clear();

	this->Read(gDirPath.GetNewPath("ExData\\Events\\CarnageEvent.dat"));
}

void CCarnageEvent::Read(char* filename)
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

		if(iType < 0 || iType > 6)
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

				Token = GetToken();
				this->m_MapNumber = (int)TokenNumber;

				Token = GetToken();
				this->m_MapX = (int)TokenNumber;

				Token = GetToken();
				this->m_MapY = (int)TokenNumber;

				Token = GetToken();
				this->m_OpenTime = (int)TokenNumber;

				Token = GetToken();
				this->m_PlayTime = (int)TokenNumber;

				Token = GetToken();
				this->m_EndTime = (int)TokenNumber;
			}
			else if(iType == 1)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				this->m_NpcClass = (int)TokenNumber;

				Token = GetToken();
				this->m_NpcMap = (int)TokenNumber;

				Token = GetToken();
				this->m_NpcX = (int)TokenNumber;

				Token = GetToken();
				this->m_NpcY = (int)TokenNumber;
			}
			else if(iType == 2)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				this->m_TicketActive = (int)TokenNumber;

				Token = GetToken();
				this->m_TicketType = (int)TokenNumber;

				Token = GetToken();
				this->m_TicketIndex = (int)TokenNumber;

				Token = GetToken();
				this->m_TicketLevel = (int)TokenNumber;
			}
			else if(iType == 3)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				this->m_RewardItemCount = (int)TokenNumber;

				Token = GetToken();
				this->m_RewardAncentRate = (int)TokenNumber;
			}
			else if(iType == 4)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				CARNAGE_TIME List;

				List.Hour = (int)TokenNumber;

				Token = GetToken();
				List.Min = (int)TokenNumber;

				this->m_TimeData.push_back(List);
			}
			else if(iType == 5)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				CARNAGE_ITEM List;

				List.Type = (int)TokenNumber;

				Token = GetToken();
				List.Index = (int)TokenNumber;

				Token = GetToken();
				List.MinLevel = (int)TokenNumber;

				Token = GetToken();
				List.MaxLevel = (int)TokenNumber;

				Token = GetToken();
				List.Skill = (int)TokenNumber;

				Token = GetToken();
				List.Luck = (int)TokenNumber;

				Token = GetToken();
				List.Add = (int)TokenNumber;

				Token = GetToken();
				List.Exc = (int)TokenNumber;

				this->m_ItemData.push_back(List);
			}
			else if(iType == 6)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				CARNAGE_MONSTER_DATA List;

				List.MobClass = (int)TokenNumber;

				Token = GetToken();
				List.MobX = (int)TokenNumber;

				Token = GetToken();
				List.MobY = (int)TokenNumber;

				Token = GetToken();
				List.MobCount = (int)TokenNumber;

				Token = GetToken();
				List.BossActive = (int)TokenNumber;

				Token = GetToken();
				List.BossClass = (int)TokenNumber;

				Token = GetToken();
				List.BossX = (int)TokenNumber;

				Token = GetToken();
				List.BossY = (int)TokenNumber;

				Token = GetToken();
				memcpy(List.BossDie, TokenString, 64-1);

				this->m_MonsterData.push_back(List);
			}
		}
	}

	fclose(SMDFile);

	LogAdd("%s file load!", filename);
}

void CCarnageEvent::Run()
{
	if(!this->m_Enable)
	{
		return;
	}

	switch(this->m_EventStatus)
	{
	case eCARNAGE_STATUS_CLOSE:	
		this->ProcessStateClose();		
		break;
	case eCARNAGE_STATUS_WAIT:	
		this->ProcessStateWait();		
		break;
	case eCARNAGE_STATUS_START:	
		this->ProcessStateStart();		
		break;
	case eCARNAGE_STATUS_END:	
		this->ProcessStateEnd();		
		break;
	}
}

void CCarnageEvent::ProcessStateClose()
{
	SYSTEMTIME systime;
	GetLocalTime(&systime);

	for(std::vector<CARNAGE_TIME>::iterator it = this->m_TimeData.begin(); it != this->m_TimeData.end(); it++)
	{
		if(it->Hour == systime.wHour && it->Min == systime.wMinute)
		{
			this->SetStateWait();

			return;
		}
	}
}

void CCarnageEvent::ProcessStateWait()
{
	int iTickMsec = (GetTickCount() - this->m_TickCount);

	if(iTickMsec >= 1000)
	{
		this->m_TickRemain -= iTickMsec;			
		this->m_TickCount = GetTickCount();

		if(this->m_TickRemain <= (60000 * this->m_OpenTime))
		{
			if((this->m_TickCount - this->m_TickWait) > 60000)
			{
				int iWaitMin = (this->m_TickRemain / 60000) + 1;
				char szTemp[128];
				sprintf(szTemp, "%d minute(s) left before Carnage starts.", iWaitMin);
				AllSendServerMsg(szTemp);
				this->m_TickWait = GetTickCount();
			}
		}
	}

	if(this->m_TickRemain <= 0)
	{
		this->SetStateStart();
	}
}

void CCarnageEvent::ProcessStateStart()
{
	int iTickMsec = (GetTickCount() - this->m_TickCount);

	if(iTickMsec >= 1000)
	{
		this->m_TickRemain -= iTickMsec;			
		this->m_TickCount = GetTickCount();
	}

	if(this->m_TickRemain <= 0)
	{
		this->SetStateEnd();
	}
}

void CCarnageEvent::ProcessStateEnd()
{
	int iTickMsec = (GetTickCount() - this->m_TickCount);

	if(iTickMsec >= 1000)
	{
		this->m_TickRemain -= iTickMsec;			
		this->m_TickCount = GetTickCount();

		if(this->m_TickRemain >= 1000 && this->m_TickRemain < (CARNAGE_TIME_END + 1000))
		{
			int iEndSec = (this->m_TickRemain / 1000);

			for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
			{
				if(gObj[aIndex].Connected >= PLAYER_PLAYING && gObj[aIndex].MapNumber == this->m_MapNumber)
				{
					MsgOutput(aIndex, "%d second(s) left before Carnage close.", iEndSec);
				}
			}
		}
	}

	if(this->m_TickRemain <= 0)
	{
		this->SetStateClose();
	}
}

void CCarnageEvent::SetStateClose()
{
	this->m_TickCount = GetTickCount();
	this->m_TickRemain = 0;
	this->m_EventStatus = eCARNAGE_STATUS_CLOSE;

	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		if(gObj[aIndex].Connected >= PLAYER_PLAYING && gObj[aIndex].MapNumber == this->m_MapNumber)
		{
			gObjMoveGate(aIndex, 17);
		}
	}

	AllSendServerMsg("Carnage Event Close!");
}

void CCarnageEvent::SetStateWait()
{
	this->m_TickCount = GetTickCount();
	this->m_TickRemain = 60000 * this->m_OpenTime;
	this->m_EventStatus = eCARNAGE_STATUS_WAIT;
}

void CCarnageEvent::SetStateStart()
{
	this->m_TickCount = GetTickCount();
	this->m_TickRemain = 60000 * this->m_PlayTime;
	this->m_EventStatus = eCARNAGE_STATUS_START;
	this->m_EventStage = 0;

	AllSendServerMsg("Carnage Event Start to fight!");

	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		LPOBJ lpUser = &gObj[aIndex];

		if(lpUser->Connected >= PLAYER_PLAYING && lpUser->MapNumber == this->m_MapNumber)
		{
			this->GCMapAttribute(aIndex, 1);
		}
	}

	this->AddMonster(this->m_EventStage, 0);
}

void CCarnageEvent::SetStateEnd()
{
	this->DelMonster();

	this->m_TickCount = GetTickCount();
	this->m_TickRemain = this->m_PlayTime * 60000;
	this->m_EventStatus = eCARNAGE_STATUS_END;

	AllSendServerMsg("Carnage Event Ended!");
}

bool CCarnageEvent::NpcDialog(int aIndex, int aNpcIndex)
{
	if(!OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(aNpcIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNpcIndex];

	if( lpNpc->Class == this->m_NpcClass && 
		lpNpc->MapNumber == this->m_NpcMap && 
		lpNpc->X == this->m_NpcX && 
		lpNpc->Y == this->m_NpcY )
	{
		if(this->m_EventStatus == eCARNAGE_STATUS_WAIT)
		{
			if(this->m_TicketActive)
			{
				if(gObjGetItemCountInInventory(aIndex, ITEMGET(this->m_TicketType, this->m_TicketIndex), this->m_TicketLevel) > 0)
				{
					gObjDeleteItemsCount(aIndex, ITEMGET(this->m_TicketType, this->m_TicketIndex), this->m_TicketLevel, 1);

					gObjTeleport(aIndex, this->m_MapNumber, this->m_MapX, this->m_MapY);	

					this->GCMapAttribute(aIndex, 0);

					return true;
				}
				else
				{
					MsgOutput(aIndex, "Carnage Event need ticket item (%d, %d).", this->m_TicketType, this->m_TicketIndex);
				}
			}
		}
		else
		{
			MsgOutput(aIndex, "Carnage Event Close.", this->m_TicketType, this->m_TicketIndex);
		}	
	}

	return false;
}

int CCarnageEvent::GetMonsterPos(WORD Type, BYTE Map, BYTE X, BYTE Y)
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
	gMSetBase.m_Mp[gMSetBase.m_Count].m_Dis			= 6;
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

void CCarnageEvent::LoadMonster()
{
	if(this->m_EventStatus == eCARNAGE_STATUS_WAIT || this->m_EventStatus == eCARNAGE_STATUS_START)
	{
		return;
	}

	this->m_MonsterCount = 0;

	for(int i = 0; i < CARNAGE_MONSTER_MAX; i++)
	{
		this->m_MonsterBase[i].Stage  = -1;
		this->m_MonsterBase[i].aIndex = -1;
		this->m_MonsterBase[i].Pos	 = -1;
		this->m_MonsterBase[i].Class  = -1;
	}

	for(int i = 0; i < this->m_MonsterData.size(); i++)
	{
		int iMobClass = this->m_MonsterData[i].MobClass;
		int iMobX = this->m_MonsterData[i].MobX;
		int iMobY = this->m_MonsterData[i].MobY;
		int iMobCount = this->m_MonsterData[i].MobCount;

		for(int n = 0; n < iMobCount; n++)
		{
			int iMobPos = this->GetMonsterPos(iMobClass, this->m_MapNumber, iMobX, iMobY);

			if(iMobPos >= 0)
			{
				this->m_MonsterBase[this->m_MonsterCount].Type = 0;
				this->m_MonsterBase[this->m_MonsterCount].Stage = i;
				this->m_MonsterBase[this->m_MonsterCount].aIndex = -1;
				this->m_MonsterBase[this->m_MonsterCount].Pos = iMobPos;
				this->m_MonsterBase[this->m_MonsterCount].Class = iMobClass;
				this->m_MonsterCount++;
			}	

			if(this->m_MonsterCount >= CARNAGE_MONSTER_MAX)
			{
				MsgBox("Carnage max load monster");
				return;
			}
		}

		if(this->m_MonsterData[i].BossActive)
		{
			int iBossClass = this->m_MonsterData[i].BossClass;
			int iBossX = this->m_MonsterData[i].BossX;
			int iBossY = this->m_MonsterData[i].BossY;

			int iBossPos = this->GetMonsterPos(iBossClass, this->m_MapNumber, iBossX, iBossY);

			if(iBossPos >= 0)
			{
				this->m_MonsterBase[this->m_MonsterCount].Type = 1;
				this->m_MonsterBase[this->m_MonsterCount].Stage = i;
				this->m_MonsterBase[this->m_MonsterCount].aIndex = -1;
				this->m_MonsterBase[this->m_MonsterCount].Pos = iBossPos;
				this->m_MonsterBase[this->m_MonsterCount].Class = iBossClass;
				this->m_MonsterCount++;
			}

			if(this->m_MonsterCount >= CARNAGE_MONSTER_MAX)
			{
				MsgBox("Carnage max load monster");
				return;
			}
		}
	}
}

void CCarnageEvent::AddMonster(int Stage, int Type)
{	
	if(this->m_EventStatus != eCARNAGE_STATUS_START)
	{
		return;
	}

	for(int i = 0; i < this->m_MonsterCount; i++)
	{
		if(this->m_MonsterBase[i].Stage == Stage && this->m_MonsterBase[i].Type == Type)
		{
			int iMobIndex = gObjAddMonster(this->m_MapNumber);

			if(iMobIndex >= 0 && iMobIndex < OBJ_MAXMONSTER)
			{
				this->m_MonsterBase[i].aIndex = iMobIndex; 

				gObjSetPosMonster(iMobIndex, this->m_MonsterBase[i].Pos);
				gObjSetMonster(iMobIndex, this->m_MonsterBase[i].Class);

				if(this->m_MonsterBase[i].Type == 0)
				{
					this->m_StageMonsterCount++;
				}
			}
		}
	}
}

void CCarnageEvent::DelMonster()
{
	if(this->m_EventStatus != eCARNAGE_STATUS_START)
	{
		return;
	}

	for(int i = 0; i < this->m_MonsterCount; i++)
	{
		int iMobIndex = this->m_MonsterBase[i].aIndex;

		if(iMobIndex >= 0 && iMobIndex < OBJ_MAXMONSTER)
		{
			int iMobPos = this->m_MonsterBase[i].Pos;
			int iMobClass = this->m_MonsterBase[i].Class;

			if(iMobClass == gObj[iMobIndex].Class && gMSetBase.m_Mp[iMobPos].m_MapNumber == gObj[iMobIndex].MapNumber)
			{
				gObjDel(iMobIndex);

				this->m_MonsterBase[i].aIndex = -1; 
			}
		}
	}
}

void CCarnageEvent::DieMonster(int aIndex, int aMonsterIndex)
{
	if(this->m_EventStatus != eCARNAGE_STATUS_START)
	{
		return;
	}

	for(int i = 0; i < this->m_MonsterCount; i++)
	{
		if(this->m_MonsterBase[i].aIndex == aMonsterIndex)
		{
			if(OBJMAX_RANGE(this->m_MonsterBase[i].aIndex))
			{
				int iMonsterType = this->m_MonsterBase[i].Type;

				this->MessageMonster(aMonsterIndex, iMonsterType);

				this->RewardMonster(aIndex, aMonsterIndex, iMonsterType);

				gObjDel(this->m_MonsterBase[i].aIndex);
				this->m_MonsterBase[i].aIndex = -1;

				this->StageMonster(aMonsterIndex, iMonsterType);

				return;
			}
		}
	}
}

void CCarnageEvent::RewardMonster(int aIndex, int aMonsterIndex, int MonsterType)
{
	if(!OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(aMonsterIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpMonster = &gObj[aMonsterIndex];

	BYTE cDropX = lpMonster->X;
	BYTE cDropY = lpMonster->Y;

	if(MonsterType == 0)
	{
		if(!gObjGetRandomItemDropLocation(lpUser->MapNumber, cDropX, cDropY, 4, 4, 10))
		{
			cDropX = lpMonster->X;
			cDropY = lpMonster->Y;
		}

		if(this->m_RewardAncentRate > (rand()%10000))
		{
			MakeRewardSetItem(aIndex, cDropX, cDropY, 0, lpMonster->MapNumber);
		}
	}
	else if(MonsterType == 1)
	{
		for(int i = 0; i < this->m_RewardItemCount; i++)
		{
			if(!gObjGetRandomItemDropLocation(lpMonster->MapNumber, cDropX, cDropY, 4, 4, 10))
			{
				cDropX = lpMonster->X;
				cDropY = lpMonster->Y;
			}

			int iRand = rand() % this->m_ItemData.size();

			int iItem = ITEMGET(this->m_ItemData[iRand].Type, this->m_ItemData[iRand].Index);
			int iLevel = this->m_ItemData[iRand].MinLevel;
			int iSkill =  this->m_ItemData[iRand].Skill;
			int iLuck =  this->m_ItemData[iRand].Luck;
			int iAdd =  this->m_ItemData[iRand].Add;
			int iExl =  GenExcOpt(this->m_ItemData[iRand].Exc);

			if(this->m_ItemData[i].MaxLevel > this->m_ItemData[i].MinLevel)
			{
				iLevel = this->m_ItemData[i].MinLevel + (rand() % (this->m_ItemData[i].MaxLevel - this->m_ItemData[i].MinLevel + 1));
			}	

			ItemSerialCreateSend(aIndex, lpUser->MapNumber, cDropX, cDropY, iItem, iLevel, 0, iSkill, iLuck, iAdd, aIndex, iExl, 0);
		}
	}
}

void CCarnageEvent::MessageMonster(int aMonsterIndex, int MonsterType)
{
	if(MonsterType != 1)
	{
		return;
	}

	if(!OBJMAX_RANGE(aMonsterIndex))
	{
		return;
	}

	int iStage = this->m_EventStage;

	if(this->m_EventStage >= this->m_MonsterData.size())
	{
		return;
	}

	if(strlen(this->m_MonsterData[iStage].BossDie) < 1)
	{
		return;
	}

	LPOBJ lpMonster = &gObj[aMonsterIndex];

	char szBossMessage[64];
	sprintf(szBossMessage, this->m_MonsterData[this->m_EventStage].BossDie);

	ChatSend(lpMonster, szBossMessage);
}

void CCarnageEvent::StageMonster(int aMonsterIndex, int MonsterType)
{
	if(!OBJMAX_RANGE(aMonsterIndex))
	{
		return;
	}

	if(MonsterType == 0)
	{
		this->m_StageMonsterCount--;

		if(this->m_StageMonsterCount <= 0)
		{
			this->AddMonster(this->m_EventStage, 1);
		}
	}
	else if(MonsterType == 1)
	{
		this->m_EventStage++;

		if(this->m_EventStage >= this->m_MonsterData.size())
		{
			this->SetStateEnd();
			return;
		}

		this->AddMonster(this->m_EventStage, 0);
	}
}

void CCarnageEvent::GCMapAttribute(int aIndex, int maptype)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	int iSizePacket = 0;
	unsigned char btPacket[256];
	
	PMSG_SETMAPATTR_COUNT pMsg;
	PMSG_SETMAPATTR pBodyMsg;

	iSizePacket += sizeof(pMsg);

	pMsg.btType = 0;
	pMsg.btMapAttr = 1;
	pMsg.btMapSetType = maptype;
	pMsg.btCount = 1;

	pBodyMsg.btX = 0;
	pBodyMsg.btY = 0;
	memcpy(&btPacket[iSizePacket], &pBodyMsg, sizeof(pBodyMsg));
	iSizePacket += sizeof(pBodyMsg);
	pBodyMsg.btX   = 255;
	pBodyMsg.btY   = 255;
	memcpy(&btPacket[iSizePacket], &pBodyMsg, sizeof(pBodyMsg));
	iSizePacket += sizeof(pBodyMsg);

	pMsg.h.c = 0xC1;
	pMsg.h.size = iSizePacket;
	pMsg.h.headcode = 0x46;
	memcpy(&btPacket, &pMsg, sizeof(pMsg));
	
	DataSend(aIndex, (LPBYTE)&btPacket, iSizePacket);
}



#endif