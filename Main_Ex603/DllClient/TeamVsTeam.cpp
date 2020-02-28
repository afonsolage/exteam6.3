#include "stdafx.h"
#include "TeamVsTeam.h"
#include "Interface.h"
#include "User.h"
#include "Protocol.h"
#include "Sound.h"
#include "TMemory.h"
#if(EVENT_TEAM_VS_TEAM)

CTeamVsTeam g_TeamVsTeam;

CTeamVsTeam::CTeamVsTeam()
{
	this->Init();
}

CTeamVsTeam::~CTeamVsTeam()
{
}

void CTeamVsTeam::Init()
{
	this->m_EventStatus = eEVENT_TEAMVSTEAM_CLOSE;
	this->m_MinLevel = 0;
	this->m_MinReset = 0;
	this->m_TeamScore1 = 0;
	this->m_TeamScore2 = 0;
	this->m_Team = 0;
	this->m_UserScore = 0;
	this->m_UserDie = 0;
	this->m_dwEventTime = 0;
	this->m_dwTickCount = 0;
}

void CTeamVsTeam::Load()
{
	this->Init();
}

void CTeamVsTeam::BindImage()
{
	gInterface.BindObject(eTEAMVSTEAM_MAIN, 0x7A5A, 222, 140, -1, -1);
	gInterface.BindObject(eTEAMVSTEAM_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eTEAMVSTEAM_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eTEAMVSTEAM_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eTEAMVSTEAM_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eTEAMVSTEAM_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eTEAMVSTEAM_CLOSE, 0x7A5F, 62, 27, -1, -1);

	gInterface.BindObject(eTEAMVSTEAM_STATISTIC_MAIN, 0x7A5A, 222, 270, -1, -1);
	gInterface.BindObject(eTEAMVSTEAM_STATISTIC_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eTEAMVSTEAM_STATISTIC_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eTEAMVSTEAM_STATISTIC_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eTEAMVSTEAM_STATISTIC_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eTEAMVSTEAM_STATISTIC_FINISH, 0x7A5E, 128, 29, -1, -1);

	gInterface.BindObject(eLORA_BATTLE_SCORE, ex_LORA_BATTLE_SCORE, 131, 70, -10, 359 + 22);
	//gInterface.BindObject(eTEAMVSTEAM_STATISTIC_INFO, ex_TEAM_VS_TEAM_STATISTIC, 170, 20, -1, -1);

	gInterface.BindObject(eTEAMVSTEAM_STATISTIC_LINE, 0x7B67, 90, 3, -1, -1);
	
}

void CTeamVsTeam::DrawMain()
{
	this->DrawWindow();
	this->DrawBattle();
	this->PKLevelTeam();
	this->DrawUserScore();
#if(TEAM_VS_TEAM_INFO)
	this->DrawStatistic();
#endif
}

void CTeamVsTeam::DrawWindow()
{
	if(!gInterface.CheckWindowEx(exWinTeamVsTeam))
	{
		return;
	}

	pSetCursorFocus = true;

	DWORD Color		= eGray100;
	float MainWidth	= 230.0;
	float StartY	= 100.0;
	float StartX	= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float ContentY	= StartY;

	gInterface.DrawGUI(eTEAMVSTEAM_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eTEAMVSTEAM_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eTEAMVSTEAM_FRAME, StartX, StartY + 67.0, 2);
	gInterface.DrawGUI(eTEAMVSTEAM_FOOTER, StartX, StartY);

	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, "Team Vs Team");

	gInterface.DrawFormat(eYellow, StartX + 10, ContentY + 60, 210, 3, "Take part in the Team Vs Team event?");

	gInterface.DrawGUI(eTEAMVSTEAM_OK, StartX+30, StartY - 5);
	gInterface.DrawFormat(eWhite, StartX + 35, StartY+5, 50, 3, "Yes");

	lpCharObj lpPlayer			= pUserObjectStruct;

	if(this->m_MinLevel > lpPlayer->Level || this->m_MinReset > gObjUser.Reset || !this->CheckStatus(eEVENT_TEAMVSTEAM_WAIT))
	{
		gInterface.Data[eTEAMVSTEAM_OK].Attribute = false;
		gInterface.DrawColoredGUI(eTEAMVSTEAM_OK, gInterface.Data[eTEAMVSTEAM_OK].X, gInterface.Data[eTEAMVSTEAM_OK].Y, eGray150);
	}
	else
	{
		gInterface.Data[eTEAMVSTEAM_OK].Attribute = true;
		if(gInterface.IsWorkZone(eTEAMVSTEAM_OK))
		{
			Color = eGray100;
			if(gInterface.Data[eTEAMVSTEAM_OK].OnClick)
			{
				Color = eGray150;
			}
			gInterface.DrawColoredGUI(eTEAMVSTEAM_OK, gInterface.Data[eTEAMVSTEAM_OK].X, gInterface.Data[eTEAMVSTEAM_OK].Y, Color);
		}
	}

	gInterface.DrawGUI(eTEAMVSTEAM_CLOSE, StartX + 70 + 62, StartY - 5);
	gInterface.DrawFormat(eWhite, StartX + 75 + 62, StartY+5, 50, 3, "No");

	if(gInterface.IsWorkZone(eTEAMVSTEAM_CLOSE))
	{
		Color = eGray100;
		if(gInterface.Data[eTEAMVSTEAM_CLOSE].OnClick)
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eTEAMVSTEAM_CLOSE, gInterface.Data[eTEAMVSTEAM_CLOSE].X, gInterface.Data[eTEAMVSTEAM_CLOSE].Y, Color);
	}
}

