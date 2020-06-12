//GameServer 1.00.90 JPN - Completed
#include "stdafx.h"
#include "MonsterItemMng.h"
#include "MonsterAttr.h"
#include "GameMain.h"
#include "LogProc.h"
#include "CashShop.h"
#include "LuckyItem.h"
#include "LargeRand.h"

CMonsterItemMng g_MonsterItemMng;


CMonsterItemMng::CMonsterItemMng()
{
	memset(this->m_iMonsterInvenItemCount, 0, sizeof(this->m_iMonsterInvenItemCount));
	memset(this->m_MonsterItemDropRate, 0, sizeof(this->m_MonsterItemDropRate));
	memset(this->m_MonsterInvenItems, 0, sizeof(m_MonsterInvenItems));
	memset(this->m_MagicBookItems, 0, sizeof(m_MagicBookItems));

	this->m_JewelOfCreationItem = nullptr;
	this->m_JewelOfBlessItem = nullptr;
	this->m_JewelOfSoulItem = nullptr;
	this->m_JewelOfChaosItem = nullptr;
	this->m_JewelOfLifeItem = nullptr;
	this->m_JewelOfCreationItem = nullptr;
	this->m_LochsFeatherItem = nullptr;
}


CMonsterItemMng::~CMonsterItemMng()
{
	this->Clear();
}

void CMonsterItemMng::LoadMonsterItemDropRate()
{
	char* path = gDirPath.GetNewPath("Custom\\MonsterDropItem.txt");
	FILE *file = fopen(path, "r");

	if (file == NULL)
	{
		MessageBoxA(0, path, "CRITICAL ERROR", 0);
		ExitProcess(1);
		return;
	}

	char Buff[256];
	bool firstLine = true;
	while (!feof(file))
	{
		fgets(Buff, 256, file);

		if (Buff[0] == '/' && Buff[1] == '/')
			continue;

		if (firstLine)
		{
			int tmp;
			sscanf(Buff, "%d", &tmp);
			m_bExActive = tmp >= 1;
			firstLine = false;
			continue;
		}

		unsigned int monsterLevel;
		double blessRate;
		double soulRate;
		double lifeRate;
		double creationRate;
		double chaosRate;
		double featherRate;
		double magicBookRate;

		sscanf(Buff, "%d %lf %lf %lf %lf %lf %lf %lf", &monsterLevel, &blessRate, &soulRate, &lifeRate, &creationRate, &chaosRate, &featherRate, &magicBookRate);

		this->m_MonsterItemDropRate[monsterLevel].m_BlessRate = blessRate * 10000000.0;
		this->m_MonsterItemDropRate[monsterLevel].m_SoulRate = soulRate * 10000000.0;
		this->m_MonsterItemDropRate[monsterLevel].m_LifeRate = lifeRate * 10000000.0;
		this->m_MonsterItemDropRate[monsterLevel].m_CreationRate = creationRate * 10000000.0;
		this->m_MonsterItemDropRate[monsterLevel].m_ChaosRate = chaosRate * 10000000.0;
		this->m_MonsterItemDropRate[monsterLevel].m_FeatherRate = featherRate * 10000000.0;
		this->m_MonsterItemDropRate[monsterLevel].m_MagicBookRate = magicBookRate * 10000000.0;

		auto varSum = +this->m_MonsterItemDropRate[monsterLevel].m_LifeRate
			+ this->m_MonsterItemDropRate[monsterLevel].m_CreationRate
			+ this->m_MonsterItemDropRate[monsterLevel].m_ChaosRate
			+ this->m_MonsterItemDropRate[monsterLevel].m_SoulRate
			+ this->m_MonsterItemDropRate[monsterLevel].m_BlessRate
			+ this->m_MonsterItemDropRate[monsterLevel].m_FeatherRate
			+ this->m_MonsterItemDropRate[monsterLevel].m_MagicBookRate;

		this->m_MonsterItemDropRate[monsterLevel].m_ItemRate = 10000000 - varSum;
	}

	fclose(file);

	m_bLoad = true;
}

