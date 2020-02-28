#include <windows.h>
#include "stdafx.h"
#include "DelayHandler.h"

CQuery::CQuery()
{
	this->WriteLog = true;
	this->AffectCount=-1;
	this->ret=SQL_SUCCESS;

	SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&this->hEnv);
	SQLSetEnvAttr(this->hEnv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER);
}

CQuery::~CQuery()
{
	if (this->hStmt) SQLFreeHandle(SQL_HANDLE_STMT,this->hStmt);
	if (this->hDbc)  SQLDisconnect(this->hDbc);
	if (this->hDbc)  SQLFreeHandle(SQL_HANDLE_DBC,this->hDbc);
	if (this->hEnv)  SQLFreeHandle(SQL_HANDLE_ENV,this->hEnv);
}

BOOL CQuery::Connect(int Type, char *ConStr, char *UID, char *PWD)
{
	SQLCHAR InCon[255];
	SQLCHAR OutCon[255];
    SQLSMALLINT cbOutCon;

	int ii=1;
	SQLRETURN Ret;
	SQLINTEGER NativeError;
	SQLCHAR SqlState[6], Msg[255];
	SQLSMALLINT MsgLen;
	char str[256];

	this->m_Type = Type;
	strcpy(this->m_szConnect, ConStr);
	strcpy(this->m_Id, UID);
	strcpy(this->m_Pass, PWD);

	SQLAllocHandle(SQL_HANDLE_DBC,this->hEnv,&this->hDbc);

	switch (Type) 
	{
	case 1:
		wsprintf((char *)InCon,"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=%s;",ConStr);
		ret=SQLDriverConnect(this->hDbc,NULL,(SQLCHAR *)InCon,sizeof(InCon),OutCon,sizeof(OutCon),&cbOutCon, SQL_DRIVER_NOPROMPT);
		break;
	case 2:
		wsprintf((char *)InCon, "FileDsn=%s",ConStr);
		ret=SQLDriverConnect(this->hDbc,NULL,(SQLCHAR *)InCon,sizeof(InCon),OutCon,sizeof(OutCon),&cbOutCon, SQL_DRIVER_NOPROMPT);
		break;
	case 3:
		ret=SQLConnect(this->hDbc,(SQLCHAR *)ConStr,SQL_NTS,(SQLCHAR *)UID,SQL_NTS,(SQLCHAR *)PWD,SQL_NTS);
		break;
	}

	if ((this->ret != SQL_SUCCESS) && (this->ret != SQL_SUCCESS_WITH_INFO)) 
	{
		while (Ret=SQLGetDiagRec(SQL_HANDLE_DBC, this->hDbc, ii, SqlState, &NativeError, Msg, sizeof(Msg), &MsgLen)!=SQL_NO_DATA) 
		{
			wsprintf(str, "(1) SQLSTATE:%s, Diagnosis:%s",(LPCTSTR)SqlState,(LPCTSTR)Msg);
#if(NEW_WIN)
			LogAddC(LOGC_RED, str);
#else
			LogAddTD(str);
#endif
			ii++;
		}
		return FALSE;
	}

	this->ret=SQLAllocHandle(SQL_HANDLE_STMT,this->hDbc,&this->hStmt);
	if ((this->ret != SQL_SUCCESS) && (this->ret != SQL_SUCCESS_WITH_INFO)) 
	{
		this->hStmt=0;
		return FALSE;
	}

	this->WriteLog = false;

	struct Temp
	{  
		char AddQuery[255];
		char Column[35];	  
		char Table[35];
	};

	Temp QueryMuOnline[] = 
	{
		{"alter table [Character] add [pcpoint] int not null default(0)","pcpoint","Character"},
		{"alter table [Character] add [ExFreePoints] int not null default(0)","ExFreePoints","Character"},
		{"alter table [Character] add [Resets] int not null default(0)","Resets","Character"},
		{"alter table [Character] add [gr_res] int not null default(0)","gr_res","Character"},
		{"alter table [Character] add [ExQuestNum] int not null default(0)","ExQuestNum","Character"},
		{"alter table [Character] add [ExQuestKill] int not null default(0)","ExQuestKill","Character"},
		{"alter table [Character] add [PremiumTime] int not null default(0)","PremiumTime","Character"},
#ifdef CONFLICT_PREM_TYPE
		{"alter table [Character] add [PremiumTimeType] int not null default(0)","PremiumTimeType","Character"},
#endif
		{"alter table [Character] add [ExCred] float not null default(0)","ExCred","Character"},
#ifdef _CR_MEMB_INFO_
		{"alter table [MEMB_INFO] add [ExCredit] float not null default(0)","ExCredit","MEMB_INFO"},
#endif
#ifdef CONFLICT_PREM
		{"alter table [MEMB_INFO] add [PremiumTime] int not null default(0)","ExCredit","MEMB_INFO"},
#endif
		//{"alter table [MEMB_INFO] add [PremiumTimeType] int not null default(0)","PremiumTimeType","MEMB_INFO"},

		{"alter table [Character] add [BanChat] int not null default(0)","BanChat","Character"},
		{"alter table [Character] add [BanPost] int not null default(0)","BanPost","Character"},
		{"alter table [Character] add [BanChar] int not null default(0)","BanChar","Character"},
		{"alter table [Character] add [ExpandedInventory] int not null default(0)","ExpandedInventory","Character"},
		{"alter table [AccountCharacter] add [ExpandedWarehouse] int not null default(0)","ExpandedWarehouse","AccountCharacter"},
		{"alter table [Character] add [ChaosBank] int not null default(0)","ChaosBank","Character"},
		{"alter table [Character] add [BlessBank] int not null default(0)","BlessBank","Character"},
		{"alter table [Character] add [SoulBank] int not null default(0)","SoulBank","Character"},
		{"alter table [Character] add [LifeBank] int not null default(0)","LifeBank","Character"},
		{"alter table [MEMB_INFO] add [MTDate] int not null default(0)","MTDate","MEMB_INFO"},
		{"alter table [Character] add [AutoParty] int not null default(0)","AutoParty","Character"},
		{"alter table [Character] add [Zen] int not null default(0)","Zen","Character"},
		{"alter table [MEMB_INFO] add [QTDate] int not null default(0)", "QTDate", "MEMB_INFO" },
		{"alter table [Character] add [QuestNum] int not null default(0)","QuestNum","Character"},
		{"alter table [Character] add [QuestKill_1] int not null default(0)","QuestKill_1","Character"},
		{"alter table [Character] add [QuestKill_2] int not null default(0)","QuestKill_2","Character"},
		{"alter table [Character] add [QuestKill_3] int not null default(0)","QuestKill_3","Character"},
		{"alter table [Character] add [QuestKill_4] int not null default(0)","QuestKill_4","Character"},
		{"alter table [Character] add [QuestKill_5] int not null default(0)","QuestKill_5","Character"},
		{"alter table [Character] add [Brother][varchar](10) not null default('One')","Brother","Character"},
		{"alter table [Character] add [PartySearch] varbinary(11) not null default(0)","PartySearch","Character"},	
		//{"alter table [Character] add [RageSystem] varbinary(152)","RageSystem","Character"},
		{"alter table [Character] add [RageSystem] varbinary(152) not null default(0)","RageSystem","Character"},
		{"alter table [Character] add [BMQuest_num] int not null default(0)","BMQuest_num","Character"},
		{"alter table [Character] add [BMQuest_kill] int not null default(0)","BMQuest_kill","Character"},
		{"alter table [Character] add [BMQuest_start] int not null default(0)","BMQuest_start","Character"},
		{"alter table [Character] add [BMDamageReflect] int not null default(0)","BMDamageReflect","Character"},
		{"alter table [Character] add [BMDamage] int not null default(0)","BMDamage","Character"},
		{"alter table [Character] add [BMDefense] int not null default(0)","BMDefense","Character"},
		{"alter table [Character] add [BMCriticalDamage] int not null default(0)","BMCriticalDamage","Character"},
		{"alter table [Character] add [BMExcelentDamage] int not null default(0)","BMExcelentDamage","Character"},
		{"alter table [Character] add [BMLife] int not null default(0)","BMLife","Character"},
		{"alter table [Character] add [StatusSpot] int not null default(0)","StatusSpot","Character"},
		{"alter table [Character] add [ExpBuffTime] int not null default(0)","ExpBuffTime","Character"},
		{"alter table [Character] add [DamageBuffTime] int not null default(0)","DamageBuffTime","Character"},
		{"alter table [Character] add [DefenceBuffTime] int not null default(0)","DefenceBuffTime","Character"},
		{"alter table [Character] add [BattleBuffTime] int not null default(0)","BattleBuffTime","Character"},
		{"alter table [Character] add [DropBuffTime] int not null default(0)","DropBuffTime","Character"},
		{"alter table [Character] add [DoubleBuffTime] int not null default(0)","DoubleBuffTime","Character"},

#if(CUSTOM_SAVE_PT==TRUE)
		{"alter table [Character] add [PartyIndex] int not null default(0)","PartyIndex","Character"},
		{"alter table [GameServerInfo] add [PartyCount] int not null default(0)","PartyCount","GameServerInfo"},
#endif

		{"alter table [Character] add [CreateonBank] int not null default(0)","CreateonBank","Character"},
		{"alter table [MEMB_INFO] add [DonateCredit] int not null default(0)","DonateCredit","MEMB_INFO"},
		{"alter table [MEMB_INFO] add [PCPoint] int not null default(0)","PCPoint","MEMB_INFO"},
		/*alter table [Character] add [PartyIndex] int not null default(0)
		alter table [GameServerInfo] add [PartyCount] int not null default(0)*/
	};

	for(int i=0;i<(sizeof(QueryMuOnline)/sizeof(QueryMuOnline[0]));i++)
	{
		//char SendQuery[257] = {0};
		//sprintf(SendQuery,"SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.Columns where COLUMN_NAME = '%s' and TABLE_NAME = '%s'",QueryMuOnline[i].Column,QueryMuOnline[i].Table);
		//if(this->Exec(SendQuery) == FALSE)
		{
		//	if (this->Fetch()==SQL_NO_DATA) 
			{
				//this->Clear();

				this->Exec(QueryMuOnline[i].AddQuery);
				this->Fetch();
				this->Clear();
			}
		}
	}

	char szQuery[1024]	= "CREATE TABLE RageSystem(Accaunt varchar(10),Name varchar(10),RageLevel int,RagePoint int,RageExp int,";
	strcat(szQuery, "Damage int,FreePoints int,SummonPet int,WingsDamagePlus int,FinalMana int,IgnoreDefence int,ResetLevel int,Teleport int,CriticalDamageRate int,AbsordDamage int,PetDamageBonus int,");
	strcat(szQuery,"FinalLife int,Strength int,DefenceRate int,FireDamage int,Energy int,Agility int,DoubleDamage int,FinalSD int,FinalDefence int,ZenDrop int,GuildBonus int,");
	strcat(szQuery,"ReflectDamage int,ExellentDamageRate int,PvPBonusPlus int,MinDefence int,Experience int,StartSD int,PartyBonus int,IceDamage int,DistanceAttack int,AttackRate int,WeaponBonus int,");
	strcat(szQuery,"ExellentDamage int,CriticalDamage int);");
	this->Exec(szQuery);
	this->Fetch();
	this->Clear();

	ZeroMemory(szQuery, sizeof(szQuery));
	strcpy(szQuery, "CREATE TABLE GensMember(Name varchar(10), Influence int, Class int, Contribute int, Rank int, RewardDate smalldatetime)");
	this->Exec(szQuery);
	this->Fetch();
	this->Clear();

	ZeroMemory(szQuery, sizeof(szQuery));
	strcat(szQuery, "CREATE TABLE WinQuest(Name varchar(10), S1 int, S2 int, S3 int, S4 int, S5 int, S6 int, S7 int, S8 int, S9 int, S10 int,");
	strcat(szQuery,"N1 int, N2 int, N3 int, N4 int, N5 int, N6 int, N7 int, N8 int, N9 int, N10 int,");
	strcat(szQuery,"C11 int, C12 int, C13 int, C14 int, C15 int,");
	strcat(szQuery,"C21 int, C22 int, C23 int, C24 int, C25 int,");
	strcat(szQuery,"C31 int, C32 int, C33 int, C34 int, C35 int,");
	strcat(szQuery,"C41 int, C42 int, C43 int, C44 int, C45 int,");
	strcat(szQuery,"C51 int, C52 int, C53 int, C54 int, C55 int,");
	strcat(szQuery,"C61 int, C62 int, C63 int, C64 int, C65 int,");
	strcat(szQuery,"C71 int, C72 int, C73 int, C74 int, C75 int,");
	strcat(szQuery,"C81 int, C82 int, C83 int, C84 int, C85 int,");
	strcat(szQuery,"C91 int, C92 int, C93 int, C94 int, C95 int,");
	strcat(szQuery,"C101 int,C102 int,C103 int,C104 int,C105 int,");
	strcat(szQuery,"Damage int,");
	strcat(szQuery,"Defence int,");
	strcat(szQuery,"Life int,");
	strcat(szQuery,"SD int,");
	strcat(szQuery,"Crit int,");
	strcat(szQuery,"Exel int,");
	strcat(szQuery,"DD int,");
	strcat(szQuery,"Ignore int,");
	strcat(szQuery,"Ref int,");
	strcat(szQuery,"Exp int,");
	strcat(szQuery,"Dr int);");

	this->Exec(szQuery);
	this->Fetch();
	this->Clear();

	//UPDATE Character SET RageSystem = 0x0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	//char szQuery2[] = "EXEC EX_OFFLINEMODE_SAVE 'Helper', 1, 1, 'est' 4e?'";
	//this->Exec(szQuery2);

	this->WriteLog = true;
	return TRUE;
}

