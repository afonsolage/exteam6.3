#include "stdafx.h"
#include "ExWinQuestSystem.h"
#include "Interface.h"
#include "Settings.h"
#include "Debug.h"
#include "Protocol.h"
#include "Console.h"
#include "Monster.h"
#include "Item.h"
#include "BuffIcon.h"
#include "ExMenuV3.h"

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
	// --
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::Init()
{
	ShowMiniInfo = true;
	// --
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::Load()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::ImageLoad()
{
	pLoadImage("Custom\\Interface\\info_block.tga", ex_INFO_2, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\newui_cha_textbox03.tga", ex_TEXT_BOX3, 0x2601, 0x2900, 1, 0);
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::BindImages()
{
	int eWHig = 303 + 60 + 45 + 15;

	gInterface.BindObject(eWIN_QUEST_MAIN, 0x7A5A, 222, eWHig, -1, -1);
	gInterface.BindObject(eWIN_QUEST_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eWIN_QUEST_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eWIN_QUEST_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eWIN_QUEST_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eWIN_QUEST_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(eWIN_QUEST_TAB, 0x7AE0, 166, 22, -1, -1);
	gInterface.BindObject(eWIN_QUEST_TAB1, 0x7AE1, 55, 22, -1, -1);
	gInterface.BindObject(eWIN_QUEST_TAB2, 0x7AE1, 55, 22, -1, -1);
	gInterface.BindObject(eWIN_QUEST_TAB3, 0x7AE1, 55, 22, -1, -1);
	gInterface.BindObject(eWIN_QUEST_FINISH, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eWIN_QUEST_COUNT1, 0x7BAC, 168, 18, -1, -1);
	gInterface.BindObject(eWIN_QUEST_COUNT2, 0x7BAC, 168, 18, -1, -1);
	gInterface.BindObject(eWIN_QUEST_COUNT3, 0x7BAC, 168, 18, -1, -1);
	gInterface.BindObject(eWIN_QUEST_INFOBG, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eWIN_QUEST_INFOBG2, 0x7AA1, 170, 22, -1, -1);
	gInterface.BindObject(eWIN_QUEST_LINE1, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eWIN_QUEST_POINT1, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eWIN_QUEST_INFO, ex_INFO_2, 22, 19, -1, -1);
	gInterface.BindObject(eWIN_QUEST_INFOBG3, ex_TEXT_BOX3, 170, 21, -1, -1);
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::Draw()
{
	if(!gInterface.CheckWindowEx(exWinQuest))
	{
		return;
	}

	pSetCursorFocus = true;

	int a = this->OpenTab;

	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 0;
	float StartX			= 0;//(MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	float ContentX          = StartX;
	float ContentY			= StartY;
	float TabX = StartX + 30;
	float TabY = ContentY + 30 + 5;
	float InfoX = 0;
	float InfoY = 0;
	int InfoA = 0;
	int InfoM = 0;
	int bColor = 0;
	// ----
	gInterface.DrawGUI(eWIN_QUEST_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eWIN_QUEST_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eWIN_QUEST_FRAME, StartX, StartY + 67.0, 21);
	gInterface.DrawGUI(eWIN_QUEST_FOOTER, StartX, StartY);
	gInterface.DrawGUI(eWIN_QUEST_CLOSE, StartX + MainWidth - gInterface.Data[eWIN_QUEST_CLOSE].Width, ContentY);
	// ----
	if( gInterface.IsWorkZone(eWIN_QUEST_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eWIN_QUEST_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eWIN_QUEST_CLOSE, gInterface.Data[eWIN_QUEST_CLOSE].X, gInterface.Data[eWIN_QUEST_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[eWIN_QUEST_CLOSE].X + 5, gInterface.Data[eWIN_QUEST_CLOSE].Y + 25, "Close");
	}
	// ----
	gInterface.DrawFormat(eGold, ContentX + 10, ContentY + 10, 210, 3, "Quest System");
	// ------------------------------------
	// -> Tab
	// ------------------------------------
	gInterface.DrawGUI(eWIN_QUEST_TAB, TabX, TabY);

	if(this->OpenTab == 0)
	{
		gInterface.DrawGUIEx(eWIN_QUEST_TAB1, TabX, TabY, true );
		gInterface.DrawGUIEx(eWIN_QUEST_TAB2, TabX + gInterface.Data[eWIN_QUEST_TAB2].Width, TabY, false );
		gInterface.DrawGUIEx(eWIN_QUEST_TAB3, TabX + gInterface.Data[eWIN_QUEST_TAB3].Width + gInterface.Data[eWIN_QUEST_TAB3].Width, TabY, false );
	}
	else if(this->OpenTab == 1)
	{
		gInterface.DrawGUIEx(eWIN_QUEST_TAB1, TabX, TabY, false );
		gInterface.DrawGUIEx(eWIN_QUEST_TAB2, TabX + gInterface.Data[eWIN_QUEST_TAB2].Width, TabY, true );
		gInterface.DrawGUIEx(eWIN_QUEST_TAB3, TabX + gInterface.Data[eWIN_QUEST_TAB3].Width + gInterface.Data[eWIN_QUEST_TAB3].Width, TabY, false );
	}
	else
	{
		gInterface.DrawGUIEx(eWIN_QUEST_TAB1, TabX, TabY, false );
		gInterface.DrawGUIEx(eWIN_QUEST_TAB2, TabX + gInterface.Data[eWIN_QUEST_TAB2].Width, TabY, false );
		gInterface.DrawGUIEx(eWIN_QUEST_TAB3, TabX + gInterface.Data[eWIN_QUEST_TAB3].Width + gInterface.Data[eWIN_QUEST_TAB3].Width, TabY, true );		
	}

	if(this->ewdata[0].b_End)
	{
		gInterface.DrawFormat(eGold, TabX, TabY + 10, 60, 3, "End");
	}
	else
	{
		gInterface.DrawFormat(eGold, TabX, TabY + 10, 60, 3, "%s", this->ewdata[0].NameQuest);
	}
	if(this->ewdata[1].b_End)
	{
		gInterface.DrawFormat(eGold, TabX + gInterface.Data[eWIN_QUEST_TAB2].Width, TabY + 10, 60, 3, "End");
	}
	else
	{
		gInterface.DrawFormat(eGold, TabX + gInterface.Data[eWIN_QUEST_TAB2].Width, TabY + 10, 60, 3, "%s", this->ewdata[1].NameQuest);
	}
	if(this->ewdata[2].b_End)
	{
		gInterface.DrawFormat(eGold, TabX + gInterface.Data[eWIN_QUEST_TAB3].Width + gInterface.Data[eWIN_QUEST_TAB3].Width, TabY + 10, 60, 3, "End");
	}
	else
	{
		gInterface.DrawFormat(eGold, TabX + gInterface.Data[eWIN_QUEST_TAB3].Width + gInterface.Data[eWIN_QUEST_TAB3].Width, TabY + 10, 60, 3, "%s",  this->ewdata[2].NameQuest);
	}
	// ------------------------------------
	// -> End Quest
	// ------------------------------------
	if(this->ewdata[a].b_End)
	{
		float EndY = ContentY + 53;
		gInterface.DrawGUI(eWIN_QUEST_INFOBG3, StartX + 30, EndY + 12);
		gInterface.DrawFormat(eAncient, ContentX + 30 , EndY + 17, 170, 3, "End");
		gInterface.Data[eWIN_QUEST_FINISH].Attribute = false;
		return;
	}
	// ------------------------------------
	// -> Content Need
	// ------------------------------------
	float NeededY = ContentY + 53;
	gInterface.DrawGUI(eWIN_QUEST_DIV, StartX, NeededY);

	gInterface.DrawGUI(eWIN_QUEST_COUNT2, ContentX + 30 , NeededY + 10);
	gInterface.DrawFormat(eAncient, ContentX + 30 , NeededY + 12, 170, 3, "Need");

	float CountNeededY = NeededY + 30;

	gInterface.DrawGUI(eWIN_QUEST_INFOBG, StartX + 30, CountNeededY);
	gInterface.DrawGUI(eWIN_QUEST_POINT1, StartX + 35, CountNeededY+5);
	gInterface.DrawFormat(eWhite, StartX + 30 + 5 + 15, CountNeededY + 6, 100, 1, "Level:");

	if(this->ewdata[a].b_Level)
	{
		bColor = eGold;
	}
	else
	{
		bColor = eRed;
	}

	gInterface.DrawFormat(bColor, StartX + 30 + 70, CountNeededY + 6, 100, 3, "%d", this->ewdata[a].NeedLevel);
	CountNeededY += 21;
	
	gInterface.DrawGUI(eWIN_QUEST_INFOBG, StartX + 30, CountNeededY);
	gInterface.DrawGUI(eWIN_QUEST_POINT1, StartX + 35, CountNeededY+5);
	gInterface.DrawFormat(eWhite, StartX + 30 + 5 + 15, CountNeededY + 6, 100, 1, "Reset:");

	if(this->ewdata[a].b_Reset)
	{
		bColor = eGold;
	}
	else
	{
		bColor = eRed;
	}

	gInterface.DrawFormat(bColor, StartX + 30 + 70, CountNeededY + 6, 100, 3, "%d", this->ewdata[a].NeedReset);
	CountNeededY += 21;

	gInterface.DrawGUI(eWIN_QUEST_INFOBG, StartX + 30, CountNeededY);
	gInterface.DrawGUI(eWIN_QUEST_POINT1, StartX + 35, CountNeededY+5);
	gInterface.DrawFormat(eWhite, StartX + 30 + 5 + 15, CountNeededY + 6, 100, 1, "Grand Reset:");

	if(this->ewdata[a].b_Grand)
	{
		bColor = eGold;
	}
	else
	{
		bColor = eRed;
	}

	gInterface.DrawFormat(bColor, StartX + 30 + 70, CountNeededY + 6, 100, 3, "%d", this->ewdata[a].NeedGrand);
	CountNeededY += 21;
	// ------------------------------------
	// -> Content Mission
	// ------------------------------------
	float MissionX = StartX;
	float MissionY = ContentY + 53 + 90;
	gInterface.DrawGUI(eWIN_QUEST_DIV, StartX, MissionY);

	MissionY+=10;

	gInterface.DrawGUI(eWIN_QUEST_COUNT1, ContentX+30 , MissionY);
	gInterface.DrawFormat(eAncient, ContentX+30 , MissionY + 2, 170, 3, "Mission");

	float CountMissionY = MissionY + 20;
	
	for(int m = 0; m < EW_MAX_MISSION; m++)
	{
		if( this->ewdata[a].MissionType[m] == Hunting || 
			this->ewdata[a].MissionType[m] == Droping ||
			this->ewdata[a].MissionType[m] == Searching )
		{
			if(this->ewdata[a].b_Mission[m])
			{
				bColor = eGold;
			}
			else
			{
				bColor = eRed;
			}

			if(this->ewdata[a].MissionType[m] == Hunting)
			{
				gInterface.DrawGUI(eWIN_QUEST_INFOBG, MissionX + 30, CountMissionY);
				gInterface.DrawGUI(eWIN_QUEST_POINT1, MissionX + 35, CountMissionY+5);

				if(this->ewdata[a].MissionID[m] == 65535)
				{
					gInterface.DrawFormat(eWhite, MissionX + 30 + 5 + 15, CountMissionY + 6, 100, 1, "Kill Level %d~%d", this->ewdata[a].MissionOpt[m], this->ewdata[a].MissionExl[m]);
				}
				else
				{
					gInterface.DrawFormat(eWhite, MissionX + 30 + 5 + 15, CountMissionY + 6, 100, 1, "%s", gMonster.GetMonsterName(this->ewdata[a].MissionID[m]));
				}

				gInterface.DrawFormat(bColor, MissionX + 30 + 70, CountMissionY + 6, 100, 3, "%d / %d", this->ewdata[a].Count[m], this->ewdata[a].MissionCount[m]);
				gInterface.DrawGUI(eWIN_QUEST_INFO, MissionX + 30 + 170 -1, CountMissionY);
			}
			else if(this->ewdata[a].MissionType[m] == Droping)
			{
				gInterface.DrawGUI(eWIN_QUEST_INFOBG, MissionX + 30, CountMissionY);
				gInterface.DrawGUI(eWIN_QUEST_POINT1, MissionX + 35, CountMissionY+5);
				gInterface.DrawFormat(eWhite, MissionX + 30 + 5 + 15, CountMissionY + 6, 100, 1, "%s:", gItem.GetItemName(ITEMGET(this->ewdata[a].MissionID[m], this->ewdata[a].MissionIndex[m])));
				gInterface.DrawFormat(bColor, MissionX + 30 + 70, CountMissionY + 6, 100, 3, "%d / %d", this->ewdata[a].Count[m], this->ewdata[a].MissionCount[m]);
				gInterface.DrawGUI(eWIN_QUEST_INFO, MissionX + 30 + 170 -1, CountMissionY);
			}
			else if(this->ewdata[a].MissionType[m] == Searching)
			{
				char OptionMSG[64] = { 0 };

				if(this->ewdata[a].MissionLevel[m] > 0)
				{
					sprintf(OptionMSG, "+%d", this->ewdata[a].MissionLevel[m]);
				}
				if(this->ewdata[a].MissionLuck[m] > 0)
				{
					strcat(OptionMSG, " +Luck");
				}
				if(this->ewdata[a].MissionOpt[m] > 0)
				{
					strcat(OptionMSG, " +Opt");
				}
				if(this->ewdata[a].MissionExl[m] > 0)
				{
					strcat(OptionMSG, " +Exellent");
				}

				gInterface.DrawGUI(eWIN_QUEST_INFOBG3, MissionX + 30, CountMissionY);
				gInterface.DrawFormat(bColor, MissionX + 15, CountMissionY + 6, 200, 3, "%s %s", gItem.GetItemName(ITEMGET(this->ewdata[a].MissionID[m], this->ewdata[a].MissionIndex[m])), OptionMSG);
			}

			gInterface.DrawGUI(eWIN_QUEST_INFO, MissionX + 30 + 170 - 1, CountMissionY);
			CountMissionY += 21;

			if(gInterface.IsWorkZone(eWIN_QUEST_INFO))
			{
				InfoX = gInterface.Data[eWIN_QUEST_INFO].X + 5;
				InfoY = gInterface.Data[eWIN_QUEST_INFO].Y + 25;
				InfoA = a;
				InfoM = m;
			}
		}
	}
	// ------------------------------------
	// -> Content Reward
	// ------------------------------------
	float RewardY = ContentY + 53 + 100 + 42 + 63 + 15;
	gInterface.DrawGUI(eWIN_QUEST_DIV, StartX, RewardY);

	gInterface.DrawGUI(eWIN_QUEST_COUNT2, ContentX+30 , RewardY + 10);
	gInterface.DrawFormat(eAncient, ContentX+30 , RewardY + 12, 170, 3, "Reward");

	float CountRewardY = RewardY + 34 - 4;
	
	for(int r = 0; r < EW_MAX_REWARD; r++)
	{
		if( this->ewdata[a].RewardType[r] == ewZen		 ||
			this->ewdata[a].RewardType[r] == ewFreePoint ||
			this->ewdata[a].RewardType[r] == ewItem		 ||
			this->ewdata[a].RewardType[r] == ewBonus	 ||
			this->ewdata[a].RewardType[r] == ewBuff		 )
		{
			if(this->ewdata[a].RewardType[r] == ewZen)
			{
				char RewardMSG[64] = { 0 };
				gInterface.DrawGUI(eWIN_QUEST_INFOBG2, StartX + 30, CountRewardY);
				gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountRewardY + 5, 100, 1, "Zen:");
				pGetMoneyFormat((double)(int)this->ewdata[a].RewardCount[r], RewardMSG, 0);
				gInterface.DrawFormat(eGold, StartX + 30 + 70, CountRewardY + 5, 100, 3, "%s", RewardMSG);
				//gConsole.Output(cGREY, "this->ewdata[a].RewardCount[r] : %d", this->ewdata[a].RewardCount[r]);
			}
			else if(this->ewdata[a].RewardType[r] == ewFreePoint)
			{
				gInterface.DrawGUI(eWIN_QUEST_INFOBG, StartX + 30, CountRewardY);
				gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountRewardY + 5, 100, 1, "Free Point:");
				gInterface.DrawFormat(eGold, StartX + 30 + 70, CountRewardY + 5, 100, 3, "%d", this->ewdata[a].RewardCount[r]);
			}
			else if(this->ewdata[a].RewardType[r] == ewItem)
			{
				gInterface.DrawGUI(eWIN_QUEST_INFOBG3, StartX + 30, CountRewardY);
				if(this->ewdata[a].RewardItemLevel[r] > 0)
				{
					gInterface.DrawFormat(eGold, StartX + 70, CountRewardY + 5, 100, 3, "%s +%d x %d", 
						gItem.GetItemName(ITEMGET(this->ewdata[a].RewardItemType[r], this->ewdata[a].RewardItemIndex[r])), this->ewdata[a].RewardItemLevel[r], this->ewdata[a].RewardCount[r]);
				}
				else
				{
					gInterface.DrawFormat(eGold, StartX + 70, CountRewardY + 5, 100, 3, "%s x %d",
						gItem.GetItemName(ITEMGET(this->ewdata[a].RewardItemType[r], this->ewdata[a].RewardItemIndex[r])), this->ewdata[a].RewardCount[r]);
				}
			}
			else if(this->ewdata[a].RewardType[r] == ewBonus)
			{
				gInterface.DrawGUI(eWIN_QUEST_INFOBG2, StartX + 30, CountRewardY);
				gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountRewardY + 5, 100, 1, "Bonus:");
				gInterface.DrawFormat(eGold, StartX + 30 + 70, CountRewardY + 5, 100, 3, "%d", this->ewdata[a].RewardCount[r]);
			}
			else if(this->ewdata[a].RewardType[r] == ewBuff)
			{
				gInterface.DrawGUI(eWIN_QUEST_INFOBG, StartX + 30, CountRewardY);
				gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountRewardY + 5, 100, 1, "Buff:");

				gInterface.DrawFormat(eGold, StartX + 30 + 70, CountRewardY + 5, 100, 3, "%s", g_BuffIcon.GetAddedBuffName(this->ewdata[a].RewardItemType[r]));
			}		

			CountRewardY += 21;
		}
	}
	// ------------------------------------
	// -> Finish
	// ------------------------------------
	bool Finish = 0;

	if(this->ewdata[a].Start)
	{
		Finish = this->ewdata[a].b_done;
	}
	else
	{
		Finish = this->ewdata[a].b_accept;
	}

	gInterface.DrawGUI(eWIN_QUEST_FINISH, ButtonX, gInterface.Data[eWIN_QUEST_FOOTER].Y + 10);

	if(this->ewdata[a].Start)
	{
		gInterface.DrawFormat(eWhite, StartX + 8, gInterface.Data[eWIN_QUEST_FOOTER].Y + 20, 210, 3, "Done");
	}
	else
	{
		gInterface.DrawFormat(eWhite, StartX + 8, gInterface.Data[eWIN_QUEST_FOOTER].Y + 20, 210, 3, "Accept");
	}
	
	gInterface.DrawGUI(eWIN_QUEST_DIV, StartX, gInterface.Data[eWIN_QUEST_FOOTER].Y - 10);
	
	if( !Finish )
	{
		gInterface.Data[eWIN_QUEST_FINISH].Attribute = false;
		gInterface.DrawColoredGUI(eWIN_QUEST_FINISH, gInterface.Data[eWIN_QUEST_FINISH].X, gInterface.Data[eWIN_QUEST_FINISH].Y, eGray150);
	}
	else
	{
		// ----
		gInterface.Data[eWIN_QUEST_FINISH].Attribute = true;
		// ----
		if( gInterface.IsWorkZone(eWIN_QUEST_FINISH) )
		{
			DWORD Color = eGray100;
			// ----
			if( gInterface.Data[eWIN_QUEST_FINISH].OnClick )
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(eWIN_QUEST_FINISH, gInterface.Data[eWIN_QUEST_FINISH].X, gInterface.Data[eWIN_QUEST_FINISH].Y, Color);
		}
	}
	// ------------------------------------
	// -> Info Y
	// ------------------------------------
	if(InfoX != 0 && InfoY != 0)
	{
		char Name[50] = { 0 };
		char NeedInfoText[256] = { 0 };
		char InfoMap[64] = { 0 };

		int BrCount = 0;

		int mID = this->ewdata[InfoA].MissionID[InfoM];
		int mIndex = this->ewdata[InfoA].MissionIndex[InfoM];
		int uCount = this->ewdata[InfoA].Count[InfoM];
		int mCount = this->ewdata[InfoA].MissionCount[InfoM];
		int mLuck = this->ewdata[InfoA].MissionLuck[InfoM];
		int mOpt = this->ewdata[InfoA].MissionOpt[InfoM];
		int mExl = this->ewdata[InfoA].MissionExl[InfoM];
		int mProc = this->ewdata[InfoA].MissionProcent[InfoM];

		if(this->ewdata[InfoA].MissionType[InfoM] == Hunting)
		{
			if(mID == 65535)
			{
				sprintf(NeedInfoText, "Information:\n Kill Monster: \n Level: %d ~ %d \n Count: %d/%d\n", mOpt, mExl, uCount, mCount);
				BrCount = 4;
			}
			else
			{
				sprintf(NeedInfoText, "Information:\n Kill Monster: \n %s %d/%d\n", gMonster.GetMonsterName(mID), uCount, mCount);
				BrCount = 3;
			}
		}
		if(this->ewdata[InfoA].MissionType[InfoM] == Droping)
		{
				sprintf(NeedInfoText, "Information:\n Drop Item:\n %s\n Count: %d/%d\n Monster:\n Level: %d ~ %d\n Procent: %d\n", gItem.GetItemName(ITEMGET(mID, mIndex)), uCount, mCount, mOpt, mExl, mProc);
				BrCount = 7;
		}
		if(this->ewdata[InfoA].MissionType[InfoM] == Searching)
		{
			strcat(NeedInfoText,"Information:\n Craft Item\n");
			BrCount = 2;
		}

		if(this->ewdata[InfoA].MissionType[InfoM] == Hunting || this->ewdata[InfoA].MissionType[InfoM] == Droping)
		{
			if(mLuck == 255)
			{
				strcat(InfoMap,"Map: All\n");	
			}
			else
			{
				sprintf(InfoMap, "Map: %s\n", pGetMapName(mLuck), uCount, mCount);
			}
			strcat(NeedInfoText, InfoMap);	
			BrCount++;
		}

		int Br = BrCount * 10;
		int Wind = 60;

		if(pGameResolutionMode > 5)
		{
			Wind = 50;
		}

		pDrawColorButton(0x7880, InfoX, InfoY, Wind, Br, NULL, NULL, Color4f(0, 0, 0, 255));	

		if(pGameResolutionMode > 4)
		{
			gInterface.DrawFormat(eWhite, InfoX /*- 8*/, InfoY, Wind, 3, NeedInfoText);
			
		}
		else
		{
			gInterface.DrawFormat(eWhite, InfoX, InfoY, Wind, 3, NeedInfoText);
		}

	}
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::DrawMiniInfo()
{
	if (!ShowMiniInfo)
		return;

	/*if(!g_Settings.ShowQuest)
	{
		return;
	}*/

	if(    gInterface.CheckWindow(Party)
		|| gInterface.CheckWindow(Guild)
		|| gInterface.CheckWindow(Trade)
		|| gInterface.CheckWindow(Warehouse)
		|| gInterface.CheckWindow(ChaosBox)
		|| gInterface.CheckWindow(CommandWindow)
		|| gInterface.CheckWindow(PetInfo)
		|| gInterface.CheckWindow(Shop)
		|| gInterface.CheckWindow(Inventory)
		|| gInterface.CheckWindow(Store)
		|| gInterface.CheckWindow(OtherStore)
		|| gInterface.CheckWindow(Character)
		|| gInterface.CheckWindow(FastMenu)
		|| gInterface.CheckWindow(SkillTree)
		|| gInterface.CheckWindow(NPC_Titus)
		|| gInterface.CheckWindow(CashShop)
		|| gInterface.CheckWindow(FullMap)
		|| gInterface.CheckWindow(NPC_Dialog)
		|| gInterface.CheckWindow(GensInfo)
		|| gInterface.CheckWindow(NPC_Julia)
		|| gInterface.CheckWindow(ExpandInventory)
		|| gInterface.CheckWindow(ExpandWarehouse) 
		|| gInterface.CheckWindow(Helper) 
		|| gInterface.CheckWindow(Quest) 
		|| gInterface.CheckWindow(QuestDevin) 
		|| gInterface.CheckWindow(DevilSquery) 
		|| gInterface.CheckWindow(GuardNPC) 
		|| gInterface.CheckWindow(VorotaCS) 
		|| gInterface.CheckWindow(Rena) 
		|| gInterface.CheckWindow(LuckyCoins)
		|| gInterface.CheckWindow(Titus)
		|| gInterface.CheckWindow(BloodCastle) )
	{
		return;
	}

	if( gInterface.CheckWindowEx(exWinRanking)		  ||
		gInterface.CheckWindowEx(exWinPersonalPrice)  ||
		gInterface.CheckWindowEx(exWinAchievements))
	{
		return;
	}

	if(g_ExMenuV3.m_Enable && g_ExMenuV3.m_Version == EXMENU_NUMBER::eVERSION_ET)
	{
		if(gInterface.CheckWindowEx(exWinMenuV3))
		{
			return;
		}
	}

	int qCount = 0;
	int mCount = 0;
	bool DrInfo = false;

	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		if(this->ewdata[a].Start == TRUE)
		{
			qCount+=15;

			for(int m = 0; m < EW_MAX_MISSION; m++)
			{
				if( this->ewdata[a].MissionType[m] == Hunting || 
					this->ewdata[a].MissionType[m] == Droping ||
					this->ewdata[a].MissionType[m] == Searching )
				{
					mCount += 10;
					DrInfo = true;
				}
			}
		}
	}

	if(DrInfo == false)
	{
		return;
	}

	float iX = 535;
	float iY = 320;
	float Wind = 100;
	float Hig = qCount + mCount;

	float StartiY = 425;
	// ----
	StartiY = gInterface.RightMiniInfoY - 5;
	gInterface.RightMiniInfoY -= Hig;
	// ----
	iY = StartiY - Hig;

	pDrawColorButton(0x7880, iX, iY, Wind, Hig, NULL, NULL, Color4f(0, 0, 0, 100));

	iY+=3;

	for(int a = 0; a < EW_MAX_ACT; a++)
	{	
		if(this->ewdata[a].Start == TRUE)
		{
			gInterface.DrawFormat(eOrange, iX+5, iY, 200, 1, "%s", this->ewdata[a].NameQuest);

			for(int m = 0; m < EW_MAX_MISSION; m++)
			{
				if( this->ewdata[a].MissionType[m] == Hunting || 
					this->ewdata[a].MissionType[m] == Droping ||
					this->ewdata[a].MissionType[m] == Searching )
				{
					iY+=10;

					if(this->ewdata[a].MissionType[m] == Hunting)
					{	
						if(this->ewdata[a].MissionID[m] == 65535)
						{
							gInterface.DrawFormat(eWhite, iX+10, iY, 200, 1, "- Kill Level %d~%d: %d/%d",
								this->ewdata[a].MissionOpt[m], this->ewdata[a].MissionExl[m],this->ewdata[a].Count[m],this->ewdata[a].MissionCount[m]);
						}
						else
						{
							gInterface.DrawFormat(eWhite, iX+10, iY, 200, 1, "- %s: %d/%d",
								gMonster.GetMonsterName(this->ewdata[a].MissionID[m]), this->ewdata[a].Count[m], this->ewdata[a].MissionCount[m]);
						}
					}
					else if(this->ewdata[a].MissionType[m] == Droping)
					{
						gInterface.DrawFormat(eWhite, iX+10, iY, 200, 1, "- %s: %d/%d", 
							gItem.GetItemName(ITEMGET(this->ewdata[a].MissionID[m], this->ewdata[a].MissionIndex[m])), ewdata[a].Count[m], ewdata[a].MissionCount[m]);
					}
					else if(this->ewdata[a].MissionType[m] == Searching)
					{
						gInterface.DrawFormat(eWhite, iX+10, iY, 200, 1, "- %s", gItem.GetItemName(ITEMGET(this->ewdata[a].MissionID[m], this->ewdata[a].MissionIndex[m])));
					}
				}
			}

			iY+=15;
		}
	}
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::Button(DWORD Event)
{
	if(!gInterface.CheckWindowEx(exWinQuest))
	{
		return;
	}

	if( gInterface.ButtonEx(Event, eWIN_QUEST_FINISH, true ) )
	{
		this->CG_AcñeptQuest();
	}
	else if( gInterface.ButtonEx(Event, eWIN_QUEST_CLOSE, false ) )
	{
		gInterface.CloseWindowEx(exWinQuest);
	}
	else if( gInterface.ButtonEx(Event, eWIN_QUEST_TAB1, false ) )
	{
		this->OpenTab = 0;
	}
	else if( gInterface.ButtonEx(Event, eWIN_QUEST_TAB2, false ) )
	{
		this->OpenTab = 1;
	}
	else if( gInterface.ButtonEx(Event, eWIN_QUEST_TAB3, false ) )
	{
		this->OpenTab = 2;
	}
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::GC_RecvMain(GC_MainPacket* aRecv)
{
	for(int a=0; a < EW_MAX_ACT; a++)
	{
		strncpy(this->ewdata[a].NameQuest, aRecv->exQuest[a].NameQuest, 25);
		this->ewdata[a].b_accept = aRecv->exQuest[a].b_accept;
		this->ewdata[a].b_done = aRecv->exQuest[a].b_done;
		this->ewdata[a].b_End = aRecv->exQuest[a].b_End;
		// -> user send
		this->ewdata[a].Start = aRecv->exQuest[a].Start;
		this->ewdata[a].Number = aRecv->exQuest[a].Number;
		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			this->ewdata[a].Count[m] = aRecv->exQuest[a].Count[m];
		}	
		// -> need send
		this->ewdata[a].b_Level = aRecv->exQuest[a].b_Level;
		this->ewdata[a].b_Reset = aRecv->exQuest[a].b_Reset;
		this->ewdata[a].b_Grand = aRecv->exQuest[a].b_Grand;

		this->ewdata[a].NeedLevel = aRecv->exQuest[a].NeedLevel;
		this->ewdata[a].NeedReset = aRecv->exQuest[a].NeedReset;
		this->ewdata[a].NeedGrand = aRecv->exQuest[a].NeedGrand;
		// -> mission send
		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			this->ewdata[a].b_Mission[m] = aRecv->exQuest[a].b_Mission[m];
			this->ewdata[a].MissionType[m] = aRecv->exQuest[a].MissionType[m];
			this->ewdata[a].MissionID[m] = aRecv->exQuest[a].MissionID[m];
			this->ewdata[a].MissionIndex[m] = aRecv->exQuest[a].MissionIndex[m];
			this->ewdata[a].MissionLevel[m] = aRecv->exQuest[a].MissionLevel[m];
			this->ewdata[a].MissionLuck[m] = aRecv->exQuest[a].MissionLuck[m];
			this->ewdata[a].MissionOpt[m] = aRecv->exQuest[a].MissionOpt[m];
			this->ewdata[a].MissionExl[m] = aRecv->exQuest[a].MissionExl[m];
			this->ewdata[a].MissionCount[m] = aRecv->exQuest[a].MissionCount[m];
			this->ewdata[a].MissionProcent[m] = aRecv->exQuest[a].MissionProcent[m];
		}
		for(int r = 0; r < EW_MAX_REWARD; r++)
		{
			
			this->ewdata[a].RewardType[r] = aRecv->exQuest[a].RewardType[r];
			this->ewdata[a].RewardCount[r] = aRecv->exQuest[a].RewardCount[r];
			this->ewdata[a].RewardItemType[r] = aRecv->exQuest[a].RewardItemType[r];
			this->ewdata[a].RewardItemIndex[r] = aRecv->exQuest[a].RewardItemIndex[r];
			this->ewdata[a].RewardItemLevel[r] = aRecv->exQuest[a].RewardItemLevel[r];
		}
	}

	if(!gInterface.CheckWindowEx(exWinQuest))
	{
		gInterface.OpenWindowEx(exWinQuest);
	}
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::CG_AcñeptQuest()
{
	CG_Accept_Done pReq = { 0 };
	pReq.h.set((LPBYTE)&pReq, 0xFB, 0x12, sizeof(pReq));
	pReq.Result = this->OpenTab;
	gProtocol.DataSend((LPBYTE)&pReq, pReq.h.size);
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::GC_MiniInfoRecv(GC_ExWinMiniInfo* aRecv)
{
	for(int a = 0; a < EW_MAX_ACT; a++)
	{
		strncpy(this->ewdata[a].NameQuest, aRecv->exQuest[a].NameQuest, 25);
		this->ewdata[a].Start = aRecv->exQuest[a].Start;
		for(int m = 0; m < EW_MAX_MISSION; m++)
		{
			this->ewdata[a].Count[m] = aRecv->exQuest[a].ExWQuestCount[m];
			this->ewdata[a].MissionType[m] = aRecv->exQuest[a].MissionType[m];
			this->ewdata[a].MissionID[m] = aRecv->exQuest[a].MissionID[m];
			this->ewdata[a].MissionIndex[m] = aRecv->exQuest[a].MissionIndex[m];
			this->ewdata[a].MissionLevel[m] = aRecv->exQuest[a].MissionLevel[m];
			this->ewdata[a].MissionLuck[m] = aRecv->exQuest[a].MissionLuck[m];
			this->ewdata[a].MissionOpt[m] = aRecv->exQuest[a].MissionOpt[m];
			this->ewdata[a].MissionExl[m] = aRecv->exQuest[a].MissionExl[m];
			this->ewdata[a].MissionCount[m] = aRecv->exQuest[a].MissionCount[m];
		}
	}
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::GC_MiniInfoRecvEx(GC_ExWinMiniInfoEx* aRecv)
{
	int a = aRecv->a;
	int m = aRecv->m;

	if(a < 0 || a >= EW_MAX_ACT)
	{
		return;
	}

	if(m < 0 && m >= EW_MAX_MISSION)
	{
		return;
	}

	this->ewdata[a].Count[m]++;
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::GC_Start(GC_ExWinStart* aRecv)
{
	int a = aRecv->Act;
	int s = aRecv->Start;

	if(a < 0 || a >= EW_MAX_ACT)
	{
		return;
	}

	if(s == true)
	{
		this->ewdata[a].Start = true;
	}
}
// ----------------------------------------------------------------------------------------------
#endif