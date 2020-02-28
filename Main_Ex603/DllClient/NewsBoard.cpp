#include "stdafx.h"
#include "NewsBoard.h"
#include "Interface.h"
#include "Protocol.h"
#include "Console.h"
#include "ExText.h"

#if(CUSTOM_NEWS==TRUE)
// -------------------------------------------------------------------------------

NewsBoard g_NewsBoard;
// -------------------------------------------------------------------------------

NewsBoard::NewsBoard()
{
	this->m_LoadedCount		= 0;
	this->m_LastRefreshTick = 0;
	this->m_LastRefreshMin	= 0;
	// ----
	for( int i = 0; i < MAX_NEWS_LIST; i++ )
	{
		this->m_Data[i].Title.Date[0]	= 0;
		this->m_Data[i].Title.Time[0]	= 0;
		this->m_Data[i].Title.Text[0]	= 0;
		this->m_Data[i].Text[0]			= 0;
		this->m_Data[i].LastRefreshTick	= 0;
		this->m_Data[i].LastRefreshMin	= 0;
	}
}
// -------------------------------------------------------------------------------

NewsBoard::~NewsBoard()
{
	// ----
}
// -------------------------------------------------------------------------------

void NewsBoard::Init(BYTE ID)
{
	ZeroMemory(this->m_Data[ID].Title.Date, sizeof(this->m_Data[ID].Title.Date)-1);
	ZeroMemory(this->m_Data[ID].Title.Time, sizeof(this->m_Data[ID].Title.Time)-1);
	ZeroMemory(this->m_Data[ID].Title.Text, sizeof(this->m_Data[ID].Title.Text)-1);
	ZeroMemory(this->m_Data[ID].Text, sizeof(this->m_Data[ID].Text)-1);
}
// -------------------------------------------------------------------------------

void NewsBoard::ReqOpenMain()
{
	DWORD CurrentTick		= GetTickCount();
	this->m_LastRefreshMin	= (CurrentTick - this->m_LastRefreshTick) / 60000;
	// ----
	//if( this->m_LastRefreshMin <= MIN_NEWS_REFRESH )
	//{
	//	gInterface.OpenWindowEx(exWinNews);
	//	return;
	//}
	// ----
	NEWS_REQ_NEWS pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFD, sizeof(pRequest));
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// -------------------------------------------------------------------------------

void NewsBoard::OpenMain(NEWS_ANS_TITLES * Answer)
{
	if( Answer->RealCount < 0 || Answer->RealCount > MAX_NEWS_LIST )
	{
		return;
	}
	// ----
	this->m_LastRefreshTick = GetTickCount();
	this->m_LastRefreshMin	= 0;
	this->m_LoadedCount		= Answer->RealCount;
	// ----
	for( int i = 0; i < Answer->RealCount; i++ )
	{
		ZeroMemory(this->m_Data[i].Title.Date, sizeof(this->m_Data[i].Title.Date)-1);
		ZeroMemory(this->m_Data[i].Title.Time, sizeof(this->m_Data[i].Title.Time)-1);
		ZeroMemory(this->m_Data[i].Title.Text, sizeof(this->m_Data[i].Title.Text)-1);
		// ----
		strcpy(this->m_Data[i].Title.Date, Answer->Titles[i].Date);
		strcpy(this->m_Data[i].Title.Time, Answer->Titles[i].Time);
		strcpy(this->m_Data[i].Title.Text, Answer->Titles[i].Text);
	}
	// ----
	gInterface.OpenWindowEx(exWinNews);
}
// -------------------------------------------------------------------------------

void NewsBoard::ReqOpenItem(BYTE ID)
{
	DWORD CurrentTick				= GetTickCount();
	this->m_Data[ID].LastRefreshMin	= (CurrentTick - this->m_Data[ID].LastRefreshTick) / 60000;
	// ----
	//if( this->m_Data[ID].LastRefreshMin <= MIN_NEWS_REFRESH_PAGE )
	//{
	//	return;
	//}
	NEWS_REQ_NEWS pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFE, sizeof(pRequest));
	pRequest.ID = ID;
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// -------------------------------------------------------------------------------

void NewsBoard::OpenItem(NEWS_ANS_NEWS * Answer)
{
	if( Answer->ID < 0 || Answer->ID > MAX_NEWS_LIST )
	{
		return;
	}
	// ----
	this->Init(Answer->ID);
	// ----
	strcpy(this->m_Data[Answer->ID].Title.Date, Answer->News.Title.Date);
	strcpy(this->m_Data[Answer->ID].Title.Time, Answer->News.Title.Time);
	strcpy(this->m_Data[Answer->ID].Title.Text, Answer->News.Title.Text);
	strcpy(this->m_Data[Answer->ID].Text, Answer->News.Text);
	this->m_Data[Answer->ID].LastRefreshTick	= GetTickCount();
	this->m_Data[Answer->ID].LastRefreshMin		= 0;
}
// -------------------------------------------------------------------------------

