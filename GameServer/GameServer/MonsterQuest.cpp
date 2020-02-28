#include "StdAfx.h"
#include "user.h"
#include "MonsterQuest.h"
#include "..\include\ReadScript.h"
#include "GameMain.h"
#include "logproc.h"
#include "Message.h"
#include "Functions.h"
#include "DSProtocol.h"
#include "ExUser.h"
// -------------------------------------------------------------------------------

MonsterQuest gMonsterQuest;
// -------------------------------------------------------------------------------

MonsterQuest::MonsterQuest()
{
	this->Init();
}
// -------------------------------------------------------------------------------

MonsterQuest::~MonsterQuest()
{
	// ----
}
// -------------------------------------------------------------------------------

void MonsterQuest::Init()
{
	ZeroMemory(&this->MonsterData,sizeof(this->MonsterData));
	ZeroMemory(&this->RewardData,sizeof(this->RewardData));
	// ----
	this->QuestCount = 0;
}
// -------------------------------------------------------------------------------

void MonsterQuest::Load()
{
	this->Init();
	this->Read(gDirPath.GetNewPath("ExData\\MonsterQuest.ini"));
}
// -------------------------------------------------------------------------------

void MonsterQuest::Read(char *File)
{
	SMDFile = fopen(File, "r");
	if ( SMDFile == NULL )
	{
		MsgBox(lMsg.Get(MSGGET(0, 112)), File);
		return;
	}

	int Token;
	int type = -1;

	int Category = -1;

	while ( true )
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

				//if ( !strcmp("end", TokenString ) )
				//{
				//	break;
				//}

		Category = (int)TokenNumber;

		//while(true)
		{

			//Token = GetToken();

			//if ( !strcmp("end", TokenString ) )
			//{
			//	break;
			//}



			if(Category == 0)	// Config
			{

				Token = GetToken();
				this->Enable = TokenNumber;

				Token = GetToken();
				this->NPC_Class = TokenNumber;

				Token = GetToken();
				this->NPC_Map = TokenNumber;

				Token = GetToken();
				this->NPC_X = TokenNumber;

				Token = GetToken();
				this->NPC_Y = TokenNumber;

			//char p[50];
			//sprintf(p,"%d %d %d %d %d",Enable,NPC_Class,NPC_Map,NPC_X,NPC_Y);
			//MessageBox(0,p,p,0);

				//break;
			}
			else if(true) //Quest Base
			{
				//MissionData
				int MissionGroupCount = 0;

				while(true)	
				{
					if( MissionGroupCount >= MAX_MISSION_QUEST )
					{
						break;
					}

					Token = GetToken();

					//if ( !strcmp("end", TokenString ) )
					//{
					//	break;
					//}

					this->MonsterData[this->QuestCount][MissionGroupCount].Active = TokenNumber;

					Token = GetToken();
					this->MonsterData[this->QuestCount][MissionGroupCount].Mission = TokenNumber;

					Token = GetToken();
					this->MonsterData[this->QuestCount][MissionGroupCount].Procent = TokenNumber;

					Token = GetToken();
					this->MonsterData[this->QuestCount][MissionGroupCount].Count = TokenNumber;

					MissionGroupCount++;
				}

				//Reward Data
				int RewardGroupData = 0;

				while(true)	
				{
					if( RewardGroupData >= MAX_REWARD_QUEST )
					{
						break;
					}

					Token = GetToken();

					//if ( !strcmp("end", TokenString ) )
					//{
					//	break;
					//}

					this->RewardData[this->QuestCount][RewardGroupData].Active = TokenNumber;

					Token = GetToken();
					this->RewardData[this->QuestCount][RewardGroupData].Reward = TokenNumber;

					Token = GetToken();
					this->RewardData[this->QuestCount][RewardGroupData].RewardID = TokenNumber;

					Token = GetToken();
					this->RewardData[this->QuestCount][RewardGroupData].Level = TokenNumber;

					Token = GetToken();
					this->RewardData[this->QuestCount][RewardGroupData].Skill = TokenNumber;

					Token = GetToken();
					this->RewardData[this->QuestCount][RewardGroupData].Luck = TokenNumber;

					Token = GetToken();
					this->RewardData[this->QuestCount][RewardGroupData].Option = TokenNumber;

					Token = GetToken();
					this->RewardData[this->QuestCount][RewardGroupData].Exellent = TokenNumber;

					Token = GetToken();
					this->RewardData[this->QuestCount][RewardGroupData].Ancent = TokenNumber;

					RewardGroupData++;
				}

				this->QuestCount++;
			}
		}
    }

	fclose(SMDFile);
}
// -------------------------------------------------------------------------------

