#ifndef GMMNG_H
#define GMMNG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_GM_COMMAND 700
#define MAX_GMCOMMAND_LEN 20
#define MAX_GAME_MASTER 5

enum COMMANDS
{
	CMD_DISCONNECT = 100,
	CMD_MOVE,

	CMD_GUILD_MOVE = 108,
	CMD_WAR_START,
	CMD_WAR_STOP,
	CMD_WAR_END,
	CMD_GUILD_END,

	CMD_WAR = 200,
	CMD_SOCCER,
	CMD_REQUEST,

	CMD_USER_STATS = 214,
	CMD_TRACE,
	CMD_MONITORING,

#if(GS_CASTLE == 1)
	CMD_CS_CHANGE_OWNER = 331,
	CMD_CS_REG_SIEGE,
	CMD_CS_REG_MARK,
	CMD_CS_NOTIFY,
	CMD_CS_START,
	CMD_CS_END,
	CMD_CS_CUR_OWNER,
	CMD_CS_CUR_STATE,
	CMD_CS_CHANGE_SIDE,

	CMD_CRYWOLF_NOTIFY = 345, 
	CMD_CRYWOLF_READY,
	CMD_CRYWOLF_START,
	CMD_CRYWOLF_END,
#endif

	CMD_HIDE_ON = 390,
	CMD_HIDE_OFF,

	CMD_DS_OPEN,
	CMD_DS_START,
	CMD_DS_END,

	CMD_BC_OPEN,
	CMD_BC_START,
	CMD_BC_END,

	CMD_CC_OPEN,
	CMD_CC_START,
	CMD_CC_END,

	CMD_DSIEGE_OPEN,
	CMD_DSIEGE_START,
	CMD_DSIEGE_END,

	CMD_ABILITY = 501,
	CMD_PARTY,
	CMD_SUMMON_MONSTER,
	CMD_CLEAR_MONSTER,
	CMD_CLEAR_ITEM,
	CMD_CLEAR_INVENTORY,
	CMD_SUMMON_CHAR,

	CMD_GMOVE = 600,
	CMD_PARTY_LEADER = 602,

	CMD_BAN_CHAT = 604,
	CMD_BAN_POST,
	CMD_BAN_CHAR,
	CMD_BAN_ALLCHAT,
	CMD_UNBAN_CHAT,
	CMD_UNBAN_POST,
	CMD_UNBAN_ALLCHAT,
	CMD_UNBAN_CHAR,

	CMD_ITEM = 659
};

#include "user.h"

struct BAN_CHAR_GS
{
	PBMSG_HEAD2 h;
	BYTE Result;
	BYTE Type;
	int aIndex;
	char Name[11];
};


class CGMCommand
{

public:


	CGMCommand()
	{
		this->Init();
	}

	void Init()
	{
		for ( int n = 0; n<  MAX_GM_COMMAND; n++ )
		{
			this->nCmdCode[0] = -1;
		}

		this->count=0;
	}

	void Add(LPSTR command_str, int command_code,int gamemaster_code) 
	{
		strcpy(this->szCmd[this->count], command_str);
		this->nCmdCode[this->count]=command_code;
		this->nGMCode[this->count]=gamemaster_code | 0x02 | 0x20 | 0x40;//Season 4.5 changed

		if ( this->count < MAX_GM_COMMAND-1 )
		{
			this->count++;
		}
	}


public:
	
	char szCmd[MAX_GM_COMMAND][MAX_GMCOMMAND_LEN];
	int nCmdCode[MAX_GM_COMMAND];
	int nGMCode[MAX_GM_COMMAND];
	int count;
};



class CGMMng
{

public:

	CGMMng();
	virtual ~CGMMng();

	void Init();
	int GetCmd(LPSTR szCmd);
	BYTE GetData(char *szCmd,int &command_code,int &gamemaster_code);
	int ManagementProc(LPOBJ lpObj, LPSTR szCmd, int aIndex);
	LPSTR GetTokenString();
	int GetTokenNumber();
	void GetInfinityArrowMPConsumption(LPOBJ lpObj);
	void ControlInfinityArrowMPConsumption0(LPOBJ lpObj, int iValue);
	void ControlInfinityArrowMPConsumption1(LPOBJ lpObj, int iValue);
	void ControlInfinityArrowMPConsumption2(LPOBJ lpObj, int iValue);
	void ControlInfinityArrowMPConsumption3(LPOBJ lpObj, int iValue);
	void SetInfinityArrowTime(LPOBJ lpObj, int iValue);
	void ControlFireScreamDoubleAttackDistance(LPOBJ lpObj, int iValue);
	void ManagerInit();
	int  ManagerAdd(LPSTR name, int aIndex);
	void ManagerDel(LPSTR name);
	void ManagerSendData(LPSTR szMsg, int size);
	void BattleInfoSend(LPSTR Name1, BYTE score1, LPSTR Name2, BYTE score2);
	void DataSend(LPBYTE szMsg, int size);

	void CmdAbility(LPOBJ lpObj,char *szName);
	void CmdParty(LPOBJ lpObj,char *szName);
	void CmdSummonMonster(LPOBJ lpObj,int MonsterClass,int MonsterCount);
	void CmdClearMonster(LPOBJ lpObj,int Dis);
	void CmdClearItem(LPOBJ lpObj,int Dis);
	void CmdClearInven(LPOBJ lpObj);
	void CmdSummonChar(LPOBJ lpObj,char * szName);
	int GetType(WORD wClass);
#if(CUSTOM_MULTIWAREHOUSE)
	void CmdWare(LPOBJ lpObj, int number);
#endif
private:

	CGMCommand cCommand;
	char szManagerName[MAX_GAME_MASTER][11];
	int ManagerIndex[MAX_GAME_MASTER];

public:

	int WatchTargetIndex;
};

extern CGMMng cManager;

#endif