BOOL CQuery::ReConnect()
{
	return this->Connect(this->m_Type, this->m_szConnect, this->m_Id, this->m_Pass);
}

/*BOOL CQuery::Exec(LPCTSTR szSQL)
{
	int c;
	while( true )
	{		
		if(this->WriteLog)
		{
			LogAddTD("%s", szSQL);
		}
		this->ret=SQLExecDirect(this->hStmt,(SQLCHAR *)szSQL,SQL_NTS);
		if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO) && (ret != SQL_NO_DATA))
		{			
			bool bReConnect = false;
			this->PrintDiag(bReConnect);
			this->Clear();

			if(bReConnect == true)
			{
				::Sleep(1);
				continue;
			}
			return FALSE;
		}

		SQLRowCount(this->hStmt,&this->AffectCount);
		SQLNumResultCols(this->hStmt,&this->nCol);

		//if(this->AffectCount  == 0)
		//{
		//	return FALSE;
		//}

		if (this->nCol > MAXCOL) 
		{
			LogAdd("CQuery error : nCol > MAXCOL");
			return FALSE;
		}

		if (this->nCol == 0) 
		{
			this->Clear();
			//return TRUE;
			return TRUE;
		}

		for (c=0;c<nCol;c++) 
		{
			SQLBindCol(this->hStmt,c+1,SQL_C_CHAR,this->Col[c],255,&lCol[c]);
			SQLDescribeCol(this->hStmt,c+1,this->ColName[c],30,NULL,NULL,NULL,NULL,NULL);
		}
		return TRUE;
	}
}*/