void CMonsterItemMng::Init()
{
	this->Clear();

	this->LoadMonsterItemDropRate();
	this->MakeJewelItem();

	for (int i = 0; i < MAX_LEVEL_MONSTER; i++)
	{
		this->m_MonsterInvenItems[i] = new CItem[MAX_ITEM_IN_MONSTER];
		this->m_MagicBookItems[i] = new CItem[MAX_ITEM_IN_MONSTER];
	}

	LPMONSTER_ATTRIBUTE lpm;

	for (int i = 0; i < MAX_MONSTER_TYPE; i++)
	{
		lpm = gMAttr.GetAttr(i);

		if (lpm != NULL)
		{
			strcpy(this->MonsterName, lpm->m_Name);

			if (lpm->m_Level != 0)
			{
				if (m_bExActive)
					this->gObjGiveItemSearchEx(lpm->m_Level, lpm->m_MaxItemLevel);
				else
					this->gObjGiveItemSearch(lpm->m_Level, lpm->m_MaxItemLevel);
			}
		}
	}
}


void CMonsterItemMng::Clear()
{
	memset(this->m_iMonsterInvenItemCount, 0, sizeof(this->m_iMonsterInvenItemCount));
	memset(this->m_MonsterItemDropRate, 0, sizeof(this->m_MonsterItemDropRate));

	for (int i = 0; i < MAX_LEVEL_MONSTER; i++)
	{
#if(FIX_MEMLEAK)
		if (this->m_MonsterInvenItems[i] != NULL) //Memleak 2
		{
			delete[] this->m_MonsterInvenItems[i];
			this->m_MonsterInvenItems[i] = NULL;
		}

		if (this->m_MagicBookItems[i] != NULL)
		{
			delete[] this->m_MagicBookItems[i];
			this->m_MagicBookItems[i] = NULL;
		}
#else
		delete this->m_MonsterInvenItems[i];
		delete[] this->m_MagicBookItems[i];
#endif
	}

	if (this->m_JewelOfBlessItem)
	{
		delete this->m_JewelOfBlessItem;
		this->m_JewelOfBlessItem = nullptr;
	}
	if (this->m_JewelOfSoulItem)
	{
		delete this->m_JewelOfSoulItem;
		this->m_JewelOfSoulItem = nullptr;
	}
	if (this->m_JewelOfChaosItem)
	{
		delete this->m_JewelOfChaosItem;
		this->m_JewelOfChaosItem = nullptr;
	}
	if (this->m_JewelOfLifeItem)
	{
		delete this->m_JewelOfLifeItem;
		this->m_JewelOfLifeItem = nullptr;
	}
	if (this->m_JewelOfCreationItem)
	{
		delete this->m_JewelOfCreationItem;
		this->m_JewelOfCreationItem = nullptr;
	}
	if (this->m_LochsFeatherItem)
	{
		delete this->m_LochsFeatherItem;
		this->m_LochsFeatherItem = nullptr;
	}

	m_bLoad = false;
	m_bExActive = false;
}

void CMonsterItemMng::MakeJewelItem()
{
	if (!m_bExActive)
		return;

	this->m_JewelOfBlessItem = new CItem;
	this->m_JewelOfSoulItem = new CItem;
	this->m_JewelOfChaosItem = new CItem;
	this->m_JewelOfLifeItem = new CItem;
	this->m_JewelOfCreationItem = new CItem;
	this->m_LochsFeatherItem = new CItem;

	this->m_JewelOfBlessItem->Convert(ITEMGET(14, 13), 0, 0, 0, 0, 0, 0, 0, -1, 0, 3);
	this->m_JewelOfBlessItem->m_Level = 0;
	this->m_JewelOfBlessItem->m_Durability = this->m_JewelOfBlessItem->m_BaseDurability;

	this->m_JewelOfSoulItem->Convert(ITEMGET(14, 14), 0, 0, 0, 0, 0, 0, 0, -1, 0, 3);
	this->m_JewelOfSoulItem->m_Level = 0;
	this->m_JewelOfSoulItem->m_Durability = this->m_JewelOfSoulItem->m_BaseDurability;

	this->m_JewelOfChaosItem->Convert(ITEMGET(12, 15), 0, 0, 0, 0, 0, 0, 0, -1, 0, 3);
	this->m_JewelOfChaosItem->m_Level = 0;
	this->m_JewelOfChaosItem->m_Durability = this->m_JewelOfChaosItem->m_BaseDurability;

	this->m_JewelOfLifeItem->Convert(ITEMGET(14, 16), 0, 0, 0, 0, 0, 0, 0, -1, 0, 3);
	this->m_JewelOfLifeItem->m_Level = 0;
	this->m_JewelOfLifeItem->m_Durability = this->m_JewelOfLifeItem->m_BaseDurability;

	this->m_JewelOfCreationItem->Convert(ITEMGET(14, 22), 0, 0, 0, 0, 0, 0, 0, -1, 0, 3);
	this->m_JewelOfCreationItem->m_Level = 0;
	this->m_JewelOfCreationItem->m_Durability = this->m_JewelOfCreationItem->m_BaseDurability;

	this->m_LochsFeatherItem->Convert(ITEMGET(13, 14), 0, 0, 0, 0, 0, 0, 0, -1, 0, 3);
	this->m_LochsFeatherItem->m_Level = 0;
	this->m_LochsFeatherItem->m_Durability = this->m_LochsFeatherItem->m_BaseDurability;
}

