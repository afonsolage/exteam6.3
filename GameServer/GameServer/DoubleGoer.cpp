#include "stdafx.h"
#include "user.h"
#include "DoubleGoer.h"
#include "protocol.h"
#include "logproc.h"
#include "..\common\winutil.h"
#include "..\include\readscript.h"
#include "TMonsterAIUtil.h"
#include "NpcTalk.h"
#include "BloodCastle.h"
#include "DevilSquare.h"
#include "BuffManager.h"
#include "GameMain.h"
#include "TNotice.h"
#include "BuffEffect.h"

//-------------------------------------------------------------------------------------------------------------------------------

CDoppelGanger g_DoppelGanger;
//-------------------------------------------------------------------------------------------------------------------------------
int			DGEnabled;
int			DGCoolDown;
int			DGSilverChestOpenRate = 5000;	//50;
int			DGUseAutoStat;
int			DGEnterMoney;
//-------------------------------------------------------------------------------------------------------------------------------

int			TickCount		= 0;
int			stTickRate		= GetTickCount();
int			EventTimeTick	= GetTickCount();
//-------------------------------------------------------------------------------------------------------------------------------

static		TMonsterAIUtil DG_UTIL;

//-------------------------------------------------------------------------------------------------------------------------------

void CDoppelGanger::Init()
{

	// player pos
	this->POSX[0] = 197,	this->POSY[0] = 30;
	this->POSX[1] = 133,	this->POSY[1] = 68;
	this->POSX[2] = 110,	this->POSY[2] = 60;
	this->POSX[3] = 95,		this->POSY[3] = 15;

	// monster pos
	this->MPOSX[0] = 224,	this->MPOSY[0] = 100;
	this->MPOSX[1] = 113,	this->MPOSY[1] = 180;
	this->MPOSX[2] = 110,	this->MPOSY[2] = 150;
	this->MPOSX[3] = 43,	this->MPOSY[3] = 108;

	this->m_DGData.Clear();

	this->LoadConfigFile(gDirPath.GetNewPath("\\Events\\DoubleGoer.dat"));

	if(!DGEnabled)
	{
		this->SetState(DG_STATE_NONE);
	}
	else
	{
		this->SetState(DG_STATE_OPEN);
	}
}

void CDoppelGanger::SetState(int iState)
{
	switch(iState)
	{
	case DG_STATE_NONE:
		return;
	case DG_STATE_OPEN:
		this->SetState_OPEN();
		break;
	case DG_STATE_WAITING:
		this->SetState_WAITING();
		break;
	case DG_STATE_STARTED:
		this->SetState_STARTED();
		break;
	case DG_STATE_ENDED:
		this->SetState_ENDED();
		break;
	}
}

void CDoppelGanger::SetState_OPEN()
{
	for(int i=OBJ_STARTUSERINDEX;i<OBJMAX;++i)
	{
		gObj[i].m_btDoubleGoerRoom = -1;
		if(DG_MAP_RANGE(gObj[i].MapNumber) && gObj[i].Connected == PLAYER_PLAYING)
		{
			gObjMoveGate(i, 267);
		}
	}
	for(int i=0;i<OBJ_MAXMONSTER;++i)
	{
		if(gObjIsConnected(i) && DG_MAP_RANGE(gObj[i].MapNumber))
			gObjDel(i);
	}
	this->m_DGData.Clear();
	this->m_DGData.btPlayState = DG_STATE_OPEN;
	LogAddTD("[DoppelGanger] SetState OPEN");
}

void CDoppelGanger::SetState_WAITING()
{
	this->m_DGData.eDuration = 660000; // 11 minutes (10 for event, 1 for cooldown)
	this->m_DGData.TickCount = GetTickCount();
	this->m_DGData.btPlayState = DG_STATE_WAITING;
	LogAddTD("[DoppelGanger] SetState WAITING");
}

void CDoppelGanger::SetState_STARTED()
{
	this->m_DGData.eDuration = 600000; // for certainly..
	this->m_DGData.HalfTimeInfoSent = false; // for Ice Walker msg
	this->m_DGData.CreateMonsterDelay = 2; // first monster create
	this->m_DGData.MonsterPassed = 0; // set monster passed portal to 0
	if(this->SetEventLevel() == false)
	{
		this->SetState(DG_STATE_ENDED);
		return;
	}
	this->SetMapAttr(false, NULL); // unblock portal zone exit
	this->SetEventInterface(); // activate interface
	this->SetMonsterCountOnInterface();
	this->m_DGData.TickCount = GetTickCount();
	this->m_DGData.btPlayState = DG_STATE_STARTED;
	LogAddTD("[DoppelGanger] SetState STARTED | Players: (%d) MapNumber: (%d)", this->m_DGData.PlayerCount, this->m_DGData.MapNumber);
}

void CDoppelGanger::SetState_ENDED()
{
	this->m_DGData.eDuration = DGCoolDown * 60 * 1000;
	this->DeleteMonster();
	this->m_DGData.TickCount = GetTickCount();
	this->m_DGData.btPlayState = DG_STATE_ENDED;
	LogAddTD("[DoppelGanger] SetState ENDED");
}

