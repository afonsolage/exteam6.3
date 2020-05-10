#pragma once

#pragma pack(push, 1)
struct VAngle
{
    float X;
    float Y;
    float Z;
};
#pragma pack(pop)

enum eEffectState
{
	AtDarkHorse		= 1,
	AtFenrir		= 4,
	AtGameMaster	= 5,
};
//---------------------------------------------------------------------------


enum eMauntType
{
	DarkHorse		= 226,
	Uniria			= 233,
	Dinorant		= 323,
	BlackFenrir		= 384,
	RedFenrir		= 385,
	BlueFenrir		= 386,
	GoldenFenrir	= 387,
};

enum ObjState // -> Complete
{
	SelectServer	= 2,
	SwitchCharacter = 4,
	GameProcess		= 5,
};

enum eClassCode // -> Complete -> Season 5.2 JPN
{
	DarkWizard 		= 0,
	SoulMaster 		= 8,
	GrandMaster		= 24,
	// ----
	DarkKnight		= 1,
	BladeKnight		= 9,
	BladeMaster		= 25,
	// ----
	Elf				= 2,
	MuseElf			= 10,
	HightElf		= 26,
	// ----
	MagicGladiator	= 3,
	DuelMaster		= 19,
	// ----
	DarkLord		= 4,
	LordEmperor		= 20,
	// ----
	Summoner		= 5,
	BloodySummoner	= 13,
	DimensionMaster	= 29,
	// ----
	Monk			= 6,
	FirstMaster		= 16,
	FirstMaster2	= 22,
};

struct PartyList //-> Complete (size: 32)
{
/*+0*/	char	Name[10];
/*+10*/	BYTE	Unknown10;
/*+11*/	BYTE	Unknown11;
/*+12*/	BYTE	MapNumber;
/*+13*/	BYTE	PosX;
/*+14*/	BYTE	PosY;
BYTE gap01;
/*+16*/	int		Life;
/*+20*/	int		MaxLife;
/*+24*/	BYTE	LifePercent;
BYTE gap02[3];
/*+28*/	int		ViewportID;
}; typedef PartyList * lpPartyList;

struct ItemAttribute
{
/*+0*/		char Name[10];	//??
/*+60*/		short ReqLevel;
};

typedef struct	//-> Complete (size: 107)
{
/*+0*/		short	ItemID;
/*+2*/		int		Level;	//int
/*+6*/		char	Unknown6;
/*+7*/		char	Unknown7;
/*+8*/		char	Unknown8;
/*+9*/		short	DamageMin;
/*+11*/		short	DamageMax;
/*+13*/		char	Unknown13;
/*+14*/		short	Unknown14;
/*+16*/		short	Unknown16;
/*+18*/		char	Unknown18;
/*+19*/		char	Unknown19;//exlnum
/*+20*/		short	Unknown20;
/*+22*/		char	Durability;
/*+23*/		char	ExcellentOption;
/*+24*/		char	AncientOption;
/*+25*/		short	ReqStrenght;
/*+27*/		short	ReqDextirity;
/*+29*/		short	ReqEnergy;
/*+31*/		short	ReqVitality;
/*+33*/		short	ReqCommand;
/*+35*/		short	ReqLevel;
/*+37*/		char    SpecialCount;
/*+38*/		WORD	SpecialType[8];
/*+54*/		BYTE	SpecialValue[8];
/*+62*/		int		UniqueID;
/*+66*/		char	Unknown66;
/*+67*/		char 	PosX;
/*+68*/		char 	PosY;
/*+69*/		WORD 	HarmonyType;
/*+71*/		short	HarmonyValue;
/*+73*/		char 	Is380Item;
/*+74*/		char	SocketOption[5];
/*+79*/		char	Unknown79;
/*+80*/		char	SocketSeedIndex[5];
/*+85*/		char	SocketSphereLevel[5];
/*+90*/		char	SocketSet;
BYTE gap01[5];
/*+96*/		char	DurabilityState;
/*+97*/		char 	PeriodItem;
/*+98*/		char 	ExpiredItem;
/*+99*/		int		ExpireDateConvert;
/*+103*/	int		Unknown103;
} ObjectItem, * lpItemObj;

