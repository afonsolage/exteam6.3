#pragma once
#include "Stdafx.h"
#include "Item.h"

#if(exPRIVIEWESET)

#define pVisible(x)						*(BYTE*)(x + 15)
#define pPlayerClass(x)					*(BYTE*)(x + 19)
#define pAncientEffect(x)				*(BYTE*)(x + 22)
#define pAtEffect(x)					*(BYTE*)(x + 23)
#define pHelmSlot(x)					*(WORD*)(x + 232)
#define pHelmSetLevel(x)				*(BYTE*)(x + 234)
#define pHelmSetExcellent(x)			*(BYTE*)(x + 235)
#define pHelmSetAncient(x)				*(BYTE*)(x + 236)
#define pArmorSlot(x)					*(WORD*)(x + 264)
#define pArmorSetLevel(x)				*(BYTE*)(x + 266)
#define pArmorSetExcellent(x)			*(BYTE*)(x + 267)
#define pArmorSetAncient(x)				*(BYTE*)(x + 268)
#define pPantsSlot(x)					*(WORD*)(x + 296)
#define pPantsSetLevel(x)				*(BYTE*)(x + 298)
#define pPantsSetExcellent(x)			*(BYTE*)(x + 299)
#define pPantsSetAncient(x)				*(BYTE*)(x + 300)
#define pGlovesSlot(x)					*(WORD*)(x + 328)
#define pGlovesSetLevel(x)				*(BYTE*)(x + 330)
#define pGlovesSetExcellent(x)			*(BYTE*)(x + 331)
#define pGlovesSetAncient(x)			*(BYTE*)(x + 332)
#define pBootsSlot(x)					*(WORD*)(x + 360)
#define pBootsSetLevel(x)				*(BYTE*)(x + 362)
#define pBootsSetExcellent(x)			*(BYTE*)(x + 363)
#define pBootsSetAncient(x)				*(BYTE*)(x + 364)
#define pWeaponFirstSlot(x)				*(WORD*)(x + 392)
#define pWeaponFirstSetLevel(x)			*(BYTE*)(x + 394)
#define pWeaponFirstSetExcellent(x)		*(BYTE*)(x + 395)
#define pWeaponFirstSetAncient(x)		*(BYTE*)(x + 396)
#define pWeaponSecondSlot(x)			*(WORD*)(x + 424)
#define pWeaponSecondSetLevel(x)		*(BYTE*)(x + 426)
#define pWeaponSecondSetExcellent(x)	*(BYTE*)(x + 427)
#define pWeaponSecondSetAncient(x)		*(BYTE*)(x + 428)
#define pWingsSlot(x)					*(WORD*)(x + 456)
#define pSetUnknown1(x)					*(BYTE*)(x + 458)
#define pSetUnknown2(x)					*(BYTE*)(x + 459)
#define pSetUnknown3(x)					*(BYTE*)(x + 460)
#define pPetSlot(x)						*(WORD*)(x + 488)
#define pSetUnknown4(x)					*(BYTE*)(x + 490)
#define pFenrirCharSet(x)				*(BYTE*)(x + 491)
#define pExpectPet(x)					*(BYTE*)(x + 492)
#define pObjAction(x)					*(BYTE*)(x + 718)
#define pObjScale(x)					*(DWORD*)(x + 796)
#define pObjSelectZone(x)				*(float*)(x + 924)
#define pGetPosition(x)					*(WORD*)(x + 952)
//--------------------------------------------------------------------------


#define LODWORD(h)				((DWORD)(__int64(h) & __int64(0xffffffff)))
// ----
#if(v103K)
#define CS_START                1236
#endif
#if(v103Y)
#define CS_START                1304
#endif
// ----
#define CS_EMPTY_SLOT			-1
#define CS_EMPTY_ITEM			511
#define CS_EMPTY_WEAPON			4095
// ----
#define	CS_SET_1(x)				( x >> 2)
// ----

#if(v103K)
#define CS_HELM					9036
#endif
#if(v103Y)
#define CS_HELM					9089	
#endif

#define CS_ARMOR				CS_HELM + 20
#define CS_PANTS				CS_ARMOR + 20
#define CS_GLOVES				CS_PANTS + 20
#define CS_BOOTS				CS_GLOVES + 20
// ----
#define CS_GET_STRUCT(x, y)		(CS_START * x + *(int*)y)
#define CS_GET_WEAPON(x, y)		( y | (16 * (x & 0xF0)) )
#define CS_GET_HELM(x, y, z)	( (32 * (z & 0xF)) + 16 * ((x >> 7) & 1) + (y >> 4) )
#define CS_GET_ARMOR(x, y, z)	( (32 * ((z >> 4) & 0xF)) + 16 * ((x >> 6) & 1) + (y & 0xF) )
#define CS_GET_PANTS(x, y, z)	( (32 * (z & 0xF)) + 16 * ((x >> 5) & 1) + (y >> 4) )
#define CS_GET_GLOVES(x, y, z)	( (32 * ((z >> 4) & 0xF)) + 16 * ((x >> 4) & 1) + (y & 0xF) )
#define CS_GET_BOOTS(x, y, z)	( (32 * (z & 0xF)) + 16 * ((x >> 3) & 1) + (y >> 4) )
//---------------------------------------------------------------------------

