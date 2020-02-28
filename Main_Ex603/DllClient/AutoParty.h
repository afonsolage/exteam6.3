#pragma once
#include "stdafx.h"
#include "Protocol.h"

#ifdef AUTO_PARTY

struct GCPartyList
{
	PWMSG_HEAD2 h;
	char Name[100][11];
	short Level[100];
	BYTE Map[100];
	BYTE X[100];
	BYTE Y[100];
	BYTE Total[100];
};

struct AutoPt_DATA
{
	char Name[11];
	short Level;
	BYTE Map;
	BYTE X;
	BYTE Y;
	BYTE Total;
};

class cAutoParty
{
public:
	cAutoParty();
	~cAutoParty();

	BYTE Active;

	bool Show;

	int Page;

	DWORD ClickTime;

	void Work();

	void Protocol(DWORD Case, LPBYTE Data, int Len, int aIndex);

	AutoPt_DATA Party[100];
};
extern cAutoParty gAutoParty;

#endif