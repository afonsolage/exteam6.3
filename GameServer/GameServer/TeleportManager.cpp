#include "StdAfx.h"
#include "TeleportManager.h"
#include "Functions.h"
#include "Message.h"
#include "ExUser.h"
#include "ExLicense.h"
#include "logproc.h"
#include "ExText.h"

#ifdef TELEPORT_MANAGER

cTeleportManager gTeleportManager;

cTeleportManager::cTeleportManager()
{

}

cTeleportManager::~cTeleportManager()
{

}

void cTeleportManager::Load()
{
	this->Enable = GetPrivateProfileInt("ExTeam","Enable",0,TeleportManager_DIR);

	ZeroMemory(this->NpcBase,sizeof(NpcBase));
	ZeroMemory(this->CmdBase,sizeof(CmdBase));

	FILE * file = fopen(TeleportManager_DIR,"r");

	if(file == NULL)
	{
		MessageBoxA(0,TeleportManager_DIR,"LOAD FILE ERROR",0);
		this->Enable = false;
	}

	if(!this->Enable) return;

	char Buff[256];
	int Flag = 0;

	this->CountNPC = 0;
	this->CountCMD = 0;

	this->m_DLMasterBlock.clear();
	this->m_DLMemberBlock.clear();

	while(!feof(file))
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;

		if( g_ExLicense.CheckUser(eExUB::Local)		 || 
			g_ExLicense.CheckUser(eExUB::SILVER1)	 || 
			g_ExLicense.CheckUser(eExUB::SILVER2)	 ||
			g_ExLicense.CheckUser(eExUB::Gredy)		 || 
			g_ExLicense.CheckUser(eExUB::GredyLocal) || 
			g_ExLicense.CheckUser(eExUB::Gredy2) )
		{
			if(Flag == 1)
			{
				int n[15];
				sscanf(Buff, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7], &n[8], &n[9], &n[10], &n[11], &n[12], &n[13], &n[14]);
				this->NpcBase[this->CountNPC].NPC			= n[0];
				this->NpcBase[this->CountNPC].MAP			= n[1];
				this->NpcBase[this->CountNPC].X				= n[2];
				this->NpcBase[this->CountNPC].Y				= n[3];
				this->NpcBase[this->CountNPC].TeleportMap	= n[4];
				this->NpcBase[this->CountNPC].TeleportX		= n[5];
				this->NpcBase[this->CountNPC].TeleportY		= n[6];
				this->NpcBase[this->CountNPC].Level			= n[7];
				this->NpcBase[this->CountNPC].Reset			= n[8];
				this->NpcBase[this->CountNPC].GReset		= n[9];
				this->NpcBase[this->CountNPC].MaxReset		= n[10];
				this->NpcBase[this->CountNPC].MaxGReset		= n[11];
				this->NpcBase[this->CountNPC].Premium		= n[12];
				this->NpcBase[this->CountNPC].Price			= n[13];
				this->NpcBase[this->CountNPC].Value			= n[14];
				this->CountNPC++;
			}

			if(Flag == 2)
			{
				char mes[50];
				int n[11];
				sscanf(Buff, "\"%[^\"]\" %d %d %d %d %d %d %d %d %d %d %d", &mes, &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7], &n[8], &n[9], &n[10]);
				sprintf(this->CmdBase[this->CountCMD].Command,"%s",mes);
				this->CmdBase[this->CountCMD].TeleportMap	= n[0];
				this->CmdBase[this->CountCMD].TeleportX		= n[1];
				this->CmdBase[this->CountCMD].TeleportY		= n[2];
				this->CmdBase[this->CountCMD].Level			= n[3];
				this->CmdBase[this->CountCMD].Reset			= n[4];
				this->CmdBase[this->CountCMD].GReset		= n[5];
				this->CmdBase[this->CountCMD].MaxReset		= n[6];
				this->CmdBase[this->CountCMD].MaxGReset		= n[7];
				this->CmdBase[this->CountCMD].Premium		= n[8];
				this->CmdBase[this->CountCMD].Price			= n[9];
				this->CmdBase[this->CountCMD].Value			= n[10];
				this->CountCMD++;
			}

		}
		else
		{
			if(Flag == 1)
			{
				int n[13];
				sscanf(Buff, "%d %d %d %d %d %d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7], &n[8], &n[9], &n[10], &n[11], &n[12]);
				this->NpcBase[this->CountNPC].NPC			= n[0];
				this->NpcBase[this->CountNPC].MAP			= n[1];
				this->NpcBase[this->CountNPC].X				= n[2];
				this->NpcBase[this->CountNPC].Y				= n[3];
				this->NpcBase[this->CountNPC].TeleportMap	= n[4];
				this->NpcBase[this->CountNPC].TeleportX		= n[5];
				this->NpcBase[this->CountNPC].TeleportY		= n[6];
				this->NpcBase[this->CountNPC].Level			= n[7];
				this->NpcBase[this->CountNPC].Reset			= n[8];
				this->NpcBase[this->CountNPC].GReset		= n[9];
				this->NpcBase[this->CountNPC].Premium		= n[10];
				this->NpcBase[this->CountNPC].Price			= n[11];
				this->NpcBase[this->CountNPC].Value			= n[12];
				this->CountNPC++;
			}

			if(Flag == 2)
			{
				char mes[50];
				int n[9];
				sscanf(Buff, "\"%[^\"]\" %d %d %d %d %d %d %d %d %d", &mes, &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7], &n[8]);
				sprintf(this->CmdBase[this->CountCMD].Command,"%s",mes);
				this->CmdBase[this->CountCMD].TeleportMap	= n[0];
				this->CmdBase[this->CountCMD].TeleportX		= n[1];
				this->CmdBase[this->CountCMD].TeleportY		= n[2];
				this->CmdBase[this->CountCMD].Level			= n[3];
				this->CmdBase[this->CountCMD].Reset			= n[4];
				this->CmdBase[this->CountCMD].GReset		= n[5];
				this->CmdBase[this->CountCMD].Premium		= n[6];
				this->CmdBase[this->CountCMD].Price			= n[7];
				this->CmdBase[this->CountCMD].Value			= n[8];
				this->CountCMD++;
			}
		}

		if( g_ExLicense.CheckUser(eExUB::Local)		 || 
			g_ExLicense.CheckUser(eExUB::SILVER1)	 || 
			g_ExLicense.CheckUser(eExUB::SILVER2)	 ||
			LICENSE_ARCMU )
		{
			if(Flag == 3)
			{
				int n;
				sscanf(Buff, "%d", &n);
				DLTP_BLOCK_DATA List;			
				List.MapNumber = n;
				this->m_dlblock.push_back(List);
			}
		}

		if( g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) )
		{
			if(Flag == 4)
			{
				int n;
				sscanf(Buff, "%d", &n);
				DLTP_BLOCK_DATA List;			
				List.MapNumber = n;
				this->m_DLMasterBlock.push_back(List);
			}

			if(Flag == 5)
			{
				int n;
				sscanf(Buff, "%d", &n);
				DLTP_BLOCK_DATA List;			
				List.MapNumber = n;
				this->m_DLMemberBlock.push_back(List);
			}
		}
	}
	fclose(file);
}

