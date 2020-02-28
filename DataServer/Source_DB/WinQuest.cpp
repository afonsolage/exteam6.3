#include "stdafx.h"
#include "WinQuest.h"
#include "winutil.h"
#include "MainFrm.h"
// -----------------------------------------------------------------

cWinQuest::cWinQuest()
{
	// ----
}
// -----------------------------------------------------------------

cWinQuest::~cWinQuest()
{
	// ----
}
// -----------------------------------------------------------------

bool cWinQuest::Connect()
{
	#if(BYNARY_WINQUEST)
	return this->ConnectEx();
	#else
	return CDBConBase::Connect(szDbConnectID, szDbConnectPass);
	#endif
}
// -----------------------------------------------------------------

void cWinQuest::GetMemberInfo(GDSelectQuest *Recv, int aIndex)
{
	#if(BYNARY_WINQUEST)

	GetMemberInfoEx(Recv, aIndex);

	#else

	CString Query;
	// ----
	Query.Format("SELECT * FROM WinQuest WHERE Name = '%s'", Recv->Name);
	// ----
	if( !m_DBQuery.Exec(Query) || m_DBQuery.Fetch() == SQL_NO_DATA )
	{
		m_DBQuery.Clear();
		// ----
		LogAddC(LOGC_RED,"[%s] Failed to select values [Next: INSERT]", __FUNCTION__);
		// ----
		CString InsertQuery;

#ifdef UPGRADE_QUEST

		char SQLCode[5120] = "INSERT INTO WinQuest (Name, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10,";

		strcat(SQLCode,"N1, N2, N3, N4, N5, N6, N7, N8, N9, N10,");

		strcat(SQLCode,"C11, C12, C13, C14, C15,");
		strcat(SQLCode,"C21, C22, C23, C24, C25,");
		strcat(SQLCode,"C31, C32, C33, C34, C35,");
		strcat(SQLCode,"C41, C42, C43, C44, C45,");
		strcat(SQLCode,"C51, C52, C53, C54, C55,");
		strcat(SQLCode,"C61, C62, C63, C64, C65,");
		strcat(SQLCode,"C71, C72, C73, C74, C75,");
		strcat(SQLCode,"C81, C82, C83, C84, C85,");
		strcat(SQLCode,"C91, C92, C93, C94, C95,");
		strcat(SQLCode,"C101, C102, C103, C104, C105,");//71

		strcat(SQLCode,"Damage,");
		strcat(SQLCode,"Defence,");
		strcat(SQLCode,"Life,");
		strcat(SQLCode,"SD,");
		strcat(SQLCode,"Crit,");
		strcat(SQLCode,"Exel,");
		strcat(SQLCode,"DD,");
		strcat(SQLCode,"Ignore,");
		strcat(SQLCode,"Ref,");
		strcat(SQLCode,"Exp,");
		strcat(SQLCode,"Dr)");	//82-1

		strcat(SQLCode,"VALUES ('%s'");

		for(int b=0;b<81;b++)
			strcat(SQLCode,",0");

			strcat(SQLCode,");");

		InsertQuery.Format(SQLCode, Recv->Name);

#else

		// ----

		char SQLCode[5120] = "INSERT INTO WinQuest (Name, Start1, Start2, Start3, Start4, Start5, Start6, Start7, Start8, Start9, Start10,";

		strcat(SQLCode,"Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num10,");

		strcat(SQLCode,"Count11, Count12, Count13, Count14, Count15,");
		strcat(SQLCode,"Count21, Count22, Count23, Count24, Count25,");
		strcat(SQLCode,"Count31, Count32, Count33, Count34, Count35,");
		strcat(SQLCode,"Count41, Count42, Count43, Count44, Count45,");
		strcat(SQLCode,"Count51, Count52, Count53, Count54, Count55,");
		strcat(SQLCode,"Count61, Count62, Count63, Count64, Count65,");
		strcat(SQLCode,"Count71, Count72, Count73, Count74, Count75,");
		strcat(SQLCode,"Count81, Count82, Count83, Count84, Count85,");
		strcat(SQLCode,"Count91, Count92, Count93, Count94, Count95,");
		strcat(SQLCode,"Count101, Count102, Count103, Count104, Count105,");//71

		strcat(SQLCode,"Damage,");
		strcat(SQLCode,"Defence,");
		strcat(SQLCode,"Life,");
		strcat(SQLCode,"SD,");
		strcat(SQLCode,"Crit,");
		strcat(SQLCode,"Exel,");
		strcat(SQLCode,"DD,");
		strcat(SQLCode,"Ignore,");
		strcat(SQLCode,"Ref,");
		strcat(SQLCode,"Exp,");
		strcat(SQLCode,"Dr)");	//82-1

		strcat(SQLCode,"VALUES ('%s'");

		for(int b=0;b<81;b++)
			strcat(SQLCode,",0");

			strcat(SQLCode,");");

		InsertQuery.Format(SQLCode, Recv->Name);

#endif

		// ----
		if( !m_DBQuery.Exec(InsertQuery) )
		{
			LogAddC(LOGC_RED,"[%s] Failed to insert new values", __FUNCTION__);
			// ----
			m_DBQuery.Clear();
			return;
		}
		// ----
		m_DBQuery.Clear();


		DGQuestUserInfo Data;
		ZeroMemory(&Data,sizeof(Data));
		Data.h.set((LPBYTE)&Data, 0xE2, 0x01, sizeof(DGQuestUserInfo));

		strncpy(Data.Name,Recv->Name,10);
		Data.aIndex = Recv->aIndex;

		wsjServer.DataSend(aIndex, (char*)&Data, sizeof(DGQuestUserInfo));

	}
	else
	{
		//Packet s Infoi

		DGQuestUserInfo Data;

		ZeroMemory(&Data,sizeof(Data));
		Data.h.set((LPBYTE)&Data, 0xE2, 0x01, sizeof(DGQuestUserInfo));

#ifdef UPGRADE_QUEST

		Data.Start[0] = m_DBQuery.GetInt("S1");
		Data.Start[1] = m_DBQuery.GetInt("S2");
		Data.Start[2] = m_DBQuery.GetInt("S3");
		Data.Start[3] = m_DBQuery.GetInt("S4");
		Data.Start[4] = m_DBQuery.GetInt("S5");
		Data.Start[5] = m_DBQuery.GetInt("S6");
		Data.Start[6] = m_DBQuery.GetInt("S7");
		Data.Start[7] = m_DBQuery.GetInt("S8");
		Data.Start[8] = m_DBQuery.GetInt("S9");
		Data.Start[9] = m_DBQuery.GetInt("S10");

		Data.Num[0] = m_DBQuery.GetInt("N1");
		Data.Num[1] = m_DBQuery.GetInt("N2");
		Data.Num[2] = m_DBQuery.GetInt("N3");
		Data.Num[3] = m_DBQuery.GetInt("N4");
		Data.Num[4] = m_DBQuery.GetInt("N5");
		Data.Num[5] = m_DBQuery.GetInt("N6");
		Data.Num[6] = m_DBQuery.GetInt("N7");
		Data.Num[7] = m_DBQuery.GetInt("N8");
		Data.Num[8] = m_DBQuery.GetInt("N9");
		Data.Num[9] = m_DBQuery.GetInt("N10");

		Data.Count[0][0] = m_DBQuery.GetInt("C11");
		Data.Count[0][1] = m_DBQuery.GetInt("C12");
		Data.Count[0][2] = m_DBQuery.GetInt("C13");
		Data.Count[0][3] = m_DBQuery.GetInt("C14");
		Data.Count[0][4] = m_DBQuery.GetInt("C15");

		Data.Count[1][0] = m_DBQuery.GetInt("C21");
		Data.Count[1][1] = m_DBQuery.GetInt("C22");
		Data.Count[1][2] = m_DBQuery.GetInt("C23");
		Data.Count[1][3] = m_DBQuery.GetInt("C24");
		Data.Count[1][4] = m_DBQuery.GetInt("C25");

		Data.Count[2][0] = m_DBQuery.GetInt("C31");
		Data.Count[2][1] = m_DBQuery.GetInt("C32");
		Data.Count[2][2] = m_DBQuery.GetInt("C33");
		Data.Count[2][3] = m_DBQuery.GetInt("C34");
		Data.Count[2][4] = m_DBQuery.GetInt("C35");

		Data.Count[3][0] = m_DBQuery.GetInt("C41");
		Data.Count[3][1] = m_DBQuery.GetInt("C42");
		Data.Count[3][2] = m_DBQuery.GetInt("C43");
		Data.Count[3][3] = m_DBQuery.GetInt("C44");
		Data.Count[3][4] = m_DBQuery.GetInt("C45");

		Data.Count[4][0] = m_DBQuery.GetInt("C51");
		Data.Count[4][1] = m_DBQuery.GetInt("C52");
		Data.Count[4][2] = m_DBQuery.GetInt("C53");
		Data.Count[4][3] = m_DBQuery.GetInt("C54");
		Data.Count[4][4] = m_DBQuery.GetInt("C55");

		Data.Count[5][0] = m_DBQuery.GetInt("C61");
		Data.Count[5][1] = m_DBQuery.GetInt("C62");
		Data.Count[5][2] = m_DBQuery.GetInt("C63");
		Data.Count[5][3] = m_DBQuery.GetInt("C64");
		Data.Count[5][4] = m_DBQuery.GetInt("C65");

		Data.Count[6][0] = m_DBQuery.GetInt("C71");
		Data.Count[6][1] = m_DBQuery.GetInt("C72");
		Data.Count[6][2] = m_DBQuery.GetInt("C73");
		Data.Count[6][3] = m_DBQuery.GetInt("C74");
		Data.Count[6][4] = m_DBQuery.GetInt("C75");

		Data.Count[7][0] = m_DBQuery.GetInt("C81");
		Data.Count[7][1] = m_DBQuery.GetInt("C82");
		Data.Count[7][2] = m_DBQuery.GetInt("C83");
		Data.Count[7][3] = m_DBQuery.GetInt("C84");
		Data.Count[7][4] = m_DBQuery.GetInt("C85");

		Data.Count[8][0] = m_DBQuery.GetInt("C91");
		Data.Count[8][1] = m_DBQuery.GetInt("C92");
		Data.Count[8][2] = m_DBQuery.GetInt("C93");
		Data.Count[8][3] = m_DBQuery.GetInt("C94");
		Data.Count[8][4] = m_DBQuery.GetInt("C95");

		Data.Count[9][0] = m_DBQuery.GetInt("C101");
		Data.Count[9][1] = m_DBQuery.GetInt("C102");
		Data.Count[9][2] = m_DBQuery.GetInt("C103");
		Data.Count[9][3] = m_DBQuery.GetInt("C104");
		Data.Count[9][4] = m_DBQuery.GetInt("C105");

		Data.Damage = m_DBQuery.GetInt("Damage");	
		Data.Defence = m_DBQuery.GetInt("Defence");	
		Data.Life = m_DBQuery.GetInt("Life");	
		Data.SD = m_DBQuery.GetInt("SD");	
		Data.Crit = m_DBQuery.GetInt("Crit");
		Data.Exel = m_DBQuery.GetInt("Exel");
		Data.Double = m_DBQuery.GetInt("DD");
		Data.Ignore = m_DBQuery.GetInt("Ignore");
		Data.Ref = m_DBQuery.GetInt("Ref");	
		Data.Exp = m_DBQuery.GetInt("Exp");
		Data.Drop = m_DBQuery.GetInt("Dr");	

		strncpy(Data.Name,Recv->Name,10);
		Data.aIndex = Recv->aIndex;

#else

		Data.Start[0] = m_DBQuery.GetInt("Start1");
		Data.Start[1] = m_DBQuery.GetInt("Start2");
		Data.Start[2] = m_DBQuery.GetInt("Start3");
		Data.Start[3] = m_DBQuery.GetInt("Start4");
		Data.Start[4] = m_DBQuery.GetInt("Start5");
		Data.Start[5] = m_DBQuery.GetInt("Start6");
		Data.Start[6] = m_DBQuery.GetInt("Start7");
		Data.Start[7] = m_DBQuery.GetInt("Start8");
		Data.Start[8] = m_DBQuery.GetInt("Start9");
		Data.Start[9] = m_DBQuery.GetInt("Start10");

		Data.Num[0] = m_DBQuery.GetInt("Num1");
		Data.Num[1] = m_DBQuery.GetInt("Num2");
		Data.Num[2] = m_DBQuery.GetInt("Num3");
		Data.Num[3] = m_DBQuery.GetInt("Num4");
		Data.Num[4] = m_DBQuery.GetInt("Num5");
		Data.Num[5] = m_DBQuery.GetInt("Num6");
		Data.Num[6] = m_DBQuery.GetInt("Num7");
		Data.Num[7] = m_DBQuery.GetInt("Num8");
		Data.Num[8] = m_DBQuery.GetInt("Num9");
		Data.Num[9] = m_DBQuery.GetInt("Num10");

		Data.Count[0][0] = m_DBQuery.GetInt("Count11");
		Data.Count[0][1] = m_DBQuery.GetInt("Count12");
		Data.Count[0][2] = m_DBQuery.GetInt("Count13");
		Data.Count[0][3] = m_DBQuery.GetInt("Count14");
		Data.Count[0][4] = m_DBQuery.GetInt("Count15");

		Data.Count[1][0] = m_DBQuery.GetInt("Count21");
		Data.Count[1][1] = m_DBQuery.GetInt("Count22");
		Data.Count[1][2] = m_DBQuery.GetInt("Count23");
		Data.Count[1][3] = m_DBQuery.GetInt("Count24");
		Data.Count[1][4] = m_DBQuery.GetInt("Count25");

		Data.Count[2][0] = m_DBQuery.GetInt("Count31");
		Data.Count[2][1] = m_DBQuery.GetInt("Count32");
		Data.Count[2][2] = m_DBQuery.GetInt("Count33");
		Data.Count[2][3] = m_DBQuery.GetInt("Count34");
		Data.Count[2][4] = m_DBQuery.GetInt("Count35");

		Data.Count[3][0] = m_DBQuery.GetInt("Count41");
		Data.Count[3][1] = m_DBQuery.GetInt("Count42");
		Data.Count[3][2] = m_DBQuery.GetInt("Count43");
		Data.Count[3][3] = m_DBQuery.GetInt("Count44");
		Data.Count[3][4] = m_DBQuery.GetInt("Count45");

		Data.Count[4][0] = m_DBQuery.GetInt("Count51");
		Data.Count[4][1] = m_DBQuery.GetInt("Count52");
		Data.Count[4][2] = m_DBQuery.GetInt("Count53");
		Data.Count[4][3] = m_DBQuery.GetInt("Count54");
		Data.Count[4][4] = m_DBQuery.GetInt("Count55");

		Data.Count[5][0] = m_DBQuery.GetInt("Count61");
		Data.Count[5][1] = m_DBQuery.GetInt("Count62");
		Data.Count[5][2] = m_DBQuery.GetInt("Count63");
		Data.Count[5][3] = m_DBQuery.GetInt("Count64");
		Data.Count[5][4] = m_DBQuery.GetInt("Count65");

		Data.Count[6][0] = m_DBQuery.GetInt("Count71");
		Data.Count[6][1] = m_DBQuery.GetInt("Count72");
		Data.Count[6][2] = m_DBQuery.GetInt("Count73");
		Data.Count[6][3] = m_DBQuery.GetInt("Count74");
		Data.Count[6][4] = m_DBQuery.GetInt("Count75");

		Data.Count[7][0] = m_DBQuery.GetInt("Count81");
		Data.Count[7][1] = m_DBQuery.GetInt("Count82");
		Data.Count[7][2] = m_DBQuery.GetInt("Count83");
		Data.Count[7][3] = m_DBQuery.GetInt("Count84");
		Data.Count[7][4] = m_DBQuery.GetInt("Count85");

		Data.Count[8][0] = m_DBQuery.GetInt("Count91");
		Data.Count[8][1] = m_DBQuery.GetInt("Count92");
		Data.Count[8][2] = m_DBQuery.GetInt("Count93");
		Data.Count[8][3] = m_DBQuery.GetInt("Count94");
		Data.Count[8][4] = m_DBQuery.GetInt("Count95");

		Data.Count[9][0] = m_DBQuery.GetInt("Count101");
		Data.Count[9][1] = m_DBQuery.GetInt("Count102");
		Data.Count[9][2] = m_DBQuery.GetInt("Count103");
		Data.Count[9][3] = m_DBQuery.GetInt("Count104");
		Data.Count[9][4] = m_DBQuery.GetInt("Count105");

		Data.Damage = m_DBQuery.GetInt("Damage");	
		Data.Defence = m_DBQuery.GetInt("Defence");
		Data.Life = m_DBQuery.GetInt("Life");	
		Data.SD = m_DBQuery.GetInt("SD");	
		Data.Crit = m_DBQuery.GetInt("Crit");	
		Data.Exel = m_DBQuery.GetInt("Exel");	
		Data.Double = m_DBQuery.GetInt("DD");	
		Data.Ignore = m_DBQuery.GetInt("Ignore");	
		Data.Ref = m_DBQuery.GetInt("Ref");	
		Data.Exp = m_DBQuery.GetInt("Exp");	
		Data.Drop = m_DBQuery.GetInt("Dr");	

		strncpy(Data.Name,Recv->Name,10);
		Data.aIndex = Recv->aIndex;

#endif

		// ----

		m_DBQuery.Clear();

		wsjServer.DataSend(aIndex, (char*)&Data, sizeof(DGQuestUserInfo));
	}

	// ----

	return;

	#endif
}
// -----------------------------------------------------------------

