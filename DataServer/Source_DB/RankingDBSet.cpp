#include "StdAfx.h"
#include "winutil.h"
#include "MainFrm.h"
#include "RankingDBSet.h"

cRanking::cRanking()
{
}

cRanking::~cRanking()
{
}

bool cRanking::Connect()
{
	return CDBConBase::Connect(szDbConnectID, szDbConnectPass);
}

void cRanking::CharacterRanking(int pIndex)
{
	int iReturnCode = 0;
	int iCharCount = 0;

	CString Query;

	DGCharTop rSend;
	ZeroMemory(&rSend,sizeof(rSend));
	PHeadSubSetW((LPBYTE)&rSend, 0xE3, 0, sizeof(DGCharTop));

	if(m_DBQuery.Exec("EXEC EX_RANKING1") == FALSE)
	{
		m_DBQuery.Clear();
		return;
	}

	short i = m_DBQuery.Fetch();

	while(i != SQL_NO_DATA && i != SQL_NULL_DATA)
	{
		iReturnCode = m_DBQuery.GetInt(1);

		if(iReturnCode < 0)
		{
			break;
		}

		char NickName[11];
		NickName[10] = 0;
		m_DBQuery.GetStr("Name", NickName);

		strncpy(rSend.tp[iCharCount].Name,NickName,10);
		rSend.tp[iCharCount].Class = m_DBQuery.GetInt("Class");
		rSend.tp[iCharCount].level = m_DBQuery.GetInt("cLevel");
		rSend.tp[iCharCount].Reset = m_DBQuery.GetInt("Resets");
		rSend.tp[iCharCount].Grand = m_DBQuery.GetInt("gr_res");
		rSend.tp[iCharCount].Str = m_DBQuery.GetInt("Strength");
		rSend.tp[iCharCount].Agi = m_DBQuery.GetInt("Dexterity");
		rSend.tp[iCharCount].Vit = m_DBQuery.GetInt("Vitality");
		rSend.tp[iCharCount].Ene = m_DBQuery.GetInt("Energy");
		rSend.tp[iCharCount].Cmd = m_DBQuery.GetInt("Leadership");
		rSend.tp[iCharCount].Premium = m_DBQuery.GetInt("PremiumTime");
		rSend.tp[iCharCount].ShowRanking = m_DBQuery.GetInt("show_ranking");

		iCharCount++;

		if(iCharCount >= MAXTOP)
		{
			break;
		}

		i = m_DBQuery.Fetch();
	}
	m_DBQuery.Clear();

	// ----

	for(int b = 0; b<iCharCount; b++ )
	{
		char cName[11];
		cName[10] = 0;
		strncpy(cName,rSend.tp[b].Name,10);

		Query.Format("EXEC EX_RANKING2 '%s'", cName);
		if(m_DBQuery.Exec(Query) == FALSE )
		{
			m_DBQuery.Clear();
			continue;
		}

		if(m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			m_DBQuery.Clear();
			continue;
		}

		char GuildName[9];
		GuildName[8] = 0;
		m_DBQuery.GetStr("G_Name", GuildName);
		strncpy(rSend.tp[b].Guild,GuildName,8);

		m_DBQuery.Clear();

		Sleep(10);
	}

	wsjServer.DataSend(pIndex, (char*)&rSend, sizeof(DGCharTop));
}

void cRanking::RecvBrother(GD_CheckBrother* Recv, int pIndex)
{
	CString Query;

	int iReturnCode = 0;
	int Count = 0;
	char szBuffer[11] = { 0 };

	strncpy(szBuffer,Recv->BrName,10);

	Query.Format("SELECT Name FROM Character WHERE Brother = '%s'",szBuffer);

	if( m_DBQuery.Exec(Query) == FALSE)
	{
		m_DBQuery.Clear();
	}

	short i = m_DBQuery.Fetch();

	while(i != SQL_NO_DATA && i != SQL_NULL_DATA)
	{
		iReturnCode = m_DBQuery.GetInt(1);

		if(iReturnCode < 0)
		{
			break;
		}

		Count++;

		i = m_DBQuery.Fetch();
	}

	m_DBQuery.Clear();

	DG_CheckBrother rSend;
	rSend.h.c = PMHC_BYTE;
	rSend.h.headcode = 0xE2;
	rSend.h.subcode = 0x02;
	rSend.h.size = sizeof(DG_CheckBrother);
	rSend.Count = Count;
	rSend.aIndex = Recv->aIndex;
	rSend.aTargetIndex = Recv->aTargetIndex;
	wsjServer.DataSend(pIndex, (char*)&rSend, sizeof(DG_CheckBrother));
}