BOOL CQuery::Exec(LPCTSTR szSQL)
{
	if(this->WriteLog)
	{
		LogAddTD("%s", szSQL);
	}

	ret=SQLExecDirect(hStmt,(SQLCHAR *)szSQL,SQL_NTS);

	if((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO) && (ret != SQL_NO_DATA)) 
	{
		bool bReConnect = false;
		PrintDiag(bReConnect);
		return FALSE;
	}

	SQLRowCount(hStmt,&AffectCount);
	SQLNumResultCols(hStmt,&nCol);

	if(nCol > MAXCOL) 
	{
		LogAdd("Query error : nCol > MAXCOL");
		return FALSE;
	}

	if(nCol == 0) 
	{
		Clear();
		return TRUE;
	}

	for(int c=0;c<nCol;c++) 
	{
		SQLBindCol(hStmt,c+1,SQL_C_CHAR,Col[c],255,&lCol[c]);
		SQLDescribeCol(hStmt,c+1,ColName[c],30,NULL,NULL,NULL,NULL,NULL);
	}
	return TRUE;
}

int CQuery::ExecGetInt(LPCTSTR szSQL)
{
	int i;

	if (this->Exec(szSQL) == FALSE) 
	{
		return CQUERYERROR;
	}

	if (this->Fetch()==SQL_NO_DATA) 
	{
		this->Clear();
		return CQUERYEOF;
	}
	i=this->GetInt(1);
	this->Clear();
	return i;
}

