#include "stdafx.h"
#include "MonsterQuest.h"
#include "Interface.h"
#include "Console.h"
#include "Object.h"
#include "Defines.h"
// -------------------------------------------------------------------------------

MonsterQuest gMonsterQuest;
// -------------------------------------------------------------------------------

MonsterQuest::MonsterQuest()
{
	ZeroMemory(&MonsterData,sizeof(MonsterData));
	ZeroMemory(&RewardData,sizeof(RewardData));
	// ----
	this->MyQuest = 0;
	this->MaxQuest = 0;

	this->MaxMonsterMission = 0;
	this->MaxRewardMission = 0;

	this->DrawInfoTable = false;
}
// -------------------------------------------------------------------------------

MonsterQuest::~MonsterQuest()
{
	// ----
}
// -------------------------------------------------------------------------------

void MonsterQuest::InterfaceLoad()
{
	gInterface.BindObject(eMQUEST_MAIN, 0x7A5A, 222, 303, -1, -1);
	gInterface.BindObject(eMQUEST_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eMQUEST_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eMQUEST_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eMQUEST_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eMQUEST_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(eMQUEST_INFOBG, 0x7AA3, 170, 21, -1, -1);	//0x79A2	//0x7AA3 - original	0x7922
	gInterface.BindObject(eMQUEST_INFOBG2, 0x7AA1, 170, 21, -1, -1);
	gInterface.BindObject(eMQUEST_MONEYBG, 0x7A89, 170, 26, -1, -1);
	gInterface.BindObject(eMQUEST_FINISH, 0x7A5E, 128, 29, -1, -1);
	gInterface.BindObject(eMQUEST_COUNT, 0x7BAC, 168, 18, -1, -1);

	gInterface.Data[eMQUEST_MAIN].OnShow = false;
	
}
// -------------------------------------------------------------------------------

void MonsterQuest::RecvKill(GCMonsterQuestKill * aRecv)
{
	int i = aRecv->MissionNum;
	if(i >= 5 || i < 0 ) return;
	this->KillCount[i] = aRecv->MissionKill;
}
// -------------------------------------------------------------------------------

void MonsterQuest::RecvMission(GCMonsterQuestDialog *aRecv)
{

	this->MyQuest =	aRecv->NumQuest + 1;
	this->MaxQuest = aRecv->MaxQuest;

	this->MaxMonsterMission = 0;
	this->MaxRewardMission = 0;

	for(int i=0; i < MAX_MISSION_QUEST; i++)
	{
		this->KillCount[i] = aRecv->KillCount[i];
		// ----
		this->MonsterData[i].Active		= aRecv->MonsterDataGC[i].Active;

		strncpy(this->MonsterData[i].Mission,aRecv->MonsterDataGC[i].Mission,20);

		//this->MonsterData[i].Mission	= aRecv->MonsterDataGC[i].Mission;
		//this->MonsterData[i].Procent	= aRecv->MonsterDataGC[i].Procent;
		this->MonsterData[i].Count		= aRecv->MonsterDataGC[i].Count;

		if(this->MonsterData[i].Active)
		{
			this->MaxMonsterMission++;
		}

		//gConsole.Output(cGREEN,"%d %d %d %d",this->MonsterData[i].Active,this->MonsterData[i].Mission,this->MonsterData[i].Procent,this->MonsterData[i].Count);
	}

	for(int i=0; i < MAX_REWARD_QUEST; i++)
	{
		this->RewardData[i].Active		= aRecv->RewardDataGC[i].Active;
		this->RewardData[i].Reward		= aRecv->RewardDataGC[i].Reward;
		this->RewardData[i].RewardID	= aRecv->RewardDataGC[i].RewardID;
		this->RewardData[i].Level		= aRecv->RewardDataGC[i].Level;
		this->RewardData[i].Skill		= aRecv->RewardDataGC[i].Skill;
		this->RewardData[i].Luck		= aRecv->RewardDataGC[i].Luck;
		this->RewardData[i].Option		= aRecv->RewardDataGC[i].Option;
		this->RewardData[i].Exellent	= aRecv->RewardDataGC[i].Exellent;
		this->RewardData[i].Ancent		= aRecv->RewardDataGC[i].Ancent;

		if(this->RewardData[i].Active)
		{
			this->MaxRewardMission++;
		}
	}

	//this->OpenQuestMainWindow();	// <<==
}
// -------------------------------------------------------------------------------

void MonsterQuest::RecvWindowsOpen(GCQuestWindowsOpen *aRecv)
{
	if(aRecv->Open)
	{
		this->OpenQuestMainWindow();
	}
}
// -------------------------------------------------------------------------------

bool MonsterQuest::DoneQuest()
{
	for(int i=0; i < MAX_MISSION_QUEST; i++)
	{
		if(this->MonsterData[i].Active)
		{
			if(this->KillCount[i] < this->MonsterData[i].Count)
			{
				return false;
			}
		}
	}

	return true;
}
// -------------------------------------------------------------------------------

void MonsterQuest::DrawMainTable()
{
	this->DrawInfo();
	//this->OpenQuestMainWindow();
	//gConsole.Output(cGREEN,"%d",gInterface.Data[eMQUEST_MAIN].OnShow);
	if( !gInterface.Data[eMQUEST_MAIN].OnShow )
	{
		
		return;
	}

	pSetCursorFocus = true;

	// ----
	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	gInterface.DrawGUI(eMQUEST_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eMQUEST_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eMQUEST_FRAME, StartX, StartY + 67.0, 13);
	gInterface.DrawGUI(eMQUEST_FOOTER, StartX, StartY);
	gInterface.DrawGUI(eMQUEST_CLOSE, StartX + MainWidth - gInterface.Data[eMQUEST_CLOSE].Width, gInterface.Data[eMQUEST_TITLE].Height + gInterface.Data[eMQUEST_CLOSE].Height + 2);
	// ----
	if( gInterface.IsWorkZoneObj(eMQUEST_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eMQUEST_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUIObj(eMQUEST_CLOSE, gInterface.Data[eMQUEST_CLOSE].X, gInterface.Data[eMQUEST_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[eMQUEST_CLOSE].X + 5, gInterface.Data[eMQUEST_CLOSE].Y + 25, "Close");
	}
	// ----
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, "Monster Quest");

	// **** Quest Info Start
	gInterface.DrawGUI(eMQUEST_COUNT, StartX+30 , 127);
	gInterface.DrawFormat(eAncient, StartX + 10, 130, 210, 3, "Count:  %d / %d", this->MyQuest , this->MaxQuest);

	// ----

	int CountMissionY = 160;

	gInterface.DrawFormat(eOrange, StartX + 10, CountMissionY - 10, 210, 3, "MISSION");

	for(int i=0;i<this->MaxMonsterMission;i++)	//Mission Count
	{
		gInterface.DrawGUI(eMQUEST_INFOBG, StartX + 30, CountMissionY);
		gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY + 5, 100, 1, "%s:", this->MonsterData[i].Mission);

		gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY + 5, 100, 3, "%d / %d", this->KillCount[i], this->MonsterData[i].Count);

		CountMissionY += 20;
	}

	int CountMissionY2 = 260;

	gInterface.DrawGUI(eMQUEST_DIV, StartX, CountMissionY2);

	CountMissionY2 += 20;

	gInterface.DrawFormat(eOrange, StartX + 10, CountMissionY2, 210, 3, "REWARD");

	CountMissionY2 += 10;

	for(int i=0;i<this->MaxRewardMission;i++)
	{
		//gInterface.DrawGUI(eMQUEST_INFOBG, StartX + 30, CountMissionY2);

		// -------------------
		switch(this->RewardData[i].Active)
		{
		case eZen:
			{
				gInterface.DrawGUI(eMQUEST_INFOBG2, StartX + 30, CountMissionY2);
				gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "Zen:", i);
				gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d", this->RewardData[i].Reward);
			}
			break;
		case eFreePoints:
			{
				gInterface.DrawGUI(eMQUEST_INFOBG2, StartX + 30, CountMissionY2);
				gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "FreePoint:", i);
				gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d", this->RewardData[i].Reward);
			}
			break;
		case eItem:
			{

				int rItem = ITEMGET(this->RewardData[i].Reward,this->RewardData[i].RewardID);
				int rLevel = this->RewardData[i].Level;
				int rSkill = this->RewardData[i].Skill;
				int rLuck = this->RewardData[i].Luck;
				int rOption = this->RewardData[i].Option;
				int rExellent = this->RewardData[i].Exellent;
				int rAncent = this->RewardData[i].Ancent;

				char ItemReward[150];
				ZeroMemory(&ItemReward,sizeof(ItemReward));
				//strcat(ItemReward,(char*)(char*)(*(DWORD*)0x8128AC0 + 84 * rItem));
				sprintf(ItemReward, "%s", (char*)(*(DWORD*)0x8128AC0 + 84 * rItem));

				char ItemOptionReward[50];
				ZeroMemory(&ItemOptionReward,sizeof(ItemOptionReward));

				if(rLevel)
				{
					sprintf(ItemOptionReward, "+%d ", rLevel);
					//strcat(ItemOptionReward,"+Luck ");
				}

				if(rSkill)
				{
					strcat(ItemOptionReward,"+Skill ");
				}

				if(rLuck)
				{
					strcat(ItemOptionReward,"+Luck");
				}

				if(rOption)
				{
					strcat(ItemOptionReward,"+Option ");
				}

				if(rExellent)
				{
					strcat(ItemOptionReward,"+Excellent ");
					ItemNameColor = eExcellent;
				}

				if(rAncent)
				{
					strcat(ItemOptionReward,"+Ancient ");
					ItemNameColor = eAncient;
				}

				//delete_secret_number
				//newui_chat_main(s)

				gInterface.DrawFormat(ItemNameColor, StartX + 30 + 5, CountMissionY2 + 5, 300, 1, "%s %s", ItemReward,ItemOptionReward);
				//gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%s", ItemOptionReward);

				//ItemSerialCreateSend(lpUser->m_Index,lpUser->MapNumber,lpUser->X,lpUser->Y,rItem,rLevel,0,rSkill,rLuck,rOption,lpUser->m_Index,rExellent,rAncent);	//?
			}
			break;
		case eWCoin:
			{
				gInterface.DrawGUI(eMQUEST_INFOBG2, StartX + 30, CountMissionY2);
				gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "WCoin:", i);
				gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d", this->RewardData[i].Reward);
			}
			break;
		case eWCoinP:
			{
				gInterface.DrawGUI(eMQUEST_INFOBG2, StartX + 30, CountMissionY2);
				gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "WCoin(P):", i);
				gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d", this->RewardData[i].Reward);
			}
			break;
		case eGoblin:
			{
				gInterface.DrawGUI(eMQUEST_INFOBG2, StartX + 30, CountMissionY2);
				gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "Goblin Points:", i);
				gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d", this->RewardData[i].Reward);
			}
			break;
		case eCredit:
			{
				gInterface.DrawGUI(eMQUEST_INFOBG2, StartX + 30, CountMissionY2);
				gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "Credits:", i);
				gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d", this->RewardData[i].Reward);
			}
			break;
		}

			// -------------------

		//gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "Reward:", i);
		//gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d / %d", i, 10);

		CountMissionY2 += 20;
	}

	// -------------------
	// **** Quest Info End
	// -------------------
	gInterface.DrawGUI(eMQUEST_DIV, StartX, gInterface.Data[eMQUEST_FOOTER].Y - 10);
	

	gInterface.DrawGUI(eMQUEST_FINISH, ButtonX, gInterface.Data[eMQUEST_FOOTER].Y + 10);
	gInterface.DrawFormat(eWhite, StartX + 8, gInterface.Data[eMQUEST_FOOTER].Y + 20, 210, 3, "Reward Quest");
	gInterface.DrawGUI(eRESET_DIV, StartX, gInterface.Data[eMQUEST_FOOTER].Y - 10);

	if( !this->DoneQuest() )
	{
		gInterface.Data[eMQUEST_FINISH].Attribute = false;
		gInterface.DrawColoredGUIObj(eMQUEST_FINISH, gInterface.Data[eMQUEST_FINISH].X, gInterface.Data[eMQUEST_FINISH].Y, eGray150);
		return;
	}

	gInterface.Data[eMQUEST_FINISH].Attribute = true;

	// ----
	if( gInterface.IsWorkZoneObj(eMQUEST_FINISH) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eMQUEST_FINISH].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUIObj(eMQUEST_FINISH, gInterface.Data[eMQUEST_FINISH].X, gInterface.Data[eMQUEST_FINISH].Y, Color);
	}
}
// -------------------------------------------------------------------------------

