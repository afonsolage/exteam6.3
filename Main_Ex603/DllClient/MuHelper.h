#pragma once

#include "Protocol.h"


//0xBF, 0x51
struct MUHELPER_ANS_DATA	//-> Complete (from 6.3 GMO)
{
	PBMSG_HEAD2 h;			//-> 0	(4)
	WORD	Time;			//-> 4	(2)
	DWORD	Money;			//-> 8	(4)
	BYTE	Mode;			//-> 12 (1)
};

//0xBF, 0x51
struct MUHELPER_REQ_ACTION	//-> Complete
{
	PBMSG_HEAD2 h;			//-> 0	(4)
	BYTE	Mode;			//-> 4	(1)
};

class CMuHelper
{
public:
	CMuHelper(void);
	virtual ~CMuHelper(void);

	void GCData(LPBYTE Data);

	bool	IsActive() {return m_Mode == 0;}
	WORD	GetTime() {return m_Time;}
	DWORD	GetMoney() {return m_Money;}

	void Start();
	void Stop();

	void RestoreState();

#ifdef ENABLE_CONSOLE
	void PrintInfo();
#endif

private:
	WORD	m_Time;
	DWORD	m_Money;
	BYTE	m_Mode;
};

extern CMuHelper gMuHelper;
