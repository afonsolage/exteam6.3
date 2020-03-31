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
	char Guild[9];
	bool ShowRanking;
};

struct DGCharTop
{
	PWMSG_HEAD2 h;
	bool ShowRanking;
	CharTop	tp[MAXTOP];
};

struct SShowRanking
{
	PBMSG_HEAD2 h;
	BYTE Show;
};

class cRanking
{
public:
	cRanking();
	~cRanking();

	bool Active;

	int StartX;
	int StartY;

	int Page;

	DWORD ClickTime;

	void ImageLoad();
	void BindImages();

	void RecvGS(DWORD Case, LPBYTE Data, int Len, int aIndex);
	void Draw();
	void Click(DWORD);

	CharTop	RankingChar[MAXTOP];
private:
	bool ShowRanking;
	
};
extern cRanking gRanking;