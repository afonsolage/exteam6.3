#pragma once

#include "StdAfx.h"
#include "..\\include\prodef.h"

#if(ANTI_CHEAT_PLUS==TRUE)
// ----------------------------------------------------------------------------------------------

#define CLIENT_HDD_BLOCK	TRUE


#define MAX_AH_DB		256
// ----------------------------------------------------------------------------------------------

#define AH_PLUS_PATH

enum eAH
{
	eTitleType,
	eClassType,
	eInjectType,
	eProcessType,
};
// ----------------------------------------------------------------------------------------------

enum eProtocolAHSub
{
	eAH_Config,
	eAH_Init,
	eAH_Title,
	eAH_Class,
	eAH_Inject,
	eAH_Process,
};
// ----------------------------------------------------------------------------------------------

struct PMSG_AH_SUB
{
	PBMSG_HEAD2 h;
	BYTE type;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_AH_CONFIG
{
	PBMSG_HEAD2 h;
	BYTE type;
	bool DumpActive;
	bool TitleActive;
	bool ClassActive;
	bool InjectActive;
	bool ProcessActive;
	bool EliteActive;
	bool MultiWindows;
	WORD DumpTime;
	WORD TitleTime;
	WORD ClassTime;
	WORD InjectTime;
	WORD ProcessTime;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_CheatBase
{
	PBMSG_HEAD2 h;
	BYTE type;
	char Name[64];
};
// ----------------------------------------------------------------------------------------------

struct PMST_CheaterUser
{
	PBMSG_HEAD2 h;
	BYTE Result;
	char CheatText[64];
};
// ----------------------------------------------------------------------------------------------

struct CG_PMSG_HDDKEY
{
	PBMSG_HEAD2 h;
	DWORD hdd_id;
};
// ----------------------------------------------------------------------------------------------
#if(ANTI_CHEAT_PLUS_CRC)
struct PMSG_CRCBase
{
	PBMSG_HEAD2 h;
	DWORD num;
	DWORD key;
	char path[128];
};
#endif
// ----------------------------------------------------------------------------------------------

struct BlockHDD_DATA
{
	BlockHDD_DATA()
	{
		this->hddid = 0;
	}
	DWORD hddid;
};
// ----------------------------------------------------------------------------------------------
#if(ANTI_CHEAT_PLUS_CRC)
struct CRC_DATA
{
	CRC_DATA()
	{
		this->Key = 0;
	}
	DWORD Key;
	char Path[128];
};

struct PMSG_UPDATEFILE
{
	PBMSG_HEAD2 h;
	DWORD num;
};

struct PMSG_FILESEND
{
	PBMSG_HEAD2 h;
	int Stage;
	int Size;
	char Buff[200];
};
#endif
// ----------------------------------------------------------------------------------------------

class AntiCheatPlus
{
public:
	void Init();
	void Load();
	void ReadConfig(char* File);
	void Read(int type, char* File);
	void ReadBlockHdd(char* filename);
#if(ANTI_CHEAT_PLUS_CRC)
	void ReadCRC(char* filename);
#endif

	void GC_Cheat(int UserIndex);
	void CG_Cheater(PMST_CheaterUser* aRecv, int UserIndex);
	void CG_HddSend(CG_PMSG_HDDKEY* aRecv, int UserIndex);

	void GC_Config(int UserIndex);
	void GC_Init(int UserIndex);
	void GC_Title(int UserIndex);
	void GC_Class(int UserIndex);
	void GC_Inject(int UserIndex);
	void GC_Process(int UserIndex);
	#if(ANTI_CHEAT_PLUS_CRC)
	void GC_Crc(int UserIndex);
	void CGAnsUpdateFile(PMSG_UPDATEFILE* lpMsg, int aIndex);
	#endif

	void CheckMultiWindow(int UserIndex);
	void WraitLog(char* Text);

	void CheckMaxWindow(int UserIndex);

	#if(SCANER_ITEM_DUPE)
	void RunItemDupe();
	bool CheckItemDupe(int UserIndex, int ItemSerial, int ItemPos);
	bool CheckWareDupe(int UserIndex, int ItemSerial, int WarePos);
	bool CheckItemSerial(int ItemType);
	#endif

	bool Enable;
	bool DumpActive;
	bool TitleActive;
	bool ClassActive;
	bool InjectActive;
	bool ProcessActive;
	bool EliteActive;
	bool MultiWindows;
	#if(ANTI_CHEAT_PLUS_CRC)
	bool CRCActive;
	#endif
	#if(SCANER_ITEM_DUPE)
	bool ScanItemDupeActive;
	#endif

	WORD DumpTime;
	WORD TitleTime;
	WORD ClassTime;
	WORD InjectTime;
	WORD ProcessTime;

	char TitleName[MAX_AH_DB][64];
	char ClassName[MAX_AH_DB][64];
	char InjectName[MAX_AH_DB][64];
	char ProcessName[MAX_AH_DB][64];

	int TitleCount;
	int ClassCount;
	int InjectCount;
	int ProcessCount;

	int m_EnableMaxWindow;
	int m_MaxWindow;

	std::vector<BlockHDD_DATA> blockhdd;
#if(ANTI_CHEAT_PLUS_CRC)
	std::vector<CRC_DATA> CrcData;
#endif
};
extern AntiCheatPlus g_AntiCheatPlus;
// ----------------------------------------------------------------------------------------------

#endif