BYTE CMonsterItemMng::InsertItem(int monsterlevel, int type, int index, int itemlevel, int op1, int op2, int op3)
{
	if (monsterlevel > MAX_LEVEL_MONSTER - 1 || monsterlevel < 0)
	{
		return -1;
	}

	int itemcount = this->m_iMonsterInvenItemCount[monsterlevel];

	if (itemcount >= MAX_ITEM_IN_MONSTER)
	{
		return -1;
	}

	if (type == 14 && index == 14)
	{
		int a = 0;
	}

	CItem * item = &this->m_MonsterInvenItems[monsterlevel][itemcount];
	int item_type = (type * MAX_SUBTYPE_ITEMS) + index;
	item->m_Level = itemlevel;
	item->Convert(item_type, op1, op2, op3, 0, 0, 0, NULL, 0xFF, 0, CURRENT_DB_VERSION);

	if (type == 13 && index == 10)
	{
		int rd = rand() % 100;
		item->m_Durability = rd + 100.0f;
	}
	else
	{
		item->m_Durability = item->m_BaseDurability;
	}

	itemcount++;
	this->m_iMonsterInvenItemCount[monsterlevel] = itemcount;
	return 0;
}


CItem * CMonsterItemMng::GetItem(int monsterlevel)
{
	if (monsterlevel > MAX_LEVEL_MONSTER - 1 || monsterlevel < 0)
	{
		return NULL;
	}

	int itemcount = this->m_iMonsterInvenItemCount[monsterlevel];

	if (itemcount <= 0)
	{
		return NULL;
	}

	int itemindex = rand() % itemcount;
	return &this->m_MonsterInvenItems[monsterlevel][itemindex];
}

void CMonsterItemMng::gObjGiveItemSearchEx(int monsterlevel, int maxlevel)
{
	if (this->m_iMonsterInvenItemCount[monsterlevel] == MAX_ITEM_IN_MONSTER)
	{
		return;
	}

	this->NormalGiveItemSearchEx(monsterlevel, maxlevel);
	this->MagicBookGiveItemSearch(monsterlevel, maxlevel);
}