int CQuery::ExecGetInt(char* szSQL, int * retvalue)
{
	LogAddTD("%s", szSQL);

	if (this->Exec(szSQL) == FALSE) 
	{
		return FALSE;
	}

	if (this->Fetch()==SQL_NO_DATA) 
	{
		this->Clear();
		return FALSE;
	}

	int i=this->GetInt(1);
	this->Clear();
	*retvalue = i;
	
	return TRUE;
}

BOOL CQuery::ExecGetStr(LPCTSTR szSQL, char *buf)
{
	if (this->Exec(szSQL) == FALSE) 
	{
		buf[0] = '\0';
		return FALSE;
	}

	if (this->Fetch()==SQL_NO_DATA) 
	{
		this->Clear();
		buf[0] = '\0';
		return FALSE;
	}
	this->GetStr(1,buf);
	this->Clear();
	return TRUE;
}

SQLRETURN CQuery::Fetch()
{
	ret=SQLFetch(hStmt);
	return ret;
}

void CQuery::Clear()
{
#if(QUERY_RECODE==TRUE)
	SQLFreeStmt(hStmt, SQL_CLOSE);
#else
	SQLCloseCursor(hStmt);
#endif
	::SQLFreeStmt(hStmt, SQL_UNBIND);
}

int CQuery::FindCol(char *name)
{
	int i;
	for (i=0;i<nCol;i++) 
	{
		if (stricmp(name,(LPCTSTR)this->ColName[i])==0)
		{
			return i+1;
		}
	}
	return -1;
}

