#include "StdAfx.h"
#include "BalanceSystem.h"
#include "GameMain.h"
#include "user.h"
#include "ExFunction.h"
#include "ExLicense.h"
#include "..\\include\\ReadScript.h"
#include "GameMain.h"
#include "logproc.h"

#ifdef _BALANS_SYSTEM_

cBalanceSystem gBalanceSystem;

cBalanceSystem::cBalanceSystem()
{
	this->Init();
}

cBalanceSystem::~cBalanceSystem()
{
}

void cBalanceSystem::Init()
{
	this->Enable	= true;

	this->DKvsDK	= 100;
	this->DKvsDW	= 100;
	this->DKvsELF	= 100;
	this->DKvsSUM	= 100;
	this->DKvsMG	= 100;
	this->DKvsDL	= 100;
	this->DKvsRF	= 100;

	this->DWvsDW	= 100;
	this->DWvsDK	= 100;
	this->DWvsELF	= 100;
	this->DWvsSUM	= 100;
	this->DWvsMG	= 100;
	this->DWvsDL	= 100;
	this->DWvsRF	= 100;

	this->ELFvsELF	= 100;
	this->ELFvsDK	= 100;
	this->ELFvsDW	= 100;
	this->ELFvsSUM	= 100;
	this->ELFvsMG	= 100;
	this->ELFvsDL	= 100;
	this->ELFvsRF	= 100;

	this->SUMvsSUM	= 100;
	this->SUMvsDK	= 100;
	this->SUMvsDW	= 100;
	this->SUMvsELF	= 100;
	this->SUMvsMG	= 100;
	this->SUMvsDL	= 100;
	this->SUMvsRF	= 100;

	this->MGvsMG	= 100;
	this->MGvsDK	= 100;
	this->MGvsDW	= 100;
	this->MGvsELF	= 100;
	this->MGvsSUM	= 100;
	this->MGvsDL	= 100;
	this->MGvsRF	= 100;

	this->DLvsDL	= 100;
	this->DLvsDK	= 100;
	this->DLvsDW	= 100;
	this->DLvsELF	= 100;
	this->DLvsSUM	= 100;
	this->DLvsMG	= 100;
	this->DLvsRF	= 100;

	this->RFvsRF	= 100;
	this->RFvsDK	= 100;
	this->RFvsDW	= 100;
	this->RFvsELF	= 100;
	this->RFvsSUM	= 100;
	this->RFvsMG	= 100;
	this->RFvsDL	= 100;

	this->m_EnableMonster = false;

	this->m_DKvsMonster = 100;
	this->m_DWvsMonster = 100;
	this->m_ELFvsMonster = 100;
	this->m_SUMvsMonster = 100;
	this->m_MGvsMonster = 100;
	this->m_DLvsMonster = 100;
	this->m_RFvsMonster = 100;

	this->m_EnableRefflect = 0;
	this->m_DWRefflectPercent = 100;
	this->m_DKRefflectPercent = 100;
	this->m_FERefflectPercent = 100;
	this->m_MGRefflectPercent = 100;
	this->m_DLRefflectPercent = 100;
	this->m_SURefflectPercent = 100;
	this->m_RFRefflectPercent = 100;

	this->m_EnableDamagePercent = false;
	this->m_vResetDamage.clear();
}

