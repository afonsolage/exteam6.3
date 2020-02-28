#include "StdAfx.h"


unsigned char GetRandomExeOption(unsigned char MaxOption);
bool Ex_IsBadFileLine(char *FileLine, int &Flag);
int GetNumberByPercent(int Proc, int Min, int Max);
int GenExcOpt(int amount);
int gObjGetItemCountInInventory(int aIndex, int ItemID,int ItemLevel);
int gObjDeleteItemsCount(int aIndex, short Type, short Level, int dCount);
void ExFireCracker(int aIndex, BYTE X, BYTE Y);
int ExGenExcOpt(int amount);
BYTE GetExcOptionCount(BYTE ExcellentOption);
int EmptyPointInventory(int aIndex);
int ExCheckInventoryEmptySpace(int aIndex);
bool ExIsBadFileLineV2(char *FileLine, int &Flag);

bool CheckOptions(bool bItem, int Item1, int Item2);

bool CheckInCharacterItem(int aIndex, int ItemType);
bool CheckInventoryItem(int aIndex, int ItemType);
void Max90Procent(int & Value);
int GetInventoryEmptyPoint(int aIndex);