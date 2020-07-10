#include "StdAfx.h"
#include "ConnectEx.h"
#include "GameMain.h"
#include "user.h"
#include "ConMember.h"
#include "..\common\winutil.h"
#include "logproc.h"
#include "DBSockMng.h"
#include "DSProtocol.h"
#include "SProtocol.h"
#include "Configs.h"
#include "ExLicense.h"
#include "OfflineMode.h"
#include "ExGDManager.h"
#include "MUHelperOffline.h"
// -------------------------------------------------------------------------------

#if(_RECONNECT_)
// -------------------------------------------------------------------------------

ConnectEx g_ConnectEx;
// -------------------------------------------------------------------------------

BOOL PacketCheckTime2(LPOBJ lpObj) 
{
	//LogAddC(2, "[DEBUG][2] PACKET TIME: %d", ( GetTickCount() - lpObj->m_PacketCheckTime ));

	if( (GetTickCount() - lpObj->m_PacketCheckTime) < 300 )
	{
		return FALSE;
	}

	lpObj->m_PacketCheckTime = GetTickCount();
	return TRUE;
}
// -------------------------------------------------------------------------------

ConnectEx::ConnectEx()
{
	this->Init();
}
// -------------------------------------------------------------------------------

void ConnectEx::Init()
{
	this->ConnectIndex = -1;
	this->ConnectTick = 0;
}
// -------------------------------------------------------------------------------

void ConnectEx::SendLogin(int UserIndex, CONNECTEX_LOGIN * Data)
{
	if(!ExConfig.CommonServer.ReConnect) return;
	// ----
	if(this->ConnectIndex != -1)
	{
		return;
	}
	this->ConnectIndex = UserIndex;
	this->ConnectTick = GetTickCount();
	// ----
	BuxConvert(Data->AccountID, MAX_ACCOUNT_LEN);
	BuxConvert(Data->Password, MAX_ACCOUNT_LEN);
	// ----
	char id[11];
	id[10]=0;
	memcpy(id, Data->AccountID, sizeof(Data->AccountID));
	BuxConvert(id, MAX_ACCOUNT_LEN);

	//char pass[20+1];
	//memset(pass, 0, sizeof(pass));
	//memcpy(pass, lpMsg->Pass, sizeof(lpMsg->Pass));
	//BuxConvert(pass, MAX_ACCOUNT_LEN);
	//memcpy(gObj[aIndex].Pass, pass, MAX_ACCOUNT_LEN);
	// ----
	//GJPUserClose(id); //Force connection
	// ----
	if( bCanConnectMember == TRUE )
	{
		if( ConMember.IsMember(id) == FALSE )
		{
			GCJoinResult(JS_ONLY_VIP_MEMBERS, UserIndex);
			return;
		}
	}

	// ----
	LPOBJ lpObj = &gObj[UserIndex];
	// ----
	if( gObj[UserIndex].Connected != PLAYER_CONNECTED )
	{
		LogAdd(lMsg.Get(MSGGET(1, 218)), UserIndex, id);
		
		CloseClient(UserIndex);
		return;
	}
	// ----
	if( gObj[UserIndex].LoginMsgSnd != FALSE )
	{
		if( gObj[UserIndex].LoginMsgSnd == TRUE )
		{
			LogAdd(lMsg.Get(MSGGET(1, 219)), UserIndex, id, gObj[UserIndex].Ip_addr );
		}
		else
		{
			LogAdd("error : %d %s %d", gObj[UserIndex].LoginMsgSnd, __FILE__, __LINE__);
		}

		//return;
	}
	// ----
	if( lpObj->Connected >= PLAYER_LOGGED )
	{
		return;
	}
	// ----
	SDHP_IDPASS spMsg = { 0 };
	// ----
	PHeadSetB((LPBYTE)&spMsg, 0x01, sizeof(spMsg));
	spMsg.Number = UserIndex;
	memcpy(spMsg.Id, Data->AccountID, sizeof(spMsg.Id));
	memcpy(spMsg.Pass, Data->Password, sizeof(spMsg.Pass));
	strcpy(spMsg.IpAddress, gObj[UserIndex].Ip_addr);
	gObj[UserIndex].CheckTick = Data->TickCount;
	gObj[UserIndex].CheckTick2 = GetTickCount();
	gObj[UserIndex].ConnectCheckTime = GetTickCount();
	gObj[UserIndex].CheckSpeedHack = true;
	gObj[UserIndex].LoginMsgSnd = 1;
	gObj[UserIndex].LoginMsgCount = 1;
#ifdef DISCONECT_FRIEND
	if( g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(ulasevich) || g_ExLicense.CheckUser(ulasevich2) || 
		g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2)
		|| g_ExLicense.CheckUser(eExUB::MU2Play) || g_ExLicense.CheckUser(eExUB::Sentinel) || g_ExLicense.CheckUser(eExUB::Escalate) || g_ExLicense.CheckUser(eExUB::Artem) ||
		g_ExLicense.CheckUser(eExUB::Artem2) || g_ExLicense.CheckUser(eExUB::RevoMU) || g_ExLicense.CheckUser(eExUB::GloryMU) || 
		g_ExLicense.CheckUser(eExUB::mu4you) || g_ExLicense.CheckUser(eExUB::eternalmu) || g_ExLicense.CheckUser(eExUB::NSGames))
	{
#define MAX_PASS_LEN 20
		ZeroMemory(&gObj[UserIndex].Pass,sizeof(gObj[UserIndex].Pass));
		char pass[MAX_PASS_LEN+1];
		pass[MAX_PASS_LEN]=0;
		memcpy(pass, Data->Password, sizeof(Data->Password));
		BuxConvert(pass, MAX_ACCOUNT_LEN);
		gObj[UserIndex].Pass[MAX_ACCOUNT_LEN] = 0;
		memcpy(gObj[UserIndex].Pass, pass, MAX_ACCOUNT_LEN);
	}
