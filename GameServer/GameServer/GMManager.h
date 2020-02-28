#pragma once
// -------------------------------------------------------------------------------

#include "StdAfx.h"
// -------------------------------------------------------------------------------

#define MAX_GM_DATA		100
#define GM_MANAGER_DIR	"ExData\\GMManager.ini"
// -------------------------------------------------------------------------------

enum eGM_CMD
{
	egm_cmd_gg,
	egm_cmd_sellpremium,
	egm_cmd_sellcredit,
	egm_cmd_gmove,
	egm_cmd_banchar,
	egm_cmd_exreload,
	egm_cmd_banchat,
	egm_cmd_disconnect,
	egm_cmd_trace,
	egm_cmd_sendwcoin,
	egm_cmd_item,
};
// -------------------------------------------------------------------------------

struct GM_DATA
{
	int Type;
	char Name[11];
	int cmd_gg;
	int cmd_sellpremium;
	int cmd_sellcredit;
	int cmd_gmove;
	int cmd_banchar;
	int cmd_exreload;
	int cmd_banchat;
	int cmd_disconnect;
	int cmd_trace;
	int cmd_sendwcoin;
	int cmd_item;
};
// -------------------------------------------------------------------------------

class GMManager
{
public:
	GMManager();
	~GMManager();

	void Init();
	void Load();
	void Read(char* File);

	bool CheckCommand(int aIndex, int cmd_type);
	void ConnectAdmin(int aIndex);

	bool Enable;

	GM_DATA		gm_data[MAX_GM_DATA];
	int GMCount;
};
extern GMManager g_GMManager;
// -------------------------------------------------------------------------------