void cBalanceSystem::ReadConfigs(char * File)
{
	CheckFile(File);

	this->Enable	= GetPrivateProfileInt("Common", "Enable", 0, File);

	this->DKvsDK	= GetPrivateProfileInt("Common", "DKvsDK", 100, File);
	this->DKvsDW	= GetPrivateProfileInt("Common", "DKvsDW", 100, File);
	this->DKvsELF	= GetPrivateProfileInt("Common", "DKvsELF", 100, File);
	this->DKvsSUM	= GetPrivateProfileInt("Common", "DKvsSUM", 100, File);
	this->DKvsMG	= GetPrivateProfileInt("Common", "DKvsMG", 100, File);
	this->DKvsDL	= GetPrivateProfileInt("Common", "DKvsDL", 100, File);
	this->DKvsRF	= GetPrivateProfileInt("Common", "DKvsRF", 100, File);

	this->DWvsDW	= GetPrivateProfileInt("Common", "DWvsDW", 100, File);
	this->DWvsDK	= GetPrivateProfileInt("Common", "DWvsDK", 100, File);
	this->DWvsELF	= GetPrivateProfileInt("Common", "DWvsELF", 100, File);
	this->DWvsSUM	= GetPrivateProfileInt("Common", "DWvsSUM", 100, File);
	this->DWvsMG	= GetPrivateProfileInt("Common", "DWvsMG", 100, File);
	this->DWvsDL	= GetPrivateProfileInt("Common", "DWvsDL", 100, File);
	this->DWvsRF	= GetPrivateProfileInt("Common", "DWvsRF", 100, File);

	this->ELFvsELF	= GetPrivateProfileInt("Common", "ELFvsELF", 100, File);
	this->ELFvsDK	= GetPrivateProfileInt("Common", "ELFvsDK", 100, File);
	this->ELFvsDW	= GetPrivateProfileInt("Common", "ELFvsDW", 100, File);
	this->ELFvsSUM	= GetPrivateProfileInt("Common", "ELFvsSUM", 100, File);
	this->ELFvsMG	= GetPrivateProfileInt("Common", "ELFvsMG ", 100, File);
	this->ELFvsDL	= GetPrivateProfileInt("Common", "ELFvsDL", 100, File);
	this->ELFvsRF	= GetPrivateProfileInt("Common", "ELFvsRF", 100, File);

	this->SUMvsSUM	= GetPrivateProfileInt("Common", "SUMvsSUM", 100, File);
	this->SUMvsDK	= GetPrivateProfileInt("Common", "SUMvsDK", 100, File);
	this->SUMvsDW	= GetPrivateProfileInt("Common", "SUMvsDW", 100, File);
	this->SUMvsELF	= GetPrivateProfileInt("Common", "SUMvsELF", 100, File);
	this->SUMvsMG	= GetPrivateProfileInt("Common", "SUMvsMG", 100, File);
	this->SUMvsDL	= GetPrivateProfileInt("Common", "SUMvsDL", 100, File);
	this->SUMvsRF	= GetPrivateProfileInt("Common", "SUMvsRF", 100, File);

	this->MGvsMG	= GetPrivateProfileInt("Common", "MGvsMG", 100, File);
	this->MGvsDK	= GetPrivateProfileInt("Common", "MGvsDK", 100, File);
	this->MGvsDW	= GetPrivateProfileInt("Common", "MGvsDW", 100, File);
	this->MGvsELF	= GetPrivateProfileInt("Common", "MGvsELF", 100, File);
	this->MGvsSUM	= GetPrivateProfileInt("Common", "MGvsSUM", 100, File);
	this->MGvsDL	= GetPrivateProfileInt("Common", "MGvsDL", 100, File);
	this->MGvsRF	= GetPrivateProfileInt("Common", "MGvsRF", 100, File);

	this->DLvsDL	= GetPrivateProfileInt("Common", "DLvsDL", 100, File);
	this->DLvsDK	= GetPrivateProfileInt("Common", "DLvsDK", 100, File);
	this->DLvsDW	= GetPrivateProfileInt("Common", "DLvsDW", 100, File);
	this->DLvsELF	= GetPrivateProfileInt("Common", "DLvsELF", 100, File);
	this->DLvsSUM	= GetPrivateProfileInt("Common", "DLvsSUM", 100, File);
	this->DLvsMG	= GetPrivateProfileInt("Common", "DLvsMG", 100, File);
	this->DLvsRF	= GetPrivateProfileInt("Common", "DLvsRF", 100, File);

	this->RFvsRF	= GetPrivateProfileInt("Common", "RFvsRF", 100, File);
	this->RFvsDK	= GetPrivateProfileInt("Common", "RFvsDK", 100, File);
	this->RFvsDW	= GetPrivateProfileInt("Common", "RFvsDW", 100, File);
	this->RFvsELF	= GetPrivateProfileInt("Common", "RFvsELF", 100, File);
	this->RFvsSUM	= GetPrivateProfileInt("Common", "RFvsSUM", 100, File);
	this->RFvsMG	= GetPrivateProfileInt("Common", "RFvsMG", 100, File);
	this->RFvsDL	= GetPrivateProfileInt("Common", "RFvsDL", 100, File);

	if( g_ExLicense.CheckUser(MedoniAndrei) || 
		g_ExLicense.CheckUser(Gredy) || g_ExLicense.CheckUser(Gredy2) || g_ExLicense.CheckUser(GredyLocal) ||
		g_ExLicense.CheckUser(ulasevich) || g_ExLicense.CheckUser(ulasevich2) ||
		g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
	{
		this->m_EnableMonster = GetPrivateProfileInt("Monster", "EnableMonster", 1, File);

		this->m_DKvsMonster = GetPrivateProfileInt("Monster", "DKvsMonster", 100, File);
		this->m_DWvsMonster = GetPrivateProfileInt("Monster", "DWvsMonster", 100, File);
		this->m_ELFvsMonster = GetPrivateProfileInt("Monster", "ELFvsMonster", 100, File);
		this->m_SUMvsMonster = GetPrivateProfileInt("Monster", "SUMvsMonster", 100, File);
		this->m_MGvsMonster = GetPrivateProfileInt("Monster", "MGvsMonster", 100, File);
		this->m_DLvsMonster = GetPrivateProfileInt("Monster", "DLvsMonster", 100, File);
		this->m_RFvsMonster = GetPrivateProfileInt("Monster", "RFvsMonster", 100, File);
	}

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
	{
		this->m_DKFenrirDamagePercent = GetPrivateProfileInt("Pet", "DKFenrirDamagePercent", 100, File);

		this->m_EnableRefflect = GetPrivateProfileInt("Reflect", "EnableReflect", 1, File);
		this->m_DWRefflectPercent = GetPrivateProfileInt("Reflect", "DWReflectPercent", 100, File);
		this->m_DKRefflectPercent = GetPrivateProfileInt("Reflect", "DKReflectPercent", 100, File);
		this->m_FERefflectPercent = GetPrivateProfileInt("Reflect", "FEReflectPercent", 100, File);
		this->m_MGRefflectPercent = GetPrivateProfileInt("Reflect", "MGReflectPercent", 100, File);
		this->m_DLRefflectPercent = GetPrivateProfileInt("Reflect", "DLReflectPercent", 100, File);
		this->m_SURefflectPercent = GetPrivateProfileInt("Reflect", "SUReflectPercent", 100, File);
		this->m_RFRefflectPercent = GetPrivateProfileInt("Reflect", "RFReflectPercent", 100, File);
	}

	if(g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ulasevich2))
	{
		this->m_vResetDamage.clear();
		this->ReadResetDamage(gDirPath.GetNewPath("ExData\\BalanceDamage.dat"));
	}

}