bool MonsterQuest::NPCDialog(int NpcIndex, int UserIndex)
{
	if(!this->Enable) return false;

	LPOBJ lpUser = &gObj[UserIndex];
	LPOBJ lpNpc = &gObj[NpcIndex];

	//LogAddC(2,"NPC: %d Code",gObj[UserIndex].Class);

	if(lpNpc->Class == this->NPC_Class && lpNpc->MapNumber == this->NPC_Map && lpNpc->X == this->NPC_X && lpNpc->Y == this->NPC_Y)
	{
		int UserQuest = lpUser->m_MonsterQuest.QuestNumber;
		//Debug LogAdd UserQuest >= QuestCount
		//LogAddC(2,"%d %d",UserQuest,this->QuestCount);
		if(UserQuest >= this->QuestCount)
		{
			MessageChat(UserIndex,"Monster Quest Finish");
			return false;
		}

		this->GCWindowsOpen(UserIndex);
		return true;
	}
	return false;
}
// -------------------------------------------------------------------------------

void MonsterQuest::MissionKill(int MonsterIndex, int UserIndex)
{
	if(!this->Enable) return;

	LPOBJ lpUser = &gObj[UserIndex];
	LPOBJ lpMonster = &gObj[MonsterIndex];

	//int UserIndex = UserIndex;
	int UserQuest = lpUser->m_MonsterQuest.QuestNumber;

	for(int n = 0; n < MAX_MISSION_QUEST; n++)
	{
		//LogAddC(2,"Monster Class: %d",lpMonster->Class);
		if( lpMonster->Class == this->MonsterData[UserQuest][n].Mission)
		{
			if(lpUser->m_MonsterQuest.KillCount[n] >= this->MonsterData[UserQuest][n].Count)
			{
				continue;
			}

			lpUser->m_MonsterQuest.KillCount[n]++;
			
			this->GCMonsterKill(UserIndex, n);

			if(this->CheckDoneQuest(UserIndex) == true)
			{
				MessageChat(lpUser->m_Index,"@[MonsterQuest]: Mission accomplished!");
				ExFireCracker(lpUser->m_Index, lpUser->X, lpUser->Y);
			}

			break;
		}
	}
}
// -------------------------------------------------------------------------------