void CMonsterItemMng::gObjGiveItemSearch(int monsterlevel, int maxlevel)
{
	int result;
	int incount = 0;
	int type;
	int index;

	if (monsterlevel > MAX_LEVEL_MONSTER - 1)
	{
		LogAdd("error-L3 : Monster Level Overflow~ %s %d", __FILE__, __LINE__);
		return;
	}

	int BallTable[22]; //season 4.5 changed

	BallTable[0] = 7;
	BallTable[1] = 8;
	BallTable[2] = 9;
	BallTable[3] = 10;
	BallTable[4] = 11;
	BallTable[5] = 12;
	BallTable[6] = 13;
	BallTable[7] = 14;
	BallTable[8] = 16;
	BallTable[9] = 17;
	BallTable[10] = 18;
	BallTable[11] = 19;
	BallTable[12] = 21;
	BallTable[13] = 22;
	BallTable[14] = 23;
	BallTable[15] = 24;
	BallTable[16] = 35;
	BallTable[17] = 44;//Season 4.5 addon
	BallTable[18] = 45;//Season 4.5 addon
	BallTable[19] = 46;//Season 4.5 addon
	BallTable[20] = 47;//Season 4.5 addon
	BallTable[21] = 48;//Season 4.5 addon

	while (true)
	{
		if ((rand() % 20) == 0) //Skills
		{
			if ((rand() % 2) != 0)
			{
				type = MAX_TYPE_ITEMS - 1;
				index = rand() % (g_MaxItemIndexOfEachItemType[type] + 1);
			}
			else
			{
				type = 12;
				index = BallTable[rand() % 17];
			}
		}
		else
		{
			type = rand() % MAX_TYPE_ITEMS;
			int iMaxItemIndex = g_MaxItemIndexOfEachItemType[type] + 1;
			index = rand() % iMaxItemIndex;

			if (type == 15 || (type == 12 && index != 15))
			{
				continue;
			}
		}

		if (type == 13 && index == 3)
		{
			continue;
		}

		if (this->m_bExActive)
		{
			if ((type == 14 && index == 13) //Jewel of Soul
				|| (type == 14 && index == 14) //Jewel of Bless
				|| (type == 14 && index == 16) //Jewel of Life
				|| (type == 14 && index == 22) //Jewel of Creation
				|| (type == 12 && index == 15) //Jewel of Chaos
				|| (type == 13 && index == 14)) //Loch's Feather
				continue;
		}

		if ((type == 13 && index == 32)
			|| (type == 13 && index == 33)
			|| (type == 13 && index == 34)
			|| (type == 13 && index == 35)
			|| (type == 13 && index == 36)
			|| (type == 13 && index == 37))
		{
			continue;
		}

		if ((type == 14 && index == 35)
			|| (type == 14 && index == 36)
			|| (type == 14 && index == 37)
			|| (type == 14 && index == 38)
			|| (type == 14 && index == 39)
			|| (type == 14 && index == 40))
		{
			continue;
		}
#ifdef OLDCASHSHOP
		if (IsCashItem(ITEMGET(type, index)) == TRUE)
		{
			continue;
		}

		if (CanItemTouchCash(ITEMGET(type, index)) == TRUE)
		{
			continue;
		}
#endif
#ifdef LUCKYITEM
		if (g_LuckyItemManager.IsLuckyItemTicket(ITEMGET(type, index)) == true)
		{
			continue;
		}
		// ----
		if (g_LuckyItemManager.IsLuckyItemEquipment(ITEMGET(type, index)) == true)
		{
			continue;
		}
#endif

		if ((type == 14 && index == 162)
			|| (type == 14 && index == 163)
			|| (type == 14 && index == 164)
			|| (type == 14 && index == 165)
			|| (type == 14 && index == 166))
		{
			continue;
		}

		//season 3.0 add-on
		if ((type == 14 && index == 45) ||
			(type == 14 && index == 46) ||
			(type == 14 && index == 47) ||
			(type == 14 && index == 48) ||
			(type == 14 && index == 49) ||
			(type == 14 && index == 50))
		{
			continue;
		}

		//season 2.5 add-on
		if ((type == 13 && index == 41))
		{
			continue;
		}

		if ((type == 13 && index < 8) ||
			((type == 14) && (index == 9 || index == 10 || index == 13 || index == 14 || index == 16 || index == 17 || index == 18 || index == 22)) ||
			(type == 12 && index == 15) ||
			(type == 13 && index == 14) ||
			(type == 14 && index == 31))
		{
			int perc = rand() % 11;
			BOOL bCheckDevil = FALSE;

			if (type == 12 && index == 15)
			{
				if (monsterlevel >= 13 && monsterlevel <= 66)
				{
					perc = rand() % 7;

					if (perc < 3)
					{
						perc = 0;
					}
				}
				else
				{
					perc = 1;
				}
			}

			if (type == 14 && index == 17)
			{
				if (gEyesOfDevilSquareDropRate <= 0)
				{
					gEyesOfDevilSquareDropRate = 1;
				}

				perc = rand() % gEyesOfDevilSquareDropRate;
				bCheckDevil = 1;

				if (gDevilSquareEvent == 0)
				{
					perc = 1;
				}
			}

			if (type == 14 && index == 18)
			{
				perc = rand() % gKeyOfDevilSquareDropRate;
				bCheckDevil = 1;

				if (gDevilSquareEvent == 0)
				{
					perc = 1;
				}

			}

			if (perc == 0)
			{
				if (bCheckDevil == 1)
				{
					int devilitemlevel = 0;

					if ((rand() % 5) != 0)
					{
						if (monsterlevel < 3)
						{
							devilitemlevel = 0;
						}
						else if (monsterlevel < 36)
						{
							devilitemlevel = 1;
						}
						else if (monsterlevel < 47)
						{
							devilitemlevel = 2;
						}
						else if (monsterlevel < 60)
						{
							devilitemlevel = 3;
						}
						else if (monsterlevel < 70)
						{
							devilitemlevel = 4;
						}
						else if (monsterlevel < 80)
						{
							devilitemlevel = 5;
						}
						else
						{
							devilitemlevel = 6;
						}

						if (devilitemlevel != 0)
						{
							if (this->InsertItem(monsterlevel, type, index, devilitemlevel, 0, 0, 0) != 0xFF)
							{
								incount++;

								if (incount > MAX_ITEM_IN_MONSTER - 1)
								{
									return;
								}
							}
						}
					}
				}
				else if (zzzItemLevel(type, index, monsterlevel) == TRUE)
				{
					if (this->InsertItem(monsterlevel, type, index, 0, 0, 0, 0) != (BYTE)-1)
					{
						incount++;

						if (incount > MAX_ITEM_IN_MONSTER - 1)
						{
							return;
						}
					}
				}
			}
		}
		else
		{
			result = GetLevelItem(type, index, monsterlevel);

			if (result >= 0)
			{
				if ((type == 13 && index == 10) || (type == 12 && index == 11))
				{
					if (this->InsertItem(monsterlevel, type, index, result, 0, 0, 0) != 0xFF)
					{
						incount++;

						if (incount > MAX_ITEM_IN_MONSTER - 1)
						{
							return;
						}
					}
				}
				else if (result <= maxlevel)
				{
					if (type == 12)
					{
						if (index != 11)
						{
							result = 0;
						}
					}

					if (type == 12 && index == 11)
					{

					}
					else
					{
						if (result > maxlevel)
						{
							result = maxlevel;
						}
					}

					if ((type == 4 && index == 7) || (type == 4 && index == 15))
					{
						result = 0;
					}


					if (this->InsertItem(monsterlevel, type, index, result, 0, 0, 0) != (BYTE)-1)
					{
						incount++;

						if (incount > MAX_ITEM_IN_MONSTER - 1)
						{
							return;
						}
					}
				}
			}
		}

		if (this->m_iMonsterInvenItemCount[monsterlevel] >= MAX_ITEM_IN_MONSTER)
		{
			return;
		}

	}
}

