#ifndef CONFIGS_H
#define CONFIGS_H

#define ExCustom_DIR "..\\Data\\ExData\\ExCustom.ini"

#define CommonServer_DIR "..\\Data\\ExData\\Common.ini"
#define Skills_DIR	"..\\Data\\ExData\\Skills.ini"
#define Character_DIR "..\\Data\\ExData\\Character.ini"
#define Commands_DIR "..\\Data\\ExData\\Commands.ini"
#define Events_DIR	"..\\Data\\ExData\\Events.ini"
//#define Reset_DIR "..\\Data\\ExData\\Reset.ini"

#define Pets_DIR "..\\Data\\ExData\\Pets.ini"
#define PVP_DIR	"..\\Data\\ExData\\PvPSystem.ini"
#define GoldenDrop_DIR "..\\Data\\ExData\\Events\\GoldenInvasionDrop.ini"
#define PlayerConnect_DIR "..\\Data\\ExData\\PlayerConnect.ini"

#ifdef _MESSAGE_CONFIG_
#define MessageConfig_DIR "..\\Data\\ExData\\MessageConfig.ini"
#endif

#ifdef PRIDEMU_CONFIG
#define PrideMuConfig_DIR "..\\Data\\ExData\\PrideMuConfig.ini"
#endif
#ifdef DRYNEA_LIST_CUSTOM
#define DryneaMuConfig_DIR "..\\Data\\ExData\\dryneaConfig.ini"
#endif
#ifdef LVL_UP_POINTS
#define ADD_LVL_POINTS_DIR "..\\Data\\ExData\\AddPointLvl.ini"
#endif

#define MAPDIE_PATH		"..\\Data\\ExData\\MapDie.ini"
#define MAPSTART_PATH	"..\\Data\\ExData\\MapStart.ini"
#define NEWBUFF_PATH	"..\\Data\\ExData\\NewBuff.ini"

struct SEVOMU_CONFIG
{
	int iMapTeleport;
};

class cExConfigs
{
public:
#ifdef EX_RELOAD_RAGE_SILVER
	void LoadConfigs(bool);
#else
	void LoadConfigs();
#endif
	//~~~~~~~~~~~~~~
	//ExCustom
	//~~~~~~~~~~~~~~
	struct sExCustom
	{
		int SwitchChar;
		int HelperClickerLevel;
		bool AutoParty;
		BYTE Top100;
		BYTE MoveTargetPosEffect;
		BYTE ClientAntiCheat;
		BYTE EnableHPBar;
		short CreateMGLevel;
		short CreateDLLevel;
		short CreateSUMLevel;
		short CreateMONKLevel;
		BYTE DLReflect;
		bool MasterSkills;
		DWORD DivFireScreamSpeed;
		bool PostItem;

	}ExCustom;
	//ExConfig.ExCustom.CreateMGLevel
	//~~~~~~~~~~~~~~
	//CommonServer
	//~~~~~~~~~~~~~~
	struct sCommonServer
	{

		int EnableCheckSum;
		int Ex_PersonalID;
		int DeleteLogs;

		//int Ex_LifeRate;
		//int Ex_SoulRate;
		//int Ex_SoulRateLuck;

		int ExMixNormal10SuccessRate;
		int ExMix380AncExc10SuccessRate;
		int ExMixSocket10SuccessRate;
		int ExMixNormal11SuccessRate;
		int ExMix380AncExc11SuccessRate;
		int ExMixSocket11SuccessRate;
		int ExMixNormal12SuccessRate;
		int ExMix380AncExc12SuccessRate;
		int ExMixSocket12SuccessRate;
		int ExMixNormal13SuccessRate;
		int ExMix380AncExc13SuccessRate;
		int ExMixSocket13SuccessRate;
		//Season 5 +15 Items
		int ExMixNormal14SuccessRate;
		int ExMix380AncExc14SuccessRate;
		int ExMixSocket14SuccessRate;
		int ExMixNormal15SuccessRate;
		int ExMix380AncExc15SuccessRate;
		int ExMixSocket15SuccessRate;

		int ExMixLuckOptRateAdd;
		int ExMixMaxSuccessRate;
		int ExWing2MaxSuccessRate;
		int ExDarkHorseMixSuccessRate;
		int ExDarkSpiritMixSuccessRate;
		int ExFeatherofCondorMixMaxPercent;
		int ExWingLv3MixMaxPercent;
		int ExDinorantMixRate;

