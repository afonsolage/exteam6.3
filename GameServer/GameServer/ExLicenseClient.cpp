#include "stdafx.h"
#include "ExLicenseClient.h"
#include "ExLicense.h"
#include "ExLicenseProtocol.h"

#if(EXLICENSE_SERVER)

CExLicenseClient g_ExLicenseClient;

CExLicenseClient::CExLicenseClient()
{
	this->m_socket = INVALID_SOCKET;
	this->m_event = WSA_INVALID_EVENT;
	this->m_WorkerThread = 0;
	this->m_StatusThread = 0;
	this->m_active = 0;
	this->m_RecvSize = 0;
	this->m_SendSize = 0;
	memset(&this->m_RecvBuff, 0, sizeof(this->m_RecvBuff));
	memset(&this->m_SendBuff, 0, sizeof(this->m_SendBuff));
}

CExLicenseClient::~CExLicenseClient()
{
	this->Disconnect();
}

void CExLicenseClient::Load()
{
	InitializeCriticalSection(&this->m_critical);

	if(g_ExLicenseClient.Connect(LICENSE_IP,LICENSE_PORT) == 0)
	{
		MessageBox(NULL, "Connect Error", "License", NULL);
		ExitProcess(0);
		return;
	}

	this->m_StatusThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)this->ClientStatusThread, (LPVOID)NULL, 0, 0);

	//g_ExLicenseProtocol.GLReqUser();
}

bool CExLicenseClient::Connect(char* IpAddress, unsigned short port)
{
	WSADATA wsa;

	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		return false;
	}

	this->m_socket = socket(AF_INET,SOCK_STREAM,0);

	if(this->m_socket == INVALID_SOCKET)
	{
		return false;
	}

	this->m_event = WSACreateEvent();

	if(this->m_event == WSA_INVALID_EVENT)
	{
		return false;
	}

	SOCKADDR_IN target;

	target.sin_family = AF_INET;
	target.sin_port = htons(port);
	target.sin_addr.s_addr = inet_addr(IpAddress);
	
	if(target.sin_addr.s_addr == INADDR_NONE)
	{
		HOSTENT* host = gethostbyname(IpAddress);

		if(host != 0)
		{
			memcpy(&target.sin_addr.s_addr,(*host->h_addr_list),host->h_length);
		}
	}

	if(connect(this->m_socket,(SOCKADDR*)&target,sizeof(target)) == SOCKET_ERROR)
	{
		if(WSAGetLastError() != WSAEWOULDBLOCK)
		{
			//gLog.Output(LOG_DEBUG,GetEncryptedString(2),WSAGetLastError());
			this->Disconnect();
			return false;
		}
	}

	if(WSAEventSelect(this->m_socket,this->m_event,FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
	{
		//gLog.Output(LOG_DEBUG,GetEncryptedString(3),WSAGetLastError());
		this->Disconnect();
		return false;
	}

	memset(this->m_RecvBuff,0,sizeof(this->m_RecvBuff));
	this->m_RecvSize = 0;
	memset(this->m_SendBuff,0,sizeof(this->m_SendBuff));
	this->m_SendSize = 0;

	this->m_WorkerThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)this->ClientWorkerThread,(LPVOID)NULL,0,0);

	this->m_active = 1;

	g_ExLicenseProtocol.GLReqUser();

	return true;
}

void CExLicenseClient::Disconnect()
{
	if(this->m_socket != INVALID_SOCKET)
	{
		closesocket(this->m_socket);
		this->m_socket = INVALID_SOCKET;
	}

	if(this->m_event != WSA_INVALID_EVENT)
	{
		WSACloseEvent(this->m_event);
		this->m_event = WSA_INVALID_EVENT;
	}

	this->m_active = 0;

	if(this->m_WorkerThread != 0)
	{
		TerminateThread(this->m_WorkerThread,0);
		CloseHandle(this->m_WorkerThread);
		this->m_WorkerThread = 0;
	}
}

bool CExLicenseClient::CheckState()
{
	if(this->m_socket == INVALID_SOCKET)
	{
		return false;
	}

	if(this->m_active == 0)
	{
		return false;
	}

	return true;
}

