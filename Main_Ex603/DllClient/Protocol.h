#pragma once
// ----------------------------------------------------------------------------------------------

#include "Import.h"
#include "Defines.h"
//#include "NewParty.h"

#define LOGIN			"1"
#define PASSWORD		"1"
#define MAX_WINGS_ITEM	50

struct PBMSG_HEAD
{
public:
	void set ( LPBYTE lpBuf, BYTE head, BYTE size)
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};
	void setE ( LPBYTE lpBuf, BYTE head, BYTE size)
	{
		lpBuf[0] = 0xC3;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};
	BYTE c;
	BYTE size;
	BYTE headcode;
};

struct PBMSG_HEAD2
{
public:
	void set( LPBYTE lpBuf, BYTE head, BYTE sub, BYTE size)
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
		lpBuf[3] = sub;
	};
	BYTE c;
	BYTE size;
	BYTE headcode;
	BYTE subcode;
};

struct PWMSG_HEAD	// Packet - Word Type
{
public:
	void set( LPBYTE lpBuf, BYTE head, int size)
	{
		lpBuf[0] = 0xC2;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
	};
	void setE( LPBYTE lpBuf, BYTE head, int size)	// line : 49
	{
		lpBuf[0] = 0xC4;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
	};
	BYTE c;
	BYTE sizeH;
	BYTE sizeL;
	BYTE headcode;
};

struct PWMSG_HEAD2
{
public:
	void set(LPBYTE lpBuf, BYTE head, BYTE sub, int size)
	{
		lpBuf[0] = 0xC2;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
		lpBuf[4] = sub;
	}
	BYTE c;
	BYTE sizeH;
	BYTE sizeL;
	BYTE headcode;
	BYTE subcode;
};

struct PMSG_DEFAULT2
{
	PBMSG_HEAD h;
	BYTE subcode;
};

struct PMSG_RESULT
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	BYTE result;	// 4
};

struct PMSG_JOINRESULT
{
	PBMSG_HEAD h;	// C1:F1
	BYTE scode;	// 3
	BYTE result;	// 4
	BYTE NumberH;	// 5
	BYTE NumberL;	// 6
	BYTE CliVersion[5];	// 7
};

struct PMSG_ATTACKRESULT
{
	PBMSG_HEAD h;	// C1:DC
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE DamageH;	// 5
	BYTE DamageL;	// 6
	BYTE DamageType;	// 7
	BYTE btShieldDamageH;	// 8
	BYTE btShieldDamageL;	// 9
	DWORD Life; // A
	DWORD MaxLife; // E
	DWORD AttackDamage;	//20
	DWORD iShieldDamage;//24
	DWORD SD;
	DWORD MaxSD;
};

struct PMSG_REFILL
{
	PBMSG_HEAD h;	// C1:26
	BYTE IPos;	// 3
	BYTE LifeH;	// 4
	BYTE LifeL;	// 5
	BYTE Flag;	// 6
	BYTE btShieldH;	// 7
	BYTE btShieldL;	// 8
	int Life;
	int Shield;
};

struct PMSG_MANASEND
{
	PBMSG_HEAD h;	// C1:27
	BYTE IPos;	// 3
	BYTE ManaH;	// 4
	BYTE ManaL;	// 5
	BYTE BPH;	// 6
	BYTE BPL;	// 7
	int Mana;
	int BP;
};

struct PMSG_CHARMAPJOINRESULT
{
	PBMSG_HEAD h;	// C3:F3:03
	BYTE subcode;	// 3
	BYTE MapX;	// 4
	BYTE MapY;	// 5
	BYTE MapNumber;	// 6
	BYTE Dir;	// 7

	BYTE ExpHHH; //
	BYTE ExpHHL; //
	BYTE ExpHLH; //
	BYTE ExpHLL; //
	BYTE ExpLHH; //
	BYTE ExpLHL; //
	BYTE ExpLLH; //
	BYTE ExpLLL; //

	BYTE NextExpHHH; //
	BYTE NextExpHHL; //
	BYTE NextExpHLH; //
	BYTE NextExpHLL; //
	BYTE NextExpLHH; //
	BYTE NextExpLHL; //
	BYTE NextExpLLH; //
	BYTE NextExpLLL; //

	WORD LevelUpPoint;	// 10
	WORD Str;	// 12
	WORD Dex;	// 14
	WORD Vit;	// 16
	WORD Energy;	// 18
	WORD Life;	// 1A
	WORD MaxLife;	// 1C
	WORD Mana;	// 1E
	WORD MaxMana;	// 20
	WORD wShield;	// 22
	WORD wMaxShield;	// 24
	WORD BP;	// 26
	WORD MaxBP;	// 28
	int Money;	// 2C
	BYTE PkLevel;	// 30
	BYTE CtlCode;	// 31
	short AddPoint;	// 32
	short MaxAddPoint;	// 34
	WORD Leadership;	// 36
	WORD wMinusPoint;	// 38
	WORD wMaxMinusPoint;	// 3A
	BYTE ExpandedInventoryLevel;	//0x44
	int UpPoint;
	WORD Reset;
	WORD GReset;