		int Wing2_5MaxSuccessRate;
		int Wing4MaxSuccessRate;
		int Wing5MaxSuccessRate;

		int Ex_MasterDropZen;

		char GuardMessage[50];

		int KundunAncDrop;

		int	DisatanceObjViewe;

		bool MarlonQuestReset;
		int MaxDropZen;
		int ProcentDropZen;

		int CountItemDropSelupan;
		int CountItemDropKundun;
		int CountItemDropErohim;

#if(_NEW_PT_SYSTEM_)
		int RePartyEnable;
		int RePartyTime;
		int AutoSetLeader;
		int CommandSetLeader;
#endif
#if(_ARENA_ITEM_)
		int ArenaItem;
#endif

		bool ReConnect;

		int ExlDropRate;
		int PercentKillZen;

#if(CUSTOM_NOOBBUFF)
		bool bNoobBuffEnable;
		int iNoobBuffMaxReset;
		int m_NoobDamage;
		int m_NoobDefence;
#endif
#if(CUSTOM_POTIONTICK)
		int PotionDelay;
#endif

		int MarlonTeleport;
		int CheckOtherGuildLand;

	}CommonServer;
	//~~~~~~~~~~~~~~
	//Skills
	//~~~~~~~~~~~~~~
	struct sSkills
	{
		//int ExStartPowerHp;
		//int ExVitality;
		//int ExEnergy;
		//int ExMaxPowerHp;

		//int ExMaster_StartPowerHp;
		//int ExMaster_Vitality;
		//int ExMaster_Energy;
		//int ExMaster_MaxPowerHp;

		//int ExMSStartPower;
		//int ExMSAgility;
		//int ExMSEnergy;
		//int ExMSMaxPower;

		//int ExMaster_MSStartPower;
		//int ExMaster_MSAgility;
		//int ExMaster_MSEnergy;
		//int ExMaster_MSMaxPower;

		//int ExWizardryPowerMax;

		//int ExAttackEnergy;
		//int ExDefenceEnergy;

		//int NeedArrow;

		//int ExCriticalEnergy;
		//int ExCriticalCommand;
		//int ExCritEneTime;

		//int ExRefStartPower;
		//int ExRefEnergy;
		//int ExRefMaxPower;
		//int ExRefStartTime;
		//int ExRefEneTime;

		//int Ex_BerserkerPower;

		//int ExBerserkerStartTime;
		//int ExBerserkerEnergyTime;
		//int ExBerserkerMaxTime;
		//int ExBerserkerEneIncMana;
		//int ExBerserkerEneDecLife;

		//int Ex_BerserkerDex;

		//int Ex_WeaknessPower;
		//int Ex_InnovationPower;

		//int ExCSSKill;

		//int AttackByNPC;
		//int AttackByPlayer;

		//int PetAttackByNPC;
		//int PetAttackByPlayer;
		////Skills Level
		//int TwistingSlashLevel;
		//int RagefulBlowLevel;
		//int DeathStabLevel;
		//int ImpaleLevel;
		//int InnerStrengthLevel;
		//int PenetrationLevel;

	}Skills;
	//~~~~~~~~~~~~~~
	//Character
	//~~~~~~~~~~~~~~
	struct sCharacter
	{
		int NeedArrow;
		int CastleSiegeSkillEnable;
		int CastleAttackByNPC;
		int CastleAttackByPlayer;
		int PetCastleAttackByNPC;
		int PetCastleAttackByPlayer;
		int MaxStats;

		int CastleDamageByAlliance;

		bool bReflectToReflect;

#if(CUSTOM_CW_ALTERELFDMG)
		int CWElfAlterDMGPercent;;
#endif
		int ComboDamagePercent;
		bool SoulBarrierAttackManaDown;

		int ELFDamageMax_Bow_StrDexRight;
		int ELFDamageMin_Bow_StrDexRight;
		int ELFDamageMax_Bow_StrDexLeft;
		int ELFDamageMin_Bow_StrDexLeft;

		int ELFDamageMax_NoBow_StrRight;
		int ELFDamageMax_NoBow_DexRight;
		int ELFDamageMin_NoBow_StrRight;
		int ELFDamageMin_NoBow_DexRight;
		
