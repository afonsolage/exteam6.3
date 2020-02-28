#include "stdafx.h"
#include "ImperialBattleOfKato.h"
#include "ImperialBattleUserMng.h"
#include "TMonsterAIGroup.h"
#include "user.h"
#include "protocol.h"
#include "logproc.h"
#include "..\include\prodef.h"
#include "..\common\winutil.h"
#include "BloodCastle.h"
#include "TNotice.h"
CImperialBattleOfKato::CImperialBattleOfKato()
{
	this->ResetData();
}

CImperialBattleOfKato::~CImperialBattleOfKato()
{
}

void CImperialBattleOfKato::ResetData()
{
	this->m_BattleData.Reset();
}

void CImperialBattleOfKato::SetState(int iState)
{
	switch ( iState )
	{
		case 0:
			this->SetState_NONE();
			break;
		case 1:
			this->SetState_STANDBY1();
			break;
		case 2:
			this->SetState_PHAZE1();
			break;
		case 3:
			this->SetState_STANDBY2();
			break;
		case 4:
			this->SetState_PHAZE2();
			break;
		case 5: 
			this->SetState_STANDBY3();
			break;
		case 6:
			this->SetState_PHAZE3();
			break;
		case 7:
			this->SetState_END();
			break;
	}
}

void CImperialBattleOfKato::SetState_NONE()
{
	LogAddC(2, "[ IMPERIAL FORT ] [ BattleOfKato ] State(%d) -> NONE", this->m_BattleData.CurrentState);
	this->ResetData();
	TMonsterAIGroup::DelGroupInstance(30);
	TMonsterAIGroup::DelGroupInstance(31);
	TMonsterAIGroup::DelGroupInstance(32);
	this->m_BattleData.CurrentState = BATTLEOFKATO_STATE_NONE;
}


void CImperialBattleOfKato::SetState_STANDBY1()
{
	LogAddC(2, "[ IMPERIAL FORT ] [ BattleOfKato ] State(%d) -> STANDBY1", this->m_BattleData.CurrentState);
	for(int i=0;i<7;++i)
	{
		this->m_BattleData.GateIndex[i] = gObjAddMonster(71);
		if(this->m_BattleData.GateIndex[i] >= 0)
		{
			gObj[this->m_BattleData.GateIndex[i]].MapNumber = 71;
			gObj[this->m_BattleData.GateIndex[i]].X = g_KatoGate[i].X;
			gObj[this->m_BattleData.GateIndex[i]].Y = g_KatoGate[i].Y;
			gObj[this->m_BattleData.GateIndex[i]].Dir = g_KatoGate[i].Dir;
			gObj[this->m_BattleData.GateIndex[i]].TX = g_KatoGate[i].X;
			gObj[this->m_BattleData.GateIndex[i]].TY = g_KatoGate[i].Y;
			gObj[this->m_BattleData.GateIndex[i]].StartX = g_KatoGate[i].X;
			gObj[this->m_BattleData.GateIndex[i]].StartY = g_KatoGate[i].Y;
			gObj[this->m_BattleData.GateIndex[i]].m_OldX = g_KatoGate[i].X;
			gObj[this->m_BattleData.GateIndex[i]].m_OldY = g_KatoGate[i].Y;
			gObjSetMonster(this->m_BattleData.GateIndex[i], g_KatoGate[i].Class);
			gObj[this->m_BattleData.GateIndex[i]].m_ImmuneToHarmCount = 3600; // IMMUNITY FOR GATES
			gObj[this->m_BattleData.GateIndex[i]].m_ImmuneToMagicCount = 3600; // IMMUNITY FOR GATES

			LogAddTD("[ IMPERIAL FORT ] [ BattleOfKato ] Create Gate Index: %d Class: %d",
				this->m_BattleData.GateIndex[i], g_KatoGate[i].Class);
		}
	}
	this->m_BattleData.Time = 60000;
	this->m_BattleData.TickCount = GetTickCount();
	TMonsterAIGroup::Init(30);
	this->m_BattleData.MonsterCount = 0;
	this->m_BattleData.CurrentAIGroup = 30;
	this->m_BattleData.CurrentState = BATTLEOFKATO_STATE_STANDBY1;
	this->SendEventState();
}

