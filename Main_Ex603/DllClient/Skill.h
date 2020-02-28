#pragma once

#include "Protocol.h"

//#define sub_5509C0			((int(*)())0x5509C0)	
//#define sub_542310			((__int16(__cdecl*)(int a1, int a2, char a3))0x542310)
//#define sub_6D6AD0			((int(__cdecl*)(int a1, int a2, int a3))0x6D6AD0)	
//#define sub_6D8F20			((int(__cdecl*)(int, int, int, int, int, int, __int16, __int16, __int16, __int16, float, __int16)) 0x6D8F20)

#define sub_5509C0			((int(*)())0x5509C0)	
#define sub_542310			((__int16(__cdecl*)(ObjectModel* a1, int a2, char a3))0x542310)
#define sub_6D6AD0			((int(__cdecl*)(int a1, int a2, int a3))0x6D6AD0)	
#define sub_6D8F20			((int(__cdecl*)(int, int, int, int, int, int, __int16, __int16, __int16, __int16, float, __int16)) 0x6D8F20)

// -> Mana shield 
//#define sub_552710			((int(__cdecl*)(int a1))0x552710)	
#define sub_552710			((int(__cdecl*)(lpViewObj a1))0x552710)	

// -> Meteorit
//#define sub_5518F0	((int(__cdecl*)(int a1))0x5518F0)
#define sub_5518F0	((int(__cdecl*)(lpViewObj a1))0x5518F0)

// -> Rand
//int sub_9CFA0D()
#define GetLargeRand	((int(__cdecl*)())0x9CFA0D)

//signed int __cdecl sub_645BA0(unsigned __int8 *a1, int a2, int a3)
#define sub_645BA0			((int(__cdecl*)(unsigned __int8 *a1, int a2, int a3))0x645BA0)	
//signed int __cdecl sub_57D9A0(int a1)
#define sub_57D9A0			((int(__cdecl*)(int a1))0x57D9A0)	


struct PMSG_MAGICATTACK
{
	PBMSG_HEAD h;
	BYTE MagicNumberH;	// 3
	BYTE MagicNumberL;	// 4
	BYTE NumberH;	// 5
	BYTE NumberL;	// 6
	BYTE Dis;	// 7
};

struct PMSG_MAGICATTACK_RESULT
{
	PBMSG_HEAD h;	// C3:19
	BYTE MagicNumberH;	// 3
	BYTE MagicNumberL;	// 4
	BYTE SourceNumberH;	// 5
	BYTE SourceNumberL;	// 6
	BYTE TargetNumberH;	// 7
	BYTE TargetNumberL;	// 8
};

class CSkill
{
public:
		 CSkill();
		 ~CSkill();

	void Load();
	static int LoadSkill();


	static int GCMagicAttack(unsigned __int8 *a1, int a2, int a3);
	void ManaShield();
	static void TeleportSkill(ObjectModel* lpModel1);
	static void ExpansionSkill(ObjectModel* lpModel);
	static void MeteoritSkill(lpViewObj lpObj1, ObjectModel* ObjectModel1);
	static void MeteorStorm(lpViewObj lpObj1);
};

extern CSkill g_Skill;