void CDoppelGanger::Run()
{
	switch ( this->m_DGData.btPlayState )
	{
	case DG_STATE_NONE:
		return;
	case DG_STATE_OPEN:
		this->ProcState_OPEN();
		break;
	case DG_STATE_WAITING:
		this->ProcState_WAITING();
		break;
	case DG_STATE_STARTED:
		this->ProcState_STARTED();
		break;
	case DG_STATE_ENDED:
		this->ProcState_ENDED();
		break;
	}
}

void CDoppelGanger::ProcState_OPEN()
{
	if(this->m_DGData.PlayerCount > 0)
	{
		this->SetState(DG_STATE_WAITING);
	}
}

void CDoppelGanger::ProcState_WAITING()
{
	int Tick = GetTickCount() - this->m_DGData.TickCount;

	if(Tick >= 1000)
	{
		this->m_DGData.eDuration -= Tick;
		this->m_DGData.TickCount = GetTickCount();

		this->CheckUsers();

		if(this->m_DGData.PlayerCount <= 0)
		{
			LogAddTD("[DoppelGanger] Reset Event - No user");
			this->SetState(DG_STATE_ENDED);
			return;
		}


		if(this->m_DGData.eDuration <= 630000 && this->m_DGData.HalfTimeInfoSent == false)
		{
			this->SendHalfTimeInfo(17);
		}

		if(this->m_DGData.eDuration <= 600000)
		{
			this->SetState(DG_STATE_STARTED);
		}
	}
}

void CDoppelGanger::ProcState_STARTED()
{
	int Tick = GetTickCount() - this->m_DGData.TickCount;

	if(Tick >= 1000)
	{
		this->m_DGData.eDuration -= Tick;
		this->m_DGData.TickCount = GetTickCount();
		++this->m_DGData.CreateMonsterDelay;
		if(this->m_DGData.CreateMonsterDelay == 3)
		{
			this->CreateMonster();
			this->m_DGData.CreateMonsterDelay = 0;
		}

		if(this->m_DGData.PlayerCount <= 0)
		{
			LogAddTD("[DoppelGanger] Reset Event - No user");
			this->SetState(DG_STATE_ENDED);
			return;
		}

		this->SendPlayerPos();
		this->SendMonsterPos();
		this->CheckPosition();
		this->CheckUsers();
		if(this->m_DGData.eDuration < 480000 && this->m_DGData.PhazesPassed == 0)
		{
			this->CreateButcher();
		}

		if(this->m_DGData.eDuration < 360000 && this->m_DGData.PhazesPassed == 1)
		{
			this->CreateButcher();
		}

		if(this->m_DGData.eDuration < 300000 && this->m_DGData.PhazesPassed == 2)
		{
			this->CreateAngryButcher();
		}

		if(this->m_DGData.eDuration < 210000 && this->m_DGData.PhazesPassed == 3)
		{
			this->CreateIceWalker();
		}

		if(this->m_DGData.PhazesPassed == 4 && gObjIsConnected(this->m_DGData.IceWalkerIndex))
		{
			this->SendIceWalkerPos();
			if(gObj[this->m_DGData.IceWalkerIndex].Live == true)
			{
				--this->m_DGData.IceWalkerPhazeTime;
				if(this->m_DGData.IceWalkerPhazeTime <= 30 && this->m_DGData.HalfTimeInfoSent == false)
				{
					this->SendHalfTimeInfo(18);
					this->m_DGData.HalfTimeInfoSent = true;
				}
				if(this->m_DGData.IceWalkerPhazeTime <= 0)
				{
					PMSG_NOTICE pNotice;
					TNotice::MakeNoticeMsg(&pNotice, 0, "Ice walker time passed");
					this->SendDoppelGangerPlayer((LPBYTE)&pNotice, pNotice.h.size);
					gObjDel(this->m_DGData.IceWalkerIndex);
					this->m_DGData.IceWalkerIndex = -1;
				}
			}
		}

		if(this->m_DGData.MonsterPassed >= GOER_MAX_PASS_PORTAL)
		{
			this->SendResultMessage(DG_RESULT_DEFENSE_FAIL, true, -1);
			this->SetState(DG_STATE_ENDED);
			LogAddTD("[DoppelGanger] Quest Failed - too many monsters passed portal");
		}

		if(this->m_DGData.eDuration <= 0)
		{
			this->CreateFinalChest();
			this->SendResultMessage(DG_RESULT_SUCCESS, true, -1);
			this->SetState(DG_STATE_ENDED);
			LogAddTD("[DoppelGanger] Quest Success | Monsters: (%d/%d)", this->m_DGData.MonsterPassed, GOER_MAX_PASS_PORTAL);
		}
	}
}

void CDoppelGanger::ProcState_ENDED()
{
	int Tick = GetTickCount() - this->m_DGData.TickCount;

	if(Tick >= 1000)
	{
		this->m_DGData.eDuration -= Tick;
		this->m_DGData.TickCount = GetTickCount();

		if(this->m_DGData.eDuration <= 0)
		{
			//this->CreateFinalChest();
			this->SetState(DG_STATE_OPEN);	
		}
	}
}




