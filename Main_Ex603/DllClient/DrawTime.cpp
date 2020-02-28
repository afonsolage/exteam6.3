#include "stdafx.h"
#include "Interface.h"
#include "DrawTime.h"
#include "ExLicense.h"
#include "ExText.h"

ServerTime g_ServerTime;

void TimeImageLoad()
{
	gInterface.LoadImages("Custom\\Interface\\TimeBar.tga", 0x787E, 0x2601, 0x2900, 1);
}

void TimeLoad()
{
	gInterface.BindObject(eTIME, 0x787E, 131, 70, -10, 359 + 22);
	gInterface.Data[eTIME].OnShow = true;
}

void DrawTime()
{
	if( !gInterface.Data[eTIME].OnShow )
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

	if( g_ExLicense.CheckUser(eExUB::Local) ||
		g_ExLicense.CheckUser(eExUB::Gredy) ||
		g_ExLicense.CheckUser(eExUB::Gredy2) ||
		g_ExLicense.CheckUser(eExUB::GredyLocal) ||
		g_ExLicense.CheckUser(eExUB::Artem) || 
		g_ExLicense.CheckUser(eExUB::Artem2) ||
		g_ExLicense.CheckUser(eExUB::Stone))
	{
		gInterface.Data[eTIME].Y = 359;
		gInterface.DrawGUI(eTIME, gInterface.Data[eTIME].X, gInterface.Data[eTIME].Y);
	}
	else
	{
		gInterface.DrawGUI(eTIME, gInterface.Data[eTIME].X, gInterface.Data[eTIME].Y);
	}

	time_t TimeServer;
	struct tm * ServerT, *LocalT;
	time(&TimeServer);

	ServerT = localtime(&TimeServer);

	char ServerTimeName[25] = "Server:";
	char ServerTime[30];

	char LocalTimeName[25] = "Local:";
	char LocalTime[30];

	if( g_ExLicense.CheckUser(eExUB::Local) ||
		g_ExLicense.CheckUser(eExUB::Gredy) ||
		g_ExLicense.CheckUser(eExUB::Gredy2) ||
		g_ExLicense.CheckUser(eExUB::GredyLocal) ||
		g_ExLicense.CheckUser(eExUB::Artem) || 
		g_ExLicense.CheckUser(eExUB::Artem2) ||
		g_ExLicense.CheckUser(eExUB::Stone))
	{
		sprintf(ServerTime, "%2d:%02d:%02d", g_ServerTime.m_Hour, g_ServerTime.m_Minute, g_ServerTime.m_Second);
	}

	sprintf(LocalTime, "%2d:%02d:%02d", ServerT->tm_hour, ServerT->tm_min, ServerT->tm_sec);

	gInterface.DrawFormat(eGold, 5, 391+22, 50, 1, g_ExText.GetText(16));
	gInterface.DrawFormat(eWhite, 55, 391+22, 100, 1, LocalTime);

	if( g_ExLicense.CheckUser(eExUB::Local) ||
		g_ExLicense.CheckUser(eExUB::Gredy) ||
		g_ExLicense.CheckUser(eExUB::Gredy2) ||
		g_ExLicense.CheckUser(eExUB::GredyLocal) ||
		g_ExLicense.CheckUser(eExUB::Artem) ||
		g_ExLicense.CheckUser(eExUB::Artem2) ||
		g_ExLicense.CheckUser(eExUB::Stone))
	{
		gInterface.DrawFormat(eGold, 5, 391, 50, 1, ServerTimeName);
		gInterface.DrawFormat(eWhite, 55, 391, 100, 1, ServerTime);
	}

}

void GCServerTime(PMSG_SERVER_TIME* lpMsg)
{
	g_ServerTime.m_Hour = lpMsg->Hour;
	g_ServerTime.m_Minute = lpMsg->Minute;
	g_ServerTime.m_Second = lpMsg->Second;
}