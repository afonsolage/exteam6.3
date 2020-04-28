#include "StdAfx.h"
#include "ExWinQuestSystem.h"
#include "user.h"
#include "GameMain.h"
#include "DSProtocol.h"
#include "ExFunction.h"
#include "logproc.h"
#include "ExUser.h"
//#include "BuffManagerEx.h"
#include "..\include\ReadScript.h"
#include "gObjMonster.h"
#include "BuffManager.h"
#include "ExLicense.h"

#if(CUSTOM_EX_QUEST_SYSTEM==TRUE)
// ----------------------------------------------------------------------------------------------

ExWinQuestSystem g_ExWinQuestSystem;
// ----------------------------------------------------------------------------------------------

ExWinQuestSystem::ExWinQuestSystem()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

ExWinQuestSystem::~ExWinQuestSystem()
{
	// ----
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::Init()
{
	ZeroMemory(&this->ewdata,sizeof(this->ewdata));

	this->Enable = false;
	this->NPC_Class = 0;
	this->NPC_Map = 0;
	this->NPC_X = 0;
	this->NPC_Y = 0;
	this->iDropLoaded = 0;
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::Load()
{
	this->Init();

	//if(!g_ExLicense.user.CraftQuestSystem)
	//{
	//	return;
	//}

	this->Read(gDirPath.GetNewPath("ExData\\ExWinQuest\\ExWinQuestSystem.ini"));
	this->ReadQuest(0, gDirPath.GetNewPath("ExData\\ExWinQuest\\ExWinQuestData_unique.ini"));
	//this->ReadQuest(1, gDirPath.GetNewPath("ExData\\ExWinQuest\\ExWinQuestData_daily.ini"));
	//this->ReadQuest(2, gDirPath.GetNewPath("ExData\\ExWinQuest\\ExWinQuestData_3.ini"));
	this->ReadDrop(gDirPath.GetNewPath("ExData\\ExWinQuest\\ExWinQuestDrop.ini"));
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::Read(char* File)
{
	this->Enable = GetPrivateProfileInt("ExTeam", "Enable", 0, File);
	this->NPC_Class = GetPrivateProfileInt("ExTeam", "NPC_Class", 0, File);
	this->NPC_Map = GetPrivateProfileInt("ExTeam", "NPC_Map", 0, File);
	this->NPC_X = GetPrivateProfileInt("ExTeam", "NPC_X", 0, File);
	this->NPC_Y = GetPrivateProfileInt("ExTeam", "NPC_Y", 0, File);
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::ReadQuest(int a, char* File)
{
	int Token;

	SMDFile = fopen(File, "r");

	if( SMDFile == NULL )
	{
		MsgBox(lMsg.Get(MSGGET(0, 112)), File);
		return;
	}

	int n = 0;

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
		
		this->ewdata[a][n].NeedLevel = TokenNumber;

		Token = GetToken();
		this->ewdata[a][n].NeedReset = TokenNumber;

		Token = GetToken();
		this->ewdata[a][n].NeedGrand = TokenNumber;

		Token = GetToken();
		strncpy(this->ewdata[a][n].NameQuest, TokenString, 25);

		Token = GetToken();
		this->ewdata[a][n].AllowDW = (BOOL)TokenNumber;

		Token = GetToken();
		this->ewdata[a][n].AllowDK = (BOOL)TokenNumber;

		Token = GetToken();
		this->ewdata[a][n].AllowELF = (BOOL)TokenNumber;

		Token = GetToken();
		this->ewdata[a][n].AllowSUM = (BOOL)TokenNumber;

		Token = GetToken();
		this->ewdata[a][n].AllowMG = (BOOL)TokenNumber;

		Token = GetToken();
		this->ewdata[a][n].AllowDL = (BOOL)TokenNumber;

		Token = GetToken();
		this->ewdata[a][n].AllowRF = (BOOL)TokenNumber;

		Token = GetToken();
		this->ewdata[a][n].Map = (int)TokenNumber;

		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			Token = GetToken();

			if (Token == END)
			{
				break;
			}
			else if ( Token == 0 )
			{
				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}
			}

			this->ewdata[a][n].MissionType[m]		= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionID[m]			= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionIndex[m]		= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionLevel[m]		= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionLuck[m]		= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionOpt[m]		= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionExl[m]		= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionProcent[m]	= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].MissionCount[m]		= TokenNumber;
		}

		for(int r = 0; r < EW_MAX_REWARD; r++)
		{
			Token = GetToken();

			if (Token == END)
			{
				break;
			}
			else if ( Token == 0 )
			{
				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}
			}

			this->ewdata[a][n].RewardType[r]		= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].RewardItemType[r]	= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].RewardItemIndex[r]	= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].RewardItemLevel[r]	= TokenNumber;

			Token = GetToken();
			this->ewdata[a][n].RewardCount[r]		= TokenNumber;
		}

		n++;
	}

	this->iLoaded[a] = n;
	fclose(SMDFile);	
	LogAddTD("[ExWinQuestSystem][ReadQuestEx] [%d] Item loaded from list", this->iLoaded[a]);
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::ReadDrop(char* File)
{
	SMDFile = fopen(File, "r");

	if( SMDFile == NULL )
	{
		LogAdd(lMsg.Get(MSGGET(1, 198)), File);
		return;
	}

	while(true)
	{
		SMDToken Token = GetToken();

		if( Token == END )
		{
			break;
		}

		this->m_Drop[this->iDropLoaded].iAct				= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].iNeedQuest			= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemType			= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemIndex			= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemMinLevel		= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemMaxLevel		= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemMaxOption		= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemLuck			= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemSkill			= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemExcellent		= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemDur				= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].ItemDropRate		= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].MonsterMinLevel		= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].MonsterMaxLevel		= TokenNumber;

		GetToken();
		this->m_Drop[this->iDropLoaded].MonsterMap			= TokenNumber;
	}
	// ----
	fclose(SMDFile);
	LogAddTD("[ExWinQuestSystem][ReadDrop] [%d] Item loaded from list", this->iDropLoaded);
}
// ----------------------------------------------------------------------------------------------

