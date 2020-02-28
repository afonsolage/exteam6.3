#include "stdafx.h"
#include "wsJoinServerCli.h"
#include "logproc.h"

wsJoinServerCli::wsJoinServerCli()
{
	return;
}

wsJoinServerCli::~wsJoinServerCli()
{
	return;
}


BOOL wsJoinServerCli::SetProtocolCore(void (*pc)(BYTE, BYTE*, int))
{
	this->wsProtocolCore = pc;
	return TRUE;
}
	
#if(SWENG_FIX==FALSE)	//FALSE
BOOL wsJoinServerCli::Connect(char* ip_addr, unsigned short port, DWORD WinMsgNum)
{
	hostent* host;
	sockaddr_in addr;
	int nResult;

	host = 0;

	if ( this->m_hWnd  == 0 )
	{
		LogAdd(" Connect Error %s %d", __FILE__, __LINE__);
		return FALSE;
	}
	addr.sin_family = AF_INET;
	addr.sin_port =  htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(ip_addr);

	if ( addr.sin_addr.S_un.S_addr == -1 )
	{
		host = gethostbyname(ip_addr);
		if ( host == 0 )
		{
			LogAdd("server name not found [%s]", ip_addr);
			return FALSE;
		}

		memcpy(&addr.sin_addr.S_un.S_addr, *host->h_addr_list  , host->h_length  );	
	}

	nResult=connect(this->m_socket, (sockaddr*)&addr, 16);

	if (nResult== -1)
	{
		if ( WSAGetLastError() != WSAEWOULDBLOCK)
		{
			this->Close(this->m_socket );
			return FALSE;
		}
	}

	nResult=WSAAsyncSelect(this->m_socket, this->m_hWnd , WinMsgNum, FD_READ|FD_WRITE|FD_CLOSE);

	if ( nResult == -1 )
	{
		closesocket(this->m_socket );
		LogAdd("Client WSAAsyncSelect error %d", WSAGetLastError());
		return FALSE;
	}
	this->m_SendBufLen=0;
	this->SetConnect(TRUE);

	return TRUE;
}
#else
int wsJoinServerCli::Connect(char *ip_addr, WORD port, DWORD WinMsgNum) // FIX SOME CRASH
{
    int result; // eax@2
    sockaddr_in addr; // [sp+8h] [bp-1Ch]@3
    int nResult; // [sp+18h] [bp-Ch]@7
    hostent *host = NULL; // [sp+1Ch] [bp-8h]@1
    int snd_buf = 81920;	//81920
 
    if ( !this->m_hWnd )
    {
        LogAdd(" Connect Error %s %d", __FILE__, __LINE__);
        return 0;
    }
 
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.S_un.S_addr = inet_addr(ip_addr);
 
    if ( addr.sin_addr.S_un.S_addr == -1 )
    {
        host = gethostbyname(ip_addr);
 
        if ( !host )
        {
            LogAdd("server name not found [%s]", ip_addr);
            return 0;
        }
 
        memcpy((char *)&addr.sin_addr, *host->h_addr_list, host->h_length);
    }
 
    setsockopt(this->m_socket, 0xFFFF, 4097, (const char *)&snd_buf, 4);
 
    nResult = connect(this->m_socket, (const struct sockaddr *)&addr, 16);
 
    if ( nResult != -1 || WSAGetLastError() == 10035 )
    {
        nResult = WSAAsyncSelect(this->m_socket, this->m_hWnd, WinMsgNum, 35);
 
        if ( nResult == -1 )
        {
            closesocket(this->m_socket);
            LogAdd("Client WSAAsyncSelect error %d", WSAGetLastError());
            result = 0;
        }
        else
        {
            this->m_SendBufLen = 0;
            this->SetConnect(TRUE);
            result = 1;
        }
    }
    else
    {
        this->Close(this->m_socket);
        result = 0;
    }
    return result;
}
#endif


