#include "StdAfx.h"
#include "MapClass.h"
#define DROPZEN_DIR "..\\Data\\ExData\\DropZenManager.ini"
class cDropZenManager
{
private:
	int Enable;
	struct  
	{
		int Map;
		int Zen;
	}Number[MAX_NUMBER_MAP];
	int mCount;
public:
	void LoadConfig();
	void Main (LPOBJ lpObj, float & money);
};
extern cDropZenManager DropZenManager;