#endif // DISCONECT_FRIEND
	gObj[UserIndex].AccountID[MAX_ACCOUNT_LEN] = 0;
	gObj[UserIndex].Name[MAX_ACCOUNT_LEN] = 0;
	memcpy(gObj[UserIndex].AccountID, id, MAX_ACCOUNT_LEN);
	memcpy(gObj[UserIndex].Name, Data->Name, MAX_ACCOUNT_LEN);
	gObj[UserIndex].m_cAccountItemBlock = 0;
	gObj[UserIndex].m_ConnectEx = true;
	gObj[UserIndex].ukn_30 = 0;
	// ----
	wsJServerCli.DataSend((char*)&spMsg, spMsg.h.size);
	LogAddTD("join send : (%d)%s", UserIndex, gObj[UserIndex].AccountID);
	
	lpObj->m_bMapSvrMoveReq = false;
	lpObj->m_sPrevMapSvrCode = -1; 
	lpObj->m_sDestMapNumber = -1;
	lpObj->m_btDestX = 0;
	lpObj->m_btDestY = 0;
}
// -------------------------------------------------------------------------------

void ConnectEx::SendGame(int UserIndex)
{
	if(!ExConfig.CommonServer.ReConnect) return;
	// ----
	gObj[UserIndex].m_ConnectEx = false;
	DataServerGetCharListRequest(UserIndex);
	// ----
	if ( !PacketCheckTime2(&gObj[UserIndex]))
	{
		return;
	}
	// ----
	if ( !gObjIsAccontConnect(UserIndex, gObj[UserIndex].AccountID))
	{
		return;
	}
	// ----
	if ( gObj[UserIndex].Connected == PLAYER_PLAYING )
	{
		return;
	}
	// ----
	gObj[UserIndex].bEnableDelCharacter = FALSE;
	// ----
	char _name[MAX_ACCOUNT_LEN+1];
	SDHP_DBCHARINFOREQUEST pCRequest;
	// ----
	PHeadSetB((LPBYTE)&pCRequest, 0x06, sizeof(pCRequest));
	memset(_name, 0, MAX_ACCOUNT_LEN);

	memcpy(_name, gObj[UserIndex].Name, MAX_ACCOUNT_LEN);

	BuxConvert(_name, MAX_ACCOUNT_LEN);
	memcpy(pCRequest.Name, _name, MAX_ACCOUNT_LEN);
	strcpy(pCRequest.AccountID, gObj[UserIndex].AccountID);
	pCRequest.Number = UserIndex;
	// ----
	cDBSMng.Send((char*)&pCRequest, pCRequest.h.size);
}
// -------------------------------------------------------------------------------