struct UnknownStruct0
{
	/*+0*/	WORD	Unknown0;//?
	/*+2*/	WORD	Unknown2;//?
	/*+4*/	WORD	Unknown4;//?
	/*+6*/	WORD	Unknown6;
	/*+8*/	WORD	Unknown8;
	/*+10*/	WORD	Unknown10;
	/*+12*/	WORD	Unknown12;//?
	/*+14*/	WORD	Unknown14;
	/*+16*/	WORD	Unknown16;
};

typedef struct	//-> InDev (size: 6012)
{
/*+0*/		char	Name[11];
/*+11*/		char	Class;
/*+12*/		BYTE	Unknown12;
/*+13*/		BYTE	Unknown13;
/*+14*/		short	Level;
/*+16*/		DWORD	Experience;
/*+20*/		DWORD	NextExperience;
/*+24*/		WORD	Strength;
/*+26*/		WORD	Dexterity;
/*+28*/		WORD	Vitality;
/*+30*/		WORD	Energy;
/*+32*/		WORD	Leadership;
/*+34*/		WORD	Life;
/*+36*/		WORD	Mana;
/*+38*/		WORD	MaxLife;
/*+40*/		WORD	MaxMana;
/*+42*/		WORD	Shield;
/*+44*/		WORD	MaxShield;
/*+46*/		WORD	AttackRate;
/*+48*/		WORD	DefenseRate;
/*+50*/		short	AddStrength;
/*+52*/		short	AddDexterity;
/*+54*/		short	AddVitality;
/*+56*/		short	AddEnergy;
BYTE gap01[4];
/*+62*/		WORD	AddLeadership;	//GS use unsigned value...
/*+64*/		WORD	Stamina;
/*+66*/		WORD	MaxStamina;
/*+68*/		BYTE	ItemSpecialUseFlag;		//Bit decomposit (1, 2, 8)
BYTE UnknownGap;
/*+70*/		WORD	ItemSpecialUseTime[3];	//[ ]
/*+76*/		WORD	AddPoint;	//FruitStat start
/*+78*/		WORD	MaxAddPoint;
/*+80*/		WORD	MinusPoint;
/*+82*/		WORD	MaxMinusPoint;	//FruitStat end
/*+84*/		WORD	AttackSpeed;
/*+86*/		WORD	DamageRate;
/*+88*/		WORD	DamageMin;
/*+90*/		WORD	DamageMax;
/*+92*/		WORD	Unknown92;
/*+94*/		WORD	Unknown94;
/*+96*/		WORD	MagicSpeed;
BYTE gap02[10];
/*+108*/	WORD	Unknown108;
/*+110*/	WORD	Unknown110;
BYTE gap03[4];
/*+116*/	WORD	LevelPoint;
/*+118*/	BYTE	MagicCount;
/*+119*/	BYTE	Unknown119;
/*+120*/	WORD	pMagicList[650];	//maybe 150?
/*1420*/
BYTE gap04[3252];	//maybe preview struct some here
/*+4672*/	ObjectItem pEquipment[12];
/*+5956*/	DWORD	MoneyInventory;	//(C4)
/*+5960*/	DWORD	MoneyWarehouse;	//(C4)
BYTE gap05[8];
/*+5972*/	UnknownStruct0 Unknown5972;
BYTE gap06[2];
/*+5992*/	WORD	Unknown5992;
/*+5994*/	WORD	Unknown5994;
BYTE gap07[2];
/*+5998*/	WORD	Unknown5998;
/*+6000*/	WORD	Unknown6000;
/*+6002*/	WORD	Unknown6002;
/*+6004*/	WORD	Unknown6004;
/*+6006*/	WORD	Unknown6006;
/*+6008*/	BYTE	Unknown6008;
/*+6009*/	BYTE	Unknown6009;
/*+6010*/	BYTE	Unknown6010;
/*+6011*/	BYTE	Unknown6011;
} ObjectCharacter, * lpCharObj;