	DWORD dwLife;
	DWORD dwMaxLife;
	DWORD dwMana;
	DWORD dwMaxMana;
	DWORD dwShield;
	DWORD dwMaxShield;
	DWORD dwBP;
	DWORD dwMaxBP;
};

struct PMSG_LEVELUP
{
	PBMSG_HEAD h;	// C1:F3:05
	BYTE subcode;	// 3
	WORD Level;	// 4
	WORD LevelUpPoint;	// 6
	WORD MaxLife;	// 8
	WORD MaxMana;	// A
	WORD wMaxShield;	// C
	WORD MaxBP;	// E
	short AddPoint;	// 10
	short MaxAddPoint;	// 12
	short MinusPoint;	// 14
	short MaxMinusPoint;	// 16
	DWORD exUpPoint;
	DWORD exMaxLife;
	DWORD exMaxMana;
	DWORD exMaxShield;
	DWORD exMaxAG;
};

struct PMSG_LVPOINTADDRESULT
{
	PBMSG_HEAD h;	// C1:F3:06
	BYTE subcode;	// 3
	BYTE ResultType;	// 4
	WORD MaxLifeAndMana;	// 6
	WORD wMaxShield;	// 8
	WORD MaxBP;	// A
};

struct PMSG_DIEPLAYER
{
	PBMSG_HEAD h;
	BYTE NumberH;
	BYTE NumberL;
	BYTE SkillH;
	BYTE SkillL;
	BYTE KillerNumberH;
	BYTE KillerNumberL;
};

struct PMSG_KILLPLAYER
{
	PBMSG_HEAD h;
	BYTE NumberH;
	BYTE NumberL;
	BYTE ExpH;
	BYTE ExpL;
	BYTE DamageH;
	BYTE DamageL;
	DWORD Exp;
	DWORD ExDamage;
};

struct PMSG_KILLPLAYER_EXT
{
	PBMSG_HEAD h;	// C3:9C
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	WORD ExpH;	// 6
	WORD ExpL;	// 8
	BYTE DamageH;	// A
	BYTE DamageL;	// B
	DWORD ExDamage;
};

struct PMSG_DURATION_MAGIC_SEND
{
	struct PBMSG_HEAD h;
	BYTE MagicNumberH;
	BYTE MagicNumberL;
	BYTE NumberH;
	BYTE NumberL;
	BYTE X;
	BYTE Y;
	BYTE Dir;
};

struct CHAR_UPDATEINFO
{
	PBMSG_HEAD2 h;
	unsigned short	Strength;
	unsigned short	Dexterity;
	unsigned short	Vitality;
	unsigned short	Energy;
	unsigned short	Leadership;
	int		LevelUpPoint;
};

struct EXINFO_UPDATE
{
	PBMSG_HEAD2 h;
	int PremiumTime;
	int Chaos;
	int Bless;
	int Soul;
	int Life;
	float ExCred;
	int Zen;
	int WCoinC;
	int WCoinP;
	int WCoinG;
	int CreateonBank;
	int PremiumType;
	int DonateCredit;
	int GuardianBank;
	int HarmonyBank;
	int LowStoneBank;
	int HighStoneBank;
	int GemStoneBank;
	int PCPoint;
};

struct VieweCharEx
{
	short aIndex;
	int Life;
	int MaxLife;
	int SD;
	int MaxSD;
	short Level;
	short Reset;
	short GrandReset;
	short Defence;
	short Class;
	short AutoParty;
#ifdef PREM_TYPE
	int PremiumType;
#endif
	BYTE TvTTeam;
#ifdef VIEW_MONSTER
	char Name[20];
#endif
};

struct CGExUserHpBar
{
	PWMSG_HEAD2 h;
	VieweCharEx Vp[MAX_VIEWPORT];
};


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

struct GCTEventTime
{
	PBMSG_HEAD2 h;
	DWORD TimeBC;
	DWORD TimeDS;
	DWORD TimeCC;
	DWORD TimeGD;
	DWORD TimeWW;
	// --
	DWORD TimeLora;
	DWORD TimeDevias;
	DWORD TimeTvT;
	DWORD TimePandora;
	DWORD TimeEvengelion;
	DWORD TimeShop;
	DWORD TimeHappy;
	DWORD TimeDropEvent;
	// --
	DWORD TimeCryWolf;
	DWORD TimeCastleSiege;
	DWORD TimeDungeonSiege;
	DWORD TimeRedDragon;
};

struct EX_USER_COUNT
{
	PWMSG_HEAD2 h;
	BYTE count;
};