void ConnectEx::SendClose(int UserIndex, int Type)
{
	if(!ExConfig.CommonServer.ReConnect)
	{
		CloseClient(UserIndex);
		return;
	}
	// ----
	CONNECTEX_CLOSE pRequest;
	gObj[UserIndex].DisconnectType = Type;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0xC, sizeof(CONNECTEX_CLOSE));
	DataSend(UserIndex, (LPBYTE)&pRequest, pRequest.h.size);
}
// -------------------------------------------------------------------------------

void ConnectEx::RecvClose(int UserIndex)
{
	LPOBJ lpObj = &gObj[UserIndex];

#if(OFFLINE_MODE==TRUE)
	if(lpObj->DisconnectType == TRUE)
	{
		GCCloseMsgSend(UserIndex, 2);
		//CloseClient(UserIndex);
		lpObj->m_OfflineMode = TRUE;//lpObj->DisconnectType;
		#if(OFFLINE_MODE_RESTORE)
		GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
		g_OfflineMode.GDUpdateData(UserIndex);
		#endif
		g_ExGDManager.GD_OfflineAfk(UserIndex, 1, 0);
		return;
	}
#endif

	if(lpObj->DisconnectType == NORM_DC)
	{
		CloseClient(UserIndex);
	}
	else
	{
		GCCloseMsgSend(UserIndex, 2);
	}

	if(lpObj->DisconnectType == OFFZEN_DC)
	{
		lpObj->OffTrade = lpObj->DisconnectType;
		g_ExGDManager.GD_OfflineAfk(UserIndex, 1, 0);
	}
	else if(lpObj->DisconnectType == OFFCR_DC)
	{
		lpObj->OffTrade = lpObj->DisconnectType;
		g_ExGDManager.GD_OfflineAfk(UserIndex, 1, 0);
	}
	else if(lpObj->DisconnectType == OFFWC_DC)
	{
		lpObj->OffTrade = lpObj->DisconnectType;
		g_ExGDManager.GD_OfflineAfk(UserIndex, 1, 0);
	}
	else if(lpObj->DisconnectType == OFFWP_DC)
	{
		lpObj->OffTrade = lpObj->DisconnectType;
		g_ExGDManager.GD_OfflineAfk(UserIndex, 1, 0);
	}
	else if(lpObj->DisconnectType == OFFWG_DC)
	{
		lpObj->OffTrade = lpObj->DisconnectType;
		g_ExGDManager.GD_OfflineAfk(UserIndex, 1, 0);
	}
	else if(lpObj->DisconnectType == OFFCHAOS_DC)
	{
		lpObj->OffTrade = lpObj->DisconnectType;
		g_ExGDManager.GD_OfflineAfk(UserIndex, 1, 0);
	}
	else if(lpObj->DisconnectType == OFFBLESS_DC)
	{
		lpObj->OffTrade = lpObj->DisconnectType;
		g_ExGDManager.GD_OfflineAfk(UserIndex, 1, 0);
	}
	else if(lpObj->DisconnectType == OFFSOUL_DC)
	{
		lpObj->OffTrade = lpObj->DisconnectType;
		g_ExGDManager.GD_OfflineAfk(UserIndex, 1, 0);
	}
	else if(lpObj->DisconnectType == OFFLIFE_DC)
	{
		lpObj->OffTrade = lpObj->DisconnectType;
		g_ExGDManager.GD_OfflineAfk(UserIndex, 1, 0);
	}
	else if(lpObj->DisconnectType == OFFAFK_DC)
	{
		lpObj->OffExp = 1;
		g_ExGDManager.GD_OfflineAfk(UserIndex, 1, 1);
		
	}
}


void ConnectEx::Timer()
{
	if(!ExConfig.CommonServer.ReConnect)
	{
		return;
	}

	if(this->ConnectIndex == -1)
	{
		return;
	}

	DWORD ConnectTime = GetTickCount() - this->ConnectTick;

	if(ConnectTime > 1000)
	{
		this->ConnectIndex = -1;
		this->ConnectTick = 0;
	}
}


#endif
// -------------------------------------------------------------------------------