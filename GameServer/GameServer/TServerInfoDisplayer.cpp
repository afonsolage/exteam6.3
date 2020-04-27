// TServerInfoDisplayer.cpp: implementation of the TServerInfoDisplayer class.
//	GS-N	1.00.77	JPN	-	Completed
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TServerInfoDisplayer.h"
#include "Gamemain.h"
#include "DBSockMng.h"
#include "LogToFile.h"
#include "CashShop.h"
#include "ExLicense.h"

TServerInfoDisplayer g_ServerInfoDisplayer;
CLogToFile SERVER_CONN_STATE_LOG("SERVER_CONN_STATE_LOG", ".\\SERVER_CONN_STATE_LOG", 1);

static char * ServerTypeText[1] =
{
#if(GS_CASTLE==0)
	"  [-  ExTeam Game Server  -]"
#else
	"[-  ExTeam Castle Server  -]"
#endif
};

static char * ErrorMessge[8] = 
{
	"0) JoinServer - Disconnected",
	"1) FsGateServer - Disconnected",
	"2) DataServer - Disconnected",
	"3) ExDBServer - Disconnected",
	"4) EventServer - Disconnected",
	"5) RankingServer - Disconnected"
};

static char * DeveloperMessage[4] = 
{
	"Developer: DangeR",
	"Skype: muonline.bk",
	//"Season 6 Episode 3",
	"Project: Multi-Emulator",
	"forum.ex-team.net"
};

static char * StatusMsg[8] = 
{
	"Join Server:",
	"Data Server:",
	"ExDB Server:",
	"Event Server:",
	"Ranking Server:",
	"CashShop Server:",
	"Online",
	"Offline"
};



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TServerInfoDisplayer::TServerInfoDisplayer()
{
	this->m_bValidJSConnection = FALSE;
	this->m_bValidFSConnection = FALSE;
	this->m_bValidDSConnection = FALSE;
	this->m_bValidEXDSConnection = FALSE;
	this->m_bValidEVDSConnection = FALSE;
	this->m_bValidRKDSConnection = FALSE;

	this->InitGDIObject();
}

TServerInfoDisplayer::~TServerInfoDisplayer()
{
	this->DelGDIObject();
}

void TServerInfoDisplayer::InitGDIObject()
{


	this->m_hFont = CreateFontA(60, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, 
		1, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE, "Times");



	//this->m_hFont = CreateFont(80, 0, 0, 0, FW_THIN, FALSE, TRUE, FALSE, 
	//	ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	//	DEFAULT_PITCH|FF_DONTCARE, "Times");

	//this->m_hNormalBrush = CreateSolidBrush(RGB(110, 240, 120));
	this->m_hNormalBrush = CreateSolidBrush(RGB(33, 200, 219));
	this->m_hAbnormalBrush = CreateSolidBrush(RGB(250, 110, 110));
}

void TServerInfoDisplayer::DelGDIObject()
{
	DeleteObject(this->m_hFont);
	DeleteObject(this->m_hNormalBrush);
	DeleteObject(this->m_hAbnormalBrush);
}

void TServerInfoDisplayer::Run(HWND hWnd)
{
	this->CheckDSConnection();
	this->CheckJSConnection();
	this->CheckFSConnection();
	this->CheckEXDSConnection();
	this->CheckEVDSConnection();
	this->CheckRKDSConnection();

	this->CheckLogFileSize();

	this->PaintAllInfo(hWnd, 0, 20);
}

void TServerInfoDisplayer::CheckLogFileSize()
{

}

void TServerInfoDisplayer::CheckJSConnection()
{
	if ( wsJServerCli.GetSocket() == INVALID_SOCKET )
		this->m_bValidJSConnection = FALSE;
	else
		this->m_bValidJSConnection = TRUE;
}

void TServerInfoDisplayer::CheckDSConnection()
{
	if ( cDBSMng.wsCDBS[0].GetSocket() == INVALID_SOCKET )
		this->m_bValidDSConnection = FALSE;
	else
		this->m_bValidDSConnection = TRUE;
}

void TServerInfoDisplayer::CheckFSConnection()
{
	this->m_bValidFSConnection = TRUE;
}

void TServerInfoDisplayer::CheckEXDSConnection()
{
	if ( wsExDbCli.GetSocket() == INVALID_SOCKET )
		this->m_bValidEXDSConnection = FALSE;
	else
		this->m_bValidEXDSConnection = TRUE;
}

void TServerInfoDisplayer::CheckEVDSConnection()
{
	if ( IsEventChipServerConnected == FALSE )
		this->m_bValidEVDSConnection = FALSE;
	else
		this->m_bValidEVDSConnection = TRUE;
}

void TServerInfoDisplayer::CheckRKDSConnection()
{
	if ( IsDevilSquareEventConnected == FALSE )
		this->m_bValidRKDSConnection = FALSE;
	else
		this->m_bValidRKDSConnection = TRUE;
}

