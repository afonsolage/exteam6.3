// SerialCheck.h: interface for the CSerialCheck class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#if(DEV_SOCKET_MANAGER)

#include "User.h"

class CSerialCheck
{
public:
	CSerialCheck();
	virtual ~CSerialCheck();
	void Init();
	bool CheckSerial(BYTE serial);
	BYTE GetRecvSerial();
	BYTE GetSendSerial();
private:
	BYTE m_RecvSerial;
	BYTE m_SendSerial;
};

extern CSerialCheck gSerialCheck[OBJMAX];

#endif