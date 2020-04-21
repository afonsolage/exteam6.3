#pragma once

#include "Protocol.h"
#include "../../Common/LCProtocol.h"

#define MUHELPER_2SEC_TIMER		0x1101
#define MUHELPER_100MS_TIMER	0x1102

struct MUHELPEROFF_ACTION
{
	PBMSG_HEAD2 h;
	BYTE Action;
};

class CMUHelperOffline
{
public:

	void GCAction(MUHELPEROFF_ACTION* lpMsg);
	
	void RestoreState();
	void Timer();
	void Tick();

	void Start();
	void Stop();

	CMUHelperOffline(void);
	~CMUHelperOffline(void);

private:

	bool m_active;
};

extern CMUHelperOffline g_MUHelperOffline;