#if(SWENG_FIX==FALSE)	//FALSE
BOOL wsJoinServerCli::DataSend(char *buf, int len)
{
	int nResult;
	int nLeft;
	int nDx;	// Degeneration X :)
	LPBYTE sendbuf;
	int* sendbuflen;
	
	if ( len <= 0 )
	{
		return 0;
	}

	if ( this->m_socket  == INVALID_SOCKET )	// 
	{
		return 0;
	}

	nDx = 0;

	sendbuf = this->m_SendBuf;
	sendbuflen= &len;	// Strange, dangeorus

	if ( this->m_SendBufLen   > 0 )
	{
		if ( (this->m_SendBufLen +len) < MAX_WS_BUF_LEN )
		{
			memcpy( &this->m_SendBuf[this->m_SendBufLen]  , buf, len);	// Review this later

			this->m_SendBufLen +=len;
			return 1;
		}
		this->Close();
		return FALSE;
	}

	nLeft= *sendbuflen;

	while ( true )
	{
		nResult=send(this->m_socket, (char*)&buf[nDx], (*sendbuflen - nDx), 0);

		if ( nResult == -1)
		{
			if ( WSAGetLastError() != WSAEWOULDBLOCK )
			{
				LogAdd("error-L3 : %d (%s %d)", WSAGetLastError(), __FILE__, __LINE__);
				*sendbuflen=0;
				this->Close(this->m_socket );
				return FALSE;
			}

			if ( (*sendbuflen + nLeft) > MAX_WS_BUF_LEN )
			{
				LogAddC(2,"error-L3 : buffer error closed %d, %d", (*sendbuflen+nLeft), MAX_WS_BUF_LEN);
				*sendbuflen = 0;
				this->Close(this->m_socket);
				return FALSE;
			}

			if ( nDx >= 0 )
			{
				memcpy( &this->m_SendBuf[this->m_SendBufLen],  &buf[nDx], nLeft);
				
				this->m_SendBufLen +=nLeft;

				LogAdd("error-L3 : Copy1 : nLeft:%d len:%d nDx:%d", nLeft, this->m_SendBufLen , nDx);
				return TRUE;
			}
		}
		else if ( nResult == 0 )
		{
			LogAdd("error-L3 : send()  result is zero", WSAGetLastError());
			break;
		}

		if ( nResult >0 )
		{
			nDx += nResult;
			nLeft -= nResult;
			*sendbuflen -= nResult;
		}
		if ( nLeft <= 0)
		{
			break;
		}
	}
	return TRUE;
}
#else
BOOL wsJoinServerCli::DataSend(PCHAR buf, int len)	//FIX_CRASH
{
    int nResult;
    int nLeft;
    int nDx;    // Degeneration X :)
    LPBYTE sendbuf;
    int* sendbuflen;
   
    if ( len <= 0 )
    {
        return 0;
    }
 
    if ( this->m_socket  == INVALID_SOCKET )    //
    {
        return 0;
    }
 
    nDx = 0;
 
    //sendbuf = this->m_SendBuf;
    //sendbuflen = &len;    // Strange, dangeorus
 
    if ( this->m_SendBufLen  > 0 )
    {
        if ( (this->m_SendBufLen +len) < MAX_WS_BUF_LEN )
        {
            memcpy(&this->m_SendBuf[this->m_SendBufLen], buf, len);
            this->m_SendBufLen += len;
            return TRUE;
        }
 
        LogAddTD("Error wsJoinServerClli DataSend m_SendBufLen+len > MAX_JOINSENDBUFSIZE");
        this->Close();
        return FALSE;
    }
 
    nLeft = len;
 
    while ( true )
    {
        nResult = send(this->m_socket, (char*)&buf[nDx], (len - nDx), 0);
 
        if ( nResult == -1)
        {
            if ( WSAGetLastError() != WSAEWOULDBLOCK )
            {
                LogAdd("error-L3 : %d (%s %d)", WSAGetLastError(), __FILE__, __LINE__);
                len = 0;
                this->Close(this->m_socket);
                return FALSE;
            }
 
            if( (len + nLeft) > MAX_WS_BUF_LEN )
            {
                LogAddC(2,"error-L3 : buffer error closed %d, %d", (*sendbuflen+nLeft), MAX_WS_BUF_LEN);
                len = 0;
                this->Close(this->m_socket);
                return FALSE;
            }
 
            /*if( !this->m_SendBufLen )
            {
                return false;
            }*/
 
            if ( nDx >= 0 )
            {
                /*memcpy( &this->m_SendBuf[this->m_SendBufLen],  &buf[nDx], nLeft);
                this->m_SendBufLen +=nLeft;
                LogAdd("error-L3 : Copy1 : nLeft:%d len:%d nDx:%d", nLeft, this->m_SendBufLen , nDx);*/
                return TRUE;
            }
        }
        else if ( nResult == 0 )
        {
            LogAdd("error-L3 : send()  result is zero", WSAGetLastError());
            break;
        }
 
        if ( nResult > 0 )
        {
            nDx += nResult;
            nLeft -= nResult;
            len -= nResult;
        }
 
        if ( nLeft <= 0)
        {
            break;
        }
    }
 
    return TRUE;
}
#endif




