#pragma once
#include "stdafx.h"
#include "Protocol.h"
#include "NewParty.h"
#include "Protocol.h"
// -----------------------------------------------------------------------------------------------

#define MAX_BUFF 300
// -----------------------------------------------------------------------------------------------

struct PMSG_BUFFLIST_SEND_PARTY
{
	PBMSG_HEAD h;				
	char szName[11];			
	char btBuffCount;					
	BYTE iBuffList[16];	
};
// -----------------------------------------------------------------------------------------------

struct PartyUser_Buff
{
	char szName[11];			
	char btBuffCount;				
	BYTE iBuffList[16];	
};
// -----------------------------------------------------------------------------------------------

class NewPartyBuff
{
public:
	float High;
	float Whith;

	float DrawX;

	void		Load();
	static void DrawPtIcon(DWORD a1, float a2, float a3, float a4, float a5);
	void		BindBuff(int BuffIndex);
	void		RecvBuff(PMSG_BUFFLIST_SEND_PARTY * Recv);
	void		DrawBuff();
	void		DrawBuffParty(int BuffIndex, int X, int Y);

	int	AllBuff[MAX_BUFF];
#if _NEW_PARTY_SYSTEM_ == TRUE
	PartyUser_Buff PartyUser[MAX_USER_IN_PARTY];
#else
	PartyUser_Buff PartyUser[5];
#endif
};
extern NewPartyBuff g_NewPartyBuff;
// -----------------------------------------------------------------------------------------------