void cBalanceSystem::ReadResetDamage(char* filename)
{
	SMDToken Token;

	SMDFile = fopen(filename, "r");

	if(!SMDFile)
	{
		MsgBox("[Ancent Drop] %s file not found", filename);
		return;
	}

	while(true)
	{
		Token = GetToken();

		if( Token == END )
		{
			break;
		}

		int iType = (int)TokenNumber;

		if(iType != 0 && iType != 1)
		{
			break;
		}

		while(true)
		{
			if(iType == 0)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				this->m_EnableDamagePercent = (int)TokenNumber;
			}
			else if(iType == 1)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				BALANS_RESET_DAMAGE List;

				List.ResetNumber = (int)TokenNumber;

				Token = GetToken();
				List.DWDamagePercent = (int)TokenNumber;

				Token = GetToken();
				List.DKDamagePercent = (int)TokenNumber;

				Token = GetToken();
				List.FEDamagePercent = (int)TokenNumber;

				Token = GetToken();
				List.MGDamagePercent = (int)TokenNumber;

				Token = GetToken();
				List.DLDamagePercent = (int)TokenNumber;

				Token = GetToken();
				List.SUDamagePercent = (int)TokenNumber;

				Token = GetToken();
				List.RFDamagePercent = (int)TokenNumber;

				this->m_vResetDamage.push_back(List);
			}
		}
	}

	fclose(SMDFile);
	LogAdd("%s file load!", filename);
}

