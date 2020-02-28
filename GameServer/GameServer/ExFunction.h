#include "StdAfx.h"
#include "protocol.h"

struct EX_GC_CONFIG_SEND
{
	PBMSG_HEAD2 h;
	BYTE CharSwitch;	
	BYTE sGENS;
	short HelperLevel;
	BYTE AutoParty;
	BYTE Top100;
	BYTE EventTimer;
	BYTE MoveTargetPosEffect;
	BYTE CastleSiegeSkill;
	BYTE AntiCheat;
	BYTE GensColorEnable;
	BYTE GensColorRed;
	BYTE GensColorGreen;
	BYTE GensColorBlue;
	int MaxStats;
	BYTE DLReflect;
	BYTE MasterSkills;
	DWORD DivFireScreamSpeed;
};

void exGCConfigSend(int aIndex);
bool exCheckSimbol(char* String, int StrLen);
char * exMapName(int MapNum);
CTime StrToCTime(const char* str);
bool CheckFile(char* File);
bool CheckOptionItem(int Item1, int Item2, int iType);
void CheckAndFixMinNumber(int &Number, int MinNumber);
void CheckAndFixNumber(int &Number, int MinNumber, int MaxNumber);