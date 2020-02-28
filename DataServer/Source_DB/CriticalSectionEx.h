#pragma once

#include "Define.h"

//#if(ENABLE_PROTOCOL_QUEUE)

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

//#endif