enum eSkillType
{
	SKILL_POISON = 0x1,
	SKILL_METEO = 0x2,
	SKILL_THUNDER = 0x3,
	SKILL_FIREBALL = 0x4,
	SKILL_FLAME = 0x5,
	SKILL_TELEPORT = 0x6,
	SKILL_SLOW = 0x7,
	SKILL_STORM = 0x8,
	SKILL_EVIL = 0x9,
	SKILL_HELL = 0xa,
	SKILL_POWERWAVE = 0xb,
	SKILL_FLASH = 0xc,
	SKILL_BLAST = 0xd,
	SKILL_INFERNO = 0xe,
	SKILL_TARGET_TELEPORT = 0xf,
	SKILL_MAGICDEFENSE = 0x10,
	SKILL_ENERGYBALL = 0x11,
	SKILL_BLOCKING = 0x12,
	SKILL_SWORD1 = 0x13,
	SKILL_SWORD2 = 0x14,
	SKILL_SWORD3 = 0x15,
	SKILL_SWORD4 = 0x16,
	SKILL_SWORD5 = 0x17,
	SKILL_CROSSBOW = 0x18,
	SKILL_BOW = 0x19,
	SKILL_HEALING = 0x1a,
	SKILL_DEFENSE = 0x1b,
	SKILL_ATTACK = 0x1c,
	SKILL_CALLMON1 = 0x1e,
	SKILL_CALLMON2 = 0x1f,
	SKILL_CALLMON3 = 0x20,
	SKILL_CALLMON4 = 0x21,
	SKILL_CALLMON5 = 0x22,
	SKILL_CALLMON6 = 0x23,
	SKILL_CALLMON7 = 0x24,
	SKILL_WHEEL = 0x29,
	SKILL_BLOWOFFURY = 0x2a,
	SKILL_STRIKE = 0x2b,
	SKILL_KNIGHTSPEAR = 0x2f,
	SKILL_KNIGHTADDLIFE = 0x30,
	SKILL_KNIGHTDINORANT = 0x31,
	SKILL_ELFHARDEN = 0x33,
	SKILL_PENETRATION = 0x34,
	SKILL_DEFENSEDOWN = 0x37,
	SKILL_SWORD6 = 0x38,
	SKILL_5CROSSBOW = 0x36,
	SKILL_EXPPOISON = 0x26,
	SKILL_EXPICE = 0x27,
	SKILL_EXPHELL = 0x28,
	SKILL_EXPHELL_START = 0x3a,
	SKILL_IMPROVE_AG_REFILL = 0x35,
	SKILL_DEVILFIRE = 0x32,
	SKILL_COMBO = 0x3b,
	SKILL_SPEAR = 0x3c,
	SKILL_FIREBURST = 0x3d,
	SKILL_DARKHORSE_ATTACK = 0x3e,
	SKILL_RECALL_PARTY = 0x3f,
	SKILL_ADD_CRITICALDAMAGE = 0x40,
	SKILL_ELECTRICSPARK = 0x41,
	SKILL_LONGSPEAR = 0x42,
	SKILL_RUSH = 0x2c,
	SKILL_JAVALIN = 0x2d,
	SKILL_DEEPIMPACT = 0x2e,
	SKILL_ONE_FLASH = 0x39,
	SKILL_DEATH_CANNON = 0x49,
	SKILL_SPACE_SPLIT = 0x4a,
	SKILL_BRAND_OF_SKILL = 0x4b,
	SKILL_STUN = 0x43,
	SKILL_REMOVAL_STUN = 0x44,
	SKILL_ADD_MANA = 0x45,
	SKILL_INVISIBLE = 0x46,
	SKILL_REMOVAL_INVISIBLE = 0x47,
	SKILL_REMOVAL_MAGIC = 0x48,
	SKILL_FENRIR_ATTACK = 0x4c,
	SKILL_INFINITY_ARROW = 0x4d,
	SKILL_FIRESCREAM = 0x4e,
	SKILL_EXPLOSION = 0x4f,
	SKILL_SUMMON = 0xc8,
	SKILL_IMMUNE_TO_MAGIC = 0xc9,
	SKILL_IMMUNE_TO_HARM = 0xca,
};

enum eObjectType	//-> Complete
{
	emPlayer	= 1,
	emMonster	= 2,
	emNPC		= 4,
	emNone		= 8,
};

// ----------------------------------------------------------------------------------------------

#pragma pack(push, 1)
struct ObjectModel_424
{
    float Unknown0;
    float Unknown4;
    float Unknown8;
    float Unknown12;
    float Unknown16;
    float Unknown20;
    float Unknown24;
    float Unknown28;
    float Unknown32;
    float Unknown36;
    float Unknown40;
    float Unknown44;
};
#pragma pack(pop)

