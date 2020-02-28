#include "stdafx.h"
#include "Item.h"
#include "TMemory.h"
#include "Console.h"
#include "Configs.h"
#include "ExLicense.h"
#include "Interface.h"
#include "Effect.h"
#include "PetEx.h"

 Item gItem;

void Item::Load()
{

	SetOp((LPVOID)oLoadModel, this->LoadModels, ASM::CALL);
	SetOp((LPVOID)oLoadTexture, this->LoadTextures, ASM::CALL);

//	SetOp((LPVOID)oGlow, this->Glow, ASM::CALL);
	
//	SetOp((LPVOID)oSocketItems1, this->SocketItems, ASM::CALL);
//	SetOp((LPVOID)oSocketItems2, this->SocketItems, ASM::CALL);

	SetOp((LPVOID)0x7E3FC0, this->IsWings, ASM::CALL);
	SetOp((LPVOID)0x7E4766, this->IsWings, ASM::CALL);
	SetOp((LPVOID)0x7E5195, this->IsWings, ASM::CALL);
	// ----
	SetOp((LPVOID)0x7DBD6B, this->GetUpgradeFlag, ASM::CALL);
	// ----
	SetOp((LPVOID)0x48FB8C, this->PreviewCharSet, ASM::CALL);
	SetOp((LPVOID)0x63D2D8, this->PreviewCharSet, ASM::CALL);
	SetOp((LPVOID)0x641189, this->PreviewCharSet, ASM::CALL);
	SetOp((LPVOID)0x641F42, this->PreviewCharSet, ASM::CALL);
	SetOp((LPVOID)0x642598, this->PreviewCharSet, ASM::CALL);
	SetOp((LPVOID)0x65EA2D, this->PreviewCharSet, ASM::CALL);
	// ----
	SetOp((LPVOID)0x7D9D5A, this->AllowRepairWings, ASM::CALL);
	// ----
	SetOp((LPVOID)0x58B77E, this->SetOption, ASM::CALL);
	SetOp((LPVOID)0x5C7833, this->SetOption, ASM::CALL);
	SetOp((LPVOID)0x5C7D71, this->SetOption, ASM::CALL);
	SetOp((LPVOID)0x5C7F1B, this->SetOption, ASM::CALL);
	SetOp((LPVOID)0x5C80BE, this->SetOption, ASM::CALL);
	SetOp((LPVOID)0x7E216A, this->SetOption, ASM::CALL);
	// ----
	//SetOp((LPVOID)0x5666C1, this->SetItemEffect, ASM::CALL);
	//SetOp((LPVOID)0x61041C, this->SetItemEffect, ASM::CALL);
	//SetOp((LPVOID)0x610466, this->SetItemEffect, ASM::CALL);
	// ----
	//SetOp((LPVOID)0x5711AB, this->SetItemEffect2, ASM::CALL);
	//SetOp((LPVOID)0x57126F, this->SetItemEffect2, ASM::CALL);
	//SetOp((LPVOID)0x5713D6, this->SetItemEffect2, ASM::CALL);
	//SetOp((LPVOID)0x57126F, this->SetItemEffect2, ASM::CALL);
	//SetOp((LPVOID)0x588357, this->SetItemEffect2, ASM::CALL);
	//SetOp((LPVOID)0x5883F4, this->SetItemEffect2, ASM::CALL);
	//SetOp((LPVOID)0x588505, this->SetItemEffect2, ASM::CALL);
	//SetOp((LPVOID)0x588617, this->SetItemEffect2, ASM::CALL);
	//SetOp((LPVOID)0x588661, this->SetItemEffect2, ASM::CALL);
	//SetOp((LPVOID)0x58876E, this->SetItemEffect2, ASM::CALL);
	//SetOp((LPVOID)0x5887AD, this->SetItemEffect2, ASM::CALL);
	//SetOp((LPVOID)0x609D1E, this->SetItemEffect2, ASM::CALL);
	//SetOp((LPVOID)0x610691, this->SetItemEffect2, ASM::CALL);
	// ----
	SetOp((LPVOID)0x51BCA5, this->GetMaxDurability, ASM::CALL);
	SetOp((LPVOID)0x590260, this->GetMaxDurability, ASM::CALL);
	SetOp((LPVOID)0x5C1A2F, this->GetMaxDurability, ASM::CALL);
	SetOp((LPVOID)0x5C1B70, this->GetMaxDurability, ASM::CALL);
	SetOp((LPVOID)0x5C423A, this->GetMaxDurability, ASM::CALL);
	SetOp((LPVOID)0x5C46E0, this->GetMaxDurability, ASM::CALL);
	SetOp((LPVOID)0x7D9A52, this->GetMaxDurability, ASM::CALL);
	SetOp((LPVOID)0x7DF4B2, this->GetMaxDurability, ASM::CALL);
	SetOp((LPVOID)0x7DFB0B, this->GetMaxDurability, ASM::CALL);
	SetOp((LPVOID)0x7E04D9, this->GetMaxDurability, ASM::CALL);
	SetOp((LPVOID)0x7E0811, this->GetMaxDurability, ASM::CALL);
	SetOp((LPVOID)0x7E5E8B, this->GetMaxDurability, ASM::CALL);
	SetOp((LPVOID)0x836FFD, this->GetMaxDurability, ASM::CALL);
	SetOp((LPVOID)0x95F5EE, this->GetMaxDurability, ASM::CALL);

	SetOp((LPVOID)0x0057AC07, this->Glow, ASM::CALL);
	SetOp((LPVOID)0x006083B9, this->Glow, ASM::CALL);

	//SetOp((LPVOID)0x005F56B9, this->PickUpItemInfo, ASM::CALL);
	

	//0057AC07
	//

	//memset(&this->m_PickUp, 0, sizeof(this->m_PickUp));

	#if(FIX_CORD_ITEM_TEXT)
	SetOp((LPVOID)0x007E5B66, this->FixCordItemTextX, ASM::CALL);
	#endif
}