void cTeleportManager::NPCClick(LPOBJ lpNpc, LPOBJ lpObj)
{
	if(!this->Enable) return;

	for(int a=0;a<this->CountNPC;a++)
	{
		if(this->NpcBase[a].NPC == lpNpc->Class && 
			this->NpcBase[a].MAP == lpNpc->MapNumber &&
			this->NpcBase[a].X == lpNpc->X &&
			this->NpcBase[a].Y == lpNpc->Y ||
			this->NpcBase[a].NPC == lpNpc->Class &&
			this->NpcBase[a].MAP == -1)
		{
			// ----

			if(this->NpcBase[a].Level > lpObj->Level)
			{
				MsgNormal(lpObj->m_Index,g_ExText.GetText(255),this->NpcBase[a].Level);
				return;
			}

			if(this->NpcBase[a].Reset > lpObj->Reset)
			{
				MsgNormal(lpObj->m_Index,g_ExText.GetText(256),this->NpcBase[a].Reset);
				return;
			}

			if(this->NpcBase[a].GReset > lpObj->GReset)
			{
				MsgNormal(lpObj->m_Index,g_ExText.GetText(257),this->NpcBase[a].GReset);
				return;
			}

			if( g_ExLicense.CheckUser(eExUB::Local)		 || 
				g_ExLicense.CheckUser(eExUB::SILVER1)	 || 
				g_ExLicense.CheckUser(eExUB::SILVER2)	 ||
				g_ExLicense.CheckUser(eExUB::Gredy)		 || 
				g_ExLicense.CheckUser(eExUB::GredyLocal) || 
				g_ExLicense.CheckUser(eExUB::Gredy2) )
			{
				if(this->NpcBase[a].MaxReset < lpObj->Reset)
				{
					MsgNormal(lpObj->m_Index,g_ExText.GetText(256),this->NpcBase[a].MaxReset);
					return;
				}

				if(this->NpcBase[a].MaxGReset < lpObj->GReset)
				{
					MsgNormal(lpObj->m_Index,g_ExText.GetText(257),this->NpcBase[a].MaxGReset);
					return;
				}
			}

			if(this->NpcBase[a].Premium)
			{
				if(g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2))
				{
					if(this->NpcBase[a].Premium != lpObj->PremiumTimeType || lpObj->PremiumTime == 0)
					{
						MsgNormal(lpObj->m_Index,g_ExText.GetText(258), this->NpcBase[a].Premium);
						return;
					}
				}
				else
				{
					if(lpObj->PremiumTime == 0)
					{
						MsgNormal(lpObj->m_Index,g_ExText.GetText(259));
						return;
					}
				}
			}

			switch(this->NpcBase[a].Price)
			{
			case 1:
				{
					if(this->NpcBase[a].Value > lpObj->Money )
					{
						MsgNormal(lpObj->m_Index,g_ExText.GetText(260),this->NpcBase[a].Value);
						return;
					}
					lpObj->Money -= this->NpcBase[a].Value;
					GCMoneySend(lpObj->m_Index,lpObj->Money);
				}
				break;
			case 2:
				{
					if(this->NpcBase[a].Value > lpObj->ExCred )
					{
						MsgNormal(lpObj->m_Index,g_ExText.GetText(261),this->NpcBase[a].Value);
						return;
					}
					lpObj->ExCred -= this->NpcBase[a].Value;
					ExUserDataSend(lpObj->m_Index);
				}
				break;
			case 3:
				{
					if(this->NpcBase[a].Value > lpObj->GameShop.WCoinC )
					{
						MsgNormal(lpObj->m_Index,g_ExText.GetText(262),this->NpcBase[a].Value);
						return;
					}
					lpObj->GameShop.WCoinC -= this->NpcBase[a].Value;
					gGameShop.GDSaveUserInfo(lpObj->m_Index);
				}
				break;
			case 4:
				{
					if(this->NpcBase[a].Value > lpObj->GameShop.WCoinP )
					{
						MsgNormal(lpObj->m_Index,g_ExText.GetText(263),this->NpcBase[a].Value);
						return;
					}
					lpObj->GameShop.WCoinP -= this->NpcBase[a].Value;
					gGameShop.GDSaveUserInfo(lpObj->m_Index);
				}
				break;
			case 5:
				{
					if(this->NpcBase[a].Value > lpObj->GameShop.GoblinPoint )
					{
						MsgNormal(lpObj->m_Index,g_ExText.GetText(264),this->NpcBase[a].Value);
						return;
					}
					lpObj->GameShop.GoblinPoint -= this->NpcBase[a].Value;
					gGameShop.GDSaveUserInfo(lpObj->m_Index);
				}
				break;
			default:

				break;
			}

			gObjTeleport(lpObj->m_Index,this->NpcBase[a].TeleportMap,this->NpcBase[a].TeleportX,this->NpcBase[a].TeleportY);
			return;
		}
	}
}