bool ExWinQuestSystem::Dialog(int aIndex, int aNpcIndex)
{
	if(!this->Enable)
	{
 		return false;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNpcIndex];

	if(		lpNpc->Class		== this->NPC_Class 
		&&	lpNpc->MapNumber	== this->NPC_Map
		&&	lpNpc->X			== this->NPC_X
		&&	lpNpc->Y			== this->NPC_Y )
	{

		this->GC_OpenWindow(aIndex);
		return true;
	}
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::GC_MainInfo(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	int n = 0;

	GC_MainPacket pReq;
	pReq.h.set((LPBYTE)&pReq, 0xFA, 0xCC, sizeof(pReq));

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		bool sb_accept = true;
		bool sb_done = true;

		bool sb_level = true;
		bool sb_reset = true;
		bool sb_grand = true;

		bool b_mission[EW_MAX_MISSION];

		for(int i = 0; i < EW_MAX_MISSION; i++)
		{
			b_mission[i] = true;
		}

		n = lpUser->ExWQuestNum[a];

		if(n >= this->iLoaded[a])
		{
			pReq.exQuest[a].b_End = true;
		}
		else
		{
			pReq.exQuest[a].b_End = false;
		}
		// -> user send
		strncpy(pReq.exQuest[a].NameQuest, this->ewdata[a][n].NameQuest, 25);
		pReq.exQuest[a].Start = lpUser->ExWQuestStart[a];
		pReq.exQuest[a].Number = lpUser->ExWQuestNum[a];
		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			if(this->ewdata[a][n].MissionType[m] == Searching)
			{
				pReq.exQuest[a].Count[m] = this->SearchItem(aIndex, a, m);
			}
			else
			{
				if(lpUser->ExWQuestCount[a][m] > this->ewdata[a][n].MissionCount[m])
				{
					lpUser->ExWQuestCount[a][m] = this->ewdata[a][n].MissionCount[m];
				}

				pReq.exQuest[a].Count[m] = lpUser->ExWQuestCount[a][m];
			}
		}	
		// -> need send
		if(this->ewdata[a][n].NeedLevel > lpUser->Level)
		{
			sb_level = false;
		}
		pReq.exQuest[a].NeedLevel = this->ewdata[a][n].NeedLevel;
		if(this->ewdata[a][n].NeedReset > lpUser->Reset)
		{
			sb_reset = false;
		}
		pReq.exQuest[a].NeedReset = this->ewdata[a][n].NeedReset;
		if(this->ewdata[a][n].NeedGrand > lpUser->GReset)
		{
			sb_grand = false;
		}
		pReq.exQuest[a].NeedGrand = this->ewdata[a][n].NeedGrand;
		// -> mission send
		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			if(this->ewdata[a][n].MissionType[m] == Hunting || this->ewdata[a][n].MissionType[m] == Droping)
			{
				if(this->ewdata[a][n].MissionCount[m] > lpUser->ExWQuestCount[a][m])
				{
					b_mission[m] = false;
					sb_done = false;
				}
			}
			else if(this->ewdata[a][n].MissionType[m] == Searching)
			{
				if(!this->SearchItem(aIndex, a, m))
				{
					b_mission[m] = false;
					sb_done = false;
				}
			}
			pReq.exQuest[a].b_Mission[m] = b_mission[m];

			pReq.exQuest[a].MissionType[m] = this->ewdata[a][n].MissionType[m];
			pReq.exQuest[a].MissionID[m] = this->ewdata[a][n].MissionID[m];
			pReq.exQuest[a].MissionIndex[m] = this->ewdata[a][n].MissionIndex[m];
			pReq.exQuest[a].MissionLevel[m] = this->ewdata[a][n].MissionLevel[m];
			pReq.exQuest[a].MissionLuck[m] = this->ewdata[a][n].MissionLuck[m];
			pReq.exQuest[a].MissionOpt[m] = this->ewdata[a][n].MissionOpt[m];
			pReq.exQuest[a].MissionExl[m] = this->ewdata[a][n].MissionExl[m];
			pReq.exQuest[a].MissionCount[m] = this->ewdata[a][n].MissionCount[m];
			pReq.exQuest[a].MissionProcent[m] = this->ewdata[a][n].MissionProcent[m];
		}
		// -> reward send
		for(int r = 0; r < EW_MAX_REWARD; r++)
		{
			pReq.exQuest[a].RewardType[r] = this->ewdata[a][n].RewardType[r];
			pReq.exQuest[a].RewardCount[r] = this->ewdata[a][n].RewardCount[r];
			pReq.exQuest[a].RewardItemType[r] = this->ewdata[a][n].RewardItemType[r];
			pReq.exQuest[a].RewardItemIndex[r] = this->ewdata[a][n].RewardItemIndex[r];
			pReq.exQuest[a].RewardItemLevel[r] = this->ewdata[a][n].RewardItemLevel[r];
		}
		if(lpUser->ExWQuestStart[a] == FALSE)
		{
			if( sb_level == false || sb_reset == false || sb_grand == false )
			{
				 sb_accept = false;
			}
		}

		pReq.exQuest[a].b_done = sb_done;
		pReq.exQuest[a].b_accept = sb_accept;

		pReq.exQuest[a].b_Level = sb_level;
		pReq.exQuest[a].b_Reset = sb_reset;
		pReq.exQuest[a].b_Grand = sb_grand;
	}

	DataSend(aIndex, (LPBYTE)&pReq, sizeof(pReq));
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::GC_OpenWindow(int aIndex)
{
	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}

	this->GC_MainInfo(aIndex);
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::GC_MiniInfo(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	GC_ExWinMiniInfo pReq = { 0 };
	pReq.h.set((LPBYTE)&pReq, 0xFA, 0xCD, sizeof(pReq));

	int n = 0;

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		n = lpUser->ExWQuestNum[a];
		strncpy(pReq.exQuest[a].NameQuest, this->ewdata[a][n].NameQuest, 25);
		pReq.exQuest[a].Start = lpUser->ExWQuestStart[a];

		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			if(this->ewdata[a][n].MissionType[m] == Hunting || this->ewdata[a][n].MissionType[m] == Droping)
			{
				pReq.exQuest[a].ExWQuestCount[m] = lpUser->ExWQuestCount[a][m];
			}
			else if(this->ewdata[a][n].MissionType[m] == Searching)
			{
				pReq.exQuest[a].ExWQuestCount[m] = this->SearchItem(aIndex, a, m);
			}

			pReq.exQuest[a].MissionType[m] = this->ewdata[a][n].MissionType[m];
			pReq.exQuest[a].MissionID[m] = this->ewdata[a][n].MissionID[m];
			pReq.exQuest[a].MissionIndex[m] = this->ewdata[a][n].MissionIndex[m];
			pReq.exQuest[a].MissionLevel[m] = this->ewdata[a][n].MissionLevel[m];
			pReq.exQuest[a].MissionLuck[m] = this->ewdata[a][n].MissionLuck[m];
			pReq.exQuest[a].MissionOpt[m] = this->ewdata[a][n].MissionOpt[m];
			pReq.exQuest[a].MissionExl[m] = this->ewdata[a][n].MissionExl[m];
			pReq.exQuest[a].MissionCount[m] = this->ewdata[a][n].MissionCount[m];
		}
	}

	DataSend(aIndex, (LPBYTE)&pReq, sizeof(pReq));
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::GC_MiniInfoEx(int aIndex, int a, int m)
{
	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}

	GC_ExWinMiniInfoEx exSend = { 0 };
	exSend.h.set((LPBYTE)&exSend, 0xFB, 0xC3, sizeof(exSend));

	exSend.a = a;
	exSend.m = m;

	DataSend(aIndex, (LPBYTE)&exSend, exSend.h.size);
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::CG_AcceptQuest(int aIndex, CG_Accept_Done* aRecv)
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

	int a = aRecv->Result;
	int n = lpUser->ExWQuestNum[a];

	if(!lpUser->ExWQuestStart[a])
	{
		if( this->ewdata[a][n].NeedLevel > lpUser->Level		||
			this->ewdata[a][n].NeedReset > lpUser->Reset		||
			this->ewdata[a][n].NeedGrand > lpUser->GReset )
		{
			LogAddC(2, "[ExWinQuestSystem] Error CG_AcceptQuest Result");
			return;
		}
		lpUser->ExWQuestStart[a] = true;
		this->GC_Start(aIndex, a, true);
	}
	else
	{
		this->RewardQuest(aIndex, a);
	}
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::GC_Start(int aIndex, int a, int s)
{
	GC_ExWinStart pReq = { 0 };
	pReq.h.set((LPBYTE)&pReq, 0xFB, 0xC4, sizeof(pReq));
	pReq.Act = a;
	pReq.Start = s;
	DataSend(aIndex, (LPBYTE)&pReq, pReq.h.size);

	/*if(g_BuffManagerEx.CheckExBuffData(aIndex, AT_QUEST_BUFF) == FALSE)
	{
		g_BuffManagerEx.AddExBuffData(aIndex, AT_QUEST_BUFF, -10);
	}*/

	//g_BuffManagerEx.GC_QuestBuffInfo(aIndex);
}
// ----------------------------------------------------------------------------------------------