int CQuery::GetInt(int nCol)
{
	if (nCol > nCol)
	{
		return CQUERYNOCOL;
	}

	if (this->lCol[nCol-1]==SQL_NULL_DATA) 
	{
		return CQUERYNULL;
	}
	else 
	{
		return atoi(this->Col[nCol-1]);
	}
}

int CQuery::GetInt(char *sCol)
{
	int n;
	n=this->FindCol(sCol);
	if (n==-1) 
	{
		return CQUERYNOCOL;
	}
	else 
	{
		return this->GetInt(n);
	}
}

__int64 CQuery::GetInt64(int nCol)
{
	if (nCol > nCol)
	{
		return CQUERYNOCOL;
	}

	if (this->lCol[nCol-1]==SQL_NULL_DATA) 
	{
		return CQUERYNULL;
	} 
	else 
	{
		return _atoi64(Col[nCol-1]);
	}
}

__int64 CQuery::GetInt64(char* sCol)
{
	int n;
	n = this->FindCol(sCol);

	if (n==-1) 
	{
		return CQUERYNOCOL;
	} 
	else 
	{
		return this->GetInt64(n);
	}
}

float CQuery::GetFloat(int nCol)
{
	if (nCol > nCol)
	{
		return CQUERYNOCOL;
	}

	if (this->lCol[nCol-1]==SQL_NULL_DATA) 
	{
		return CQUERYNULL;
	}
	else 
	{
		return (float)atof(Col[nCol-1]);
	}
}

float CQuery::GetFloat(char *sCol)
{
	int n;
	n=this->FindCol(sCol);
	if (n==-1) 
	{
		return CQUERYNOCOL;
	} 
	else 
	{
		return this->GetFloat(n);
	}
}

void CQuery::GetStr(int nCol, char *buf)
{
	if (nCol > nCol) 
	{
		buf[0] = '\0';
		return;
	}

	if (this->lCol[nCol-1]==SQL_NULL_DATA) 
	{
		buf[0] = '\0';
	} 
	else 
	{
		lstrcpy(buf,this->Col[nCol-1]);
	}
}

void CQuery::GetStr(char *sCol, char *buf)
{
	int n;
	n=this->FindCol(sCol);
	if (n==-1) 
	{
		buf[0] = '\0';
	} else 
	{
		this->GetStr(n, buf);
	}
}

void CQuery::PrintDiag(bool &bReconnect)
{
	int ii;
	SQLRETURN Ret;
	SQLINTEGER NativeError;
	SQLCHAR SqlState[6], Msg[255];
	SQLSMALLINT MsgLen;
	char str[256];

	ii=1;
	while (Ret=SQLGetDiagRec(SQL_HANDLE_STMT, this->hStmt, ii, SqlState, &NativeError, Msg, sizeof(Msg), &MsgLen)!=SQL_NO_DATA) 
	{
		if(this->WriteLog)
		{
			wsprintf(str, "(2) SQLSTATE:%s, Diagnosis:%s",(LPCTSTR)SqlState,(LPCTSTR)Msg);
#if(NEW_WIN)
			LogAddC(LOGC_RED, str);
#else
			LogAddTD(str);
#endif
		}
		ii++;
		if(ii > 3) break;
	}

	if( strcmp((LPCTSTR)SqlState, "08S01") == 0 )
	{
		if(this->ReConnect() == 1) 
		{
			g_DelayHandler.IncreaseQuerySessionId();
		}
		bReconnect = true;
	}
}

