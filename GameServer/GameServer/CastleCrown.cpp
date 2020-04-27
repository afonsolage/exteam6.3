// CastleCrown.cpp: implementation of the CCastleCrown class.
// GS-CS	1.00.90	JPN	-	Completed
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CastleCrown.h"
#include "CastleSiege.h"
#include "user.h"
#include "LogProc.h"
#include "ExLicense.h"
#include "UserConfig.h"

#if(GS_CASTLE==1)
CCastleCrown g_CsNPC_CastleCrown;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCastleCrown::CCastleCrown()
{
	return;
}

CCastleCrown::~CCastleCrown()
{
	return;
}


void CCastleCrown::CastleCrownAct(int iIndex)
{
	if ( !gObjIsConnected(iIndex))
		return;

	if ( gObj[iIndex].Type != OBJ_NPC ||
		 gObj[iIndex].Class != 216 )
		 return;

	if ( !gObjIsConnected(g_CastleSiege.GetCrownUserIndex()) )
	{
		g_CastleSiege.ResetCrownUserIndex();
		g_CastleSiege.SetCrownAccessUserX(0);
		g_CastleSiege.SetCrownAccessUserY(0);
		g_CastleSiege.ResetCrownAccessTickCount();

		return;
	}

	LPOBJ lpObj = &gObj[iIndex];
	LPOBJ lpUserObj = &gObj[g_CastleSiege.GetCrownUserIndex()];

#if(EVOMU_CASTLE_SEGE==TRUE)
	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
	{
		if(lpUserObj->CrownNpc == true)
		{
			g_CastleSiege.SetCrownAccessUserX(lpUserObj->X);
			g_CastleSiege.SetCrownAccessUserY(lpUserObj->Y);
			lpUserObj->CrownNpc = false;
		}
	}
#endif

	if(g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
	{
		if(lpUserObj->CrownNpc == true)
		{
			g_CastleSiege.SetCrownAccessUserX(lpUserObj->X);
			g_CastleSiege.SetCrownAccessUserY(lpUserObj->Y);
			lpUserObj->CrownNpc = false;
		}
	}

	if ( lpUserObj->MapNumber == MAP_INDEX_CASTLESIEGE && lpUserObj->m_btCsJoinSide >= 2 && lpUserObj->m_bCsGuildInvolved == 1 )
	{
		if ( lpUserObj->Y == g_CastleSiege.GetCrownAccessUserY() &&	lpUserObj->X == g_CastleSiege.GetCrownAccessUserX() )
		{
			if ( gObjIsConnected(g_CastleSiege.GetCrownUserIndex()) && gObjIsConnected(g_CastleSiege.GetCrownSwitchUserIndex(217)) && gObjIsConnected(g_CastleSiege.GetCrownSwitchUserIndex(218)) )
			{
				if ( gObj[g_CastleSiege.GetCrownUserIndex()].m_btCsJoinSide == gObj[g_CastleSiege.GetCrownSwitchUserIndex(217)].m_btCsJoinSide && gObj[g_CastleSiege.GetCrownUserIndex()].m_btCsJoinSide == gObj[g_CastleSiege.GetCrownSwitchUserIndex(217)].m_btCsJoinSide )
				{
					DWORD dwTime = GetTickCount() - g_CastleSiege.GetCrownAccessTickCount();

						LogAddTD("[CastleSiege] [Reg. Accumulating] Accumulated Crown AccessTime : acc(%d) + %d [%s](%s)(%s)",
							lpUserObj->m_iAccumulatedCrownAccessTime, dwTime,
							lpUserObj->GuildName, lpUserObj->AccountID, lpUserObj->Name);
				}
				else
				{
					GCAnsCsAccessCrownState(lpUserObj->m_Index, 2);
					g_CastleSiege.ResetCrownUserIndex();
					g_CastleSiege.SetCrownAccessUserX(0);
					g_CastleSiege.SetCrownAccessUserY(0);
					g_CastleSiege.ResetCrownAccessTickCount();

					LogAddTD("[CastleSiege] [%s][%s] Register Castle Crown Canceled (GUILD:%s)",
						lpUserObj->AccountID, lpUserObj->Name, lpUserObj->GuildName);
				}
			}
			else
			{
#if(EVOMU_CASTLE_SEGE==TRUE)
				if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
				{
					if(lpUserObj->m_iAccumulatedCrownAccessTime > 0)
					{
						//lpUserObj->m_iAccumulatedCrownAccessTime -= 4000;
						lpUserObj->m_iAccumulatedCrownAccessTime -= g_UserConfig.m_EvoMU.CSRegTimeMinus;
						if(lpUserObj->m_iAccumulatedCrownAccessTime < 0)
						{
							lpUserObj->m_iAccumulatedCrownAccessTime = 0;
						}
					}
				}
#endif

				if(g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
				{
					if(lpObj->m_iAccumulatedCrownAccessTime > 0)
					{
						lpObj->m_iAccumulatedCrownAccessTime = 0;
					}
				}

				GCAnsCsAccessCrownState(lpUserObj->m_Index, 2);//knopka
				g_CastleSiege.ResetCrownUserIndex();
				g_CastleSiege.SetCrownAccessUserX(0);
				g_CastleSiege.SetCrownAccessUserY(0);
				g_CastleSiege.ResetCrownAccessTickCount();
			}
		}
		else
		{
#if(EVOMU_CASTLE_SEGE==TRUE)
			if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
			{
				if(lpUserObj->m_iAccumulatedCrownAccessTime > 0)
				{
					//lpUserObj->m_iAccumulatedCrownAccessTime -= 4000;
					lpUserObj->m_iAccumulatedCrownAccessTime -= g_UserConfig.m_EvoMU.CSRegTimeMinus;
					if(lpUserObj->m_iAccumulatedCrownAccessTime < 0)
					{
						lpUserObj->m_iAccumulatedCrownAccessTime = 0;
					}
				}
			}
#endif
			if(g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
			{
				if(lpObj->m_iAccumulatedCrownAccessTime > 0)
				{
					lpObj->m_iAccumulatedCrownAccessTime = 0;
				}
			}
			//LogAddC(2,"X:%d == CX:%d | Y:%d == CY:%d", lpUserObj->X, g_CastleSiege.GetCrownAccessUserX(), lpUserObj->Y, g_CastleSiege.GetCrownAccessUserY());
			GCAnsCsAccessCrownState(lpUserObj->m_Index, 2);	//XY
			g_CastleSiege.ResetCrownUserIndex();
			g_CastleSiege.SetCrownAccessUserX(0);
			g_CastleSiege.SetCrownAccessUserY(0);
			g_CastleSiege.ResetCrownAccessTickCount();
		}
	}
	else
	{
		GCAnsCsAccessCrownState(lpUserObj->m_Index, 2);
		g_CastleSiege.ResetCrownUserIndex();
		g_CastleSiege.SetCrownAccessUserX(0);
		g_CastleSiege.SetCrownAccessUserY(0);
		g_CastleSiege.ResetCrownAccessTickCount();
	}
}

#endif