//#pragma pack(push, 1)
//struct ObjectModel    //648?
//{
//BYTE gap00[4];
///*+4*/        BYTE    Visible;
//BYTE gap01[4];
///*+9*/        BYTE    Unknown9;
//BYTE gap02[5];
///*+15*/        BYTE    Unknown15;
//BYTE gap03[2];
///*+18*/        WORD    AnimationID;
///*+20*/        WORD    SubAnimationID;
///*+22*/        BYTE    Unknown22;
///*+23*/        BYTE    Unknown23;
///*+24*/        BYTE    ObjectType;
//BYTE gap04[13];
///*+38*/        WORD    Unknown38;
//BYTE gap05[8];
///*+48*/        DWORD    Unknown48;
//BYTE gap06[44];
///*+96*/        float    Scale;
//BYTE gap07[16];
///*+116*/    float    Unknown116;
//BYTE gap08[20];
///*+140*/    float    CurrentAnimationTime;
///*+144*/    float    CurrentAnimationFrame;
//BYTE gap09[56];
///*+204*/    VAngle    Unknown204;
///*+216*/    VAngle    Unknown216;
//BYTE gap10[24];
///*+252*/    float    VecPosX;
///*+256*/    float    VecPosY;
///*+260*/    float    VecPosZ;
///*+264*/    float    Unknown264;
///*+268*/    float    Unknown268;
///*+272*/    float    Unknown272;
//BYTE gap11[148];
///*+424*/    ObjectModel_424 Unknown424;
//BYTE gap12[176];
///*+484*/
//};
//#pragma pack(pop)

#pragma pack(push, 1)
struct ObjectModel	//648? 848!!
{
BYTE gap00[4];
/*+4*/	BYTE	Visible;
BYTE gap01[4];
/*+9*/	BYTE	Unknown9;
BYTE gap02[2];
/*+12*/	BYTE	Unknown12;
BYTE gap022[2];
/*+15*/	BYTE	Unknown15;
BYTE gap03[2];
/*+18*/	WORD	AnimationID;
/*+20*/	WORD	SubAnimationID;
/*+22*/	BYTE	Unknown22;
/*+23*/	BYTE	Unknown23;
/*+24*/	BYTE	ObjectType;
BYTE gap04[13];
/*+38*/	WORD	Unknown38;
BYTE gap05[8];
/*+48*/	DWORD	Unknown48;
BYTE gap06[44];
/*+96*/	float	Scale;
BYTE gap07[16];
/*+116*/	float	Unknown116;
BYTE gap08[20];
/*+140*/	float	CurrentAnimationTime;
/*+144*/	float	CurrentAnimationFrame;
BYTE gap09[56];
/*+204*/	VAngle	Unknown204;
/*+216*/	VAngle	Unknown216;
BYTE gap10[24];
/*+252*/	float	VecPosX;
/*+256*/	float	VecPosY;
/*+260*/	float	VecPosZ;
/*+264*/	float	Unknown264;
/*+268*/	float	Unknown268;
/*+272*/	float	Unknown272;
BYTE gap11[148];
/*+424*/	ObjectModel_424 Unknown424;
BYTE gap12[176];
/*+484*/
};
#pragma pack(pop)
// ----------------------------------------------------------------------------------------------


