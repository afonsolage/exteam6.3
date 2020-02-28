#pragma once

#include "stdafx.h"
#include "Protocol.h"

#if(CUSTOM_SMITHY == TRUE)

#define SMITHY_CLASS	0
#define SMITHY_CATEGORY	1
#define SMITHY_ITEM		2
#define SMITHY_OPTION	3

static char* Menu1[7] = 
{
	"Dark Wizard",
	"Dark Knight",
	"Elf",
	"Magic Gladiator",
	"Dark Lord",
	"Summoner",
	"Rage Fighter"
};

static char* Menu2[] = 
{
	"Weapon",
	"Shield",
	"Helm",
	"Armor",
	"Pants",
	"Gloves",
	"Boots",
	"Wings",
	"Ring & Pendant",
};

struct GC_SmithyInit
{
	PBMSG_HEAD2 h;
	bool result;
};

struct GC_SmithySettings
{
	PBMSG_HEAD2 h;
	unsigned char MaxLevel;
	unsigned short LevelPrice;
	unsigned short LuckPrice;
	unsigned short AddPrice;
	unsigned short Opt1Price;
	unsigned short Opt2Price;
	unsigned short Opt3Price;
	unsigned short Opt4Price;
	unsigned short Opt5Price;
	unsigned short Opt6Price;
	unsigned short MaxExlOpt;
};

struct CG_SmithyCreateItem
{
	PBMSG_HEAD2 h;
	unsigned short Item;
	unsigned char ItemLevel;
	unsigned char ItemAdd;
	bool ItemLuck;
	bool ItemOpt1;
	bool ItemOpt2;
	bool ItemOpt3;
	bool ItemOpt4;
	bool ItemOpt5;
	bool ItemOpt6;
};

struct GC_SmithyDATA
{
	PBMSG_HEAD2 h;
	unsigned char Class;
	unsigned char Type;
	unsigned char Index;
	unsigned int  Price;
};

struct SmithyDATA
{
	unsigned char Class;
	unsigned char Type;
	unsigned char Index;
	unsigned int  Price;
};

class CSmithy
{
public:
	CSmithy();
	~CSmithy();
	void Init();
	void Load();
	void LoadImg();
	void BindImg();
	void Draw();
	bool DrawCheckBuy();
	void DrawItem();
	void Button(DWORD Event);
	void GCItemInit(GC_SmithyInit* aRecv);
	void GCItemSend(GC_SmithyDATA* aRecv);
	void GCSettingsRecv(GC_SmithySettings* aRecv);
	void CGCreateItem();
	int GetCategory(int Type);
	int GetMaxItemCategory();
	int GetItemPrice();
	void CloseWindow();
	bool CheckRing();
	bool CheckPend();
	bool CheckExlOpt();
	unsigned char CheckWingLevel();
	unsigned char MainPage;
	unsigned char Class;
	unsigned char Category;
	unsigned char CategoryPage;
	unsigned short Item;
	unsigned char ItemLevel;
	unsigned char ItemAdd;
	bool ItemLuck;
	bool ItemOpt1;
	bool ItemOpt2;
	bool ItemOpt3;
	bool ItemOpt4;
	bool ItemOpt5;
	bool ItemOpt6;
	unsigned char MaxLevel;
	unsigned short LevelPrice;
	unsigned short LuckPrice;
	unsigned short AddPrice;
	unsigned short Opt1Price;
	unsigned short Opt2Price;
	unsigned short Opt3Price;
	unsigned short Opt4Price;
	unsigned short Opt5Price;
	unsigned short Opt6Price;
	unsigned short MaxExlOpt;
	std::vector<SmithyDATA> itemdata;
	bool License;
};
extern CSmithy g_Smithy;

/*
2 wing:
	2 -- Increase Attackin(Wizardy) speed +5
	3 - Max Ag + 50 Increased
	4 - Ignor Optionent's defensive power by 3%%
	5 - Mana + 50 Increased
	6 - HP + 50 Increased

3 wing:
	3 - Complete reco of Mana in 5%% rate
	4 - Complete recoy of Life in 5%% rate
	5 - Return the enemy attack power in 5%%
	6 - Ignor openent defensive power by 5%%
*/

#endif