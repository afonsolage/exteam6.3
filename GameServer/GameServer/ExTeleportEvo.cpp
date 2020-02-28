#include "StdAfx.h"
#include "ExTeleportEvo.h"
#include "GameMain.h"
#include "..\\include\\ReadScript.h"
#include "logproc.h"
#include "ExUser.h"
#include "ExLicense.h"
#include "ExTeleport.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_EX_TELEPORT_EVO==TRUE)
// ----------------------------------------------------------------------------------------------

ExTeleportEvo g_ExTeleportEvo;
// ----------------------------------------------------------------------------------------------

ExTeleportEvo::ExTeleportEvo()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

ExTeleportEvo::~ExTeleportEvo()
{
}
// ----------------------------------------------------------------------------------------------

void ExTeleportEvo::Init()
{
	ZeroMemory(this->data, sizeof(this->data));
	this->Enable = 0;
	this->NPC_Class = 0;
	this->NPC_Map = 0;
	this->NPC_X = 0;
	this->NPC_Y = 0;
	this->iLoadedCount = 0;
}
// ----------------------------------------------------------------------------------------------

void ExTeleportEvo::Load()
{
	this->Init();

	if(g_ExLicense.CheckUser(Local) || g_ExLicense.CheckUser(Gredy) || g_ExLicense.CheckUser(Gredy2) || g_ExLicense.CheckUser(GredyLocal))
	{
		this->Read(gDirPath.GetNewPath("ExData\\ExTeleportEvo.ini"));
	}
}
// ----------------------------------------------------------------------------------------------

void ExTeleportEvo::Read(char* File)
{
	SMDFile = fopen(File, "r");

	if( SMDFile == NULL )
	{
		LogAdd(lMsg.Get(MSGGET(1, 198)), File);
		return;
	}

	int Token;
	int type = -1;

	while ( true )
	{
	    Token = GetToken();

        if( Token == END )
		{
            break;
		}

		//if(this->iLoadedCount >= MAXEXTELEPORT)
		//{
		//	break;
		//}

		type = (int)TokenNumber;

		while ( true )
		{
			if ( type == 0 )
			{
				Token = GetToken();

				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}

				this->Enable = TokenNumber;
				Token = GetToken();
				this->NPC_Class = TokenNumber;
				Token = GetToken();
				this->NPC_Map = TokenNumber;
				Token = GetToken();
				this->NPC_X = TokenNumber;
				Token = GetToken();
				this->NPC_Y = TokenNumber;
			}
			else if( type == 1 )
			{
				Token = GetToken();

				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}

				this->data[this->iLoadedCount].map = TokenNumber;
				Token = GetToken();
				this->data[this->iLoadedCount].x = TokenNumber;
				Token = GetToken();
				this->data[this->iLoadedCount].y = TokenNumber;
				Token = GetToken();
				this->data[this->iLoadedCount].min_level = TokenNumber;
				Token = GetToken();
				this->data[this->iLoadedCount].max_level = TokenNumber;
				Token = GetToken();
				this->data[this->iLoadedCount].min_reset = TokenNumber;
				Token = GetToken();
				this->data[this->iLoadedCount].max_reset = TokenNumber;
				Token = GetToken();
				this->data[this->iLoadedCount].min_grand = TokenNumber;
				Token = GetToken();
				this->data[this->iLoadedCount].max_grand = TokenNumber;
				Token = GetToken();
				this->data[this->iLoadedCount].premium = TokenNumber;
				Token = GetToken();
				this->data[this->iLoadedCount].zen = TokenNumber;
				Token = GetToken();
				this->data[this->iLoadedCount].bonus = TokenNumber;
				Token = GetToken();
				this->data[this->iLoadedCount].credit = TokenNumber;
				Token = GetToken();
				this->data[this->iLoadedCount].Master = TokenNumber;
				Token = GetToken();
				this->data[this->iLoadedCount].EmptyInv = TokenNumber;
				this->iLoadedCount++;
				if(this->iLoadedCount >= MAXEXTELEPORT)
				{
					break;
				}
			}
		}
    }

	fclose(SMDFile);
}
// ----------------------------------------------------------------------------------------------

