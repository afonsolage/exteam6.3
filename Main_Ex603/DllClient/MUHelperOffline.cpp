#include "stdafx.h"
#include "MUHelperOffline.h"
#include "User.h"
#include "Console.h"

CMUHelperOffline g_MUHelperOffline;

CMUHelperOffline::CMUHelperOffline(void)
{
	this->m_active = false;
}


CMUHelperOffline::~CMUHelperOffline(void)
{
}

void CMUHelperOffline::GCAction(MUHELPEROFF_ACTION* lpMsg)
{
	this->m_active = lpMsg->Action >= 1;

	if (this->m_active)
	{
		gObjUser.HideModel();
	}
	else
	{
		gObjUser.ShowModel();
	}
}

void CMUHelperOffline::RestoreState()
{
	if (this->m_active)
	{
		SetTimer(GetForegroundWindow(), MUHELPER_2SEC_TIMER, 2000, NULL);
	}
}

void CMUHelperOffline::Timer()
{
	if (this->m_active)
	{
		Start();
		gObjUser.Refresh();
	}

	KillTimer(pGameWindow, MUHELPER_2SEC_TIMER);
}

void CMUHelperOffline::Start()
{
	PBMSG_HEAD2 pRequest;
	pRequest.set((LPBYTE)&pRequest, LC_HEADER, LC_MUHELPER_OFF_START, sizeof(PBMSG_HEAD2));
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.size);
}

void CMUHelperOffline::Stop()
{
	PBMSG_HEAD2 pRequest;
	pRequest.set((LPBYTE)&pRequest, LC_HEADER, LC_MUHELPER_OFF_STOP, sizeof(PBMSG_HEAD2));
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.size);
}

void CMUHelperOffline::Tick()
{
	//auto state = pPlayerState;
	//auto gameIdx = pGameIndex;
	//lpViewObj lpViewPlayerEx	= &*(ObjectPreview*)oUserPreviewStruct;
	//SetTimer(GetForegroundWindow(), MUHELPER_100MS_TIMER, 100, NULL);
}