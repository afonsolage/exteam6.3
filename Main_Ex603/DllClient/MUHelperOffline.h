#pragma once

#include "Protocol.h"
#include "../../Common/LCProtocol.h"
#include "Import.h"
#include "Object.h"

#define MUHELPER_2SEC_TIMER		0x1101
#define MUHELPER_100MS_TIMER	0x1102

#define MAX_OBJECTS_COUNT	400

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
	void Reset();
	void Tick();

	void Start();
	void Stop();

	void GCMoveProc(PMSG_RECVMOVE* lpMsg);
	void GCMsgClose(PMSG_RESULT* lpMsg);

	CMUHelperOffline(void);
	~CMUHelperOffline(void);

private:
	bool m_active;

	ObjectPreview* GetMainObject();
	ObjectPreview* FindMainObject();
	ObjectPreview* FindDummyObject();

	ObjectPreview* m_Dummy;

	BYTE m_TargetCamX;
	BYTE m_TargetCamY;

	DWORD m_lastTick;
	float m_deltaTime;

	void UpdateCamPosition();

};

extern CMUHelperOffline g_MUHelperOffline;