#include "stdafx.h"
#include "GameShopDBSet.h"
#include "winutil.h"
// -------------------------------------------------------------------------------

GameShopDBSet::GameShopDBSet()
{

}
// -------------------------------------------------------------------------------

GameShopDBSet::~GameShopDBSet()
{

}
// -------------------------------------------------------------------------------

bool GameShopDBSet::Connect()
{
	return CDBConBase::Connect(szDbConnectID, szDbConnectPass);
	////if( m_Query.Connect(3,gSettings.ConnectDNS,gSettings.ConnectLogin,gSettings.ConnectPassword) == FALSE )
	//if( m_Query.Connect(3, szDbConnectID, szDbConnectPass) == FALSE)
	//{
	//	//MsgBox("PeriodtemExDBSet ODBC Connect Fail");
	//	return FALSE;
	//}

	//return TRUE;
}
// -------------------------------------------------------------------------------

bool GameShopDBSet::SavePoint(char * AccountID, long WCoinP, long WCoinC, long GoblinPoint)
{

	char szAccountID[11];
	memcpy(szAccountID, AccountID, sizeof(szAccountID)-1);
	szAccountID[10] = 0;

	CString Query;
	// ----
	//Query.Format("UPDATE GameShopPoint SET WCoinC = %d, WCoinP = %d, GoblinPoint = %d WHERE AccountID = '%s'", 
	//	WCoinC, WCoinP, GoblinPoint, AccountID);
	// ----

	char szQuery[256];
	sprintf(szQuery, "EXEC EX_WCOIN_SAVE '%s', %d, %d, %d", szAccountID, WCoinC, WCoinP, GoblinPoint);

	if( !m_DBQuery.Exec(szQuery) )
	{
		m_DBQuery.Clear();
		return false;
	}
	// ----
	m_DBQuery.Clear();
	// ----


	return true;
}
// -------------------------------------------------------------------------------

bool GameShopDBSet::ReqPoint(char * AccountID, GAMESHOP_DG_GET_POINT * Result)
{
	char szAccountID[11];
	memcpy(szAccountID, AccountID, sizeof(szAccountID)-1);
	szAccountID[10] = 0;

	CString Query;
	// ----
	//Query.Format("SELECT * FROM GameShopPoint WHERE AccountID = '%s'", AccountID);
	Query.Format("EX_WCOIN_LOAD '%s'", szAccountID);
	// ----
	if( !m_DBQuery.Exec(Query) || m_DBQuery.Fetch() == SQL_NO_DATA )
	{
		m_DBQuery.Clear();
		// ----
		LogAdd("[%s] Failed to select values [Next: INSERT]", __FUNCTION__);
		// ----
		CString InsertQuery;
		// ----
		InsertQuery.Format("INSERT INTO GameShopPoint (AccountID, WCoinC, WCoinP, GoblinPoint) VALUES ('%s', %d, %d, %d)", 
			szAccountID, 0, 0, 0);
		// ----
		if( !m_DBQuery.Exec(InsertQuery) )
		{
			Result->WCoinC		= 0;
			Result->WCoinP		= 0;
			Result->GoblinPoint	= 0;
			m_DBQuery.Clear();
			LogAdd("[%s] Failed to insert new values", __FUNCTION__);
			return false;
		}
		// ----
		m_DBQuery.Clear();

		Result->WCoinC		= 0;
		Result->WCoinP		= 0;
		Result->GoblinPoint	= 0;
	}
	else
	{
		Result->WCoinC		= m_DBQuery.GetInt("WCoinC");
		Result->WCoinP		= m_DBQuery.GetInt("WCoinP");
		Result->GoblinPoint	= m_DBQuery.GetInt("GoblinPoint");
		m_DBQuery.Clear();
	}
	// ----
	return true;
}
// -------------------------------------------------------------------------------

void GameShopDBSet::InsertPoint(char * AccountID, long WCoinP, long WCoinC, long GoblinPoint)
{
	CString InsertQuery;
	// ----
	InsertQuery.Format("INSERT INTO GameShopPoint (AccountID, WCoinC, WCoinP, GoblinPoint) VALUES ('%s', %d, %d, %d)", 
		AccountID, 0, 0, 0);
	// ----
	if( !m_DBQuery.Exec(InsertQuery) )
	{
		LogAdd("[%s] Failed to insert new values", __FUNCTION__);
	}
	// ----
	m_DBQuery.Clear();
}
// -------------------------------------------------------------------------------