		int ELFDamageMax_NoBow_StrLeft;
		int ELFDamageMax_NoBow_DexLeft;
		int ELFDamageMin_NoBow_StrLeft;
		int ELFDamageMin_NoBow_DexLeft;

		int ELFDamageMax_DexStrRight;
		int ELFDamageMin_DexStrRight;
		int ELFDamageMax_DexStrLeft;
		int	ELFDamageMin_DexStrLeft;
		//----------------------
		int DKDamageMax_StrRight;
		int DKDamageMin_StrRight;
		int DKDamageMax_StrLeft;
		int DKDamageMin_StrLeft;
		//----------------------
		int MGDamageMax_StrRight;
		int MGDamageMax_EneRight;
		int MGDamageMin_StrRight;
		int MGDamageMin_EneRight;

		int MGDamageMax_StrLeft;
		int MGDamageMax_EneLeft;
		int MGDamageMin_StrLeft;
		int MGDamageMin_EneLeft;

		//----------------------
		int SUMDamageMax_StrRight;
		int SUMDamageMin_StrRight;
		int SUMDamageMax_StrLeft;
		int SUMDamageMin_StrLeft;
		//----------------------
		int DWDamageMax_StrRight;
		int DWDamageMin_StrRight;
		int DWDamageMax_StrLeft;
		int DWDamageMin_StrLeft;
		//----------------------
		int DLDamageMax_StrRight;
		int DLDamageMax_EneRight;
		int DLDamageMin_StrRight;
		int DLDamageMin_EneRight;
		
		int DLDamageMax_StrLeft;
		int DLDamageMax_EneLeft;
		int DLDamageMin_StrLeft;
		int DLDamageMin_EneLeft;
		//----------------------
		int SUMMagicDamageMax;
		int SUMMagicDamageMin;
		//----------------------	
		int MGMagicDamageMax;
		int MGMagicDamageMin;
		//------
		int DWMagicDamageMax;
		int DWMagicDamageMin;	
		//------------------
		int ELFSuccessfulBlocking;
		int DLSuccessfulBlocking;
		int SUMSuccessfulBlocking;
		int DWSuccessfulBlocking;
		int DKSuccessfulBlocking;
		int MGSuccessfulBlocking;
		//--------------------
		int ELFDefense;
		int DKDefense;
		int DLDefense;
		int SUMDefense;
		int MGDefense;
		int DWDefense;

		int RFDamageMin_VitRight;
		int RFDamageMin_StrRight;
		int RFDamageMax_VitRight;
		int RFDamageMax_StrRight;

		int RFDamageMin_VitLeft;
		int RFDamageMin_StrLeft;
		int RFDamageMax_VitLeft;
		int RFDamageMax_StrLeft;

		int RFSuccessfulBlocking;

		int RFDefense;

		int DKSkillDMGPercentMax;
		int DLSkillDMGPercentMax;

#ifdef FIX_BERSERK_SUM
	int	BerserkAddMana;
#endif

	// ======
	int DKPvPAttackRateFact1;
	int DKPvPAttackRateFact2;
	int DKPvPAttackRateDiv;

	int DWPvPAttackRateFact1;
	int DWPvPAttackRateFact2;

	int EEPvPAttackRateFact1;
	int EEPvPAttackRateFact2;
	int EEPvPAttackRateDiv;

	int MGPvPAttackRateFact1;
	int MGPvPAttackRateFact2;
	int MGPvPAttackRateDiv;

	int DLPvPAttackRateFact1;
	int DLPvPAttackRateFact2;

	int SUPvPAttackRateFact1;
	int SUPvPAttackRateFact2;
	int SUPvPAttackRateDiv;

	int RFPvPAttackRateFact1;
	int RFPvPAttackRateFact2;
	int RFPvPAttackRateDiv;
	}Character;

	struct sCommands
	{
		//w_char CommandPost[100];	//Post

