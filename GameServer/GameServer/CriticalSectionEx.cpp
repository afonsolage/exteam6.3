#include "stdafx.h"
#include "CriticalSectionEx.h"

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
