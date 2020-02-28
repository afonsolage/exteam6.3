#pragma once

#if(DEV_GUILDBANK)

#define Protocol_GSSend_GetGuildWarehouseList				0xDB
#define Protocol_GSSend_SetGuildWarehouseList				0xCB
#define Protocol_GSSend_DelGuildWarehouseList				0xDE
#define Protocol_GSRecv_GetGuildWarehouseList				0xD7
#define Protocol_GSRecv_GetWarehouseNoItem					0xC6

struct SDHP_GETGUILDWAREHOUSEDB
{
	PBMSG_HEAD h;	// C1:08
	char G_Name[10];
	char AccountID[10];	// 3
	short aIndex;	// E
	int Number;	
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

struct PMSG_GUILD_BANK
{
	PBMSG_HEAD h;
	BYTE Result;
};

class CGuildBank
{
public:
	void Load();
	void Read(char* filename);
	void GDGetGuildWarehouseList(int aIndex);
	void GDDelGuildWarehouseList(int aIndex);
	void GDSetGuildWarehouseList(int aIndex);
	bool WarehousePassword(int aIndex);
	void CGOpenGuildWarehouse(PMSG_GUILD_BANK* lpMsg, int aIndex);
	void ClearWarehouse(int aIndex);

	int m_iEnable;
	int m_iGuildBankMap;
	int m_iGuildBankX;
	int m_iGuildBankY;
};

extern CGuildBank g_GuildBank;





#endif