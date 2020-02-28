#include "StdAfx.h"
#include "NewPartyBuff.h"
#include "user.h"
#include "..\common\winutil.h"
#include "GameServer.h"
#include "GameMain.h"
#include "logproc.h"
#include "ExLicense.h"

#ifdef _EX_DEV_BUFF_PT_

struct PMSG_BUFFLIST_SEND_PARTY
{
	PBMSG_HEAD h;				
	char szName[11];			
	char btBuffCount;			
	BYTE iBuffList[32];	
};

void GCDisplayBuffeffectPartyMember(int aIndex)
{
	//if(g_ExLicense.CheckUser(eExUB::PrideMuLocal) || g_ExLicense.CheckUser(eExUB::drynea) || g_ExLicense.CheckUser(eExUB::PrideMu) || g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::feqan))
	if(g_ExLicense.user.PartySystem || g_ExLicense.CheckUser(eExUB::MedoniAndrei))
	{
			
	int nDestUserIndex;
	signed int i;
	signed int nBuffCnt;
	int nPartyIndex;
	signed int nTotalBuffCount;
	PMSG_BUFFLIST_SEND_PARTY pMsg;

	if ( aIndex < 0 || aIndex > OBJMAX-1)
	{
		return;
	}

	if ( gObj[aIndex].Connected < PLAYER_PLAYING )
	{
		return;
	}

	if ( gObjIsConnected(aIndex) && gObj[aIndex].PartyNumber >= 0 )
	{
		ZeroMemory(&pMsg,sizeof(pMsg));
		//PHeadSetB((LPBYTE)&pMsg, 0x2E, 175);
		PHeadSetB((LPBYTE)&pMsg, 0x2E, sizeof(pMsg));
		//LogAddC(2, "PMSG_BUFFLIST_SEND_PARTY: %d", sizeof(pMsg));
		
		nTotalBuffCount = gObj[aIndex].m_btViewStateCount;
		pMsg.btBuffCount = gObj[aIndex].m_btViewStateCount;

	    memcpy(pMsg.szName, gObj[aIndex].Name, 10);
		nPartyIndex = gObj[aIndex].PartyNumber;
		if ( nTotalBuffCount >= 0 )
		{
			if ( nTotalBuffCount > 32 )
			{
				nTotalBuffCount = 32;
				pMsg.btBuffCount = 32;
			}
			for ( nBuffCnt = 0; nBuffCnt < nTotalBuffCount; nBuffCnt++ )
			{
				pMsg.iBuffList[nBuffCnt] = gObj[aIndex].m_BuffEffectState[nBuffCnt].btBuffIndex;
			}
			for ( i = 0; i < MAX_USER_IN_PARTY; ++i )
			{
				nDestUserIndex = gParty.m_PartyS[nPartyIndex].Number[i];
				if ( gObjIsConnected(nDestUserIndex) )
				{
					DataSend(nDestUserIndex, (LPBYTE)&pMsg, pMsg.h.size);
				}
		
			}
		}
	}
	}
}

#endif