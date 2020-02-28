#include "StdAfx.h"
#include "Ranking.h"
#include "DSProtocol.h"
#include "DBSockMng.h"
#include "logproc.h"
#include "user.h"
#include "protocol.h"
#include "..\\common\\winutil.h"
#include "Configs.h"

cRanking gRanking;

void cRanking::SendDS()
{
	if(!ExConfig.ExCustom.Top100)return;
	GDTop pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xE2, 0x03, sizeof(GDTop));
	pMsg.Result = 1;
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void cRanking::RecvDS(DGCharTop *Recv)
{
	if(!ExConfig.ExCustom.Top100)return;

	for(int i=0;i<MAXTOP;i++)
	{
		/*
	BYTE Class;
	unsigned short level;
	unsigned short Reset;
	unsigned short Grand;
	unsigned short Str;
	unsigned short Agi;
	unsigned short Vit;
	unsigned short Ene;
	unsigned Cmd;
	char Guild[8];
		*/
		strncpy(this->RankingChar[i].Name,Recv->tp[i].Name,10);

		this->RankingChar[i].Class = Recv->tp[i].Class;
		this->RankingChar[i].level = Recv->tp[i].level;
		this->RankingChar[i].Reset = Recv->tp[i].Reset;
		this->RankingChar[i].Grand = Recv->tp[i].Grand;
		this->RankingChar[i].Str = Recv->tp[i].Str;
		this->RankingChar[i].Agi = Recv->tp[i].Agi;
		this->RankingChar[i].Vit = Recv->tp[i].Vit;
		this->RankingChar[i].Ene = Recv->tp[i].Ene;
		this->RankingChar[i].Cmd = Recv->tp[i].Cmd;
		this->RankingChar[i].Premium = Recv->tp[i].Premium;

		strncpy(this->RankingChar[i].Guild,Recv->tp[i].Guild,8);

		//if(this->RankingChar[i].Name[0] != NULL)
		//LogAddC(2,"Name: %s",this->RankingChar[i].Name);
	}
}

void cRanking::SendClient()
{
	if(!ExConfig.ExCustom.Top100)return;

	for (int  n=OBJ_STARTUSERINDEX;n<OBJMAX;n++)
	{
		LPOBJ lpObj = &gObj[n];
		if(lpObj->Connected == PLAYER_PLAYING && lpObj->OffExp == 0 && lpObj->OffTrade == 0)
		{
			DGCharTop	sClient;
			ZeroMemory(&sClient,sizeof(sClient));
			PHeadSubSetW((LPBYTE)&sClient, 0xFA, 0x06, sizeof(sClient));

			for(int i=0;i<MAXTOP;i++)
			{
				strncpy(sClient.tp[i].Name,this->RankingChar[i].Name,10);

				sClient.tp[i].Class = this->RankingChar[i].Class;
				sClient.tp[i].level = this->RankingChar[i].level;
				sClient.tp[i].Reset = this->RankingChar[i].Reset;
				sClient.tp[i].Grand = this->RankingChar[i].Grand;
				sClient.tp[i].Str = this->RankingChar[i].Str;
				sClient.tp[i].Agi = this->RankingChar[i].Agi;
				sClient.tp[i].Vit = this->RankingChar[i].Vit;
				sClient.tp[i].Ene = this->RankingChar[i].Ene;
				sClient.tp[i].Cmd = this->RankingChar[i].Cmd;
				sClient.tp[i].Premium = this->RankingChar[i].Premium;

				strncpy(sClient.tp[i].Guild,this->RankingChar[i].Guild,8);
			}

			DataSend(n,(LPBYTE)&sClient,sizeof(sClient));
		}
	}
}

void cRanking::SendUser(int aIndex)
{
	if(!ExConfig.ExCustom.Top100) return;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Connected == PLAYER_PLAYING && lpObj->OffExp == 0 && lpObj->OffTrade == 0)
	{

		DGCharTop	sClient;
		ZeroMemory(&sClient,sizeof(sClient));
		PHeadSubSetW((LPBYTE)&sClient, 0xFA, 0x06, sizeof(sClient));

		for(int i=0;i<MAXTOP;i++)
		{
			strncpy(sClient.tp[i].Name,this->RankingChar[i].Name,10);
			sClient.tp[i].Class = this->RankingChar[i].Class;
			sClient.tp[i].level = this->RankingChar[i].level;
			sClient.tp[i].Reset = this->RankingChar[i].Reset;
			sClient.tp[i].Grand = this->RankingChar[i].Grand;
			sClient.tp[i].Str = this->RankingChar[i].Str;
			sClient.tp[i].Agi = this->RankingChar[i].Agi;
			sClient.tp[i].Vit = this->RankingChar[i].Vit;
			sClient.tp[i].Ene = this->RankingChar[i].Ene;
			sClient.tp[i].Cmd = this->RankingChar[i].Cmd;
			sClient.tp[i].Premium = this->RankingChar[i].Premium;
			strncpy(sClient.tp[i].Guild,this->RankingChar[i].Guild,8);
		}

		DataSend(aIndex,(LPBYTE)&sClient,sizeof(sClient));
	}
}