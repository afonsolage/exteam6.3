#pragma once

#include "Protocol.h"

#if(CUSTOM_ACCOUNT_SECURITY)

#define DEBUG_ACCOUNT_SECURITY	0

// GS <-> CL

struct PMSG_ANS_ACC_CONNECT
{
	PBMSG_HEAD2 h;
	DWORD PCID;
};

struct PMSG_REQ_ACC_SETTING_PC
{
	PBMSG_HEAD2 h;
	BYTE ActivePCID;
	BYTE ChangePCID;
	DWORD SecretNumber;
};

struct PMSG_REQ_ACC_OPTION
{
	PBMSG_HEAD2 h;
	BYTE OnlyMyPC;
	BYTE Trade;
	BYTE Inventory;
	BYTE Werehouse;
	BYTE DisconnectFriend;
	BYTE SellChar;
};

struct PMSG_ANS_ACC_SETTING_PC
{
	PBMSG_HEAD2 h;
	BYTE Result;
};

struct PMSG_REQ_ACC_INFO
{
	PBMSG_HEAD2 h;
	BYTE ActivePCID;
	BYTE NewSecretNumber;
	BYTE CheckPCID;
	BYTE OnlyMyPC;
	BYTE Trade;
	BYTE Inventory;
	BYTE Werehouse;
	BYTE DisconnectFriend;
	BYTE SellChar;
};

struct PMSG_REQ_ACC_SAVENUMBER
{
	PBMSG_HEAD2 h;
	DWORD SecretNumber;
};

struct PMSG_REQ_ACC_LOGIN
{
	PBMSG_HEAD2 h;
	BYTE Result;
};

// GS <-> DS

struct PMSG_REQ_ACC_DATABASE_LOAD
{
	PBMSG_HEAD2 h;
	WORD aIndex;
	char Account[11];
};

struct PMSG_ANS_ACC_DATABASE_LOAD
{
	PBMSG_HEAD2 h;
	WORD aIndex;
	BYTE Result;
	BYTE ActivePCID;
	DWORD ProtectPCID;
	DWORD SecretNumber;
	BYTE OnlyMyPC;
	BYTE Trade;
	BYTE Inventory;
	BYTE Werehouse;
	BYTE DisconnectFriend;
	BYTE SellChar;
};

struct PMSG_REQ_ACC_DATABASE_SAVE
{
	PBMSG_HEAD2 h;
	WORD aIndex;
	char Account[11];
	BYTE ActivePCID;
	DWORD ProtectPCID;
	DWORD SecretNumber;
	BYTE OnlyMyPC;
	BYTE Trade;
	BYTE Inventory;
	BYTE Werehouse;
	BYTE DisconnectFriend;
	BYTE SellChar;
};

struct PMSG_ANS_ACC_DATABASE_SAVE
{
	PBMSG_HEAD2 h;
	WORD aIndex;
	BYTE Result;
};

class CAccountSecurity
{
public:
		 CAccountSecurity();
		 ~CAccountSecurity();

	void Init();
	void Load();
	void GDReqLoad(int aIndex);
	void DGAnsLoad(PMSG_ANS_ACC_DATABASE_LOAD* lpMsg);
	void GDReqSave(int aIndex);
	void DGAnsSave(PMSG_ANS_ACC_DATABASE_SAVE* lpMsg);
	void CGRecvAccountConnect(int aIndex, PMSG_ANS_ACC_CONNECT* lpMsg);
	void CGRecvSettingPC(int aIndex, PMSG_REQ_ACC_SETTING_PC* lpMsg);
	void CGRecvAccountOption(int aIndex, PMSG_REQ_ACC_OPTION* lpMsg);
	void CGRecvSaveNumber(int aIndex, PMSG_REQ_ACC_SAVENUMBER* lpMsg);
	void GCSendAccountInfo(int aIndex);
	bool CheckNewSecretNumber(int aIndex);
	bool CheckPCID(int aIndex);
	bool CheckOnlyMyPC(int aIndex);
	bool CheckTrade(int aIndex);
	bool CheckInventory(int aIndex);
	bool CheckWerehouse(int aIndex);
	bool CheckDisconnectFriend(int aIndex, int aFriendIndex);
	bool CheckSellChar(int aIndex);
	bool SelectCharacter(int aIndex);
	bool CheckJoinLogin(int aIndex, BYTE Result, bool JoinResult);
	void GCReqAccountConnect(int aIndex);
	bool GetActivePC(int aIndex);

	bool m_bEnable;

	bool m_AccProtectPC;
	DWORD m_AccPCID;
	DWORD m_AccSecretNumber;
	bool m_AccOnlyMyPC;
	bool m_AccTrade;
	bool m_AccInventory;
	bool m_AccWerehouse;
	bool m_AccDisconnectFriend;
	bool m_AccSellChar;
};

extern CAccountSecurity g_AccountSecurity;

#endif