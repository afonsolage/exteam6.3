#pragma once
#include "stdafx.h"
#include "Protocol.h"

#define MAXTOP	100

struct CharTop
{
	char Name[10];
	BYTE Class;
	unsigned short level;
	unsigned short Reset;
	unsigned short Grand;
	unsigned short Str;
	unsigned short Agi;
	unsigned short Vit;
	unsigned short Ene;
	unsigned Cmd;
	BYTE Premium;
	char Guild[8];
};

struct DGCharTop
{
	PWMSG_HEAD2 h;
	CharTop	tp[MAXTOP];
};

class cRanking
{
public:
	cRanking();
	~cRanking();

	bool Active;
	bool Show;

	int StartX;
	int StartY;

	int Page;

	DWORD ClickTime;

	void ImageLoad();

	void RecvGS(DWORD Case, LPBYTE Data, int Len, int aIndex);
	void Draw();

	CharTop	RankingChar[MAXTOP];
private:

	
};
extern cRanking gRanking;