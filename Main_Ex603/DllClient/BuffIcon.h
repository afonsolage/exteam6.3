#pragma once
// ------------------------------------------------------------------------------

#include "stdafx.h"
#include "Protocol.h"
// ------------------------------------------------------------------------------

#define WIN_DRAW_CORD(x)		 ( ( pWinWidth * x ) / 640 )
// ------------------------------------------------------------------------------
#if(USER_BUFF_ICON_EX==TRUE)

#define MAX_BUFF_INDEX	255//170
#define MAX_STATE_COUNT	 16
// ------------------------------------------------------------------------------

#define ADD_OPTION_SPEED					1
#define ADD_OPTION_ATTACK_DAMAGE			2
#define ADD_OPTION_DEFENSE					3
#define ADD_OPTION_LIFE						4
#define ADD_OPTION_MANA						5
#define ADD_OPTION_EXPERIENCE				6
#define ADD_OPTION_DROP_RATE				7
#define ADD_OPTION_SUSTENANCE				8
#define ADD_OPTION_STRENGTH					9
#define ADD_OPTION_DEXTERITY				10
#define ADD_OPTION_VITALITY					11
#define ADD_OPTION_ENERGY					12
#define ADD_OPTION_LEADERSHIP				13
#define ADD_OPTION_WRATH					14
#define ADD_OPTION_WIZARDRY					15
#define ADD_OPTION_MOBILITY					16
#define ADD_OPTION_CRITICAL_DMG				17
#define ADD_OPTION_WIZARD_DEFENSE			21
#define ADD_OPTION_MAGIC_DEFENSE			22
#define ADD_OPTION_REDUCE_DEFENSE			23
#define ADD_OPTION_REFLECT					24
#define ADD_OPTION_ATTACK_RATE				26
#define ADD_OPTION_WIZARD_DEFENSE_DURATION	28
#define ADD_OPTION_BERSERKMANA				31
#define ADD_OPTION_BERSERKLIFE				32
#define ADD_OPTION_MAGICDAMAGEMIN			33
#define ADD_OPTION_MAGICDAMAGEMAX			34
#define ADD_OPTION_ATTACK_NORMAL_DAMAGE		51
#define ADD_OPTION_MONSTER_DAMAGE_ABSORB	52
#define ADD_OPTION_LIFE_AUTO_RECOVERY		53
#define ADD_OPTION_MANA_AUTO_RECOVERY		54
#define ADD_OPTION_CRITICAL_DAMAGE			55
#define ADD_OPTION_EXCELLENT_DAMAGE			56
#define ADD_OPTION_XMASATTACK				57
#define ADD_OPTION_XMASDEFENSE				58
#define ADD_OPTION_LEVEL_BP					66
#define ADD_OPTION_LEVEL_SD					67
#define ADD_OPTION_BP						71
#define ADD_OPTION_SD						70
#define ADD_OPTION_IGNOREDEFENSE			72
#define ADD_OPTION_VITALITY_MONK			ADD_OPTION_VITALITY	//73 in original
#define ADD_OPTION_SUCCESSFULBLOCKING		74
#define SUB_OPTION_SUCCESSFULBLOCKING		75

#define ADD_OPTION_BERSAKER_DEFENCE			100
#define ADD_OPTION_BERSAKER_DAMAGE			101
// ------------------------------------------------------------------------------

enum eBuffID
{
	eAddExp		 = 1,
	eAddDamage	 = 2,
	eAddDefence  = 3,
	eAddBattle   = 4,
	eAddDrop     = 5,
	eAddDouble   = 6,
};
// -------------------------------------------------------------------------------

#if(CUSTOM_BUFF_INFO==TRUE)
struct PMSG_SEND_BUFF_ICON_EX
{
	PBMSG_HEAD2 h;
	BYTE btEffectIndex;
	char szBuffName[20];
	BYTE btEffectType[5]; 
	int iValue[5];
};
#endif

struct PMSG_SEND_BUFF_ICON
{
	PBMSG_HEAD h;	// C1:2D
	WORD wOptionType;
	WORD wEffectType;
	BYTE byEffectOption;
	int iLeftTime;
	BYTE btEffectIndex;
};
// ------------------------------------------------------------------------------

struct BUFF_DATA2
{
	BYTE Index;
	char Name[50];
	char Text[200];
};
// ------------------------------------------------------------------------------

struct BUFF_USER
{
	int Index;
	int Time;
	int MaxTime;
};
// ------------------------------------------------------------------------------

struct BUFF2_USER
{
	int Index;
	int Time;
	int MaxTime;
};
// ------------------------------------------------------------------------------

struct ExBuff
{
	int BuffIndex;
	int BuffTime;
	int BuffMaxTime;
};
// ------------------------------------------------------------------------------

struct GC_PMSG_ExBuff
{
	PBMSG_HEAD2 h;
	BYTE ExBuffCount;
	ExBuff ex_buff[MAX_STATE_COUNT];
};
// ------------------------------------------------------------------------------

struct PMSG_GC_GUILDBUFF
{
	PBMSG_HEAD2 h;
	BYTE AddExp;
	BYTE AddZen;
	BYTE AddMix;
	BYTE AddDmgDef;
};
// ------------------------------------------------------------------------------


struct PMSG_GC_QUESTBUFF
{
	PBMSG_HEAD2 h;
	WORD Count1;
	WORD Count2;
	WORD Count3;
};
// ------------------------------------------------------------------------------

class BuffIcon
{
public:
		 BuffIcon();
		 ~BuffIcon();

	void Init();
	void Load();
	bool Read(char * filename);
	void BindIcon(BYTE Index,  char* Name, char* Text);

	void Draw();
	void DrawBuffInfo(int BuffIndex, int InfoIndex, float iX, float iY, int uType);
	//void Timer();
	static unsigned int __stdcall Timer(void *Args);
	void Recv(PMSG_SEND_BUFF_ICON* DataRecv);

	void DeleteAllBuff();
	void DrawBuffInfoEx(int BuffIndex, float iX, float iY, int iTime);

	char* GetBuffName(int ID);
	char* GetAddedBuffName(int buff);

	void GC_BuffInfo(PMSG_SEND_BUFF_ICON_EX* aRecv);
	void GC_ExBuffData(GC_PMSG_ExBuff* aRecv);
	void GC_GuildBuffRecv(PMSG_GC_GUILDBUFF* aRecv);
	void GC_QuestBuffRecv(PMSG_GC_QUESTBUFF* aRecv);

	HANDLE hThread;

	int LoadBuffCount;
	int UserBuffCount;
	int User2BuffCount;

	BUFF_DATA2	DataBuff[MAX_BUFF_INDEX];
	BUFF_USER	UserBuff[MAX_STATE_COUNT];
	BUFF2_USER	UserExBuff[MAX_STATE_COUNT];
};
extern BuffIcon g_BuffIcon;
// ------------------------------------------------------------------------------
#endif