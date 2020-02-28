#pragma once

#include "StdAfx.h"
#include "protocol.h"

#ifdef AUTO_PARTY

#define AUTO_PT_DEBUG	0

struct ExPMSG_PARTYREQUESTSEND
{
	PBMSG_HEAD h;
	BYTE NumberH;
	BYTE NumberL;
};

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

class cAutoParty
{
public:
	cAutoParty();
	~cAutoParty();

	void Work();
	void Party(int aIndex, int Number);

	bool CheckDistance(int aIndex, int x, int y);

	void SendPartyList(int aIndex);

};
extern cAutoParty gAutoParty;

#endif