void CTeamVsTeam::DrawUserScore()
{
	if(!this->CheckStatus(eEVENT_TEAMVSTEAM_START) || gObjUser.m_MapNumber != TEAMVSTEAM_MAP)
	{
		return;
	}

	if( gInterface.CheckWindow(ObjWindow::ChatWindow)	|| 
		gInterface.CheckWindow(ObjWindow::CashShop)		|| 
		gInterface.CheckWindow(ObjWindow::FullMap)		|| 
		gInterface.CheckWindow(ObjWindow::SkillTree) )
	{
		return;
	}

	int nuX = 16;

	gInterface.DrawGUI(eLORA_BATTLE_SCORE, 0, 359/* + 22*/);
	gInterface.DrawFormat(eGold, nuX, 391, 50, 1, "Kill:");
	gInterface.DrawFormat(eWhite, nuX+20, 391, 100, 1, "%d", this->m_UserScore);

	gInterface.DrawFormat(eGold, nuX+40, 391, 50, 1, "Die:");
	gInterface.DrawFormat(eWhite, nuX+60, 391, 100, 1, "%d", this->m_UserDie);

	DWORD dwInSec = this->m_dwEventTime / 1000;

	int minT = ( dwInSec / 60 );
	int secT = ( dwInSec % 60 );
	gInterface.DrawFormat(eGold, nuX, 391+22, 50, 1, "Battle Time:");

	char szScore[10] = { 0 };
	sprintf(szScore, "%2d : %2d", minT, secT);
	gInterface.DrawFormat(eWhite, nuX+55+2, 391+22, 100, 1, szScore);
}

void CTeamVsTeam::DrawBattle()
{
	if(this->CheckStatus(eEVENT_TEAMVSTEAM_START) && gObjUser.m_MapNumber == TEAMVSTEAM_MAP)
	{
		SetRange((LPVOID)0x007D2CE1, 5, ASM::NOP);
		gInterface.DrawFormat(eBlue, 30, 4, 50, 3, "Blue: %d", this->m_TeamScore1);
		gInterface.DrawFormat(eExcellent, 70, 4, 50, 3, "Green: %d", this->m_TeamScore2);
	}
	else
	{
		BYTE btBuffer[] = { 0xE8, 0x6A, 0xD4, 0xC4, 0xFF };
		WriteMemory((LPVOID)0x007D2CE1, btBuffer, sizeof(btBuffer));
	}
}

