#include "stdafx.h"
#include "ConnectEx.h"
#include "Other.h"
#include "TMemory.h"
#include "Protocol.h"
#include "User.h"
#include "Interface.h"
#include "Console.h"
#include  "NewParty.h"
#include "Configs.h"
#include "ExText.h"
#include "BuffIcon.h"
#include "MuHelper.h"
#include "MUHelperOffline.h"

#ifdef exRECONNECT
// ----------------------------------------------------------------------------------------------

ConnectEx gConnectEx;
// ----------------------------------------------------------------------------------------------

DWORD GetAccountInfo_Buff;
DWORD GetAccountInfo_Buff2;
DWORD DisconnectExcept_Buff;
DWORD DisconnectEvent_Buff;
DWORD MenuExit_Buff;
int Counter;
// ----------------------------------------------------------------------------------------------

Naked(GetAccountInfo)
{
	_asm
	{
		lea ecx, [ebp-0x18]
		mov GetAccountInfo_Buff, ecx
		lea ecx, [ebp-0x30]
		mov GetAccountInfo_Buff2, ecx
	}
	// ----
	memcpy(gConnectEx.m_AccountID, (char*)GetAccountInfo_Buff, 10);
	memcpy(gConnectEx.m_Password, (char*)GetAccountInfo_Buff2, 20);

	*(DWORD*)0x8793714 = 1;
	// ----
	_asm
	{
		mov GetAccountInfo_Buff, 0x0040B90D
		jmp GetAccountInfo_Buff
	}
}
// ----------------------------------------------------------------------------------------------

Naked(DisconnectEvent)
{
	_asm
	{
		mov DisconnectEvent_Buff, ecx
	}

	// ----
	if( DisconnectEvent_Buff == 32 )
	{
		if( gConnectEx.m_ConnectState != ConnectExType::OnForceDisconnect )
		{
			//gConsole.Output(cGREEN,"1");
			gConnectEx.m_ConnectState = ConnectExType::OnReconnect;
		}
		else
		{
			SetByte((LPVOID)0x004DA422, 0x75);
		}
		// ----
		_asm
		{
			mov DisconnectEvent_Buff, 0x004D038B
			jmp DisconnectEvent_Buff
		}
	}
	// ----
	_asm
	{
		mov DisconnectEvent_Buff, 0x004D0430
		jmp DisconnectEvent_Buff
	}
}
// ----------------------------------------------------------------------------------------------

Naked(MenuExit)
{
	gConnectEx.m_ConnectState = ConnectExType::OnForceDisconnect;
	// ----
	_asm
	{
		mov MenuExit_Buff, 0x007A88AD
		jmp MenuExit_Buff
	}
}
// ----------------------------------------------------------------------------------------------

void ConnectEx::Load()
{
	this->m_ConnectState	= ConnectExType::OnLine;
	this->m_LastSendTick	= 0;
	this->m_ReconnectTick	= 0;
	this->m_WantMUHelper	= false;
	// ----
	SetRange((LPVOID)oMenuExit, 18, ASM::NOP);
	SetOp((LPVOID)oMenuExit, (LPVOID)MenuExit, ASM::JMP);
	SetRange((LPVOID)oDisconnectEvent, 9, ASM::NOP);
	SetOp((LPVOID)oDisconnectEvent, (LPVOID)DisconnectEvent, ASM::JMP);
	SetRange((LPVOID)oGetAccountInfo, 10, ASM::NOP);
	SetOp((LPVOID)oGetAccountInfo, (LPVOID)GetAccountInfo, ASM::JMP);
	SetByte((LPVOID)0x004DA422, 0xEB);
	//SetRange((LPVOID)0x0063CD76, 5, ASM::NOP);	//-> You are connected to the server	//x3

	SetRange((LPVOID)0x0063CDCB, 5, ASM::NOP);
	
}
// ----------------------------------------------------------------------------------------------