#if(v103K)
#define gIsChaosCastle			((bool(__cdecl*)(int MapNumber)) 0x490280)
#define gItemCharSetConvert		((WORD(__cdecl*)(BYTE Pointer)) 0x504A69)
#define gAmpersandConvert		((BYTE(__cdecl*)(BYTE Pointer)) 0x45A030)
#define mObjMakePreviewCharSet	((int(__cdecl*)(int a1, BYTE * CharSet, int a3, int a4)) 0x4FDFE0)
#define sub_49A50A				((int(__cdecl*)(int Arg1)) 0x49033A)
#define sub_514A21				((int(__cdecl*)(int Arg1)) 0x4FC216)
#define gCheckPetStatus			((int(__cdecl*)(int Arg1)) 0x4997AD)
#define gReturnPetSlot			((int(__cdecl*)(int Arg1)) 0x4ABEB0)
#define gSetObjMaunt			((int(__cdecl*)(int MauntCode, int Arg2, int Arg3, int Arg4, int Arg5)) 0x4AC2C4)
#define gSetObjMaunt2			((bool(__cdecl*)(int Arg1, int Arg2, int Arg3, int Arg4, int Arg5)) 0x4ABF7C)
#define gObjPetGetThis			((LPVOID(__cdecl*)(void)) 0x81AB71)
#define gSetObjPetReset			((void(__thiscall*)(LPVOID This, int Arg1, int Arg2, int Arg3)) 0x81BDA7)
#define gSetObjPetOnSwitch		((void(__thiscall*)(LPVOID This, int Arg1, int Arg2, int Arg3, int Arg4, int Arg5, int Arg6)) 0x81BA70)
#define sub_4ADABB				((int(__cdecl*)(int Arg1)) 0x4A3820)
#define gObjPreviewDarkRaven	((int(__cdecl*)(int Arg1)) 0x4A2AD6)
#define dword_7B65114			0x7A723B8
#define dword_7BA6278			0x7AB3518
#define dword_7B650F8			0x7A7239C
#endif
#if(v103Y)
#define gIsChaosCastle			((bool(__cdecl*)(int MapNumber)) 0x49A450)	//Done
#define gItemCharSetConvert		((WORD(__cdecl*)(BYTE Pointer)) 0x51C4EC)	//Done
#define gAmpersandConvert		((BYTE(__cdecl*)(BYTE Pointer)) 0x463890)	//Done
#define mObjMakePreviewCharSet	((int(__cdecl*)(int a1, BYTE * CharSet, int a3, int a4)) 0x51564C)	//Done
#define sub_49A50A				((int(__cdecl*)(int Arg1)) 0x49A50A)	//Done
#define sub_514A21				((int(__cdecl*)(int Arg1)) 0x514A21)	//Done
#define gCheckPetStatus			((int(__cdecl*)(int Arg1)) 0x4A3A7D)	//Done
#define gReturnPetSlot			((int(__cdecl*)(int Arg1)) 0x4B6740)	//Done
#define gSetObjMaunt			((int(__cdecl*)(int MauntCode, int Arg2, int Arg3, int Arg4, int Arg5)) 0x4B6B54)	//Done
#define gSetObjMaunt2			((bool(__cdecl*)(int Arg1, int Arg2, int Arg3, int Arg4, int Arg5)) 0x4B680C)	//Done
#define gObjPetGetThis			((LPVOID(__cdecl*)(void)) 0x8831F1)	//Done
#define gSetObjPetReset			((void(__thiscall*)(LPVOID This, int Arg1, int Arg2, int Arg3)) 0x88457C)	//Done
#define gSetObjPetOnSwitch		((void(__thiscall*)(LPVOID This, int Arg1, int Arg2, int Arg3, int Arg4, int Arg5, int Arg6)) 0x884245)	//Done
#define sub_4ADABB				((int(__cdecl*)(int Arg1)) 0x4ADABB)	//Done
#define gObjPreviewDarkRaven	((int(__cdecl*)(int Arg1)) 0x4ACDA6)	//Done
#define dword_7B65114			0x7B65114	//Done
#define dword_7BA6278			0x7BA6278	//Done
#define dword_7B650F8			0x7B650F8	//Done
#endif
//---------------------------------------------------------------------------