void MonsterQuest::MissionReward(int UserIndex)
{
	if(!this->Enable) return;

	if(this->CheckDoneQuest(UserIndex) == false) return;

	LPOBJ lpUser = &gObj[UserIndex];

	int UserQuest = lpUser->m_MonsterQuest.QuestNumber;

	for(int n = 0; n < MAX_REWARD_QUEST; n++)
	{
		if(this->RewardData[UserQuest][n].Active)
		{
			switch(this->RewardData[UserQuest][n].Active)
			{
			case eZen:
				{
					MapC[lpUser->MapNumber].MoneyItemDrop(this->RewardData[UserQuest][n].Reward, lpUser->X, lpUser->Y);	//Скорее всего нужно будет переписать
				}
				break;
			case eFreePoints:
				{
					MessageChat(lpUser->m_Index,"@[MonsterQuest]: FreePoints %d!",this->RewardData[UserQuest][n].Reward);
					lpUser->ExFreePoints += this->RewardData[UserQuest][n].Reward;
					lpUser->LevelUpPoint += this->RewardData[UserQuest][n].Reward;
				}
				break;
			case eItem:
				{
					int rItem = ITEMGET(this->RewardData[UserQuest][n].Reward,this->RewardData[UserQuest][n].RewardID);
					int rLevel = this->RewardData[UserQuest][n].Level;
					int rSkill = this->RewardData[UserQuest][n].Skill;
					int rLuck = this->RewardData[UserQuest][n].Luck;
					int rOption = this->RewardData[UserQuest][n].Option;
					int rExellent = this->RewardData[UserQuest][n].Exellent;
					int rAncent = this->RewardData[UserQuest][n].Ancent;
					ItemSerialCreateSend(lpUser->m_Index,lpUser->MapNumber,lpUser->X,lpUser->Y,rItem,rLevel,0,rSkill,rLuck,rOption,lpUser->m_Index,rExellent,rAncent);	//?
				}
				break;
			case eWCoin:
				{
					MessageChat(lpUser->m_Index,"@[MonsterQuest]: WCoinC %d!",this->RewardData[UserQuest][n].Reward);
					lpUser->GameShop.WCoinC += this->RewardData[UserQuest][n].Reward;
					gGameShop.GDSaveUserInfo(lpUser->m_Index);
				}
				break;
			case eWCoinP:
				{
					MessageChat(lpUser->m_Index,"@[MonsterQuest]: WCoinP %d!",this->RewardData[UserQuest][n].Reward);
					lpUser->GameShop.WCoinP += this->RewardData[UserQuest][n].Reward;
					gGameShop.GDSaveUserInfo(lpUser->m_Index);
				}
				break;
			case eGoblin:
				{
					MessageChat(lpUser->m_Index,"@[MonsterQuest]: Goblin %d!",this->RewardData[UserQuest][n].Reward);
					lpUser->GameShop.GoblinPoint += this->RewardData[UserQuest][n].Reward;
					gGameShop.GDSaveUserInfo(lpUser->m_Index);
				}
				break;
			case eCredit:
				{
					MessageChat(lpUser->m_Index,"@[MonsterQuest]: Credit %d!",this->RewardData[UserQuest][n].Reward);
					lpUser->ExCred += this->RewardData[UserQuest][n].Reward;
					ExUserDataSend(UserQuest);
				}
				break;
			}
		}
	}

	lpUser->m_MonsterQuest.QuestNumber++;

	for(int i=0; i<MAX_MISSION_QUEST; i++)
	{
		lpUser->m_MonsterQuest.KillCount[i] = 0;
	}

	this->GCMission(UserIndex);

	ExFireCracker(lpUser->m_Index, lpUser->X, lpUser->Y);
}
// -------------------------------------------------------------------------------

bool MonsterQuest::CheckDoneQuest(int UserIndex)
{
	LPOBJ lpUser = &gObj[UserIndex];

	bool DoneQuest = true;

	int QuestNum = lpUser->m_MonsterQuest.QuestNumber;

	for(int i=0; i < MAX_MISSION_QUEST; i++)
	{
		if(lpUser->m_MonsterQuest.KillCount[i] < this->MonsterData[QuestNum][i].Count)
		{
			DoneQuest = false;
			break;
		}
	}

	return DoneQuest;
}
// -------------------------------------------------------------------------------

void MonsterQuest::GCMonsterKill(int aIndex, int n)
{
	
	LPOBJ lpUser = &gObj[aIndex];
	GCMonsterQuestKill rSend;	//Добавить структуру
	ZeroMemory(&rSend,sizeof(rSend));	
	rSend.h.set((LPBYTE)&rSend, 0xFB, 18, sizeof(rSend));
	rSend.MissionNum = n;
	rSend.MissionKill = lpUser->m_MonsterQuest.KillCount[n];	//нуэно урезать пакет можно прост ++ в клиенте
	DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
	//MessageChat(aIndex,"Kill: %d", lpUser->m_MonsterQuest.KillCount[n]);
}
// -------------------------------------------------------------------------------

