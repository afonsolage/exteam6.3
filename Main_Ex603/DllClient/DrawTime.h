#pragma once

#include "stdafx.h"
#include "Protocol.h"

void TimeImageLoad();
void TimeLoad();
void DrawTime();

#if(CUSTOM_SERVER_TIME)
struct PMSG_SERVER_TIME
{
	PBMSG_HEAD2 h;
    WORD Hour;
    WORD Minute;
    WORD Second;
};

struct ServerTime
{
    WORD m_Hour;
    WORD m_Minute;
    WORD m_Second;
};
extern ServerTime g_ServerTime;

void GCServerTime(PMSG_SERVER_TIME* lpMsg);
#endif