void CImperialBattleOfKato::SetState_STANDBY2()
{
	LogAddC(2, "[ IMPERIAL FORT ] [ BattleOfKato ] State(%d) -> STANDBY2", this->m_BattleData.CurrentState);
	this->m_BattleData.Time = 60000;
	this->m_BattleData.TickCount = GetTickCount();
	TMonsterAIGroup::DelGroupInstance(30);
	TMonsterAIGroup::Init(31);
	this->m_BattleData.MonsterCount = 0;
	this->m_BattleData.CurrentAIGroup = 31;
	this->m_BattleData.CurrentState = BATTLEOFKATO_STATE_STANDBY2;
	this->SendEventState();
}

void CImperialBattleOfKato::SetState_STANDBY3()
{
	LogAddC(2, "[ IMPERIAL FORT ] [ BattleOfKato ] State(%d) -> STANDBY3", this->m_BattleData.CurrentState);

	this->m_BattleData.Time = 60000;
	this->m_BattleData.TickCount = GetTickCount();
	TMonsterAIGroup::DelGroupInstance(31);
	TMonsterAIGroup::Init(32);
	this->m_BattleData.MonsterCount = 0;
	this->m_BattleData.CurrentLeaderIndex = TMonsterAIGroup::FindGroupLeader(32);
	LogAddTD("[ IMPERIAL FORT ] Create BOSS %s Index: %d", gObj[this->m_BattleData.CurrentLeaderIndex].Name, this->m_BattleData.CurrentLeaderIndex);
	this->m_BattleData.CurrentAIGroup = 32;
	this->m_BattleData.CurrentState = BATTLEOFKATO_STATE_STANDBY3;
	this->SendEventState();
}

void CImperialBattleOfKato::SetState_PHAZE1()
{
	LogAddC(2, "[ IMPERIAL FORT ] [ BattleOfKato ] State(%d) -> PHAZE1", this->m_BattleData.CurrentState);
	gObj[this->m_BattleData.GateIndex[0]].m_ImmuneToHarmCount = 0;
	gObj[this->m_BattleData.GateIndex[0]].m_ImmuneToMagicCount = 0; // REMOVE IMMUNITY
	this->m_BattleData.Time = 600000;
	this->m_BattleData.TickCount = GetTickCount();
	TMonsterAIGroup::ChangeAIOrder(30, 1);
	this->m_BattleData.MonsterCount = TMonsterAIGroup::s_iMonsterAIGroupMemberCount[27];
	this->m_BattleData.PhazeStep = 0;
	this->m_BattleData.NotifyCount = -1;
	PMSG_NOTICE pNotice;
	TNotice::MakeNoticeMsg(&pNotice, 0, "Quest Started!");
	this->SendImperialPlayers((LPBYTE)&pNotice, pNotice.h.size);
	this->m_BattleData.CurrentState = BATTLEOFKATO_STATE_PHAZE1;
}

void CImperialBattleOfKato::SetState_PHAZE2()
{
	LogAddC(2, "[ IMPERIAL FORT ] [ BattleOfKato ] State(%d) -> PHAZE2", this->m_BattleData.CurrentState);
	gObj[this->m_BattleData.GateIndex[3]].m_ImmuneToHarmCount = 0;
	gObj[this->m_BattleData.GateIndex[3]].m_ImmuneToMagicCount = 0; // REMOVE IMMUNITY
	this->m_BattleData.Time = 600000;
	this->m_BattleData.TickCount = GetTickCount();
	TMonsterAIGroup::ChangeAIOrder(31, 1);
	this->m_BattleData.MonsterCount = TMonsterAIGroup::s_iMonsterAIGroupMemberCount[28];
	this->m_BattleData.PhazeStep = 0;
	this->m_BattleData.NotifyCount = -1;
	PMSG_NOTICE pNotice;
	TNotice::MakeNoticeMsg(&pNotice, 0, "Quest Started!");
	this->SendImperialPlayers((LPBYTE)&pNotice, pNotice.h.size);
	this->m_BattleData.CurrentState = BATTLEOFKATO_STATE_PHAZE2;
}

