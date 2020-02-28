#include "StdAfx.h"
#include "AutoParty.h"
#include "user.h"
#include "logproc.h"
#include "..\common\winutil.h"
#include "protocol.h"
#include "ChaosCastle.h"
#include "IllusionTempleEvent.h"
#include "GameMain.h"
#include "GensSystem.h"
#include "logproc.h"
#include "Configs.h"
#include "OffExp.h"
#include "ExLicense.h"

#ifdef AUTO_PARTY

cAutoParty gAutoParty;

cAutoParty::cAutoParty()
{

}

cAutoParty::~cAutoParty()
{

}

bool cAutoParty::CheckDistance(int aIndex, int x, int y)
{
	LPOBJ lpObj = &gObj[aIndex];

	int DisViewe = 2;

	if(x < lpObj->X - DisViewe  || x > lpObj->X + DisViewe || y < lpObj->Y - DisViewe || y > lpObj->Y + DisViewe)
	{
		return false;
	}

	return true;
}

void cAutoParty::Work()
{
	if(!ExConfig.ExCustom.AutoParty) return;
	for (int  aIndex=OBJ_STARTUSERINDEX;aIndex<OBJMAX;aIndex++)
	{
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->Connected < PLAYER_PLAYING) continue;
		for(int number = 0; number < OBJMAX; number++)
		{
			if(aIndex == number) continue;

			LPOBJ lpTempObj = &gObj[number];

			if(lpTempObj->Connected == PLAYER_PLAYING && lpTempObj->Type == OBJ_USER)
			{
				//if(lpTempObj->m_State == 1 || lpTempObj->m_State == 2)
				{
					if(lpObj->MapNumber == lpTempObj->MapNumber)
					{
						if(this->CheckDistance(aIndex,lpTempObj->X,lpTempObj->Y) == 1)
						{
							this->Party(aIndex, number);
						}
					}
				}
			}
		}
	}
}

void cAutoParty::Party(int aIndex, int number)
{
	if(gGENS)
	{
		if( gGensSystem.CheckPartyEnter )
		{
			if( gGensSystem.GetGensInfluence(&gObj[aIndex]) != gGensSystem.GetGensInfluence(&gObj[number]) )
			{
				return;
			}
		}
	}

	int pnumber = -1;

	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpParty = &gObj[number];

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))
	{
		if(!lpParty->bAutoPt)
		{
			return;
		}
	}

	if(lpObj->AutoPt == 0)
	{
		return;		
	}

	if(lpParty->AutoPt != 0) return;

	if(lpParty->Level > lpObj->AutoPt) 
	{
		return;
	}

	if(lpObj->AutoPt && lpParty->AutoPt) return; //fix 2 auto party

	//BYTE attr = MapC[lpObj->MapNumber].GetAttr(lpObj->X, lpObj->Y);
	//if ( (attr&1) != 1 )
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}

	if(!OffExp.CheckTerrain(lpObj))
	{
		return;
	}

	if ( gObj[aIndex].PartyNumber < 0 )
	{
		gObj[aIndex].PartyNumber = gParty.Create(aIndex, gObj[aIndex].DBNumber, gObj[aIndex].Level);
	}

	if ( gObj[aIndex].PartyNumber >= 0  && gObj[number].PartyNumber == -1)
	{
		if( !gParty.Isleader(gObj[aIndex].PartyNumber, aIndex, gObj[aIndex].DBNumber) )
		{
			return;
		}
#if _NEW_PARTY_SYSTEM_ == TRUE
		if( gParty.GetCount(gObj[aIndex].PartyNumber) >= g_MaxPartyMember )
#else
		if( gParty.GetCount(gObj[aIndex].PartyNumber) => 5 )
#endif
		{
			return;
		}

		pnumber = gObj[aIndex].PartyNumber;

		int iPartyPos = gParty.Add(gObj[aIndex].PartyNumber, number, gObj[number].DBNumber, gObj[number].Level);

		if ( iPartyPos >= 0 )
		{
			gObj[number].PartyNumber = gObj[aIndex].PartyNumber;

			gParty.Paint(pnumber);
		}
		else if ( iPartyPos == -1 )
		{
			return;
		}
		else if ( iPartyPos == -2 )
		{
			return;
		}
	}

	if ( pnumber >= 0 )
	{
		CGPartyListAll(pnumber);
	}
}

void cAutoParty::SendPartyList(int aIndex)
{
	if(!ExConfig.ExCustom.AutoParty) return;

	GCPartyList exSend;
	ZeroMemory(&exSend,sizeof(exSend));
	PHeadSubSetW((LPBYTE)&exSend, 0xFA, 0x05, sizeof(exSend));

	int Count = 0;

	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->Connected < PLAYER_PLAYING) return;
	for (int  number=OBJ_STARTUSERINDEX;number<OBJMAX;number++)
	{
		LPOBJ lpTempObj = &gObj[number];

		if(lpTempObj->Connected == PLAYER_PLAYING && lpTempObj->Type == OBJ_USER && lpTempObj->AutoPt )
		{
			if(lpTempObj->PartyNumber >= 0)
			{
				if( !gParty.Isleader(gObj[number].PartyNumber, number, gObj[number].DBNumber) )
				{
					continue;
				}
			}

			strncpy(exSend.Name[Count],lpTempObj->Name,10);
			exSend.Level[Count] = lpTempObj->AutoPt;
			exSend.Map[Count] = lpTempObj->MapNumber;
			exSend.X[Count] = lpTempObj->X;
			exSend.Y[Count] = lpTempObj->Y;
			exSend.Total[Count]  = gParty.GetCount(lpTempObj->PartyNumber);
			Count++;
			if(Count == 100) break;
		}
	}

	DataSend(aIndex,(LPBYTE)&exSend,sizeof(exSend));
}

#endif