		char CommandPost[100];	//Post
		char CommandAddStr[100];
		char CommandAddAgi[100];
		char CommandAddVit[100];
		char CommandAddEne[100];
		char CommandAddCmd[100];
		char CommandPkClear[100];
		//char CommandReset[100];		// = "/reset";		//Reset
		//char CommandGrandReset[100]; //= "/grandreset";	//Grand Reset
		// command configs
		int PostLevel;
		int PostMoney;
		char PostPrist[100];
		int PostColor;
		int PostDelay;
		int PostServer;
		int OnlineColor;
		char AdminPostName[100];
		// add config
		int AddMoney;
		int AddLeveL;
		// pk clear config
		int Ex_PkClear_Enabled;
		int Ex_PkClearLevel;
		int Ex_PkClearMoney;
		int Ex_PKClearType;
#ifdef PK_CLEAR_TO_CREDITS
		int Ex_PkClearCredits;
#endif // PK_CLEAR_TO_CREDITS

		int PostPCPoint;
		int MoneyType;
		bool GensColorEnable;
		BYTE GensColorRed;
		BYTE GensColorGreen;
		BYTE GensColorBlue;
	}Command;

	struct sEvent
	{
		int Ex_IllusionTemplPlaerMin;
		int Ex_ItDropType;
		int Ex_ItDropID;
		int Ex_ItDropLevel;
		int Ex_ItDropSkill;
		int Ex_ItDropLuck;
		int Ex_ItDropOpt;
		int Ex_ItDropExcOpt;
		int Ex_ItDropAncOpt;
		
		int Ex_BCDropType;
		int Ex_BCDropID;
		int Ex_BCDropLevel;
		int Ex_BCDropSkill;
		int Ex_BCDropLuck;
		int Ex_BCDropOpt;
		int Ex_BCDropExcOpt;
		int Ex_BCDropAncOpt;
		int BCAllowPKPlayer;
#ifdef BC_LVL_DROP
#define BC_LVL 8
		//Configs Blood Castle
		int Ex_BCDropType_DRYNEA[BC_LVL];
		int Ex_BCDropID_DRYNEA[BC_LVL];
		int Ex_BCDropLevel_DRYNEA[BC_LVL];
		int Ex_BCDropSkill_DRYNEA[BC_LVL];
		int Ex_BCDropLuck_DRYNEA[BC_LVL];
		int Ex_BCDropOpt_DRYNEA[BC_LVL];
		int Ex_BCDropExcOpt_DRYNEA[BC_LVL];
		int Ex_BCDropAncOpt_DRYNEA[BC_LVL];
		int BCAllowPKPlayer_DRYNEA[BC_LVL];

#endif
		int Ex_CCMinPlayer;

		int DSParty3ExpPercent;
		int DSParty4ExpPercent;
		int DSParty5ExpPercent;
		int DSPartyExpPercentOther;
		int DSParty2ExpSetPercent;
		int DSParty3ExpSetPercent;
		int DSParty4ExpSetPercent;
		int DSParty5ExpSetPercent;
		int DSParty1ExpSetPercent;
		int DSAllowPKPlayer;

	}Event;

	//struct sReset
	//{
	//	int EnableResetSystem;
	//	int Maxres;
	//	int ZenForm;
	//	int NeedZen;
	//	int NeedLevel;
	//	int AddForm;
	//	int AddPointsDW;
	//	int AddPointsDK;
	//	int AddPointsELF;
	//	int AddPointsSUM;
	//	int AddPointsMG;
	//	int AddPointsDL;
	//	int AddPcPoint;
	//	int NeedEmptyInv;
	//}Reset;

	//struct sGrandReset
	//{
	//	int EnableGrandResetSystem;	
	//	int MaxGrandRes;
	//	int ZenForm;
	//	int NeedZen;
	//	int NeedRes;
	//	int NeedLevel;
	//	int AddForm;
	//	int AddPointsDW;
	//	int AddPointsDK;
	//	int AddPointsELF;
	//	int AddPointsSUM;
	//	int AddPointsMG;
	//	int AddPointsDL;
	//	int AddPcPoint;
	//	int NeedEmptyInv;
	//}GrandReset;

	struct sPets
	{
		int Ex_PandaRingZen;
		int Ex_PandaRingAttack;
		int Ex_PandaDef;
		int Ex_PandaExp;

		int RavenAttackDamageMinLvl;
		int RavenAttackDamageMaxLvl;
		int RavenAttackDamageMinCmd;
		int RavenAttackDamageMaxCmd;
		int RavenDurabilitySmall;

		int SkeletonPetExp;
		int SkeletonPetAndRingExp;

