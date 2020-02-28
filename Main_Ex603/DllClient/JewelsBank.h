#pragma once

#include "stdafx.h"
#include "protocol.h"

struct PMSG_JEWELBANK
{
	PBMSG_HEAD2 h;
	int Result;
};


class JewelsBank
{
public:
	bool Active;
	void JewelsBankImageLoad();
	void JewelsBankLoad();
	void JewelsBankDraw();
#if(INTERFACE_JEWELBANK)
	void Bind();
	void DrawItem(int ItemType, int ItemIndex, int ItemLevel);
	void Draw();
	void DrawLine(int ItemType, int ItemIndex, int ItemLevel, float DrawX, float DrawY, char * ItemName, int Count);
	void DrawInfo(float InfoDrawX, float InfoDrawY, char* Text, bool Type, int Count);
	void Button(DWORD key);
	void Packet(int number);
#endif
};
extern JewelsBank gJewelsBank;

