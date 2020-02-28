#pragma once

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

	bool Connect();

	void Protocol(BYTE protoNum, BYTE *aRecv, int uIndex);

	void GDReqLoad(PMSG_REQ_ACC_DATABASE_LOAD* lpMsg, int uIndex);
	void GDReqSave(PMSG_REQ_ACC_DATABASE_SAVE* lpMsg, int uIndex);

	CQuery m_MEMBQuery;
};

extern CAccountSecurity g_AccountSecurity;