void CDoppelGanger::EnterEvent(LPOBJ lpObj)
{

	if(this->m_DGData.btPlayState != DG_STATE_OPEN && this->m_DGData.btPlayState != DG_STATE_WAITING)
	{
		return;
	}

	if(lpObj->TargetShopNumber != 540) // Lugard
	{
		return;
	}

	int invitationpos = -1;

	for(short i = 12 ; i < 76; ++i)
	{
		if(lpObj->pInventory[i].m_Type > 0 && lpObj->pInventory[i].m_Type == ITEMGET(14,111))
		{
			invitationpos = i;
			break;
		}
	}
	if(invitationpos == -1)
		return;

	//if(lpObj->VipType == 0)
	//{
	if(lpObj->Money < DGEnterMoney)
	{
		GCServerMsgStringSend("You are short of money", lpObj->m_Index, 1);
		return;
	}
	lpObj->Money -= DGEnterMoney;
	GCMoneySend(lpObj->m_Index, lpObj->Money);
	//}

	if(this->m_DGData.btPlayState == DG_STATE_WAITING)
	{
		if(this->m_DGData.PartyNumber != lpObj->PartyNumber)
		{
			return;
		}
	}
	if(this->AddPlayer(lpObj) == true)
	{		
		gObjInventoryDeleteItem(lpObj->m_Index, invitationpos);
		GCInventoryItemDeleteSend(lpObj->m_Index, invitationpos, 1);

		int iGate = this->SetMapNumber();

		gObjMoveGate(lpObj->m_Index, iGate);

		this->SetMapAttr(true, lpObj);

		lpObj->TargetShopNumber = 0;

		LogAddTD("[DoppelGanger] [%s][%s] Entered to DoppelGanger (%d)", lpObj->AccountID, lpObj->Name, this->m_DGData.PlayerCount);
	}
}

bool CDoppelGanger::AddPlayer(LPOBJ lpObj)
{
	for(int i=0;i<5;++i)
	{
		if(this->m_DGData.PlayerIndex[i] == -1)
		{
			this->m_DGData.PlayerIndex[i] = lpObj->m_Index;
			lpObj->m_btDoubleGoerRoom = 1;
			if(i == 0) // first player, set party number, that other teammates can enter to event
			{
				this->m_DGData.PartyNumber = lpObj->PartyNumber;
			}
			++this->m_DGData.PlayerCount;
			LogAddTD("[DoppelGanger] (%s)(%s) Add to event, current player count: %d", lpObj->AccountID, lpObj->Name, this->m_DGData.PlayerCount);
			return true;
		}
	}
	return false;
}

char CDoppelGanger::GetEventTime(LPOBJ lpObj)
{
	if(lpObj->PartyNumber == this->m_DGData.PartyNumber && this->m_DGData.btPlayState == DG_STATE_WAITING)
	{
		return 0;
	}
	else if(this->m_DGData.btPlayState == DG_STATE_OPEN)
	{
		return 0;
	}
	return this->m_DGData.eDuration;
}

void CDoppelGanger::SetMapAttr(bool Block, LPOBJ lpObj)
{
	char cTEMP_BUF[256];
	int lOfs = 0;
	PMSG_SETMAPATTR_COUNT pMsg;
	PMSG_SETMAPATTR pBodyMsg;
	lOfs += sizeof(pMsg);

	pMsg.btType = 0;
	pMsg.btCount = 1;
	pMsg.btMapAttr = 4;
	pMsg.btMapSetType = (Block == true) ? 4 : 1;

	pBodyMsg.btX = g_DGEntrance[this->m_DGData.MapNumber-65].iStartX;
	pBodyMsg.btY = g_DGEntrance[this->m_DGData.MapNumber-65].iStartY;
	memcpy(&cTEMP_BUF[lOfs], &pBodyMsg, sizeof(pBodyMsg));
	lOfs += sizeof(pBodyMsg);
	pBodyMsg.btX   = g_DGEntrance[this->m_DGData.MapNumber-65].iEndX;
	pBodyMsg.btY   = g_DGEntrance[this->m_DGData.MapNumber-65].iEndY;
	memcpy(&cTEMP_BUF[lOfs], &pBodyMsg, sizeof(pBodyMsg));
	lOfs += sizeof(pBodyMsg);

	pMsg.h.c = 0xC1;
	pMsg.h.size = lOfs;
	pMsg.h.headcode = 0x46;
	memcpy(&cTEMP_BUF, &pMsg, sizeof(pMsg));

	if(Block)
	{
		DataSend(lpObj->m_Index, (LPBYTE)&cTEMP_BUF, lOfs);
	}
	else
	{
		this->SendDoppelGangerPlayer((LPBYTE)&cTEMP_BUF, lOfs);
	}
}

void CDoppelGanger::SendDoppelGangerPlayer(LPBYTE lpMsg, int iSize)
{
	for(int i=0;i<5;++i)
	{
		if(this->m_DGData.PlayerIndex[i] != -1 && gObjIsConnectedGP(this->m_DGData.PlayerIndex[i]) && gObj[this->m_DGData.PlayerIndex[i]].MapNumber == this->m_DGData.MapNumber)
		{
			DataSend(this->m_DGData.PlayerIndex[i], lpMsg, iSize);
		}
	}
}

