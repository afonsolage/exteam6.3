#pragma once
#include "StdAfx.h"
#include "protocol.h"

#define MAXTOP	100

struct GDTop
{
	PBMSG_HEAD2 h;
	BYTE Result;
};

struct SShowRanking
{
	PBMSG_HEAD2 h;
	BYTE Show;
};

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

class cRanking
{
public:
	void SendDS();
	void RecvDS(DGCharTop *Recv);
	void SendClient();
	void SendUser(int aIndex);
	void CGShowRanking(SShowRanking* lpMsg, int aIndex);
private:
	CharTop	RankingChar[MAXTOP];
};
extern cRanking gRanking;