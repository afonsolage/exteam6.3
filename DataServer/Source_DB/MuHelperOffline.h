#pragma once

#include ".\\DbSet\\DBConBase.h"
#include "..\include\ProDef.h"

#include <queue>

#define RESTORE_INTERVAL 200

struct MUHELPEROFF_DATA
{
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	BOOL Active;
	BOOL Offline;
};

struct MUHELPEROFF_RESTORE_DATA
{
	char AccountID[MAX_IDSTRING + 1];
	char Password[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	int	ServerIndex;
};

struct PMSG_SAVE_MUHELPEROFF_DATA
{
	PBMSG_HEAD2 h;
	MUHELPEROFF_DATA data;
};

struct PMSG_REQ_MUHELPEROFF_DATA
{
	PBMSG_HEAD2 h;
};

struct PMSG_RESTORE_DATA
{
	PBMSG_HEAD2 h;
	char AccountID[MAX_IDSTRING + 1];
	char Password[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
};

class CMUHelperOffline
{
public:
	bool	Connect();
	void	CreateTable();

	void	GDReqUpdateData(PMSG_SAVE_MUHELPEROFF_DATA* lpMsg, int uIndex);
	void	GDReqAllData(int uIndex);
	void	DGSendRestoreData(MUHELPEROFF_RESTORE_DATA data);
	void	Tick();
private:

	CQuery	m_DBQuery;
	std::queue<MUHELPEROFF_RESTORE_DATA> m_restoreStack;
	DWORD	m_nextTick;
};

extern CMUHelperOffline g_MUHelperOffline;