void CDoppelGanger::SendHalfTimeInfo(int Type)
{
	PMSG_SET_DEVILSQUARE pMsg;

	PHeadSetB((LPBYTE)&pMsg, 0x92, sizeof(pMsg));
	pMsg.Type = Type;

	this->SendDoppelGangerPlayer((LPBYTE)&pMsg, pMsg.h.size);
	this->m_DGData.HalfTimeInfoSent = true;
}

void CDoppelGanger::SetEventInterface()
{
	PMSG_DGOER_TIMER_INIT pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xBF, 0x10, sizeof(pMsg));
	pMsg.Timer = 2;

	this->SendDoppelGangerPlayer((LPBYTE)&pMsg, pMsg.h.size);
}

void CDoppelGanger::SetMonsterCountOnInterface()
{
	PMSG_DGOER_MONSTER_COUNT pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xBF, 0x14, sizeof(pMsg));
	pMsg.Killed = this->m_DGData.MonsterPassed;
	pMsg.Total = GOER_MAX_PASS_PORTAL;

	this->SendDoppelGangerPlayer((LPBYTE)&pMsg, pMsg.h.size);
}

void CDoppelGanger::SendPlayerPos()
{
	PMSG_DGOER_UPDATE_BAR pMsg;
	PLAYER_BAR_INFO pPlayer;

	int Time = this->m_DGData.eDuration / 1000;
	char cBUFF[256];
	int lOfs = 8;

	for(int i=0;i<5;++i)
	{
		memset(&pPlayer, 0x00, sizeof(pPlayer));
		if(gObjIsConnectedGP(this->m_DGData.PlayerIndex[i]) )
		{
			pPlayer.UserH = HIBYTE(this->m_DGData.PlayerIndex[i]);
			pPlayer.UserL = LOBYTE(this->m_DGData.PlayerIndex[i]);
			pPlayer.Visible = 1; // visible on bar
			pPlayer.Pos = this->CalcPos(i, false);
		}
		memcpy(&cBUFF[lOfs], &pPlayer, sizeof(pPlayer));
		lOfs += sizeof(pPlayer);
	}

	pMsg.UserCount = this->m_DGData.PlayerCount;
	pMsg.Unk = 0;
	pMsg.TimerH = HIBYTE(Time);
	pMsg.TimerL = LOBYTE(Time);

	PHeadSubSetB((LPBYTE)&pMsg, 0xBF, 0x12, lOfs);
	memcpy(&cBUFF, &pMsg, sizeof(pMsg));

	this->SendDoppelGangerPlayer((LPBYTE)&cBUFF, lOfs);
}

void CDoppelGanger::SendMonsterPos()
{
	PMSG_DGOER_TRIANG_POS pMsg;

	int nearest = 0, temp = -1;

	PHeadSubSetB((LPBYTE)&pMsg, 0xBF, 0x0F, sizeof(pMsg));

	for(int i=0;i<OBJ_MAXMONSTER;++i)
	{
		if(this->IsDGMonster(&gObj[i]) && this->m_DGData.MapNumber == gObj[i].MapNumber && gObj[i].Live == true && gObj[i].Connected == PLAYER_PLAYING)
		{
			temp = this->CalcPos(i, true);
		}
		if(temp > nearest)
		{
			nearest = temp;
		}
	}
	if(nearest == -1)
		nearest = 0;

	pMsg.Pos = nearest;
	this->SendDoppelGangerPlayer((LPBYTE)&pMsg, pMsg.h.size);
}

void CDoppelGanger::SendIceWalkerPos()
{
	PMSG_DGOER_RTRIANG_POS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xBF, 0x11, sizeof(pMsg));

	pMsg.Unk = (gObj[this->m_DGData.IceWalkerIndex].Live==true) ? 0 : 1;
	pMsg.Pos = this->CalcPos(this->m_DGData.IceWalkerIndex, true);

	this->SendDoppelGangerPlayer((LPBYTE)&pMsg, pMsg.h.size);
}


int CDoppelGanger::SetMapNumber()
{
	if(this->m_DGData.MapNumber != -1)
	{
		return (264+this->m_DGData.MapNumber);
	}
	else
	{
		this->m_DGData.MapNumber = 65 + (rand()%4);
		return (264+this->m_DGData.MapNumber);
	}
}

void CDoppelGanger::CreateMonster()
{
	if(this->m_DGData.MonsterCount < (40 * this->m_DGData.PlayerCount))
	{
		for(int i=0;i<200;++i)
		{
			if(this->m_DGData.MonsterIndex[i] == -1)
			{
				this->m_DGData.MonsterIndex[i] = gObjAddMonster(this->m_DGData.MapNumber);
				if(this->m_DGData.MonsterIndex[i] >= 0)
				{
					gObj[this->m_DGData.MonsterIndex[i]].MapNumber = this->m_DGData.MapNumber;
					gObj[this->m_DGData.MonsterIndex[i]].X = this->MPOSX[this->m_DGData.MapNumber-65];
					gObj[this->m_DGData.MonsterIndex[i]].Y = this->MPOSY[this->m_DGData.MapNumber-65];

					gObjSetMonster(this->m_DGData.MonsterIndex[i], (rand()%6+533));
					++this->m_DGData.MonsterCount;
					LogAddTD("[DoppelGanger] Spawn Illusion: (%d) Index: (%d)", i, this->m_DGData.MonsterIndex[i]);
					return;
				}
			}
		}
	}
}