void cTeleportManager::ChatDataSend(int aIndex, LPBYTE Protocol)
{
	return;

	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	for(int a=0;a<this->CountCMD;a++)
	{
		if(!memcmp(&Protocol[13],this->CmdBase[a].Command,strlen(this->CmdBase[a].Command)))
		{
			// ----

			if(this->CmdBase[a].Level > lpObj->Level)
			{
				MsgNormal(lpObj->m_Index,g_ExText.GetText(255),this->CmdBase[a].Level);
				return;
			}

			if(this->CmdBase[a].Reset > lpObj->Reset)
			{
				MsgNormal(lpObj->m_Index,g_ExText.GetText(256),this->CmdBase[a].Reset);
				return;
			}

			if(this->CmdBase[a].GReset > lpObj->GReset)
			{
				MsgNormal(lpObj->m_Index,g_ExText.GetText(257),this->CmdBase[a].GReset);
				return;
			}

			if( g_ExLicense.CheckUser(eExUB::Local)		 || 
				g_ExLicense.CheckUser(eExUB::SILVER1)	 || 
				g_ExLicense.CheckUser(eExUB::SILVER2)	 ||
				g_ExLicense.CheckUser(eExUB::Gredy)		 || 
				g_ExLicense.CheckUser(eExUB::GredyLocal) || 
				g_ExLicense.CheckUser(eExUB::Gredy2) )
			{
				if(this->CmdBase[a].MaxReset < lpObj->Reset)
				{
					MsgNormal(lpObj->m_Index,g_ExText.GetText(265),this->CmdBase[a].MaxReset);
					return;
				}

				if(this->CmdBase[a].MaxGReset < lpObj->GReset)
				{
					MsgNormal(lpObj->m_Index,g_ExText.GetText(266),this->CmdBase[a].MaxGReset);
					return;
				}
			}

			if(this->CmdBase[a].Premium)
			{
				if(g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2))
				{
					if(this->CmdBase[a].Premium != lpObj->PremiumTimeType || lpObj->PremiumTime == 0)
					{
						MsgNormal(lpObj->m_Index,g_ExText.GetText(258), this->CmdBase[a].Premium);
						return;
					}
				}
				else
				{
					if(lpObj->PremiumTime == 0)
					{
						MsgNormal(lpObj->m_Index,g_ExText.GetText(259));
						return;
					}
				}
			}

			switch(this->CmdBase[a].Price)
			{
			case 1:
				{
					if(this->CmdBase[a].Value > lpObj->Money )
					{
						MsgNormal(lpObj->m_Index,g_ExText.GetText(260),this->CmdBase[a].Value);
						return;
					}
					lpObj->Money -= this->CmdBase[a].Value;
					GCMoneySend(lpObj->m_Index,lpObj->Money);
				}
				break;
			case 2:
				{
					if(this->CmdBase[a].Value > lpObj->ExCred )
					{
						MsgNormal(lpObj->m_Index,g_ExText.GetText(261),this->CmdBase[a].Value);
						return;
					}
					lpObj->ExCred -= this->CmdBase[a].Value;
					ExUserDataSend(lpObj->m_Index);
				}
				break;
			case 3:
				{
					if(this->CmdBase[a].Value > lpObj->GameShop.WCoinC )
					{
						MsgNormal(lpObj->m_Index,g_ExText.GetText(262),this->CmdBase[a].Value);
						return;
					}
					lpObj->GameShop.WCoinC -= this->CmdBase[a].Value;
					gGameShop.GDSaveUserInfo(lpObj->m_Index);
				}
				break;
			case 4:
				{
					if(this->CmdBase[a].Value > lpObj->GameShop.WCoinP )
					{
						MsgNormal(lpObj->m_Index,g_ExText.GetText(263),this->CmdBase[a].Value);
						return;
					}
					lpObj->GameShop.WCoinP -= this->CmdBase[a].Value;
					gGameShop.GDSaveUserInfo(lpObj->m_Index);
				}
				break;
			case 5:
				{
					if(this->CmdBase[a].Value > lpObj->GameShop.GoblinPoint )
					{
						MsgNormal(lpObj->m_Index,g_ExText.GetText(264),this->CmdBase[a].Value);
						return;
					}
					lpObj->GameShop.GoblinPoint -= this->CmdBase[a].Value;
					gGameShop.GDSaveUserInfo(lpObj->m_Index);
				}
				break;
			default:

				break;
			}

			gObjTeleport(lpObj->m_Index,this->CmdBase[a].TeleportMap,this->CmdBase[a].TeleportX,this->CmdBase[a].TeleportY);
			return;
		}
	}
}

