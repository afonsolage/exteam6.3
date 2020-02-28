#pragma once

#define Naked(Function)				void __declspec(naked) Function()
#define Color4f(r, b, g, o)			((o << 24) + (g << 16) + (b << 8) + r)

#define _FC							__fastcall
#define _CD							__cdecl
#define _TC							__thiscall

#define MAX_ITEMOPT_BIT				0x3F
#define GET_ITEMOPT_LEVEL(x)		((x >> 3) & 0xF)
#define GET_ITEMOPT0(x)				(x & 3)
#define GET_ITEMOPT16(x)			(x & 0x40)
#define GET_ITEMOPT_SKILL(x)		(x >> 7)
#define GET_ITEMOPT_LUCK(x)			((x >> 2) & 1)
#define GET_ITEMOPT_0(x)			(x & 1)
#define GET_ITEMOPT_1(x)			(((x & MAX_ITEMOPT_BIT) >> 1) & 1)
#define GET_ITEMOPT_2(x)			(((x & MAX_ITEMOPT_BIT) >> 2) & 1)
#define GET_ITEMOPT_3(x)			(((x & MAX_ITEMOPT_BIT) >> 3) & 1)
#define GET_ITEMOPT_4(x)			(((x & MAX_ITEMOPT_BIT) >> 4) & 1)
#define GET_ITEMOPT_5(x)			(((x & MAX_ITEMOPT_BIT) >> 5) & 1)


typedef float vec_t;
typedef vec_t vec3_t[3];	
#define Vector(a,b,c,d) {(d)[0]=a;(d)[1]=b;(d)[2]=c;}

#define MAX_SUBTYPE_ITEMS 512
#define ITEMGET(x,y) ( (x)*MAX_SUBTYPE_ITEMS + (y))

#define MAX_ITEM_INFO				12

#define DBI_TYPE			0
#define DBI_OPTION_DATA		1
#define DBI_DUR				2
#define DBI_SERIAL1			3
#define DBI_SERIAL2			4
#define DBI_SERIAL3			5
#define DBI_SERIAL4			6
#define DBI_NOPTION_DATA	7
#define DBI_SOPTION_DATA	8
#define DBI_OPTION380_DATA	9
#define DBI_JOH_DATA		10

#define CC_MAP_RANGE(value) ( ( value == MAP_INDEX_CHAOSCASTLE7 ) ? TRUE : ( value < MAP_INDEX_CHAOSCASTLE1 ) ? FALSE : ( value > MAP_INDEX_CHAOSCASTLE6) ? FALSE : TRUE )

