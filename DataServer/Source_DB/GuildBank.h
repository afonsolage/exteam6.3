#pragma once

#define Protocol_GSSend_GetGuildWarehouseList				0xDB
#define Protocol_GSSend_SetGuildWarehouseList				0xCB
#define Protocol_GSSend_DelGuildWarehouseList				0xDE
#define Protocol_GSRecv_GetGuildWarehouseList				0xD7
#define Protocol_GSRecv_GetWarehouseNoItem					0xC6

#define DB_MAX_VAULT_SIZE		3840

struct SDHP_GETGUILDWAREHOUSEDB
{
	PBMSG_HEAD h;	// C1:08
	char G_Name[10];
	char AccountID[10];	// 3
	short aIndex;	// E
	int Number;
};

struct SDHP_GETUSERWAREHOUSEDB_SAVE
{
	PWMSG_HEAD h;
	char AccountID[10];	// 4
	short aIndex;	// E
	int Money;	// 10
	BYTE dbItems[DB_MAX_VAULT_SIZE];	// 14
	BYTE DbVersion;	// 794
	short pw;	// 796
	int Number;
};

struct SDHP_GETGUILDWAREHOUSEDB_RESULT
{
	PBMSG_HEAD h;
	char AccountID[10];	// 3
	short aIndex;	// E
};

struct SDHP_GETGUILDWAREHOUSEDB_SAVE
{
	PWMSG_HEAD h;
	char G_Name[10];
	char AccountID[10];	// 4
	short aIndex;	// E
	int Money;	// 10
	BYTE dbItems[DB_MAX_VAULT_SIZE];	// 14
	BYTE DbVersion;	// 794
	short pw;	// 796
	int Number;
};

class CGuildBank
{
public:
	bool Connect();
	void CreateTable();
	void DGGetGuildWarehouseList(int aIndex, SDHP_GETGUILDWAREHOUSEDB * aRecv);
	void GDSetGuildWarehouseList(SDHP_GETGUILDWAREHOUSEDB_SAVE * aRecv);
	void GDDelGuildWarehouseList(SDHP_GETGUILDWAREHOUSEDB * aRecv);

	CQuery m_DBQuery;
};

extern CGuildBank g_GuildBank;