void CImperialBattleOfKato::SetState_PHAZE3()
{
	LogAddC(2, "[ IMPERIAL FORT ] [ BattleOfKato ] State(%d) -> PHAZE3", this->m_BattleData.CurrentState);
	gObj[this->m_BattleData.GateIndex[6]].m_ImmuneToHarmCount = 0;
	gObj[this->m_BattleData.GateIndex[6]].m_ImmuneToMagicCount = 0; // REMOVE IMMUNITY
	this->m_BattleData.Time = 600000;
	this->m_BattleData.TickCount = GetTickCount();
	TMonsterAIGroup::ChangeAIOrder(32, 1);
	this->m_BattleData.MonsterCount = TMonsterAIGroup::s_iMonsterAIGroupMemberCount[29];
	this->m_BattleData.PhazeStep = 0;
	this->m_BattleData.NotifyCount = -1;
	PMSG_NOTICE pNotice;
	TNotice::MakeNoticeMsg(&pNotice, 0, "Quest Started!");
	this->SendImperialPlayers((LPBYTE)&pNotice, pNotice.h.size);
	this->m_BattleData.CurrentState = BATTLEOFKATO_STATE_PHAZE3;
}

void CImperialBattleOfKato::SetState_END()
{
	LogAddC(2, "[ IMPERIAL FORT ] [ BattleOfKato ] State(%d) -> END", this->m_BattleData.CurrentState);
	this->m_BattleData.CurrentState = BATTLEOFKATO_STATE_END;
	return;
}



void CImperialBattleOfKato::Run()
{
	switch ( this->m_BattleData.CurrentState )
	{
		case 0:
			return;
		case 1:
			this->ProcState_STANDBY1();
			break;
		case 2:
			this->ProcState_PHAZE1();
			break;
		case 3:
			this->ProcState_STANDBY2();
			break;
		case 4:
			this->ProcState_PHAZE2();
			break;
		case 5:
			this->ProcState_STANDBY3();
			break;
		case 6:
			this->ProcState_PHAZE3();
			break;
		case 7:
			this->ProcState_END();
			break;
	}
}

void CImperialBattleOfKato::ProcState_STANDBY1()
{
	int Tick = GetTickCount() - this->m_BattleData.TickCount;
	if(Tick >= 1000)
	{
		this->m_BattleData.Time -= Tick;
		this->m_BattleData.TickCount = GetTickCount();

		this->SendEventInterface();

		if(this->m_BattleData.Time <= 0)
		{
			this->SetState(BATTLEOFKATO_STATE_PHAZE1);
		}
	}
}

void CImperialBattleOfKato::ProcState_PHAZE1()
{
	int Tick = GetTickCount() - this->m_BattleData.TickCount;
	if(Tick >= 1000)
	{
		this->m_BattleData.Time -= Tick;
		this->m_BattleData.TickCount = GetTickCount();

		this->SendEventInterface();
		this->MonsterProc();

		for(int i=0;i<12;++i)
		{
			for(int n=0;n<g_ImperialBattleUserMng.GetUserCount();++n)
			{

				if(gObj[g_ImperialBattleUserMng.m_BattleUser[n].GetIndex()].X >= g_KatoTrap[i].X-5 && gObj[g_ImperialBattleUserMng.m_BattleUser[n].GetIndex()].X <= g_KatoTrap[i].X+5
					&& gObj[g_ImperialBattleUserMng.m_BattleUser[n].GetIndex()].Y >= g_KatoTrap[i].Y-5 && gObj[g_ImperialBattleUserMng.m_BattleUser[n].GetIndex()].Y <= g_KatoTrap[i].Y+5)
				{
					gObjAttack(&gObj[this->m_BattleData.TrapIndex], &gObj[g_ImperialBattleUserMng.m_BattleUser[n].GetIndex()], NULL, 0, 0, 0, 0,0,0);
				}
			}
		}

		if(this->m_BattleData.Time > 0 && (this->m_BattleData.Time/60000) !=this->m_BattleData.NotifyCount)
		{
			this->m_BattleData.NotifyCount = this->m_BattleData.Time / 60000;
			PMSG_NOTICE pNotice;
			TNotice::MakeNoticeMsgEx(&pNotice, 0, "Portal will be closed after %d minutes", this->m_BattleData.NotifyCount+1);
			this->SendImperialPlayers((LPBYTE)&pNotice, pNotice.h.size);
		}

		if(gObj[this->m_BattleData.GateIndex[0]].Live == false && this->m_BattleData.PhazeStep == 0)
		{
			this->SetMapAttr(0);
			this->m_BattleData.PhazeStep++;
		}

		if(this->m_BattleData.MonsterCount <= 0 && this->m_BattleData.PhazeStep == 1)
		{
			gObj[this->m_BattleData.GateIndex[1]].m_ImmuneToHarmCount = 0;
			gObj[this->m_BattleData.GateIndex[1]].m_ImmuneToMagicCount = 0;
			this->m_BattleData.PhazeStep++;
		}
		if(gObj[this->m_BattleData.GateIndex[1]].Live == false && this->m_BattleData.PhazeStep == 2)
		{
			gObj[this->m_BattleData.GateIndex[2]].m_ImmuneToHarmCount = 0;
			gObj[this->m_BattleData.GateIndex[2]].m_ImmuneToMagicCount = 0;
			this->SetMapAttr(1);
			this->m_BattleData.PhazeStep++;
		}
		if(gObj[this->m_BattleData.GateIndex[2]].Live == false && this->m_BattleData.PhazeStep == 3)
		{
			this->SetMapAttr(2);
			this->PortalSetState = false;
			this->m_BattleData.PhazeStep++;
		}

		if(this->m_BattleData.Time <= 0)
		{
			this->SetSuccessValue(false);
			this->SetState(BATTLEOFKATO_STATE_END);
		}
	}
}