struct USER_BASE
{
	char Name[100];
	DWORD Credit;
	DWORD hdd_id;
	bool Baned;
	bool Rage;
	bool WinQuest;
	bool BloodHound;
	bool MonsterQuest;
	bool TvTEvent;	
	bool GrandHero;
	bool PartySystem;
	bool Brotherhood;
	bool PartySearch;
	bool ChatLog;
	bool GM_Manager;
	bool PerosnalStoreEx;
	bool PandoraEvent;
	bool bAntiCheatPlus;
	bool bSpotReturn;
    bool bComboCustom;
	bool bNpcBuffer;
	bool bBMQuest;
	bool bLoraBattle;
	bool bSmithy;
};

struct EX_CG_PRIVATE_USER
{
	PBMSG_HEAD2 h;
	BYTE exUser;	
	USER_BASE base;
};

#pragma pack(1)
struct PMSG_IDPASS
{
 PBMSG_HEAD h;
 BYTE subcode; // 3
 char Id[10]; // 4
 char Pass[20]; //  -> in new same as E 
 DWORD TickCount; // 18 -> in new is 0x22
 BYTE CliVersion[5]; // 1C
 BYTE CliSerial[16]; // 21 
};
#pragma pack()

struct PMSG_CHARMAPJOIN
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	char Name[10];	// 4
};

struct GC_SHOP_CLOSE	
{
	PBMSG_HEAD2 h;
	BYTE Close;
};

struct PMSG_PROTOCOL_RESULT
{
	PBMSG_HEAD2 h;
	int Result;
};

struct PMSG_SIMPLE_GUILDVIEWPORT_COUNT
{
	PWMSG_HEAD h;	// C2:65
	BYTE Count;	// 4
};

struct PMSG_SIMPLE_GUILDVIEWPORT
{
	int GuildNumber;	// 0
	BYTE btGuildStatus;	// 4
	BYTE btGuildType;	// 5
	BYTE btGuildRelationShip;	// 6
	BYTE NumberH;	// 7
	BYTE NumberL;	// 8
	BYTE btOwnerStatus; //9 season4 add-on
};

struct PMSG_DUNGEON_SYSTEM
{
	PBMSG_HEAD2 h;
	bool Show;
	int Count;
	int MaxCount;
};

struct PMSG_ITEMGETRESULT
{
	PBMSG_HEAD h;	// C1:22
	BYTE result;	// [0xFE:Money] 3
	BYTE Data[MAX_ITEM_INFO];	// 4
};

struct WING_INFO
{
	DWORD ItemType;
	DWORD Damage;
	DWORD Absord;
};

struct PMSG_WINGS_INFO
{
	PWMSG_HEAD2 h;
	WING_INFO Wing[MAX_WINGS_ITEM];
};


#if(DEV_PLAYERINFO)
struct INFOPLAYER_DATA
{
	int aIndex;
	WORD Strength;
	WORD Agility;
	WORD Vitality;
	WORD Energy;
	WORD Command;
	WORD Reset;
	WORD GReset;
	WORD PKLevel;
	BYTE Vip;
};

struct PMSG_REQ_INFOPLAYER
{
	PBMSG_HEAD2 h;
	int aIndex;
};

struct PMSG_ANS_INFOPLAYER
{
	PBMSG_HEAD2 h;
	INFOPLAYER_DATA Data;
};
#endif

#if(DEV_DAMAGE_TABLE)
struct PMSG_DAMAGE_TABLE
{
	PBMSG_HEAD2 h;
	int SecondDamage;
	int SecondDefence;
	int SecondReflect;
};
#endif

class Protocol
{
public:
	BYTE		byXorFilter[32];
	void		Load();
	// ----
	static void	DataRecv(DWORD Case, LPBYTE Data, int Len, int aIndex);
	void		DataSend(LPBYTE Data, int Size);
	void		JewelsBankRecv(EXINFO_UPDATE * aRecv);
#ifdef HPBAR_UPDATE
	void		NewExVieweport(LPBYTE aRecv);
#else
	void		NewExVieweport(CGExUserHpBar * aRecv);
#endif
	void		RecvConfig(EX_GC_CONFIG_SEND * Recv);
	void		RecvTimer(GCTEventTime * Recv);
	void		AutoLogin();
	void		AutoCharacter();

	void		GC_ShopClose(GC_SHOP_CLOSE *Recv);
	void		GCGuildInfo(LPBYTE aRecv);

	void        GCMapQuestMiniInfo(PMSG_DUNGEON_SYSTEM* aRecv);
	void		CG_AutoHP(bool State);

	#if(DEV_PLAYERINFO)
	void SendInfoPlayer();
	void RecvInfoPlayer(PMSG_ANS_INFOPLAYER* lpMsg);
	#endif
	#if(DEV_DAMAGE_TABLE)
	void RecvDamageTable(PMSG_DAMAGE_TABLE* lpMsg);
	#endif

	WING_INFO   m_Wing[MAX_WINGS_ITEM];
	// ----
}; extern Protocol gProtocol;
// ----------------------------------------------------------------------------------------------