bool ExTeleportEvo::Dialog(int aUserIndex, int aNpcIndex)
{
	if(!this->Enable)
	{
 		return false;
	}

	if(!gObjIsConnectedEx(aUserIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aUserIndex];
	LPOBJ lpNpc = &gObj[aNpcIndex];

	if(		lpNpc->Class		== this->NPC_Class 
		&&	lpNpc->MapNumber	== this->NPC_Map
		&&	lpNpc->X			== this->NPC_X
		&&	lpNpc->Y			== this->NPC_Y )
	{
		this->GCWindows(aUserIndex);
		return true;
	}
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

void ExTeleportEvo::Timer()
{
	/*
	for (int aUserIndex = OBJ_STARTUSERINDEX; aUserIndex < OBJMAX; aUserIndex++)
	{
		if(OBJMAX_RANGE(aUserIndex) == 0)
		{
			continue;
		}

		LPOBJ lpUser = &gObj[aUserIndex];

		if(lpUser->Connected < PLAYER_PLAYING)
		{
			continue;
		}
		
		for(int i = 0; i < this->iLoadedCount; i++)
		{
			if(this->data[i].map == lpUser->MapNumber)
			{
				if(this->data[i].level > lpUser->Level)
				{
					gObjTeleport(aUserIndex, 0, 123, 123);
				}
				else if(this->data[i].reset > lpUser->Reset)
				{
					gObjTeleport(aUserIndex, 0, 123, 123);
				}
				else if(this->data[i].grand > lpUser->GReset)
				{
					gObjTeleport(aUserIndex, 0, 123, 123);
				}
				else if(this->data[i].Master)
				{
					if(!lpUser->ChangeUP3rd)
					{
						gObjTeleport(aUserIndex, 0, 123, 123);
					}
				}
			}
		}
	}
	*/
}
// ----------------------------------------------------------------------------------------------

bool ExTeleportEvo::Check(int aUserIndex)
{
	if(OBJMAX_RANGE(aUserIndex) == 0)
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aUserIndex];

	if(!lpUser)
	{
		return false;
	}

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	for(int i = 0; i < this->iLoadedCount; i++)
	{
		if(this->data[i].map == lpUser->MapNumber)
		{
			return false;
		}
	}

	return true;
}
// ----------------------------------------------------------------------------------------------

void ExTeleportEvo::GCWindows(int aUserIndex)
{
	if(OBJMAX_RANGE(aUserIndex) == 0)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aUserIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	PMSG_GC_TELEPORTWINEVO pMsg;
	ZeroMemory(&pMsg, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xFA, 0x12, sizeof(pMsg));

	pMsg.count = this->iLoadedCount;
	

	for(int i = 0; i < this->iLoadedCount; i++)
	{
		pMsg.tdata[i].result = 1;
		pMsg.tdata[i].map = this->data[i].map;
		pMsg.tdata[i].x = this->data[i].x;
		pMsg.tdata[i].y = this->data[i].y;
		pMsg.tdata[i].min_level = this->data[i].min_level;
		pMsg.tdata[i].max_level = this->data[i].max_level;
		pMsg.tdata[i].min_reset = this->data[i].min_reset;
		pMsg.tdata[i].max_reset = this->data[i].max_reset;
		pMsg.tdata[i].min_grand = this->data[i].min_grand;
		pMsg.tdata[i].max_grand = this->data[i].max_grand;
		pMsg.tdata[i].premium = this->data[i].premium;
		pMsg.tdata[i].zen = this->data[i].zen;
		pMsg.tdata[i].bonus = this->data[i].bonus;
		pMsg.tdata[i].credit = this->data[i].credit;
		pMsg.tdata[i].Master = this->data[i].Master;
		pMsg.tdata[i].EmptyInv = this->data[i].EmptyInv;

		pMsg.tdata[i].ok_level = 1;
		pMsg.tdata[i].ok_reset = 1;
		pMsg.tdata[i].ok_grand = 1;
		pMsg.tdata[i].ok_premium = 1;
		pMsg.tdata[i].ok_zen = 1;
		pMsg.tdata[i].ok_bonus = 1;
		pMsg.tdata[i].ok_credit = 1;
		pMsg.tdata[i].ok_Master = 1;
		pMsg.tdata[i].ok_EmptyInv = 1;

		if(this->data[i].min_level > lpUser->Level || lpUser->Level > this->data[i].max_level )
		{
			pMsg.tdata[i].result = 0;
			pMsg.tdata[i].ok_level = 0;
		}
		if(this->data[i].min_reset > lpUser->Reset || lpUser->Reset > this->data[i].max_reset )
		{
			pMsg.tdata[i].result = 0;
			pMsg.tdata[i].ok_reset = 0;
		}
		if(this->data[i].min_grand > lpUser->GReset || lpUser->GReset > this->data[i].max_grand )
		{
			pMsg.tdata[i].result = 0;
			pMsg.tdata[i].ok_grand = 0;
		}
		if(this->data[i].premium > 0 && lpUser->PremiumTime == 0)
		{
			pMsg.tdata[i].result = 0;
			pMsg.tdata[i].ok_premium = 0;
		}
#if(LICENSE_MUEVIL)
		if(this->data[i].premium > lpUser->PremiumTimeType)
		{
			pMsg.tdata[i].result = 0;
			pMsg.tdata[i].ok_premium = 0;
		}
#endif
		if(this->data[i].zen > lpUser->Money)
		{
			pMsg.tdata[i].result = 0;
			pMsg.tdata[i].ok_zen = 0;
		}
		if(this->data[i].bonus > lpUser->GameShop.WCoinC)
		{
			pMsg.tdata[i].result = 0;
			pMsg.tdata[i].ok_bonus = 0;
		}
		if(this->data[i].credit > lpUser->ExCred)
		{
			pMsg.tdata[i].result = 0;
			pMsg.tdata[i].ok_credit = 0;
		}
		if(this->data[i].Master)
		{
			if(!lpUser->ChangeUP3rd)
			{
				pMsg.tdata[i].result = 0;
				pMsg.tdata[i].ok_Master = 0;
			}
		}
		if(this->data[i].EmptyInv)
		{
			for(int n = 0; n < INVENTORY_SIZE; n++)
			{
				if(lpUser->pInventory[n].IsItem() == TRUE)
				{
					pMsg.tdata[i].result = 0;
					pMsg.tdata[i].ok_EmptyInv = 0;				
				}
			}
		}

	}

	DataSend(lpUser->m_Index, (LPBYTE)&pMsg, sizeof(pMsg));
}
// ----------------------------------------------------------------------------------------------

void ExTeleportEvo::CGResult(PMSG_CG_TELEPORTWINRESEVO* aRecv, int aUserIndex)
{
	if(OBJMAX_RANGE(aUserIndex) == 0)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aUserIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	int i = aRecv->result;

	if(i < 0 || i > this->iLoadedCount)
	{
		return;
	}

	if(this->data[i].min_level > lpUser->Level || lpUser->Level > this->data[i].max_level)
	{
		return;
	}
	if(this->data[i].min_reset > lpUser->Reset || lpUser->Reset > this->data[i].max_reset)
	{
		return;
	}
	if(this->data[i].min_grand > lpUser->GReset || lpUser->GReset > this->data[i].max_grand)
	{
		return;
	}
	if(this->data[i].premium > 0)
	{
		#if(LICENSE_MUEVIL)
		if(this->data[i].premium > lpUser->PremiumTimeType)
		{
			return;
		}
		#endif
		if(lpUser->PremiumTime <= 0)
		{
			return;
		}		
	}
	if(this->data[i].zen > lpUser->Money)
	{
		return;
	}
	if(this->data[i].bonus > lpUser->GameShop.WCoinC)
	{
		return;
	}
	if(this->data[i].credit > lpUser->ExCred)
	{
		return;
	}
	// ----
	if(this->data[i].zen > 0)
	{
		lpUser->Money -= this->data[i].zen;
		GCMoneySend(aUserIndex, lpUser->Money);
	}
	if(this->data[i].bonus > 0)
	{
		lpUser->GameShop.WCoinC -= this->data[i].bonus;
		ExUserDataSend(aUserIndex);
	}
	if(this->data[i].credit > 0)
	{
		lpUser->ExCred -= this->data[i].credit;
		ExUserDataSend(aUserIndex);
	}

	gObjTeleport(aUserIndex, this->data[i].map, this->data[i].x, this->data[i].y);
}
// ----------------------------------------------------------------------------------------------

void ExTeleportEvo::CGDialog(PMSG_CG_DIALOGEVO* lpMsg, int aUserIndex)
{
	if(OBJMAX_RANGE(aUserIndex) == 0)
	{
		return;
	}

	if(g_ExLicense.CheckUser(Local) || g_ExLicense.CheckUser(Gredy) || g_ExLicense.CheckUser(Gredy2) || g_ExLicense.CheckUser(GredyLocal))
	{
		this->GCWindows(aUserIndex);
	}
	else
	{
		g_ExTeleport.GCWindows(aUserIndex);
	}
}
// ----------------------------------------------------------------------------------------------
#endif