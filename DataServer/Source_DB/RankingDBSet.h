#pragma once

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

struct GD_CheckBrother
{
	PBMSG_HEAD2 h;
	int aIndex;
	int aTargetIndex;
	char BrName[11];
};

struct DG_CheckBrother
{
	PBMSG_HEAD2 h;
	int aIndex;
	int aTargetIndex;
	int Count;
};

class cRanking :public CDBConBase
{
public:
	cRanking();
	~cRanking();

bool Connect();

void CharacterRanking(int pIndex);
void RecvBrother(GD_CheckBrother* Recv, int pIndex);
};