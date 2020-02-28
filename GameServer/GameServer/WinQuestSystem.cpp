#include "StdAfx.h"
#include "user.h"
#include "WinQuestSystem.h"
#include "Functions.h"
#include "logproc.h"
#include "..\\common\\winutil.h"
#include "MonsterAttr.h"
#include "GameMain.h"
#include "Message.h"
#include "..\include\ReadScript.h"
#include "ExUser.h"
#include "DSProtocol.h"
#include "Functions.h"
#include "DBSockMng.h"
#include "ExLicense.h"

//#ifdef WIN_QUEST_SYSTEM

// ---------------------------------------------------------------------------------------------

cWinQuestSystem gWinQuestSystem;

// ---------------------------------------------------------------------------------------------

cWinQuestSystem::cWinQuestSystem()
{
	this->Enable = true;
	ZeroMemory(this->Data, sizeof(this->Data));
	ZeroMemory(this->Count, sizeof(this->Count));
}

// ---------------------------------------------------------------------------------------------

void cWinQuestSystem::Init()
{
	if(!g_ExLicense.user.WinQuest)
	{
		return;
	}

	this->Enable = GetPrivateProfileInt("ExTeam","Enable",0,WIN_QUEST_SYSTEM_CFG);
	this->NPC = GetPrivateProfileInt("ExTeam","NPC",0,WIN_QUEST_SYSTEM_CFG);

	this->Load(0, WIN_QUEST_SYSTEM_DIR1);
	this->Load(1, WIN_QUEST_SYSTEM_DIR2);
	this->Load(2, WIN_QUEST_SYSTEM_DIR3);
	this->Load(3, WIN_QUEST_SYSTEM_DIR4);
	this->Load(4, WIN_QUEST_SYSTEM_DIR5);
	this->Load(5, WIN_QUEST_SYSTEM_DIR6);
	this->Load(6, WIN_QUEST_SYSTEM_DIR7);
	this->Load(7, WIN_QUEST_SYSTEM_DIR8);
	this->Load(8, WIN_QUEST_SYSTEM_DIR9);
	this->Load(9, WIN_QUEST_SYSTEM_DIR10);
}

// ---------------------------------------------------------------------------------------------

void cWinQuestSystem::Load(int iQuest, char *Dir)
{
	SMDFile = fopen(Dir, "r");

	if ( SMDFile == NULL )
	{
		MsgBox(Dir);
		this->Enable = 0;
		return;
	}

	int Token;

	while ( true )
	{
	    Token = GetToken();

        if( Token == END)
		{
            break;
		}

		if ( strcmp("end", TokenString ) == 0)
		{
			break;
		}

		strncpy(this->Data[iQuest][this->Count[iQuest]].Name,TokenString,50);

		for (int k=0;k<5;k++)
		{
			Token=GetToken();
			this->Data[iQuest][this->Count[iQuest]].MissionType[k] = TokenNumber;

			Token=GetToken();
			this->Data[iQuest][this->Count[iQuest]].MissionMain[k] = TokenNumber;

			Token=GetToken();
			this->Data[iQuest][this->Count[iQuest]].MissionLvL[k] = TokenNumber;

			Token=GetToken();
			this->Data[iQuest][this->Count[iQuest]].MissionLuck[k] = TokenNumber;

			Token=GetToken();
			this->Data[iQuest][this->Count[iQuest]].MissionExl[k] = TokenNumber;

			Token=GetToken();
			this->Data[iQuest][this->Count[iQuest]].MissionAnc[k] = TokenNumber;
		}

		for (int k=0;k<5;k++)
		{
			Token=GetToken();
			this->Data[iQuest][this->Count[iQuest]].RewardType[k] = TokenNumber;

			Token=GetToken();
			this->Data[iQuest][this->Count[iQuest]].RewardMain[k] = TokenNumber;

			Token=GetToken();
			this->Data[iQuest][this->Count[iQuest]].RewardLvL[k] = TokenNumber;

			Token=GetToken();
			this->Data[iQuest][this->Count[iQuest]].RewardLuck[k] = TokenNumber;

			Token=GetToken();
			this->Data[iQuest][this->Count[iQuest]].RewardExl[k] = TokenNumber;

			Token=GetToken();
			this->Data[iQuest][this->Count[iQuest]].RewardAnc[k] = TokenNumber;
		}

		for (int k=0;k<5;k++)
		{
			Token=GetToken();
			this->Data[iQuest][this->Count[iQuest]].PriceType[k] = TokenNumber;

			Token=GetToken();
			this->Data[iQuest][this->Count[iQuest]].PriceMain[k] = TokenNumber;

			Token=GetToken();
			this->Data[iQuest][this->Count[iQuest]].PriceLvL[k] = TokenNumber;
		}

		Token=GetToken();
		this->Data[iQuest][this->Count[iQuest]].NeedLevel = TokenNumber;

		Token=GetToken();
		this->Data[iQuest][this->Count[iQuest]].NeedReset = TokenNumber;

		Token=GetToken();
		this->Data[iQuest][this->Count[iQuest]].NeedGrand = TokenNumber;

		Token = GetToken();
		strncpy(this->Data[iQuest][this->Count[iQuest]].Info,TokenString,256);

		this->Count[iQuest]++;

	}
    
	fclose(SMDFile);
}

