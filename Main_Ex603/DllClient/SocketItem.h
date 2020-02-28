#pragma once
#include "stdafx.h"

#define MAX_ITEM 7680

#define SOCKET_DIR	"Data\\Custom\\Configs\\SocketItem.ini"





class cSocketItem
{
public:
	void Load();
	static int CheckItem(signed int a1);


	struct
	{
		short Type;
		short Index;
	}sItem[MAX_ITEM];
	int ItemCount;


};
extern cSocketItem gSocketItem;
