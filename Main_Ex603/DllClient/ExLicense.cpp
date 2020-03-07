#include "stdafx.h"
#include "ExLicense.h"
#include "Monster.h"
#include "ItemSmokeEffect.h"
#include "Configs.h"
#include "PartySearch.h"
#include "PersonalShopEx.h"
#include "Smithy.h"
#include "TMemory.h"
#include "Interface.h"
#include "VisualFix.h"
#include "User.h"
#include "DonateShop.h"
#include "AddPoints.h"
#include "Console.h"
#include "WingEffect.h"
#include "MiniMenu.h"
#include "Controller.h"
#include "ChatExpanded.h"
#include "ItemSetOption.h"
#include "AccountSecurity.h"
#include "Interface.h"
#include "BuffIcon.h"
#include "ExMenuV3.h"
#include "StatsAdvance.h"
#include "PetEx.h"
#include "CustomInterfaceMenu.h"
// ----------------------------------------------------------------------------------------------

#if(EX_LICENSE==TRUE)

CExLicense g_ExLicense;
// ----------------------------------------------------------------------------------------------

static DWORD InterfaceBuffer;

Naked(_00811D69)
{
	_asm
	{
		MOV InterfaceBuffer, EDX
	}

	/*if(g_ExLicense.CheckUser(eExUB::Escalate))
	{
		if(InterfaceBuffer)
		{
			if(gObjUser.InSafeZone() && !gInterface.CheckWindow(Shop))
			{
				g_DonateShop.CG_CashSend();
			}
		}
	}
	else */if(g_ExLicense.m_ExMenuV2 || g_ExLicense.m_Achievements)
	{
		if(InterfaceBuffer)
		{
			if(gCustomMenuInterface.DrawTable)
					{
						gCustomMenuInterface.DrawTable = false;
					}
					else
					{
						gCustomMenuInterface.DrawTable = true;
					}
		}
		else if(gInterface.m_bCashShopOpen)
		{
			gInterface.m_bCashShopOpen = false;
			
			if(g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
			{
				if(gObjUser.InSafeZone() && !gInterface.CheckWindow(Shop))
				{
					g_DonateShop.CG_CashSend();
				}
			}
			else
			{
				_asm
				{
					MOV InterfaceBuffer,  0x00811D6F
					JMP InterfaceBuffer
				}
			}
		}
	}
	else
	{
		if(gObjUser.InSafeZone() && !gInterface.CheckWindow(Shop))
		{
			g_DonateShop.CG_CashSend();
		}
	}

	_asm
	{
		MOV InterfaceBuffer,  0x00811F40
		JMP InterfaceBuffer
	}
}

Naked(_007D3C16)
{
	/*if(g_ExLicense.CheckUser(eExUB::Escalate))
	{
		if(gObjUser.InSafeZone() && !gInterface.CheckWindow(Shop))
		{
			g_DonateShop.CG_CashSend();
		}

		_asm
		{
			MOV InterfaceBuffer,  0x007D3DF5
			JMP InterfaceBuffer
		}
	}
	else */if( g_ExLicense.m_ExMenuV2 || g_ExLicense.m_Achievements )
	{
		if(gCustomMenuInterface.DrawTable)
					{
						gCustomMenuInterface.DrawTable = false;
					}
					else
					{
						gCustomMenuInterface.DrawTable = true;
					}
	}
	else 
	{
		if(gObjUser.InSafeZone() && !gInterface.CheckWindow(Shop))
		{
			g_DonateShop.CG_CashSend();
		}
	}

	_asm
	{
		MOV InterfaceBuffer,  0x007D3DF5
		JMP InterfaceBuffer
	}
}

void __declspec(naked) GuildAllieReqv()
{
	static DWORD __jmpTRUE = 0x0078F4AD;
	static DWORD __jmpFALSE = 0x0078F42A;
	static DWORD _UserGuildStatus = 0;

	_asm
	{
		MOV _UserGuildStatus, ECX
	}

	if(_UserGuildStatus == 0x80 || _UserGuildStatus == 0x40)
	{
		_asm
		{
			JMP __jmpTRUE;
		}
	}

	_asm
	{
		JMP __jmpFALSE;
	}
}

CExLicense::CExLicense()
{
	//VMBEGIN
	this->Init();
	//VMEND
}
// ----------------------------------------------------------------------------------------------

CExLicense::~CExLicense()
{
}
// ----------------------------------------------------------------------------------------------

void CExLicense::Init()
{
	//VMBEGIN
	this->Enable = true;

	this->TEXTXoR[0] = 0x03;
	this->TEXTXoR[1] = 0x05;
	this->TEXTXoR[2] = 0x08;

	this->URLXoR[0] = 0xA9;
	this->URLXoR[1] = 0xB3;
	this->URLXoR[2] = 0x18;

	this->ActiveUser = -1;

	this->m_Achievements = false;
	this->m_ExMenuV2 = false;
	//VMEND
}
// ----------------------------------------------------------------------------------------------

void CExLicense::Load()
{
	//VMBEGIN
	this->Init();
	//VMEND

}
// ----------------------------------------------------------------------------------------------

void CExLicense::GCLicenseUser(PMSG_LICENSE_DATA* aRecv)
{
	//VMBEGIN
	this->ActiveUser = aRecv->LicenseUser;
	this->user.Rage = aRecv->base.Rage;
	this->user.WinQuest = aRecv->base.WinQuest;
	this->user.BloodHound = aRecv->base.BloodHound;
 	this->user.MonsterQuest = aRecv->base.MonsterQuest;
	this->user.TvTEvent = aRecv->base.TvTEvent;
	this->user.GrandHero = aRecv->base.GrandHero;
	this->user.PartySystem = aRecv->base.PartySystem;
	this->user.Brotherhood = aRecv->base.Brotherhood;
	this->user.PartySearch = aRecv->base.PartySearch;
	this->user.ChatLog = aRecv->base.ChatLog;
	this->user.GM_Manager = aRecv->base.GM_Manager;
	this->user.PerosnalStoreEx = aRecv->base.PerosnalStoreEx;
	this->user.PandoraEvent = aRecv->base.PandoraEvent;
	this->user.AntiCheatPlus = aRecv->base.AntiCheatPlus;
	this->user.SpotReturn = aRecv->base.SpotReturn;
	this->user.ComboCustom = aRecv->base.ComboCustom;
	this->user.NpcBuffer = aRecv->base.NpcBuffer;
	this->user.BMQuest = aRecv->base.BMQuest;
	this->user.LoraBattle = aRecv->base.LoraBattle;
	this->user.Smithy = aRecv->base.Smithy;
	this->user.Monster = aRecv->base.Monster;
	this->user.ItemSmokeEffect = aRecv->base.ItemSmokeEffect;
	this->user.GrandDinamicExp = aRecv->base.GrandDinamicExp;
	this->user.PartySave = aRecv->base.PartySave;
	//this->user.DisableMasterTree = aRecv->base.DisableMasterTree;
	this->user.OfflineMode = aRecv->base.OfflineMode;
	this->user.bAchievements = aRecv->base.bAchievements;
	this->user.PremiumEx = aRecv->base.PremiumEx;
	this->user.AccSecurity = aRecv->base.AccSecurity;
	this->user.CraftQuestSystem = aRecv->base.CraftQuestSystem;
	this->user.PickUpItemInfo = aRecv->base.PickUpItemInfo;
	this->user.ReferralSystem = aRecv->base.ReferralSystem;
	this->config.MaxPartyUser = aRecv->config.MaxPartyUser;
	this->config.PersonalEnable = aRecv->config.PersonalEnable;
	this->config.PersonalBonus = aRecv->config.PersonalBonus;
	this->config.PersonalCredit = aRecv->config.PersonalCredit;

	gConsole.Output(cYELLOW, "ActiveUser = %d", this->ActiveUser);
	gConsole.Output(cYELLOW, "Rage = %s", this->user.Rage ? "true" : "false" );
	gConsole.Output(cYELLOW, "WinQuest = %s", this->user.WinQuest ? "true" : "false" );
	gConsole.Output(cYELLOW, "BloodHound = %s", this->user.BloodHound ? "true" : "false" );
	gConsole.Output(cYELLOW, "MonsterQuest = %s", this->user.MonsterQuest ? "true" : "false" );
	gConsole.Output(cYELLOW, "TvTEvent = %s", this->user.TvTEvent ? "true" : "false" );
	gConsole.Output(cYELLOW, "GrandHero = %s", this->user.GrandHero ? "true" : "false" );
	gConsole.Output(cYELLOW, "PartySystem = %s", this->user.PartySystem ? "true" : "false" );
	gConsole.Output(cYELLOW, "Brotherhood = %s", this->user.Brotherhood ? "true" : "false" );
	gConsole.Output(cYELLOW, "PartySearch = %s", this->user.PartySearch ? "true" : "false" );
	gConsole.Output(cYELLOW, "ChatLog = %s", this->user.ChatLog ? "true" : "false" );
	gConsole.Output(cYELLOW, "GM_Manager = %s", this->user.GM_Manager ? "true" : "false" );
	gConsole.Output(cYELLOW, "PerosnalStoreEx = %s", this->user.PerosnalStoreEx ? "true" : "false" );
	gConsole.Output(cYELLOW, "PandoraEvent = %s", this->user.PandoraEvent ? "true" : "false" );
	gConsole.Output(cYELLOW, "AntiCheatPlus = %s", this->user.AntiCheatPlus ? "true" : "false" );
	gConsole.Output(cYELLOW, "SpotReturn = %s", this->user.SpotReturn ? "true" : "false" );
	gConsole.Output(cYELLOW, "ComboCustom = %s", this->user.ComboCustom ? "true" : "false" );
	gConsole.Output(cYELLOW, "NpcBuffer = %s", this->user.NpcBuffer ? "true" : "false" );
	gConsole.Output(cYELLOW, "BMQuest = %s", this->user.BMQuest ? "true" : "false" );
	gConsole.Output(cYELLOW, "LoraBattle = %s", this->user.LoraBattle ? "true" : "false" );
	gConsole.Output(cYELLOW, "Smithy = %s", this->user.Smithy ? "true" : "false" );
	gConsole.Output(cYELLOW, "Monster = %s", this->user.Monster ? "true" : "false" );
	gConsole.Output(cYELLOW, "ItemSmokeEffect = %s", this->user.ItemSmokeEffect ? "true" : "false" );
	gConsole.Output(cYELLOW, "GrandDinamicExp = %s", this->user.GrandDinamicExp ? "true" : "false" );
	gConsole.Output(cYELLOW, "PartySave = %s", this->user.PartySave ? "true" : "false" );
	gConsole.Output(cYELLOW, "OfflineMode = %s", this->user.OfflineMode ? "true" : "false" );
	gConsole.Output(cYELLOW, "bAchievements = %s", this->user.bAchievements ? "true" : "false" );
	gConsole.Output(cYELLOW, "PremiumEx = %s", this->user.PremiumEx ? "true" : "false" );
	gConsole.Output(cYELLOW, "AccSecurity = %s", this->user.AccSecurity ? "true" : "false" );
	gConsole.Output(cYELLOW, "CraftQuestSystem = %s", this->user.CraftQuestSystem ? "true" : "false" );
	gConsole.Output(cYELLOW, "PickUpItemInfo = %s", this->user.PickUpItemInfo ? "true" : "false" );
	gConsole.Output(cYELLOW, "ReferralSystem = %s", this->user.ReferralSystem ? "true" : "false" );
	gConsole.Output(cYELLOW, "MaxPartyUser = %d", this->config.MaxPartyUser);
	gConsole.Output(cYELLOW, "PersonalEnable = %s", this->config.PersonalEnable ? "true" : "false" );
	gConsole.Output(cYELLOW, "PersonalBonus = %c", this->config.PersonalBonus);
	gConsole.Output(cYELLOW, "PersonalCredit = %c", this->config.PersonalCredit);

	this->CustomManager();
	//VMEND
}
// ----------------------------------------------------------------------------------------------

bool IsMasterClass(BYTE Class)
{
	return false;
}

void CExLicense::CustomManager()
{
	if(this->user.Monster)
	{ 
		gMonster.Load();
	}
	if(this->user.ItemSmokeEffect)
	{
		gItemSmokeEffect.Load();
	}
	if(this->user.MonsterQuest)
	{
		gMONSTER_QUEST_SYSTEM = true;
	}
	if(this->user.PartySystem)
	{
		gPARTY_SYSTEM = true;
	}
	if(this->user.PartySearch)
	{
		g_PartySearch.Active = true;
	}
	if(this->user.Smithy)
	{
		this->user.Smithy = true;
	}
	if(this->user.Rage)
	{
		gRAGESYSTEM = true;
	}
	if(this->user.WinQuest)
	{
		gWINQUEST = true;
	}
	if(this->user.PerosnalStoreEx && this->config.PersonalEnable)
	{
		g_PersonalShopEx.Load();
		g_PersonalShopEx.iPERSONAL_BONUS = this->config.PersonalBonus;
		g_PersonalShopEx.iPERSONAL_CREDIT = this->config.PersonalCredit;
	}

#if (CUSTOM_SMITHY == 1)
	g_Smithy.License = this->user.Smithy;
#endif

	this->m_Achievements = this->user.bAchievements;

	if(this->user.AccSecurity)
	{
		g_AccountSecurity.m_bEnable = true;
	}

	//Master Skill Button Disable
	if(this->user.DisableMasterTree)
	{
		SetRange((LPVOID)0x00784B77, 5, ASM::NOP);
		SetOp((LPVOID)0x00784F79, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0		//Master Button Disable
		SetOp((LPVOID)0x007D3916, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0		//Master A Key Disable
	}

	g_MaxPartyMember = this->config.MaxPartyUser;

	if( g_ExLicense.CheckUser(eExUB::SILVER1) ||
	    g_ExLicense.CheckUser(eExUB::SILVER2) )
	{
		gVisualFix.GCVisualInit();
		//SetRange((LPVOID)0x007D3C1C, 5, ASM::NOP);	
		//SetOp((LPVOID)0x007D3C1C, _007D3C16, ASM::JMP);
		////SetRange((LPVOID)0x00811D6F, 5, ASM::NOP);	
		////SetOp((LPVOID)0x00811D6F, _00811D69, ASM::JMP);
		//SetRange((LPVOID)0x00811D69, 6, ASM::NOP);	
		//SetOp((LPVOID)0x00811D69, _00811D69, ASM::JMP);
		SetRange((LPVOID)0x00811D89, 7, ASM::NOP);
		SetRange((LPVOID)0x00811EC5, 5, ASM::NOP);//
		g_AddPoints.Load();

		gChatExpanded.LoadChatEx();
	}

#if(CUSTOM_ADD_POINTS==TRUE)
	if( g_ExLicense.CheckUser(eExUB::Gredy) ||
		g_ExLicense.CheckUser(eExUB::Gredy2) || 
		g_ExLicense.CheckUser(eExUB::GredyLocal) )
	{
		g_AddPoints.Load();
		//SetRange((LPVOID)0x005528DE, 23, ASM::NOP);	//dark lord horse spotikaeca pt damaga reflecta
	}
#endif
	if(g_ExLicense.CheckUser(eExUB::Stone))
	{
		SetRange((LPVOID)0x005528D7, 2, ASM::NOP);	//ne kto ne spotikaeca ot damaga i reflecta

		//Credit Shop
		SetRange((LPVOID)0x007D3C1C, 5, ASM::NOP);	
		SetOp((LPVOID)0x007D3C1C, _007D3C16, ASM::JMP);
		SetRange((LPVOID)0x00811D6F, 5, ASM::NOP);	
		SetOp((LPVOID)0x00811D6F, _00811D69, ASM::JMP);
	}
	else if(g_ExLicense.CheckUser(eExUB::Stone) || g_ExLicense.CheckUser(eExUB::Almdar))
	{
		SetRange((LPVOID)0x005528D7, 2, ASM::NOP);	//ne sko ne spotikaeca ot damaga i reflecta
	}
	else if(g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
	{
		//Credit Shop
		SetRange((LPVOID)0x007D3C1C, 5, ASM::NOP);	
		SetOp((LPVOID)0x007D3C1C, _007D3C16, ASM::JMP);
		SetRange((LPVOID)0x00811D6F, 5, ASM::NOP);	
		SetOp((LPVOID)0x00811D6F, _00811D69, ASM::JMP);

		g_AddPoints.Load();

		#if(USER_BUFF_ICON_EX==TRUE)
		g_BuffIcon.Load();
		#endif
	}
	else if(g_ExLicense.CheckUser(eExUB::MU2Play))
	{
		g_AddPoints.Load();
	}
	else if(g_ExLicense.CheckUser(eExUB::EpicMU))
	{
		//-> Siege minimap fix
		SetRange((PVOID)0x006505FB, 4, ASM::NOP);
		//-> Fix BC Master Disable
		SetByte((LPVOID)(0x008742AC+3), 0x07);
		SetByte((LPVOID)(0x00874C04+6), 0x07);
		SetRange((LPVOID)(0x00874EBF), 5, ASM::NOP);
		//-> Fix DS Master Disable
		SetByte((LPVOID)(0x00877D8C+3), 0x06);
		SetByte((LPVOID)(0x00878754+6), 0x06);
		SetRange((LPVOID)(0x00878A0F), 5, ASM::NOP);
		SetRange((LPVOID)0x005F7AEA, 27, ASM::NOP);		//Fix Item Pol
		SetByte((LPVOID)(0x005CD192), 0xEB);			//Fix Inventory Pos
		SetRange((LPVOID)0x005528D7, 2, ASM::NOP);		//ne sko ne spotikaeca ot damaga i reflecta

		this->m_ExMenuV2 = true;

		g_AddPoints.Load();
	}

#if(THINNAKORN_MAC)
	g_AddPoints.Load();

	SetByte((LPVOID)(0x00405B7A+2), 0x91);	//Character delete 400 level
#endif

	if( g_ExLicense.CheckUser(eExUB::SILVER1) ||
	    g_ExLicense.CheckUser(eExUB::SILVER2) ||
		THINNAKORN_MAC == 1)
	{
		this->m_Achievements = true;
	}

	if( g_ExLicense.CheckUser(eExUB::DavitRazmadze) || g_ExLicense.CheckUser(eExUB::DavitRazmadze2) || g_ExLicense.CheckUser(eExUB::DavitRazmadze3) ||
		g_ExLicense.CheckUser(eExUB::MedoniAndrei))
	{
		this->m_ExMenuV2 = true;
	}

	if(g_ExLicense.CheckUser(eExUB::Escalate))
	{
		g_AddPoints.Load();

		//SetRange((LPVOID)0x007D3C1C, 5, ASM::NOP);	
		//SetOp((LPVOID)0x007D3C1C, _007D3C16, ASM::JMP);
		//SetRange((LPVOID)0x00811D69, 6, ASM::NOP);	
		//SetOp((LPVOID)0x00811D69, _00811D69, ASM::JMP);
	}

	if(g_ExLicense.CheckUser(eExUB::eternalmu))
	{
		g_AddPoints.Load();
	}

#if(FIX_AGM_REQVALLIANCE==TRUE)
	if(g_ExLicense.CheckUser(eExUB::Gredy)		|| 
	   g_ExLicense.CheckUser(eExUB::Gredy2)		|| 
	   g_ExLicense.CheckUser(eExUB::GredyLocal) || 
	   g_ExLicense.CheckUser(eExUB::mu4you)		||
	   g_ExLicense.CheckUser(eExUB::NSGames))
	{
		SetOp((LPVOID)0x0078F41E, (LPVOID)GuildAllieReqv, ASM::JMP);	//  CALL 005878E0
		SetRange((LPVOID)0x007E519C, 6, ASM::NOP);	// -> Disable Check ItemAddOption Wings
		//SetRange((LPVOID)0x006D80F0, 2, ASM::NOP);	// -> Fix File Scream Target Block
		//SetByte((LPVOID)(0x006F0B06 + 2), 0xE0);	// -> Fix File Scream Target Block
		//SetByte((LPVOID)(0x006F0B06 + 3), 0x7B);	// -> Fix File Scream Target Block
		SetByte((LPVOID)(0x006F0B51 + 0), 0xE9);
		SetByte((LPVOID)(0x006F0B51 + 1), 0xB4);
		SetByte((LPVOID)(0x006F0B51 + 2), 0x02);
		SetByte((LPVOID)(0x006F0B51 + 3), 0x00);
		SetByte((LPVOID)(0x006F0B51 + 4), 0x00);

		gChatExpanded.LoadChatEx();

		SetByte((LPVOID)0x005C8B42, 0xEB);	//Rena trade
		SetByte((LPVOID)0x005C8881, 0xEB);	//Rena store

		gInterface.m_ActiveAutoHP = true;

#if(USER_BUFF_ICON_EX==TRUE)
		g_BuffIcon.Load();
#endif	
	}
#endif

	if(g_ExLicense.CheckUser(eExUB::RevoMU))
	{
		this->m_ExMenuV2 = true;
		g_AddPoints.Load();
		SetRange((LPVOID)0x005528D7, 2, ASM::NOP);	//ne kto ne spotikaeca ot damaga i reflecta
		SetRange((PVOID)0x006505FB, 4, ASM::NOP);	//-> Siege minimap fix

		gChatExpanded.LoadChatEx();
	}
#if(ENABLE_CHATCOLOR)
	//gChatExpanded.LoadChatEx();
#endif
	// ----
	#if(ENABLE_ITEMSETOPTION)
	if( g_ExLicense.CheckUser(eExUB::Gredy) || 
		g_ExLicense.CheckUser(eExUB::Gredy2) || 
		g_ExLicense.CheckUser(eExUB::GredyLocal) ||
		g_ExLicense.CheckUser(eExUB::masonX) || g_ExLicense.CheckUser(eExUB::masonX2)||
		g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ulasevich2) ||
		g_ExLicense.CheckUser(eExUB::Escalate) || g_ExLicense.CheckUser(eExUB::mu4you) ||
		g_ExLicense.CheckUser(eExUB::eternalmu) || g_ExLicense.CheckUser(eExUB::NSGames))
	{
		g_ItemSetOption.Load();
	}
	#endif
	// ----
	if(g_ExLicense.CheckUser(eExUB::masonX) || g_ExLicense.CheckUser(eExUB::masonX2))
	{
		g_AddPoints.Load();
	}
	// ----
	if(g_ExLicense.CheckUser(eExUB::GloryMU))
	{
		//this->m_ExMenuV2 = true;

		//SetRange((LPVOID)0x005F7AEA, 27, ASM::NOP);		//Fix Item Pol
		//SetByte((LPVOID)(0x005CD192), 0xEB);		 	//Fix Inventory Pos

		SetRange((LPVOID)0x005528D7, 2, ASM::NOP);		//ne kto ne spotikaeca ot damaga i reflecta	
		SetRange((PVOID)0x006505FB, 4, ASM::NOP);		//-> Siege minimap fix		

		g_AddPoints.Load();
		gChatExpanded.LoadChatEx();
		g_ItemSetOption.Load();
		#if(USER_BUFF_ICON_EX==TRUE)
		g_BuffIcon.Load();
		#endif

		//this->DisableMasterEvent();
	}
	// ----
	if(g_ExLicense.CheckUser(eExUB::ArcMu))
	{
		g_AddPoints.Load();
		#if(USER_BUFF_ICON_EX==TRUE)
		g_BuffIcon.Load();
		#endif
	}

	if(g_ExLicense.CheckUser(eExUB::MedoniAndrei))
	{
		g_AddPoints.Load();
	}

	if(g_ExLicense.CheckUser(eExUB::mu4you))
	{
		g_AddPoints.Load();
		#if(USER_BUFF_ICON_EX==TRUE)
		g_BuffIcon.Load();
		#endif
		gChatExpanded.LoadChatEx();

		SetRange((LPVOID)0x0095DE51, 2, ASM::NOP);	//MUHelper Inventory 1
		SetByte((LPVOID)(0x0095CE90), 0xEB);		//MUHelper Inventory 2

		SetRange((PVOID)0x006505FB, 4, ASM::NOP);		//-> Siege minimap fix	

		gVisualFix.GCVisualInit();
	}

	if(g_ExLicense.CheckUser(eExUB::eternalmu))
	{
		#if(USER_BUFF_ICON_EX==TRUE)
		g_BuffIcon.Load();
		#endif
		#if(DEV_EXMENU_V3)
		g_ExMenuV3.Load(EXMENU_NUMBER::eVERSION_ET);
		#endif
	}

	if(g_ExLicense.CheckUser(eExUB::WarBorn))
	{
		#if(USER_BUFF_ICON_EX==TRUE)
		g_BuffIcon.Load();
		#endif

	}

	//if(g_ExLicense.CheckUser(eExUB::NSGames))
	//{
		//g_AddPoints.Load();
		//#if(USER_BUFF_ICON_EX==TRUE)
		//g_BuffIcon.Load();
		//#endif
		gChatExpanded.LoadChatEx();

		SetRange((LPVOID)0x0095DE51, 2, ASM::NOP);	//MUHelper Inventory 1
		SetByte((LPVOID)(0x0095CE90), 0xEB);		//MUHelper Inventory 2

		SetRange((PVOID)0x006505FB, 4, ASM::NOP);		//-> Siege minimap fix	

		gVisualFix.GCVisualInit();

		#if(DEV_EXMENU_V3)
		g_ExMenuV3.Load(EXMENU_NUMBER::eVERSION_NS);
		#endif

		#if(DEV_STATS_ADVANCE)
		g_StatsAdvance.Load();
		#endif

		//char szSerial[17];
		//memset(szSerial, 0, sizeof(szSerial));
		//sprintf(szSerial, "01332jcEX48mxL3b");
		//WriteMemory((PDWORD)SERIAL_MAIN, szSerial, sizeof(szSerial));
	//}

#if(CUSTOM_POSTITEM)
	gInterface.LoadItemPost();
#endif

#if(LICENSE_MUEVIL)
	SetRange((LPVOID)0x0095DE51, 2, ASM::NOP);	//MUHelper Inventory 1
	SetByte((LPVOID)(0x0095CE90), 0xEB);		//MUHelper Inventory 2
#endif

	if( g_ExLicense.m_ExMenuV2 || g_ExLicense.m_Achievements )
	{
		#if(DEV_EXMENU_V3)
		if(!g_ExMenuV3.m_Enable)
		{
			SetRange((LPVOID)0x007D3C1C, 5, ASM::NOP);	
			SetOp((LPVOID)0x007D3C1C, _007D3C16, ASM::JMP);
			SetRange((LPVOID)0x00811D69, 6, ASM::NOP);	
			SetOp((LPVOID)0x00811D69, _00811D69, ASM::JMP);
		}
		#endif
	}

	// ------------------------------------
	if(g_ExLicense.CheckUser(eExUB::Local))
	{
		g_AddPoints.Load();
		#if(USER_BUFF_ICON_EX==TRUE)
		g_BuffIcon.Load();
		#endif
		gChatExpanded.LoadChatEx();
		SetRange((LPVOID)0x0095DE51, 2, ASM::NOP);	//MUHelper Inventory 1
		SetByte((LPVOID)(0x0095CE90), 0xEB);		//MUHelper Inventory 2
		SetRange((PVOID)0x006505FB, 4, ASM::NOP);	//-> Siege minimap fix	
		gVisualFix.GCVisualInit();
		#if(DEV_STATS_ADVANCE)
		g_StatsAdvance.Load();
		#endif
	}
	// ------------------------------------
}
// ----------------------------------------------------------------------------------------------

bool CExLicense::CheckUser(int NeedUser)
{
	//VMBEGIN
	if(this->ActiveUser == NeedUser)
	{
		return true;
	}
	return false;
	//VMEND
}
// ----------------------------------------------------------------------------------------------

char* CExLicense::GetDecText(char* EncodeChar)
{
	//VMBEGIN
	int len = strlen(EncodeChar);	
	char* Line = new char[len+1];
	for(int i = 0; i < len; i++)
	{
		Line[i] = char(EncodeChar[i] ^ this->TEXTXoR[i % 3]);
	}
	Line[len] = 0;
	return Line;
	//VMEND
}
// ----------------------------------------------------------------------------------------------

void CExLicense::GCAttackEnable(PMSG_GC_ATTACK* lpMsg)
{

}

void CExLicense::GCAttackDisable()
{

}

void CExLicense::GC_UserConfigRecv(PMSG_USERCONFIG * lpMsg)
{
	gInterface.m_ActiveAutoHP = false;
	gInterface.m_AutoHP = false;

	memcpy(&g_ExLicense.m_EvoConfig, &lpMsg->EvoConfig, sizeof(g_ExLicense.m_EvoConfig));

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))
	{
		gInterface.m_ActiveAutoHP = g_ExLicense.m_EvoConfig.HPAutoClicker;
	}
}

void CExLicense::DisableMasterEvent()
{
	//-> Fix BC Master Disable
	SetByte((LPVOID)(0x008742AC+3), 0x07);
	SetByte((LPVOID)(0x00874C04+6), 0x07);
	SetRange((LPVOID)(0x00874EBF), 5, ASM::NOP);
	//-> Fix DS Master Disable
	SetByte((LPVOID)(0x00877D8C+3), 0x06);
	SetByte((LPVOID)(0x00878754+6), 0x06);
	SetRange((LPVOID)(0x00878A0F), 5, ASM::NOP);

	SetOp((LPVOID)0x0063DDF2, (LPVOID)IsMasterClass, ASM::CALL);//
	SetOp((LPVOID)0x0063DF89, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0063E5F2, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0063EA4C, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0064A79A, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0064A85F, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0064AB3D, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0064AC02, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0064CA0C, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	
	SetOp((LPVOID)0x0064CDE9, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0064CF5F, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x00651674, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x00656E03, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0077EFD0, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0077F9A9, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0077FBC8, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x00782C5A, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x00783032, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	
	SetOp((LPVOID)0x00784F79, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0		//Master Button Disable
	SetOp((LPVOID)0x007D3916, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0		//Master A Key Disable
	SetOp((LPVOID)0x007E4B19, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x007E4B8F, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0080F8D9, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0

	SetOp((LPVOID)0x00810019, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x008102E9, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x008105CB, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0081064B, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x00869213, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0

	SetOp((LPVOID)0x0087455B, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0087862E, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x00878661, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0095DFAF, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0095E090, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x0095E1F0, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x00968450, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x009684A6, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
	SetOp((LPVOID)0x009684EF, (LPVOID)IsMasterClass, ASM::CALL);//  CALL 005878E0
}

#endif
