// ImperialBattleUserMng.cpp: implementation of the CImperialBattleUserMng class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImperialBattleUserMng.h"
#include "Imperial.h"
#include "user.h"

#include "LogProc.h"

CImperialBattleUserMng g_ImperialBattleUserMng;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImperialBattleUserMng::CImperialBattleUserMng()
{
	this->ResetAllData();
}

CImperialBattleUserMng::~CImperialBattleUserMng()
{
	return;
}



void CImperialBattleUserMng::ResetAllData()
{
	this->m_iBattleUserCount = 0;
	this->SetMaxUser(MAX_IMPERIAL_BATTLE_USER);

	for ( int iCount=0;iCount<MAX_IMPERIAL_BATTLE_USER;iCount++)
	{
		this->m_BattleUser[iCount].ResetData();
	}
}



BOOL CImperialBattleUserMng::AddUserData(int iIndex)
{
	if ( !gObjIsConnected(iIndex))
	{
		LogAddTD("[Imperial][User Mng] Add User Fail - Disconnect User [%s][%s]",
			gObj[iIndex].AccountID, gObj[iIndex].Name);

		return FALSE;
	}

	for ( int iCount=0;iCount<MAX_IMPERIAL_BATTLE_USER;iCount++)
	{
		if ( this->m_BattleUser[iCount].IsUseData() == FALSE )
		{
			this->m_BattleUser[iCount].SetIndex(iIndex);
			this->m_iBattleUserCount++;
			
			return TRUE;
		}
	}

	return FALSE;
}


BOOL CImperialBattleUserMng::DeleteUserData(int iIndex)
{
	if ( iIndex < 0 || iIndex > OBJMAX-1)
	{
		LogAddTD("[Imperial][User Mng] Delete User Fail - Unvalid Index:%d",
			iIndex);

		return FALSE;
	}

	for ( int iCount=0;iCount<MAX_IMPERIAL_BATTLE_USER;iCount++)
	{
		if ( this->m_BattleUser[iCount].IsUseData() == TRUE )
		{
			if ( this->m_BattleUser[iCount].GetIndex() == iIndex )
			{
				this->m_BattleUser[iCount].ResetData();
				this->m_iBattleUserCount--;
				LogAddTD("[Imperial][User Mng] Delete User - [%s][%s] Current Battle User:%d",
					gObj[iIndex].AccountID, gObj[iIndex].Name, this->m_iBattleUserCount);

				return TRUE;
			}
		}
	}

	return FALSE;
}



void CImperialBattleUserMng::CheckUserState()
{
	int iIndex;

	for ( int iCount=0;iCount<MAX_IMPERIAL_BATTLE_USER;iCount++)
	{
		if ( this->m_BattleUser[iCount].IsUseData() == TRUE )
		{
			iIndex = this->m_BattleUser[iCount].GetIndex();

			if ( !gObjIsConnected(iIndex))
			{
				this->DeleteUserData(iIndex);

				LogAddTD("[Imperial][User Mng] Delete User - Disconnect [%s][%s]",
					gObj[iIndex].AccountID, gObj[iIndex].Name);
			}

			if ( !IMPERIAL_MAP_RANGE(gObj[iIndex].MapNumber) &&
				 gObj[iIndex].m_State == 2 &&
				 gObj[iIndex].Live == 1 )
			{
				this->DeleteUserData(iIndex);

				LogAddTD("[Imperial][User Mng] Delete User - Map Move [%s][%s]",
					gObj[iIndex].AccountID, gObj[iIndex].Name);
			}
		}
	}
}

BOOL CImperialBattleUserMng::CheckUserIsInEvent(int iIndex)
{
	for ( int i = 0; i < MAX_IMPERIAL_BATTLE_USER ; ++i )
	{
		if ( iIndex == this->m_BattleUser[i].GetIndex() )
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CImperialBattleUserMng::MoveAllUser(int iGateNumber)
{
	int iIndex;
	BOOL bMoveGateSuccess = FALSE;

	for ( int iCount=0;iCount<MAX_IMPERIAL_BATTLE_USER;iCount++)
	{
		iIndex = this->m_BattleUser[iCount].GetIndex();

		if ( this->m_BattleUser[iCount].IsUseData()  )
		{
			bMoveGateSuccess = gObjMoveGate(iIndex, iGateNumber);

			if ( bMoveGateSuccess == TRUE )
			{
				LogAddTD("[Imperial][User Mng] [%s][%s] MoveGate(%d)",
					gObj[iIndex].AccountID, gObj[iIndex].Name, iGateNumber);
			}
			else
			{
				this->DeleteUserData(iIndex);

				LogAddTD( "[Imperial][User Mng] [%s][%s] MoveGate Fail (%d)",
					gObj[iIndex].AccountID, gObj[iIndex].Name, iGateNumber);

				gObjMoveGate(iIndex, 137);
			}
		}
	}

	return TRUE;
}



void CImperialBattleUserMng::SetMaxUser(int iMaxUser)
{
	this->m_iBattleMaxUser = iMaxUser;

	if ( iMaxUser > MAX_IMPERIAL_BATTLE_USER )
	{
		this->m_iBattleMaxUser = MAX_IMPERIAL_BATTLE_USER;

		LogAddTD("[Imperial][User Mng] Set Max User:%d",
			iMaxUser);
	}
}



int CImperialBattleUserMng::GetMaxUser()
{
	return this->m_iBattleMaxUser;
}


int CImperialBattleUserMng::GetUserCount()
{
	return this->m_iBattleUserCount;
}


BOOL CImperialBattleUserMng::IsEmpty()
{
	if ( this->m_iBattleUserCount <= 0 )
	{
		return TRUE;
	}

	return FALSE;
}


BOOL CImperialBattleUserMng::IsOverMaxUser()
{
	if ( this->m_iBattleUserCount >=  MAX_IMPERIAL_BATTLE_USER )
	{
		return TRUE;
	}

	return FALSE;
}

/*

void CImperialBattleUserMng::LogBattleWinnerUserInfo(BYTE btFlag, int iElapsedTime)
{
	int iIndex = -1;
	float fTime = iElapsedTime / 1000.0f;

	for ( int iCount=0;iCount<MAX_Imperial_BATTLE_USER;iCount++)
	{
		if ( this->m_BattleUser[iCount].IsUseData() == TRUE )
		{
			iIndex = this->m_BattleUser[iCount].GetIndex();
			
			LogAddTD("[Imperial][User Mng] WINNER: [%d/ElapsedTime:%0.3f] [%s][%s] MapNumber[%d]-(%d/%d)",
				btFlag, fTime, gObj[iIndex].AccountID, gObj[iIndex].Name,
				gObj[iIndex].MapNumber, gObj[iIndex].X, gObj[iIndex].Y);

		}
	}
}
*/