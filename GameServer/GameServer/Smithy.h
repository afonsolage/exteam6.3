#pragma once

#include "StdAfx.h"
#include "..\\include\prodef.h"

#if(CUSTOM_SMITHY == TRUE)

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

struct GC_SmithyInit
{
	PBMSG_HEAD2 h;
	bool result;
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
	void Read(char* filename);
	void GCInitItem(int aIndex);
	void GCIemSend(int aIndex);
	void GCSettingsSend(int aIndex);
	void CGCreateItem(CG_SmithyCreateItem* aRecv, int aIndex);
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
};
extern CSmithy g_Smithy;

#endif