// ---------------------------------------------------------------------------------------------

void cWinQuestSystem::NPCClicker(LPOBJ lpNpc, LPOBJ lpObj)
{
	if(!this->Enable) return;

	if(lpNpc->Class != this->NPC) return;

	this->SendPacket(lpObj->m_Index,1);
}

// ---------------------------------------------------------------------------------------------

void cWinQuestSystem::MonsterKiller(LPOBJ lpObj, LPOBJ lpTargetObj)	//lpTargetObj - тот кто убивает
{
	if(!this->Enable) return;

	int aIndex = lpTargetObj->m_Index;

	for(int i=0; i < MAX_WIN_QUEST; i++)
	{
		int n = this->WinQ[aIndex].Num[i];

		//Monsterr killer
		if(this->WinQ[aIndex].Start[i] == 1)
		{
			for(int k = 0; k < 5; k++)
			{
				if(this->Data[i][n].MissionType[k] == 1)
				{
					if(this->Data[i][n].MissionMain[k] == lpObj->Class)
					{
						if(this->Data[i][n].MissionLvL[k] > this->WinQ[aIndex].Count[i][k])
						{
							this->WinQ[aIndex].Count[i][k]++;
							this->SendInfoPacket(aIndex);
						}
					}
				}
			}
		}

		//Item Drop Rate
		if(this->WinQ[aIndex].Start[i] == 1)
		{
			for(int k = 0; k < 5; k++)
			{
				if(this->Data[i][n].MissionType[k] == 2)
				{
					if ( lpTargetObj->MapNumber == this->Data[i][n].MissionLuck[k] || this->Data[i][n].MissionLuck[k] == -1 )
					{
						if ( (rand()%10000) < this->Data[i][n].MissionExl[k] )
						{
							if(this->Data[i][n].MissionLvL[k] > this->WinQ[aIndex].Count[i][k])
							{
								//CreateItemDr
								ItemSerialCreateSend(aIndex,lpObj->MapNumber,lpObj->X,lpObj->Y,this->Data[i][n].MissionMain[k],0,0,0,0,0,aIndex,0,0);
								break;
							}
						}
					}
				}
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------

void cWinQuestSystem::SendPacket(int aIndex, BYTE OpenWind)
{
	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];
	CGWinQuestSystemTable qSend;

	memset(&qSend,0,sizeof(qSend));
	PHeadSubSetW((LPBYTE)&qSend, 0xFA, 0x02, sizeof(qSend));
	
	for(int i=0; i < MAX_WIN_QUEST; i++)
	{
		BYTE Accept = 1;
		BYTE Reward = 1;

		int n = this->WinQ[aIndex].Num[i];

		strncpy(qSend.exQuest[i].Name,this->Data[i][n].Name,40);
		strncpy(qSend.exQuest[i].Info,this->Data[i][n].Info,200);

		qSend.exQuest[i].n = n;
		qSend.exQuest[i].e = this->Count[i];

		//MsgNormal(aIndex,"%d / %d",n,this->Count[i]);

		if(n >= this->Count[i])
		{
			qSend.exQuest[i].Finish = true;
		}
		else
		{
			qSend.exQuest[i].Finish = false;
		}

		qSend.exQuest[i].start = this->WinQ[aIndex].Start[i];

		// ----

		for(int k = 0; k < 5; k++)
		{
			qSend.exQuest[i].MissionType[k] = this->Data[i][n].MissionType[k];
			qSend.exQuest[i].MissionMain[k] = this->Data[i][n].MissionMain[k];
			qSend.exQuest[i].MissionLvL[k] = this->Data[i][n].MissionLvL[k];
			qSend.exQuest[i].MissionLuck[k] = this->Data[i][n].MissionLuck[k];
			qSend.exQuest[i].MissionExl[k] = this->Data[i][n].MissionExl[k];
			qSend.exQuest[i].MissionAnc[k] = this->Data[i][n].MissionAnc[k];

			if(this->Data[i][n].MissionType[k] == 1)	//Kill Mission
			{
				LPMONSTER_ATTRIBUTE lpMonsterAttr = gMAttr.GetAttr(this->Data[i][n].MissionMain[k]);
				strncpy(qSend.exQuest[i].MissionName[k], lpMonsterAttr->m_Name,20);

				if(this->WinQ[aIndex].Count[i][k] < this->Data[i][n].MissionLvL[k])
				{
					Reward = 0;
					qSend.exQuest[i].MissionCheck[k] = 0;
				}
				else
				{
					qSend.exQuest[i].MissionCheck[k] = 1;
				}
			}

			if(this->Data[i][n].MissionType[k] == 2)
			{
				LPITEM_ATTRIBUTE pItem = &ItemAttribute[this->Data[i][n].MissionMain[k]];
				strncpy(qSend.exQuest[i].MissionName[k], pItem->Name,20);
				if(this->WinQ[aIndex].Count[i][k] < this->Data[i][n].MissionLvL[k])
				{
					Reward = 0;
					qSend.exQuest[i].MissionCheck[k] = 0;
				}
				else
				{
					qSend.exQuest[i].MissionCheck[k] = 1;
				}
			}

			if(this->Data[i][n].MissionType[k] == 3)
			{
				LPITEM_ATTRIBUTE pItem = &ItemAttribute[this->Data[i][n].MissionMain[k]];
				strncpy(qSend.exQuest[i].MissionName[k], pItem->Name,20);

				if(!CheckItemUser(aIndex, i, k))
				{
					Reward = 0;
					qSend.exQuest[i].MissionCheck[k] = 0;
				}
				else
				{
					qSend.exQuest[i].MissionCheck[k] = 1;
				}
			}

			qSend.exQuest[i].Count[k] = this->WinQ[aIndex].Count[i][k];
		}

		// ----

		for(int k = 0; k < 5; k++)
		{
			qSend.exQuest[i].RewardType[k] = this->Data[i][n].RewardType[k];
			qSend.exQuest[i].RewardMain[k] = this->Data[i][n].RewardMain[k];
			qSend.exQuest[i].RewardLvL[k] = this->Data[i][n].RewardLvL[k];
			qSend.exQuest[i].RewardLuck[k] = this->Data[i][n].RewardLuck[k];
			qSend.exQuest[i].RewardExl[k] = this->Data[i][n].RewardExl[k];
			qSend.exQuest[i].RewardAnc[k] = this->Data[i][n].RewardAnc[k];
		}

		// ----
		
		for(int k = 0; k < 5; k++)
		{
			qSend.exQuest[i].PriceType[k] = this->Data[i][n].PriceType[k];
			qSend.exQuest[i].PriceMain[k] = this->Data[i][n].PriceMain[k];
			qSend.exQuest[i].PriceLvL[k] = this->Data[i][n].PriceLvL[k];

			qSend.exQuest[i].PriceCheck[k] = 1;

			//0 - off; 1 - zen; 2 - WcoinC; 3 - WcoinP; 4 - Goblin; 5 - Cred; 6 - Item

			if(this->Data[i][n].PriceType[k] == 1) //1 - zen
			{
				qSend.exQuest[i].PriceDone[k] = lpObj->Money;

				if(this->Data[i][n].PriceMain[k] > lpObj->Money)
				{
					Accept = 0;
					qSend.exQuest[i].PriceCheck[k] = 0;
				}
			}
			if(this->Data[i][n].PriceType[k] == 2) //2 - WcoinC
			{
				qSend.exQuest[i].PriceDone[k] = lpObj->GameShop.WCoinC;
				if(this->Data[i][n].PriceMain[k] > lpObj->GameShop.WCoinC)
				{
					Accept = 0;
					qSend.exQuest[i].PriceCheck[k] = 0;
				}
			}
			if(this->Data[i][n].PriceType[k] == 3) //3 - WcoinP
			{
				qSend.exQuest[i].PriceDone[k] = lpObj->GameShop.WCoinP;
				if(this->Data[i][n].PriceMain[k] > lpObj->GameShop.WCoinP)
				{
					Accept = 0;
					qSend.exQuest[i].PriceCheck[k] = 0;
				}
			}
			if(this->Data[i][n].PriceType[k] == 4) //4 - Goblin
			{
				qSend.exQuest[i].PriceDone[k] = lpObj->GameShop.GoblinPoint;
				if(this->Data[i][n].PriceMain[k] > lpObj->GameShop.GoblinPoint)
				{
					Accept = 0;
					qSend.exQuest[i].PriceCheck[k] = 0;
				}
			}
			if(this->Data[i][n].PriceType[k] == 5) //5 - Cred
			{
				qSend.exQuest[i].PriceDone[k] = lpObj->ExCred;
				if(this->Data[i][n].PriceMain[k] > lpObj->ExCred)
				{
					Accept = 0;
					qSend.exQuest[i].PriceCheck[k] = 0;
				}
			}
			if(this->Data[i][n].PriceType[k] == 6) //6 - Item
			{
				qSend.exQuest[i].PriceDone[k] = gObjGetItemCountInInventory(aIndex,this->Data[i][n].PriceMain[k],this->Data[i][n].PriceLvL[k]);
				if(gObjGetItemCountInInventory(aIndex,this->Data[i][n].PriceMain[k],this->Data[i][n].PriceLvL[k]) < 0)
				{
					Accept = 0;
					qSend.exQuest[i].PriceCheck[k] = 0;
				}
			}
		}

		// ----

		qSend.exQuest[i].NeedLevel = this->Data[i][n].NeedLevel;
		qSend.exQuest[i].NeedReset = this->Data[i][n].NeedReset;
		qSend.exQuest[i].NeedGrand = this->Data[i][n].NeedGrand;

		qSend.exQuest[i].LevelDone = lpObj->Level;
		if(this->Data[i][n].NeedLevel > lpObj->Level)
		{
			Accept = 0;
		}

		qSend.exQuest[i].ResetDone = lpObj->Reset;
		if(this->Data[i][n].NeedReset > lpObj->Reset)
		{
			Accept = 0;
		}

		qSend.exQuest[i].GrandDone = lpObj->GReset;
		if(this->Data[i][n].NeedGrand > lpObj->GReset)
		{
			Accept = 0;
		}

		qSend.exQuest[i].accept = Accept;
		qSend.exQuest[i].reward = Reward;
	}

	qSend.OpenWind = OpenWind;

	// ----

	qSend.Damage = this->WinQ[aIndex].Damage;
	qSend.Defence = this->WinQ[aIndex].Defence;
	qSend.Life = this->WinQ[aIndex].Life;
	qSend.SD = this->WinQ[aIndex].SD;
	qSend.Crit = this->WinQ[aIndex].Crit;
	qSend.Exel = this->WinQ[aIndex].Exel;
	qSend.Double = this->WinQ[aIndex].Double;
	qSend.Ignore = this->WinQ[aIndex].Ignore;
	qSend.Ref = this->WinQ[aIndex].Ref;
	qSend.Exp = this->WinQ[aIndex].Exp;
	qSend.Drop = this->WinQ[aIndex].Drop;	

	// ----

	DataSend(aIndex,(LPBYTE)&qSend,sizeof(qSend));
}

// ---------------------------------------------------------------------------------------------

void cWinQuestSystem::SendInfoPacket(int aIndex)
{
	CGWinQuestProcess rSend;

	ZeroMemory(&rSend,sizeof(rSend));
	PHeadSubSetW((LPBYTE)&rSend, 0xFA, 0x03, sizeof(rSend));

	for(int i=0; i < MAX_WIN_QUEST; i++)
	{
		int n = this->WinQ[aIndex].Num[i];
		for(int k=0;k<5;k++)
		{
			rSend.Count[i][k] = this->WinQ[aIndex].Count[i][k];

			if(this->WinQ[aIndex].Count[i][k] < this->Data[i][n].MissionLvL[k])
			{
				rSend.Check[i][k] = 0;
			}
			else
			{
				rSend.Check[i][k] = 1;
			}

			if(this->Data[i][n].MissionType[k] == 1)	//Kill Mission
			{
				if(this->WinQ[aIndex].Count[i][k] < this->Data[i][n].MissionLvL[k])
				{
					rSend.Check[i][k] = 0;
				}
				else
				{
					rSend.Check[i][k] = 1;
				}
			}

			if(this->Data[i][n].MissionType[k] == 2)	//Drop Mission
			{
				if(this->WinQ[aIndex].Count[i][k] < this->Data[i][n].MissionLvL[k])
				{
					rSend.Check[i][k] = 0;
				}
				else
				{
					rSend.Check[i][k] = 1;
				}
			}

			if(this->Data[i][n].MissionType[k] == 3)	//Item Mission
			{

				if(!CheckItemUser(aIndex, i, k))
				{
					rSend.Check[i][k] = 0;
				}
				else
				{
					rSend.Check[i][k] = 1;
				}
			}

		}
	}

	DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
}

// ---------------------------------------------------------------------------------------------

void cWinQuestSystem::RecvPacket(int aIndex, CGSendQuestResult * Date)
{
	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	int i = Date->Num;
	int n = this->WinQ[aIndex].Num[i];

	//-----------------------------------------------------------------------------------
	//	Quest Price Update
	//-----------------------------------------------------------------------------------

	if(Date->Result == 1)
	{
		for(int k = 0; k < 5; k++)
		{
			//0 - off; 1 - zen; 2 - WcoinC; 3 - WcoinP; 4 - Goblin; 5 - Cred; 6 - Item
			if(this->Data[i][n].PriceType[k] == 1) //1 - zen
			{
				lpObj->Money -= this->Data[i][n].PriceMain[k];
				GCMoneySend(aIndex,lpObj->Money);
			}
			if(this->Data[i][n].PriceType[k] == 2) //2 - WcoinC
			{
				lpObj->GameShop.WCoinC -= this->Data[i][n].PriceMain[k];
				gGameShop.GDSaveUserInfo(aIndex);
			}
			if(this->Data[i][n].PriceType[k] == 3) //3 - WcoinP
			{
				lpObj->GameShop.WCoinP -= this->Data[i][n].PriceMain[k];
				gGameShop.GDSaveUserInfo(aIndex);
			}
			if(this->Data[i][n].PriceType[k] == 4) //4 - Goblin
			{
				lpObj->GameShop.GoblinPoint -= this->Data[i][n].PriceMain[k];
				gGameShop.GDSaveUserInfo(aIndex);
			}
			if(this->Data[i][n].PriceType[k] == 5) //5 - Cred
			{
				lpObj->ExCred -= this->Data[i][n].PriceMain[k];
				ExUserDataSend(aIndex);

			}
			if(this->Data[i][n].PriceType[k] == 6) //6 - Item
			{
				gObjDeleteItemsCount(aIndex,this->Data[i][n].PriceMain[k],this->Data[i][n].PriceLvL[k],1);
			}
		}

		this->WinQ[aIndex].Start[Date->Num] = 1;

		this->SendPacket(aIndex,1);	//Need ReCode

	}

	//-----------------------------------------------------------------------------------
	//	Quest Reward Update
	//-----------------------------------------------------------------------------------

	if(Date->Result == 2)
	{
		for(int k = 0; k < 5; k++)
		{
			//0-off;1-zen;2-ExFreePoints;3-WcoinC;4-WcoinP;5-Goblin;6-Cred;7-Damage;8-Defence;9-Life;10-SD;11-CritDmg;12-ExlDmg;13-Double;14-Ignore;15-Ref;16-Exp;17-Drop;18-Item

			if(this->Data[i][n].RewardType[k] == 1)	//1-zen
			{
				if(lpObj->Money + this->Data[i][n].RewardMain[k] > 2000000000 )
				{
					lpObj->Money = 2000000000;
				}
				else
				{
					lpObj->Money += this->Data[i][n].RewardMain[k];
				}
				GCMoneySend(aIndex,lpObj->Money);
			}
			if(this->Data[i][n].RewardType[k] == 2)	//2-ExFreePoints
			{
				lpObj->ExFreePoints += this->Data[i][n].RewardMain[k];
			}
			if(this->Data[i][n].RewardType[k] == 3)	//3-WcoinC
			{
				lpObj->GameShop.WCoinC += this->Data[i][n].RewardMain[k];
				gGameShop.GDSaveUserInfo(aIndex);
			}
			if(this->Data[i][n].RewardType[k] == 4)	//4-WcoinP
			{
				lpObj->GameShop.WCoinP += this->Data[i][n].RewardMain[k];
				gGameShop.GDSaveUserInfo(aIndex);
			}
			if(this->Data[i][n].RewardType[k] == 5)	//5-WcoinP
			{
				lpObj->GameShop.GoblinPoint += this->Data[i][n].RewardMain[k];
				gGameShop.GDSaveUserInfo(aIndex);
			}
			if(this->Data[i][n].RewardType[k] == 6)	//6-Cred
			{
				lpObj->GameShop.GoblinPoint += this->Data[i][n].RewardMain[k];
				ExUserDataSend(aIndex);
			}
			if(this->Data[i][n].RewardType[k] == 7)	//7-Damage
			{
				this->WinQ[aIndex].Damage += this->Data[i][n].RewardMain[k];
			}	
			if(this->Data[i][n].RewardType[k] == 8)	//8-Defence
			{
				this->WinQ[aIndex].Defence += this->Data[i][n].RewardMain[k];
			}
			if(this->Data[i][n].RewardType[k] == 9)	//9-Life
			{
				this->WinQ[aIndex].Life += this->Data[i][n].RewardMain[k];
			}
			if(this->Data[i][n].RewardType[k] == 10)	//10-SD
			{
				this->WinQ[aIndex].SD += this->Data[i][n].RewardMain[k];
			}
			if(this->Data[i][n].RewardType[k] == 11)	//11-CritDmg
			{
				this->WinQ[aIndex].Crit += this->Data[i][n].RewardMain[k];
			}
			if(this->Data[i][n].RewardType[k] == 12)	//12-ExlDmg
			{
				this->WinQ[aIndex].Exel += this->Data[i][n].RewardMain[k];
			}
			if(this->Data[i][n].RewardType[k] == 13)	//13-Double
			{
				this->WinQ[aIndex].Double += this->Data[i][n].RewardMain[k];
			}
			if(this->Data[i][n].RewardType[k] == 14)	//14-Ignore
			{
				this->WinQ[aIndex].Ignore += this->Data[i][n].RewardMain[k];
			}
			if(this->Data[i][n].RewardType[k] == 15)	//15-Ref
			{
				this->WinQ[aIndex].Ref += this->Data[i][n].RewardMain[k];
			}
			if(this->Data[i][n].RewardType[k] == 16)	//16-Exp
			{
				this->WinQ[aIndex].Exp += this->Data[i][n].RewardMain[k];
			}
			if(this->Data[i][n].RewardType[k] == 17)	//17-Drop
			{
				this->WinQ[aIndex].Drop += this->Data[i][n].RewardMain[k];
			}		
			if(this->Data[i][n].RewardType[k] == 18)	//18-Item
			{
				ItemSerialCreateSend(aIndex,lpObj->MapNumber,lpObj->X,lpObj->Y,this->Data[i][n].RewardMain[k],this->Data[i][n].RewardLvL[k],0,0,this->Data[i][n].RewardLuck[k],0,aIndex,this->Data[i][n].RewardExl[k],this->Data[i][n].RewardAnc[k]);

				this->SendWindowsClose(aIndex);
			}		
		}

		this->WinQ[aIndex].Start[i] = 0;

		for(int k=0;k<5;k++)
		{
			this->WinQ[aIndex].Count[i][k] = 0;
		}

		this->WinQ[aIndex].Num[i]++;

		SendPacket(aIndex, 0);
	}
}

// ---------------------------------------------------------------------------------------------

void cWinQuestSystem::SendWindowsClose(int aIndex)
{
	CGWinClose rSend;

	ZeroMemory(&rSend,sizeof(rSend));
	PHeadSubSetW((LPBYTE)&rSend, 0xFA, 0x04, sizeof(rSend));

	rSend.Result = 1;

	DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
}

// ---------------------------------------------------------------------------------------------

bool cWinQuestSystem::MonsterDrop(int aIndex, short ItemType)
{
	if(!this->Enable) return true;

	for(int i=0; i < MAX_WIN_QUEST; i++)
	{
		int n = this->WinQ[aIndex].Num[i];

		if(this->WinQ[aIndex].Start[i] == 1)
		{
			for(int k = 0; k < 5; k++)
			{
				if(this->Data[i][n].MissionType[k] == 2)	//2-Drop
				{
					if(this->Data[i][n].MissionMain[k] == ItemType)
					{
						if(this->Data[i][n].MissionLvL[k] > this->WinQ[aIndex].Count[i][k])
						{
							this->WinQ[aIndex].Count[i][k]++;
							this->SendInfoPacket(aIndex);
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

// ---------------------------------------------------------------------------------------------

bool cWinQuestSystem::CheckItemUser(int aIndex, int QuestNum, int k)
{
	if(aIndex >= OBJMAX)
		return 0;

	int n = this->WinQ[aIndex].Num[QuestNum];

	LPOBJ lpObj = &gObj[aIndex];

	if(this->Data[QuestNum][n].MissionType[k] == 3)
	{
		short iType = this->Data[QuestNum][n].MissionMain[k];
		short iLvl = this->Data[QuestNum][n].MissionLvL[k];

		for (int i = INVETORY_WEAR_SIZE; i < INVENTORY_SIZE; i++)
		{
			if( lpObj->pInventory[i].m_Type == iType && 
				lpObj->pInventory[i].m_Level >= iLvl &&
				CheckOptions(0,lpObj->pInventory[i].m_Option2, this->Data[QuestNum][n].MissionLuck[k]) &&
				CheckOptions(0,lpObj->pInventory[i].m_NewOption, this->Data[QuestNum][n].MissionExl[k]) &&
				CheckOptions(0,lpObj->pInventory[i].m_SetOption, this->Data[QuestNum][n].MissionAnc[k]) )
			{
				return true;
			}
		}

	}

	return false;
}

// ---------------------------------------------------------------------------------------------

void cWinQuestSystem::DGSendInformation(int aIndex)
{
	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	GDQuestUser GDsend;

	ZeroMemory(&GDsend,sizeof(GDsend));

	PHeadSubSetB((LPBYTE)&GDsend, 0xE2, 0x02, sizeof(GDsend));

	strncpy(GDsend.Name,lpObj->Name,10);

	for(int i=0; i < MAX_WIN_QUEST; i++)
	{
		GDsend.Start[i] = this->WinQ[aIndex].Start[i];
		GDsend.Num[i] = this->WinQ[aIndex].Num[i];

		for(int k = 0; k < 5 ; k++)
		{
			GDsend.Count[i][k] = this->WinQ[aIndex].Count[i][k];
		}
	}

	GDsend.Damage = this->WinQ[aIndex].Damage;
	GDsend.Defence = this->WinQ[aIndex].Defence;
	GDsend.Life = this->WinQ[aIndex].Life;
	GDsend.SD = this->WinQ[aIndex].SD;
	GDsend.Crit = this->WinQ[aIndex].Crit;
	GDsend.Exel = this->WinQ[aIndex].Exel;
	GDsend.Double = this->WinQ[aIndex].Double;
	GDsend.Ignore = this->WinQ[aIndex].Ignore;
	GDsend.Ref = this->WinQ[aIndex].Ref;
	GDsend.Exp = this->WinQ[aIndex].Exp;
	GDsend.Drop = this->WinQ[aIndex].Drop;

	cDBSMng.Send( (char*)&GDsend, GDsend.h.size);
}

// ---------------------------------------------------------------------------------------------

void cWinQuestSystem::ReqQuestInfo(LPOBJ lpObj)
{
	if( !OBJMAX_RANGE(lpObj->m_Index) ) 
	{
		return;
	}

	// ----

	if( gObjIsConnected(lpObj) )
	{
		GDSelectQuest pMsg;			

		PHeadSubSetB((LPBYTE)&pMsg, 0xE2, 0x01, sizeof(pMsg));

		memcpy(pMsg.Name, lpObj->Name, 10);
		pMsg.aIndex = lpObj->m_Index;

		if( cDBSMng.Send((PCHAR)&pMsg, pMsg.h.size) )
		{
			return;
		}
	}
	return;
}

// ---------------------------------------------------------------------------------------------

void cWinQuestSystem::RecvQuestInfo(DGQuestUserInfo * Recv)
{
	int aIndex = Recv->aIndex;

	for(int i=0; i < MAX_WIN_QUEST; i++)
	{
		this->WinQ[aIndex].Start[i] = Recv->Start[i];
		this->WinQ[aIndex].Num[i] = Recv->Num[i];

		for(int k = 0; k < 5 ; k++)
		{
			this->WinQ[aIndex].Count[i][k] = Recv->Count[i][k];
		}
	}

	this->WinQ[aIndex].Damage = Recv->Damage;	//
	this->WinQ[aIndex].Defence = Recv->Defence;	//
	this->WinQ[aIndex].Life = Recv->Life;	//<--NoWork
	this->WinQ[aIndex].SD = Recv->SD;//<--NoWork
	this->WinQ[aIndex].Crit = Recv->Crit;//
	this->WinQ[aIndex].Exel = Recv->Exel;//
	this->WinQ[aIndex].Double = Recv->Double;//
	this->WinQ[aIndex].Ignore = Recv->Ignore;
	this->WinQ[aIndex].Ref = Recv->Ref;	//
	this->WinQ[aIndex].Exp = Recv->Exp;
	this->WinQ[aIndex].Drop = Recv->Drop;

	this->SendPacket(aIndex,0);
}

// ---------------------------------------------------------------------------------------------

void cWinQuestSystem::CharOptions(int aIndex)
{
	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	if(this->WinQ[aIndex].Ref > 0)
	{
		lpObj->DamageReflect += this->WinQ[aIndex].Ref;
		if(lpObj->DamageReflect >= 90)
		{
			lpObj->DamageReflect = 90;
		}
	}

	if(this->WinQ[aIndex].Damage > 0)
	{
		lpObj->m_AttackDamageMaxLeft += this->WinQ[aIndex].Damage;
		lpObj->m_AttackDamageMinLeft += this->WinQ[aIndex].Damage;
		lpObj->m_AttackDamageMaxRight += this->WinQ[aIndex].Damage;
		lpObj->m_AttackDamageMinRight += this->WinQ[aIndex].Damage;

		lpObj->m_MagicDamageMin += this->WinQ[aIndex].Damage;
		lpObj->m_MagicDamageMax += this->WinQ[aIndex].Damage;
	}

	if(this->WinQ[aIndex].Defence > 0)
	{
		lpObj->m_Defense += this->WinQ[aIndex].Defence;
		lpObj->m_MagicDefense += this->WinQ[aIndex].Defence;
	}

	if(this->WinQ[aIndex].Crit > 0)
	{
		lpObj->m_CriticalDamage += this->WinQ[aIndex].Crit;
		if(lpObj->m_CriticalDamage > 90)
		{
			lpObj->m_CriticalDamage = 90;
		}
	}

	if(this->WinQ[aIndex].Exel > 0)
	{
		lpObj->m_ExcelentDamage += this->WinQ[aIndex].Exel;
		if(lpObj->m_ExcelentDamage > 90)
		{
			lpObj->m_ExcelentDamage = 90;
		}
	}

	if(this->WinQ[aIndex].Double > 0)
	{
		lpObj->SetOpDoubleDamage += this->WinQ[aIndex].Double;
		if(lpObj->SetOpDoubleDamage > 90)
		{
			lpObj->SetOpDoubleDamage = 90;
		}
	}

	if(this->WinQ[aIndex].Ignore > 0)
	{
		lpObj->SetOpIgnoreDefense += this->WinQ[aIndex].Ignore;
		if(lpObj->SetOpIgnoreDefense > 90)
		{
			lpObj->SetOpIgnoreDefense = 90;
		}
	}

	if(this->WinQ[aIndex].Life > 0)
	{
		lpObj->AddLife += this->WinQ[aIndex].Life;
	}

	if(this->WinQ[aIndex].SD > 0)
	{
		lpObj->iAddShield += this->WinQ[aIndex].SD;
	}
}

// ---------------------------------------------------------------------------------------------

void cWinQuestSystem::ExpOption(int aIndex, __int64 &Exp)
{
	if(!this->Enable) return;
	
	if(this->WinQ[aIndex].Exp > 0)
	{
		Exp += ( Exp * this->WinQ[aIndex].Exp ) / 100;
	}
}

// ---------------------------------------------------------------------------------------------

void cWinQuestSystem::ZenOption(int aIndex, float &Money)
{
	if(!this->Enable) return;

	if(this->WinQ[aIndex].Drop > 0)
	{
		Money += ( Money * this->WinQ[aIndex].Exp ) / 100;
	}
}

// ---------------------------------------------------------------------------------------------

bool cWinQuestSystem::GetActive()
{
	return this->Enable;
}

//#endif
