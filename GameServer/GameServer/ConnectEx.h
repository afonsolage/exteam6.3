#pragma once
#include "StdAfx.h"
// -------------------------------------------------------------------------------
#if(_RECONNECT_)
// -------------------------------------------------------------------------------

#include "..\include\prodef.h"
// -------------------------------------------------------------------------------
#define NORM_DC		0
#define OFFZEN_DC	1
#define OFFCR_DC	2
#define OFFWC_DC	3
#define OFFWP_DC	4
#define OFFWG_DC	5

#define OFFCHAOS_DC	6
#define OFFBLESS_DC	7
#define OFFSOUL_DC	8
#define OFFLIFE_DC	9

#define OFFAFK_DC	20

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
// -------------------------------------------------------------------------------

#pragma pack(push, 1)
struct CONNECTEX_CLOSE
{
	PBMSG_HEAD2	h;
};
#pragma pack(pop)
// -------------------------------------------------------------------------------

class ConnectEx
{
public:
			ConnectEx();
	void	Init();
	void	SendLogin(int UserIndex, CONNECTEX_LOGIN * Data);
	void	SendGame(int UserIndex);
	void	SendClose(int UserIndex, int Type);
	void	RecvClose(int UserIndex);
	void	Timer();

	int		ConnectIndex;
	DWORD   ConnectTick;
	// ----
}; extern ConnectEx g_ConnectEx;
// -------------------------------------------------------------------------------

#endif
// -------------------------------------------------------------------------------