bool ExWinQuestSystem::MonsterKiller(int aIndexMonster, int aIndexUser)
{
	bool Result = false;

	if(!this->Enable)
	{
 		return Result;
	}

	LPOBJ lpUser = &gObj[aIndexUser];
	LPOBJ lpMonster = &gObj[aIndexMonster];

	int n = 0;

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		n = lpUser->ExWQuestNum[a];

		if(lpUser->ExWQuestStart[a] == TRUE)
		{
			for(int m = 0; m < EW_MAX_MISSION; m++)
			{
				// -> Monsterr Mission
				if(this->ewdata[a][n].MissionType[m] == Hunting)
				{
					if(this->ewdata[a][n].MissionCount[m] > lpUser->ExWQuestCount[a][m])
					{
						if( this->ewdata[a][n].MissionLuck[m] == lpMonster->MapNumber ||  this->ewdata[a][n].MissionLuck[m] == -1 )
						{
							if(this->ewdata[a][n].MissionID[m] == lpMonster->Class)	// Охота на монастров по классу
							{
								lpUser->ExWQuestCount[a][m]++;
								this->GC_MiniInfoEx(aIndexUser, a, m);
							}
							else if(this->ewdata[a][n].MissionID[m] == -1)	// Охота на монастров по уровню
							{
								if(lpMonster->Level >= this->ewdata[a][n].MissionOpt[m] && lpMonster->Level <= this->ewdata[a][n].MissionExl[m])
								{
									lpUser->ExWQuestCount[a][m]++;
									this->GC_MiniInfoEx(aIndexUser, a, m);
								}
							}
						}
					}
				}
				// -> Drop Mission
				if( this->ewdata[a][n].MissionType[m] == Droping )
				{
					if( this->ewdata[a][n].MissionCount[m] > lpUser->ExWQuestCount[a][m] )
					{
						if( this->ewdata[a][n].MissionLuck[m] == lpMonster->MapNumber ||  this->ewdata[a][n].MissionLuck[m] == -1 )
						{
							if(lpMonster->Level >= this->ewdata[a][n].MissionOpt[m] && lpMonster->Level <= this->ewdata[a][n].MissionExl[m])
							{
								if ( (rand()%100) < this->ewdata[a][n].MissionProcent[m] )
								{
									int ItemType = ITEMGET(this->ewdata[a][n].MissionID[m], this->ewdata[a][n].MissionIndex[m]);
									ItemSerialCreateSend(aIndexUser,lpMonster->MapNumber,lpMonster->X,lpMonster->Y,ItemType,0,0,0,0,0,aIndexUser,0,0);
									Result = true;
								}
							}
						}
					}
				}
			}
		}
	}

