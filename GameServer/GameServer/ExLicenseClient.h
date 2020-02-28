#pragma once

#include "stdafx.h"
#include "ExLicense.h"

#if(EXLICENSE_SERVER)

#define LICENSE_IP				"127.0.0.1"
#define LICENSE_PORT			50325

#define MAX_BUFF_SIZE			20000
#define EXLIC_DEBUG				1

class CExLicenseClient
{
public:
		 CExLicenseClient();
		 ~CExLicenseClient();
	void Load();
	bool Connect(char* IpAddress, unsigned short port);
	void Disconnect();
	bool CheckState();
	bool DataRecv();
	bool DataSend(BYTE* lpMsg, int size);
	bool DataSendEx();
	static DWORD WINAPI ClientWorkerThread();
	static DWORD WINAPI ClientStatusThread();

private:
	CRITICAL_SECTION m_critical;
	SOCKET m_socket;
	WSAEVENT m_event;
	BYTE m_RecvBuff[MAX_BUFF_SIZE];
	int m_RecvSize;
	BYTE m_SendBuff[MAX_BUFF_SIZE];
	int m_SendSize;
	HANDLE m_WorkerThread;
	HANDLE m_StatusThread;
	bool m_active;
};

extern CExLicenseClient g_ExLicenseClient;

#endif