void Item::LoadModels()
{
	pInitModelData();
	 //----
	//New Jewels
	char JewelDir[] = "Data\\Custom\\Items\\Jewels\\";
	//pLoadModel(ITEM2(14,180), JewelDir, "Jewel180",		-1);
	pLoadModel(ITEM2(14,181), JewelDir, "Jewel181",		-1);
	pLoadModel(ITEM2(14,182), JewelDir, "Jewel182",		-1);
	pLoadModel(ITEM2(14,183), JewelDir, "Jewel183",		-1);
	pLoadModel(ITEM2(14,184), JewelDir, "Jewel184",		-1);
	pLoadModel(ITEM2(14,185), JewelDir, "Jewel185",		-1);
	pLoadModel(ITEM2(14,186), JewelDir, "Jewel186",		-1);
	pLoadModel(ITEM2(14,187), JewelDir, "Jewel187",		-1);
	pLoadModel(ITEM2(14,188), JewelDir, "Jewel188",		-1);
	pLoadModel(ITEM2(14,189), JewelDir, "Jewel189",		-1);
	pLoadModel(ITEM2(14,190), JewelDir, "Jewel190",		-1);
	pLoadModel(ITEM2(14,191), JewelDir, "Jewel191",		-1);
	//pLoadModel(ITEM2(14,200), JewelDir, "Jewel191",		-1);
	//Wings 4 rd
	char WingsDir[]		= "Data\\Custom\\Items\\Wings4\\";
	pLoadModel(ITEM2(12,180), WingsDir, "Wings180", -1); // Wings201.bmd	- Grand Master
	pLoadModel(ITEM2(12,181), WingsDir, "Wings181", -1); // Wings202.bmd	- Blade Master
	pLoadModel(ITEM2(12,182), WingsDir, "Wings182", -1); // Wings203.bmd	- Hight Elf
	pLoadModel(ITEM2(12,183), WingsDir, "Wings183", -1); // Wings206.bmd	-  Summoner
	pLoadModel(ITEM2(12,185), WingsDir, "Wings185", -1); // Wings204.bmd	- Magic Gladiator
	pLoadModel(ITEM2(12,184), WingsDir, "Wings184", -1); // Wing51.bmd		- Lord Emperor
	//Wings 2.5 
	char Wings2_5Dir[]		= "Data\\Custom\\Items\\Wings2_5\\";
	pLoadModel(ITEM2(12,186), Wings2_5Dir, "wing1", -1); // Wings201.bmd	- Black Knight
	pLoadModel(ITEM2(12,187), Wings2_5Dir, "wing2", -1); // Wings202.bmd	- Soul Master
	pLoadModel(ITEM2(12,188), Wings2_5Dir, "wing3", -1); // Wings203.bmd	- Muse Elf
	//Wings 5 rd
	char Wings5Dir[] = "Data\\Custom\\Items\\Wings5\\";
	pLoadModel(ITEM2(12,189), Wings5Dir, "DW_Wings5", -1);
	pLoadModel(ITEM2(12,190), Wings5Dir, "DK_Wings5", -1);
	pLoadModel(ITEM2(12,191), Wings5Dir, "Elf_Wings5", -1);
	pLoadModel(ITEM2(12,192), Wings5Dir, "MG_Wings5", -1);
	pLoadModel(ITEM2(12,193), Wings5Dir, "MG_Wings5_2", -1);
	pLoadModel(ITEM2(12,194), Wings5Dir, "DL_Wings5", -1);
	//char StoneDir[] = "";

#ifdef _COINS_
	//char CoinDir[] = "Data\\ExTeam\\Coins\\";
	//pLoadModel(ITEM2(14,192), CoinDir, "BronzeCoin",		-1);
#endif
#ifdef _GRAND_SYSTEM_
	////Grand Hero Item


	char StormWingSetDir[] = "Data\\Custom\\Items\\Hero\\StormWingSet(BM)\\";
	char CerberusSetDir[] = "Data\\Custom\\Items\\Hero\\CerberusSet(GM)\\";
	char UpperKeysSetDir[] = "Data\\Custom\\Items\\Hero\\UpperKeysSet(HE)\\";
	char HellKnightSetDir[] = "Data\\Custom\\Items\\Hero\\HellKnightSet(DM)\\";
	char EmbisyeonSetDir[] = "Data\\Custom\\Items\\Hero\\EmbisyeonSet(LE)\\";
	char SuccubusSetDir[] = "Data\\Custom\\Items\\Hero\\SuccubusSet(Sum)\\";
	//StormWingSet(BM)
	pLoadModel(ITEM2(7,84), StormWingSetDir,  "HelmMale75", -1);
	pLoadModel(ITEM2(8,84), StormWingSetDir, "ArmorMale75", -1);
	pLoadModel(ITEM2(9,84), StormWingSetDir, "PantMale75",  -1);
	pLoadModel(ITEM2(10,84),StormWingSetDir, "GloveMale75", -1);
	pLoadModel(ITEM2(11,84),StormWingSetDir, "BootMale75",  -1);
	//CerberusSet(GM)
	pLoadModel(ITEM2(7,85), CerberusSetDir, "HelmMale160",  -1);
	pLoadModel(ITEM2(8,85), CerberusSetDir, "ArmorMale160", -1);
	pLoadModel(ITEM2(9,85), CerberusSetDir, "PantMale160",  -1);
	pLoadModel(ITEM2(10,85),CerberusSetDir, "GloveMale160", -1);
	pLoadModel(ITEM2(11,85),CerberusSetDir, "BootMale160",  -1);
	//UpperKeysSet(HE)
	pLoadModel(ITEM2(7,86), UpperKeysSetDir, "HelmMale76",  -1);
	pLoadModel(ITEM2(8,86), UpperKeysSetDir, "ArmorMale76", -1);
	pLoadModel(ITEM2(9,86), UpperKeysSetDir, "PantMale76",  -1);
	pLoadModel(ITEM2(10,86),UpperKeysSetDir, "GloveMale76", -1);
	pLoadModel(ITEM2(11,86),UpperKeysSetDir, "BootMale76",  -1);
	//HellKnightSet(DM)
	pLoadModel(ITEM2(8,87), HellKnightSetDir,  "ArmorMale57", -1);
	pLoadModel(ITEM2(9,87), HellKnightSetDir, "PantMale57",  -1);
	pLoadModel(ITEM2(10,87),HellKnightSetDir, "GloveMale57", -1);
	pLoadModel(ITEM2(11,87),HellKnightSetDir, "BootMale57",  -1);	
	//EmbisyeonSet(LE)
	pLoadModel(ITEM2(7,88), EmbisyeonSetDir, "HelmMale59",  -1);
	pLoadModel(ITEM2(8,88), EmbisyeonSetDir, "ArmorMale59", -1);
	pLoadModel(ITEM2(9,88), EmbisyeonSetDir, "PantMale59",  -1);
	pLoadModel(ITEM2(10,88),EmbisyeonSetDir, "GloveMale59", -1);
	pLoadModel(ITEM2(11,88),EmbisyeonSetDir, "BootMale59",  -1);
	//SuccubusSet(Sum)
	pLoadModel(ITEM2(7,89), SuccubusSetDir, "HelmMale55",  -1);
	pLoadModel(ITEM2(8,89), SuccubusSetDir, "ArmorMale55", -1);
	pLoadModel(ITEM2(9,89), SuccubusSetDir, "PantMale55",  -1);
	pLoadModel(ITEM2(10,89),SuccubusSetDir, "GloveMale55", -1);
	pLoadModel(ITEM2(11,89),SuccubusSetDir, "BootMale55",  -1);
	//Weapons
	pLoadModel(ITEM2(5,41), "Data\\Custom\\Hero\\ApocalypseStaff\\", "Staff26",  -1 );
	pLoadModel(ITEM2(4,30), "Data\\Custom\\Hero\\DraconicBow\\", "BowDraconic", -1 );
	//pLoadModel(ITEM2(0,41), "Data\\ExData\\Item\\test\\", "Sword100",  -1 );

	pLoadModel(ITEM2(0,41), "Data\\Custom\\Hero\\NagaSword\\", "Sword37",  -1 );

	pLoadModel(ITEM2(2,20), "Data\\Custom\\Hero\\SepScepetr\\", "Staff20",  -1);
	pLoadModel(ITEM2(5,42), "Data\\Custom\\Hero\\SpiritStick\\", "Staff38",  -1);
	pLoadModel(ITEM2(0,42), "Data\\Custom\\Hero\\StormSword\\", "Sword33",  -1);
	//Shield
	
	pLoadModel(ITEM2(6,30), "Data\\Custom\\Hero\\EmbisyeonShield(LE)\\", "Shield27",  -1 );
	pLoadModel(ITEM2(6,31), "Data\\Custom\\Hero\\HellKnightShield(DM)\\", "Shield26",  -1 );
	pLoadModel(ITEM2(6,32), "Data\\Custom\\Hero\\LazyWingShield(BM)\\", "Shield23",  -1);
	pLoadModel(ITEM2(6,33), "Data\\Custom\\Hero\\ShieldofDivine\\", "ShieldofDivine",  -1);


	pLoadModel(ITEM2(7,90), "Data\\Player\\", "HelmMale61",  -1 );
	pLoadModel(ITEM2(8,90), "Data\\Player\\", "ArmorMale61",  -1 );
	pLoadModel(ITEM2(9,90), "Data\\Player\\", "PantMale61",  -1);
	pLoadModel(ITEM2(11,90), "Data\\Player\\", "BootMale61",  -1);
	pLoadModel(ITEM2(9,90), "Data\\Player\\", "PantMale61",  -1);
	pLoadModel(ITEM2(14,195), "Data\\Custom\\Items\\Stone\\", "suho",  -1);

#endif
#ifdef NEWWINGS6
	//if( g_ExLicense.ActiveUser == Local2 ||	g_ExLicense.ActiveUser == PrideMu ||		g_ExLicense.ActiveUser == Local3||		g_ExLicense.ActiveUser ==PrideMuLocal)	{
	//if(g_ExLicense.ActiveUser == PrideMu ||		g_ExLicense.ActiveUser ==PrideMuLocal||		g_ExLicense.ActiveUser == Local2 || g_ExLicense.ActiveUser == Local3)
	//{
	pLoadModel(ITEM2(12,195), "Data\\Custom\\Items\\Wings6\\", "Wing186", -1);
	pLoadModel(ITEM2(12,196), "Data\\Custom\\Items\\Wings6\\", "Wing191", -1);
	//}
	//}
#endif
	//14 	 	"suho" 			"Data\\ExTeam\\stone\\"		"ExTeam\\stone\\"
#ifdef EXCLUSIVE_AMYLET
	pLoadModel(ITEM2(13,147), "Data\\Custom\\Items\\Stone\\", "suho",  -1);
	pLoadModel(ITEM2(13,148), "Data\\Custom\\Items\\Stone\\", "suho",  -1);
pLoadModel(ITEM2(13,149), "Data\\Custom\\Items\\Stone\\", "suho",  -1);
pLoadModel(ITEM2(13,150), "Data\\Custom\\Items\\Stone\\", "suho",  -1);
pLoadModel(ITEM2(13,151), "Data\\Custom\\Items\\Stone\\", "suho",  -1);
pLoadModel(ITEM2(13,152), "Data\\Custom\\Items\\Stone\\", "suho",  -1);

pLoadModel(ITEM2(13,153), "Data\\Custom\\Items\\Stone\\", "suho",  -1);
pLoadModel(ITEM2(13,154), "Data\\Custom\\Items\\Stone\\", "suho",  -1);
pLoadModel(ITEM2(13,155), "Data\\Custom\\Items\\Stone\\", "suho",  -1);
pLoadModel(ITEM2(13,156), "Data\\Custom\\Items\\Stone\\", "suho",  -1);

#endif

	for(int i=0;i<gConfig.CountItem;i++)
	{
		#if(ENABLE_PETEX)
		if(g_PetEx.IsPet(ITEM2(gConfig.Item[i].Type,gConfig.Item[i].Index), true))
		{
			continue;
		}
		#endif
		pLoadModel(ITEM2(gConfig.Item[i].Type,gConfig.Item[i].Index), gConfig.Item[i].Dir1, gConfig.Item[i].BMD , -1);
	}

	//InitModel(LOAD_ITEM(12,189), "DW_Wings5", "ExTeam\\Wings5\\", "Data\\ExTeam\\Wings5\\"); 
	//InitModel(LOAD_ITEM(12,190), "DK_Wings5", "ExTeam\\Wings5\\", "Data\\ExTeam\\Wings5\\");
	//InitModel(LOAD_ITEM(12,191), "Elf_Wings5", "ExTeam\\Wings5\\", "Data\\ExTeam\\Wings5\\");
	//InitModel(LOAD_ITEM(12,192), "MG_Wings5", "ExTeam\\Wings5\\", "Data\\ExTeam\\Wings5\\");
	//InitModel(LOAD_ITEM(12,193), "MG_Wings5_2", "ExTeam\\Wings5\\", "Data\\ExTeam\\Wings5\\");
	//InitModel(LOAD_ITEM(12,194), "DL_Wings5", "ExTeam\\Wings5\\", "Data\\ExTeam\\Wings5\\");


	//////Grand Hero Item
	//char StormWingSetDir[] = "Data\\ExTeam\\Items\\StormWingSet(BM)\\";
	//char CerberusSetDir[] = "Data\\ExTeam\\Items\\CerberusSet(GM)\\";
	//char UpperKeysSetDir[] = "Data\\ExTeam\\Items\\UpperKeysSet(HE)\\";
	//char HellKnightSetDir[] = "Data\\ExTeam\\Items\\HellKnightSet(DM)\\";
	//char EmbisyeonSetDir[] = "Data\\ExTeam\\Items\\EmbisyeonSet(LE)\\";
	//char SuccubusSetDir[] = "Data\\ExTeam\\Items\\SuccubusSet(Sum)\\";
	////StormWingSet(BM)
	//pLoadModel(ITEM2(7,60), StormWingSetDir,  "HelmMale75", -1);
	//pLoadModel(ITEM2(8,60), StormWingSetDir, "ArmorMale75", -1);
	//pLoadModel(ITEM2(9,60), StormWingSetDir, "PantMale75",  -1);
	//pLoadModel(ITEM2(10,60),StormWingSetDir, "GloveMale75", -1);
	//pLoadModel(ITEM2(11,60),StormWingSetDir, "BootMale75",  -1);
	////CerberusSet(GM)
	//pLoadModel(ITEM2(7,61), CerberusSetDir, "HelmMale160",  -1);
	//pLoadModel(ITEM2(8,61), CerberusSetDir, "ArmorMale160", -1);
	//pLoadModel(ITEM2(9,61), CerberusSetDir, "PantMale160",  -1);
	//pLoadModel(ITEM2(10,61),CerberusSetDir, "GloveMale160", -1);
	//pLoadModel(ITEM2(11,61),CerberusSetDir, "BootMale160",  -1);
	////UpperKeysSet(HE)
	//pLoadModel(ITEM2(7,62), UpperKeysSetDir, "HelmMale76",  -1);
	//pLoadModel(ITEM2(8,62), UpperKeysSetDir, "ArmorMale76", -1);
	//pLoadModel(ITEM2(9,62), UpperKeysSetDir, "PantMale76",  -1);
	//pLoadModel(ITEM2(10,62),UpperKeysSetDir, "GloveMale76", -1);
	//pLoadModel(ITEM2(11,62),UpperKeysSetDir, "BootMale76",  -1);
	////HellKnightSet(DM)
	//pLoadModel(ITEM2(8,63), HellKnightSetDir,  "ArmorMale57", -1);
	//pLoadModel(ITEM2(9,63), HellKnightSetDir, "PantMale57",  -1);
	//pLoadModel(ITEM2(10,63),HellKnightSetDir, "GloveMale57", -1);
	//pLoadModel(ITEM2(11,63),HellKnightSetDir, "BootMale57",  -1);	
	////EmbisyeonSet(LE)
	//pLoadModel(ITEM2(7,64), EmbisyeonSetDir, "HelmMale59",  -1);
	//pLoadModel(ITEM2(8,64), EmbisyeonSetDir, "ArmorMale59", -1);
	//pLoadModel(ITEM2(9,64), EmbisyeonSetDir, "PantMale59",  -1);
	//pLoadModel(ITEM2(10,64),EmbisyeonSetDir, "GloveMale59", -1);
	//pLoadModel(ITEM2(11,64),EmbisyeonSetDir, "BootMale59",  -1);
	//SuccubusSet(Sum)
	//pLoadModel(ITEM2(7,65), SuccubusSetDir, "HelmMale55",  -1);
	//pLoadModel(ITEM2(8,65), SuccubusSetDir, "ArmorMale55", -1);
	//pLoadModel(ITEM2(9,65), SuccubusSetDir, "PantMale55",  -1);
	//pLoadModel(ITEM2(10,65),SuccubusSetDir, "GloveMale55", -1);
	//pLoadModel(ITEM2(11,65),SuccubusSetDir, "BootMale55",  -1);
	//Weapons
	//pLoadModel(ITEM2(5,100), "Data\\ExTeam\\Weapon\\ApocalypseStaff\\", "Staff26",  -1 );
	//pLoadModel(ITEM2(4,30), "Data\\ExTeam\\Weapon\\DraconicBow\\", "BowDraconic", -1 );
	//pLoadModel(ITEM2(0,40), "Data\\ExTeam\\Weapon\\NagaSword\\", "Sword37",  -1 );
	//pLoadModel(ITEM2(2,20), "Data\\ExTeam\\Weapon\\SepScepetr\\", "Staff20",  -1);
	//pLoadModel(ITEM2(5,41), "Data\\ExTeam\\Weapon\\SpiritStick\\", "Staff38",  -1);
	//pLoadModel(ITEM2(0,41), "Data\\ExTeam\\Weapon\\StormSword\\", "Sword33",  -1);
	//Shield
	//pLoadModel(ITEM2(6,30), "Data\\ExTeam\\Shield\\EmbisyeonShield(LE)\\", "Shield27",  -1 );
	//pLoadModel(ITEM2(6,31), "Data\\ExTeam\\Shield\\HellKnightShield(DM)\\", "Shield26",  -1 );
	//pLoadModel(ITEM2(6,32), "Data\\ExTeam\\Shield\\LazyWingShield(BM)\\", "Shield23",  -1);
	//pLoadModel(ITEM2(6,33), "Data\\ExTeam\\Shield\\ShieldofDivine\\", "ShieldofDivine",  -1);
	////Stone
	//pLoadModel(ITEM2(14,208), "suho", "Data\\ExTeam\\stone\\", -1); // Mix Stone


	//Talisman System
	//char TalismanDir[] = "Data\\ExTeam\\Talismans\\";
	//pLoadModel(ITEM2(14,200), TalismanDir, "Jewel201", -1); 
	//pLoadModel(ITEM2(14,201), TalismanDir, "Jewel202", -1); 
	//pLoadModel(ITEM2(14,202), TalismanDir, "Jewel203", -1); 
	//pLoadModel(ITEM2(14,203), TalismanDir, "Jewel204", -1); 
	//pLoadModel(ITEM2(14,204), TalismanDir, "Jewel205", -1); 
	//pLoadModel(ITEM2(14,205), TalismanDir, "Jewel206", -1); 
	//pLoadModel(ITEM2(14,206), TalismanDir, "Jewel207", -1); 
	//pLoadModel(ITEM2(14,207), TalismanDir, "Jewel208", -1); 


	//Pack System
	//char PackDir[] = "Data\\ExTeam\\Pack\\";
	//pLoadModel(ITEM2(14,210), PackDir, "ChaosPack",	-1);
	//pLoadModel(ITEM2(14,211), PackDir, "CreationPack",-1);
	//pLoadModel(ITEM2(14,212), PackDir, "GuardianPack",-1);
	//pLoadModel(ITEM2(14,213), PackDir, "LifePack",	-1);
	//pLoadModel(ITEM2(14,214), PackDir, "HarmonyPack",	-1);


	//Wings 5 Level
	//char Wings5Dir[] = "Data\\ExTeam\\Wings5\\";
	//pLoadModel(ITEM2(12,189), Wings5Dir, "DW_Wings5", -1); 
	//pLoadModel(ITEM2(12,190), Wings5Dir, "DK_Wings5", -1);
	//pLoadModel(ITEM2(12,191), Wings5Dir, "Elf_Wings5", -1);
	//pLoadModel(ITEM2(12,192), Wings5Dir, "MG_Wings5", -1);
	//pLoadModel(ITEM2(12,193), Wings5Dir, "MG_Wings5_2", -1);
	//pLoadModel(ITEM2(12,194), Wings5Dir, "DL_Wings5", -1);

#if(RF_NEW_GLOV)
	pLoadModel(ITEM2(0,114), "Data\\ExData\\Item\\BloodyDragon_RF\\GloveMaleBloodyDragon\\", "Sword34", -1);
	pLoadModel(GLOV1, "Data\\ExData\\Item\\BloodyDragon_RF\\GloveMaleBloodyDragon\\", "SwordL34", -1);
	pLoadModel(GLOV2, "Data\\ExData\\Item\\BloodyDragon_RF\\GloveMaleBloodyDragon\\", "SwordR34", -1);
#endif

	#if(ENABLE_PETEX)
	g_PetEx.LoadModel();
	#endif
}