void cBalanceSystem::Load()
{
	this->Init();
	this->ReadConfigs(gDirPath.GetNewPath(BALANCESYSTEM_DIR));
}

void cBalanceSystem::Main(LPOBJ lpObj, LPOBJ lpTarget, int & AttackDamage)
{
	if(this->Enable)
	{
		if(lpObj->Type == OBJ_USER && lpTarget->Type == OBJ_USER)
		{
			if(lpObj->Class == CLASS_KNIGHT)
			{
				switch(lpTarget->Class)
				{
					case CLASS_KNIGHT:		AttackDamage = ( AttackDamage * this->DKvsDK ) / 100; break;
					case CLASS_WIZARD:		AttackDamage = ( AttackDamage * this->DKvsDW ) / 100; break;
					case CLASS_ELF:			AttackDamage = ( AttackDamage * this->DKvsELF) / 100; break;
					case CLASS_SUMMONER:	AttackDamage = ( AttackDamage * this->DKvsSUM) / 100; break;
					case CLASS_MAGUMSA:		AttackDamage = ( AttackDamage * this->DKvsMG ) / 100; break;
					case CLASS_DARKLORD:	AttackDamage = ( AttackDamage * this->DKvsDL ) / 100; break;
					case CLASS_MONK:		AttackDamage = ( AttackDamage * this->DKvsRF ) / 100; break;
				}
			}
			else if(lpObj->Class == CLASS_WIZARD)
			{
				switch(lpTarget->Class)
				{
					case CLASS_WIZARD:		AttackDamage = ( AttackDamage * this->DWvsDW ) / 100; break;
					case CLASS_KNIGHT:		AttackDamage = ( AttackDamage * this->DWvsDK ) / 100; break;
					case CLASS_ELF:			AttackDamage = ( AttackDamage * this->DWvsELF) / 100; break;
					case CLASS_SUMMONER:	AttackDamage = ( AttackDamage * this->DWvsSUM) / 100; break;
					case CLASS_MAGUMSA:		AttackDamage = ( AttackDamage * this->DWvsMG ) / 100; break;
					case CLASS_DARKLORD:	AttackDamage = ( AttackDamage * this->DWvsDL ) / 100; break;
					case CLASS_MONK:		AttackDamage = ( AttackDamage * this->DWvsRF ) / 100; break;
				}
			}
			else if(lpObj->Class == CLASS_ELF)
			{
				switch(lpTarget->Class)
				{
					case CLASS_ELF:			AttackDamage = ( AttackDamage * this->ELFvsELF ) / 100; break;
					case CLASS_KNIGHT:		AttackDamage = ( AttackDamage * this->ELFvsDK ) / 100; break;
					case CLASS_WIZARD:		AttackDamage = ( AttackDamage * this->ELFvsDW ) / 100; break;
					case CLASS_SUMMONER:	AttackDamage = ( AttackDamage * this->ELFvsSUM) / 100; break;
					case CLASS_MAGUMSA:		AttackDamage = ( AttackDamage * this->ELFvsMG ) / 100; break;
					case CLASS_DARKLORD:	AttackDamage = ( AttackDamage * this->ELFvsDL ) / 100; break;
					case CLASS_MONK:		AttackDamage = ( AttackDamage * this->ELFvsRF ) / 100; break;
				}
			}
			else if(lpObj->Class == CLASS_SUMMONER)
			{
				switch(lpTarget->Class)
				{
					case CLASS_SUMMONER:	AttackDamage = ( AttackDamage * this->SUMvsSUM ) / 100; break;
					case CLASS_KNIGHT:		AttackDamage = ( AttackDamage * this->SUMvsDK ) / 100; break;
					case CLASS_WIZARD:		AttackDamage = ( AttackDamage * this->SUMvsDW ) / 100; break;
					case CLASS_ELF:			AttackDamage = ( AttackDamage * this->SUMvsELF) / 100; break;
					case CLASS_MAGUMSA:		AttackDamage = ( AttackDamage * this->SUMvsMG ) / 100; break;
					case CLASS_DARKLORD:	AttackDamage = ( AttackDamage * this->SUMvsDL ) / 100; break;
					case CLASS_MONK:		AttackDamage = ( AttackDamage * this->SUMvsRF ) / 100; break;
				}
			}
			else if(lpObj->Class == CLASS_MAGUMSA)
			{
				switch(lpTarget->Class)
				{
					case CLASS_MAGUMSA:		AttackDamage = ( AttackDamage * this->MGvsMG ) / 100; break;
					case CLASS_KNIGHT:		AttackDamage = ( AttackDamage * this->MGvsDK ) / 100; break;
					case CLASS_WIZARD:		AttackDamage = ( AttackDamage * this->MGvsDW ) / 100; break;
					case CLASS_ELF:			AttackDamage = ( AttackDamage * this->MGvsELF) / 100; break;
					case CLASS_SUMMONER:	AttackDamage = ( AttackDamage * this->MGvsSUM) / 100; break;
					case CLASS_DARKLORD:	AttackDamage = ( AttackDamage * this->MGvsDL ) / 100; break;
					case CLASS_MONK:		AttackDamage = ( AttackDamage * this->MGvsRF ) / 100; break;
				}
			}
			else if(lpObj->Class == CLASS_DARKLORD)
			{
				switch(lpTarget->Class)
				{
					case CLASS_DARKLORD:	AttackDamage = ( AttackDamage * this->DLvsDL ) / 100; break;
					case CLASS_KNIGHT:		AttackDamage = ( AttackDamage * this->DLvsDK ) / 100; break;
					case CLASS_WIZARD:		AttackDamage = ( AttackDamage * this->DLvsDW ) / 100; break;
					case CLASS_ELF:			AttackDamage = ( AttackDamage * this->DLvsELF) / 100; break;
					case CLASS_SUMMONER:	AttackDamage = ( AttackDamage * this->DLvsSUM) / 100; break;
					case CLASS_MAGUMSA:		AttackDamage = ( AttackDamage * this->DLvsMG ) / 100; break;
					case CLASS_MONK:		AttackDamage = ( AttackDamage * this->DLvsRF ) / 100; break;
				}
			}
			else if(lpObj->Class == CLASS_MONK)
			{
				switch(lpTarget->Class)
				{
					case CLASS_MONK:		AttackDamage = ( AttackDamage * this->RFvsRF ) / 100; break;
					case CLASS_KNIGHT:		AttackDamage = ( AttackDamage * this->RFvsDK ) / 100; break;
					case CLASS_WIZARD:		AttackDamage = ( AttackDamage * this->RFvsDW ) / 100; break;
					case CLASS_ELF:			AttackDamage = ( AttackDamage * this->RFvsELF) / 100; break;
					case CLASS_SUMMONER:	AttackDamage = ( AttackDamage * this->RFvsSUM) / 100; break;
					case CLASS_MAGUMSA:		AttackDamage = ( AttackDamage * this->RFvsMG ) / 100; break;
					case CLASS_DARKLORD:	AttackDamage = ( AttackDamage * this->RFvsDL ) / 100; break;
				}
			}

			if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
			{
				if(lpObj->Class == CLASS_KNIGHT)
				{
					if(lpObj->pInventory[8].m_Type == ITEMGET(13,37))
					{
						AttackDamage = ( AttackDamage * this->m_DKFenrirDamagePercent ) / 100;
					}
				}
			}
		}
	}

	if(this->m_EnableMonster)
	{
		if(lpObj->Type == OBJ_USER && lpTarget->Type == OBJ_MONSTER)
		{
			switch(lpObj->Class)
			{
				case CLASS_KNIGHT:		AttackDamage = ( AttackDamage * this->m_DKvsMonster ) / 100; break;
				case CLASS_WIZARD:		AttackDamage = ( AttackDamage * this->m_DWvsMonster ) / 100; break;
				case CLASS_ELF:			AttackDamage = ( AttackDamage * this->m_ELFvsMonster) / 100; break;
				case CLASS_SUMMONER:	AttackDamage = ( AttackDamage * this->m_SUMvsMonster) / 100; break;
				case CLASS_MAGUMSA:		AttackDamage = ( AttackDamage * this->m_MGvsMonster ) / 100; break;
				case CLASS_DARKLORD:	AttackDamage = ( AttackDamage * this->m_DLvsMonster ) / 100; break;
				case CLASS_MONK:		AttackDamage = ( AttackDamage * this->m_RFvsMonster ) / 100; break;
			}
		}
	}

	if(this->m_EnableDamagePercent)
	{
		if(lpObj->Type == OBJ_USER && lpTarget->Type == OBJ_MONSTER)
		{
			for(int i = 0; i < this->m_vResetDamage.size(); i++)
			{
				if(lpObj->Reset == this->m_vResetDamage[i].ResetNumber)
				{
					switch(lpObj->Class)
					{
						case CLASS_WIZARD:		AttackDamage = ( AttackDamage * this->m_vResetDamage[i].DWDamagePercent ) / 100; break;
						case CLASS_KNIGHT:		AttackDamage = ( AttackDamage * this->m_vResetDamage[i].DKDamagePercent ) / 100; break;
						case CLASS_ELF:			AttackDamage = ( AttackDamage * this->m_vResetDamage[i].FEDamagePercent) / 100; break;
						case CLASS_SUMMONER:	AttackDamage = ( AttackDamage * this->m_vResetDamage[i].SUDamagePercent) / 100; break;
						case CLASS_MAGUMSA:		AttackDamage = ( AttackDamage * this->m_vResetDamage[i].MGDamagePercent ) / 100; break;
						case CLASS_DARKLORD:	AttackDamage = ( AttackDamage * this->m_vResetDamage[i].DLDamagePercent ) / 100; break;
						case CLASS_MONK:		AttackDamage = ( AttackDamage * this->m_vResetDamage[i].RFDamagePercent ) / 100; break;
					}
				}
			}


		}
	}
}

