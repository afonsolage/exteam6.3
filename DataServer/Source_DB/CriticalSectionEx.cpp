#include "stdafx.h"
#include "CriticalSectionEx.h"
#include "Define.h"

//#if(ENABLE_PROTOCOL_QUEUE)

CCriticalSectionEx::CCriticalSectionEx()
{
	InitializeCriticalSection(&this->m_critical);
}

CCriticalSectionEx::~CCriticalSectionEx()
{
	DeleteCriticalSection(&this->m_critical);
}

void CCriticalSectionEx::lock()
{
	EnterCriticalSection(&this->m_critical);
}

void CCriticalSectionEx::unlock()
{
	LeaveCriticalSection(&this->m_critical);
}

//#endif