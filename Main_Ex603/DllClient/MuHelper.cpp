#include "stdafx.h"
#include "MuHelper.h"
#include "User.h"
#include "TMemory.h";

#ifdef ENABLE_CONSOLE
#include "Console.h"
#endif

CMuHelper gMuHelper;

void MuTickHook()
{
	pMUHelperTick();
}

CMuHelper::CMuHelper(void)
{
	m_Time = 0;
	m_Money = 0;
	m_Mode = 1;	//Closed

	//SetOp((LPVOID)0x004D92E2, MuTickHook, ASM::CALL);
}


CMuHelper::~CMuHelper(void)
{

}



void CMuHelper::GCData(LPBYTE Data)
{
	MUHELPER_ANS_DATA * Recv = (MUHELPER_ANS_DATA*)Data;
	this->m_Mode = Recv->Mode;
	this->m_Money = Recv->Money;
	this->m_Time = Recv->Time;

#ifdef ENABLE_CONSOLE
	this->PrintInfo();
#endif
}

void CMuHelper::Start()
{
	MUHELPER_REQ_ACTION pReq = { 0 };
	pReq.h.set((LPBYTE)&pReq, 0xBF, 0x51, sizeof(pReq));
	pReq.Mode = 0;
	gProtocol.DataSend((LPBYTE)&pReq, pReq.h.size);

#ifdef ENABLE_CONSOLE
	gConsole.Output(cYELLOW, "[MuHelper] Started!");
#endif
}

void CMuHelper::Stop()
{
	MUHELPER_REQ_ACTION pReq = { 0 };
	pReq.h.set((LPBYTE)&pReq, 0xBF, 0x51, sizeof(pReq));
	pReq.Mode = 1;
	gProtocol.DataSend((LPBYTE)&pReq, pReq.h.size);

#ifdef ENABLE_CONSOLE
	gConsole.Output(cYELLOW, "[MuHelper] Stopped!");
#endif
}

void CMuHelper::RestoreState()
{
	/*lpMUHelper MUHelper = &*(lpMUHelper)pMUHelperClass;
	gConsole.Output(cYELLOW, "[MuHelper] Hunting Range: %d", MUHelper->HuntingRange);

	*/if (IsActive())
		Start();
	else
		Stop();
}

#ifdef ENABLE_CONSOLE
void CMuHelper::PrintInfo()
{
	gConsole.Output(cYELLOW, "[MuHelper] Active: %s, Money: %d, Time: %d", this->m_Mode == 0 ? "TRUE" : "FALSE", this->m_Money, this->m_Time);
}
#endif