#if(EW_NEW_DROP==TRUE)
	if(this->NewDrop(aIndexUser, aIndexMonster))
	{
		Result = true;
	}
#endif

	return Result;
}
// ----------------------------------------------------------------------------------------------

int ExWinQuestSystem::PickUpItem(int aIndex, int ItemType)
{
	if(!this->Enable)
	{
 		return 0;
	}

	int n = 0;
	LPOBJ lpUser = &gObj[aIndex];

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		n = lpUser->ExWQuestNum[a];

		if(lpUser->ExWQuestStart[a] == TRUE)
		{
			for(int m = 0; m < EW_MAX_MISSION; m++)
			{
				if( this->ewdata[a][n].MissionType[m] == Droping && 
					ITEMGET(this->ewdata[a][n].MissionID[m], this->ewdata[a][n].MissionIndex[m]) == ItemType )
				{
					if(this->ewdata[a][n].MissionCount[m] > lpUser->ExWQuestCount[a][m])
					{
						lpUser->ExWQuestCount[a][m]++;
						this->GC_MiniInfoEx(aIndex, a, m);
						return 1;
					}
					else if(lpUser->ExWQuestCount[a][m] >= this->ewdata[a][n].MissionCount[m])
					{
						return 2;
					}
				}
			}
		}
	}

	return 0;
}
// ----------------------------------------------------------------------------------------------