float CMonsterItemMng::GetItemDropRate(int type, int index, int level, int monsterlevel)
{
	if (monsterlevel > MAX_LEVEL_MONSTER - 1 || monsterlevel < 0)
	{
		return 0;
	}

	int itemcount = this->m_iMonsterInvenItemCount[monsterlevel];

	if (itemcount <= 0)
	{
		return 0;
	}

	int count = 0;
	int itemType = ITEMGET(type, index);

	for (int i = 0; i < itemcount; i++)
	{
		if (this->m_MonsterInvenItems[monsterlevel][i].m_Type == itemType)

			count++;
	}

	return (count / (float)itemcount * 10000.f);
}

float CMonsterItemMng::GetMagicBookDropRate(int monsterlevel)
{
	if (monsterlevel > MAX_LEVEL_MONSTER - 1 || monsterlevel < 0)
	{
		return 0;
	}

	int itemcount = this->m_iMonsterInvenItemCount[monsterlevel];

	if (itemcount <= 0)
	{
		return 0;
	}

	int count = 0;

	int BallTable[22]; //season 4.5 changed

	BallTable[0] = ITEMGET(12, 7);
	BallTable[1] = ITEMGET(12, 8);
	BallTable[2] = ITEMGET(12, 9);
	BallTable[3] = ITEMGET(12, 10);
	BallTable[4] = ITEMGET(12, 11);
	BallTable[5] = ITEMGET(12, 12);
	BallTable[6] = ITEMGET(12, 13);
	BallTable[7] = ITEMGET(12, 14);
	BallTable[8] = ITEMGET(12, 16);
	BallTable[9] = ITEMGET(12, 17);
	BallTable[10] = ITEMGET(12, 18);
	BallTable[11] = ITEMGET(12, 19);
	BallTable[12] = ITEMGET(12, 21);
	BallTable[13] = ITEMGET(12, 22);
	BallTable[14] = ITEMGET(12, 23);
	BallTable[15] = ITEMGET(12, 24);
	BallTable[16] = ITEMGET(12, 35);
	BallTable[17] = ITEMGET(12, 44);//Season 4.5 addon
	BallTable[18] = ITEMGET(12, 45);//Season 4.5 addon
	BallTable[19] = ITEMGET(12, 46);//Season 4.5 addon
	BallTable[20] = ITEMGET(12, 47);//Season 4.5 addon
	BallTable[21] = ITEMGET(12, 48);//Season 4.5 addon

	for (int i = 0; i < itemcount; i++)
	{
		for (int k = 0; k < 22; k++) {
			if (this->m_MonsterInvenItems[monsterlevel][i].m_Type == BallTable[k]) {
				count++;
				break;
			}
		}

		if (this->m_MonsterInvenItems[monsterlevel][i].m_Type > 15 * 512)
			count++;
	}

	return (count / (float)itemcount * 10000.f);
}