#if(TEAM_VS_TEAM_INFO)
void CTeamVsTeam::DrawStatistic()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinTeamVsTeamStatistic))
	{
		return;
	}

	pSetCursorFocus = true;

	DWORD Color			= eGray100;
	float MainWidth		= 230.0;
	float StartY		= 100.0;
	float StartX		= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter	= StartX + (MainWidth / 3);
	float ButtonX		= MainCenter - (29.0 / 2);
	float ContentX		= StartX;
	float ContentY		= StartY;
	float ContentX2		= StartX;
	float ContentY2		= StartY;

	gInterface.DrawGUI(eTEAMVSTEAM_STATISTIC_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eTEAMVSTEAM_STATISTIC_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eTEAMVSTEAM_STATISTIC_FRAME, StartX, StartY + 67.0, 11);
	gInterface.DrawGUI(eTEAMVSTEAM_STATISTIC_FOOTER, StartX, StartY);

	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, "Team Vs Team");

	gInterface.DrawFormat(eYellow, StartX + 10, 140, 210, 3, "Statistic Players");

	// table 1
	ContentX += 15;
	ContentY += 50;

	gInterface.DrawFormat(eBlue, ContentX+10, ContentY+5, 100, 1, "Team: Blue");
	ContentY += 15;

	gInterface.DrawFormat(eYellow, ContentX, ContentY+5, 100, 1, "#)");
	gInterface.DrawFormat(eWhite, ContentX+10, ContentY+5, 100, 1, "Name");
	gInterface.DrawFormat(eExcellent, ContentX+65, ContentY+5, 100, 1, "Kill");
	gInterface.DrawFormat(eRed, ContentX+80, ContentY+5, 100, 1, "Die");
	gInterface.DrawGUI(eTEAMVSTEAM_STATISTIC_LINE, ContentX, ContentY+15);
	ContentY += 15;

	for(int i = 0; i < this->m_iDataCount1; i++)
	{		
		gInterface.DrawFormat(eYellow, ContentX, ContentY+5, 100, 1, "%d)", i+1);
		gInterface.DrawFormat(eWhite, ContentX+10, ContentY+5, 100, 1, this->m_Data1[i].Name);
		gInterface.DrawFormat(eExcellent, ContentX+65, ContentY+5, 100, 1, "%d", this->m_Data1[i].Kill);
		gInterface.DrawFormat(eRed, ContentX+80, ContentY+5, 100, 1, "%d", this->m_Data1[i].Die);
		gInterface.DrawGUI(eTEAMVSTEAM_STATISTIC_LINE, ContentX, ContentY+15);
		ContentY += 15;
	}

	// table 2
	ContentX2 += 115;
	ContentY2 += 50;

	gInterface.DrawFormat(eExcellent, ContentX2+10, ContentY2+5, 100, 1, "Team: Green");
	ContentY2 += 15;

	gInterface.DrawFormat(eYellow, ContentX2, ContentY2+5, 100, 1, "#)");
	gInterface.DrawFormat(eWhite, ContentX2+10, ContentY2+5, 100, 1, "Name");
	gInterface.DrawFormat(eExcellent, ContentX2+65, ContentY2+5, 100, 1, "Kill");
	gInterface.DrawFormat(eRed, ContentX2+80, ContentY2+5, 100, 1, "Die");
	gInterface.DrawGUI(eTEAMVSTEAM_STATISTIC_LINE, ContentX2, ContentY2+15);
	ContentY2 += 15;

	for(int i = 0; i < this->m_iDataCount2; i++)
	{
		gInterface.DrawFormat(eYellow, ContentX2, ContentY2+5, 100, 1, "%d)", i+1);
		gInterface.DrawFormat(eWhite, ContentX2+10, ContentY2+5, 100, 1, this->m_Data2[i].Name);
		gInterface.DrawFormat(eExcellent, ContentX2+65, ContentY2+5, 100, 1, "%d", this->m_Data2[i].Kill);
		gInterface.DrawFormat(eRed, ContentX2+80, ContentY2+5, 100, 1, "%d", this->m_Data2[i].Die);
		gInterface.DrawGUI(eTEAMVSTEAM_STATISTIC_LINE, ContentX2, ContentY2+15);
		ContentY2 += 15;
	}
	// end
	
	ContentX = StartX;
	ContentY = StartY;
	gInterface.DrawGUI(eTEAMVSTEAM_STATISTIC_FINISH, ButtonX, ContentY + 10);
	gInterface.DrawFormat(eWhite, StartX + 8, ContentY + 20, 210, 3, "Ok");
	gInterface.DrawGUI(eTEAMVSTEAM_STATISTIC_DIV, StartX, ContentY - 10);

	gInterface.Data[eTEAMVSTEAM_STATISTIC_FINISH].Attribute = true;

	if( gInterface.IsWorkZone(eTEAMVSTEAM_STATISTIC_FINISH) )
	{
		Color = eGray100;

		if( gInterface.Data[eTEAMVSTEAM_STATISTIC_FINISH].OnClick )
		{
			Color = eGray150;
		}

		gInterface.DrawColoredGUI(eTEAMVSTEAM_STATISTIC_FINISH, gInterface.Data[eTEAMVSTEAM_STATISTIC_FINISH].X, gInterface.Data[eTEAMVSTEAM_STATISTIC_FINISH].Y, Color);
	}

}
#endif