#pragma pack(push, 1)
typedef struct    //-> InDev (size: 1432)
{
BYTE gap01[14];
/*+14*/        bool    InSafeZone;
/*+15*/        BYTE    Unknown15;
/*+16*/        BYTE    Unknown16;
/*+17*/        BYTE    IsLiveObject;
/*+18*/        BYTE    Unknown18;
/*+19*/        BYTE    Class;
/*+20*/        BYTE    Unknown20;
/*+21*/        BYTE    CtlCode;    //Bit decomposit (0x10)
/*+22*/        BYTE    Unknown22;
/*+23*/        BYTE    Unknown23;
/*+24*/        BYTE    Unknown24;
/*+25*/        BYTE    Unknown25;
/*+26*/        BYTE    Unknown26;
/*+27*/        BYTE    Unknown27;
/*+28*/        BYTE    Unknown28;
/*+29*/        BYTE    Unknown29;
/*+30*/        BYTE    Unknown30;
/*+31*/        BYTE    GensInfluence;    //0 - None, 1 - D, 2 - V
/*+32*/        BYTE    PKLevel;
/*+33*/        BYTE    Unknown33;
/*+34*/        BYTE    Unknown34;
/*+35*/        BYTE    Unknown35;
/*+36*/        BYTE    Unknown36;    //Personal Shop
/*+37*/        BYTE    Unknown37;
/*+38*/        WORD    Unknown38;
/*+40*/        BYTE    Unknown40;
/*+41*/        BYTE    Unknown41;
/*+42*/        BYTE    Unknown42;
BYTE gap03[2];
/*+45*/        BYTE    RespawnPosX;
/*+46*/        BYTE    RespawnPosY;
BYTE gap04[3];
/*+50*/        BYTE    ActiveMagic;
BYTE gap05[5];
/*+56*/        char    Name[25];    //need check size
BYTE gap06[39];
/*+120*/    BYTE    Unknown120;
/*+121*/    BYTE    Unknown121;
BYTE gap07[2];
/*+124*/    WORD    Unknown124;
/*+126*/    WORD    aIndex;
/*+128*/    WORD    Unknown128;
/*+130*/    WORD    Unknown130;
/*+132*/    WORD    ID;
/*+134*/    WORD    Unknown134;
/*+136*/    //maybe word
BYTE gap09[36];
/*+172*/    DWORD    MapPosX;
/*+176*/    DWORD    MapPosY;
BYTE gap10[8];
/*+188*/    float    Unknown188;
BYTE gap11[76];
/*+268*/    short    HelmSlot;
/*+270*/    BYTE    HelmLevel;
/*+271*/    BYTE    HelmExcellent;
/*+272*/    BYTE    HelmAncient;
BYTE gap12[31];
/*+304*/    short    ArmorSlot;
/*+306*/    BYTE    ArmorLevel;
/*+307*/    BYTE    ArmorExcellent;
/*+308*/    BYTE    ArmorAncient;
BYTE gap13[31];
/*+340*/    short    PantsSlot;
/*+342*/    BYTE    PantsLevel;
/*+343*/    BYTE    PantsExcellent;
/*+344*/    BYTE    PantsAncient;
BYTE gap14[31];
/*+376*/    short    GlovesSlot;
/*+378*/    BYTE    GlovesLevel;
/*+379*/    BYTE    GlovesExcellent;
/*+380*/    BYTE    GlovesAncient;
BYTE gap15[31];
/*+412*/    short    BootsSlot;
/*+414*/    BYTE    BootsLevel;
/*+415*/    BYTE    BootsExcellent;
/*+416*/    BYTE    BootsAncient;
BYTE gap16[31];
/*+448*/    short    WeaponFirstSlot;
/*+450*/    BYTE    WeaponFirstLevel;
/*+451*/    BYTE    WeaponFirstExcellent;
/*+452*/    BYTE    WeaponFirstAncient;
BYTE gap17[31];
/*+484*/    short    WeaponSecondSlot;
/*+486*/    BYTE    WeaponSecondLevel;
/*+487*/    BYTE    WeaponSecondExcellent;
/*+488*/    BYTE    WeaponSecondAncient;
BYTE gap18[31];
/*+520*/    short    WingsSlot;
/*+522*/    BYTE    WingsLevel;
/*+523*/    BYTE    WingsExcellent;
/*+524*/    BYTE    WingsAncient;
BYTE gap19[31];
/*+556*/    short    PetSlot;
/*+558*/    BYTE    PetLevel;
/*+559*/    BYTE    PetExcellent;
/*+560*/    BYTE    PetAncient;
BYTE gap20[111];
/*+672*/    DWORD    Unknown672;
/*+676*/    DWORD    Unknown676;
BYTE gap21[84];
/*+764*/    DWORD    Unknown764;
BYTE gap22[8];
/*+776*/    ObjectModel    m_Model;
/*+1424*/    BYTE    Unknown1424;    //maybe gens rank
BYTE gap23[3];
/*+1428*/    DWORD    Unknown1428;    //-> end
} ObjectPreview, * lpViewObj;
#pragma pack(pop)
// ----------------------------------------------------------------------------------------------

#pragma pack(push, 1)
typedef struct  //-> Complete (size: 27)
{
	WORD	ObjectID;
	char	Name[25];
} NpcNameList, * lpNpcNameList;
#pragma pack(pop)


