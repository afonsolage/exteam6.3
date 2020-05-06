#include "stdafx.h"
#include "DungeonConqueror.h"
#include "GameMain.h"
#include "logproc.h"

CDungeonConqueror g_DungeonConqueror;

void CDungeonConqueror::Clear()
{
	this->m_State = eDC_STATE_CLOSED;
}

void CDungeonConqueror::Load()
{
	this->Clear();

	auto path = gDirPath.GetNewPath("Custom\\Events\\DungeonConqueror.ini");

	this->m_Enabled = GetPrivateProfileInt("DungeonConqueror", "Enable", 0, path);
	this->m_RegWeekDay = GetPrivateProfileInt("DungeonConqueror", "RegWeekDay", 7, path);
	this->m_RegHour = GetPrivateProfileInt("DungeonConqueror", "RegHour", 21, path);
	this->m_RegMin = GetPrivateProfileInt("DungeonConqueror", "RegMin", 30, path);
	this->m_StartWeekDay = GetPrivateProfileInt("DungeonConqueror", "StartWeekDay", 6, path);
	this->m_StartHour = GetPrivateProfileInt("DungeonConqueror", "StartHour", 21, path);
	this->m_StartMin = GetPrivateProfileInt("DungeonConqueror", "StartMin", 30, path);
	this->m_WaitDuration = GetPrivateProfileInt("DungeonConqueror", "WaitDuration", 5, path);
	this->m_EventDuration = GetPrivateProfileInt("DungeonConqueror", "EventDuration", 25, path);

	LOG_INFO("Loaded!");
}

void CDungeonConqueror::Tick()
{
	if (!this->m_Enabled) return;

	switch (this->m_State)
	{
	case eDC_STATE_CLOSED:
		ProcessClosedState();
		break;
	case eDC_STATE_REG:
		ProcessRegState();
		break;
	case eDC_STATE_WAIT:
		ProcessWaitState();
		break;
	case eDC_STATE_START:
		ProcessStartState();
		break;
	default:
		LOG_ERROR("Unkown state %d", this->m_State);
		Clear();
		break;
	}
}

void CDungeonConqueror::ProcessClosedState()
{
}

void CDungeonConqueror::ProcessRegState()
{
}

void CDungeonConqueror::ProcessWaitState()
{
}

void CDungeonConqueror::ProcessStartState()
{
}
