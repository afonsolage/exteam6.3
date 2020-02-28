#include "stdafx.h"
#include "Server.h"
#include "JoinServer.h"
#include "DataServer.h"
#include "Ranking.h"
#include "EventServer.h"
#include "Window.h"
#include "CashShopServer.h"
#include "ExDataServer.h"
#include "eXWindow.h"

char SQLUser[64];
char SQLPass[64];

int g_ServerGroup = -1;

char szLogPath[MAX_SERVERTYPE][20] = {
	"JoinServer",
	"DataServer",
#if(ENABLE_DATASERVER2)
	"DataServer2",
#endif
#if(ENABLE_EXDATASERVER)
	"ExDataServer",
#endif
	"EventServer",
	"Ranking",
	"CashShop",
};

BOOL g_bIsServer[MAX_SERVERTYPE] = {FALSE};

ServerObject_Struct gSObj[MAX_SERVEROBJECT];
int gSObjCount=0;

short gSObjAddSearch()
{
	int count = gSObjCount;
	int totalcount=0;

	while( true )
	{
		if( gSObj[count].Connected == 0 )
		{
			return (short)count;
		}
	
		count++;

		if( count >= MAX_SERVEROBJECT ) count = 0;

		totalcount++;
		if( totalcount >= MAX_SERVEROBJECT )
		{
			//MsgBox("error-L3 : Add fail %s %d", __FILE__, __LINE__);
			break;
		}
	}

	return -1;
}

void gSObjInit()
{
	memset(gSObj, 0, sizeof(ServerObject_Struct) * MAX_SERVEROBJECT);

	for(int i = 0; i < MAX_SERVEROBJECT; i++)
	{
		gSObj[i].Connected = 0;
		gSObj[i].m_socket = INVALID_SOCKET;
		gSObj[i].ProtocolCore = NULL;
		gSObj[i].SType = -1;
	}
}

short gSObjAdd(SOCKET socket, char *ip,int aIndex , DWORD S_TYPE)
{
	gSObj[aIndex].Connected = 1;
	strcpy(gSObj[aIndex].Ip , ip);
	gSObj[aIndex].m_socket = socket;
	gSObj[aIndex].SType = S_TYPE;
	gSObj[aIndex].ServerCode = -1;

	gSObjCount++;

	switch(S_TYPE)
	{
	case ST_JOINSERVER:
		gSObj[aIndex].ProtocolCore = &JSProtocolCore;
		break;
	case ST_DATASERVER:
		gSObj[aIndex].ProtocolCore = &DSProtocolCore;
		break;
#if(ENABLE_DATASERVER2)
	case ST_DATASERVER2:
		gSObj[aIndex].ProtocolCore = &DSProtocolCore;
		break;
#endif
#if(ENABLE_EXDATASERVER)
	case ST_EXDATASERVER:
		gSObj[aIndex].ProtocolCore = &EDSProtocolCore;
		break;
#endif
	case ST_RANKINGSERVER:
		gSObj[aIndex].ProtocolCore = &RSProtocolCore;
		break;
	case ST_EVENTSERVER:
		gSObj[aIndex].ProtocolCore = &ESProtocolCore;
		break;
	case ST_CASHSHOPSERVER:
		gSObj[aIndex].ProtocolCore = &CSProtocolCore;
		break;
	}

return TRUE;
}

short gSObjDel(int index)
{
	if( gSObj[index].Connected < 1 ) return -1;

	DWORD S_TYPE = gSObj[index].SType;

	gSObj[index].Connected = 0;
	gSObjCount--;

	switch(S_TYPE)
	{
	case ST_JOINSERVER:
		g_JSData.Del(index);
		gObjAllDelete(index);
		break;
#if(ENABLE_MYFIXCODE)
	//case ST_EXDATASERVER:
	//	g_Window.ServerLogAdd(S_TYPE,"[ %s ][ %s:%d ] Test close", gSObj[index].ServerName, gSObj[index].Ip, gSObj[index].Port);
	//	break;
#endif
	}

	g_Window.ServerLogAdd(S_TYPE,"[ %s ][ %s:%d ] GameServer Close", gSObj[index].ServerName, gSObj[index].Ip, gSObj[index].Port);
	return 1;
}


