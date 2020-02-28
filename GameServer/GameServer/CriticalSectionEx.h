#pragma once

#include "StdAfx.h"

class CCriticalSectionEx
{
public:
	CCriticalSectionEx();
	virtual ~CCriticalSectionEx();
	void lock();
	void unlock();

private:
	CRITICAL_SECTION m_critical;
};