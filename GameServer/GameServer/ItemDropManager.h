#define ITEM_DROP_DIR	"..\\Data\\ExData\\ItemDropManager.ini"
#define MAX_DROP_ITEM	1000

#include "User.h"

struct ANCENT_ITEM_DATA
{
	short sType;
	short sIndex;
	short sOpt;
};

struct ANCENT_GROUP_DATA
{
	short sMap;
	short sMinLvlMob;
	short sMaxLvlMob;
	int   iRate;
	int   ItemCount;
	ANCENT_ITEM_DATA m_item[256];
};

struct MAP_DROPRATE_DATA
{
	int MapNum;
	int Rate;
};

struct MAP_ALLOW_DATA
{
	short sType;
	short sIndex;
	short sLevel;
	int MapNum;
};

class CItemDropManager
{
public:
	void Init();
	bool ProccessItemDrop(LPOBJ lpMobObj, LPOBJ lpTargetObj);
	bool BlockItemDrop(int aIndex, int ItemID, int Level, int MapNumber);
	void ReadAnc(char* filename);
	void DropAncent(int aIndex, int iMobIndex);
	int GetMapDropRate(int Map);

private:

	bool iUser[OBJMAX];

	int DropCount;
	struct 
	{
		int Type;
		int Index;
		int MinLevel;
		int MaxLevel;
		int Dur;
		int OptionRate;
		int MaxOption;
		int LuckRate;
		int LuckOption;
		int SkillRate;
		int SkillOption;
		int ExlRate;
		int ExlOption;
		int AncRate;
		int AncOption;
		int MonsterMinLevel;
		int MonsterMaxLevel;
		int MonsterMap;
		int ItemDropRate;
	}Drop[MAX_DROP_ITEM];

	int BlockCount;
	struct
	{
		int Type;
		int Index;
	}Block[MAX_DROP_ITEM];

	int MapBlockCount;
	struct
	{
		int Map;
		int Type;
		int Index;
	}MapBlockDrop[MAX_DROP_ITEM];

	ANCENT_GROUP_DATA m_AncData[100];
	int iAncCount;

	std::vector<MAP_DROPRATE_DATA> m_MapDropRate;
	std::vector<MAP_ALLOW_DATA> m_MapAllowDrop;
};

extern CItemDropManager gItemDropManager;