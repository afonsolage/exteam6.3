#include "stdafx.h"
#include "AccountSecurity.h"
#include "DBSockMng.h"
#include "logproc.h"
#include "ConnectEx.h"
#include "SProtocol.h"
#include "GameMain.h"
#include "ExLicense.h"
#include "VIPSystem.h"

#if(CUSTOM_ACCOUNT_SECURITY)

CAccountSecurity g_AccountSecurity;

CAccountSecurity::CAccountSecurity()
{
	this->Init();
}

CAccountSecurity::~CAccountSecurity()
{
}

void CAccountSecurity::Init()
{
	this->m_bEnable = false;
}

void CAccountSecurity::Load()
{
	this->Init();

	if(!g_ExLicense.user.AccSecurity)
	{
		return;
	}

	this->m_bEnable = GetPrivateProfileInt("ExTeam", "Enable", 0, gDirPath.GetNewPath("ExData\\AccountSecurity.ini"));

}

void CAccountSecurity::GDReqLoad(int aIndex)
{
	if(!this->m_bEnable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	PMSG_REQ_ACC_DATABASE_LOAD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEF, 0x00, sizeof(pMsg));
	pMsg.aIndex = aIndex;
	pMsg.Account[10] = 0;
	memcpy(pMsg.Account, lpUser->AccountID, sizeof(pMsg.Account)-1);
	cDBSMng.Send((char*)&pMsg, sizeof(pMsg));
}

void CAccountSecurity::DGAnsLoad(PMSG_ANS_ACC_DATABASE_LOAD* lpMsg)
{
	int aIndex = lpMsg->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->AccountSecurity.ActivePCID = lpMsg->ActivePCID;
	lpUser->AccountSecurity.ProtectPCID = lpMsg->ProtectPCID;
	lpUser->AccountSecurity.SecretNumber = lpMsg->SecretNumber;
	lpUser->AccountSecurity.OnlyMyPC = lpMsg->OnlyMyPC;
	lpUser->AccountSecurity.Trade = lpMsg->Trade;
	lpUser->AccountSecurity.Inventory = lpMsg->Inventory;
	lpUser->AccountSecurity.Werehouse = lpMsg->Werehouse;
	lpUser->AccountSecurity.DisconnectFriend = lpMsg->DisconnectFriend;
	lpUser->AccountSecurity.SellChar = lpMsg->SellChar;

#if(!DEBUG_ACCOUNT_SECURITY)

	if(this->CheckOnlyMyPC(aIndex) == false)
	{
		//GCServerMsgStringSend("[Account Security] Only Owner PC", aIndex, 0);
		//GCServerMsgStringSend("[Account Security] Only Owner PC", aIndex, 1);
		//GCJoinResult(0, aIndex);
		//gObjCloseSet(aIndex, 2);
		//Sleep(1000);
		GCCloseMsgSend(aIndex, 2);

		//CloseClient(aIndex);

		return;	
	}

	this->GCSendAccountInfo(aIndex);

#else

	this->GCReqAccountConnect(aIndex);

#endif

}

void CAccountSecurity::GDReqSave(int aIndex)
{
	if(!this->m_bEnable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	PMSG_REQ_ACC_DATABASE_SAVE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEF, 0x01, sizeof(pMsg));
	pMsg.aIndex = aIndex;
	pMsg.Account[10] = 0;
	memcpy(pMsg.Account, lpUser->AccountID, sizeof(pMsg.Account)-1);

	pMsg.ActivePCID = lpUser->AccountSecurity.ActivePCID;
	pMsg.ProtectPCID = lpUser->AccountSecurity.ProtectPCID;
	pMsg.SecretNumber = lpUser->AccountSecurity.SecretNumber;
	pMsg.OnlyMyPC = lpUser->AccountSecurity.OnlyMyPC;
	pMsg.Trade = lpUser->AccountSecurity.Trade;
	pMsg.Inventory = lpUser->AccountSecurity.Inventory;
	pMsg.Werehouse = lpUser->AccountSecurity.Werehouse;
	pMsg.DisconnectFriend = lpUser->AccountSecurity.DisconnectFriend;
	pMsg.SellChar = lpUser->AccountSecurity.SellChar;

	cDBSMng.Send((char*)&pMsg, sizeof(pMsg));
}