void CTeamVsTeam::Button(DWORD Event)
{
	if(gInterface.CheckWindowEx(ObjWindowsEx::exWinTeamVsTeam))
	{
		if(gInterface.ButtonEx(Event, eTEAMVSTEAM_OK, true))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinTeamVsTeam);
			PMSG_TVTGC_RESULT pMsg;
			pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x81, sizeof(pMsg));
			gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
			return;
		}

		if(gInterface.ButtonEx(Event, eTEAMVSTEAM_CLOSE, false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinTeamVsTeam);
			return;
		}
	}

	if(gInterface.CheckWindowEx(ObjWindowsEx::exWinTeamVsTeamStatistic))
	{
		if(gInterface.ButtonEx(Event, eTEAMVSTEAM_STATISTIC_FINISH, true))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinTeamVsTeamStatistic);
		}
	}
}

bool CTeamVsTeam::CheckStatus(int Status)
{
	if(this->m_EventStatus == Status)
	{
		return true;
	}

	return false;
}

void CTeamVsTeam::GCEventStatus(PMSG_TVTGC_STATUS* lpMsg)
{
	this->m_EventStatus = lpMsg->Status;

	switch(this->m_EventStatus)
	{
		case eEVENT_TEAMVSTEAM_CLOSE: 
			{
				this->m_TeamScore1 = 0;
				this->m_TeamScore2 = 0;
				this->m_Team = 0;
				if(pMapNumber == TEAMVSTEAM_MAP)
				{
					g_Sound.Stop(eSOUND_TEAM_VS_TEAM);
				}
			}
			break;
		case eEVENT_TEAMVSTEAM_WAIT:   
			break;
		case eEVENT_TEAMVSTEAM_START:  
			{
				if(pMapNumber == TEAMVSTEAM_MAP)
				{
					g_Sound.Play(eSOUND_TEAM_VS_TEAM);
				}
			}
			break;
	}
}

void CTeamVsTeam::GCOpenWindow(PMSG_TVTGC_WINOPEN* lpMsg)
{
	this->m_MinLevel = lpMsg->MinLevel;
	this->m_MinReset = lpMsg->MinReset;

	gInterface.OpenWindowEx(ObjWindowsEx::exWinTeamVsTeam);
}

void CTeamVsTeam::GCEventScore(PMSG_TVTGC_SCORE* lpMsg)
{
	this->m_TeamScore1 = lpMsg->TeamScore1;
	this->m_TeamScore2 = lpMsg->TeamScore2;
}

void CTeamVsTeam::GCViewePortTvT(LPBYTE lpMsg)
{
	if(!this->CheckStatus(eEVENT_TEAMVSTEAM_START))
	{
		return;
	}

	if(!lpMsg)
	{
		return;
	}

	memset(&this->m_Viewe, 0, sizeof(this->m_Viewe));
	int datasize = 6;
	int excount = lpMsg[datasize-1];

	for(int n = 0; n < excount; n++)
	{
		VIEWEPORT_TVT Vp;
		memcpy(&Vp,&lpMsg[datasize],sizeof(Vp));

		this->m_Viewe[n].aIndex = Vp.aIndex;
		this->m_Viewe[n].Life = Vp.Life;
		this->m_Viewe[n].MaxLife = Vp.MaxLife;
		this->m_Viewe[n].TvTTeam = Vp.TvTTeam;

		datasize += sizeof(Vp);
	}
}

