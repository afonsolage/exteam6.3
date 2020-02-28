#include "StdAfx.h"
#define BLOCK_MOVE_ITEM_DIR	"..\\Data\\ExData\\BlockMoveItem.ini"

#define BMI_MAX_ITEM	1000

class cBlockMoveItem
{
private:
	int Enable;
	int MaxLevel;
	int MaxExlOpt;
public:

	struct
	{
		int Type;
		int Index;
	}bmi[BMI_MAX_ITEM];
	int Count;

	void Load();

	bool ItemMoveBlockExlOpt(int exlopt_num);

	bool Move(int aIndex, int Pos);

	bool Sell(int aIndex, int Pos);

};
extern cBlockMoveItem gBlockMoveIteml;