bool ExWinQuestSystem::SearchItem(int aIndex, int a, int m)
{
	LPOBJ lpUser = &gObj[aIndex];

	int n = lpUser->ExWQuestNum[a];

	short iType = ITEMGET(this->ewdata[a][n].MissionID[m], this->ewdata[a][n].MissionIndex[m]);
	short iLevel = this->ewdata[a][n].MissionLevel[m];
	short iLuck = this->ewdata[a][n].MissionLuck[m];
	short iOpt =  this->ewdata[a][n].MissionOpt[m];
	short iExl = this->ewdata[a][n].MissionExl[m];

	for (int i = INVETORY_WEAR_SIZE; i < INVENTORY_SIZE; i++)
	{
		if( lpUser->pInventory[i].m_Type == iType && 
			lpUser->pInventory[i].m_Level >= iLevel &&
			CheckOptionItem(lpUser->pInventory[i].m_Option2, iLuck, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_Option3, iOpt, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_NewOption, iExl, FALSE) )
		{
			return true;
		}
	}

	return false;
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::DeleteItem(int aIndex, int a, int m)
{
	LPOBJ lpUser = &gObj[aIndex];

	int n = lpUser->ExWQuestNum[a];

	short iType = ITEMGET(this->ewdata[a][n].MissionID[m], this->ewdata[a][n].MissionIndex[m]);
	short iLevel = this->ewdata[a][n].MissionLevel[m];
	short iLuck = this->ewdata[a][n].MissionLuck[m];
	short iOpt =  this->ewdata[a][n].MissionOpt[m];
	short iExl = this->ewdata[a][n].MissionExl[m];

	for (int i = INVETORY_WEAR_SIZE; i < INVENTORY_SIZE; i++)
	{
		if( lpUser->pInventory[i].m_Type == iType && 
			lpUser->pInventory[i].m_Level >= iLevel &&
			CheckOptionItem(lpUser->pInventory[i].m_Option2, iLuck, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_Option3, iOpt, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_NewOption, iExl, FALSE) )
		{
			gObjInventoryDeleteItem(aIndex, i);
			GCInventoryItemDeleteSend(aIndex, i, 1);
		}
	}
}
// ----------------------------------------------------------------------------------------------

bool ExWinQuestSystem::CheckMission(int aIndex, int a)
{
	LPOBJ lpUser = &gObj[aIndex];

	int n = lpUser->ExWQuestNum[a];

	for(int m = 0; m < EW_MAX_MISSION; m++)
	{
		if(this->ewdata[a][n].MissionType[m] == Hunting || this->ewdata[a][n].MissionType[m] == Droping)
		{
			if(this->ewdata[a][n].MissionCount[m] > lpUser->ExWQuestCount[a][m])
			{
				return false;
			}
		}
		else if(this->ewdata[a][n].MissionType[m] == Searching)
		{
			if(!this->SearchItem(aIndex, a, m))
			{
				return false;
			}
		}
	}

	return true;
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::UserConnect(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	this->GC_MiniInfo(aIndex);

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		if(lpUser->ExWQuestNum[a] >= 0 && lpUser->ExWQuestStart[a] == true)
		{
#if(CUSTOM_QUEST_BUFF==TRUE)
			//gObjAddBuffEffect(lpUser,AT_QUEST_BUFF,0,0,0,0,-10);
			g_BuffManagerEx.AddExBuffData(aIndex, AT_QUEST_BUFF, -10);
			g_BuffManagerEx.GC_QuestBuffInfo(aIndex);
#endif
			return;
		}
	}
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::RewardQuest(int aIndex, int Act)
{
	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}	

	LPOBJ lpUser = &gObj[aIndex];

	int a = Act;

	if(!this->CheckMission(aIndex, a))
	{
		LogAddC(2, "[ExWinQuestSystem] RewardQuest ERROR");
		return;
	}
	
	int n = lpUser->ExWQuestNum[a];
	int UserMap = lpUser->MapNumber;
	int UserX = lpUser->X;
	int UserY = lpUser->Y;

	int rType = 0;
	int rItemType = 0;
	int rItemIndex = 0;
	int rItemLevel = 0;
	int rCount = 0;

	for(int m = 0; m < EW_MAX_MISSION; m++)
	{
		lpUser->ExWQuestCount[a][m] = 0;
		if(this->ewdata[a][n].MissionType[m] == Searching)
		{
			this->DeleteItem(aIndex, a, m);
		}
	}

	for(int r = 0; r < EW_MAX_REWARD; r++)
	{
		rType = this->ewdata[a][n].RewardType[r];
		rItemType = this->ewdata[a][n].RewardItemType[r];
		rItemIndex = this->ewdata[a][n].RewardItemIndex[r];
		rItemLevel = this->ewdata[a][n].RewardItemLevel[r];
		rCount = this->ewdata[a][n].RewardCount[r];

		if(rType == ewZen)
		{	
			if(!MAX_MAP_RANGE(UserMap))
			{
				return;
			}
			MapC[UserMap].MoneyItemDrop(rCount, UserX, UserY);
		}
		if(rType == ewFreePoint)
		{
//#if(CUSTOM_EX_FREE_POINT==TRUE)
			lpUser->ExFreePoints += rCount;
//#endif
			lpUser->LevelUpPoint += rCount;
			//g_ExUser.UpdateCharInfo(aIndex);
			ExUserDataSend(aIndex);
		}
		if(rType == ewItem)
		{
			for(int d = 0; d < rCount; d++ )
			{
				ItemSerialCreateSend(aIndex, UserMap, UserX, UserY, ITEMGET(rItemType, rItemIndex), rItemLevel, 0, 0, 0, 0, lpUser->m_Index, 0, 0);
			}
		}
		if(rType == ewBonus)
		{
			//lpUser->Bonus += rCount;
			

			lpUser->GameShop.WCoinC += rCount;
			gGameShop.GDSaveUserInfo(lpUser->m_Index);

			//g_ExUser.UpdateCharInfo(aIndex);
			ExUserDataSend(aIndex);
		}
#if(CUSTOM_NPC_BUFFER==TRUE)
		if(rType == ewBuff)
		{
			int idBuffer = AT_NPC_BUFF_EXP;
			lpUser->ExpBuffTime = rCount;

			if(rItemType == 1)
			{
				idBuffer = AT_NPC_BUFF_EXP;
				lpUser->ExpBuffTime = rCount;
			}
			if(rItemType == 2)
			{
				idBuffer = AT_NPC_BUFF_DAMAGE;
				lpUser->DamageBuffTime = rCount;
			}
			if(rItemType == 3)
			{
				idBuffer = AT_NPC_BUFF_DEFENCE;
				lpUser->DefenceBuffTime = rCount;
			}
			if(rItemType == 4)
			{
				idBuffer = AT_NPC_BUFF_EXL_CRIT;
				lpUser->BattleBuffTime = rCount;
			}
			if(rItemType == 5)
			{
				idBuffer = AT_NPC_BUFF_DROP;
				lpUser->DropBuffTime = rCount;
			}
			if(rItemType == 6)
			{
				idBuffer = AT_NPC_BUFF_DOUBLE;
				lpUser->DoubleBuffTime = rCount;
			}

			gObjApplyBuffEffectDuration(lpUser, idBuffer, 0, 0, 0, 0, rCount);

			//g_BuffManagerEx.AddedBuff(aIndex, rItemType, rCount);
		}
#endif
	}

	lpUser->ExWQuestNum[a]++;
	lpUser->ExWQuestStart[a] = false;
	this->GC_MainInfo(aIndex);
	//g_BuffManagerEx.GC_QuestBuffInfo(aIndex);
}
// ----------------------------------------------------------------------------------------------

bool ExWinQuestSystem::NewDrop(int aIndexMob, int aIndexUser)
{
	LPOBJ lpUser = &gObj[aIndexUser];
	LPOBJ lpMonster = &gObj[aIndexMob];

	switch(lpMonster->Class)
	{
	case 78:
	case 53:
	case 79:
	case 80:
	case 82:
	case 502:
	case 493:
	case 494:
	case 495:
	case 496:
	case 497:
	case 498:
	case 499:
	case 500:
	case 501:
		{
			return false;
		}
		break;
	}

	for( int i = 0; i < this->iDropLoaded; i++ )
	{
		int a = this->m_Drop[i].iAct;

		if(a < 0 || a >= EW_MAX_ACT)
		{
			continue;
		}

		if(lpUser->ExWQuestNum[a] >= this->m_Drop[i].iNeedQuest)
		{
			if( lpMonster->Level >= this->m_Drop[i].MonsterMinLevel && lpMonster->Level <= this->m_Drop[i].MonsterMaxLevel )
			{
				if( lpMonster->MapNumber == this->m_Drop[i].MonsterMap || this->m_Drop[i].MonsterMap == -1 )
				{
					if( rand() % 10000 < this->m_Drop[i].ItemDropRate )
					{
						int iLuck	= 0;
						int iSkill	= 0;
						int iOption	= 0;
						int iLevel	= 0;

						// ----
						if( this->m_Drop[i].ItemMaxLevel == this->m_Drop[i].ItemMinLevel )
						{
							iLevel = this->m_Drop[i].ItemMinLevel;
						}
						else
						{
							iLevel = this->m_Drop[i].ItemMinLevel + (rand() % (this->m_Drop[i].ItemMaxLevel - this->m_Drop[i].ItemMinLevel + 1));
						}

						// ----
						if( this->m_Drop[i].ItemLuck == 1 )
						{
							if( rand() % 100 < 50 )
							{
								iLuck = 1;
							}
						}
						// ----
						if( this->m_Drop[i].ItemSkill == 1 )
						{
							if( rand() % 100 < 50 )
							{
								iSkill = 1;
							}
						}
						// ----
						if( this->m_Drop[i].ItemMaxOption != 0 )
						{
							if( rand() % 100 < 50 )
							{
								iOption = rand() % this->m_Drop[i].ItemMaxOption + 1;
							}
						}

						ItemSerialCreateSend(lpUser->m_Index, lpMonster->MapNumber, lpMonster->X, lpMonster->Y, ITEMGET(this->m_Drop[i].ItemType, this->m_Drop[i].ItemIndex), iLevel, this->m_Drop[i].ItemDur, iOption, iLuck, iSkill, gObjMonsterTopHitDamageUser(lpMonster), this->m_Drop[i].ItemExcellent, 0);
					
						return true;
					}
				}
			}
		}
	}

	return false;
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::SaveQuest(int aIndex, LPBYTE buf)
{
	return;
	LPOBJ lpUser = &gObj[aIndex];

	int n = 0;
	BYTE Start = 0;
	WORD Number = 0;
	WORD Count = 0;

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		Start = lpUser->ExWQuestStart[a];
		buf[n] = Start;
		n++;
		WORD Number = lpUser->ExWQuestNum[a];
		buf[n] = SET_NUMBERH(Number);
		n++;
		buf[n] = SET_NUMBERL(Number);
		n++;
		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			Count = lpUser->ExWQuestCount[a][m];
			buf[n] = SET_NUMBERH(Count);
			n++;
			buf[n] = SET_NUMBERL(Count);
			n++;
		}
	}

#if(EW_DEBUG==TRUE)
	LogAddC(2, "SaveQuest: %d", n);
#endif
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::LoadQuest(int aIndex, LPBYTE buf)
{
	return;
	LPOBJ lpUser = &gObj[aIndex];
	int n = 0;

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		lpUser->ExWQuestStart[a] = buf[n];
		n++;
		lpUser->ExWQuestNum[a] = MAKE_NUMBERW(buf[n], buf[n+1]);
		n+=2;
		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			lpUser->ExWQuestCount[a][m] = MAKE_NUMBERW(buf[n], buf[n+1]);
			n+=2;
		}
	}

#if(EW_DEBUG==TRUE)
	LogAddC(2, "LoadQuest: %d", n);
#endif
}
// ----------------------------------------------------------------------------------------------
#endif