void CImperialBattleOfKato::ProcState_STANDBY2()
{
	int Tick = GetTickCount() - this->m_BattleData.TickCount;
	if(Tick >= 1000)
	{
		this->m_BattleData.Time -= Tick;
		this->m_BattleData.TickCount = GetTickCount();

		this->SendEventInterface();

		if(this->m_BattleData.Time <= 0)
		{
			this->SetState(BATTLEOFKATO_STATE_PHAZE2);
		}
	}
}

void CImperialBattleOfKato::ProcState_PHAZE2()
{
	int Tick = GetTickCount() - this->m_BattleData.TickCount;
	if(Tick >= 1000)
	{
		this->m_BattleData.Time -= Tick;
		this->m_BattleData.TickCount = GetTickCount();

		this->SendEventInterface();
		this->MonsterProc();

		for(int i=0;i<12;++i)
		{
			for(int n=0;n<g_ImperialBattleUserMng.GetUserCount();++n)
			{

				if(gObj[g_ImperialBattleUserMng.m_BattleUser[n].GetIndex()].X >= g_KatoTrap[i].X-5 && gObj[g_ImperialBattleUserMng.m_BattleUser[n].GetIndex()].X <= g_KatoTrap[i].X+5
					&& gObj[g_ImperialBattleUserMng.m_BattleUser[n].GetIndex()].Y >= g_KatoTrap[i].Y-5 && gObj[g_ImperialBattleUserMng.m_BattleUser[n].GetIndex()].Y <= g_KatoTrap[i].Y+5)
				{
					gObjAttack(&gObj[this->m_BattleData.TrapIndex], &gObj[g_ImperialBattleUserMng.m_BattleUser[n].GetIndex()], NULL, 0, 0, 0, 0,0,0);
				}
			}
		}

		if(this->m_BattleData.Time > 0 && (this->m_BattleData.Time/60000) !=this->m_BattleData.NotifyCount)
		{
			this->m_BattleData.NotifyCount = this->m_BattleData.Time / 60000;
			PMSG_NOTICE pNotice;
			TNotice::MakeNoticeMsgEx(&pNotice, 0, "Portal will be closed after %d minutes", this->m_BattleData.NotifyCount+1);
			this->SendImperialPlayers((LPBYTE)&pNotice, pNotice.h.size);
		}

		if(gObj[this->m_BattleData.GateIndex[3]].Live == false && this->m_BattleData.PhazeStep == 0)
		{
			this->SetMapAttr(3);
			this->m_BattleData.PhazeStep++;
		}

		if(this->m_BattleData.MonsterCount <= 0 && this->m_BattleData.PhazeStep == 1)
		{
			gObj[this->m_BattleData.GateIndex[4]].m_ImmuneToHarmCount = 0;
			gObj[this->m_BattleData.GateIndex[4]].m_ImmuneToMagicCount = 0;
			this->m_BattleData.PhazeStep++;
		}
		if(gObj[this->m_BattleData.GateIndex[4]].Live == false && this->m_BattleData.PhazeStep == 2)
		{
			gObj[this->m_BattleData.GateIndex[5]].m_ImmuneToHarmCount = 0;
			gObj[this->m_BattleData.GateIndex[5]].m_ImmuneToMagicCount = 0;
			this->SetMapAttr(4);
			this->m_BattleData.PhazeStep++;
		}
		if(gObj[this->m_BattleData.GateIndex[5]].Live == false && this->m_BattleData.PhazeStep == 3)
		{
			this->SetMapAttr(5);
			this->PortalSetState = false;
			this->m_BattleData.PhazeStep++;
		}

		if(this->m_BattleData.Time <= 0)
		{
			this->SetSuccessValue(false);
			this->SetState(BATTLEOFKATO_STATE_END);
		}
	}
}

