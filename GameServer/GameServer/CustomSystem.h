#pragma once

class CCustomSystem
{
public:
	CCustomSystem(void);
	virtual ~CCustomSystem(void);

public:
	void Init();
	void Load();

	bool IsRage(){return m_bRage;}
	bool IsWinQuest(){return m_bWinQuest;}
	bool IsBloodHound(){return m_bBloodHound;}
	bool IsMonsterQuest(){return m_bMonsterQuest;}
	bool IsTvTEvent(){return m_bTvTEvent;}
	bool IsGrandHero(){return m_bGrandHero;}
	bool IsPartySystem(){return m_bPartySystem;}
	bool IsBrotherhood(){return m_bBrotherhood;}
	bool IsPartySearch(){return m_bPartySearch;}
	bool IsChatLog(){return m_bChatLog;}
	bool IsGM_Manager(){return m_bGM_Manager;}
	bool IsPerosnalStoreEx(){return m_bPerosnalStoreEx;}
	bool IsPandoraEvent(){return m_bPandoraEvent;}
	bool IsAntiCheatPlus(){return m_bAntiCheatPlus;}
	bool IsSpotReturn(){return m_bSpotReturn;}
	bool IsComboCustom(){return m_bComboCustom;}
	bool IsNpcBuffer(){return m_bNpcBuffer;}
	bool IsBMQuest(){return m_bBMQuest;}
	bool IsLoraBattle(){return m_bLoraBattle;}
	bool IsSmithy(){return m_bSmithy;}
	bool IsMonster(){return m_bMonster;}
	bool IsItemSmokeEffect(){return m_bItemSmokeEffect;}
	bool IsGrandDinamicExp(){return m_bGrandDinamicExp;}
	bool IsPartySave(){return m_bPartySave;}
	bool IsDisableMasterTree(){return m_bDisableMasterTree;}
	bool IsOfflineMode(){return m_bOfflineMode;}
	bool IsMarriage(){return m_bMarriage;}
	bool IsMonsterAttackLife(){return m_bMonsterAttackLife;}
	bool IsbRankItem(){return m_bbRankItem;}
	bool IsRestoreOffMode(){return m_bRestoreOffMode;}
	bool IsMapQuest(){return m_bMapQuest;}
	bool IsbTeamVsTeam2(){return m_bbTeamVsTeam2;}
	bool IsbAchievements(){return m_bbAchievements;}
	bool IsPremiumEx(){return m_bPremiumEx;}
	bool IsAccSecurity(){return m_bAccSecurity;}
	bool IsCraftQuestSystem(){return m_bCraftQuestSystem;}
	bool IsPickUpItemInfo(){return m_bPickUpItemInfo;}
	bool IsReferralSystem(){return m_bReferralSystem;}
	bool IsGuildBank(){return m_bGuildBank;}

private:
	bool m_bRage;
	bool m_bWinQuest;
	bool m_bBloodHound;
	bool m_bMonsterQuest;
	bool m_bTvTEvent;	
	bool m_bGrandHero;
	bool m_bPartySystem;
	bool m_bBrotherhood;
	bool m_bPartySearch;
	bool m_bChatLog;
	bool m_bGM_Manager;
	bool m_bPerosnalStoreEx;
	bool m_bPandoraEvent;
	bool m_bAntiCheatPlus;
	bool m_bSpotReturn;
	bool m_bComboCustom;
	bool m_bNpcBuffer;
	bool m_bBMQuest;
	bool m_bLoraBattle;
	bool m_bSmithy;
	bool m_bMonster;
	bool m_bItemSmokeEffect;
	bool m_bGrandDinamicExp;
	bool m_bPartySave;
	bool m_bDisableMasterTree;
	bool m_bOfflineMode;
	bool m_bMarriage;
	bool m_bMonsterAttackLife;
	bool m_bbRankItem;
	bool m_bRestoreOffMode;
	bool m_bMapQuest;
	bool m_bbTeamVsTeam2;
	bool m_bbAchievements;
	bool m_bPremiumEx;
	bool m_bAccSecurity;
	bool m_bCraftQuestSystem;
	bool m_bPickUpItemInfo;
	bool m_bReferralSystem;

	bool m_bGuildBank;
};

extern CCustomSystem g_CustomSystem;