void CAccountSecurity::DGAnsSave(PMSG_ANS_ACC_DATABASE_SAVE* lpMsg)
{
	int aIndex = lpMsg->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if(lpMsg->Result)
	{
		this->GCSendAccountInfo(aIndex);
	}
}

void CAccountSecurity::CGRecvAccountConnect(int aIndex, PMSG_ANS_ACC_CONNECT* lpMsg)
{
	if(!this->m_bEnable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->AccountSecurity.ClientPCID = lpMsg->PCID;

#if(DEBUG_ACCOUNT_SECURITY)

	BYTE bResult = 1;

	if(this->CheckOnlyMyPC(aIndex) == true)
	{
		gObj[aIndex].UserNumber = gObj[aIndex].Join_aUserNumber;
		gObj[aIndex].DBNumber = gObj[aIndex].Join_aDBNumber;
		gObj[aIndex].Connected = PLAYER_LOGGED;
		strcpy(gObj[aIndex].LastJoominNumber, gObj[aIndex].Join_JoominNumber);
		gObj[aIndex].ukn_30 = gObj[aIndex].Join_ukn_30;
		gObj[aIndex].m_iPcBangRoom = gObj[aIndex].Join_PcBangRoom;
	}
	else
	{
		GJPAccountFail(aIndex, gObj[aIndex].AccountID, gObj[aIndex].DBNumber , gObj[aIndex].UserNumber  );
		bResult  = 5;	//5 - blocked, 7 - Connection Error
	}

	GCJoinResult(bResult , aIndex);

	if(bResult == 1)
	{
		if(gObj[aIndex].LoginMsgCount > 3)
		{
			CloseClient(aIndex);
		}

		return;
	}

	this->GCSendAccountInfo(aIndex);

#endif

}

void CAccountSecurity::CGRecvSettingPC(int aIndex, PMSG_REQ_ACC_SETTING_PC* lpMsg)
{
	if(!this->m_bEnable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	PMSG_ANS_ACC_SETTING_PC pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xB1, sizeof(pMsg));

	pMsg.Result = 0;

	if(lpUser->AccountSecurity.SecretNumber == lpMsg->SecretNumber)
	{
		pMsg.Result = 1;

		lpUser->AccountSecurity.ActivePCID = lpMsg->ActivePCID;

		if(lpMsg->ChangePCID)
		{
			lpUser->AccountSecurity.ProtectPCID = lpUser->AccountSecurity.ClientPCID;
		}
	}

	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));

	if(pMsg.Result == 1)
	{
		this->GDReqSave(aIndex);
	}
}