BOOL ServersInit()
{
BOOL bRet = FALSE;

	IocpServerStart();

	gSObjInit();

#if(ENABLE_NEW_WINDOW)
	bool JoinEnable = false;
	bool DataEnable = false;
	bool Data2Enable = false;
	bool ExDBEnable = false;
	bool RankingEnable = false;
	bool EventEnable = false;
	bool CashEnable = false;
#endif

//	bIsLog = GetPrivateProfileInt(INI_SECTION,"WriteLog",FALSE,INI_FILE);

	GetPrivateProfileString(INI_SECTION,"SQLUser","sa",SQLUser,sizeof(SQLUser),INI_FILE);
	GetPrivateProfileString(INI_SECTION,"SQLPass","",SQLPass,sizeof(SQLPass),INI_FILE);

	if(GetPrivateProfileInt(JS_INISECTION,"Enabled",FALSE,INI_FILE) == TRUE)
	{
#if(ENABLE_NEW_WINDOW)
		JoinEnable = true;
#endif
		bRet = TRUE;
		JoinServerInit();
		Sleep(20);
	}

	if(GetPrivateProfileInt(DS_INISECTION,"Enabled",FALSE,INI_FILE) == TRUE)
	{
#if(ENABLE_NEW_WINDOW)
		DataEnable = true;
#endif
		bRet = TRUE;
		DataServerInit();
		Sleep(20);
	}

#if(ENABLE_DATASERVER2)
	if(GetPrivateProfileInt(DS2_INISECTION,"Enabled",FALSE,INI_FILE) == TRUE)
	{
#if(ENABLE_NEW_WINDOW)
		Data2Enable = true;
#endif
		bRet = TRUE;
		DataServer2Init();
		Sleep(20);
	}
#endif

#if(ENABLE_EXDATASERVER)
	if(GetPrivateProfileInt(EXDS_INISECTION,"Enabled",FALSE,INI_FILE) == TRUE)
	{
#if(ENABLE_NEW_WINDOW)
		ExDBEnable = true;
#endif
		bRet = TRUE;
		ExDataServerInit();
		Sleep(20);
	}
#endif

	if(GetPrivateProfileInt(RS_INISECTION,"Enabled",FALSE,INI_FILE) == TRUE)
	{
#if(ENABLE_NEW_WINDOW)
		RankingEnable = true;
#endif
		bRet = TRUE;
		RankingServerInit();
		Sleep(20);
	}

	if(GetPrivateProfileInt(ES_INISECTION,"Enabled",FALSE,INI_FILE) == TRUE)
	{
#if(ENABLE_NEW_WINDOW)
		EventEnable = true;
#endif
		bRet = TRUE;
		EventServerInit();
		Sleep(20);
	}

	if(GetPrivateProfileInt(CS_INISECTION,"Enabled",FALSE,INI_FILE) == TRUE)
	{
#if(ENABLE_NEW_WINDOW)
		CashEnable = true;
#endif
		bRet = TRUE;
		CashShopServerInit();
	}

#if(ENABLE_NEW_WINDOW)

	if(JoinEnable)
	{
		g_WindowEx.UpdateStatusBar(0, "Join Server: Online");
	}
	else
	{
		g_WindowEx.UpdateStatusBar(0, "Join Server: Offline");
	}

	//if(DataEnable)
	//{
	//	g_WindowEx.UpdateStatusBar(1, "Data Server");
	//}
	//else
	//{
	//	g_WindowEx.UpdateStatusBar(1, "Data Server");
	//}

	//if(Data2Enable)
	//{
	//	g_WindowEx.UpdateStatusBar(2, "Data Server 2");
	//}
	//else
	//{
	//	g_WindowEx.UpdateStatusBar(2, "Data Server 2");
	//}
		
	if(ExDBEnable)
	{
		g_WindowEx.UpdateStatusBar(1, "ExDB Server: Online");
	}
	else
	{
		g_WindowEx.UpdateStatusBar(1, "ExDB Server: Offline");
	}

	if(RankingEnable)
	{
		g_WindowEx.UpdateStatusBar(2, "Rank Server: Online");
	}
	else
	{
		g_WindowEx.UpdateStatusBar(2, "Rank Server: Offline");
	}

	if(EventEnable)
	{
		g_WindowEx.UpdateStatusBar(3, "Event Server: Online");
	}
	else
	{
		g_WindowEx.UpdateStatusBar(3, "Event Server: Offline");
	}

	//if(CashEnable)
	//{
	//	g_WindowEx.UpdateStatusBar(6, "Cash Shop");
	//}
	//else
	//{
	//	g_WindowEx.UpdateStatusBar(6, "Cash Shop");
	//}

#endif

	return bRet;
}

BOOL gSObjSetInfo(int aIndex, WORD port, int type, char * servername)
{
	if( gSObj[aIndex].Connected  < 1 ) {
		g_Window.ServerLogAdd(gSObj[aIndex].SType,"Error : Server not connected");
		return FALSE;
	}
		
	if( gSObj[aIndex].Connected  == 2 ) {
		g_Window.ServerLogAdd(gSObj[aIndex].SType,"error-L2 : Server information setting error (%d)",gSObj[aIndex].Connected);
		return FALSE;
	}

	gSObj[aIndex].Connected = 2;
	gSObj[aIndex].Port = port;
	gSObj[aIndex].Type = type;
	strcpy(gSObj[aIndex].ServerName, servername);
	
	g_Window.ServerLogAdd(gSObj[aIndex].SType,"[ %s ][ %s:%d ] GameServer Connect ", servername, gSObj[aIndex].Ip, port);
	return TRUE;
}

BOOL gSObjSetInfo(int aIndex, WORD port, int type, WORD ServerCode, char * servername)
{
	if( gSObj[aIndex].Connected  < 1 ) {
		g_Window.ServerLogAdd(gSObj[aIndex].SType,"Error : Server not connected");
		return FALSE;
	}
		
	if( gSObj[aIndex].Connected  == 2 ) {
		g_Window.ServerLogAdd(gSObj[aIndex].SType,"error-L2 : Server information setting error (%d)",gSObj[aIndex].Connected);
		return FALSE;
	}

	gSObj[aIndex].Connected = 2;
	gSObj[aIndex].Port = port;
	gSObj[aIndex].Type = type;
	gSObj[aIndex].ServerCode = ServerCode;
	strcpy(gSObj[aIndex].ServerName, servername);
	
	g_Window.ServerLogAdd(gSObj[aIndex].SType,"[ %s ][ %s:%d ] GameServer Connect ", servername, gSObj[aIndex].Ip, port);
	return TRUE;
}