bool CTeamVsTeam::HPBar()
{
	if(!this->CheckStatus(eEVENT_TEAMVSTEAM_START))
	{
		return false;
	}

	pGLSwitch();
	pSetBlend(true);
	pGLSwitchBlend();

	char LifeDisplay[50] = { 0 };
	VAngle Angle;
	int PosX, PosY, LifeProgress;

	float LifeBarWidth	= 38.0f;

	for(int i = 0; i < 400; i++)
	{
		lpViewObj lpObj    = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), i);

		if(!lpObj || !lpObj->m_Model.Unknown4)
		{
			continue;
		}

		if(lpObj->m_Model.ObjectType == emPlayer)
		{
			int Life, MaxLife, iTeam;
			DWORD ColorBar;

			bool Draw = false;

			for(int n = 0; n < MAX_VIEWPORT;n++)
			{
				if(lpObj->aIndex == this->m_Viewe[n].aIndex)
				{
					Life = this->m_Viewe[n].Life;
					MaxLife = this->m_Viewe[n].MaxLife;
					iTeam = this->m_Viewe[n].TvTTeam;

					if(iTeam == this->m_Team)
					{
						ColorBar = Color4f(0, 255, 0, 150);			
					}
					else
					{
						ColorBar = Color4f(255, 0, 0, 150);
					}

					Draw = true;

					if(Life > MaxLife)
					{
						this->m_Viewe[n].Life = MaxLife;
						Life = MaxLife;
					}
					break;
				}
			}

			if(Draw == false || Life <= 0)
			{
				continue;
			}

			sprintf(LifeDisplay, "HP: %d", Life);

			int hpbarsymbol = strlen(LifeDisplay);

			int DevX = 20;
			int Wind = 70;
			int LineHG = 1;

			if(pGameResolutionMode == 1 )
			{
				Wind = 70;
			}
			else if(pGameResolutionMode == 2)
			{
				Wind = 60;
			}
			else if(pGameResolutionMode >= 3)
			{
				Wind = 50;
			}

			if(pGameResolutionMode == 1 && hpbarsymbol > 20)
			{
				Wind = hpbarsymbol * 3.5;
			}
			else if( pGameResolutionMode == 2 && hpbarsymbol > 20)
			{
				Wind = hpbarsymbol * 3;
			}
			else if(pGameResolutionMode >= 3 && hpbarsymbol > 20)
			{
				Wind = hpbarsymbol * 2.5;
			}

			Angle.X = lpObj->m_Model.VecPosX;
			Angle.Y = lpObj->m_Model.VecPosY;
			Angle.Z = lpObj->m_Model.VecPosZ + lpObj->m_Model.Unknown216.Z + 100.0;

			pGetPosFromAngle(&Angle, &PosX, &PosY);

			PosX -= (int)floor((double)Wind / (double)4.0);

			int pHP = (Life * 100) / MaxLife;

			pSetBlend(true);

			pDrawColorButton(0x7880, (PosX-DevX), (PosY-8), Wind, 10, 0, 0, Color4f(0, 0, 0, 150));	
			pDrawColorText(LifeDisplay, (PosX-DevX), (PosY-8), Wind, 0, eWhite, 0, 3);

			pDrawColorButton(0x7880, (PosX - DevX) , (PosY), (Wind * pHP) / 100, LineHG, 0, 0, ColorBar);
		}
	}

	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);

	return true;
}

void CTeamVsTeam::GCTeam(PMSG_TVTGC_TEAM* lpMsg)
{
	this->m_Team = lpMsg->Team;
}

void CTeamVsTeam::PKLevelTeam()
{
	if(!this->CheckStatus(eEVENT_TEAMVSTEAM_START))
	{
		return;
	}

	if(pMapNumber != TEAMVSTEAM_MAP)
	{
		return;
	}

	for(int i = 0; i < 400; i++)
	{
		lpViewObj lpObj    = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), i);

		if(!lpObj || !lpObj->m_Model.Unknown4 || lpObj->aIndex == pGameIndex || lpObj->m_Model.ObjectType != emPlayer)
		{
			continue;
		}

		for(int n = 0; n < MAX_VIEWPORT; n++)
		{
			if(lpObj->aIndex == this->m_Viewe[n].aIndex)
			{
				if(this->m_Team == this->m_Viewe[n].TvTTeam)
				{
					lpObj->PKLevel = 3;	
				}
				else
				{					
					lpObj->PKLevel = 7;
				}

				break;
			}
		}
	}
}

void CTeamVsTeam::GCUserKillCount(PMSG_TVTGC_KILL* lpMsg)
{
	this->m_UserScore = lpMsg->KillCount;
	this->m_UserDie = lpMsg->DieCount;
}

void CTeamVsTeam::GCEventiTimer(PMSG_TVTGC_TIME* lpMsg)
{
	this->m_dwEventTime = lpMsg->EventTime;
}

void CTeamVsTeam::GCEventStatistic(PMSG_TVT_STATISTIC* lpMsg)
{
	this->m_iDataCount1 = lpMsg->Count;
	for(int i = 0; i < lpMsg->Count; i++)
	{
		this->m_Data1[i].Name[10] = 0;
		memcpy(this->m_Data1[i].Name, lpMsg->stat[i].Name, 10);
		this->m_Data1[i].Kill = lpMsg->stat[i].Kill;
		this->m_Data1[i].Die = lpMsg->stat[i].Die;
	}

	this->m_iDataCount2 = lpMsg->Count2;
	for(int i = 0; i < lpMsg->Count2; i++)
	{
		this->m_Data2[i].Name[10] = 0;
		memcpy(this->m_Data2[i].Name, lpMsg->stat2[i].Name, 10);
		this->m_Data2[i].Kill = lpMsg->stat2[i].Kill;
		this->m_Data2[i].Die = lpMsg->stat2[i].Die;
	}

	gInterface.OpenWindowEx(ObjWindowsEx::exWinTeamVsTeamStatistic);
}

#endif