void CDoppelGanger::MoveProc(LPOBJ lpObj)
{
	if(this->IsDGMonster(lpObj) == true)
	{
		lpObj->MTX = this->POSX[this->m_DGData.MapNumber-65];
		lpObj->MTY = this->POSY[this->m_DGData.MapNumber-65];

		DG_UTIL.FindPathToMoveMonster(lpObj, this->POSX[this->m_DGData.MapNumber-65], this->POSY[this->m_DGData.MapNumber-65], 40, 2);
	}
}

bool CDoppelGanger::IsDGMonster(LPOBJ lpObj)
{
	for(int i=0;i<200;++i)
	{
		if(this->m_DGData.MonsterIndex[i] == lpObj->m_Index)
		{
			return true;
		}
	}
	if(this->m_DGData.ButcherIndex == lpObj->m_Index) return true;
	if(this->m_DGData.AngryButcherIndex == lpObj->m_Index) return true;
	if(this->m_DGData.IceWalkerIndex == lpObj->m_Index) return true;
	for(int n=0;n<3;++n)
	{
		if(this->m_DGData.SilverBoxIndex[n] == lpObj->m_Index)
		{
			return true;
		}
	}
	return false;
}

void CDoppelGanger::RegenProc(LPOBJ lpObj)
{
	if(this->IsDGMonster(lpObj) == true)
	{
		lpObj->RegenMapX = this->MPOSX[this->m_DGData.MapNumber-65];
		lpObj->RegenMapY = this->MPOSY[this->m_DGData.MapNumber-65];
		lpObj->X = this->MPOSX[this->m_DGData.MapNumber-65];
		lpObj->Y = this->MPOSY[this->m_DGData.MapNumber-65];
	}
	if(this->m_DGData.ButcherIndex == lpObj->m_Index) gObjDel(lpObj->m_Index);
	if(this->m_DGData.AngryButcherIndex == lpObj->m_Index) gObjDel(lpObj->m_Index);
	if(this->m_DGData.IceWalkerIndex == lpObj->m_Index) gObjDel(lpObj->m_Index);
	for(int i=0;i<2;++i)
	{
		if(this->m_DGData.SilverBoxIndex[i] == lpObj->m_Index)
		{
			this->m_DGData.SilverBoxIndex[i] = -1;
			gObjDel(lpObj->m_Index);
		}
	}
}

int CDoppelGanger::CalcPos(int player, bool MonsterCalc)
{
	if(MonsterCalc == false)
	{
		if(this->m_DGData.MapNumber == 65)
		{
			if(gObj[this->m_DGData.PlayerIndex[player]].Y>31)
			{
				return 22-((gObj[this->m_DGData.PlayerIndex[player]].Y-31)/3.2);
			}
			else
			{
				return 22;
			}
		}
		else if(this->m_DGData.MapNumber == 66)
		{
			if(gObj[this->m_DGData.PlayerIndex[player]].Y>69)
			{
				return 22-(((gObj[this->m_DGData.PlayerIndex[player]].Y -70)*2)/10);
			}
			else
			{
				return 22;
			}
		}
		else if(this->m_DGData.MapNumber == 67)
		{
			if(gObj[this->m_DGData.PlayerIndex[player]].Y>61)
			{
				return 22-((gObj[this->m_DGData.PlayerIndex[player]].Y-61)/4.1);
			}
			else
			{
				return 22;
			}
		}
		else if(this->m_DGData.MapNumber == 68)
		{
			//for(int n=1;n<23;n++)
			//{	
			//	if(gObj[this->m_DGData.PlayerIndex[player]].MapNumber == 68 && gObj[this->m_DGData.PlayerIndex[player]].Y > 24+((n-1)*4) && gObj[this->m_DGData.PlayerIndex[player]].Y <= 27+((n-1)*4))
			//	{
			//		return n;
			//	}
			//}
			if(gObj[this->m_DGData.PlayerIndex[player]].Y>18)
			{
				return 22-((gObj[this->m_DGData.PlayerIndex[player]].Y-18)/4.1);
			}
			else
			{
				return 22;
			}
		}

	}
	else
	{
		if(this->m_DGData.MapNumber == 65)
		{
			if(gObj[player].Y>31)
			{
				return 22-((gObj[player].Y-31)/3.2);
			}
			else
			{
				return 22;
			}
		}
		else if(this->m_DGData.MapNumber == 66)
		{
			if(gObj[player].Y>69)
			{
				return 22-(((gObj[player].Y -70)*2)/10);
			}
			else
			{
				return 22;
			}
		}
		else if(this->m_DGData.MapNumber == 67)
		{
			if(gObj[player].Y>61)
			{
				return 22-((gObj[player].Y-61)/4.1);
			}
			else
			{
				return 22;
			}
		}
		else if(this->m_DGData.MapNumber == 68)
		{
			//for(int n=1;n<23;n++)
			//{	
			//	if(gObj[player].MapNumber == 68 && gObj[player].Y > 24+((n-1)*4) && gObj[player].Y <= 27+((n-1)*4))
			//	{
			//		return n;
			//	}
			//}
			if(gObj[player].Y>18)
			{
				return 22-((gObj[player].Y-18)/4.1);
			}
			else
			{
				return 22;
			}
		}
	}
	return 22;
}