int CQuery::ReadBlob(LPCTSTR szSQL, void *buf)
{
	SQLCHAR BinaryPtr[BLOBBATCH];
	SQLINTEGER LenBin;
	char *p;
	int nGet;
	int TotalGet=0;

	while(true)
	{
		this->ret=SQLExecDirect(this->hStmt,(SQLCHAR *)szSQL,SQL_NTS);
		if (this->ret!=SQL_SUCCESS)
		{
			bool bReconnect = false;
			this->PrintDiag(bReconnect);
			if(bReconnect == true)
			{
				::Sleep(1);
				continue;
			}

			return -1;
		}

		while((this->ret=SQLFetch(this->hStmt)) != SQL_NO_DATA) 
		{
			p=(char *)buf;
			while ((ret=SQLGetData(this->hStmt,1,SQL_C_BINARY,BinaryPtr,sizeof(BinaryPtr),&LenBin))!=SQL_NO_DATA) 
			{
				if (LenBin==SQL_NULL_DATA) 
				{
					this->Clear();
					return 0;
				}
				if (ret==SQL_SUCCESS)
				{
					nGet=LenBin;
				}
				else
				{
					nGet=BLOBBATCH;
				}
				TotalGet+=nGet;
				memcpy(p,BinaryPtr,nGet);
				p+=nGet;
			}
		}
		this->Clear();
		return TotalGet;
	}
}

void CQuery::WriteBlob(LPCTSTR szSQL, void *buf, int size)
{
	SQLINTEGER cbBlob;
	char tmp[BLOBBATCH],*p;
	SQLPOINTER pToken;
	int nPut;

	cbBlob=SQL_LEN_DATA_AT_EXEC(size);
	SQLBindParameter(this->hStmt,1,SQL_PARAM_INPUT,SQL_C_BINARY,SQL_LONGVARBINARY,
		size,0,(SQLPOINTER)1,0,&cbBlob);
	SQLExecDirect(this->hStmt,(SQLCHAR *)szSQL,SQL_NTS);
	this->ret=SQLParamData(this->hStmt, &pToken);
	while (this->ret==SQL_NEED_DATA) 
	{
		if (this->ret==SQL_NEED_DATA) 
		{
			if ((int)pToken==1) 
			{
				for (p=(char *)buf;p<(char *)buf+size;p+=BLOBBATCH) 
				{
					nPut=min(BLOBBATCH,(char *)buf+size-p);
					memcpy(tmp,p,nPut);
					SQLPutData(this->hStmt,(PTR)tmp,nPut);
				}
			}
		}
		this->ret=SQLParamData(this->hStmt, &pToken);
	}
	this->Clear();
}

int CQuery::BindParameterBinaryOutput(int nCol, BYTE *nValue, int iSize, long *lLength)
{
	return SQLBindParameter(this->hStmt, nCol, 4, -2, -3, iSize, 0, nValue, iSize, lLength);
}

BOOL CQuery::ExecH(LPCTSTR szSQL)
{
	int c;
	while(true)
	{		
		this->ret=SQLExecDirect(this->hStmt,(SQLCHAR *)szSQL,SQL_NTS);
		if ((this->ret != SQL_SUCCESS) && (this->ret != SQL_SUCCESS_WITH_INFO) && (this->ret != SQL_NO_DATA))
		{			
			bool bReConnect = false;
			this->PrintDiag(bReConnect);
			this->Clear();
			if(bReConnect == true)
			{
				::Sleep(1);
				continue;
			}
			return FALSE;
		}

		SQLRowCount(this->hStmt,&this->AffectCount);
		SQLNumResultCols(this->hStmt,&this->nCol);

		if(nCol > MAXCOL) 
		{
			return FALSE;
		}

		if(nCol == 0) 
		{
			this->Clear();
			return TRUE;
		}

		for(c=0;c<nCol;c++) 
		{
			SQLBindCol(hStmt,c+1,SQL_C_CHAR,Col[c],255,&lCol[c]);
			SQLDescribeCol(hStmt,c+1,ColName[c],30,NULL,NULL,NULL,NULL,NULL);
		}
		return TRUE;
	}
}

long CQuery::GetAffectCount()
{
	return this->AffectCount;
}