#include "StdAfx.h"
#include "ItemRank.h"
#include "logproc.h"
#include "..\include\readscript.h"
#include "GameMain.h"
#include "user.h"
#include "ExLicense.h"

#if(CUSTOM_ITEM_RANK==TRUE)

ItemRank g_ItemRank;

ItemRank::ItemRank()
{
	this->Init();
}

ItemRank::~ItemRank()
{
}

void ItemRank::Init()
{
	this->bEnable = false;
	this->m_Data.clear();
	this->m_ItemList.clear();
}

void ItemRank::Load()
{
	this->Init();

	this->bEnable = g_ExLicense.user.bRankItem;

	if(!this->bEnable)
	{
		return;
	}

	this->Read(gDirPath.GetNewPath("ExData\\ItemRank.ini"));
}

void ItemRank::Read(char * File)
{
	SMDToken Token;
	SMDFile = fopen(File, "r");

	if( !SMDFile )
	{
		MsgBox("[ItemRank] %s file not found", File);
		return;
	}

	while(true)
	{
		SMDToken Token = GetToken();

		if( Token == END )
		{
			break;
		}

		int Type = (int)TokenNumber;

		if( Type == 0 ) //RankList
		{
			while(true)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				ItemRank_Data lpData;

				lpData.RankID = TokenNumber;

				Token = GetToken();
				lpData.OptionValue[0] = TokenNumber;

				Token = GetToken();
				lpData.OptionValue[1] = TokenNumber;

				Token = GetToken();
				lpData.OptionValue[2] = TokenNumber;

				Token = GetToken();
				lpData.OptionValue[3] = TokenNumber;

				Token = GetToken();
				lpData.OptionValue[4] = TokenNumber;

				Token = GetToken();
				lpData.OptionValue[5] = TokenNumber;

				this->m_Data.push_back(lpData);
			}
		}
		else if( Type == 1 ) //ItemList
		{
			while(true)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				ItemRank_List lpData;
				int ItemType = -1, ItemIndex = -1;

				lpData.RankID = TokenNumber;

				Token = GetToken();
				ItemType = TokenNumber;

				Token = GetToken();
				ItemIndex = TokenNumber;

				Token = GetToken();
				lpData.MinLevel = TokenNumber;

				lpData.ItemType = ITEMGET(ItemType, ItemIndex);

				if(!this->IsDataRank(lpData.RankID))
				{
					MsgBox("[ItemRank] Invalid RankID (Item: %d/%d - RankID: %d)", 
						ItemType, ItemIndex, lpData.RankID);
					continue;
				}

				this->m_ItemList.push_back(lpData);
			}
		}
		else if( Type == 2 ) //SetList
		{
			while(true)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				int ItemIndex = -1, ItemRankID = -1, ItemLevel = 0;

				ItemRankID = TokenNumber;

				Token = GetToken();
				ItemIndex = TokenNumber;

				Token = GetToken();
				ItemLevel = TokenNumber;

				if(!this->IsDataRank(ItemRankID))
				{
					MsgBox("[ItemRank] Invalid RankID (Item: %d - RankID: %d)", 
						ItemIndex, ItemRankID);
					continue;
				}

				for(int i = 7; i < 12; i++)
				{
					ItemRank_List lpData;

					lpData.RankID = ItemRankID;

					lpData.MinLevel = ItemLevel;

					lpData.ItemType = ITEMGET(i, ItemIndex);

					this->m_ItemList.push_back(lpData);
				}
			}
		}
	}

	fclose(SMDFile);
	LogAdd("%s file load!", File);
}

int ItemRank::IsRankItem(WORD ItemType, BYTE ItemLevel)
{
	int iID = -1;
	int iMaxLevel = 0;

	for(int i = 0; i < this->m_ItemList.size(); i++)
	{
		if(this->m_ItemList[i].ItemType != ItemType)
		{
			continue;
		}

		if(!this->IsDataRank(this->m_ItemList[i].RankID)) 
		{
			continue;
		}

		if(this->m_ItemList[i].MinLevel > ItemLevel)
		{
			continue;
		}

		if(this->m_ItemList[i].MinLevel >= iMaxLevel)
		{
			iMaxLevel = this->m_ItemList[i].MinLevel;
			iID = i;
		}
	}

	if(iID == -1)
	{
		return -1;
	}

	return iID;
}

bool ItemRank::IsDataRank(BYTE RankID)
{
	for(int i = 0; i < this->m_Data.size(); i++)
	{
		if(this->m_Data[i].RankID == RankID)
		{
			return true;
		}
	}

	return false;
}

int ItemRank::GetRankValueOption(int id, BYTE OptionType)
{
	int iRankID = -1;
	int iResult = -1;

	if(id < 0)
	{
		iResult = 0;
		return iResult;
	}

	iRankID = this->m_ItemList[id].RankID;

	if(iRankID <= 0)
	{
		iResult = 0;
		return iResult;
	}

	for(int i = 0; i < this->m_Data.size(); i++)
	{
		if(this->m_Data[i].RankID == iRankID)
		{
			iResult = this->m_Data[i].OptionValue[OptionType];
			break;
		}
	}

	return iResult;
}

void ItemRank::GCRankInit(int aUserIndex)
{
	if(!OBJMAX_RANGE(aUserIndex))
	{
		return;
	}

	PMSG_INITRANK pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x51, sizeof(pMsg));
	pMsg.Result = 1;
	DataSend(aUserIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void ItemRank::GCRankData(int aUserIndex)
{
	if(!OBJMAX_RANGE(aUserIndex))
	{
		return;
	}

	for(int i = 0; i < this->m_Data.size(); i++)
	{
		PMSG_DATARANK pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x52, sizeof(pMsg));
		pMsg.RankID = this->m_Data[i].RankID;
		pMsg.OptionValue[0] = this->m_Data[i].OptionValue[0];
		pMsg.OptionValue[1] = this->m_Data[i].OptionValue[1];
		pMsg.OptionValue[2] = this->m_Data[i].OptionValue[2];
		pMsg.OptionValue[3] = this->m_Data[i].OptionValue[3];
		pMsg.OptionValue[4] = this->m_Data[i].OptionValue[4];
		pMsg.OptionValue[5] = this->m_Data[i].OptionValue[5];
		DataSend(aUserIndex, (LPBYTE)&pMsg, pMsg.h.size);
	}
}

void ItemRank::GCRankList(int aUserIndex)
{
	if(!OBJMAX_RANGE(aUserIndex))
	{
		return;
	}

	for(int i = 0; i < this->m_ItemList.size(); i++)
	{
		PMSG_LISTRANK pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x53, sizeof(pMsg));
		pMsg.RankID = this->m_ItemList[i].RankID;
		pMsg.ItemType = this->m_ItemList[i].ItemType;
		pMsg.MinLevel = this->m_ItemList[i].MinLevel;
		DataSend(aUserIndex, (LPBYTE)&pMsg, pMsg.h.size);
	}
}

#endif