void CDoppelGanger::CheckPosition()
{
	for(int i=0;i<200;++i)
	{
		if(gObj[this->m_DGData.MonsterIndex[i]].X > g_DGPortal[this->m_DGData.MapNumber-65].StartX - 3 &&
			gObj[this->m_DGData.MonsterIndex[i]].X < g_DGPortal[this->m_DGData.MapNumber-65].StartX +3 )
		{
			if(gObj[this->m_DGData.MonsterIndex[i]].Y > g_DGPortal[this->m_DGData.MapNumber-65].StartY - 5 &&
				gObj[this->m_DGData.MonsterIndex[i]].Y < g_DGPortal[this->m_DGData.MapNumber-65].StartY +5 )
			{
				gObj[this->m_DGData.MonsterIndex[i]].m_ViewSkillState[105] = 1;
				//BuffEffectC.EnableBuff(this->m_DGData.MonsterIndex[i], 105, -1, 0, 0, 0);
				gObjDel(this->m_DGData.MonsterIndex[i]);
				this->m_DGData.MonsterIndex[i] = -1;
				--this->m_DGData.MonsterCount;
				++this->m_DGData.MonsterPassed;
				this->SetMonsterCountOnInterface();
				LogAddTD("[DoppelGanger] Increase Monster Passed: (%d/%d)", this->m_DGData.MonsterPassed, GOER_MAX_PASS_PORTAL);
			}
		}
	}
}

void CDoppelGanger::SendResultMessage(BYTE Result, bool SendForAll, int aIndex)
{
	PMSG_DGOER_END pResult;

	PHeadSubSetB((LPBYTE)&pResult, 0xBF, 0x13, sizeof(pResult));

	pResult.Status = Result;

	if(SendForAll)
	{
		this->SendDoppelGangerPlayer((LPBYTE)&pResult, pResult.h.size);
	}
	else
	{
		DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);
	}
}

void CDoppelGanger::DeleteMonster()
{
	for(int i=0;i<200;++i)
	{
		if(this->m_DGData.MonsterIndex[i] != -1)
		{
			gObjDel(this->m_DGData.MonsterIndex[i]);
			this->m_DGData.MonsterIndex[i] = -1;
			--this->m_DGData.MonsterCount;
		}
	}
	if(this->m_DGData.ButcherIndex >= 0)
		gObjDel(this->m_DGData.ButcherIndex);
	if(this->m_DGData.AngryButcherIndex >= 0)
		gObjDel(this->m_DGData.AngryButcherIndex);
	if(this->m_DGData.IceWalkerIndex >= 0)
		gObjDel(this->m_DGData.IceWalkerIndex);

	this->m_DGData.SilverBoxIndex[0] = -1;
	this->m_DGData.SilverBoxIndex[1] = -1;
	this->m_DGData.SilverBoxIndex[2] = -1;

	for(int i=0;i<OBJ_MAXMONSTER;++i)
	{
		if(gObj[i].Class == 541 || gObj[i].Class == 532)
			gObjDel(i);
	}
}

void CDoppelGanger::CreateButcher()
{
	if(this->m_DGData.ButcherIndex >= 0) gObjDel(this->m_DGData.ButcherIndex);
	this->m_DGData.ButcherIndex = gObjAddMonster(this->m_DGData.MapNumber);
	if(this->m_DGData.ButcherIndex >= 0)
	{
		gObj[this->m_DGData.ButcherIndex].MapNumber = this->m_DGData.MapNumber;
		gObj[this->m_DGData.ButcherIndex].X = this->MPOSX[this->m_DGData.MapNumber-65];
		gObj[this->m_DGData.ButcherIndex].Y = this->MPOSY[this->m_DGData.MapNumber-65];
		gObj[this->m_DGData.ButcherIndex].m_MoveRange = 30;
		++this->m_DGData.PhazesPassed;
		gObjSetMonster(this->m_DGData.ButcherIndex, 530);

		LogAddTD("[DoppelGanger] Current Phaze: Butcher Attack");
	}
}

void CDoppelGanger::CreateAngryButcher()
{
	if(this->m_DGData.AngryButcherIndex >= 0) gObjDel(this->m_DGData.AngryButcherIndex);
	this->m_DGData.AngryButcherIndex = gObjAddMonster(this->m_DGData.MapNumber);
	if(this->m_DGData.AngryButcherIndex >= 0)
	{
		gObj[this->m_DGData.AngryButcherIndex].MapNumber = this->m_DGData.MapNumber;
		gObj[this->m_DGData.AngryButcherIndex].X = this->MPOSX[this->m_DGData.MapNumber-65];
		gObj[this->m_DGData.AngryButcherIndex].Y = this->MPOSY[this->m_DGData.MapNumber-65];
		gObj[this->m_DGData.AngryButcherIndex].m_MoveRange = 30;
		++this->m_DGData.PhazesPassed;
		gObjSetMonster(this->m_DGData.AngryButcherIndex, 529);

		LogAddTD("[DoppelGanger] Current Phaze: Angry Butcher Attack");
	}
}