void cWinQuest::UpdateMemberInfo(GDQuestUser *Recv)
{
	#if(BYNARY_WINQUEST)

	UpdateMemberInfoEx(Recv);

	#else

	bool ResultCheck = true;
	// ----
	CString Query;

#ifdef UPGRADE_QUEST

		char SQLCode[5120] = "UPDATE WinQuest SET S1 = %d, S2 = %d, S3 = %d, S4 = %d, S5 = %d, S6 = %d, S7 = %d, S8 = %d, S9 = %d, S10 = %d,";

		strcat(SQLCode,"N1 = %d, N2 = %d, N3 = %d, N4 = %d, N5 = %d, N6 = %d, N7 = %d, N8 = %d, N9 = %d, N10 = %d,");

		strcat(SQLCode,"C11 = %d, C12 = %d, C13 = %d, C14 = %d, C15 = %d,");
		strcat(SQLCode,"C21 = %d, C22 = %d, C23 = %d, C24 = %d, C25 = %d,");
		strcat(SQLCode,"C31 = %d, C32 = %d, C33 = %d, C34 = %d, C35 = %d,");
		strcat(SQLCode,"C41 = %d, C42 = %d, C43 = %d, C44 = %d, C45 = %d,");
		strcat(SQLCode,"C51 = %d, C52 = %d, C53 = %d, C54 = %d, C55 = %d,");
		strcat(SQLCode,"C61 = %d, C62 = %d, C63 = %d, C64 = %d, C65 = %d,");
		strcat(SQLCode,"C71 = %d, C72 = %d, C73 = %d, C74 = %d, C75 = %d,");
		strcat(SQLCode,"C81 = %d, C82 = %d, C83 = %d, C84 = %d, C85 = %d,");
		strcat(SQLCode,"C91 = %d, C92 = %d, C93 = %d, C94 = %d, C95 = %d,");
		strcat(SQLCode,"C101 = %d,C102= %d, C103= %d, C104 =%d, C105 = %d,");

		strcat(SQLCode,"Damage = %d,");
		strcat(SQLCode,"Defence = %d,");
		strcat(SQLCode,"Life = %d,");
		strcat(SQLCode,"SD = %d,");
		strcat(SQLCode,"Crit = %d,");
		strcat(SQLCode,"Exel = %d,");
		strcat(SQLCode,"DD = %d,");
		strcat(SQLCode,"Ignore = %d,");
		strcat(SQLCode,"Ref = %d,");
		strcat(SQLCode,"Exp = %d,");
		strcat(SQLCode,"Dr = %d");

		strcat(SQLCode," WHERE Name = '%s'");

#else
		char SQLCode[5120] = "UPDATE WinQuest SET Start1 = %d, Start2 = %d, Start3 = %d, Start4 = %d, Start5 = %d, Start6 = %d, Start7 = %d, Start8 = %d, Start9 = %d, Start10 = %d,";

		strcat(SQLCode,"Num1 = %d, Num2 = %d, Num3 = %d, Num4 = %d, Num5 = %d, Num6 = %d, Num7 = %d, Num8 = %d, Num9 = %d, Num10 = %d,");

		strcat(SQLCode,"Count11 = %d, Count12 = %d, Count13 = %d, Count14 = %d, Count15 = %d,");
		strcat(SQLCode,"Count21 = %d, Count22 = %d, Count23 = %d, Count24 = %d, Count25 = %d,");
		strcat(SQLCode,"Count31 = %d, Count32 = %d, Count33 = %d, Count34 = %d, Count35 = %d,");
		strcat(SQLCode,"Count41 = %d, Count42 = %d, Count43 = %d, Count44 = %d, Count45 = %d,");
		strcat(SQLCode,"Count51 = %d, Count52 = %d, Count53 = %d, Count54 = %d, Count55 = %d,");
		strcat(SQLCode,"Count61 = %d, Count62 = %d, Count63 = %d, Count64 = %d, Count65 = %d,");
		strcat(SQLCode,"Count71 = %d, Count72 = %d, Count73 = %d, Count74 = %d, Count75 = %d,");
		strcat(SQLCode,"Count81 = %d, Count82 = %d, Count83 = %d, Count84 = %d, Count85 = %d,");
		strcat(SQLCode,"Count91 = %d, Count92 = %d, Count93 = %d, Count94 = %d, Count95 = %d,");
		strcat(SQLCode,"Count101 = %d, Count102 = %d, Count103 = %d, Count104 = %d, Count105 = %d,");

		strcat(SQLCode,"Damage = %d,");
		strcat(SQLCode,"Defence = %d,");
		strcat(SQLCode,"Life = %d,");
		strcat(SQLCode,"SD = %d,");
		strcat(SQLCode,"Crit = %d,");
		strcat(SQLCode,"Exel = %d,");
		strcat(SQLCode,"DD = %d,");
		strcat(SQLCode,"Ignore = %d,");
		strcat(SQLCode,"Ref = %d,");
		strcat(SQLCode,"Exp = %d,");
		strcat(SQLCode,"Dr = %d");

		strcat(SQLCode," WHERE Name = '%s'");
#endif

		Query.Format(SQLCode,
			Recv->Start[0],Recv->Start[1],Recv->Start[2],Recv->Start[3],Recv->Start[4],Recv->Start[5],Recv->Start[6],Recv->Start[7],Recv->Start[8],Recv->Start[9],
			Recv->Num[0],Recv->Num[1],Recv->Num[2],Recv->Num[3],Recv->Num[4],Recv->Num[5],Recv->Num[6],Recv->Num[7],Recv->Num[8],Recv->Num[9],

			Recv->Count[0][0],Recv->Count[0][1],Recv->Count[0][2],Recv->Count[0][3],Recv->Count[0][4],
			Recv->Count[1][0],Recv->Count[1][1],Recv->Count[1][2],Recv->Count[1][3],Recv->Count[1][4],
			Recv->Count[2][0],Recv->Count[2][1],Recv->Count[2][2],Recv->Count[2][3],Recv->Count[2][4],
			Recv->Count[3][0],Recv->Count[3][1],Recv->Count[3][2],Recv->Count[3][3],Recv->Count[3][4],
			Recv->Count[4][0],Recv->Count[4][1],Recv->Count[4][2],Recv->Count[4][3],Recv->Count[4][4],
			Recv->Count[5][0],Recv->Count[5][1],Recv->Count[5][2],Recv->Count[5][3],Recv->Count[5][4],
			Recv->Count[6][0],Recv->Count[6][1],Recv->Count[6][2],Recv->Count[6][3],Recv->Count[6][4],
			Recv->Count[7][0],Recv->Count[7][1],Recv->Count[7][2],Recv->Count[7][3],Recv->Count[7][4],
			Recv->Count[8][0],Recv->Count[8][1],Recv->Count[8][2],Recv->Count[8][3],Recv->Count[8][4],
			Recv->Count[9][0],Recv->Count[9][1],Recv->Count[9][2],Recv->Count[9][3],Recv->Count[9][4],

			Recv->Damage,
			Recv->Defence,
			Recv->Life,
			Recv->SD,
			Recv->Crit,
			Recv->Exel,
			Recv->Double,
			Recv->Ignore,
			Recv->Ref,
			Recv->Exp,
			Recv->Drop,

			Recv->Name
			);
	// ----
	if( !m_DBQuery.Exec(Query) )
	{
		ResultCheck = false;
	}
	// ----
	m_DBQuery.Clear();
	// ----
	return ;

	#endif
}

