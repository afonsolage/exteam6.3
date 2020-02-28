#pragma once

#include "User.h"
#include "Defines.h"
#include "PostItem.h"

//signed int __cdecl sub_4E0F10(int a1, char a2, char a3)
#define pPickUpItemInfo ((int (__cdecl *)(int a1, char a2)) 0x4E1250)

//#define oGlow					0x005CD032
//#define OriginalGlow			((signed int (__cdecl *)(DWORD, DWORD, DWORD, FRGB&, BYTE)) 0x005C2744)
//#define oSocketItems1			0x004C2CBD
//#define oSocketItems2			0x004C2CDF
//#define SocketItemOriginal	((signed int(__stdcall*)(signed int a1)) 0x4C2CEA)



//enum eItemOption
//{
//	Damage          = 80,        //-> Additional Damage +<N>
//	WizardryDamage  = 81,
//	CurseSpell      = 82,
//	Defense         = 84,        //-> Additional Defense +<N>
//	Luck			= 85,        //-> Default: 0
//	HPRecovery      = 86,
//	IncreaseDamage	= 95,        //-> Increase Damage +<N>%
//	IncreaseSpeed	= 98,        //-> Increase Attacking(Wizardry)speed +<N>
//	IgnorOpDefense	= 103,
//	ReturnAttack    = 106,        //-> Return's the enemy's attack power in <N>%
//	CompleteLife    = 107,        //-> Complete recovery of life in <N>% rate
//	CompleteMana    = 108,        //-> Complete recovery of Mana in <N>% rate
//};

namespace eItemOption
{
	enum T
	{
		Damage				= 80,		//-> Additional Damage +<N>
		WizardryDamage		= 81,
		CurseSpell			= 82,
		Defense				= 84,		//-> Additional Defense +<N>
		Luck				= 85,		//-> Default: 0
		HPRecovery			= 86,
		// ----
		LifeIncrease		= 87,		//-> Increase Max HP +4%%
		ManaIncrease		= 88,		//-> Increase Max Mana +4%%
		DamageDecrease		= 89,		//-> Damage Decrease +4%%
		Reflect				= 90,		//-> Reflect Damage +5%%
		DefenseSuccess		= 91,		//-> Defense success rate +10%%
		IncreaseZen			= 92,		//-> Increases acquisition rate of Zen after hunting monsters +30%%
		// ----
		ExcellentDamage		= 93,		//-> Excellent Damage rate +10%%
		DamageByLevel		= 94,		//-> Increase Damage +level/20
		IncreaseDamage		= 95,		//-> Increase Damage +%d%%
		IncreaseWizardry	= 96,		//-> Increase Wizardry Dmg +level/20
		IncreaseWizardryDmg = 97,		//-> Increase Wizardry Dmg +2%
		IncreaseSpeed		= 98,		//-> Increase Attacking(Wizardry)speed +%d
		LifePerMob			= 99,		//-> Increases acquisition rate of Life after hunting monsters +life/8
		ManaPerMob			= 100,		//-> Increases acquisition rate of Mana after hunting monsters +Mana/8
		IgnorOpDefense		= 103,
		ReturnAttack		= 106,		//-> Return's the enemy's attack power in <N>%
		CompleteLife		= 107,		//-> Complete recovery of life in <N>% rate
		CompleteMana		= 108,		//-> Complete recovery of Mana in <N>% rate
	};
};

struct FRGB
{
    float r, g, b;
};


class Item
{
public:
	void			Load();
	static void		LoadModels();
	static void		LoadTextures();

	//static void		Glow(DWORD dwItemId, DWORD uk1, DWORD uk2, FRGB& cl, BYTE bUkn);
	//static int		SocketItems(signed int a1);
	// ----

	bool			IsCustomJewels(WORD ItemID, bool Preview);
	bool			IsWings2_5(WORD ItemID, bool Preview);
	bool			IsWings4(WORD ItemID, bool Preview);
	bool			IsWings5(WORD ItemID, bool Preview);
	bool			IsWings6(WORD ItemID, bool Preview);

	bool			IsCustomWings(WORD ItemID, bool Preview);

	static int	_FC IsWings(LPVOID This, LPVOID EDX, DWORD ItemID);
	static bool	_FC	GetUpgradeFlag(LPVOID This, LPVOID EDX, ObjectItem * lpSource, ObjectItem * lpTarget);
	static void		PreviewCharSet(int ObjectIndex, BYTE * CharSet, lpViewObj Object, int Mode);
	static bool		AllowRepairWings(ObjectItem * lpItem);
	static void		SetOption(ObjectItem * lpItem, BYTE Option, BYTE Special, BYTE Value);
	static void		SetItemEffect(int Arg1, int ModelID, VAngle Angle, int Arg4, int ItemLevel, char Arg6, int Arg7, int Arg8, int Arg9);
	static void		SetItemEffect2(float a4, float a5, float a6, lpViewObj Object, float a8, DWORD ModelID, int a10, char a11, char a12, char a13, signed int a14, char a15);
	static short	GetMaxDurability(ObjectItem * lpItem, int ScriptStruct, int Level);

	static void Glow(DWORD dwItemId, DWORD uk1, DWORD uk2, FRGB& cl, BYTE bUkn);
	char* GetItemName(int ItemType);
	static int FixCordItemTextX(signed int a1, signed int a2, int a3, signed int a4, int a5, int a6, int a7);

	

	//void RecvPickUpItemInfo();
	//void DrawPickUpItemInfp();

	//MuObjectItemData m_PickUp;

}; extern Item gItem;