		int RedFenrirProcDamage;
		int RedFenrirProcAbsurd;
		int RedFenrirProcLife;
		int RedFenrirProcDurability;

		int BlueFenrirProcDamage;
		int BlueFenrirProcAbsurd;
		int BlueFenrirProcLife;
		int BlueFenrirProcDurability;

		int BlackFenrirProcDamage;
		int BlackFenrirProcAbsurd;
		int BlackFenrirProcLife;
		int BlackFenrirProcDurability;

		int GoldFenrirProcDamage;
		int GoldFenrirProcAbsurd;
		int GoldFenrirProcLife;
		int GoldFenrirProcDurability;

#if(CONFIG_PET_DURABILITY)
		int AngelDurability;
		int RudolfDurability;
		int SatanDurability;
		int DemonDurability;
		int GuardianDurability;
		int PandaDurability;
		int SkeletonDurability;
		int UnicornDurability;
		int UniriaDurability;
		int DinorantDurability;
		int RingPandaDurability;
		int RingSkeletonDurability;
#endif
	}Pet;

	struct sPvP
	{
		int ExPkPartySystem;
		int ExPkLimit;
		int DuelGate;
		int DuelLevel;
	}PvP;

	struct sGoldenDrop
	{
		int ItemType44;
		int ItemIndex44;
		int level44;

		int ItemType43;
		int ItemIndex43;
		int level43;

		int ItemType78;
		int ItemIndex78;
		int level78;

		int ItemType493;
		int ItemIndex493;
		int level493;

		int ItemType53;
		int ItemIndex53;
		int level53;

		int ItemType54;
		int ItemIndex54;
		int level54;

		int ItemType80;
		int ItemIndex80;
		int level80;

		int ItemType81;
		int ItemIndex81;
		int level81;

		int ItemType494;
		int ItemIndex494;
		int level494;

		int ItemType82;
		int ItemIndex82;
		int level82;

		int ItemType83;
		int ItemIndex83;
		int level83;

		int ItemType495;
		int ItemIndex495;
		int level495;

		int ItemType496;
		int ItemIndex496;
		int level496;

		int ItemType497;
		int ItemIndex497;
		int level497;

		int ItemType498;
		int ItemIndex498;
		int level498;

		int ItemType499;
		int ItemIndex499;
		int level499;

		int ItemType500;
		int ItemIndex500;
		int level500;

		int ItemType79;
		int ItemIndex79;
		int level1_79;
		int level2_79;
		int rate1_79;
		int rate2_79;
		int countitem79;

		int ItemType501;
		int ItemIndex501;
		int level1_501;
		int level2_501;
		int rate1_501;
		int rate2_501;
		int countitem501;

	}GoldenDrop;

	struct sPlayerConnect
	{
		int EnablePlayerConnectSystem;
		int ShowReset;
		int ShowGReset;
		int ShowOnline;
		int ShowNameAll;
		int ShowNameColor;
		int ShowGMAll;
		int ShowWcoinC;
		int ShowGP;
		int ShowExCredit;
	}PlayerConnect;

#ifdef _MESSAGE_CONFIG_
	struct sMessageConfig
	{
		char HappyHour[100];
		char DropEvent[100];
		char SearchEvent[100];
	}MessageConfig;
#endif
#ifdef _CONFLICT_
	struct sGmMap
	{
		int GmMap;
		int GmX;
		int GMY;
	
	}GmMap;
#endif

#ifdef PRIDEMU_CONFIG

	struct sPrideMu
	{
		int MasterMoney;
		int DiapasonMasterMoney;

		//Illusion Fenrir
		int AddLife;
		int AddMana;
		int AttackDamageMin;
		int AttackDamageMax;
		int MagicDamageMin;
		int MagicDamageMax;
		//Protect Fenrir
		int DecPercent;
		//Destroy Fenrir
		int IncPercent;
		int OffDecreaseDur;
		
		int ComboBase;// = (STR+AGI+ENE)/2
		int Fortitude;// = 12+VIT/300+ENE/60

		int LevelLifeSM;
		int VitalityToLifeSM;

		int LevelLifeDK;
		int VitalityToLifeDK;

		int LevelLifeELF;
		int VitalityToLifeELF;

		int LevelLifeMG;
		int VitalityToLifeMG;

