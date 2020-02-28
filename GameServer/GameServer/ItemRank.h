#pragma once

#include "StdAfx.h"
#include "..\\include\\prodef.h"

#if(CUSTOM_ITEM_RANK==TRUE)

#define ITEMRANK_MAX_OPTION		6

struct ItemRank_Data
{
	BYTE RankID;
	BYTE OptionValue[ITEMRANK_MAX_OPTION];
	ItemRank_Data()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

struct ItemRank_List
{
	BYTE RankID;
	WORD ItemType;
	BYTE MinLevel;
	ItemRank_List()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

struct PMSG_INITRANK
{
	PBMSG_HEAD2 h;
	BYTE Result;
};

struct PMSG_DATARANK
{
	PBMSG_HEAD2 h;
	BYTE RankID;
	BYTE OptionValue[ITEMRANK_MAX_OPTION];
};

struct PMSG_LISTRANK
{
	PBMSG_HEAD2 h;
	BYTE RankID;
	WORD ItemType;
	BYTE MinLevel;
};

class ItemRank
{
public:
		 ItemRank();
		 ~ItemRank();

	void Init();
	void Load();
	void Read(char * File);
	int  IsRankItem(WORD ItemType, BYTE ItemLevel);
	bool IsDataRank(BYTE RankID);
	int  GetRankValueOption(int id, BYTE OptionType);
	void GCRankInit(int aUserIndex);
	void GCRankData(int aUserIndex);
	void GCRankList(int aUserIndex);

private:
	bool bEnable;
	std::vector<ItemRank_Data> m_Data;
	std::vector<ItemRank_List> m_ItemList;
}; 
extern ItemRank g_ItemRank;

#endif