#if(BYNARY_WINQUEST)

bool cWinQuest::ConnectEx()
{
	bool Result = this->m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);

	if(Result)
	{
		//this->CreateTable();
	}

	return Result;
}

void cWinQuest::GetMemberInfoEx(GDSelectQuest *Recv, int aIndex)
{
	char szQuery[256];
	BYTE btBynaryQuest[MAX_BYNARYQUEST];
	int iDataSize = 0;
	char szName[11];

	DGQuestUserInfo Data;
	ZeroMemory(&Data,sizeof(Data));
	Data.h.set((LPBYTE)&Data, 0xE2, 0x01, sizeof(DGQuestUserInfo));

	memcpy(szName, Recv->Name, sizeof(szName)-1);
	szName[10] = 0;

	strncpy(Data.Name,szName,10);
	Data.aIndex = Recv->aIndex;

	sprintf(szQuery, "EXEC WINQUEST_LOAD '%s'", szName);

	if(this->m_DBQuery.Exec(szQuery) == FALSE || this->m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		this->m_DBQuery.Clear();
	}	
	else
	{
		Data.Damage = this->m_DBQuery.GetInt("Damage");	
		Data.Defence = this->m_DBQuery.GetInt("Defence");	
		Data.Life = this->m_DBQuery.GetInt("Life");	
		Data.SD = this->m_DBQuery.GetInt("SD");	
		Data.Crit = this->m_DBQuery.GetInt("Crit");
		Data.Exel = this->m_DBQuery.GetInt("Exel");
		Data.Double = this->m_DBQuery.GetInt("DD");
		Data.Ignore = this->m_DBQuery.GetInt("Ignore");
		Data.Ref = this->m_DBQuery.GetInt("Ref");	
		Data.Exp = this->m_DBQuery.GetInt("Exp");
		Data.Drop = this->m_DBQuery.GetInt("Dr");	

		this->m_DBQuery.Clear();

		sprintf(szQuery, "SELECT Quest FROM WinQuest WHERE Name = '%s'", szName);

		int nRet = this->m_DBQuery.ReadBlob(szQuery, btBynaryQuest);

		if(nRet == 0)
		{
			for(int n = 0; n < MAX_BYNARYQUEST; n++)
			{
				btBynaryQuest[n] = 0x00;
			}
		}
		
		for(int i = 0; i < 10; i++)
		{
			iDataSize = this->bynary_int((int&)Data.Start[i], iDataSize, btBynaryQuest);
		}

		for(int i = 0; i < 10; i++)
		{
			iDataSize = this->bynary_int((int&)Data.Num[i], iDataSize, btBynaryQuest);
		}

		for(int i = 0; i < 10; i++)
		{
			for(int n = 0; n < 5; n++)
			{
				iDataSize = this->bynary_int((int&)Data.Count[i][n], iDataSize, btBynaryQuest);
			}
		}

		this->m_DBQuery.Clear();
	}

	wsjServer.DataSend(aIndex, (char*)&Data, sizeof(DGQuestUserInfo));
}