bool CExLicenseClient::DataRecv()
{
	int count = 0;
	int size = 0;
	int result = recv(this->m_socket,(char*)&this->m_RecvBuff[this->m_RecvSize],(MAX_BUFF_SIZE-this->m_RecvSize),0);

	if(result == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAEWOULDBLOCK)
		{
			return 1;
		}
		else
		{
			//gLog.Output(LOG_DEBUG,GetEncryptedString(4),WSAGetLastError());
			this->Disconnect();
			return 0;
		}
	}

	this->m_RecvSize += result;

	if(this->m_RecvSize < 3)
	{
		return 1;
	}

	BYTE header;
	BYTE head;

	while(true)
	{
		if(this->m_RecvBuff[count] == 0xC1)
		{
			header = this->m_RecvBuff[count];
			size = this->m_RecvBuff[count+1];
			head = this->m_RecvBuff[count+2];
		}
		else if(this->m_RecvBuff[count] == 0xC2)
		{
			header = this->m_RecvBuff[count];
			size = MAKEWORD(this->m_RecvBuff[count+2],this->m_RecvBuff[count+1]);
			head = this->m_RecvBuff[count+3];
		}
		else
		{
			//gLog.Output(LOG_DEBUG,GetEncryptedString(5),this->m_RecvBuff[count]);
			this->Disconnect();
			return 0;
		}

		if(size < 3 || size > MAX_BUFF_SIZE)
		{
			//gLog.Output(LOG_DEBUG,GetEncryptedString(6),header,size,head);
			this->Disconnect();
			return 0;
		}

		if(size <= this->m_RecvSize)
		{
			if(header == 0xC1)
			{
				//PacketDecryptData(&this->m_RecvBuff[count+3],(size-3),this->m_RecvBuff[count+2]);
				head = this->m_RecvBuff[count+2];
			}
			else
			{
				//PacketDecryptData(&this->m_RecvBuff[count+4],(size-4),this->m_RecvBuff[count+3]);
				head = this->m_RecvBuff[count+3];
			}

			g_ExLicenseProtocol.ProtocolCore(head,&this->m_RecvBuff[count],size);

			count += size;
			this->m_RecvSize -= size;

			if(this->m_RecvSize <= 0)
			{
				break;
			}
		}
		else
		{
			if(count > 0 && this->m_RecvSize > 0 && this->m_RecvSize <= (MAX_BUFF_SIZE-count))
			{
				memcpy(this->m_RecvBuff,&this->m_RecvBuff[count],this->m_RecvSize);
			}
			break;
		}
	}

	return true;
}

bool CExLicenseClient::DataSend(BYTE* lpMsg,int size)
{
	EnterCriticalSection(&this->m_critical);

	if(this->CheckState() == 0)
	{
		LeaveCriticalSection(&this->m_critical);
		return false;
	}

	BYTE buff[MAX_BUFF_SIZE];

	memcpy(buff,lpMsg,size);

	if(buff[0] == 0xC1)
	{
		//PacketEncryptData(&buff[3],(size-3),buff[2]);
	}
	else
	{
		//PacketEncryptData(&buff[4],(size-4),buff[3]);
	}

#if(!EXLIC_DEBUG)
	if(this->m_SendSize > 0)
	{
		if((this->m_SendSize+size) > MAX_BUFF_SIZE)
		{
			//gLog.Output(LOG_DEBUG,GetEncryptedString(7),(this->m_SendSize+size));

			this->Disconnect();

			LeaveCriticalSection(&this->m_critical);
			return false;
		}
		else
		{
			memcpy(&this->m_SendBuff[this->m_SendSize],buff,size);
			this->m_SendSize += size;
			LeaveCriticalSection(&this->m_critical);
			return true;
		}
	}
#endif

	int count = 0;
	int result = 0;

	while(size > 0)
	{
		result = send(this->m_socket,(char*)&buff[count],size,0);

		if(result == SOCKET_ERROR)
		{
			if(WSAGetLastError() == WSAEWOULDBLOCK)
			{
#if(!EXLIC_DEBUG)
				if((this->m_SendSize+size) > MAX_BUFF_SIZE)
				{
					//gLog.Output(LOG_DEBUG,GetEncryptedString(8),(this->m_SendSize+size));

					this->Disconnect();

					LeaveCriticalSection(&this->m_critical);
					return false;
				}
				else
				{
					memcpy(&this->m_SendBuff[this->m_SendSize],&buff[count],size);
					this->m_SendSize += size;
					LeaveCriticalSection(&this->m_critical);
					return true;
				}
#endif
			}
			else
			{
				//gLog.Output(LOG_DEBUG,GetEncryptedString(9),WSAGetLastError());
				this->Disconnect();
				LeaveCriticalSection(&this->m_critical);
				return false;
			}
		}
		else
		{
			count += result;
			size -= result;
		}
	}

	LeaveCriticalSection(&this->m_critical);

	return true;
}