void CDoppelGanger::CreateIceWalker()
{
	if(this->m_DGData.IceWalkerIndex >= 0) gObjDel(this->m_DGData.IceWalkerIndex);
	this->m_DGData.IceWalkerIndex = gObjAddMonster(this->m_DGData.MapNumber);
	if(this->m_DGData.IceWalkerIndex >= 0)
	{
		gObj[this->m_DGData.IceWalkerIndex].MapNumber = this->m_DGData.MapNumber;
		gObj[this->m_DGData.IceWalkerIndex].X = this->MPOSX[this->m_DGData.MapNumber-65];
		gObj[this->m_DGData.IceWalkerIndex].Y = this->MPOSY[this->m_DGData.MapNumber-65];
		gObj[this->m_DGData.IceWalkerIndex].m_MoveRange = 30;
		++this->m_DGData.PhazesPassed;
		this->m_DGData.IceWalkerPhazeTime = 90;
		gObjSetMonster(this->m_DGData.IceWalkerIndex, 531);

		PMSG_NOTICE pNotice;
		TNotice::MakeNoticeMsg(&pNotice, 0, "ICE Walker has been Spawn");
		this->SendDoppelGangerPlayer((LPBYTE)&pNotice, pNotice.h.size);
	}
}

bool CDoppelGanger::CreateSilverChest(LPOBJ lpObj)
{
	if(this->IsDGMonster(lpObj))
	{
		for(int i=0;i<3;++i)
		{
			this->m_DGData.SilverBoxIndex[i] = gObjAddMonster(this->m_DGData.MapNumber);
			gObj[this->m_DGData.SilverBoxIndex[i]].MapNumber = lpObj->MapNumber;
			gObj[this->m_DGData.SilverBoxIndex[i]].X = lpObj->X;
			gObj[this->m_DGData.SilverBoxIndex[i]].Y = lpObj->Y+rand()%2;
			gObjSetMonster(this->m_DGData.SilverBoxIndex[i], 541);
		}
		return true;
	}
	return false;
}

void CDoppelGanger::DeadUserProc(LPOBJ lpObj)
{
	unsigned char index = -1;

	for(int i=0;i<5;++i)
	{
		if(this->m_DGData.PlayerIndex[i] == lpObj->m_Index)
		{
			index = i;
			break;
		}
	}
	if(index == -1)
	{
		return;
	}

	this->m_DGData.PlayerIndex[index] = -1;
	--this->m_DGData.PlayerCount;

	this->SendResultMessage(DG_RESULT_DEAD_PLAYER, false, lpObj->m_Index);
}

void CDoppelGanger::CreateGoldenLarva(LPOBJ lpObj)
{
	int index;
	for(int i=0;i<2;++i)
	{
		index = gObjAddMonster(lpObj->MapNumber);
		if(index >= 0)
		{
			gObj[index].MapNumber = lpObj->MapNumber;
			gObj[index].X = lpObj->X;
			gObj[index].Y = lpObj->Y;
			gObjSetMonster(index, 532);
			LogAddTD("[DoppelGanger] Spawn Golden Larva Trap (%d) (%d/%d/%d)", index, gObj[index].MapNumber, gObj[index].X, gObj[index].Y);
		}
	}
}

void CDoppelGanger::SilverChestOpen(LPOBJ lpChest)
{
	if(rand()%10000 < DGSilverChestOpenRate)
	{
		SilverChestItemBag->DropSilverChestItem(lpChest->m_Index, lpChest->MapNumber, lpChest->X, lpChest->Y);
	}
	else
	{
		this->CreateGoldenLarva(lpChest);
	}
	lpChest->Life = 0.0;
	gObjLifeCheck(lpChest, lpChest, 1, 0, 0, 0, 0, 0);
	for(int i=0;i<3;++i)
	{
		if(this->m_DGData.SilverBoxIndex[i] != lpChest->m_Index)
		{
			gObjDel(this->m_DGData.SilverBoxIndex[i]);
		}
	}
}

void CDoppelGanger::CreateFinalChest()
{
	int index = -1;
	for(int i=0;i<5;++i)
	{
		if(this->m_DGData.PlayerIndex[i] != -1)
		{
			index = gObjAddMonster(this->m_DGData.MapNumber);
			if(index >= 0)
			{
				gObj[index].MapNumber = this->m_DGData.MapNumber;
				gObj[index].X = gObj[this->m_DGData.PlayerIndex[i]].X;
				gObj[index].Y = gObj[this->m_DGData.PlayerIndex[i]].Y;
				gObjSetMonster(index, 542);
			}
		}
	}
}