enum eBuffEffectType
{
	AT_NULL_BUFF_EFFECT = 0,
	AT_INCREASE_ATTACK = 1,
	AT_INCREASE_DEFENSE = 2,
	AT_NPC_HELP = 3,
	AT_WIZARD_DEFENSE = 4,
	AT_INCREASE_CRITICAL_DMG = 5,
	AT_INFINITY_ARROW = 6,
	AT_INCREASE_AG_SPEED = 7,
	AT_SWELL_LIFE = 8,
	AT_SWELL_MANA = 9,
	AT_POTION_OF_BLESS = 10,
	AT_POTION_OF_SOUL = 11,
	AT_CANCEL_MAGIC = 12,
	AT_CASTLE_GATE_STATUS = 13,
	AT_WATCHING_TOWER = 14,
	AT_ATTACKING_GUILD1 = 15,
	AT_ATTACKING_GUILD2 = 16,
	AT_ATTACKING_GUILD3 = 17,
	AT_INVISIBILITY = 18,
	AT_DARK_ROD_SKILL = 19,
	AT_CASTLE_CROWN_STATUS = 20,
	AT_CW_ALTAR_ACTIVE = 21,
	AT_CW_ALTAR_INACTIVE = 22,
	AT_CW_ALTAR_STATUS = 23,
	AT_CW_ALTAR_ATTEMPT = 24,
	AT_CW_ALTAR_ATTACKING_STATUS = 25,
	AT_CW_ALTAR_HERO_STATUS = 26,
	AT_CW_NPC_TRANSPARENCY = 27,
	AT_GAMEMASTER_LOGO = 28,
	AT_PCBANG_SEAL_OF_ASCENSION = 29,
	AT_PCBANG_SEAL_OF_WEALTH = 30,
	AT_PCBANG_SEAL_OF_SUSTENANCE = 31,
	AT_ILLUSION_SPELL1 = 32,
	AT_ILLUSION_SPELL2 = 33,
	AT_ILLUSION_SHIELD_SPELL = 34,
	AT_HALLOWEEN_BLESSING = 35,
	AT_HALLOWEEN_RAGE = 36,
	AT_HALLOWEEN_SCREAM = 37,
	AT_HALLOWEEN_FOOD = 38,
	AT_HALLOWEEN_DRINK = 39,
	AT_CSHOP_SEAL_OF_ASCENSION = 40,
	AT_CSHOP_SEAL_OF_WEALTH = 41,
	AT_CSHOP_SEAL_OF_SUSTENANCE = 42,
	AT_CSHOP_SEAL_OF_MOBILITY = 43,
	AT_CSHOP_SCROLL_OF_QUICKNESS = 44,
	AT_CSHOP_SCROLL_OF_DEFENSE = 45,
	AT_CSHOP_SCROLL_OF_WRATH = 46,
	AT_CSHOP_SCROLL_OF_WIZARDRY = 47,
	AT_CSHOP_SCROLL_OF_HEALTH = 48,
	AT_CSHOP_SCROLL_OF_MANA = 49,
	AT_CSHOP_LEAP_OF_STRENGTH = 50,
	AT_CSHOP_LEAP_OF_QUICKNESS = 51,
	AT_CSHOP_LEAP_OF_HEALTH = 52,
	AT_CSHOP_LEAP_OF_ENERGY = 53,
	AT_CSHOP_LEAP_OF_CONTROL = 54,
	AT_POISON = 55,
	AT_ICE = 56,
	AT_ICE_ARROW = 57,
	AT_REDUCE_DEFENSE = 58,
	AT_REDUCE_ATTACK = 59,
	AT_REDUCE_MAGIC = 60,
	AT_STUN = 61,
	AT_MAGIC_DEFENSE = 62,
	AT_IMMUNE_MAGIC = 63,
	AT_IMMUNE_HARM = 64,
	AT_ILLUSION_RESTRICTION_SPELL = 65,
	AT_CRYWOLF_PROTECTION1 = 66,
	AT_CRYWOLF_PROTECTION2 = 67,
	AT_CRYWOLF_PROTECTION3 = 68,
	AT_CRYWOLF_PROTECTION4 = 69,
	AT_CRYWOLF_PROTECTION5 = 70,
	AT_DAMAGE_REFLECTION = 71,
	AT_SLEEP = 72,
	AT_BLIND = 73,
	AT_REQUIEM = 74,
	AT_EXPLOSION = 75,
	AT_WEAKNESS = 76,
	AT_INNOVATION = 77,
	AT_CHERRYBLOSSOM_STAMEN = 78,
	AT_CHERRYBLOSSOM_RICECAKE = 79,
	AT_CHERRYBLOSSOM_FLOWERPETAL = 80,
	AT_BERSERKER = 81,
	AT_EXPANSION_WIZARDRY = 82,
	AT_FLAME_STRIKE = 83,
	AT_GIGANTIC_STORM = 84,
	AT_LIGHTNING_SHOCK = 85,
	AT_DESTRUCTION = 86,
	AT_CSHOP_SEAL_OF_HEALING = 87,
	AT_CSHOP_SEAL_OF_DIVINITY = 88,
	AT_CSHOP_SCROLL_OF_BATTLE = 89,
	AT_CSHOP_SCROLL_OF_STRENGTHENER = 90,
	AT_XMASS_REWARD = 91,
	AT_XMASS_HEALTH = 92,
	AT_XMASS_MANA = 93,
	AT_XMASS_ATTACK = 94,
	AT_XMASS_DEFENSE = 95,
	AT_XMASS_DEXTERITY = 96,
	AT_XMASS_AG_RECOVERY = 97,
	AT_NEWPVPSYSTEM_WATCH_DUEL = 98,
	AT_CSHOP_GUARDIAN_AMULET = 99,
	AT_CSHOP_PROTECT_AMULET = 100,
	AT_CSHOP_MASTER_SEAL_OF_ASCENSION = 101,
	AT_CSHOP_MASTER_SEAL_OF_WEALTH = 102,
	AT_NEWPVPSYSTEM_REWARD = 103,
	AT_PCBANG_SEAL_OF_BALANCE = 104,

