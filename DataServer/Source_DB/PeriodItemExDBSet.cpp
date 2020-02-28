// PeriodItemExDBSet.cpp: implementation of the CPeriodItemExDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PeriodItemExDBSet.h"
#include "winutil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPeriodItemExDBSet::CPeriodItemExDBSet()
{

}

CPeriodItemExDBSet::~CPeriodItemExDBSet()
{

}

BOOL CPeriodItemExDBSet::Connect()
{
	//if( m_Query.Connect(3,gSettings.ConnectDNS,gSettings.ConnectLogin,gSettings.ConnectPassword) == FALSE )
	return CDBConBase::Connect(szDbConnectID, szDbConnectPass);
	{
		//MsgBox("PeriodtemExDBSet ODBC Connect Fail");
		return FALSE;
	}

	return TRUE;
}

int CPeriodItemExDBSet::Insert(DWORD dwUserGUID, char* pchCharacterName, BYTE btItemType, WORD wItemCode, BYTE btEffectCategory, BYTE btEffectType1, BYTE btEffectType2, DWORD dwSerial, DWORD dwDuration, long lBuyDate, long lExpireDate)
{
	int iReturnCode = 0;

	CString QuerySql;

	QuerySql.Format("EXEC WZ_PeriodItemInsertEx %d, '%s', %d, %d, %d, %d, %d, %u, %d, %d, %d",
		dwUserGUID, pchCharacterName, btItemType, wItemCode, btEffectCategory, btEffectType1, btEffectType2, dwSerial, dwDuration, lBuyDate, lExpireDate);

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

int CPeriodItemExDBSet::Delete(DWORD dwUserGUID, char* pchCharacterName, WORD wItemCode, BYTE btItemType, DWORD dwSerial)
{
	CString QuerySql;

	if(SQLSyntexCheck(pchCharacterName) == FALSE)
	{
		return 2;
	}

	QuerySql.Format("EXEC WZ_PeriodItemDeleteEx %d, '%s', %d, %d, %u", dwUserGUID, pchCharacterName, wItemCode, btItemType, dwSerial);

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

int CPeriodItemExDBSet::Select(LPPERIOD_ITEMLIST lpPeriodItemList)
{
	int iReturnCode = 0;
	int iItemCount = 0;

	CString QuerySql;

	QuerySql.Format("EXEC WZ_PeriodItemSelectEx %d, '%s'", lpPeriodItemList->dwUserGuid, lpPeriodItemList->chCharacterName);

	if( m_DBQuery.Exec(QuerySql) == FALSE)
	{
		m_DBQuery.Clear();
		return -3;
	}

	short i = m_DBQuery.Fetch();

	while(i != SQL_NO_DATA && i != SQL_NULL_DATA)
	{
		iReturnCode = m_DBQuery.GetInt(1);

		if(iReturnCode < 0)
		{
			break;
		}

		lpPeriodItemList->ItemData[iItemCount].btUsedInfo			= 1;
		lpPeriodItemList->ItemData[iItemCount].wItemCode			= m_DBQuery.GetInt("ItemCode");
		lpPeriodItemList->ItemData[iItemCount].btItemType			= m_DBQuery.GetInt("ItemType");
		lpPeriodItemList->ItemData[iItemCount].btEffectType1		= m_DBQuery.GetInt("EffectType1");
		lpPeriodItemList->ItemData[iItemCount].btEffectType2		= m_DBQuery.GetInt("EffectType2");
		lpPeriodItemList->ItemData[iItemCount].btEffectCategory		= m_DBQuery.GetInt("OptionType");
		lpPeriodItemList->ItemData[iItemCount].dwSerial				= (DWORD)m_DBQuery.GetInt64("SerialCode");
		lpPeriodItemList->ItemData[iItemCount].lItemBuyDate			= m_DBQuery.GetInt("BuyDateConvert");
		lpPeriodItemList->ItemData[iItemCount].lItemExpireDate		= m_DBQuery.GetInt("ExpireDateConvert");
		iItemCount++;

		if(iItemCount >= 100)
		{
			LogAdd("[PeriodItemEx][Select] Period Item List Count Over %d, User Id : %s(%d)", 100, lpPeriodItemList->chCharacterName, lpPeriodItemList->dwUserGuid);
			break;
		}

		i = m_DBQuery.Fetch();
	}

	m_DBQuery.Clear();
	lpPeriodItemList->btItemCount = iItemCount;

	return iReturnCode;
}

int CPeriodItemExDBSet::Update()
{
	int iReturnCode = 0;

	return iReturnCode;
}

int CPeriodItemExDBSet::SelectExpiredItemList(DWORD dwUserGuid, char* pchCharacterName, LPPERIOD_EXPIRED_ITEMLIST lpExpiredItemList)
{
	int iReturnCode = 0;
	int iItemCount = 0;
	
	CString QueryStr;
	QueryStr.Format("EXEC WZ_PeriodItemExpiredItemSelectEx %d, '%s'", dwUserGuid, pchCharacterName);

	if( m_DBQuery.Exec(QueryStr) == FALSE)
	{
		m_DBQuery.Clear();
		return -3;
	}

	short sqlReturn = m_DBQuery.Fetch();

	while(sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
	{
		lpExpiredItemList->ExpiredItem[iItemCount].wItemCode = m_DBQuery.GetInt("ItemCode");
		lpExpiredItemList->ExpiredItem[iItemCount].dwSerial = (DWORD)m_DBQuery.GetInt64("SerialCode");
		iItemCount++;

		sqlReturn = m_DBQuery.Fetch();

		if(iItemCount >= 30)
		{
			break;
		}
	}

	m_DBQuery.Clear();

	lpExpiredItemList->btItemCount = iItemCount;

	return iItemCount; //wz bug
}

LuckyItemDBSet::LuckyItemDBSet()
{

}

LuckyItemDBSet::~LuckyItemDBSet()
{

}

BOOL LuckyItemDBSet::Connect()
{
	return CDBConBase::Connect(szDbConnectID, szDbConnectPass);
	//if( m_Query.Connect(3,gSettings.ConnectDNS,gSettings.ConnectLogin,gSettings.ConnectPassword) == FALSE )
	//{
	//	//MsgBox("LuckyItemDBSet ODBC Connect Fail");
	//	return FALSE;
	//}

	//return TRUE;
}

int LuckyItemDBSet::Insert(DWORD dwUserGuid, char* szCharName, WORD wItemCode, DWORD dwSerial, WORD wDurabilitySmall)
{
	int iReturnCode = 0;

	CString QuerySql;
	QuerySql.Format("EXEC WZ_LuckyItemInsert %d, '%s', %d, %u, %d", dwUserGuid, szCharName, wItemCode, dwSerial, wDurabilitySmall);

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

int LuckyItemDBSet::Delete(char* szCharName, WORD wItemCode, DWORD dwSerial)
{
	int iReturnCode = 0;

	CString QuerySql;
	QuerySql.Format("WZ_LuckyItemDelete '%s', %d, %u", szCharName, wItemCode, dwSerial);

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

int LuckyItemDBSet::SelectLuckyItemList(char* szCharName, LPPMSG_LUCKYITME_DB_INFO pLuckyItemInfo)
{
	int iItemCount = 0;
	int iReturnCode = 0;

	CString QueryStr;

	QueryStr.Format("WZ_LuckyItemSelect '%s'", szCharName);

	if( m_DBQuery.Exec(QueryStr) == FALSE)
	{
		m_DBQuery.Clear();
		return -3;
	}

	short sqlReturn = m_DBQuery.Fetch();

	while(sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
	{
		pLuckyItemInfo[iItemCount].wItemCode = m_DBQuery.GetInt("ItemCode");
		pLuckyItemInfo[iItemCount].dwSerial = (DWORD)m_DBQuery.GetInt64("ItemSerial");
		pLuckyItemInfo[iItemCount].wDurabilitySmall = (WORD)m_DBQuery.GetInt64("DurabilitySmall");
		iItemCount++;

		sqlReturn = m_DBQuery.Fetch();

		if(iItemCount >= 45)
		{
			break;
		}
	}

	m_DBQuery.Clear();

	return iItemCount; //wz bug
}