#pragma once

#define ExclusiveOptions_DIR "..\\Data\\ExData\\ExclusiveOptions.ini"
#define MAX_Excl_OPT	200

/*
	0 - Damage
	1 - MinDefence
	2 - IgnoreDefence
	3 - CriticalDamageRate
	4 - ExellentDamageRate
	5 - DoubleDamage
	6 - AbsordDamage
	7 - ReflectDamage
	8 - SD
	9 - Life
	10 - Wizard Damage
	11 - Exp
	12 - Zen
*/

enum eExclusiveOpt
{
	Damage, 
	MinDefence,
	IgnoreDefence,
	CriticalDamageRate,
	ExellentDamageRate,
	DoubleDamage,
	AbsordDamage,
	ReflectDamage,
	SD,
	Life,
	WizardDamage, 
	Exp, //%
	Zen, //%
};

struct Exclusive_DATA
{
	short Type;
	short Index;
	short Options;
	int Value;
};

struct ExclusiveInv_DATA
{
	short Type;
	short Index;
	short Options;
	int Value;
};
#ifdef EXCLUSIVE_AMYLET
struct ExclusiveInvTime_DATA
{
	short Type;
	short Index;
	short Options;
	int Value;
};
#endif
class cExclusiveOptions
{
private:
	bool Enable;


	Exclusive_DATA		Exclusive[MAX_Excl_OPT];
	ExclusiveInv_DATA	ExclusiveInv[MAX_Excl_OPT];
#ifdef EXCLUSIVE_AMYLET
	ExclusiveInvTime_DATA	ExclusiveInvTime[10];
	int CountInvTime;
#endif

	int Count;
	int CountInv;
public:

	void Load();

	void Options(int aIndex);

	void DropZen (int aIndex, float & money);
	void ExpFunction(int aIndex, __int64 & exp);
#ifdef EXCLUSIVE_AMYLET
	void TickTime(int aIndex);
#endif
};
extern cExclusiveOptions gExclusiveOptions;