#if(v103K)
#define oMakePreviewCharSet		0x0046D96B
#define oMakePreviewCharSet2	0x00611613
#define oMakePreviewCharSet3	0x006177F5
#define oMakePreviewCharSet4	0x006182D0
#define oMakePreviewCharSet5	0x006188B6
#define oMakePreviewCharSet6	0x0063D4FC
#define oMakePreviewCharSet7	0x00640572
#define oMakePreviewSoldierElf	0x005025B8
#endif
#if(v103Y)
#define oMakePreviewCharSet		0x0047797F
#define oMakePreviewCharSet2	0x006317A3
#define oMakePreviewCharSet3	0x00637C15
#define oMakePreviewCharSet4	0x00638702
#define oMakePreviewCharSet5	0x00638CF3
#define oMakePreviewCharSet6	0x0065EDCC
#define oMakePreviewCharSet7	0x00663A57
#define oMakePreviewSoldierElf	0x00519CCF
#endif
//---------------------------------------------------------------------------


struct Preview
{
	BYTE	Shift1[14];

	/*4*/	//BYTE	Unknown4;	// -> 100%
	/*8*/	//DWORD	Unknown8;	// -> 100%

	/*14*/	BYTE	IsSafeZone;
	/*15*/	BYTE	Visible;
	/*16*/	BYTE	Unknown16;
	/*17*/	BYTE	IsLiveObject;
	/*18*/	BYTE	Unknown18;
	/*19*/	BYTE	Class;
	/*20*/	BYTE	Unknown20;
	/*21*/	BYTE	CtrlCode;
	/*22*/	BYTE	AncientEffect;
	/*23*/	BYTE	PetStatus;
	/*24*/	BYTE	Unknown24;
	/*25*/	BYTE	Unknown25;
	/*26*/	BYTE	Unknown26;
	/*27*/	BYTE	Unknown27;
	/*28*/	BYTE	Unknown28;
	/*29*/	BYTE	Unknown29;
	/*30*/	BYTE	Unknown30;
	/*31*/	BYTE	Unknown31;
	/*32*/	BYTE	PKLevel;
	/*33*/	BYTE	Unknown33;
	/*34*/	BYTE	Unknown34;
	/*35*/	BYTE	Unknown35;
	/*36*/	BYTE	Unknown36;
	/*37*/	BYTE	Unknown37;
	/*38*/	WORD	Unknown38;
	/*40*/	BYTE	Unknown40;
	/*41*/	BYTE	Unknown41;
	/*42*/	BYTE	Unknown42;
	/*43*/	BYTE	Unknown43;
	/*44*/	BYTE	Unknown44;
	/*45*/	BYTE	MapPosX;
	/*46*/	BYTE	MapPosY;
	BYTE	Shift47[9];
	/*56*/	char	Name[25];	//-> Need check size

	/*50*/	//BYTE	Unknown50;	// -> 100%
	/*88*/	//BYTE	Unknown88;	// -> 100%
	/*90*/	//BYTE	Unknown90;	// -> 100%
	/*91*/	//BYTE	Unknown91;	// -> 100%
	/*92*/	//WORD	InGuild;	// -> 100%
	/*94*/	//WORD	ObjIndex;	// -> 100%
	/*96*/	//WORD	Unknown96;	// -> 100%
	/*98*/	//WORD	Unknown98;	// -> 100%
	/*100*/	//WORD	Unknown100;	// -> 100%
	/*106*/	//WORD	Unknown106;	// -> 100%
	/*112*/	//DWORD	Unknown112;	// -> 100%
	/*116*/	//DWORD	Unknown116;	// -> 100%
	/*124*/	//DWORD	Unknown124;	// -> 100%
	/*140*/	//DWORD MapPosX;	// -> 100%
	/*144*/	//DWORD MapPosY;	// -> 100%
	/*156*/	//DWORD	Unknown156;	// -> 100%
	/*172*/	//DWORD	Unknown172;	// -> 100%
	/*188*/	//DWORD	Unknown188;	// -> 100%
	/*192*/	//DWORD	Unknown192;	// -> 100%
	/*196*/	//DWORD	Unknown196;	// -> 100%

	BYTE	Shift2[150];

