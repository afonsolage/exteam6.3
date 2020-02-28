#pragma once

#include "Protocol.h"

#if(CUSTOM_ACCOUNT_SECURITY)

#define DEBUG_ACCOUNT_SECURITY	0

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

class CAccountSecurity
{
public:
		 CAccountSecurity();
		 ~CAccountSecurity();

	void Init();
	void Load();
	void BindImage();
	void DrawMain();
	void DrawWarning();
	void DrawMenu();
	void DrawSettingPC();
	void DrawOption();
	void DrawMessage();
	void DrawNumber();
	void ButtonMain(DWORD Event);
	void ButtonWarning(DWORD Event);
	void ButtonMenu(DWORD Event);
	void ButtonPC(DWORD Event);
	void ButtonOption(DWORD Event);
	void ButtonMessage(DWORD Event);
	void ButtonNumber(DWORD Event);
	void KeyboardPC(DWORD Event);
	void CGSendAccountConnect();
	void CGSendSettingPC();
	void GCRecvSettingPC(PMSG_ANS_ACC_SETTING_PC* lpMsg);
	void GCRecvAccountInfo(PMSG_REQ_ACC_INFO* lpMsg);
	void CGSendAccountOption();
	void CGSendSaveNumber();
	void GCRecvConnectLogin(PMSG_REQ_ACC_LOGIN* lpMsg);
	void SetTempData();
	void RestoreTempData();

	bool m_bEnable;

	int m_iTypeMessage;
	bool m_bCheckPCID;
	bool m_bNewSecretNumber;

	bool m_bActivePCID;
	bool m_bChangePCID;
	bool m_bOnlyMyPC;
	bool m_bTrade;
	bool m_bInventory;
	bool m_bWerehouse;
	bool m_bDisconnectFriend;
	bool m_bSellChar;

	bool m_bTempActivePCID;
	bool m_bTempChangePCID;
	char m_szTempSecretNumber[12];
	bool m_bTempOnlyMyPC;
	bool m_bTempTrade;
	bool m_bTempInventory;
	bool m_bTempWerehouse;
	bool m_bTempDisconnectFriend;
	bool m_bTempSellChar;
};

extern CAccountSecurity g_AccountSecurity;

#endif