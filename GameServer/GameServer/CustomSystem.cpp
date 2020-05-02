#include "stdafx.h"
#include "CustomSystem.h"
#include "logproc.h"
#include "GameMain.h"

CCustomSystem g_CustomSystem;

CCustomSystem::CCustomSystem(void)
{
}


CCustomSystem::~CCustomSystem(void)
{
}

void CCustomSystem::Init()
{
	m_bRage = false;
	m_bWinQuest = false;
	m_bBloodHound = false;
	m_bMonsterQuest = false;
	m_bTvTEvent = false;	
	m_bGrandHero = false;
	m_bPartySystem = false;
	m_bBrotherhood = false;
	m_bPartySearch = false;
	m_bChatLog = false;
	m_bGM_Manager = false;
	m_bPerosnalStoreEx = false;
	m_bPandoraEvent = false;
	m_bAntiCheatPlus = false;
	m_bSpotReturn = false;
	m_bComboCustom = false;
	m_bNpcBuffer = false;
	m_bBMQuest = false;
	m_bLoraBattle = false;
	m_bSmithy = false;
	m_bMonster = false;
	m_bItemSmokeEffect = false;
	m_bGrandDinamicExp = false;
	m_bPartySave = false;
	m_bDisableMasterTree = false;
	m_bOfflineMode = false;
	m_bMarriage = false;
	m_bMonsterAttackLife = false;
	m_bbRankItem = false;
	m_bRestoreOffMode = false;
	m_bMapQuest = false;
	m_bbTeamVsTeam2 = false;
	m_bbAchievements = false;
	m_bPremiumEx = false;
	m_bAccSecurity = false;
	m_bCraftQuestSystem = false;
	m_bPickUpItemInfo = false;
	m_bReferralSystem = false;
	m_b3DCamera = false;
	m_bJewelBank = false;
	m_bDungeonSiege = false;

	m_bMUHelperOffline = false;
}

void CCustomSystem::Load()
{
	Init();

	m_bRage = (bool) GetPrivateProfileInt("CustomSystem", "Rage", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bWinQuest = (bool) GetPrivateProfileInt("CustomSystem", "WinQuest", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bBloodHound = (bool) GetPrivateProfileInt("CustomSystem", "BloodHound", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bMonsterQuest = (bool) GetPrivateProfileInt("CustomSystem", "MonsterQuest", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bTvTEvent = (bool) GetPrivateProfileInt("CustomSystem", "TvTEvent", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bGrandHero = (bool) GetPrivateProfileInt("CustomSystem", "GrandHero", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bPartySystem = (bool) GetPrivateProfileInt("CustomSystem", "PartySystem", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bBrotherhood = (bool) GetPrivateProfileInt("CustomSystem", "Brotherhood", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bPartySearch = (bool) GetPrivateProfileInt("CustomSystem", "PartySearch", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bChatLog = (bool) GetPrivateProfileInt("CustomSystem", "ChatLog", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bGM_Manager = (bool) GetPrivateProfileInt("CustomSystem", "GM_Manager", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bPerosnalStoreEx = (bool) GetPrivateProfileInt("CustomSystem", "PerosnalStoreEx", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bPandoraEvent = (bool) GetPrivateProfileInt("CustomSystem", "PandoraEvent", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bAntiCheatPlus = (bool) GetPrivateProfileInt("CustomSystem", "AntiCheatPlus", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bSpotReturn = (bool) GetPrivateProfileInt("CustomSystem", "SpotReturn", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bComboCustom = (bool) GetPrivateProfileInt("CustomSystem", "ComboCustom", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bNpcBuffer = (bool) GetPrivateProfileInt("CustomSystem", "NpcBuffer", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bBMQuest = (bool) GetPrivateProfileInt("CustomSystem", "BMQuest", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bLoraBattle = (bool) GetPrivateProfileInt("CustomSystem", "LoraBattle", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bSmithy = (bool) GetPrivateProfileInt("CustomSystem", "Smithy", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bMonster = (bool) GetPrivateProfileInt("CustomSystem", "Monster", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bItemSmokeEffect = (bool) GetPrivateProfileInt("CustomSystem", "ItemSmokeEffect", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bGrandDinamicExp = (bool) GetPrivateProfileInt("CustomSystem", "GrandDinamicExp", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bPartySave = (bool) GetPrivateProfileInt("CustomSystem", "PartySave", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bDisableMasterTree = (bool) GetPrivateProfileInt("CustomSystem", "DisableMasterTree", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bOfflineMode = (bool) GetPrivateProfileInt("CustomSystem", "OfflineMode", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bMarriage = (bool) GetPrivateProfileInt("CustomSystem", "Marriage", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bMonsterAttackLife = (bool) GetPrivateProfileInt("CustomSystem", "MonsterAttackLife", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bbRankItem = (bool) GetPrivateProfileInt("CustomSystem", "bRankItem", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bRestoreOffMode = (bool) GetPrivateProfileInt("CustomSystem", "RestoreOffMode", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bMapQuest = (bool) GetPrivateProfileInt("CustomSystem", "MapQuest", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bbTeamVsTeam2 = (bool) GetPrivateProfileInt("CustomSystem", "bTeamVsTeam2", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bbAchievements = (bool) GetPrivateProfileInt("CustomSystem", "bAchievements", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bPremiumEx = (bool) GetPrivateProfileInt("CustomSystem", "PremiumEx", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bAccSecurity = (bool) GetPrivateProfileInt("CustomSystem", "AccSecurity", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bCraftQuestSystem = (bool) GetPrivateProfileInt("CustomSystem", "CraftQuestSystem", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bPickUpItemInfo = (bool) GetPrivateProfileInt("CustomSystem", "PickUpItemInfo", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bReferralSystem = (bool) GetPrivateProfileInt("CustomSystem", "ReferralSystem", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bGuildBank = (bool) GetPrivateProfileInt("CustomSystem", "GuildBank", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bStatsAdvance = (bool) GetPrivateProfileInt("CustomSystem", "StatsAdvance", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_b3DCamera = (bool) GetPrivateProfileInt("CustomSystem", "3DCamera", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bJewelBank = (bool) GetPrivateProfileInt("CustomSystem", "JewelBank", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
	m_bDungeonSiege = (bool)GetPrivateProfileInt("CustomSystem", "DungeonSiege", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));

	m_bMUHelperOffline = (bool)GetPrivateProfileInt("CustomSystem", "MUHelperOffline", 0, gDirPath.GetNewPath("Custom\\CustomSystem.ini"));
}