bool cTeleportManager::CheckTeleoprtMap(int aIndex, int aTargetIndex)
{
	if(!this->Enable)
	{
		return true;
	}

	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return false;
	}

	if ( OBJMAX_RANGE(aTargetIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpTarget = &gObj[aTargetIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	if(lpTarget->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	for(int a=0;a<this->CountNPC;a++)
	{
		if(this->NpcBase[a].Premium)
		{
			if(lpTarget->PremiumTime == 0 && this->NpcBase[a].TeleportMap == lpUser->MapNumber)
			{
				MsgNormal(lpTarget->m_Index,"[Need Premium]: Status");
				return false;
			}
		}
	}

	for(int a=0;a<this->CountCMD;a++)
	{
		if(this->CmdBase[a].Premium)
		{
			if(lpTarget->PremiumTime == 0 && this->CmdBase[a].TeleportMap == lpUser->MapNumber)
			{
				MsgNormal(lpTarget->m_Index,"[Need Premium]: Status");
				return false;
			}
		}
	}

	return true;

}

#if(SILVER_DL_TP)
bool cTeleportManager::CheckTeleportDL(int map)
{
	if( g_ExLicense.CheckUser(eExUB::SILVER1)	 || 
		g_ExLicense.CheckUser(eExUB::SILVER2)	 )
	{
		for(int i = 0; i < this->m_dlblock.size(); i++)
		{
			if(this->m_dlblock[i].MapNumber == map)
			{
				return false;
			}
		}
	}

	return true;
}
#endif

bool cTeleportManager::CheckDLMasterTeleport(int Map)
{
	if( g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) )
	{
		for(int i = 0; i < this->m_DLMasterBlock.size(); i++)
		{
			if(this->m_DLMasterBlock[i].MapNumber == Map)
			{
				return false;
			}
		}
	}

	return true;
}

bool cTeleportManager::CheckDLMemberTeleport(int Map)
{
	if( g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) )
	{
		for(int i = 0; i < this->m_DLMemberBlock.size(); i++)
		{
			if(this->m_DLMemberBlock[i].MapNumber == Map)
			{
				return false;
			}
		}
	}

	return true;
}

#endif