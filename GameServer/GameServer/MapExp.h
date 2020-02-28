#include "StdAfx.h"


#include "user.h"
#include "MapClass.h"

#define MAP_EXP_DIR "..\\Data\\ExData\\MapExp.ini"

class cMapExp
{
private:
	int Enable;

	struct 
	{
		int Map;
		int Exp;
	} Number[MAX_NUMBER_MAP];
	int rCount;

public:
	void LoadConfig();
	void Main(LPOBJ lpObj, __int64 & Experience);	//Panda User

};
extern cMapExp gMapExp;