void CMonsterItemMng::MagicBookGiveItemSearch(int monsterlevel, int maxlevel)
{
	if (monsterlevel >= MAX_LEVEL_MONSTER)
	{
		LogAdd("[INFO] Monster Level greater than max drop Level (%d) excluded from general drop, line: %d", MAX_LEVEL_MONSTER - 1, __LINE__);
		return;
	}

	int BallTable[22]; // Orbs

	BallTable[0] = 7;
	BallTable[1] = 8;
	BallTable[2] = 9;
	BallTable[3] = 10;
	BallTable[4] = 11;
	BallTable[5] = 12;
	BallTable[6] = 13;
	BallTable[7] = 14;
	BallTable[8] = 16;
	BallTable[9] = 17;
	BallTable[10] = 18;
	BallTable[11] = 19;
	BallTable[12] = 21;
	BallTable[13] = 22;
	BallTable[14] = 23;
	BallTable[15] = 24;
	BallTable[16] = 35;
	BallTable[17] = 44;
	BallTable[18] = 45;
	BallTable[19] = 46;
	BallTable[20] = 47;
	BallTable[21] = 48;

	int LoopCount = 200;
	int incount = 0;
	int type, index;

	while (LoopCount != 0)
	{
		while (true)
		{
			if (rand() % 2 == 0) //Orb
			{
				type = 12;
				index = BallTable[GetLargeRand() % 0x16];
			}

			else
			{
				type = MAX_TYPE_ITEMS - 1; //Scroll
				index = GetLargeRand() % (g_MaxItemIndexOfEachItemType[type] + 1);
			}

			if (type != 12 || index != 11) //Orb of Summoning
				break;

			int result = GetLevelItem(12, 11, monsterlevel);

			if (result >= 0)
			{
				this->m_MagicBookItems[monsterlevel][incount].Convert(ITEMGET(12, 11), 0, 0, 0, 0, 0, 0, 0, -1, 0, 3);
				this->m_MagicBookItems[monsterlevel][incount].m_Level = result;
				this->m_MagicBookItems[monsterlevel][incount].m_Durability = this->m_MagicBookItems[monsterlevel][incount].m_BaseDurability;

				incount++;

				if (incount >= MAX_MAGIC_IN_MONSTER)
				{
					goto END_LOOP;
				}
			}
		}

		if (GetLevelItem(type, index, monsterlevel) == 0)
		{
			this->m_MagicBookItems[monsterlevel][incount].Convert(ITEMGET(type, index), 0, 0, 0, 0, 0, 0, 0, -1, 0, 3);
			this->m_MagicBookItems[monsterlevel][incount].m_Level = 0;
			this->m_MagicBookItems[monsterlevel][incount].m_Durability = this->m_MagicBookItems[monsterlevel][incount].m_BaseDurability;

			incount++;

			if (incount >= MAX_MAGIC_IN_MONSTER)
			{
				goto END_LOOP;
			}
		}

		LoopCount--;
	}

END_LOOP:
	this->m_iMagicBookItmeCount[monsterlevel] = incount;
}

