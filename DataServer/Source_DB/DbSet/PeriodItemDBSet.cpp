// PeriodItemDBSet.cpp: implementation of the CPeriodItemDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PeriodItemDBSet.h"
#include "..\\winutil.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPeriodItemDBSet::CPeriodItemDBSet()
{

}

CPeriodItemDBSet::~CPeriodItemDBSet()
{

}

BOOL CPeriodItemDBSet::Connect()
{
	return CDBConBase::Connect(szDbConnectID, szDbConnectPass);
	//if( m_Query.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE )
	//{
	//	MsgBox("PeriodtemExDBSet ODBC Connect Fail");
	//	return FALSE;
	//}

	//return TRUE;
}

int CPeriodItemDBSet::Insert(int iUserGUID, char* pchCharacterName, int iItemCode, BYTE btEffectCategory, BYTE btEffectType1, BYTE btEffectType2, DWORD dwDuration, char * chExpireDate)
{
	int iReturnCode = 0;

	CString QuerySql;

//	CTime tExpireDate = (CTime)chExpireDate;
//
////#ifdef DEBUG_CODE
//	LogAdd(2,"%d-%d-%d %d:%d",tExpireDate.GetYear(), tExpireDate.GetMonth(), tExpireDate.GetDay(), tExpireDate.GetHour(), tExpireDate.GetMinute());
////#endif

	QuerySql.Format("EXEC WZ_PeriodItemInsert %d, '%s', %d, %d, %d, %d, %d, '%s'",
		iUserGUID, pchCharacterName, iItemCode, btEffectCategory, btEffectType1, btEffectType2, dwDuration, chExpireDate);

	if( m_DBQuery.Exec(QuerySql) == FALSE)
	{
		m_DBQuery.Clear();
		return -1;
	}

	if( m_DBQuery.Fetch() != SQL_NO_DATA)
	{
		iReturnCode = m_DBQuery.GetInt(1);
	}
	else
	{
		m_DBQuery.Clear();
		return -1;
	}

	m_DBQuery.Clear();

	return iReturnCode;
}

int CPeriodItemDBSet::Delete(int iUserGUID, char* pchCharacterName)
{
	CString QuerySql;

	if(SQLSyntexCheck(pchCharacterName) == FALSE)
	{
		return 2;
	}

	QuerySql.Format("EXEC WZ_PeriodItemDelete %d, '%s'", iUserGUID, pchCharacterName);

	if( m_DBQuery.Exec(QuerySql) == FALSE)
	{
		m_DBQuery.Clear();
		return 2;
	}

	if( m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return 1;
	}

	m_DBQuery.Clear();

	return 0;
}

int CPeriodItemDBSet::Select(LPITEMPERIOD_INFO lpPeriodItemList)
{
	int iReturnCode = 0;
	int iItemCount = 0;

	CString QuerySql;

	QuerySql.Format("EXEC WZ_PeriodItemSelect %d, '%s'", lpPeriodItemList->iUserGuid, lpPeriodItemList->chCharacterName);

	if( m_DBQuery.Exec(QuerySql) == FALSE)
	{
		m_DBQuery.Clear();
		return -3;
	}

	short i = m_DBQuery.Fetch();

	while(i != SQL_NO_DATA && i != SQL_NULL_DATA)
	{
		iReturnCode = m_DBQuery.GetInt(1);

		//LogAddTD("[PeriodItem][iReturnCode] %d", iReturnCode);

		if(iReturnCode < 0)
		{
			break;
		}

		lpPeriodItemList->DateInfo[iItemCount].btUsedInfo = 1;
		lpPeriodItemList->DateInfo[iItemCount].iItemCode = m_DBQuery.GetInt("ItemCode");
		lpPeriodItemList->DateInfo[iItemCount].btEffectType1 = m_DBQuery.GetInt("EffectType1");
		lpPeriodItemList->DateInfo[iItemCount].btEffectType2 = m_DBQuery.GetInt("EffectType2");
		lpPeriodItemList->DateInfo[iItemCount].btEffectCategory = m_DBQuery.GetInt("OptionType");
		lpPeriodItemList->DateInfo[iItemCount].dwItemUsedTime = m_DBQuery.GetInt("UsedMinutes");
		lpPeriodItemList->DateInfo[iItemCount].dwItemLeftTime = m_DBQuery.GetInt("LeftMinutes");
		iItemCount++;

		if(iItemCount >= 10)
		{
			LogAddTD("[PeriodItem][Select] Period Item List Count Over %d, User Id : %s(%d)", 10, lpPeriodItemList->chCharacterName, lpPeriodItemList->iUserGuid);
			break;
		}

		i = m_DBQuery.Fetch();
	}

	m_DBQuery.Clear();
	lpPeriodItemList->btDateInfoUseCount = iItemCount;

	return iReturnCode;
}

int CPeriodItemDBSet::Update(int iUserGUID, char* pchCharacterName, int iItemCode, DWORD dwDuration, int iLeftTime)
{
	int iReturnCode = 0;

	CString QuerySql;

	QuerySql.Format("EXEC WZ_PeriodItemUpdate %d, '%s', %d, %d, %d",
		iUserGUID, pchCharacterName, iItemCode, dwDuration, iLeftTime);

	if( m_DBQuery.Exec(QuerySql) == FALSE)
	{
		m_DBQuery.Clear();
		return -1;
	}

	if( m_DBQuery.Fetch() != SQL_NO_DATA)
	{
		iReturnCode = m_DBQuery.GetInt(1);
	}
	else
	{
		m_DBQuery.Clear();
		return -1;
	}

	m_DBQuery.Clear();

	return iReturnCode;
}