void TServerInfoDisplayer::PaintAllInfo(HWND hWnd, int iTopLeftX, int iTopLeftY)
{
	HDC hDC = GetDC(hWnd);
	RECT rect;
	GetClientRect(hWnd, &rect);
	rect.top = 20;
	rect.bottom = 100;
	int iLineCount = 0;

	int iOldBkMode = SetBkMode(hDC, TRANSPARENT);

#if(NEW_WINDOW==1)

	SetTextColor(hDC, RGB(123, 123, 250));
	TextOut(hDC, 10, 80, StatusMsg[0], strlen(StatusMsg[0]));

	TextOut(hDC, 150, 80, StatusMsg[1], strlen(StatusMsg[1]));

	TextOut(hDC, 300, 80, StatusMsg[2], strlen(StatusMsg[2]));

	TextOut(hDC, 450, 80, StatusMsg[3], strlen(StatusMsg[3]));

	TextOut(hDC, 600, 80, StatusMsg[4], strlen(StatusMsg[4]));

	TextOut(hDC, 770, 80, StatusMsg[5], strlen(StatusMsg[5]));

	if ( this->m_bValidJSConnection == FALSE )
	{
		SetTextColor(hDC, RGB(255, 0, 0));
		TextOut(hDC, 95, 80, StatusMsg[7], strlen(StatusMsg[7]));
	}
	else
	{
		SetTextColor(hDC, RGB(0, 255,0));
		TextOut(hDC, 95, 80, StatusMsg[6], strlen(StatusMsg[6]));
	}
	// ----
	if ( this->m_bValidFSConnection == FALSE || m_bValidDSConnection == FALSE)
	{
		SetTextColor(hDC, RGB(255, 0, 0));
		TextOut(hDC, 150+86, 80, StatusMsg[7], strlen(StatusMsg[7]));
	}
	else
	{
		SetTextColor(hDC, RGB(0, 255,0));
		TextOut(hDC, 150+86, 80, StatusMsg[6], strlen(StatusMsg[6]));
	}

	// ----

	if ( this->m_bValidEXDSConnection == FALSE )
	{
		SetTextColor(hDC, RGB(255, 0, 0));
		TextOut(hDC, 300+92, 80, StatusMsg[7], strlen(StatusMsg[7]));
	}
	else
	{
		SetTextColor(hDC, RGB(0, 255,0));
		TextOut(hDC, 300+92, 80, StatusMsg[6], strlen(StatusMsg[6]));
	}

	// ----

	if ( this->m_bValidEVDSConnection == FALSE )
	{
		SetTextColor(hDC, RGB(255, 0, 0));
		TextOut(hDC, 450+92, 80, StatusMsg[7], strlen(StatusMsg[7]));
	}
	else
	{
		SetTextColor(hDC, RGB(0, 255,0));
		TextOut(hDC, 450+92, 80, StatusMsg[6], strlen(StatusMsg[6]));
	}

	// ----

	if ( this->m_bValidRKDSConnection == FALSE )
	{
		SetTextColor(hDC, RGB(255, 0, 0));
		TextOut(hDC, 600+108, 80, StatusMsg[7], strlen(StatusMsg[7]));
	}
	else
	{
		SetTextColor(hDC, RGB(0, 255,0));
		TextOut(hDC, 600+108, 80, StatusMsg[6], strlen(StatusMsg[6]));
	}

	// ----

	if ( m_bValidFSConnection == FALSE )	//New Game Shop
	{
		SetTextColor(hDC, RGB(255, 0, 0));
		TextOut(hDC, 770+123, 80, StatusMsg[7], strlen(StatusMsg[7]));
	}
	else
	{
		SetTextColor(hDC, RGB(0, 255,0));
		TextOut(hDC, 770+123, 80, StatusMsg[6], strlen(StatusMsg[6]));
	}

	SetTextColor(hDC, RGB(255, 255, 255));
	TextOutA(hDC, GAMESERVER_WIDTH - 160, 5, DeveloperMessage[0], strlen(DeveloperMessage[0]));
	TextOutA(hDC, GAMESERVER_WIDTH - 160, 20, DeveloperMessage[1], strlen(DeveloperMessage[1]));
	TextOutA(hDC, GAMESERVER_WIDTH - 160, 35, DeveloperMessage[2], strlen(DeveloperMessage[2]));	//Added Season

	if(g_ExLicense.m_Enable)
	{
		char szLicense[50] = { 0 };
		sprintf(szLicense, "License: %s", g_ExLicense.GetLicenseName());
		TextOutA(hDC, GAMESERVER_WIDTH - 160, 50, szLicense, strlen(szLicense));
	}

	TextOutA(hDC, GAMESERVER_WIDTH - 940, 5, DeveloperMessage[3], strlen(DeveloperMessage[3]));


	if (g_ExLicense.m_Enable && g_ExLicense.NewVersion)
	{
		g_ExLicense.DrawVersion = !g_ExLicense.DrawVersion;

		if(g_ExLicense.DrawVersion)
		{
			SetTextColor(hDC, RGB(255, 0, 0));
			TextOutA(hDC, GAMESERVER_WIDTH - 940, 17+10, EXNEW_VERISON, strlen(EXNEW_VERISON));

			char InfoServer[50] = { 0 };
			sprintf(InfoServer,"Version: %s",g_ExLicense.VersionNum);
			TextOutA(hDC, GAMESERVER_WIDTH - 940, 31+10, InfoServer, strlen(InfoServer));

			char InfoServer2[50] = { 0 };
			sprintf(InfoServer2,"Date: %s",g_ExLicense.VersionDate);
			TextOutA(hDC, GAMESERVER_WIDTH - 940, 45+10, InfoServer2, strlen(InfoServer2));
		}
	}

	if (g_ExLicense.m_Enable)
	{

	}
#else

	if ( this->m_bValidJSConnection != FALSE && this->m_bValidDSConnection != FALSE && this->m_bValidFSConnection != FALSE )
		FillRect(hDC, &rect, this->m_hNormalBrush);
	else
		FillRect(hDC, &rect, this->m_hAbnormalBrush);

	if ( this->m_bValidJSConnection == FALSE )
	{
		SetTextColor(hDC, RGB(255, 0, 0));
		TextOut(hDC, iTopLeftX, iTopLeftY+iLineCount*15, ErrorMessge[0], strlen(ErrorMessge[0]));
		iLineCount++;
	}

	if ( this->m_bValidFSConnection == FALSE )
	{
		SetTextColor(hDC, RGB(255, 0, 0));
		TextOut(hDC, iTopLeftX,  iTopLeftY+iLineCount*15, ErrorMessge[1], strlen(ErrorMessge[1]));
		iLineCount++;
	}

	if ( this->m_bValidDSConnection == FALSE )
	{
		SetTextColor(hDC, RGB(255, 0, 0));
		TextOut(hDC, iTopLeftX, iTopLeftY+iLineCount*15, ErrorMessge[2], strlen(ErrorMessge[2]));
		iLineCount++;
	}

	if ( this->m_bValidEXDSConnection == FALSE )
	{
		SetTextColor(hDC, RGB(255, 0, 0));
		TextOut(hDC, iTopLeftX, iTopLeftY+iLineCount*15, ErrorMessge[3], strlen(ErrorMessge[3]));
		iLineCount++;
	}

	if ( this->m_bValidEVDSConnection == FALSE )
	{
		SetTextColor(hDC, RGB(255, 0, 0));
		TextOut(hDC, iTopLeftX,  iTopLeftY+iLineCount*15, ErrorMessge[4], strlen(ErrorMessge[4]));
		iLineCount++;
	}

	if ( this->m_bValidRKDSConnection == FALSE )
	{
		SetTextColor(hDC, RGB(255, 0, 0));
		TextOut(hDC, iTopLeftX, iTopLeftY+iLineCount*15, ErrorMessge[5], strlen(ErrorMessge[5]));
		iLineCount++;
	}

#endif

	if ( this->m_bValidJSConnection == FALSE || this->m_bValidDSConnection == FALSE || this->m_bValidFSConnection == FALSE || this->m_bValidEXDSConnection == FALSE || this->m_bValidEVDSConnection == FALSE || this->m_bValidRKDSConnection == FALSE )
	{
		SERVER_CONN_STATE_LOG.Output("Server Interconnection Check - [FS/%d] [DS/%d] [EX/%d] [ES/%d] [RS/%d]", this->m_bValidFSConnection, this->m_bValidDSConnection, this->m_bValidEXDSConnection, this->m_bValidEVDSConnection,	this->m_bValidRKDSConnection);
	}

	HFONT pOldFont = (HFONT)SelectObject(hDC, this->m_hFont);

#if(NEW_WINDOW==1)	//GAMESERVER_WIDTH / 2 - 100
	//SetTextColor(hDC, RGB(123, 123, 250));
	//SetTextColor(hDC, RGB(130, 170, 190));
	SetTextColor(hDC, RGB(33, 200, 219));
	TextOutA(hDC, GAMESERVER_WIDTH / 2 - 320, 15, ServerTypeText[0], strlen(ServerTypeText[0]));
#else
	SetTextColor(hDC, RGB(250, 250, 250));
	TextOut(hDC, 250, 20, ServerTypeText[0], strlen(ServerTypeText[0]));
#endif
	
	SelectObject(hDC, pOldFont);
	SetBkMode(hDC, iOldBkMode);
	ReleaseDC(hWnd, hDC);
}