void CMonsterItemMng::NormalGiveItemSearchEx(int monsterlevel, int maxlevel)
{
	BYTE DropTypes[14] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14 };
	int incount = 0;
	int result;
	int perc;
	int devilitemlevel;
	signed int bCheckDevil;

	if (monsterlevel >= MAX_LEVEL_MONSTER)
	{
		LogAdd("[INFO] Monster (%s) Level greater than max drop Level (%d) excluded from general drop, line: %d", this->MonsterName, MAX_LEVEL_MONSTER - 1, __LINE__);
		return;
	}

	for (int type = 0; type < 14; type++)
	{
		for (int index = 0; index < g_MaxItemIndexOfEachItemType[DropTypes[type]]; index++)
		{
			if (!this->CheckMonsterDropItem(type, index))
				continue;
			if ((type != 13 || index >= 8) //Exclude Angel, Imo, Uniria, Dinorant, Dark Horse, Dark Raven, Summon
				&& (type != 14 || index != 9 && index != 10 && index != 17 && index != 18)  //Exclude Ale, Town Portal Scroll, Devil Eye n Key
				&& (type != 13 || index != 14) // Exclude Loch's Feather
				&& (type != 14 || index != 31)) // Exclude JoG
			{
				result = GetLevelItem(type, index, monsterlevel);
				if (result >= 0 && result <= maxlevel)
				{
					if (type == 12 && index != 11) //Exclude summoning orb. But the type 12 is excluded.
						result = 0;
					if ((type != 12 || index != 11) && result > maxlevel) //Exclude summoning orb. How result will > maxlevel? 
						result = maxlevel;
					if (type == 4 && index == 7 || type == 4 && index == 15) //Bolt and Arrow
						result = 0;
					if (this->InsertItem(monsterlevel, type, index, result, 0, 0, 0) != 255)
					{
						++incount;

						if (incount > MAX_ITEM_IN_MONSTER - 1)
							return;
					}
				}
			}
			else
			{
				perc = rand() % 8;
				bCheckDevil = 0;
				if (type == 12 && index == 15) //Jewel of Chaos...But type 12 is excluded in the for loop...
				{
					if (monsterlevel < 13 || monsterlevel > 66)
					{
						perc = 1;
					}
					else
					{
						perc = rand() % 7;
						if (perc < 3)
							perc = 0;
					}
				}

				if (!perc) //12,5% (1/8) of drop devil item (when perc == 0)
				{
					//if (bCheckDevil == 1) //Will never proc. bCheckDevil is always 0
					//{
					//	if (rand() % 5)
					//	{
					//		if (monsterlevel >= 3)
					//		{
					//			if (monsterlevel >= 36)
					//			{
					//				if (monsterlevel >= 47)
					//				{
					//					if (monsterlevel >= 60)
					//					{
					//						if (monsterlevel >= 70)
					//							devilitemlevel = monsterlevel >= 80 ? 6 : 5;
					//						else
					//							devilitemlevel = 4;
					//					}
					//					else
					//					{
					//						devilitemlevel = 3;
					//					}
					//				}
					//				else
					//				{
					//					devilitemlevel = 2;
					//				}
					//			}
					//			else
					//			{
					//				devilitemlevel = 1;
					//			}
					//		}
					//		else
					//		{
					//			devilitemlevel = 0;
					//		}
					//		if (devilitemlevel)
					//		{
					//			if (this->InsertItem(monsterlevel, type, index, devilitemlevel, 0, 0, 0) != 255)
					//			{
					//				++incount;

					//				if (incount > MAX_ITEM_IN_MONSTER - 1)
					//					return;
					//			}
					//		}
					//	}
					//}
					//else
					//{
						if (zzzItemLevel(type, index, monsterlevel) == 1)
						{
							if (this->InsertItem(monsterlevel, type, index, 0, 0, 0, 0) != 255)
							{
								++incount;
								if (incount > MAX_ITEM_IN_MONSTER - 1)
									return;
							}
						}
					//}
				}
			}
			if (this->m_iMonsterInvenItemCount[monsterlevel] >= MAX_ITEM_IN_MONSTER)
				return;

		}
	}
}

