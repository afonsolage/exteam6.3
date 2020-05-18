#ifndef MONSTERITEMMNG_H
#define MONSTERITEMMNG_H


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\common\zzzitem.h"


#define MAX_ITEM_IN_MONSTER 1000
#define MAX_LEVEL_MONSTER 200	//150
#define MAX_MAGIC_IN_MONSTER 100

struct MONS_ITEM_DROP_RATE
{
	DWORD m_Level;
	DWORD m_MagicBookRate;
	DWORD m_BlessRate;
	DWORD m_SoulRate;
	DWORD m_ChaosRate;
	DWORD m_LifeRate;
	DWORD m_CreationRate;
	DWORD m_FeatherRate;
	DWORD m_ItemRate;
};


class CMonsterItemMng
{

public:

	CMonsterItemMng();
	virtual ~CMonsterItemMng();

	void Init();
	void Clear();

	void LoadMonsterItemDropRate();
	void MakeJewelItem();

	BYTE InsertItem(int monsterlevel, int type, int index, int itemlevel,  int op1, int op2, int op3);

	CItem* GetItem(int monsterlevel);
	CItem* GetItemEx(int monsterlevel);

	void gObjGiveItemSearch(int monsterlevel, int maxlevel);
	void gObjGiveItemSearchEx(int monsterlevel, int maxlevel);

	void MagicBookGiveItemSearch(int monsterlevel, int maxlevel);
	void NormalGiveItemSearchEx(int monsterlevel,  int maxlevel);

	int CheckMonsterDropItem(int type, int index);

	float GetItemDropRate(int type, int index, int level, int monsterlevel);
	float GetMagicBookDropRate(int monsterlevel);
private:

	CItem* m_MonsterInvenItems[MAX_LEVEL_MONSTER];	// 4
	int m_iMonsterInvenItemCount[MAX_LEVEL_MONSTER];	//25C
	char MonsterName[255];	// 4B4

	MONS_ITEM_DROP_RATE m_MonsterItemDropRate[MAX_LEVEL_MONSTER];
	bool m_bLoad;
	bool m_bExActive;

	int m_iMagicBookItmeCount[MAX_LEVEL_MONSTER];
	CItem *m_MagicBookItems[MAX_LEVEL_MONSTER];
	CItem *m_JewelOfBlessItem;
	CItem *m_JewelOfSoulItem;
	CItem *m_JewelOfChaosItem;
	CItem *m_JewelOfLifeItem;
	CItem *m_JewelOfCreationItem;
	CItem *m_LochsFeatherItem;

};


extern CMonsterItemMng g_MonsterItemMng;

#endif