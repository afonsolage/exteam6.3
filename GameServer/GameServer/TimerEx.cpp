#include "StdAfx.h"
#include "TimerEx.h"

CTimerEx g_TimerEx;

CTimerEx::CTimerEx()
{
	this->Init();
}

CTimerEx::~CTimerEx()
{
}

void CTimerEx::Init()
{
	this->m_TickSecond = 0;
}

void CTimerEx::Run()
{
	this->m_TickSecond++;

	if(this->m_TickSecond >= 60)
	{
		this->m_TickSecond = 0;
	}
}

int CTimerEx::GetSecond()
{
	return this->m_TickSecond;
}