void cBalanceSystem::Refflect(LPOBJ lpObj)
{
	if(this->m_EnableRefflect == true)
	{
		if(lpObj->Type == OBJ_USER)
		{
			//switch(lpObj->Class)
			//{
			//	case CLASS_KNIGHT:		AttackDamage = ( AttackDamage * this->m_DKRefflectPercent ) / 100; break;
			//	case CLASS_WIZARD:		AttackDamage = ( AttackDamage * this->m_DWRefflectPercent ) / 100; break;
			//	case CLASS_ELF:			AttackDamage = ( AttackDamage * this->m_FERefflectPercent ) / 100; break;
			//	case CLASS_SUMMONER:	AttackDamage = ( AttackDamage * this->m_SURefflectPercent ) / 100; break;
			//	case CLASS_MAGUMSA:		AttackDamage = ( AttackDamage * this->m_MGRefflectPercent ) / 100; break;
			//	case CLASS_DARKLORD:	AttackDamage = ( AttackDamage * this->m_DLRefflectPercent ) / 100; break;
			//	case CLASS_MONK:		AttackDamage = ( AttackDamage * this->m_RFRefflectPercent ) / 100; break;
			//}

			switch(lpObj->Class)
			{
			case CLASS_KNIGHT:		lpObj->DamageReflect = ( lpObj->DamageReflect * this->m_DKRefflectPercent ) / 100; break;
				case CLASS_WIZARD:		lpObj->DamageReflect = ( lpObj->DamageReflect * this->m_DWRefflectPercent ) / 100; break;
				case CLASS_ELF:			lpObj->DamageReflect = ( lpObj->DamageReflect * this->m_FERefflectPercent ) / 100; break;
				case CLASS_SUMMONER:	lpObj->DamageReflect = ( lpObj->DamageReflect * this->m_SURefflectPercent ) / 100; break;
				case CLASS_MAGUMSA:		lpObj->DamageReflect = ( lpObj->DamageReflect * this->m_MGRefflectPercent ) / 100; break;
				case CLASS_DARKLORD:	lpObj->DamageReflect = ( lpObj->DamageReflect * this->m_DLRefflectPercent ) / 100; break;
				case CLASS_MONK:		lpObj->DamageReflect = ( lpObj->DamageReflect * this->m_RFRefflectPercent ) / 100; break;
			}
		}
	}
}

#endif