#include "stdafx.h"
#include "MUHelperOffline.h"
#include "User.h"
#include "Console.h"
#include "ExLicense.h"
#include "Interface.h"

CMUHelperOffline g_MUHelperOffline;

CMUHelperOffline::CMUHelperOffline(void)
{
	this->m_active = false;
}


CMUHelperOffline::~CMUHelperOffline(void)
{
}

ObjectPreview* CMUHelperOffline::GetMainObject()
{
	return (ObjectPreview*)oUserPreviewStruct;
}

ObjectPreview* CMUHelperOffline::FindMainObject()
{
	auto mainIndex = pGameIndex;

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		lpViewObj lpViewTarget = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), i);

		if (!lpViewTarget || lpViewTarget->m_Model.Visible == FALSE) continue;
		if (lpViewTarget->m_Model.ObjectType != emPlayer) continue;

		if (lpViewTarget->aIndex == mainIndex)
		{
			return lpViewTarget;
		}
	}

	return nullptr;
}

ObjectPreview* CMUHelperOffline::FindDummyObject()
{
	auto mainIndex = pGameIndex;

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		lpViewObj lpViewTarget = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), i);

		if (!lpViewTarget || lpViewTarget->m_Model.Visible == FALSE) continue;
		if (lpViewTarget->m_Model.ObjectType != emPlayer) continue;
		if (lpViewTarget == GetMainObject()) continue;

		if (lpViewTarget->aIndex == mainIndex)
		{
			return lpViewTarget;
		}
	}

	return nullptr;
}

void CMUHelperOffline::UpdateCamPosition()
{
	if (g_ExLicense.user.MUHelperOffline == false) return;

	if (m_active == false || m_TargetCamX == 0 || m_TargetCamY == 0) return;

	auto lpPreview = GetMainObject();

	auto currentX = lpPreview->m_Model.VecPosX;
	auto currentY = lpPreview->m_Model.VecPosY;

	if ((BYTE)(currentX / 100) == m_TargetCamX && (BYTE)(currentY / 100) == m_TargetCamY)
	{
		m_TargetCamX = 0;
		m_TargetCamY = 0;
		return;
	}

	auto targetX = (float)m_TargetCamX;
	auto targetY = (float)m_TargetCamY;

	auto distX = targetX - (currentX / 100);
	auto distY = targetY - (currentY / 100);

	if (isinf(distX))
		distX = 0;

	if (isinf(distY))
		distY = 0;

	if ((abs(distX < 0.01) && abs(distY) < 0.01))
	{
		m_TargetCamX = 0;
		m_TargetCamY = 0;
		return;
	}
	else if (abs(distX) > 15 || abs(distY) > 15)
	{
		lpPreview->m_Model.VecPosX = targetX * 100;
		lpPreview->m_Model.VecPosY = targetY * 100;
	}
	else
	{
		lpPreview->m_Model.VecPosX += distX * m_deltaTime * 50;
		lpPreview->m_Model.VecPosY += distY * m_deltaTime * 50;
	}
}

void CMUHelperOffline::GCAction(MUHELPEROFF_ACTION* lpMsg)
{
	if (g_ExLicense.user.MUHelperOffline == false) return;

	this->m_active = lpMsg->Action >= 1;

	if (this->m_active)
	{
		gObjUser.HideModel();
	}
	else
	{
		gObjUser.ShowModel();
	}

	Reset();
}

void CMUHelperOffline::RestoreState()
{
	if (g_ExLicense.user.MUHelperOffline == false) return;

	if (this->m_active)
	{
		SetTimer(pGameWindow, MUHELPER_2SEC_TIMER, 2000, NULL);
	}
}

void CMUHelperOffline::Timer()
{
	if (g_ExLicense.user.MUHelperOffline == false) return;

	if (this->m_active)
	{
		Start();
	}

	KillTimer(pGameWindow, MUHELPER_2SEC_TIMER);

	Reset();
}

void CMUHelperOffline::Reset()
{
	m_TargetCamX = 0;
	m_TargetCamY = 0;
	m_Dummy = NULL;
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

void CMUHelperOffline::GCMoveProc(PMSG_RECVMOVE * lpMsg)
{
	if (g_ExLicense.user.MUHelperOffline == false) return;

	if (!this->m_active || m_Dummy == NULL)
	{
		return;
	}

	int aIndex = MAKE_NUMBERW(lpMsg->NumberH, lpMsg->NumberL);

	if (aIndex != m_Dummy->aIndex) return;

	auto x = m_Dummy->RespawnPosX;
	auto y = m_Dummy->RespawnPosY;

	m_Dummy->RespawnPosX = lpMsg->X;
	m_Dummy->RespawnPosY = lpMsg->Y;

	m_Dummy->MapPosX = x;
	m_Dummy->MapPosY = y;
}

void CMUHelperOffline::GCMsgClose(PMSG_RESULT* lpMsg)
{
	m_active = false;
	Reset();
}

void CMUHelperOffline::Tick()
{
	if (g_ExLicense.user.MUHelperOffline == false) return;

	auto currentTick = GetTickCount();
	m_deltaTime = (currentTick - m_lastTick) / 1000.0f;
	m_lastTick = currentTick;

	UpdateCamPosition();

	auto lpPreview = GetMainObject();
	auto lpPlayer = pUserObjectStruct;
	auto dummy = FindDummyObject();
	
	if (this->m_active)
	{
		if (lpPreview->InSafeZone == true)
		{
			Stop();
			return;
		}

		if (m_Dummy == NULL)
		{
			m_Dummy = FindDummyObject();
		}

		if (m_Dummy != NULL && lpPreview->m_Model.Visible == FALSE)
		{
			auto camPosX = (BYTE)(lpPreview->m_Model.VecPosX / 100);
			auto camPosY = (BYTE)(lpPreview->m_Model.VecPosY / 100);

			if (camPosX != m_Dummy->MapPosX || camPosY != m_Dummy->MapPosY)
			{
				m_TargetCamX = m_Dummy->MapPosX;
				m_TargetCamY = m_Dummy->MapPosY;
			}
		}
	}
	else if (!this->m_active && lpPreview->m_Model.Visible == false)
	{
		gObjUser.ShowModel();
		if (m_Dummy != NULL)
		{
			m_Dummy->m_Model.Visible = FALSE;
		}
	}

	if (lpPreview->aIndex != pGameIndex)
	{
		auto lpNewPreview = FindMainObject();

		if (lpNewPreview == nullptr) return;

		*lpUserPreviewStruct = lpNewPreview;
	}
}