void MonsterQuest::GCMission(int UserIndex)
{

	LPOBJ lpUser = &gObj[UserIndex];

	GCMonsterQuestDialog rSend;	//Добавить структуру
	ZeroMemory(&rSend,sizeof(rSend));
	rSend.h.set((LPBYTE)&rSend, 0xFB, 19, sizeof(rSend));
	int QuestNum = lpUser->m_MonsterQuest.QuestNumber;
	rSend.NumQuest = QuestNum;
	rSend.MaxQuest = this->QuestCount;
	// Можно улучшить код и сохранить больше трафика
	for(int i=0; i < MAX_MISSION_QUEST; i++)
	{
		rSend.KillCount[i] = lpUser->m_MonsterQuest.KillCount[i];
		// ----
		rSend.MonsterDataGC[i].Active	= this->MonsterData[QuestNum][i].Active;

		LPMONSTER_ATTRIBUTE pMonster = gMAttr.GetAttr(this->MonsterData[QuestNum][i].Mission);

		strncpy(rSend.MonsterDataGC[i].Mission,pMonster->m_Name,20);

		//rSend.MonsterDataGC[i].Mission	= this->MonsterData[QuestNum][i].Mission;
		//rSend.MonsterDataGC[i].Procent	= this->MonsterData[QuestNum][i].Procent;
		rSend.MonsterDataGC[i].Count	= this->MonsterData[QuestNum][i].Count;
	}

	for(int i=0; i < MAX_REWARD_QUEST; i++)
	{
		rSend.RewardDataGC[i].Active	= this->RewardData[QuestNum][i].Active;
		rSend.RewardDataGC[i].Reward	= this->RewardData[QuestNum][i].Reward;
		rSend.RewardDataGC[i].RewardID	= this->RewardData[QuestNum][i].RewardID;
		rSend.RewardDataGC[i].Level		= this->RewardData[QuestNum][i].Level;
		rSend.RewardDataGC[i].Skill		= this->RewardData[QuestNum][i].Skill;
		rSend.RewardDataGC[i].Luck		= this->RewardData[QuestNum][i].Luck;
		rSend.RewardDataGC[i].Option	= this->RewardData[QuestNum][i].Option;
		rSend.RewardDataGC[i].Exellent	= this->RewardData[QuestNum][i].Exellent;
		rSend.RewardDataGC[i].Ancent	= this->RewardData[QuestNum][i].Ancent;
	}

	//LogAddC(2,"rSend = %d",sizeof(rSend));

	DataSend(UserIndex,(LPBYTE)&rSend,sizeof(rSend));
}
// -------------------------------------------------------------------------------

void MonsterQuest::GCConnectUser(int UserIndex)
{
	//GCMonsterQuestConnect	rSend;	//Добавить структуру
	//ZeroMemory(&rSend,sizeof(rSend));
	//rSend.h.set((LPBYTE)&rSend, 0xFB, 19, sizeof(rSend));

	//rSend.UserQuest.QuestNumber = lpUser->m_MonsterQuest.QuestNumber;

	//for(int i=0; i < MAX_MISSION_QUEST; i++)
	//{
	//	rSend.UserQuest.KillCount[i] = lpUser->m_MonsterQuest.KillCount[i];
	//}

	//DataSend(lpUser->m_Index,(LPBYTE)&rSend,sizeof(rSend));
	// ----
	this->GCMission(UserIndex);
}
// -------------------------------------------------------------------------------

void MonsterQuest::GCWindowsOpen(int UserIndex)
{
	LPOBJ lpUser = &gObj[UserIndex];

	GCQuestWindowsOpen rSend;	//Добавить структуру
	ZeroMemory(&rSend,sizeof(rSend));
	rSend.h.set((LPBYTE)&rSend, 0xFB, 20, sizeof(rSend));
	rSend.Open = 1;
	DataSend(lpUser->m_Index,(LPBYTE)&rSend,sizeof(rSend));
}
// -------------------------------------------------------------------------------