BOOL wsJoinServerCli::FDWRITE_MsgDataSend()
{
	int nResult;
	int nDx;	// Degeneration X :)
	LPBYTE sendbuf;
	int* sendbuflen;

	nDx=0;
	sendbuf=&this->m_SendBuf[0];
	sendbuflen=&this->m_SendBufLen ;

	if (this->m_SendBufLen < 1)
	{
		return TRUE;
	}

	while (*sendbuflen>0)
	{
		nResult=send(this->m_socket, (char*)&sendbuf[nDx], *sendbuflen-nDx, 0);
		if (nResult == -1)
		{
			if ( WSAGetLastError() != WSAEWOULDBLOCK)
			{
				LogAdd("FD_WRITE send() ¿¡·¯ %d %d", WSAGetLastError(), *sendbuflen);
				this->Close();
				return FALSE;
			}
			else
			{
				LogAdd("FD_WRITE send() WSAEWOULDBLOCK : %d", WSAGetLastError());
				break;
			}
		}
		if (nResult <= 0)
		{
			LogAdd("send() result is zero %d", WSAGetLastError());
			break;
		}
		LogAdd("error-L3 : nDx %d m_SendBufLen %d", nDx, this->m_SendBufLen );

		if (nResult > 0)
		{
			nDx += nResult;
			*sendbuflen -= nResult;
		}

		LogAdd("error-L3 : nDx %d m_SendBufLen %d", nDx, this->m_SendBufLen );
	}
	return TRUE;
}



int wsJoinServerCli::DataRecv()
{
	int nResult;
	LPBYTE recvbuf;
	int* recvbuflen;
	int lOfs;
	int size;
	BYTE headcode;

	recvbuf= (LPBYTE)&this->m_RecvBuf[0]   ;
	recvbuflen=&this->m_RecvBufLen ;
	nResult=recv(this->m_socket , (char*)&recvbuf[*recvbuflen], (MAX_WS_BUF_LEN-*recvbuflen), 0);

	if ( nResult == 0 )
	{
		LogAdd("error-L3 : closed %d - buff:%d(%d) ",
			WSAGetLastError(), this->m_RecvBufLen, MAX_WS_BUF_LEN - *recvbuflen);

		return 1;
	}
	else if (nResult == -1 )
	{
		if ( WSAGetLastError() == WSAEWOULDBLOCK )
		{
			return 1;
		}
		LogAdd("error-L3 : recv error %d", WSAGetLastError() );
		return 1;
	}

	*recvbuflen += nResult;

	if (*recvbuflen<3)
	{
		return 3;
	}

	lOfs=0;
	size=0;

	//LogAddC(2, "[DEBUG] Type: %x", recvbuf[lOfs]);

	while ( true )
	{
		
		if (recvbuf[lOfs] == 0xC1 )	// Type packet handling C1 Type
		{
			LPBYTE c1subbase = (LPBYTE)&recvbuf[lOfs];
			size=c1subbase[1];
			headcode=c1subbase[2];
		}
		else if ( recvbuf[lOfs] == 0xC2 ) // Type packet handling C2 Type
		{
			LPBYTE c2subbase=(LPBYTE)&recvbuf[lOfs];
			size = c2subbase[1] * 256;
			size |= c2subbase[2];
			headcode = c2subbase[3];

			//header = lpMsg[count];
			//size = MAKEWORD(recvbuf[lOfs+2],recvbuf[lOfs+1]);
			//headcode = recvbuf[lOfs+3];
		}
		else
		{
			LogAdd("error-L2 : header error (%s %d)lOfs:%d, head: 0x%02X size:%d", __FILE__, __LINE__, lOfs, recvbuf[lOfs], *recvbuflen);
			
			/*char DebugOut[6000] = { 0 };

			for( int i = 0; i < 200; i++ )
			{
				char ByteFormat[100] = { 0 };
				sprintf(ByteFormat, "%X ", recvbuf[i]);
				strcat(DebugOut, ByteFormat);
			}
			
			LogAddC(2, DebugOut);	*/		
			
			*recvbuflen = 0;
			return 0;
		}

		if ( size <= 0 )
		{
			LogAdd("error-L2 : size %d", size);
			return 0;
		}

		if ( size <= *recvbuflen )
		{
			this->wsProtocolCore(headcode, &recvbuf[lOfs], size);
			lOfs += size;
			*recvbuflen -= size;

			if ( *recvbuflen <= 0)
			{
				break;
			}
		}	
		else if ( lOfs > 0 )
		{
			if ( *recvbuflen < 1 ) 
			{
				break;
			}

			memcpy(recvbuf, &recvbuf[lOfs], *recvbuflen);
			break;
		}
		else
		{
			break;
		}
	}
	return 0;
}



