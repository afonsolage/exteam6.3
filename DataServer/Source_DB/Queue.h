#pragma once

#include "Define.h"

//#if(ENABLE_PROTOCOL_QUEUE)

#include "CriticalSectionEx.h"
#include <queue>

#define MAX_QUEUE_SIZE 2048

struct QUEUE_INFO
{
	WORD index;
	BYTE head;
	BYTE buff[8192];
	DWORD size;
};

class CQueue
{
public:
	CQueue();
	virtual ~CQueue();
	void ClearQueue();
	DWORD GetQueueSize();
	bool AddToQueue(QUEUE_INFO* lpInfo);
	bool GetFromQueue(QUEUE_INFO* lpInfo);
private:
	CCriticalSectionEx m_critical;
	std::queue<QUEUE_INFO> m_QueueInfo;
};

//#endif