void ConnectEx::Run()
{
	DWORD Delay = GetTickCount() - this->m_LastSendTick;
	// ----
	if(	this->m_ConnectState != ConnectExType::OnReconnect )
	{
		return;
	}

	this->ClearGame();

	this->DrawProgres();

	if( Delay < 5000 || pPlayerState != GameProcess )
	{
		return;
	}
	// ----
	if( pOnLine == 0 )
	{
		this->Reconnect();
	}
	// ----
	if( pOnLine == 1 )
	{

		this->Relogin();
	}
	// ----
	this->m_LastSendTick = GetTickCount();
}
// ----------------------------------------------------------------------------------------------

void ConnectEx::ClearGame()
{
	//if( *(BYTE*)(pMUHelperClass + 8) )
	//{
	//	this->m_WantMUHelper = true;
	//	pMUHelperClose(pMUHelperThis());
	//}
	// ----
#if _NEW_PARTY_SYSTEM_ == TRUE
	g_Party.PartyMemberCount = 0;
	ZeroMemory(g_Party.PartyData,sizeof(g_Party.PartyData));
#else
	pPartyMemberCount = 0;
#endif

#if(USER_BUFF_ICON_EX==TRUE)
	g_BuffIcon.DeleteAllBuff();
#endif

	*(BYTE*)(oUserPreviewStruct + 780)	= 0; //gObjUser.lpViewPlayer->m_Model.Visible = 0;
	pPShopSet(pPShopThis2(pPShopThis1()), 0);
	pPShopRefresh(oUserPreviewStruct);


}
// ----------------------------------------------------------------------------------------------

void ConnectEx::RestoreGame()
{
	// ----
	if (this->m_ConnectState == ConnectExType::OnReconnect)
	{
		g_MUHelperOffline.RestoreState();
	}

	this->m_LastSendTick	= 0;
	this->m_ConnectState	= ConnectExType::OnLine;
	// ----
	//if( this->m_WantMUHelper )
	//{
	//	this->m_WantMUHelper = false;
	//	// ----
	//	if( !gObjUser.lpViewPlayer->InSafeZone )
	//	{
	//		pMUHelperStart(pMUHelperThis());
	//	}
	//}
}
// ----------------------------------------------------------------------------------------------

void ConnectEx::DrawProgres()
{
	float StartX = (MAX_WIN_WIDTH / 2) - (160.0 / 2);
	// ----
	Counter++;
	// ----
	if( Counter > 150 )
	{
		Counter = 0;
	}
	// ----

	pDrawGUI(0x7A65, StartX, 100, 160.0, 18.0);
	pDrawGUI(0x7A66, StartX + 5, 105, Counter, 8.0);

	// ----
	if( pOnLine == 0 )
	{
		pDrawColorText(g_ExText.GetText(114), StartX, 104, 160, 0, eBlue, 0, 3);
	}
	else if( pOnLine == 1 )
	{
		pDrawColorText(g_ExText.GetText(115), StartX, 104, 160, 0, eBlue, 0, 3);
	}
}
// ----------------------------------------------------------------------------------------------

void ConnectEx::Reconnect()
{
	PMSG_ANS_SERVER_INFO pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xF4, 3, sizeof(PMSG_ANS_SERVER_INFO));
	pRequest.Port = this->m_GSPort;
	memcpy(pRequest.Ip, this->m_GSIP, 16);
	gProtocol.DataRecv(pRequest.h.headcode, (LPBYTE)&pRequest, pRequest.h.size, 0);
}
// ----------------------------------------------------------------------------------------------

void ConnectEx::Relogin()
{
	lpCharObj lpPlayer			= pUserObjectStruct;
	CONNECTEX_LOGIN pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 12, sizeof(CONNECTEX_LOGIN));
	memcpy(pRequest.AccountID, this->m_AccountID, 10);
	memcpy(pRequest.Password, this->m_Password, 10);
	memcpy(pRequest.Name, lpPlayer->Name, 10);
	pRequest.TickCount = GetTickCount();
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// ----------------------------------------------------------------------------------------------

void ConnectEx::Disconnect()
{
	CONNECTEX_CLOSE pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 13, sizeof(CONNECTEX_CLOSE));
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// ----------------------------------------------------------------------------------------------
#endif