	BUFF_ASCENSION				=	105,
	BUFF_PK_PENALTY				=	106,
	BUFF_PENALTY				=	107,
	BUFF_PENALTY2				=	108,
	BUFF_PARTYEXP				=	112,
	BUFF_MAXAG					=	113,
	BUFF_MAXSD					=	114,
	BUFF_VITALITY_MINIMUM		=	115,
	BUFF_VITALITY_LOW			=	116,
	BUFF_VITALITY_MEDIUM		=	117,
	BUFF_VITALITY_HIGH			=	118,
	BUFF_SEAL_WEALTH3			=	119,
	BUFF_BAN					=	120,
	BUFF_SCROLL_HEALING			=	121,
	BUFF_IGNORE_DEFENSE			=	129,
	BUFF_INCREASE_VIT			=	130,
	BUFF_INCREASE_DEFRATE		=	131,
	BUFF_DECREASE_DEFRATE		=	132,
	BUFF_INVINCIBILITY			=	133,
	BUFF_IRONDEFENSE			=	134,
	BUFF_SWELL_LIFE2			=	135,
	BUFF_SWELL_LIFE3			=	136,
	BUFF_BLEEDING				=	137,
	BUFF_EXP_WIZARDRY2			=	138,
	BUFF_EXP_WIZARDRY3			=	139,
	BUFF_MANASHIELD2			=	140,
	BUFF_DECREASE_ATTACKSPEED	=	141,
	BUFF_BLESS					=	142,
	BUFF_INFINITY_ARROW2		=	143,
	BUFF_BLIND2					=	144,
	BUFF_VAMPIRIC				=	145,
	BUFF_FREEZE					=	146,
	BUFF_EARTHBINDS				=	147,
	BUFF_ADD_CRITDMG2			=	148,
	BUFF_ADD_CRITDMG3			=	149,
	BUFF_BERSERKER2				=	150,
	BUFF_BERSERKER3				=	151,
	BUFF_BERSERKER4				=	152,
	BUFF_INCREASE_DEFRATE2		=	153,
	BUFF_INCREASE_DEFRATE3		=	154,
	BUFF_INCREASE_VIT2			=	155,
	BUFF_IGNORE_DEFENSE2		=	156,
	BUFF_FIRE					=	157,
	BUFF_FROST					=	158,
	BUFF__POISON				=	159,
	BUFF__POISON2				=	160,
	BUFF_BLESS2					=	161,
	BUFF_WEAKNESS2				=	162,
	BUFF_INNOVATION2			=	163,
	BUFF_DECREASE_DEFRATE2		=	164,
	BUFF_IRONDEFENSE2			=	165,
	BUFF_BLOODHOWL				=	166,
	BUFF_BLOODHOWL2				=	167,
	BUFF_PENETRATE_ARMOR		=	169,
	//BUFF_FIRE2					=	174,
	//BUFF_FROST2					=	175,
	//BUFF_TORNADO				=	176,
	//BUFF_BIND					=	177,
	//BUFF_DARKNESS				=	178,
	//BUFF_FIRETOWER				=	179,
	//BUFF_WATERTOWER				=	180,
	//BUFF_EARTHTOWER				=	181,
	//BUFF_WINDTOWER				=	182,
	//BUFF_DARKNESSTOWER			=	183,
	//BUFF_RESURRECT_PENALTY		=	184,
	//BUFF_EXP_VAULT				=	185,
	//BUFF_CONFUSION				=	186,
	//BUFF_EXPREWARD				=	187,
	AT_VIP_SILVER = 171,
	AT_VIP_GOLD = 172,
	AT_VIP_PLATINUM = 173,
	AT_PARTY_EXP_BONUS_EX = 174,
	AT_GUILD_BUFF = 175,
	AT_NPC_BUFF_EXP = 176,
	AT_NPC_BUFF_DAMAGE = 177,
	AT_NPC_BUFF_DEFENCE = 178,
	AT_NPC_BUFF_EXL_CRIT = 179,
	AT_NPC_BUFF_DROP = 180,
	AT_NPC_BUFF_DOUBLE = 181,
	AT_NOOB_BUFF = 182,
	AT_QUEST_BUFF = 183,
	AT_LORABATTLE_BUFF = 184,
};