enum MAP_INDEX
{
	MAP_INDEX_RORENCIA = 0x0,
	MAP_INDEX_DUNGEON = 0x1,
	MAP_INDEX_DEVIAS = 0x2,
	MAP_INDEX_NORIA = 0x3,
	MAP_INDEX_LOSTTOWER = 0x4,
	MAP_INDEX_RESERVED = 0x5,
	MAP_INDEX_BATTLESOCCER = 0x6,
	MAP_INDEX_ATHLANSE = 0x7,
	MAP_INDEX_TARKAN = 0x8,
	MAP_INDEX_DEVILSQUARE = 0x9,
	MAP_INDEX_ICARUS = 0xa,
	MAP_INDEX_BLOODCASTLE1 = 0xb,
	MAP_INDEX_BLOODCASTLE2 = 0xc,
	MAP_INDEX_BLOODCASTLE3 = 0xd,
	MAP_INDEX_BLOODCASTLE4 = 0xe,
	MAP_INDEX_BLOODCASTLE5 = 0xf,
	MAP_INDEX_BLOODCASTLE6 = 0x10,
	MAP_INDEX_BLOODCASTLE7 = 0x11,
	MAP_INDEX_CHAOSCASTLE1 = 0x12,
	MAP_INDEX_CHAOSCASTLE2 = 0x13,
	MAP_INDEX_CHAOSCASTLE3 = 0x14,
	MAP_INDEX_CHAOSCASTLE4 = 0x15,
	MAP_INDEX_CHAOSCASTLE5 = 0x16,
	MAP_INDEX_CHAOSCASTLE6 = 0x17,
	MAP_INDEX_KALIMA1 = 0x18,
	MAP_INDEX_KALIMA2 = 0x19,
	MAP_INDEX_KALIMA3 = 0x1a,
	MAP_INDEX_KALIMA4 = 0x1b,
	MAP_INDEX_KALIMA5 = 0x1c,
	MAP_INDEX_KALIMA6 = 0x1d,
	MAP_INDEX_CASTLESIEGE = 0x1e,
	MAP_INDEX_CASTLEHUNTZONE = 0x1f,
	MAP_INDEX_DEVILSQUARE2 = 0x20,
	MAP_INDEX_AIDA = 0x21,
	MAP_INDEX_CRYWOLF_FIRSTZONE = 0x22,
	MAP_INDEX_CRYWOLF_SECONDZONE = 0x23,
	MAP_INDEX_KALIMA7 = 0x24,
	MAP_INDEX_KANTURU1 = 0x25,
	MAP_INDEX_KANTURU2 = 0x26,
	MAP_INDEX_KANTURU_BOSS = 0x27,
	MAP_INDEX_GM_SUMMONZONE = 0x28,
	MAP_INDEX_BALGASS_BARRACKS = 0x29,
	MAP_INDEX_BALGASS_REFUGEE = 0x2A,
	MAP_INDEX_ILLUSIONTEMPLE1 = 0x2D,
	MAP_INDEX_ILLUSIONTEMPLE2 = 0x2E,
	MAP_INDEX_ILLUSIONTEMPLE3 = 0x2F,
	MAP_INDEX_ILLUSIONTEMPLE4 = 0x30,
	MAP_INDEX_ILLUSIONTEMPLE5 = 0x31,
	MAP_INDEX_ILLUSIONTEMPLE6 = 0x32,
	MAP_INDEX_ELBELAND = 0x33,
	MAP_INDEX_BLOODCASTLE8 = 0x34,
	MAP_INDEX_CHAOSCASTLE7 = 0x35,
	MAP_INDEX_DEVILSQUARE7 = 0x36,
	MAP_INDEX_SWAMPOFCALMNESS = 0x38,
	MAP_INDEX_RAKLION = 0x39,
	MAP_INDEX_RAKLION_BOSS = 0x3A,
	MAP_INDEX_SANTATOWN = 0x3E,
	MAP_INDEX_VULCAN			= 0x3f,
	MAP_INDEX_VULCANROOM		= 0x40,
	MAP_INDEX_DOUBLE_GOER1 = 65,	//Season 5 DoppelGanger
	MAP_INDEX_DOUBLE_GOER2 = 66,	//Season 5 DoppelGanger
	MAP_INDEX_DOUBLE_GOER3 = 67,	//Season 5 DoppelGanger
	MAP_INDEX_DOUBLE_GOER4 = 68,	//Season 5 DoppelGanger
	MAP_INDEX_IMPERIAL1 = 69,		//Season 5 ImperialFort
	MAP_INDEX_IMPERIAL2 = 70,
	MAP_INDEX_IMPERIAL3 = 71,
	MAP_INDEX_IMPERIAL4 = 72
};