void cWinQuest::UpdateMemberInfoEx(GDQuestUser *Recv)
{
	char szQuesry[256];
	BYTE btBynaryQuest[MAX_BYNARYQUEST];
	int iDataSize = 0;
	char szName[11];

	memcpy(szName, Recv->Name, sizeof(szName)-1);
	szName[10] = 0;

	sprintf(szQuesry, "EXEC WINQUEST_SAVE '%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
			szName,Recv->Damage,Recv->Defence,Recv->Life,Recv->SD,Recv->Crit,
			Recv->Exel,Recv->Double,Recv->Ignore,Recv->Ref,Recv->Exp,Recv->Drop);

	this->m_DBQuery.Exec(szQuesry);
	this->m_DBQuery.Clear();

	for(int i = 0; i < 10; i++)
	{
		iDataSize = this->int_binary(Recv->Start[i], iDataSize, btBynaryQuest);
	}

	for(int i = 0; i < 10; i++)
	{
		iDataSize = this->int_binary(Recv->Num[i], iDataSize, btBynaryQuest);
	}

	for(int i = 0; i < 10; i++)
	{
		for(int n = 0; n < 5; n++)
		{
			iDataSize = this->int_binary(Recv->Count[i][n], iDataSize, btBynaryQuest);
		}
	}

	sprintf(szQuesry, "UPDATE WinQuest SET Quest=? WHERE Name='%s'", szName);
	this->m_DBQuery.WriteBlob(szQuesry, btBynaryQuest, MAX_BYNARYQUEST);
	this->m_DBQuery.Clear();
}

int cWinQuest::int_binary(int a, int b, LPBYTE buf)
{
	WORD hiWord = SET_NUMBERHW(a);
	WORD loWord = SET_NUMBERLW(a);
	buf[b] = SET_NUMBERH(hiWord);
	b++;
	buf[b] = SET_NUMBERL(hiWord);
	b++;
	buf[b] = SET_NUMBERH(loWord);
	b++;
	buf[b] = SET_NUMBERL(loWord);
	b++;
	return b;
}

int cWinQuest::bynary_int(int& a, int b, LPBYTE buf)
{
	a = 0;
	WORD hiword = MAKE_NUMBERW(buf[b], buf[b+1]);
	WORD loword = MAKE_NUMBERW(buf[b+2], buf[b+3]);
	a = MAKE_NUMBERDW(hiword, loword);
	return b+4;
}
#endif