void CAccountSecurity::CGRecvAccountOption(int aIndex, PMSG_REQ_ACC_OPTION* lpMsg)
{
	if(!this->m_bEnable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if(!this->CheckPCID(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->AccountSecurity.OnlyMyPC = lpMsg->OnlyMyPC;
	lpUser->AccountSecurity.Trade = lpMsg->Trade;
	lpUser->AccountSecurity.Inventory = lpMsg->Inventory;
	lpUser->AccountSecurity.Werehouse = lpMsg->Werehouse;
	lpUser->AccountSecurity.DisconnectFriend = lpMsg->DisconnectFriend;
	lpUser->AccountSecurity.SellChar = lpMsg->SellChar;

	this->GDReqSave(aIndex);
}

void CAccountSecurity::CGRecvSaveNumber(int aIndex, PMSG_REQ_ACC_SAVENUMBER* lpMsg)
{
	if(!this->m_bEnable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->AccountSecurity.SecretNumber = lpMsg->SecretNumber;

	this->GDReqSave(aIndex);
}

void CAccountSecurity::GCSendAccountInfo(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	PMSG_REQ_ACC_INFO pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xB0, sizeof(pMsg));
	pMsg.ActivePCID = lpUser->AccountSecurity.ActivePCID;
	pMsg.NewSecretNumber = this->CheckNewSecretNumber(aIndex);
	pMsg.CheckPCID = this->CheckPCID(aIndex);
	pMsg.OnlyMyPC = lpUser->AccountSecurity.OnlyMyPC;
	pMsg.Trade = lpUser->AccountSecurity.Trade;
	pMsg.Inventory = lpUser->AccountSecurity.Inventory;
	pMsg.Werehouse = lpUser->AccountSecurity.Werehouse;
	pMsg.DisconnectFriend = lpUser->AccountSecurity.DisconnectFriend;
	pMsg.SellChar = lpUser->AccountSecurity.SellChar;
	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

bool CAccountSecurity::CheckNewSecretNumber(int aIndex)
{
	if(!this->m_bEnable)
	{
		return true;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->AccountSecurity.SecretNumber == 0)
	{
		return true;
	}

	return false;
}

bool CAccountSecurity::CheckPCID(int aIndex)
{
	if(!this->m_bEnable)
	{
		return true;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->AccountSecurity.ClientPCID == lpUser->AccountSecurity.ProtectPCID)
	{
		return true;
	}

	return false;
}

bool CAccountSecurity::CheckOnlyMyPC(int aIndex)
{
	if(!this->m_bEnable)
	{
		return true;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->AccountSecurity.ActivePCID == true && this->CheckPCID(aIndex) == false && lpUser->AccountSecurity.OnlyMyPC == true)
	{
		return false;	
	}

	return true;
}

bool CAccountSecurity::CheckTrade(int aIndex)
{
	if(!this->m_bEnable)
	{
		return true;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->AccountSecurity.ActivePCID == true && this->CheckPCID(aIndex) == false && lpUser->AccountSecurity.Trade == false)
	{
		GCServerMsgStringSend("[Account Security] Trade Blocked", aIndex, 0);

		return false;	
	}

	return true;
}

bool CAccountSecurity::CheckInventory(int aIndex)
{
	if(!this->m_bEnable)
	{
		return true;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->AccountSecurity.ActivePCID == true && this->CheckPCID(aIndex) == false && lpUser->AccountSecurity.Inventory == false)
	{
		GCServerMsgStringSend("[Account Security] Inventory Blocked", aIndex, 0);

		return false;	
	}

	return true;
}

bool CAccountSecurity::CheckWerehouse(int aIndex)
{
	if(!this->m_bEnable)
	{
		return true;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->AccountSecurity.ActivePCID == true && this->CheckPCID(aIndex) == false && lpUser->AccountSecurity.Werehouse == false)
	{
		GCServerMsgStringSend("[Account Security] Werehouse Blocked", aIndex, 0);

		return false;	
	}

	return true;
}

bool CAccountSecurity::CheckDisconnectFriend(int aIndex, int aFriendIndex)
{
	if(!this->m_bEnable)
	{
		return true;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->AccountSecurity.ActivePCID == true && this->CheckPCID(aIndex) == false && lpUser->AccountSecurity.DisconnectFriend == false)
	{
		GCServerMsgStringSend("[Account Security] Disconnect Friend Blocked", aFriendIndex, 0);

		return false;	
	}

	return true;
}

bool CAccountSecurity::CheckSellChar(int aIndex)
{
	if(!this->m_bEnable)
	{
		return true;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->AccountSecurity.ActivePCID == true && this->CheckPCID(aIndex) == false && lpUser->AccountSecurity.SellChar == false)
	{
		return false;	
	}

	return true;
}

bool CAccountSecurity::SelectCharacter(int aIndex)
{
	if(!this->m_bEnable)
	{
		return true;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return true;
	}

	if(this->CheckOnlyMyPC(aIndex) == false)
	{
		GCCloseMsgSend(aIndex, 2);

		return false;	
	}

	return true;
}

bool CAccountSecurity::CheckJoinLogin(int aIndex, BYTE Result, bool JoinResult)
{
	if(!this->m_bEnable)
	{
		return false;
	}

	if(Result != 1)
	{
		return false;
	}

	if(JoinResult == false)
	{
		return false;
	}

	this->GDReqLoad(aIndex);

	return true;
}

void CAccountSecurity::GCReqAccountConnect(int aIndex)
{
	PMSG_REQ_ACC_LOGIN pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xB4, sizeof(pMsg));
	pMsg.Result = true;
	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

bool CAccountSecurity::GetActivePC(int aIndex)
{
	if(!this->m_bEnable)
	{
		return false;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];

	return lpUser->AccountSecurity.ActivePCID;
}


#endif