void CImperialBattleOfKato::ProcState_STANDBY3()
{
	int Tick = GetTickCount() - this->m_BattleData.TickCount;
	if(Tick >= 1000)
	{
		this->m_BattleData.Time -= Tick;
		this->m_BattleData.TickCount = GetTickCount();

		this->SendEventInterface();

		if(this->m_BattleData.Time <= 0)
		{
			this->SetState(BATTLEOFKATO_STATE_PHAZE3);
		}
	}
}

void CImperialBattleOfKato::ProcState_PHAZE3()
{
	int Tick = GetTickCount() - this->m_BattleData.TickCount;
	if(Tick >= 1000)
	{
		this->m_BattleData.Time -= Tick;
		this->m_BattleData.TickCount = GetTickCount();

		this->SendEventInterface();
		this->MonsterProc();

		if(this->m_BattleData.Time > 0 && (this->m_BattleData.Time/60000) !=this->m_BattleData.NotifyCount)
		{
			this->m_BattleData.NotifyCount = this->m_BattleData.Time / 60000;
			PMSG_NOTICE pNotice;
			TNotice::MakeNoticeMsgEx(&pNotice, 0, "%d minutes to escape %s!", this->m_BattleData.NotifyCount+1, gObj[this->m_BattleData.CurrentLeaderIndex].Name);
			this->SendImperialPlayers((LPBYTE)&pNotice, pNotice.h.size);
		}

		if(gObj[this->m_BattleData.GateIndex[6]].Live == false && this->m_BattleData.PhazeStep == 0)
		{
			this->SetMapAttr(6);
			this->m_BattleData.PhazeStep++;
		}

		if(gObj[this->m_BattleData.CurrentLeaderIndex].Live == false)
		{
			this->SetSuccessValue(true);
			this->SetState(BATTLEOFKATO_STATE_END);
		}
		if(this->m_BattleData.Time <= 0 && gObj[this->m_BattleData.CurrentLeaderIndex].Live == true)
		{
			this->SetSuccessValue(false);
			this->SetState(BATTLEOFKATO_STATE_END);
		}
	}
}

void CImperialBattleOfKato::ProcState_END()
{
	return;
}

int CImperialBattleOfKato::GetEventTime()
{
	return this->m_BattleData.Time / 1000;
}

int CImperialBattleOfKato::GetEventState()
{
	int CurrState = this->m_BattleData.CurrentState;
	if(CurrState == 1 || CurrState == 3 || CurrState == 5)
	{
		return 1;
	}
	else if(CurrState == 2 || CurrState == 4 || CurrState == 6)
	{
		return 2;
	}
	else if(CurrState == 7)
	{
		return 0;
	}
	return 3;
}

void CImperialBattleOfKato::SendImperialPlayers(LPBYTE lpMsg, int iSize)
{
	int index;
	for(int i=0; i < g_ImperialBattleUserMng.GetUserCount();++i)
	{
		index = g_ImperialBattleUserMng.m_BattleUser[i].GetIndex();

		if(IMPERIAL_MAP_RANGE(gObj[index].MapNumber))
		{
			DataSend(index, lpMsg, iSize);
		}	
	}
}

