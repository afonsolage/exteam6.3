#include "StdAfx.h"
#include "SpotReturn.h"
#include "DSProtocol.h"
#include "DBSockMng.h"
#include "ExUser.h"
#include "GameMain.h"
#include "MUHelper.h"
#include "logproc.h"
#include "ExLicense.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_RETURNSPOT==TRUE)
// ----------------------------------------------------------------------------------------------

SpotReturn g_SpotReturn;
// ----------------------------------------------------------------------------------------------

SpotReturn::SpotReturn()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

SpotReturn::~SpotReturn()
{
}
// ----------------------------------------------------------------------------------------------

void SpotReturn::Init()
{
	this->Enable = false;
	this->CheckTimeStatus = STATUSMAXTIME;
}
// ----------------------------------------------------------------------------------------------

void SpotReturn::Load()
{
	this->Init();

	if(!g_ExLicense.user.SpotReturn)
	{
		return;
	}

	this->Read(gDirPath.GetNewPath("ExData\\SpotReturn.ini"));
}
// ----------------------------------------------------------------------------------------------

void SpotReturn::Read(char* File)
{
	this->Enable = GetPrivateProfileInt("ExTeam", "Enable", 1, File);
	this->CheckTimeStatus = GetPrivateProfileInt("ExTeam", "CheckTimeStatus", STATUSMAXTIME, File);
}
// ----------------------------------------------------------------------------------------------

void SpotReturn::StatusTime()
{
	if(!this->Enable)
	{
		return;
	}

	for (int aUserIndex = OBJ_STARTUSERINDEX; aUserIndex < OBJMAX; aUserIndex++)
	{
		if(OBJMAX_RANGE(aUserIndex) == 0)
		{
			continue;
		}

		LPOBJ lpUser = &gObj[aUserIndex];

		if(lpUser->Connected < PLAYER_PLAYING)
		{
			continue;
		}

		if(ExUserInSafeZone(aUserIndex) == false)
		{
			if(lpUser->StatusNeedHelper == 1 && lpUser->m_MUHelperOn == false )
			{
				g_MUHelper.Start(lpUser);
				lpUser->StatusNeedHelper = 0;
			}
		}

		if(lpUser->StatusCode == 0)
		{
			return;
		}

		if(lpUser->X != lpUser->TX || lpUser->Y != lpUser->TY)
		{
			if(lpUser->StatusCode == 1)
			{
				this->GDStatusUpdate(aUserIndex, eStatusNormal);
			}
			lpUser->StatusCode = 0;
			return;
		}

		lpUser->StatusTime++;

		if(lpUser->StatusTime >= this->CheckTimeStatus)
		{
			this->GDStatus(aUserIndex);
			lpUser->StatusTime = 0;
		}
	}
}
// ----------------------------------------------------------------------------------------------

void SpotReturn::GDStatus(int aUserIndex)
{
	if(OBJMAX_RANGE(aUserIndex) == 0)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aUserIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	PMSG_GD_SPOTSTATUS pMsg = { 0 };
	pMsg.h.set((LPBYTE)&pMsg, 0xE2, 0x05, sizeof(PMSG_GD_SPOTSTATUS));
	memcpy(pMsg.szCharName, lpUser->Name, 11);
	pMsg.Number = lpUser->m_Index;
	cDBSMng.Send((char*)&pMsg, sizeof(pMsg));
}
// ----------------------------------------------------------------------------------------------

void SpotReturn::DGStatus(PMSG_DG_SPOTSTATUS* lpMsg)
{
	if(!lpMsg)
	{
		return;
	}

	int aUserIndex = lpMsg->Number;

	if(OBJMAX_RANGE(aUserIndex) == 0)
	{
		return;
	}

	if( !gObjIsConnectedEx(aUserIndex) )
	{
		return;
	}

	LPOBJ lpUser = &gObj[aUserIndex];

	if(!lpUser)
	{
		return;
	}

	if(ExUserInSafeZone(aUserIndex) == false)
	{
		return;
	}

	if(lpMsg->GetStatus == eStatusKlick)
	{
		gObjTeleport(aUserIndex, lpUser->StatusMap, lpUser->StatusX, lpUser->StatusY);
		this->GDStatusUpdate(aUserIndex, eStatusNormal);
		if(lpUser->OffExp == false || lpUser->OffTrade == false)
		{
			lpUser->StatusNeedHelper = 1;
		}
		lpUser->StatusCode = 0;
	}
}
// ----------------------------------------------------------------------------------------------

void SpotReturn::GDStatusUpdate(int aUserIndex, BYTE eStatus)
{
	PMSG_GD_SPOTSTATUS_UPDATE pMsg = { 0 };
	pMsg.h.set((LPBYTE)&pMsg, 0xE2, 0x06, sizeof(PMSG_GD_SPOTSTATUS_UPDATE));

	if(OBJMAX_RANGE(aUserIndex) == 0)
	{
		return;
	}

	if( !gObjIsConnectedEx(aUserIndex) )
	{
		return;
	}

	LPOBJ lpUser = &gObj[aUserIndex];

	memcpy(pMsg.szCharName, lpUser->Name, 11);
	pMsg.GetStatus = eStatus;

	cDBSMng.Send((char*)&pMsg, sizeof(pMsg));
}
// ----------------------------------------------------------------------------------------------

void SpotReturn::StatusSave(int aUserIndex)
{
	if(OBJMAX_RANGE(aUserIndex) == 0)
	{
		return;
	}

	if( !gObjIsConnectedEx(aUserIndex) )
	{
		return;
	}

	LPOBJ lpUser = &gObj[aUserIndex];

	lpUser->StatusMap = lpUser->MapNumber;
	lpUser->StatusX = lpUser->X;
	lpUser->StatusY = lpUser->Y;
	lpUser->StatusCode = 1;
	this->GDStatusUpdate(aUserIndex, eStatusKill);
}
// ----------------------------------------------------------------------------------------------

#endif