bool CExLicenseClient::DataSendEx()
{
	EnterCriticalSection(&this->m_critical);

	int count = 0;
	int result = 0;

	while(this->m_SendSize > 0)
	{
		if((result=send(this->m_socket,(char*)&this->m_SendBuff[count],this->m_SendSize,0)) == SOCKET_ERROR)
		{
			if(WSAGetLastError() == WSAEWOULDBLOCK)
			{
				memmove(this->m_SendBuff,&this->m_SendBuff[count],this->m_SendSize);
				LeaveCriticalSection(&this->m_critical);
				return true;
			}
			else
			{
				//gLog.Output(LOG_DEBUG,GetEncryptedString(10),WSAGetLastError());
				this->Disconnect();
				LeaveCriticalSection(&this->m_critical);
				return false;
			}
		}
		else
		{
			count += result;
			this->m_SendSize -= result;
		}
	}

	LeaveCriticalSection(&this->m_critical);

	return true;
}

DWORD WINAPI CExLicenseClient::ClientWorkerThread()
{
	while(true)
	{
		DWORD result = WSAWaitForMultipleEvents(1,&g_ExLicenseClient.m_event,0,WSA_INFINITE,0);

		if(result != WSA_WAIT_FAILED && result != WSA_WAIT_TIMEOUT)
		{
			WSANETWORKEVENTS NetworkEvents;

			if(WSAEnumNetworkEvents(g_ExLicenseClient.m_socket,g_ExLicenseClient.m_event,&NetworkEvents) == SOCKET_ERROR)
			{
				//gLog.Output(LOG_DEBUG,GetEncryptedString(11),WSAGetLastError());
				g_ExLicenseClient.Disconnect();
				return false;
			}

			if((NetworkEvents.lNetworkEvents & FD_READ) == FD_READ)
			{
				if(NetworkEvents.iErrorCode[FD_READ_BIT] == 0)
				{
					g_ExLicenseClient.DataRecv();
				}
				else
				{
					//gLog.Output(LOG_DEBUG,GetEncryptedString(12),NetworkEvents.iErrorCode[FD_READ_BIT]);
					g_ExLicenseClient.Disconnect();
					return false;
				}
			}

			if((NetworkEvents.lNetworkEvents & FD_WRITE) == FD_WRITE)
			{
				if(NetworkEvents.iErrorCode[FD_WRITE_BIT] == 0)
				{
					g_ExLicenseClient.DataSendEx();
				}
				else
				{
					//gLog.Output(LOG_DEBUG,GetEncryptedString(13),NetworkEvents.iErrorCode[FD_WRITE_BIT]);
					g_ExLicenseClient.Disconnect();
					return false;
				}
			}

			if((NetworkEvents.lNetworkEvents & FD_CLOSE) == FD_CLOSE)
			{
				if(NetworkEvents.iErrorCode[FD_CLOSE_BIT] == 0)
				{
					g_ExLicenseClient.Disconnect();
				}
				else
				{
					//gLog.Output(LOG_DEBUG,GetEncryptedString(14),NetworkEvents.iErrorCode[FD_CLOSE_BIT]);
					g_ExLicenseClient.Disconnect();
					return false;
				}
			}
		}
	}

	return true;
}

DWORD WINAPI CExLicenseClient::ClientStatusThread()
{
	while(true)
	{
		if(g_ExLicenseClient.CheckState() == 0)
		{
			if(g_ExLicenseClient.Connect(LICENSE_IP, LICENSE_PORT) == 0)	//config
			{
				continue;
			}
		}

		Sleep(10000);
	}

	return true;
}

#endif