void Item::LoadTextures()
{
	pInitTextureData();
	// ----
	//New Jewels
	char JewelFolder[]	= "Custom\\Items\\Jewels\\";
	pLoadTexture(ITEM2(14, 180), JewelFolder, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(14, 181), JewelFolder, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(14, 182), JewelFolder, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(14, 183), JewelFolder, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(14, 184), JewelFolder, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(14, 185), JewelFolder, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(14, 186), JewelFolder, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(14, 187), JewelFolder, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(14, 188), JewelFolder, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(14, 189), JewelFolder, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(14, 190), JewelFolder, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(14, 191), JewelFolder, GL_REPEAT, GL_NEAREST, GL_TRUE);
	//pLoadTexture(ITEM2(14, 200), JewelFolder, GL_REPEAT, GL_NEAREST, GL_TRUE);
	//Wings 4 rd
	char WingsFolder[]	= "Custom\\Items\\Wings4\\";
	pLoadTexture(ITEM2(12,180), WingsFolder, GL_REPEAT, GL_NEAREST, GL_TRUE); // Wings201.bmd	- Grand Master
	pLoadTexture(ITEM2(12,181), WingsFolder, GL_REPEAT, GL_NEAREST, GL_TRUE); // Wings202.bmd	- Blade Master
	pLoadTexture(ITEM2(12,182), WingsFolder, GL_REPEAT, GL_NEAREST, GL_TRUE); // Wings203.bmd	- Hight Elf
	pLoadTexture(ITEM2(12,183), WingsFolder, GL_REPEAT, GL_NEAREST, GL_TRUE); // Wings206.bmd	-  Summoner
	pLoadTexture(ITEM2(12,185), WingsFolder, GL_REPEAT, GL_NEAREST, GL_TRUE); // Wings204.bmd	- Magic Gladiator
	pLoadTexture(ITEM2(12,184), WingsFolder, GL_REPEAT, GL_NEAREST, GL_TRUE); // Wing51.bmd		- Lord Emperor
	//Wings 2.5 
	char WingsFolder2[]	= "Custom\\Items\\Wings2_5\\";
	pLoadTexture(ITEM2(12,186), WingsFolder2, GL_REPEAT, GL_NEAREST, GL_TRUE); // Wings201.bmd	- Black Knight
	pLoadTexture(ITEM2(12,187), WingsFolder2, GL_REPEAT, GL_NEAREST, GL_TRUE); // Wings202.bmd	- Soul Master
	pLoadTexture(ITEM2(12,188), WingsFolder2, GL_REPEAT, GL_NEAREST, GL_TRUE); // Wings203.bmd	- Muse Elf
	//Wings 5 rd
	char Wings5Folder[] = "Custom\\Items\\Wings5\\";
	pLoadTexture(ITEM2(12,189), Wings5Folder, GL_REPEAT, GL_NEAREST, GL_TRUE); // Wings201.bmd	- Grand Master
	pLoadTexture(ITEM2(12,190), Wings5Folder, GL_REPEAT, GL_NEAREST, GL_TRUE); // Wings202.bmd	- Blade Master
	pLoadTexture(ITEM2(12,191), Wings5Folder, GL_REPEAT, GL_NEAREST, GL_TRUE); // Wings203.bmd	- Hight Elf
	pLoadTexture(ITEM2(12,192), Wings5Folder, GL_REPEAT, GL_NEAREST, GL_TRUE); // Wings206.bmd	-  Summoner
	pLoadTexture(ITEM2(12,193), Wings5Folder, GL_REPEAT, GL_NEAREST, GL_TRUE); // Wings204.bmd	- Magic Gladiator
	pLoadTexture(ITEM2(12,194), Wings5Folder, GL_REPEAT, GL_NEAREST, GL_TRUE); // Wing51.bmd		- Lord Emperor
	//pLoadTexture(ITEM2(12,196), "Data\\ExTeam\\Wings6\\", GL_REPEAT, GL_NEAREST, GL_TRUE); // Wing02.bmd		
	
	#ifdef _GRAND_SYSTEM_

	//GrandHero Item
	char StormWingSetFol[] = "Custom\\Items\\Hero\\StormWingSet(BM)\\";
	char CerberusSetFol[] = "Custom\\Items\\Hero\\CerberusSet(GM)\\";
	char UpperKeysSetFol[] = "Custom\\Items\\Hero\\UpperKeysSet(HE)\\";
	char HellKnightSetFol[] = "Custom\\Items\\Hero\\HellKnightSet(DM)\\";
	char EmbisyeonSetFol[] = "Custom\\Items\\Hero\\EmbisyeonSet(LE)\\";
	char SuccubusSetFol[] = "Custom\\Items\\Hero\\SuccubusSet(Sum)\\";
	//StormWingSet(BM)
	pLoadTexture(ITEM2(7,84), StormWingSetFol,  GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(8,84), StormWingSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(9,84), StormWingSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(10,84),StormWingSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(11,84),StormWingSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	//CerberusSet(GM)
	pLoadTexture(ITEM2(7,85), CerberusSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(8,85), CerberusSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(9,85), CerberusSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(10,85),CerberusSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(11,85),CerberusSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	//UpperKeysSet(HE)
	pLoadTexture(ITEM2(7,86), UpperKeysSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(8,86), UpperKeysSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(9,86), UpperKeysSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(10,86),UpperKeysSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(11,86),UpperKeysSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	//HellKnightSet(DM)
	pLoadTexture(ITEM2(8,87), HellKnightSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(9,87), HellKnightSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(10,87),HellKnightSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(11,87),HellKnightSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);	
	//EmbisyeonSet(LE)
	pLoadTexture(ITEM2(7,88), EmbisyeonSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(8,88), EmbisyeonSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(9,88), EmbisyeonSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(10,88),EmbisyeonSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(11,88),EmbisyeonSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	//SuccubusSet(Sum)
	pLoadTexture(ITEM2(7,89), SuccubusSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(8,89), SuccubusSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(9,89), SuccubusSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(10,89),SuccubusSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(11,89),SuccubusSetFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	//Weapons
	pLoadTexture(ITEM2(5,41), "Custom\\Items\\Hero\\ApocalypseStaff\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(4,30), "Custom\\Items\\Hero\\DraconicBow\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(0,41), "Custom\\Items\\Hero\\NagaSword\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(2,20), "Custom\\Items\\Hero\\SepScepetr\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(5,42), "Custom\\Items\\Hero\\SpiritStick\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(0,42), "Custom\\Items\\Hero\\StormSword\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	//Shield
	pLoadTexture(ITEM2(6,30), "Custom\\Items\\Hero\\EmbisyeonShield(LE)\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(6,31), "Custom\\Items\\Hero\\HellKnightShield(DM)\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(6,32), "Custom\\Items\\Hero\\LazyWingShield(BM)\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(6,33), "Custom\\Items\\Hero\\ShieldofDivine\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	//RF
	pLoadTexture(ITEM2(7,90), "Player\\",  GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(8,90), "Player\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(9,90),"Player\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(11,90),"Player\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	
	
	
	pLoadTexture(ITEM2(14,195),"Custom\\Items\\Stone\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
#endif
#ifdef NEWWINGS6
	//if(g_ExLicense.ActiveUser == PrideMu ||		g_ExLicense.ActiveUser ==PrideMuLocal||		g_ExLicense.ActiveUser == Local2 || g_ExLicense.ActiveUser == Local3)
	//{
	pLoadTexture(ITEM2(12,195), "Custom\\Items\\Wings6\\", GL_REPEAT, GL_NEAREST, GL_TRUE); // Wing186.bmd.bmd	
	pLoadTexture(ITEM2(12,196), "Custom\\Items\\Wings6\\", GL_REPEAT, GL_NEAREST, GL_TRUE); // Wing02.bmd	
	//}
#endif
#ifdef EXCLUSIVE_AMYLET
	pLoadTexture(ITEM2(13,147),"Custom\\Items\\Stone\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(13,148),"Custom\\Items\\Stone\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(13,149),"Custom\\Items\\Stone\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(13,150),"Custom\\Items\\Stone\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(13,151),"Custom\\Items\\Stone\\", GL_REPEAT, GL_NEAREST, GL_TRUE);

	pLoadTexture(ITEM2(13,152),"Custom\\Items\\Stone\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(13,153),"Custom\\Items\\Stone\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(13,154),"Custom\\Items\\Stone\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(13,155),"Custom\\Items\\Stone\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(ITEM2(13,156),"Custom\\Items\\Stone\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
#endif

	for(int i=0;i<gConfig.CountItem;i++)
	{
		#if(ENABLE_PETEX)
		if(g_PetEx.IsPet(ITEM2(gConfig.Item[i].Type,gConfig.Item[i].Index), true))
		{
			continue;
		}
		#endif
		pLoadTexture(ITEM2(gConfig.Item[i].Type,gConfig.Item[i].Index), gConfig.Item[i].Dir2, GL_REPEAT, GL_NEAREST, GL_TRUE);
	}

	//14 	195 	"suho" 			"Data\\ExTeam\\stone\\"		"ExTeam\\stone\\"
	//ArmorMale61.bmd
	//ITEM2(0,43), "Data\\ExTeam\\Items\\RFsw\\", "Sword34"
	////Mix Stone
	//pLoadTexture(ITEM2(14,208), "ExTeam\\stone\\",  GL_REPEAT, GL_NEAREST, GL_TRUE);

	//Wings 5 Level
	//char Wings5kFol[] = "ExTeam\\Wings5\\";
	//pLoadTexture(ITEM2(12,189), Wings5kFol, GL_REPEAT, GL_NEAREST, GL_TRUE); 
	//pLoadTexture(ITEM2(12,190), Wings5kFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	//pLoadTexture(ITEM2(12,191), Wings5kFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	//pLoadTexture(ITEM2(12,192), Wings5kFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	//pLoadTexture(ITEM2(12,193), Wings5kFol, GL_REPEAT, GL_NEAREST, GL_TRUE);
	//pLoadTexture(ITEM2(12,194), Wings5kFol, GL_REPEAT, GL_NEAREST, GL_TRUE);

#if(RF_NEW_GLOV)
	//pLoadTexture(ITEM2(0,114), "ExData\\Item\\BloodyDragon_RF\\GloveMaleBloodyDragon\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	//pLoadTexture(GLOV1, "ExData\\Item\\BloodyDragon_RF\\GloveMaleBloodyDragon\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	//pLoadTexture(GLOV2, "ExData\\Item\\BloodyDragon_RF\\GloveMaleBloodyDragon\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
#endif

	#if(ENABLE_PETEX)
	g_PetEx.LoadTexture();
	#endif
}

//void Item::Glow(DWORD dwItemId, DWORD uk1, DWORD uk2, FRGB& cl, BYTE bUkn)
//{
//    switch(dwItemId)
//    {
//		//Grand Master
//        case ITEM2(5,40): cl.r = 0.10f; cl.g = 0.30f; cl.b = 0.50f; break;
//		case ITEM2(6,33): cl.r = 0.70; cl.g = 0.70f; cl.b = 0.70f; break;
//		case ITEM2(7,61):
//		case ITEM2(8,61):
//		case ITEM2(9,61):
//		case ITEM2(10,61):
//		case ITEM2(11,61):cl.r = 0.20f; cl.g = 0.45f; cl.b = 1.00f; break;
//		//Blade Master
//		case ITEM2(0,40): cl.r = 0.30f; cl.g = 1.00f; cl.b = 1.00f; break;
//		case ITEM2(6,32): cl.r = 0.30f; cl.g = 1.00f; cl.b = 1.00f; break;
//		case ITEM2(7,60):
//		case ITEM2(8,60):
//		case ITEM2(9,60):
//		case ITEM2(10,60):
//		case ITEM2(11,60):cl.r = 0.00f; cl.g = 0.20f; cl.b = 0.10f; break;
//		//High Elf
//		case ITEM2(4,30): cl.r = 0.30f; cl.g = 0.30f; cl.b = 0.00f; break;
//		case ITEM2(7,62):
//		case ITEM2(8,62):
//		case ITEM2(9,62):
//		case ITEM2(10,62):
//		case ITEM2(11,62):cl.r = 0.10f; cl.g = 0.60f; cl.b = 0.50f; break;
//		//Duel Master
//		case ITEM2(0,41): cl.r = 0.30f; cl.g = 0.20f; cl.b = 0.00f; break;
//		case ITEM2(6,31): cl.r = 0.80f; cl.g = 0.30f; cl.b = 0.10f; break;
//		case ITEM2(8,63):
//		case ITEM2(9,63):
//		case ITEM2(10,63):
//		case ITEM2(11,63):cl.r = 0.40f; cl.g = 0.40f; cl.b = 0.40f; break;
//		//Lord Emperor
//		case ITEM2(2,20): cl.r = 0.90f; cl.g = 0.50f; cl.b = 0.20f; break;
//		case ITEM2(6,30): cl.r = 0.90f; cl.g = 0.50f; cl.b = 0.20f; break;
//		case ITEM2(7,64):
//		case ITEM2(8,64):
//		case ITEM2(9,64):
//		case ITEM2(10,64):
//		case ITEM2(11,64):cl.r = 0.40f; cl.g = 0.40f; cl.b = 0.40f; break;
//		//Dimention Master
//        case ITEM2(5,41): cl.r = 0.10f; cl.g = 0.30f; cl.b = 0.50f; break;
//		case ITEM2(7,65):
//		case ITEM2(8,65):
//		case ITEM2(9,65):
//		case ITEM2(10,65):
//		case ITEM2(11,65):cl.r = 0.40f; cl.g = 0.40f; cl.b = 0.40f; break;
//        default:OriginalGlow(dwItemId, uk1, uk2, cl, bUkn);
//    }
//}

//int Item::SocketItems(signed int a1)
//{
//	switch(a1)
//	{
//		case ITEM(0,40):
//		case ITEM(0,41):
//		case ITEM(2,20):
//		case ITEM(4,30):
//		case ITEM(5,40):
//		case ITEM(5,41):
//		case ITEM(6,30):
//		case ITEM(6,31):
//		case ITEM(6,32):
//		case ITEM(6,33):
//			return 1;
//	}
//
//	if( a1 >= ITEM(7,60) && a1 <= ITEM(7,65) ||
//		a1 >= ITEM(8,60) && a1 <= ITEM(8,65) ||
//		a1 >= ITEM(9,60) && a1 <= ITEM(9,65) ||
//		a1 >= ITEM(10,60) && a1 <= ITEM(10,65) ||
//		a1 >= ITEM(11,60) && a1 <= ITEM(11,65) )
//	{
//		return 1;
//	}
//	else
//	{
//		SocketItemOriginal(a1);
//	}
//}

bool Item::IsCustomJewels(WORD ItemID, bool Preview)
{
	if( Preview )
	{
		ItemID -= ITEM_INTER;
	}
	// ----
	if( ItemID >= ITEM(14, 180) && ItemID <= ITEM(14, 188) )
	{
		return true;
	}

	if( ItemID == ITEM(14, 190) )
	{
		return true;
	}

	if(!g_ExLicense.CheckUser(MedoniAndrei))
	{
		if( ItemID == ITEM(14, 200) )
		{
			return true;
		}
	}

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))
	{
		if( ItemID == ITEM(14, 200) )
		{
			return true;
		}
	}

#if(JEWEL_OF_PVP==TRUE)
	if( ItemID == ITEM(14, 188) || ItemID == ITEM(14, 189) )
	{
		return true;
	}
#endif
#ifdef EXCLUSIVE_AMYLET
	if( ItemID >= ITEM(13, 147) && ItemID <= ITEM(13, 156) )
	{
		return true;
	}
#endif
	// ----
	return false;
}

bool Item::IsWings2_5(WORD ItemID, bool Preview)
{
	if( Preview )
	{
		ItemID -= ITEM_INTER;
	}
	if( ItemID >= ITEM(12, 186) && ItemID <= ITEM(12, 188) )
	{
		return true;
	}
	return false;
}

bool Item::IsWings4(WORD ItemID, bool Preview)
{
	if( Preview )
	{
		ItemID -= ITEM_INTER;
	}
	if( ItemID >= ITEM(12, 180) && ItemID <= ITEM(12, 185) )
	{
		return true;
	}
	return false;
}

bool Item::IsWings5(WORD ItemID, bool Preview)
{
	if( Preview )
	{
		ItemID -= ITEM_INTER;
	}
	if( ItemID >= ITEM(12, 189) && ItemID <= ITEM(12, 194) )
	{
		return true;
	}
	return false;
}
bool Item::IsWings6(WORD ItemID, bool Preview)
{
	if( Preview )
	{
		ItemID -= ITEM_INTER;
	}
	if( ItemID >= ITEM(12, 195) && ItemID <= ITEM(12, 196) )
	{
		gConsole.Output(cGREY, "%d - 196, return true", ItemID);
		return true;
	}

	if( ItemID >= ITEM(12, 197) && ItemID <= ITEM(12, 220) )
	{
		gConsole.Output(cGREY, "%d - 220, return true", ItemID);
		return true;
	}

	//gConsole.Output(cGREY, "%d, return false", ItemID);
	return false;
}

bool Item::IsCustomWings(WORD ItemID, bool Preview)
{
	if(this->IsWings2_5(ItemID, Preview)) return true;
	if(this->IsWings4(ItemID, Preview)) return true;
	if(this->IsWings5(ItemID, Preview)) return true;
	if(this->IsWings6(ItemID, Preview)) return true;
	return false;
}

void Item::PreviewCharSet(int ObjectIndex, BYTE * CharSet, lpViewObj Object, int Mode)
{
	pPreviewCharSet(ObjectIndex, CharSet, Object, Mode);
	// ----
//#ifdef NEWWINGS
	lpViewObj lpObj;
	// ----
	if( Object == 0 )
	{
		lpObj = &*(lpViewObj)pGetPreviewStruct(pPreviewThis(), ObjectIndex);
	}
	else
	{
		lpObj = Object;
	}
	// ----
	BYTE CustomWings = CharSet[16]  >> 2/* & 7*/;//Conflict
	// ----
	//gConsole.Output(2,"%d",CustomWings);
	if( CustomWings > 0 )
	{
		lpObj->WingsSlot = ITEM2(12, 180) + (CustomWings - 1);
	}
//#endif

	#if(ENABLE_PETEX)
	g_PetEx.PreviewCharSet(lpObj, CharSet, Object, Mode);
	#endif	

}

int Item::IsWings(LPVOID This, LPVOID EDX, DWORD ItemID)
{
	if( gItem.IsCustomWings(ItemID, false) )
	{
		return true;
	}
	// ----
	return pIsWings(This, ItemID);
}
// ----------------------------------------------------------------------------------------------

bool Item::GetUpgradeFlag(LPVOID This, LPVOID EDX, ObjectItem * lpSource, ObjectItem * lpTarget)
{
	BYTE TargetLevel = (lpTarget->Level >> 3) & 0xF;
	// ----
	if( gItem.IsCustomJewels(lpSource->ItemID, false) )
	{
		return true;
	}
	// ----
	if( gItem.IsCustomWings(lpTarget->ItemID, false) )
	{
		if( lpSource->ItemID == ITEM(14, 13) )
		{
			if( TargetLevel >= 0 && TargetLevel <= 5 )
			{
				return true;
			}
		}
		else if( lpSource->ItemID == ITEM(14, 14) )
		{
			if( TargetLevel >= 0 && TargetLevel <= 8 )
			{
				return true;
			}
		}
	}
	// ----
	return pIsUpgradeItem(This, lpSource, lpTarget);
}
// ----------------------------------------------------------------------------------------------


bool Item::AllowRepairWings(ObjectItem * lpItem)
{
	if( gItem.IsCustomWings(lpItem->ItemID, false) )
	{
		return true;
	}
	// ----
	return pAllowRepairWings(lpItem);
}
// ----------------------------------------------------------------------------------------------

void Item::SetOption(ObjectItem * lpItem, BYTE Option, BYTE Special, BYTE Value)
{
	pSetItemOption(lpItem, Option, Special, Value);

	return;
	// ----
	if( !gItem.IsCustomWings(lpItem->ItemID, false) )
	{
		return;
	}

#ifdef exDEBUG_CODE
		//gConsole.Output(2,"SetOption");
#endif

	// ----
	int ItemAttr		= *(DWORD*)0x8128AC0 + 84 * lpItem->ItemID;
	int SpecialValue	= GET_ITEMOPT0(Option) + 4 * (GET_ITEMOPT16(Special) >> 6);	
	// ----
	lpItem->ReqLevel	= *(short*)(ItemAttr + 60);
	// ----
	if( Special & MAX_ITEMOPT_BIT >= 10 && Special & MAX_ITEMOPT_BIT <= 15 )
	{
		lpItem->Unknown14 += 1;
	}

	lpItem->SpecialCount = 0;




	// ----
	if( GET_ITEMOPT_LUCK(Option) ) //-> Add luck option
	{
		//lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::Luck;
		*(WORD *)(lpItem + 2 * (*(BYTE *)(lpItem + 37))++ + 38) = 85;
		lpItem->SpecialCount++;
#ifdef exDEBUG_CODE
		//gConsole.Output(2,"GET_ITEMOPT_LUCK %d",lpItem->SpecialCount);
#endif
	}
	//// ----
	if( GET_ITEMOPT_0(Special) ) //-> Set IgnorOpDefense
	{
		lpItem->SpecialValue[lpItem->SpecialCount]	= 8;
		lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::IgnorOpDefense;
		lpItem->SpecialCount++;
#ifdef exDEBUG_CODE
		//gConsole.Output(2,"GET_ITEMOPT_0 %d",lpItem->SpecialCount);
#endif
	}
	// ----
	if( GET_ITEMOPT_1(Special) ) //-> Set ReturnAttack
	{
		lpItem->SpecialValue[lpItem->SpecialCount]	= 10;
		lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::ReturnAttack;
		lpItem->SpecialCount++;
#ifdef exDEBUG_CODE
		//gConsole.Output(2,"GET_ITEMOPT_1 %d",lpItem->SpecialCount);
#endif
	}
	// ----
	if( GET_ITEMOPT_2(Special) ) //-> Set CompleteLife
	{
		lpItem->SpecialValue[lpItem->SpecialCount]	= 5;
		lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::CompleteLife;
		lpItem->SpecialCount++;
#ifdef exDEBUG_CODE
		//gConsole.Output(2,"GET_ITEMOPT_2 %d",lpItem->SpecialCount);
#endif
	}
	// ----
	if( GET_ITEMOPT_3(Special) ) //-> Set CompleteMana
	{
		lpItem->SpecialValue[lpItem->SpecialCount]	= 5;
		lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::CompleteMana;
		lpItem->SpecialCount++;
#ifdef exDEBUG_CODE
		//gConsole.Output(2,"GET_ITEMOPT_2 %d",lpItem->SpecialCount);
#endif
	}
	// ----
	if( SpecialValue < 1 )
	{
		return;
	}
	// ----

	switch(lpItem->ItemID) //-> Set add option
	{
	case ITEM(12, 180):	//-> DW
		{
			if( GET_ITEMOPT_4(Special) )
			{
				lpItem->SpecialValue[lpItem->SpecialCount]	= 4 * SpecialValue;
				lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::WizardryDamage;
				lpItem->SpecialCount++;
			}
			else if( GET_ITEMOPT_5(Special) )
			{
				lpItem->SpecialValue[lpItem->SpecialCount]	= 4 * SpecialValue;
				lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::Defense;
				lpItem->SpecialCount++;
			}
			else
			{
				lpItem->SpecialValue[lpItem->SpecialCount]	= SpecialValue;
				lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::HPRecovery;
				lpItem->SpecialCount++;
			}
		}
		break;
		// --
	case ITEM(12, 183):	//-> MG
		{
			if( GET_ITEMOPT_4(Special) )
			{
				lpItem->SpecialValue[lpItem->SpecialCount]	= 4 * SpecialValue;
				lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::Damage;
				lpItem->SpecialCount++;
			}
			else if( GET_ITEMOPT_5(Special) )
			{
				lpItem->SpecialValue[lpItem->SpecialCount]	= 4 * SpecialValue;
				lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::WizardryDamage;
				lpItem->SpecialCount++;
			}
			else
			{
				lpItem->SpecialValue[lpItem->SpecialCount]	= SpecialValue;
				lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::HPRecovery;
				lpItem->SpecialCount++;
			}
		}
		break;
		// --
	case ITEM(12, 181):	//-> DK
	case ITEM(12, 182):	//-> ELF
	case ITEM(12, 184):	//-> DL
	case ITEM(12, 186):	//-> MONK
		{
			if( GET_ITEMOPT_4(Special) )
			{
				lpItem->SpecialValue[lpItem->SpecialCount]	= 4 * SpecialValue;
				lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::Damage;
				lpItem->SpecialCount++;
			}
			else if( GET_ITEMOPT_5(Special) )
			{
				lpItem->SpecialValue[lpItem->SpecialCount]	= 4 * SpecialValue;
				lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::Defense;
				lpItem->SpecialCount++;
			}
			else
			{
				lpItem->SpecialValue[lpItem->SpecialCount]	= SpecialValue;
				lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::HPRecovery;
				lpItem->SpecialCount++;
			}
		}
		break;
		// --
	case ITEM(12, 185):	//-> SUM
		{
			if( GET_ITEMOPT_4(Special) )
			{
				lpItem->SpecialValue[lpItem->SpecialCount]	= 4 * SpecialValue;
				lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::WizardryDamage;
				lpItem->SpecialCount++;
			}
			else if( GET_ITEMOPT_5(Special) )
			{
				lpItem->SpecialValue[lpItem->SpecialCount]	= 4 * SpecialValue;
				lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::CurseSpell;
				lpItem->SpecialCount++;
			}
			else
			{
				lpItem->SpecialValue[lpItem->SpecialCount]	= SpecialValue;
				lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::HPRecovery;
				lpItem->SpecialCount++;
			}
		}
		break;
	}
	if( gItem.IsCustomWings(lpItem->ItemID, false) )
	{
			if( GET_ITEMOPT_4(Special) )
			{
				lpItem->SpecialValue[lpItem->SpecialCount]	= 4 * SpecialValue;
				lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::Damage;
				lpItem->SpecialCount++;
			}
			else if( GET_ITEMOPT_5(Special) )
			{
				lpItem->SpecialValue[lpItem->SpecialCount]	= 4 * SpecialValue;
				lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::Defense;
				lpItem->SpecialCount++;
			}
			else
			{
				lpItem->SpecialValue[lpItem->SpecialCount]	= SpecialValue;
				lpItem->SpecialType[lpItem->SpecialCount]	= eItemOption::HPRecovery;
				lpItem->SpecialCount++;
			}
	}
}
// ----------------------------------------------------------------------------------------------

//sub_6D8F20(388, &v301, a1 + 264, &v297, 1, a1, -1, 0, 0, 0, 0.0, -1);	//Create Effect
//CreateEffect(388,Position,o->Angle,Light2,2,o,-1,0,-2.1f,0,0);


//int __thiscall sub_545030(void *this, int a2, int a3, int a4, char a5)
#define sub_545030	((int(__thiscall*)(LPVOID this2, int a2, int & a3, int & a4, char a5)) 0x545030)
#define sub_969AD0	((LPVOID(__thiscall*)(LPVOID this2, int a1)) 0x969AD0)
//int __cdecl sub_4CDA10()
#define sub_4CDA10	((LPVOID(__cdecl*)()) 0x4CDA10)
//sub_545030(
	//(void *)v398,(int)((char *)&unk_7BC08A0 + 48 * *(&v303 + l)),(int)&v270,(int)&v300,1);
	//#include "Skill.h"
void Item::SetItemEffect(int Arg1, int ModelID, VAngle Angle, int Arg4, int ItemLevel, char Arg6, int Arg7, int Arg8, int Arg9)
{
	pSetItemEffect(Arg1, ModelID, Angle, Arg4, ItemLevel, Arg6, Arg7, Arg8, Arg9);

	if(ModelID == 1198)
	{
		//gConsole.Output(cGREEN, "%d | %d", 
		//	ModelID, Arg1
		//	);
	}

	if(ModelID == 1212)
	{
		//Angle.X = 0.0;
		//Angle.Y = 1.0;
		//Angle.Z = 0.0;

		//gConsole.Output(cGREEN, "%d | %d", 
		//	ModelID, Arg1
		//	);

	}

	//gEffect.DynamicEffectEx(ModelID, (vec3_t&)Angle, Arg4, 

}
// ----------------------------------------------------------------------------------------------

#define pSetItemEffect2			((void(__cdecl*)(float a4, float a5, float a6, lpViewObj Object, float a8, DWORD ModelID, int a10, char a11, char a12, char a13, signed int a14, char a15)) 0x5655C0)

void Item::SetItemEffect2(float a4, float a5, float a6, lpViewObj Object, float a8, DWORD ModelID, int a10, char a11, char a12, char a13, signed int a14, char a15)
{
	return pSetItemEffect2(a4, a5, a6, Object, a8, ModelID, a10, a11, a12, a13, a14, a15);
}

short Item::GetMaxDurability(ObjectItem * lpItem, int ScriptStruct, int Level)
{
	if( gItem.IsCustomWings(lpItem->ItemID, false) )
	{
		return 255;
	}
	// ----
	return pGetMaxDurability(lpItem, ScriptStruct, Level);
}
// ----------------------------------------------------------------------------------------------


void __cdecl Item::Glow(DWORD dwItemId, DWORD uk1, DWORD uk2, FRGB& cl, BYTE bUkn)
{
	OriginalGlow(dwItemId, uk1, uk2, cl, bUkn);

	for(int i=0;i<gConfig.CountGlow;i++)
	{
		if(gConfig.iGlow[i].Type == -1)
		{
			if(dwItemId == ITEM2(7,gConfig.iGlow[i].Index))
			{
				cl.r = gConfig.iGlow[i].Red; cl.g = gConfig.iGlow[i].Green; cl.b = gConfig.iGlow[i].Blue;
			}
			else if(dwItemId == ITEM2(8,gConfig.iGlow[i].Index))
			{
				cl.r = gConfig.iGlow[i].Red; cl.g = gConfig.iGlow[i].Green; cl.b = gConfig.iGlow[i].Blue;
			}
			else if(dwItemId == ITEM2(9,gConfig.iGlow[i].Index))
			{
				cl.r = gConfig.iGlow[i].Red; cl.g = gConfig.iGlow[i].Green; cl.b = gConfig.iGlow[i].Blue;
			}
			else if(dwItemId == ITEM2(10,gConfig.iGlow[i].Index))
			{
				cl.r = gConfig.iGlow[i].Red; cl.g = gConfig.iGlow[i].Green; cl.b = gConfig.iGlow[i].Blue;
			}
			else if(dwItemId == ITEM2(11,gConfig.iGlow[i].Index))
			{
				cl.r = gConfig.iGlow[i].Red; cl.g = gConfig.iGlow[i].Green; cl.b = gConfig.iGlow[i].Blue;
			}
		}
		else if(dwItemId == ITEM2(gConfig.iGlow[i].Type,gConfig.iGlow[i].Index))
		{
			cl.r = gConfig.iGlow[i].Red; cl.g = gConfig.iGlow[i].Green; cl.b = gConfig.iGlow[i].Blue;
		}
	}
}

char* Item::GetItemName(int ItemType)
{
	return (char*)(*(DWORD*)0x8128AC0 + 84 * ItemType);
}

#if(FIX_CORD_ITEM_TEXT)

#define pFixCordItemTextX ((int (__cdecl*)(signed int a1, signed int a2, int a3, signed int a4, int a5, int a6, int a7)) 0x005BF700)

int Item::FixCordItemTextX(signed int a1, signed int a2, int a3, signed int a4, int a5, int a6, int a7)
{
	if(a2 < 0)
	{
		a2 = 20;
	}


	return pFixCordItemTextX(a1, a2, a3, a4, a5, a6, a7);
}

#endif

//
//int Item::PickUpItemInfo(int a1, char a2)
//{
//#ifdef exDEBUG_CODE
//	gConsole.Output(cGREEN,"%d E61728=%d", a1, *(DWORD*)0xE61728);
//#endif	
//	return pPickUpItemInfo(a1, a2);
//}
//
//void Item::SendPickUpItemInfo()
//{
////	if(*(int*)0xE61728 != -1)
////	{
////		PMSG_REQ_PICKUP_INFO pMsg;
////		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xBF, sizeof(pMsg));
////		pMsg.ItemNum = *(int*)0xE61728;
////		gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
////
////#ifdef exDEBUG_CODE
////		gConsole.Output(cGREEN,"0xE61728 = %d", *(int*)0xE61728);
////#endif	
////	}
//}
//
//void Item::RecvPickUpItemInfo()
//{
//
//}
//
//void Item::DrawPickUpItemInfp()
//{
//	//__try {
//	//	LinkNode<ItemPost> * item_node = ( LinkNode<ItemPost> * ) * ( unsigned long * ) &message[message_len - 1 - 8 + 2];
//	//	ItemPost * item_post = item_node->value();
//	//	ObjectItem * item_data = ( ObjectItem * ) &item_post->item_;
//	//	// set show item tool tip
//	//	//*gPostItem.last_tickcount_view_ = GetTickCount();
//	//	//*gPostItem.current_item_post_ = item_data;
//	//}  __except (EXCEPTION_EXECUTE_HANDLER)
//	//{
//	//}
//
//	ItemBmdStruct* ItemInfo = pGetItemBmdStruct(this->m_PickUp.ItemID);
//
//	this->m_PickUp.DamageMax = ItemInfo->MaxDmg;
//	this->m_PickUp.DamageMin = ItemInfo->MinDmg;
//
//	
//	if(*(int*)0xE61728 != -1)
//	{
//		gInterface.DrawItemToolTipText ( (void*)&this->m_PickUp, pCursorX + 80, pCursorY - 80 );
//	}
//}