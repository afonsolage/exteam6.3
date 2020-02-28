#pragma once
// ----------------------------------------------------------------------------------------------


/*
00663C31 - функция с коннект пакетом
*/

#include "Protocol.h"

#ifdef exRECONNECT

//#define DEBUG_RECONNECT 1



//#define NORM_DC		0
//#define OFFZEN_DC	1
//#define OFFWCOIN_DC	2
//#define OFFPC_DC	3
//#define OFFCR_DC	4
//#define OFFAFK_DC	5
#define NORM_DC		0
#define OFFZEN_DC	1
#define OFFCR_DC	2
#define OFFWC_DC	3
#define OFFWP_DC	4
#define OFFWG_DC	5
#define OFFAFK_DC	20

// ----------------------------------------------------------------------------------------------

#pragma pack(push, 1)
struct CONNECTEX_LOGIN
{
	PBMSG_HEAD2	h;
	char		AccountID[10];
	char		Password[10];
	char		Name[10];
	DWORD		TickCount;
};
#pragma pack(pop)
// ----------------------------------------------------------------------------------------------

#pragma pack(push, 1)
struct PMSG_ANS_SERVER_INFO
{
	PBMSG_HEAD2 h;
	char		Ip[16];
	WORD		Port;
};
#pragma pack(pop)
// ----------------------------------------------------------------------------------------------

#pragma pack(push, 1)
struct CONNECTEX_CLOSE
{
	PBMSG_HEAD2	h;
};
#pragma pack(pop)

namespace ConnectExType
{
	enum T
	{
		OnLine				= 0,
		OnReconnect			= 1,
		OnForceDisconnect	= 2,
	};
};
// ----------------------------------------------------------------------------------------------

class ConnectEx
{
public:
	void	Load();
	void	Run();
	// ----
	void	ClearGame();
	void	RestoreGame();
	// ----
	void	DrawProgres();
	void	LoginReq();
	void	Reconnect();
	void	Relogin();
	void	Disconnect();
	// ----
	int		m_ConnectState;
	char	m_AccountID[11];
	char	m_Password[21];
	// ----
	char	m_CSIP[16];
	WORD	m_CSPort;
	char	m_GSIP[16];
	WORD	m_GSPort;
private:
	// ----
	DWORD	m_LastSendTick;
	DWORD	m_ReconnectTick;
	bool	m_WantMUHelper;
	// ----
}; extern ConnectEx gConnectEx;
// ----------------------------------------------------------------------------------------------

#endif