	/*232*/	WORD	HelmSlot;
	/*234*/	BYTE	HelmLevel;
	/*235*/	BYTE	HelmExcellent;
	/*236*/	BYTE	HelmAncient;
	BYTE	Shift5[27];
	/*264*/	WORD	ArmorSlot;
	/*266*/	BYTE	ArmorLevel;
	/*267*/	BYTE	ArmorExcellent;
	/*268*/	BYTE	ArmorAncient;
	BYTE	Shift6[27];
	/*296*/	WORD	PantsSlot;
	/*298*/	BYTE	PantsLevel;
	/*299*/	BYTE	PantsExcellent;
	/*300*/	BYTE	PantsAncient;
	BYTE	Shift7[27];
	/*328*/	WORD	GlovesSlot;
	/*330*/	BYTE	GlovesLevel;
	/*331*/	BYTE	GlovesExcellent;
	/*332*/	BYTE	GlovesAncient;
	BYTE	Shift8[27];
	/*360*/	WORD	BootsSlot;
	/*362*/	BYTE	BootsLevel;
	/*363*/	BYTE	BootsExcellent;
	/*364*/	BYTE	BootsAncient;
	BYTE	Shift9[27];
	/*392*/	WORD	WeaponFirstSlot;
	/*394*/	BYTE	WeaponFirstLevel;
	/*395*/	BYTE	WeaponFirstExcellent;
	/*396*/	BYTE	WeaponFirstAncient;
	/*397*/	BYTE	Unknown397;
	BYTE	Shift10[26];
	/*424*/	WORD	WeaponSecondSlot;
	/*426*/	BYTE	WeaponSecondLevel;
	/*427*/	BYTE	WeaponSecondExcellent;
	/*428*/	BYTE	WeaponSecondAncient;
	/*429*/	BYTE	Unknown429;
	BYTE	Shift11[26];
	/*456*/	WORD	WingsSlot;
	/*458*/ BYTE	Unknown458;
	/*459*/ BYTE	Unknown459;
	/*460*/ BYTE	Unknown460;
	BYTE	Shift12[27];
	/*488*/	WORD	PetSlot;
	/*490*/ BYTE	Unknown490;
	/*491*/ BYTE	FenrirCharSet;
	/*492*/ BYTE	ExpectPet;

	/*520*/	//WORD	Unknown520;	// -> 100%
	/*596*/	//DWORD	Unknown596;	// -> 100%
	/*688*/	//DWORD	Unknown688;	//
	BYTE	Shift13[207];

	/*700*/	DWORD	Unknown700;	// -> # Need check
	/*704*/	BYTE	Unknown704;

	BYTE	Shift14[2];

	/*707*/	BYTE	Unknown707;
	/*708*/	BYTE	Unknown708;
	/*709*/	BYTE	Unknown709;
	/*710*/	BYTE	Unknown710;	// -> 100%
	/*711*/	BYTE	Unknown711;
	/*712*/	BYTE	Unknown712;
	BYTE	Shift16[5];
	/*718*/	BYTE	Action;
	/*719*/	BYTE	Unknown719;
	/*720*/	BYTE	Unknown720; //-> 100%
	/*721*/	BYTE	Unknown721;	//-> 100%
	/*722*/ BYTE	ObjectType; //-> Object Type (1 = Player, 2 = Monster, 4 = NPC) 100%
	BYTE	Shift17[25];
	/*748*/	DWORD	Unknown748;
	/*752*/	DWORD	Unknown752;
	/*756*/	DWORD	Unknown756;
	/*760*/	DWORD	Unknown760;

	/*768*/	//DWORD	Unknown768;	// -> 100%

	BYTE	Shift18[32];
	/*796*/	DWORD	ModelScale;
	BYTE	Shift19[16];

	/*800*/	//DWORD	Unknown800;	// -> 100%

	/*816*/	DWORD	Unknown816;

	/*824*/	//DWORD	Unknown824;	// -> 100%

	BYTE	Shift20[103];

	/*856*/	//DWORD	Unknown856;	// -> 100%
	/*860*/	//DWORD	Unknown860;	// -> 100%
	/*864*/	//DWORD	Unknown864;	// -> 100%
	/*972*/	//DWORD	Unknown972;	// -> 100%
	/*904*/	//DWORD	Unknown904;	// -> 100%
	/*908*/	//DWORD	Unknown908;	// -> 100%
	/*912*/	//DWORD	Unknown912;	// -> 100%
	/*916*/	//DWORD	Unknown916;	// -> 100% / Maybe float
	/*920*/	//DWORD	Unknown920;	// -> 100% / Maybe float

	/*924*/	float	SelectZone;	// -> Maybe DWORD
	BYTE	Shift21[32];

	/*952*/	//float	Unknown952;	// -> 100%
	/*956*/	//float	Unknown956;	// -> 100%

	/*960*/ float	Unknown960;

	/*964*/	//DWORD	Unknown964;	// -> 100%
	/*968*/	//DWORD	Unknown968;	// -> 100%
	/*972*/	//DWORD	Unknown972;	// -> 100%
	/*1120*/	//DWORD	Unknown1120;	// -> 100%
	/*1184*/	//void?
};

class cMakePreviewCharSet
{
public:
	void Load();

	BYTE		LevelSmallConvert(int SmallValue);
	static int	MakePreviewSoldierElf(int Struct);
	static int  MakePreviewCharSet(int Index, BYTE * CharSet, int UseStruct, int Mode);

};
extern cMakePreviewCharSet gMakePreviewCharSet;

//---------------------------------------------------------------------------

#endif