bool MonsterQuest::EventCloseMainTable(DWORD Event)
{
	if( pPlayerState != GameProcess )
	{
		return false;
	}

	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - gInterface.Data[eMQUEST_CLOSE].EventTick);
	// ----
	if( !gInterface.Data[eMQUEST_MAIN].OnShow || !gInterface.IsWorkZoneObj(eMQUEST_CLOSE) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		gInterface.Data[eMQUEST_CLOSE].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eMQUEST_CLOSE].OnClick = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	gInterface.Data[eMQUEST_CLOSE].EventTick = GetTickCount();
	this->CloseQuestMainWindow();
	// ----
	return false;
}
// -------------------------------------------------------------------------------

bool MonsterQuest::EventFinishMainTable(DWORD Event)
{

	if( pPlayerState != GameProcess )
	{
		return false;
	}

	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - gInterface.Data[eMQUEST_FINISH].EventTick);
	// ----
	if( !gInterface.Data[eMQUEST_MAIN].OnShow || !gInterface.IsWorkZoneObj(eMQUEST_FINISH) 
		|| !gInterface.Data[eMQUEST_FINISH].Attribute )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		gInterface.Data[eMQUEST_FINISH].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eMQUEST_FINISH].OnClick = false;;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	gInterface.Data[eMQUEST_FINISH].EventTick = GetTickCount();
	// ----
	this->CloseQuestMainWindow();
	this->SendFinish();
	// ----
	return false;
}
// -------------------------------------------------------------------------------