void CDoppelGanger::FinalChestOpen(LPOBJ lpChest)
{
	GoldenChestItemBag->DropGoldenChestItem(lpChest->m_Index, lpChest->MapNumber, lpChest->X, lpChest->Y);
	lpChest->Life = 0.0;
	gObjLifeCheck(lpChest, lpChest, 1, 0, 0, 0, 0, 0);
}

void CDoppelGanger::CheckUsers()
{
	for(int i=0;i<5;++i)
	{
		if(this->m_DGData.PlayerIndex[i] != -1)
		{
			if(gObj[this->m_DGData.PlayerIndex[i]].MapNumber != this->m_DGData.MapNumber || !gObjIsConnectedGP(this->m_DGData.PlayerIndex[i]))
			{
				this->SendResultMessage(DG_RESULT_DEAD_PLAYER, false, this->m_DGData.PlayerIndex[i]);
				this->m_DGData.PlayerIndex[i] = -1;
				--this->m_DGData.PlayerCount;
			}
		}
	}
}

bool CDoppelGanger::LoadConfigFile(LPSTR hFile)
{
	SMDFile = fopen(hFile, "r");

	if(SMDFile == NULL)
	{
		MsgBox("%s file not found", hFile);
		return false;
	}

	int Token;
	int n = 0;
	int type;

	DG_MONSTER_STAT Stat;

	while(true)
	{
		type = 0;

		Token = GetToken();

		if(Token == END)
			break;

		if(Token == NAME)
			continue;

		type = TokenNumber;

		if(type == 1)
		{
			Token = GetToken();
			DGEnabled = TokenNumber;

			Token = GetToken();
			DGCoolDown = TokenNumber;

			Token = GetToken();
			DGUseAutoStat = TokenNumber;

			Token = GetToken();
			DGEnterMoney = TokenNumber;

			LogAddTD("[DoppelGanger] Load Option: Enabled: %d, CoolDown: %d, AutoStat: %d, EnterMoney: %d", DGEnabled, DGCoolDown, DGUseAutoStat, DGEnterMoney);
		}

		else if(type == 2)
		{
			while(true)
			{
				Token = GetToken();

				if(Token == END)
					break;

				if(strcmp("end", TokenString)== 0)
					break;

				Stat.EventLevel = TokenNumber;

				Token = GetToken();
				Stat.Class = TokenNumber;

				Token = GetToken();
				Stat.Level = TokenNumber;

				Token = GetToken();
				Stat.HP = TokenNumber;

				Token = GetToken();
				Stat.DmgMin = TokenNumber;

				Token = GetToken();
				Stat.DmgMax = TokenNumber;

				Token = GetToken();
				Stat.Defense = TokenNumber;

				this->m_vtDGMobStat.push_back(Stat);
				++n;
			}
		}
	}
	LogAddTD("[DoppelGanger] Loaded %d Monster stats",n);
	return true;
}

bool CDoppelGanger::SetEventLevel()
{
	if(!DGUseAutoStat)
	{
		return true;
	}
	int temp = -1;
	int level;
	for(int i=0;i<5;++i)
	{
		if((level = (gObj[this->m_DGData.PlayerIndex[i]].Level + gObj[this->m_DGData.PlayerIndex[i]].MLevel)) > temp)
		{
			temp = level;
		}
	}
	if(temp == -1)
	{
		LogAddC(2, "[DoppelGanger] ERROR: EventLevel == -1!");
		return false;
	}
	this->m_DGData.EventLevel = temp/10;
	return true;
}

void CDoppelGanger::SetMonsterStats(LPOBJ lpObj)
{
	if(!DGUseAutoStat)
	{
		return;
	}

	short partyinc = 0;

	switch ( this->m_DGData.PlayerCount )
	{
	case 2:
		partyinc = 20;
		break;
	case 3:
		partyinc = 50;
		break;
	case 4:
		partyinc = 100;
		break;
	case 5:
		partyinc = 170;
		break;
	}


	std::vector<DG_MONSTER_STAT>::iterator Iterator;

	for(Iterator = this->m_vtDGMobStat.begin(); Iterator != this->m_vtDGMobStat.end(); ++Iterator)
	{
		if(this->m_DGData.EventLevel == Iterator->EventLevel && lpObj->Class == Iterator->Class)
		{
			lpObj->Level = Iterator->Level;
			lpObj->Life = Iterator->HP;
			lpObj->MaxLife = Iterator->HP;
			lpObj->m_Defense = Iterator->Defense;
			lpObj->m_AttackDamageMin = Iterator->DmgMin;
			lpObj->m_AttackDamageMax = Iterator->DmgMax;
			if(partyinc != 0)
			{
				lpObj->Life = ((lpObj->Life * partyinc)/100.0f);
				lpObj->MaxLife = ((lpObj->MaxLife * partyinc)/100.0f);
				lpObj->m_Defense = ((lpObj->m_Defense * partyinc)/100.0f);
				lpObj->m_AttackDamageMin = ((lpObj->m_AttackDamageMin * partyinc)/100.0f);
				lpObj->m_AttackDamageMax = ((lpObj->m_AttackDamageMax * partyinc)/100.0f);
			}
			break;
		}
	}
}