int CMonsterItemMng::CheckMonsterDropItem(int type, int index)
{
	int result;
	if ((type != 14 || index != 13)	//Bless
		&& (type != 14 || index != 14) //Soul
		&& (type != 14 || index != 16) //Life
		&& (type != 14 || index != 22) //Creation
		&& (type != 12 || index != 15)) //Chaos
	{
		if (type != 13 || index != 3)	//Dinorant
		{
			if ((type != 13 || index != 32) //Splinter of Armor
				&& (type != 13 || index != 33) //Bless of Guardian
				&& (type != 13 || index != 34) //Claw of Beast
				&& (type != 13 || index != 35) //Fragment of Horn
				&& (type != 13 || index != 36) //Broken Horn
				&& (type != 13 || index != 37)) //Hrn of Fenrir
			{
				if ((type != 14 || index != 35) //Small SD Potion
					&& (type != 14 || index != 36) //SD Potion
					&& (type != 14 || index != 37) //Large SD Potion
					&& (type != 14 || index != 38) //Small Complex Potion
					&& (type != 14 || index != 39) //Complex Potion
					&& (type != 14 || index != 40)) //Large Complex Potion
				{
					if (IsCashItem(ITEMGET(type, index)) == 1)
					{
						result = 0;
					}
					else
					{
						//if (IsPremiumItem(ITEMGET(type, index)) == 1)
						//{
						//	result = 0;
						//}
						//else
						//{
						if (g_LuckyItemManager.IsLuckyItemTicket(ITEMGET(type, index)) == 1)
						{
							result = 0;
						}
						else
						{
							if (g_LuckyItemManager.IsLuckyItemEquipment(ITEMGET(type, index)) == 1)
							{
								result = 0;
							}
							else
							{
								if ((type != 14 || index != 45)	// Pumpkin of Luck
									&& (type != 14 || index != 46) //Jack O'Lantern Blessings
									&& (type != 14 || index != 47) //Jack
									&& (type != 14 || index != 48) //Jack
									&& (type != 14 || index != 49) //Jack
									&& (type != 14 || index != 50)) //Jack
								{
									if (type != 13 || index != 41) //Transfer Christmas Ring"
									{
										if ((type != 13 || index != 106) && (type != 13 || index != 107)) //Pet Unicorn Lethal Wizard Ring
											result = (type != 14 || index != 162) //Magic Backpack
											&& (type != 14 || index != 163) //Vault Expansion Certificate
											&& (type != 14 || index != 164) //Ancient Statue
											&& (type != 14 || index != 165) //Magic Cloth
											&& (type != 14 || index != 166); //Space Clocth
										else
											result = 0;
									}
									else
									{
										result = 0;
									}
								}
								else
								{
									result = 0;
								}
							}
						}
						//}
					}
				}
				else
				{
					result = 0;
				}
			}
			else
			{
				result = 0;
			}
		}
		else
		{
			result = 0;
		}
	}
	else
	{
		result = 0;
	}
	return result;
}

CItem * CMonsterItemMng::GetItemEx(int monsterlevel)
{
	if (!m_bExActive)
		return this->GetItem(monsterlevel);

	if (this->m_bLoad == false)
	{
		return nullptr;
	}

	if (monsterlevel < 0 || monsterlevel >= MAX_LEVEL_MONSTER)
	{
		return nullptr;
	}

	DWORD nRandValue = GetLargeRand() % 10000000;
	int nSum = this->m_MonsterItemDropRate[monsterlevel].m_MagicBookRate;

	if (nRandValue >= nSum)
	{
		nSum += this->m_MonsterItemDropRate[monsterlevel].m_BlessRate;

		if (nRandValue >= nSum)
		{
			nSum += this->m_MonsterItemDropRate[monsterlevel].m_SoulRate;

			if (nRandValue >= nSum)
			{
				nSum += this->m_MonsterItemDropRate[monsterlevel].m_ChaosRate;

				if (nRandValue >= nSum)
				{
					nSum += this->m_MonsterItemDropRate[monsterlevel].m_LifeRate;

					if (nRandValue >= nSum)
					{
						nSum += this->m_MonsterItemDropRate[monsterlevel].m_CreationRate;

						if (nRandValue >= nSum)
						{
							nSum += this->m_MonsterItemDropRate[monsterlevel].m_FeatherRate;

							if (nRandValue >= nSum)
							{
								int itemcount = this->m_iMonsterInvenItemCount[monsterlevel];

								if (itemcount <= 0)
								{
									return nullptr;
								}
								else
								{
									return &this->m_MonsterInvenItems[monsterlevel][GetLargeRand() % itemcount];
								}
							}
							else
							{
								return this->m_LochsFeatherItem;
							}
						}
						else
						{
							return this->m_JewelOfCreationItem;
						}
					}
					else
					{
						return this->m_JewelOfLifeItem;
					}
				}
				else
				{
					return this->m_JewelOfChaosItem;
				}
			}
			else
			{
				return this->m_JewelOfSoulItem;
			}
		}
		else
		{
			return this->m_JewelOfBlessItem;
		}
	}
	else
	{
		int itemcount = this->m_iMagicBookItmeCount[monsterlevel];

		if (itemcount <= 0)
		{
			return nullptr;
		}
		else
		{
			return &this->m_MagicBookItems[monsterlevel][GetLargeRand() % itemcount];
		}
	}

	return nullptr;
}