void MonsterQuest::SendFinish()
{
	CGFinishMonsterQuest pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 20, sizeof(pRequest));
	pRequest.Reward	= 1;
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// -------------------------------------------------------------------------------

void MonsterQuest::OpenQuestMainWindow() 
{
	gInterface.Data[eMQUEST_MAIN].OnShow = true;
	pSetCursorFocus = true; 
}
// -------------------------------------------------------------------------------

void MonsterQuest::CloseQuestMainWindow() 
{ 
	gInterface.Data[eMQUEST_MAIN].OnShow = false; 
	pSetCursorFocus = false; 
}
// -------------------------------------------------------------------------------

bool MonsterQuest::CheckQuestMainWindow() 
{ 
	return gInterface.Data[eMQUEST_MAIN].OnShow; 
}
// -------------------------------------------------------------------------------

void MonsterQuest::DrawInfo()
{
	if(this->MyQuest > this->MaxQuest)
	{
		return;
	}

	if(!this->DrawInfoTable) return;

	bool Result = false;

	for(int i=0;i<5;i++)
	{
		if(this->MonsterData[i].Active)
		{
			Result = true;
		}
	}

	if(Result == false)
	{
		return;
	}

	//if(this->DrawQuestTable) return;

	//if(!gInterface.RightWindows()) return;

	if( gInterface.CheckWindow(CashShop)
		||	gInterface.CheckWindow(SkillTree)
		||	gInterface.CheckWindow(FullMap) 
		||	gInterface.CheckWindow(MoveList) 
		||  (gInterface.CheckWindow(Inventory) 
		&& gInterface.CheckWindow(ExpandInventory) 
		&& gInterface.CheckWindow(Store)) 
		||  (gInterface.CheckWindow(Inventory) 
		&& gInterface.CheckWindow(Warehouse) 
		&& gInterface.CheckWindow(ExpandWarehouse)) )
	{
		return;
	}

	int InfoColor = 150;
	float InfoStartY = 25;	//13
	float InfoWidth	 = 80;
	float InfoHigh	 = 75;	
	float InfoStartX = 65;	//50

	//pDrawColorButton(0x7880, InfoStartX , InfoStartY, InfoWidth, 11, 0, 0, (int)Color4f(0, 0, 0, 255));
	//pDrawColorButton(0x7880, InfoStartX , InfoStartY, 2, InfoHigh, 0, 0, (int)Color4f(0, 0, 0, 255));

	//pDrawColorButton(0x7880, InfoStartX , InfoStartY+InfoHigh, InfoWidth+2, 2, 0, 0, (int)Color4f(0, 0, 0, 255));	//Должна быть нижняя линия
	//pDrawColorButton(0x7880, InfoStartX+InfoWidth , InfoStartY, 2, InfoHigh, 0, 0, (int)Color4f(0, 0, 0, 255));	//Боковая линия

	//pDrawColorButton(0x7880, InfoStartX , InfoStartY, InfoWidth, InfoHigh, 0, 0, (int)Color4f(0, 0, 0, InfoColor));

	pDrawGUI(400000, InfoStartX, InfoStartY, 85, 100);

	float TextY = InfoStartY+2+10;

	float CountMissionY = 28 + 10;

	float StartX = InfoStartX;

	gInterface.DrawFormat(eAncient, StartX + 5, CountMissionY - 10, 80, 3, "Quest: %d", this->MyQuest);

	for(int i=0;i<5;i++)
	{
		gInterface.DrawFormat(eWhite, StartX + 5, CountMissionY, 100, 1, "%s:", this->MonsterData[i].Mission);
		gInterface.DrawFormat(eGold, StartX - 25, CountMissionY, 100, 4, "%d / %d", this->KillCount[i], this->MonsterData[i].Count);
		CountMissionY += 15;
	}

	//TextY = gInterface.DrawFormat(eExcellent, InfoStartX , TextY , InfoWidth, 3, "Damage: +%d",this->Damage);
}
// -------------------------------------------------------------------------------