void CImperialBattleOfKato::SendEventInterface()
{
	PMSG_FORT_TIMER pMsg;

	PHeadSubSetB((LPBYTE)&pMsg,0xF7,0x04,sizeof(pMsg));

	int Time = this->GetEventTime() * 4;

	pMsg.Status = this->GetEventState();
	pMsg.Unk1 = 1;
	pMsg.Unk2 = 1;
	pMsg.Unk3 = 0;
	pMsg.Unk5 = 0;
	pMsg.TimerH = HIBYTE(Time);
	pMsg.TimerL = LOBYTE(Time);
	pMsg.Unk4 = 0;
	pMsg.Monster = this->m_BattleData.MonsterCount;

	this->SendImperialPlayers((LPBYTE)&pMsg, pMsg.h.size);
}

void CImperialBattleOfKato::SetMapAttr(int Gate)
{
	char Buff[256];
	short PacketSize = 0;
	PMSG_SETMAPATTR_COUNT * lpMsg = (PMSG_SETMAPATTR_COUNT *)(Buff);
	PMSG_SETMAPATTR * lpMsgBody = (PMSG_SETMAPATTR *)(Buff + sizeof(PMSG_SETMAPATTR_COUNT));

	lpMsgBody[0].btX = g_KatoMapAttr[Gate].StartX;
	lpMsgBody[0].btY = g_KatoMapAttr[Gate].StartY;
	lpMsgBody[1].btX = g_KatoMapAttr[Gate].EndX;
	lpMsgBody[1].btY = g_KatoMapAttr[Gate].EndY;

	PacketSize = (sizeof(PMSG_SETMAPATTR_COUNT)+6*sizeof(PMSG_SETMAPATTR));

	lpMsg->btMapAttr = 16;
	lpMsg->btMapSetType = 1;
	lpMsg->btCount = 1;
	lpMsg->btType = 0;

	lpMsg->h.c = 0xC1;
	lpMsg->h.headcode = 0x46;
	lpMsg->h.size = PacketSize;

	this->SendImperialPlayers((LPBYTE)Buff, PacketSize);
}

void CImperialBattleOfKato::MonsterProc()
{
	short alivecount = 0;
	for(int i=0;i<TMonsterAIGroup::s_iMonsterAIGroupMemberCount[this->m_BattleData.CurrentAIGroup];++i)
	{
		if(gObj[TMonsterAIGroup::FindGroupMemberObjectIndex(this->m_BattleData.CurrentAIGroup, i)].Live == true)
		{
			++alivecount;
		}
	}
	this->m_BattleData.MonsterCount = alivecount;
}

void CImperialBattleOfKato::OperatePortalGate(bool Block, bool ForAll, int aIndex)
{
	return;
}

void CImperialBattleOfKato::SetNextState()
{
	int iNextState = this->m_BattleData.CurrentState + 1;

	if ( iNextState >= BATTLEOFKATO_STATE_END )
	{
		iNextState = BATTLEOFKATO_STATE_NONE;
	}

	this->SetState(iNextState);
}

bool CImperialBattleOfKato::EnterPortal(LPOBJ lpObj)
{
	if(this->m_BattleData.MonsterCount > 0)
		return false;
	
	//if(this->m_BattleData.PhazeStep != 4)	//DeBug
	//	return false;

	if(!this->PortalSetState)
	{
		this->SetNextState();
		this->PortalSetState = true;
	}

	return true;
}

void CImperialBattleOfKato::SendEventState()
{
	PMSG_FORT_ENTER_RESULT pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF7, 0x02, sizeof(pMsg));

	pMsg.EntryTime = 0;
	pMsg.Day = 3;
	pMsg.Result = 0;
	
	int State;

	if(this->m_BattleData.CurrentState == 1 || this->m_BattleData.CurrentState == 2)
	{
		State = 1;
	}
	else if(this->m_BattleData.CurrentState == 3 || this->m_BattleData.CurrentState == 4)
	{
		State = 2;
	}
	else if(this->m_BattleData.CurrentState == 5 || this->m_BattleData.CurrentState == 6)
	{
		State = 3;
	}

	pMsg.State = State;
	pMsg.Unk = 3;

	this->SendImperialPlayers((LPBYTE)&pMsg, pMsg.h.size);
}