void NewsBoard::DrawNewsWindow()
{
	if(!gInterface.CheckWindowEx(exWinNews))
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
	gInterface.DrawGUI(eNEWS_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eNEWS_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eNEWS_FRAME, StartX, StartY + 67.0, 13);
	gInterface.DrawGUI(eNEWS_FOOTER, StartX, StartY);
	gInterface.DrawGUI(eNEWS_CLOSE, StartX + MainWidth - gInterface.Data[eNEWS_CLOSE].Width, gInterface.Data[eNEWS_TITLE].Height + gInterface.Data[eNEWS_CLOSE].Height + 2);
	// ----
	if( gInterface.IsWorkZone(eNEWS_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eNEWS_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eNEWS_CLOSE, gInterface.Data[eNEWS_CLOSE].X, gInterface.Data[eNEWS_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[eNEWS_CLOSE].X + 5, gInterface.Data[eNEWS_CLOSE].Y + 25, g_ExText.GetText(78));
	}
	// ----
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, g_ExText.GetText(78));
	// ----
	if( gInterface.Data[eNEWS_MAIN].Attribute == 0 )
	{
		for( int i = 0; i < g_NewsBoard.m_LoadedCount; i++ )
		{
			gInterface.DrawGUI(eNEWS_INFOBG, StartX + 30, 140 + (i * 21));
			// ----
			if( gInterface.IsWorkZone(StartX + 30, 140 + (i * 21), StartX + 200, 160 + (i * 21)) )
			{
				gInterface.DrawColoredGUI(eNEWS_INFOBG, StartX + 30,  140 + (i * 21), pMakeColor(255, 204, 20, 200));
			}
			// ----
			gInterface.DrawFormat(eGold, StartX + 19, 145 + (i * 21), 65, 3, g_NewsBoard.m_Data[i].Title.Date);
			//gInterface.DrawFormat(eOrange, StartX + 18, 148 + (i * 21), 65, 3, g_NewsBoard.m_Data[i].Title.Time);
			gInterface.DrawFormat(eWhite, StartX + 80, 145 + (i * 21), 190, 1, g_NewsBoard.m_Data[i].Title.Text);
		}
		// ----
		//gInterface.DrawFormat(eBlue, StartX + 8, 130, 210, 3, "Last refresh: %d min. ago", g_NewsBoard.m_LastRefreshMin);
	}
	else
	{
		BYTE ID = gInterface.Data[eNEWS_MAIN].Attribute - 10;
		// ----
		gInterface.DrawGUI(eNEWS_INFOBG, StartX + 30, 140);
		gInterface.DrawFormat(eGold, StartX + 19, 145, 65, 3, g_NewsBoard.m_Data[ID].Title.Date);
		//gInterface.DrawFormat(eOrange, StartX + 18, 148, 65, 3, g_NewsBoard.m_Data[ID].Title.Time);
		gInterface.DrawFormat(eWhite, StartX + 80, 145, 190, 1, g_NewsBoard.m_Data[ID].Title.Text);
		gInterface.DrawFormat(eWhite, StartX + 15, 170, 200, 1, g_NewsBoard.m_Data[ID].Text);
		// ----
		gInterface.DrawGUI(eNEWS_BACK, ButtonX, gInterface.Data[eNEWS_FOOTER].Y + 10);
		gInterface.DrawFormat(eWhite, StartX + 8, gInterface.Data[eNEWS_FOOTER].Y + 20, 210, 3, g_ExText.GetText(79));
		gInterface.DrawGUI(eNEWS_DIV, StartX, gInterface.Data[eNEWS_FOOTER].Y - 10);
		// ----
		if( gInterface.IsWorkZone(eNEWS_BACK) )
		{
			DWORD Color = eGray100;
			// ----
			if( gInterface.Data[eNEWS_BACK].OnClick )
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(eNEWS_BACK, gInterface.Data[eNEWS_BACK].X, gInterface.Data[eNEWS_BACK].Y, Color);
		}
		// ----
		//gInterface.DrawFormat(eBlue, StartX + 8, 130, 210, 3, "Last page refresh: %d min. ago", g_NewsBoard.m_Data[ID].LastRefreshMin);
	}
}
// ----------------------------------------------------------------------------------------------

bool NewsBoard::EventNewsWindow_Main(DWORD Event)
{
	if(!gInterface.CheckWindowEx(exWinNews))
	{
		return false;
	}

	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	// ----
	for( int i = 0; i < g_NewsBoard.m_LoadedCount; i++ )
	{
		if( gInterface.IsWorkZone(StartX + 30, 140 + (i * 21), StartX + 200, 161 + (i * 21)) )
		{
			if( Event == WM_LBUTTONDOWN && gInterface.Data[eNEWS_MAIN].Attribute == 0 )
			{
				gInterface.Data[eNEWS_MAIN].Attribute = i + 10;
				g_NewsBoard.ReqOpenItem(i);
				return true;
			}
		}
	}
	// ----
	if( gInterface.ButtonEx(Event, eNEWS_CLOSE, false ) )
	{
		gInterface.Data[eNEWS_MAIN].Attribute = 0;
		gInterface.CloseWindowEx(exWinNews);
		return true;
	}
	// ----
	if( gInterface.ButtonEx(Event, eNEWS_BACK, false ) && gInterface.Data[eNEWS_MAIN].Attribute != 0)
	{
		gInterface.Data[eNEWS_MAIN].Attribute = 0;
		return true;
	}
	// ----
	return true;
}
// ----------------------------------------------------------------------------------------------
#endif