		int LevelLifeDL;
		int VitalityToLifeDL;

		int LevelLifeSUM;
		int VitalityToLifeSUM;
		
		int LevelLifeRF;
		int VitalityToLifeRF;
	}PrideMu;
#endif
#ifdef DRYNEA_LIST_CUSTOM

	struct sDryneaConfig
	{
		//b.координаты после убийства
		int GMKillMap;
		short GMKillMapX;
		short GMKillMapY;


		//PartySystem
		int PartySystemEnable;
		int Silver;
		int Gold;
		int ExpMinus;
#define MAXPARTY_DIAPASON 10
		struct 
		{
			int StartDiapason;
			int EndDiapason;
		} PartyDiapason[MAXPARTY_DIAPASON];
		int CountPartyDiapason;
		int KundumItemsDrop;// = 5 //Item Drop
		int ErohimItemsDrop;// = 5 //Item Drop
		int CountKundumItemsDrop;
		int CountErohimItemsDrop;

		int PostFloodProtect;
		int PostFloodProtectTime;
		/*
			[PartySystem]
			Silver = 10; +10% опыта каждому
			Gold = +20% опыта каждому
			ExpMinus = 30 (штраф на опыт в диапазонах)

			1
			//[Start duapazon reset] [End diapazon reset]
			0 20
			21 80
			81 150
			end
		*/
	}DryneaConfig;
#endif

#ifdef LVL_UP_POINTS
	struct cAddLvlPoint
	{
		int DkLevelPoints;
		int DwLevelPoints;
		int ElfLevelPoints;
		int SumLevelPoints;
		int MgLevelPoints;
		int DlLevelPoints;
		int RfLevelPoints;
	}AddLvlPoint;
	struct cAddMasterLvlPoint
	{
		int DkLevelPoints;
		int DwLevelPoints;
		int ElfLevelPoints;
		int SumLevelPoints;
		int MgLevelPoints;
		int DlLevelPoints;
		int RfLevelPoints;
	}AddMasterLvlPoint;
#endif

	struct cAddMarlonPoint
	{
		int DkLevelPoints;
		int DwLevelPoints;
		int ElfLevelPoints;
		int SumLevelPoints;
		int MgLevelPoints;
		int DlLevelPoints;
		int RfLevelPoints;
	}AddMarlonPoint;

	struct cAddClass2rdPoint
	{
		int DkLevelPoints;
		int DwLevelPoints;
		int ElfLevelPoints;
		int SumLevelPoints;
	}AddClass2rdPoint;

	struct cAddClass3rdPoint
	{
		int DkLevelPoints;
		int DwLevelPoints;
		int ElfLevelPoints;
		int SumLevelPoints;
		int MgLevelPoints;
		int DlLevelPoints;
		int RfLevelPoints;
	}AddClass3rdPoint;


#if(USER_EVOMU)
	SEVOMU_CONFIG evo_cfg;
#endif
	int iTeleportMapForDieMap6;
	int iTeleportMapForDieMap40;
	int iTeleportMapForDieMap51;

	int DW_MapStart;
	int DW_X;
	int DW_Y;
	int DK_MapStart;
	int DK_X;
	int DK_Y;
	int EE_MapStart;
	int EE_X;
	int EE_Y;
	int SU_MapStart;
	int SU_X;
	int SU_Y;
	int MG_MapStart;
	int MG_X;
	int MG_Y;
	int DL_MapStart;
	int DL_X;
	int DL_Y;
	int RF_MapStart;
	int RF_X;
	int RF_Y;

	bool m_bNewBuffPremiumEnable;
	int m_iNewBuffPremiumDamage;
	int m_iNewBuffPremiumDefence;

	bool m_bNewBuffGuildEnable;
	int m_bNewBuffGuildMembOnline;
	int m_iNewBuffGuildDamage;
	int m_iNewBuffGuildDefence;

	bool m_bNewBuffPartyEnable;
	int m_bNewBuffPartyMembCount;
	int m_iNewBuffPartyDamage;
	int m_iNewBuffPartyDefence;

	int m_iBloodCastleMaxUser;
	int m_iGuildMaxUser;
	int m_iAllianceMaxGuild;

	int m_iExpPartyPlus;
};
extern cExConfigs ExConfig;

#endif CONFIGS_H