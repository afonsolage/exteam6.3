#pragma once

#if(CUSTOM_ACCOUNT_SECURITY)

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
	void DrawOption();
	void DrawScan();
	void DrawCheckNumber();

	void ButtonMain(DWORD Event);
	void ButtonWarning(DWORD Event);
	void ButtonOption(DWORD Event);
	void ButtonScan(DWORD Event);
	void ButtonCheckNumber(DWORD Event);

	void GCReqOption();
	void CGAnsOption();

	bool m_bAccountStatus;
	DWORD m_dwAccountPCID;
	DWORD m_dwUserPCID;
	bool m_bOnlyMyPC;
	bool m_bTrade;
	bool m_bInventory;
	bool m_bWerehouse;
	bool m_bDisconnectFriend;
	bool m_bSellChar;
};

extern CAccountSecurity g_AccountSecurity;

#endif