// SkillAdditionInfo.cpp: implementation of the CSkillAdditionInfo class.
//	GS	1.00.90	JPN		-	Completed
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SkillAdditionInfo.h"
#include "LogProc.h"
#include "Gamemain.h"
#include "..\include\ReadScript.h"

CSkillAdditionInfo g_SkillAdditionInfo;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkillAdditionInfo::CSkillAdditionInfo()
{
	this->Init();
}

CSkillAdditionInfo::~CSkillAdditionInfo()
{
	return;
}

void CSkillAdditionInfo::Init()
{
	this->m_iInfinityArrowSkillTime = 0; //4
	this->m_iInfinityArrowUseLevel = 0; //8

	this->m_iInfinityArrowMPConsumptionPlus0 = 0; //C
	this->m_iInfinityArrowMPConsumptionPlus1 = 0; //10
	this->m_iInfinityArrowMPConsumptionPlus2 = 0; //14
	this->m_iInfinityArrowMPConsumptionPlus3 = 0; //18 //Season4.5 add-on

	for(int i = 0; i <= 5; i++) //Master Soul Barrier Season 3
	{
		this->m_wSoulBarrierManaRateLevel[i] = 0;
	}

	ZeroMemory(this->m_SkillUseReqLevel, sizeof(m_SkillUseReqLevel));
}

BOOL CSkillAdditionInfo::Load(LPSTR lpszFileName)
{
	if ( lpszFileName == NULL || strcmp(lpszFileName, "") == 0 )
	{
		LogAddTD("[Skill Addition Info] - File load error : File Name Error");
		return FALSE;
	}

	int Token;
	this->Init();
	// ----
	SMDFile = fopen(gDirPath.GetNewPath(lpszFileName), "r");
	// ----
	if( SMDFile == 0 )
	{
		MsgBox(lMsg.Get(MSGGET(0, 112)), lpszFileName);
		ExitProcess(0);
		return false;
	}
	// ----
	while(true) 
	{
		Token = GetToken();
		// ----
		if( Token == END || !strcmp(TokenString, "end") )
		{
			break;
		}
		else
		{
			int SkillID = TokenNumber;
			Token = GetToken();
			int Level	= TokenNumber;
			// ----
			if( Level < 1 )
			{
				Level = 1;
			}
			// ----
			this->m_SkillUseReqLevel[SkillID] = Level;
		}
	}
	// ----
	fclose(SMDFile);


	this->m_iInfinityArrowSkillTime = GetPrivateProfileInt("SkillInfo", "InfinityArrowSkillTime", 600, gDirPath.GetNewPath(lpszFileName)); 
	this->m_iInfinityArrowUseLevel = GetPrivateProfileInt("SkillInfo", "InfinityArrowUseLevel", 220, gDirPath.GetNewPath(lpszFileName)); 
	
	this->m_iInfinityArrowMPConsumptionPlus0 = GetPrivateProfileInt("SkillInfo", "InfinityArraowMPConsumptionPlus0", 0, gDirPath.GetNewPath(lpszFileName));
	this->m_iInfinityArrowMPConsumptionPlus1 = GetPrivateProfileInt("SkillInfo", "InfinityArraowMPConsumptionPlus1", 0, gDirPath.GetNewPath(lpszFileName));
	//this->m_iInfinityArrowMPConsumptionPlus2 = GetPrivateProfileInt("SkillInfo", "InfinityArraowMPConsumptionPlus2", 0, gDirPath.GetNewPath(lpszFileName));
	this->m_iInfinityArrowMPConsumptionPlus3 = GetPrivateProfileInt("SkillInfo", "InfinityArraowMPConsumptionPlus3", 0, gDirPath.GetNewPath(lpszFileName));

	LogAddTD("[Skill Addition Info] [Infinity Arrow] Skill Time[%d], UseLevel[%d], Arrow MP Consumption +0[%d] +1[%d] +2[%d] +3[%d]", this->m_iInfinityArrowSkillTime, this->m_iInfinityArrowUseLevel, this->m_iInfinityArrowMPConsumptionPlus0, this->m_iInfinityArrowMPConsumptionPlus1, this->m_iInfinityArrowMPConsumptionPlus2, this->m_iInfinityArrowMPConsumptionPlus3);

	this->m_bFireScreamSkill = GetPrivateProfileInt("SkillInfo", "FireScreamSkill", 1, gDirPath.GetNewPath(lpszFileName));
	this->m_iFireScreamExplosionAttackDistance = GetPrivateProfileInt("SkillInfo", "FireScreamExplosionAttackDistance", 1, gDirPath.GetNewPath(lpszFileName));
	this->m_iFireScreamExplosionRate = GetPrivateProfileInt("SkillInfo", "FireScreamExplosionRate", 300, gDirPath.GetNewPath(lpszFileName));
	this->m_iFireScreamMaxAttackCountSameSerial = GetPrivateProfileInt("SkillInfo", "FireScreamMaxAttackCountSameSerial", 3, gDirPath.GetNewPath(lpszFileName));
	this->m_iFireScreamSerialInitCount = GetPrivateProfileInt("SkillInfo", "FireScreamSerialInitCount", 100, gDirPath.GetNewPath(lpszFileName));
	this->m_bCheckFireScreamSerial = GetPrivateProfileInt("SkillInfo", "CheckFireScreamSerial", 1, gDirPath.GetNewPath(lpszFileName));

	LogAddTD("[Skill Addition Info] [Fire Scream] Use(%d) : Explosion Distance(%d) - Rate(%d), MaxAttack_SameSerial(%d), SerialInitCount(%d), Check Serial(%d)", this->m_bFireScreamSkill, this->m_iFireScreamExplosionAttackDistance, this->m_iFireScreamExplosionRate, this->m_iFireScreamMaxAttackCountSameSerial, this->m_iFireScreamSerialInitCount, this->m_bCheckFireScreamSerial);

	//Season3 Addition

	// -------------------------------------------------------------------------------------------------------------------------------
	char oszFloat[256];
	this->SoulBarrierDefenseStart				= GetPrivateProfileInt(OTHER_SKILL_CM, "SoulBarrierDefenseStart", 600, OTHER_SKILL_DIR); 
	this->SoulBarrierDefenseDiv1				= GetPrivateProfileInt(OTHER_SKILL_CM, "SoulBarrierDefenseDiv1", 600, OTHER_SKILL_DIR); 
	this->SoulBarrierDefenseDiv2				= GetPrivateProfileInt(OTHER_SKILL_CM, "SoulBarrierDefenseDiv2", 600, OTHER_SKILL_DIR); 
	this->SoulBarrierDefenseMax				= GetPrivateProfileInt(OTHER_SKILL_CM, "SoulBarrierDefenseMax", 600, OTHER_SKILL_DIR); 
	this->SoulBarrierTimeStart				= GetPrivateProfileInt(OTHER_SKILL_CM, "SoulBarrierTimeStart", 600, OTHER_SKILL_DIR); 
	this->SoulBarrierTimeDiv					= GetPrivateProfileInt(OTHER_SKILL_CM, "SoulBarrierTimeDiv", 600, OTHER_SKILL_DIR); 
	this->SoulBarrierTimeMax					= GetPrivateProfileInt(OTHER_SKILL_CM, "SoulBarrierTimeMax", 600, OTHER_SKILL_DIR); 
	this->WizardryEnchantDamageDiv			= GetPrivateProfileInt(OTHER_SKILL_CM, "WizardryEnchantDamageDiv", 600, OTHER_SKILL_DIR); 
	GetPrivateProfileString(OTHER_SKILL_CM, "WizardryEnchantDamageFact", "0.2", oszFloat, 5, OTHER_SKILL_DIR);
	sscanf(oszFloat, "%f", &this->WizardryEnchantDamageFact);
	this->WizardryEnchantDamageMax			= GetPrivateProfileInt(OTHER_SKILL_CM, "WizardryEnchantDamageMax", 600, OTHER_SKILL_DIR); 
	this->WizardryEnchantTime					= GetPrivateProfileInt(OTHER_SKILL_CM, "WizardryEnchantTime", 600, OTHER_SKILL_DIR); 
	this->SwellLifeEffectStart				= GetPrivateProfileInt(OTHER_SKILL_CM, "SwellLifeEffectStart", 600, OTHER_SKILL_DIR); 
	this->SwellLifeEffectDiv1					= GetPrivateProfileInt(OTHER_SKILL_CM, "SwellLifeEffectDiv1", 600, OTHER_SKILL_DIR); 
	this->SwellLifeEffectDiv2					= GetPrivateProfileInt(OTHER_SKILL_CM, "SwellLifeEffectDiv2", 600, OTHER_SKILL_DIR); 
	this->SwellLifeEffectMax					= GetPrivateProfileInt(OTHER_SKILL_CM, "SwellLifeEffectMax", 600, OTHER_SKILL_DIR); 
	this->SwellLifeTimeStart					= GetPrivateProfileInt(OTHER_SKILL_CM, "SwellLifeTimeStart", 600, OTHER_SKILL_DIR); 
	this->SwellLifeTimeDiv					= GetPrivateProfileInt(OTHER_SKILL_CM, "SwellLifeTimeDiv", 600, OTHER_SKILL_DIR); 
	this->SwellLifeTimeMax					= GetPrivateProfileInt(OTHER_SKILL_CM, "SwellLifeTimeMax", 600, OTHER_SKILL_DIR); 
	this->ElfDefenseEffectFact				= GetPrivateProfileInt(OTHER_SKILL_CM, "ElfDefenseEffectFact", 600, OTHER_SKILL_DIR); 
	this->ElfDefenseEffectDiv					= GetPrivateProfileInt(OTHER_SKILL_CM, "ElfDefenseEffectDiv", 600, OTHER_SKILL_DIR); 
	this->ElfDefenseEffectMax					= GetPrivateProfileInt(OTHER_SKILL_CM, "ElfDefenseEffectMax", 600, OTHER_SKILL_DIR); 
	this->ElfDefenseTime						= GetPrivateProfileInt(OTHER_SKILL_CM, "ElfDefenseTime", 600, OTHER_SKILL_DIR); 
	this->ElfAttackEffectFact					= GetPrivateProfileInt(OTHER_SKILL_CM, "ElfAttackEffectFact", 600, OTHER_SKILL_DIR); 
	this->ElfAttackEffectDiv					= GetPrivateProfileInt(OTHER_SKILL_CM, "ElfAttackEffectDiv", 600, OTHER_SKILL_DIR); 
	this->ElfAttackEffectMax					= GetPrivateProfileInt(OTHER_SKILL_CM, "ElfAttackEffectMax", 600, OTHER_SKILL_DIR); 
	this->ElfAttackTime						= GetPrivateProfileInt(OTHER_SKILL_CM, "ElfAttackTime", 600, OTHER_SKILL_DIR); 
	this->CriticalDamageEffectDiv1			= GetPrivateProfileInt(OTHER_SKILL_CM, "CriticalDamageEffectDiv1", 600, OTHER_SKILL_DIR); 
	this->CriticalDamageEffectDiv2			= GetPrivateProfileInt(OTHER_SKILL_CM, "CriticalDamageEffectDiv2", 600, OTHER_SKILL_DIR); 
	this->CriticalDamageEffectMax				= GetPrivateProfileInt(OTHER_SKILL_CM, "CriticalDamageEffectMax", 600, OTHER_SKILL_DIR); 
	this->CriticalDamageTimeStart				= GetPrivateProfileInt(OTHER_SKILL_CM, "CriticalDamageTimeStart", 600, OTHER_SKILL_DIR); 
	this->CriticalDamageTimeDiv				= GetPrivateProfileInt(OTHER_SKILL_CM, "CriticalDamageTimeDiv", 600, OTHER_SKILL_DIR); 
	this->CriticalDamageTimeMax				= GetPrivateProfileInt(OTHER_SKILL_CM, "CriticalDamageTimeMax", 600, OTHER_SKILL_DIR); 
	this->BerserkerManaIncDiv					= GetPrivateProfileInt(OTHER_SKILL_CM, "BerserkerManaIncDiv", 600, OTHER_SKILL_DIR); 
	this->BerserkerLifeDecDiv					= GetPrivateProfileInt(OTHER_SKILL_CM, "BerserkerLifeDecDiv", 600, OTHER_SKILL_DIR); 
	this->BerserkerTimeStart					= GetPrivateProfileInt(OTHER_SKILL_CM, "BerserkerTimeStart", 600, OTHER_SKILL_DIR); 
	this->BerserkerTimeDiv					= GetPrivateProfileInt(OTHER_SKILL_CM, "BerserkerTimeDiv", 600, OTHER_SKILL_DIR); 
	this->BerserkerTimeMax					= GetPrivateProfileInt(OTHER_SKILL_CM, "BerserkerTimeMax", 600, OTHER_SKILL_DIR); 
	this->BerserkerProcentDamageMax				= GetPrivateProfileInt(OTHER_SKILL_CM, "BerserkerProcentDamageMax", 0, OTHER_SKILL_DIR); 
	this->BerserkerDefenceDivProcent	= GetPrivateProfileInt(OTHER_SKILL_CM, "BerserkerDefenceDivProcent", 10, OTHER_SKILL_DIR); 
	this->ReflectEffectStart					= GetPrivateProfileInt(OTHER_SKILL_CM, "ReflectEffectStart", 600, OTHER_SKILL_DIR); 
	this->ReflectEffectDiv					= GetPrivateProfileInt(OTHER_SKILL_CM, "ReflectEffectDiv", 600, OTHER_SKILL_DIR); 
	this->ReflectEffectMax					= GetPrivateProfileInt(OTHER_SKILL_CM, "ReflectEffectMax", 600, OTHER_SKILL_DIR); 
	this->ReflectTimeStart					= GetPrivateProfileInt(OTHER_SKILL_CM, "ReflectTimeStart", 600, OTHER_SKILL_DIR); 
	this->ReflectTimeDiv						= GetPrivateProfileInt(OTHER_SKILL_CM, "ReflectTimeDiv", 600, OTHER_SKILL_DIR); 
	this->ReflectTimeMax						= GetPrivateProfileInt(OTHER_SKILL_CM, "ReflectTimeMax", 600, OTHER_SKILL_DIR); 
	this->IgnoreDefenseEffectStart			= GetPrivateProfileInt(OTHER_SKILL_CM, "IgnoreDefenseEffectStart", 600, OTHER_SKILL_DIR); 
	this->IgnoreDefenseEffectSub				= GetPrivateProfileInt(OTHER_SKILL_CM, "IgnoreDefenseEffectSub", 600, OTHER_SKILL_DIR); 
	this->IgnoreDefenseEffectDiv				= GetPrivateProfileInt(OTHER_SKILL_CM, "IgnoreDefenseEffectDiv", 600, OTHER_SKILL_DIR); 
	this->IgnoreDefenseEffectMax				= GetPrivateProfileInt(OTHER_SKILL_CM, "IgnoreDefenseEffectMax", 600, OTHER_SKILL_DIR); 
	this->IgnoreDefenseTimeStart				= GetPrivateProfileInt(OTHER_SKILL_CM, "IgnoreDefenseTimeStart", 600, OTHER_SKILL_DIR); 
	this->IgnoreDefenseTimeDiv				= GetPrivateProfileInt(OTHER_SKILL_CM, "IgnoreDefenseTimeDiv", 600, OTHER_SKILL_DIR); 
	this->IgnoreDefenseTimeMax				= GetPrivateProfileInt(OTHER_SKILL_CM, "IgnoreDefenseTimeMax", 600, OTHER_SKILL_DIR); 
	this->IncreaseHealthEffectStart			= GetPrivateProfileInt(OTHER_SKILL_CM, "IncreaseHealthEffectStart", 600, OTHER_SKILL_DIR); 
	this->IncreaseHealthEffectSub				= GetPrivateProfileInt(OTHER_SKILL_CM, "IncreaseHealthEffectSub", 600, OTHER_SKILL_DIR); 

	//this->m_IncreaseHealthEffectDiv				= GetPrivateProfileInt("SkillInfo", "IncreaseHealthEffectDiv", 600, gDirPath.GetNewPath(lpszFileName)); 
	char oszTempEx[256] = { 0 };
	GetPrivateProfileString(OTHER_SKILL_CM, "DecTimePerAttackSpeed", "10", oszTempEx, 256, OTHER_SKILL_DIR);
	this->IncreaseHealthEffectDiv = atof(oszTempEx);

	this->IncreaseHealthEffectMax				= GetPrivateProfileInt(OTHER_SKILL_CM, "IncreaseHealthEffectMax", 600, OTHER_SKILL_DIR); 
	this->IncreaseHealthTimeStart				= GetPrivateProfileInt(OTHER_SKILL_CM, "IncreaseHealthTimeStart", 600, OTHER_SKILL_DIR); 
	this->IncreaseHealthTimeDiv				= GetPrivateProfileInt(OTHER_SKILL_CM, "IncreaseHealthTimeDiv", 600, OTHER_SKILL_DIR); 
	this->IncreaseHealthTimeMax				= GetPrivateProfileInt(OTHER_SKILL_CM, "IncreaseHealthTimeMax", 600, OTHER_SKILL_DIR); 
	this->IncreaseBlockEffectStart			= GetPrivateProfileInt(OTHER_SKILL_CM, "IncreaseBlockEffectStart", 600, OTHER_SKILL_DIR); 
	this->IncreaseBlockEffectSub				= GetPrivateProfileInt(OTHER_SKILL_CM, "IncreaseBlockEffectSub", 600, OTHER_SKILL_DIR); 
	this->IncreaseBlockEffectDiv				= GetPrivateProfileInt(OTHER_SKILL_CM, "IncreaseBlockEffectDiv", 600, OTHER_SKILL_DIR); 
	this->IncreaseBlockEffectMax				= GetPrivateProfileInt(OTHER_SKILL_CM, "IncreaseBlockEffectMax", 600, OTHER_SKILL_DIR); 
	this->IncreaseBlockTimeStart				= GetPrivateProfileInt(OTHER_SKILL_CM, "IncreaseBlockTimeStart", 600, OTHER_SKILL_DIR); 
	this->IncreaseBlockTimeDiv				= GetPrivateProfileInt(OTHER_SKILL_CM, "IncreaseBlockTimeDiv", 600, OTHER_SKILL_DIR); 
	this->IncreaseBlockTimeMax				= GetPrivateProfileInt(OTHER_SKILL_CM, "IncreaseBlockTimeMax", 600, OTHER_SKILL_DIR); 
	// ----
	this->WeaknessEffectStartVsMob			= GetPrivateProfileInt(OTHER_SKILL_CM, "WeaknessEffectStartVsMob", 4, OTHER_SKILL_DIR);
	this->WeaknessEffectDivVsMob				= GetPrivateProfileInt(OTHER_SKILL_CM, "WeaknessEffectDivVsMob", 58, OTHER_SKILL_DIR);
	this->WeaknessEffectMaxVsMob				= GetPrivateProfileInt(OTHER_SKILL_CM, "WeaknessEffectMaxVsMob", 0, OTHER_SKILL_DIR);

	this->WeaknessTimeStartVsMob				= GetPrivateProfileInt(OTHER_SKILL_CM, "WeaknessTimeStartVsMob", 4, OTHER_SKILL_DIR);
	this->WeaknessTimeDivVsMob				= GetPrivateProfileInt(OTHER_SKILL_CM, "WeaknessTimeDivVsMob", 100, OTHER_SKILL_DIR);
	this->WeaknessTimeMaxVsMob				= GetPrivateProfileInt(OTHER_SKILL_CM, "WeaknessTimeMaxVsMob", 0, OTHER_SKILL_DIR);

	this->WeaknessEffectStartVsUser			= GetPrivateProfileInt(OTHER_SKILL_CM, "WeaknessEffectStartVsUser", 3, OTHER_SKILL_DIR);
	this->WeaknessEffectDivVsUser				= GetPrivateProfileInt(OTHER_SKILL_CM, "WeaknessEffectDivVsUser", 93, OTHER_SKILL_DIR);
	this->WeaknessEffectMaxVsUser				= GetPrivateProfileInt(OTHER_SKILL_CM, "WeaknessEffectMaxVsUser", 72, OTHER_SKILL_DIR);

	this->WeaknessTimeStartVsUser				= GetPrivateProfileInt(OTHER_SKILL_CM, "WeaknessTimeStartVsUser", 5, OTHER_SKILL_DIR);
	this->WeaknessTimeDivVsUser				= GetPrivateProfileInt(OTHER_SKILL_CM, "WeaknessTimeDivVsUser", 300, OTHER_SKILL_DIR);
	this->WeaknessTimeMaxVsUser				= GetPrivateProfileInt(OTHER_SKILL_CM, "WeaknessTimeMaxVsUser", 0, OTHER_SKILL_DIR);
	this->WeaknessMaxPower				= GetPrivateProfileInt(OTHER_SKILL_CM, "WeaknessMaxPower", 0, OTHER_SKILL_DIR);
	// ----
	this->InnovationEffectStartVsMob			= GetPrivateProfileInt(OTHER_SKILL_CM, "InnovationEffectStartVsMob", 20, OTHER_SKILL_DIR);
	this->InnovationEffectDivVsMob			= GetPrivateProfileInt(OTHER_SKILL_CM, "InnovationEffectDivVsMob", 90, OTHER_SKILL_DIR);
	this->InnovationEffectMaxVsMob			= GetPrivateProfileInt(OTHER_SKILL_CM, "InnovationEffectMaxVsMob", 0, OTHER_SKILL_DIR);

	this->InnovationTimeStartVsMob			= GetPrivateProfileInt(OTHER_SKILL_CM, "InnovationTimeStartVsMob", 4, OTHER_SKILL_DIR);
	this->InnovationTimeDivVsMob				= GetPrivateProfileInt(OTHER_SKILL_CM, "InnovationTimeDivVsMob", 100, OTHER_SKILL_DIR);
	this->InnovationTimeMaxVsMob				= GetPrivateProfileInt(OTHER_SKILL_CM, "InnovationTimeMaxVsMob", 0, OTHER_SKILL_DIR);

	this->InnovationEffectStartVsUser			= GetPrivateProfileInt(OTHER_SKILL_CM, "InnovationEffectStartVsUser", 12, OTHER_SKILL_DIR);
	this->InnovationEffectDivVsUser			= GetPrivateProfileInt(OTHER_SKILL_CM, "InnovationEffectDivVsUser", 110, OTHER_SKILL_DIR);
	this->InnovationEffectMaxVsUser			= GetPrivateProfileInt(OTHER_SKILL_CM, "InnovationEffectMaxVsUser", 0, OTHER_SKILL_DIR);

	this->InnovationTimeStartVsUser			= GetPrivateProfileInt(OTHER_SKILL_CM, "InnovationTimeStartVsUser", 5, OTHER_SKILL_DIR);
	this->InnovationTimeDivVsUser				= GetPrivateProfileInt(OTHER_SKILL_CM, "InnovationTimeDivVsUser", 300, OTHER_SKILL_DIR);
	this->InnovationTimeMaxVsUser				= GetPrivateProfileInt(OTHER_SKILL_CM, "InnovationTimeMaxVsUser", 0, OTHER_SKILL_DIR);	
	this->InnovationMaxPower				= GetPrivateProfileInt(OTHER_SKILL_CM, "InnovationMaxPower", 0, OTHER_SKILL_DIR);	
	// ----

	this->SleepRateStartVsMob					= GetPrivateProfileInt(OTHER_SKILL_CM, "SleepRateStartVsMob", 20, OTHER_SKILL_DIR);
	this->SleepRateDivVsMob					= GetPrivateProfileInt(OTHER_SKILL_CM, "SleepRateDivVsMob", 30, OTHER_SKILL_DIR);
	this->SleepRateMaxVsMob					= GetPrivateProfileInt(OTHER_SKILL_CM, "SleepRateMaxVsMob", 0, OTHER_SKILL_DIR);

	this->SleepRateStartVsUser				= GetPrivateProfileInt(OTHER_SKILL_CM, "SleepRateStartVsUser", 15, OTHER_SKILL_DIR);
	this->SleepRateDivVsUser					= GetPrivateProfileInt(OTHER_SKILL_CM, "SleepRateDivVsUser", 37, OTHER_SKILL_DIR);
	this->SleepRateMaxVsUser					= GetPrivateProfileInt(OTHER_SKILL_CM, "SleepRateMaxVsUser", 0, OTHER_SKILL_DIR);

	this->SleepTimeStartVsMob					= GetPrivateProfileInt(OTHER_SKILL_CM, "SleepTimeStartVsMob", 5, OTHER_SKILL_DIR);
	this->SleepTimeDivVsMob					= GetPrivateProfileInt(OTHER_SKILL_CM, "SleepTimeDivVsMob", 100, OTHER_SKILL_DIR);
	this->SleepTimeMaxVsMob					= GetPrivateProfileInt(OTHER_SKILL_CM, "SleepTimeMaxVsMob", 0, OTHER_SKILL_DIR);

	this->SleepTimeStartVsUser				= GetPrivateProfileInt(OTHER_SKILL_CM, "SleepTimeStartVsUser", 4, OTHER_SKILL_DIR);
	this->SleepTimeDivVsUser					= GetPrivateProfileInt(OTHER_SKILL_CM, "SleepTimeDivVsUser", 250, OTHER_SKILL_DIR);
	this->SleepTimeMaxVsUser					= GetPrivateProfileInt(OTHER_SKILL_CM, "SleepTimeMaxVsUser", 0, OTHER_SKILL_DIR);
	// -------------------------------------------------------------------------------------------------------------------------------

	this->m_wSoulBarrierManaRateLevel[0] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level0", 20, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[1] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level1", 21, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[2] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level2", 22, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[3] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level3", 23, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[4] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level4", 24, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[5] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level5", 25, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[6] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level6", 26, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[7] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level7", 27, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[8] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level8", 28, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[9] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level9", 29, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[10] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level10", 30, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[11] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level11", 31, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[12] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level12", 32, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[13] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level13", 33, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[14] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level14", 34, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[15] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level15", 35, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[16] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level16", 36, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[17] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level17", 37, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[18] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level18", 38, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[19] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level19", 39, MASTER_SKILL_DIR);
	this->m_wSoulBarrierManaRateLevel[20] = GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierManaRate_Level20", 40, MASTER_SKILL_DIR);

	char szFloat[256];
	this->m_SoulBarrierDefenseStart				= GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierDefenseStart", 600, MASTER_SKILL_DIR); 
	this->m_SoulBarrierDefenseDiv1				= GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierDefenseDiv1", 600, MASTER_SKILL_DIR); 
	this->m_SoulBarrierDefenseDiv2				= GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierDefenseDiv2", 600, MASTER_SKILL_DIR); 
	this->m_SoulBarrierDefenseMax				= GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierDefenseMax", 600, MASTER_SKILL_DIR); 
	this->m_SoulBarrierTimeStart				= GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierTimeStart", 600, MASTER_SKILL_DIR); 
	this->m_SoulBarrierTimeDiv					= GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierTimeDiv", 600, MASTER_SKILL_DIR); 
	this->m_SoulBarrierTimeMax					= GetPrivateProfileInt(MASTER_SKILL_CM, "SoulBarrierTimeMax", 600, MASTER_SKILL_DIR); 
	this->m_WizardryEnchantDamageDiv			= GetPrivateProfileInt(MASTER_SKILL_CM, "WizardryEnchantDamageDiv", 600, MASTER_SKILL_DIR); 
	GetPrivateProfileString(MASTER_SKILL_CM, "WizardryEnchantDamageFact", "10", szFloat, 5, MASTER_SKILL_DIR);
	sscanf(szFloat, "%f", &this->m_WizardryEnchantDamageFact);
	this->m_WizardryEnchantDamageMax			= GetPrivateProfileInt(MASTER_SKILL_CM, "WizardryEnchantDamageMax", 600, MASTER_SKILL_DIR); 
	this->m_WizardryEnchantTime					= GetPrivateProfileInt(MASTER_SKILL_CM, "WizardryEnchantTime", 600, MASTER_SKILL_DIR); 
	this->m_SwellLifeEffectStart				= GetPrivateProfileInt(MASTER_SKILL_CM, "SwellLifeEffectStart", 600, MASTER_SKILL_DIR); 
	this->m_SwellLifeEffectDiv1					= GetPrivateProfileInt(MASTER_SKILL_CM, "SwellLifeEffectDiv1", 600, MASTER_SKILL_DIR); 
	this->m_SwellLifeEffectDiv2					= GetPrivateProfileInt(MASTER_SKILL_CM, "SwellLifeEffectDiv2", 600, MASTER_SKILL_DIR); 
	this->m_SwellLifeEffectMax					= GetPrivateProfileInt(MASTER_SKILL_CM, "SwellLifeEffectMax", 600, MASTER_SKILL_DIR); 
	this->m_SwellLifeTimeStart					= GetPrivateProfileInt(MASTER_SKILL_CM, "SwellLifeTimeStart", 600, MASTER_SKILL_DIR); 
	this->m_SwellLifeTimeDiv					= GetPrivateProfileInt(MASTER_SKILL_CM, "SwellLifeTimeDiv", 600, MASTER_SKILL_DIR); 
	this->m_SwellLifeTimeMax					= GetPrivateProfileInt(MASTER_SKILL_CM, "SwellLifeTimeMax", 600, MASTER_SKILL_DIR); 
	this->m_ElfDefenseEffectFact				= GetPrivateProfileInt(MASTER_SKILL_CM, "ElfDefenseEffectFact", 600, MASTER_SKILL_DIR); 
	this->m_ElfDefenseEffectDiv					= GetPrivateProfileInt(MASTER_SKILL_CM, "ElfDefenseEffectDiv", 600, MASTER_SKILL_DIR); 
	this->m_ElfDefenseEffectMax					= GetPrivateProfileInt(MASTER_SKILL_CM, "ElfDefenseEffectMax", 600, MASTER_SKILL_DIR); 
	this->m_ElfDefenseTime						= GetPrivateProfileInt(MASTER_SKILL_CM, "ElfDefenseTime", 600, MASTER_SKILL_DIR); 
	this->m_ElfAttackEffectFact					= GetPrivateProfileInt(MASTER_SKILL_CM, "ElfAttackEffectFact", 600, MASTER_SKILL_DIR); 
	this->m_ElfAttackEffectDiv					= GetPrivateProfileInt(MASTER_SKILL_CM, "ElfAttackEffectDiv", 600, MASTER_SKILL_DIR); 
	this->m_ElfAttackEffectMax					= GetPrivateProfileInt(MASTER_SKILL_CM, "ElfAttackEffectMax", 600, MASTER_SKILL_DIR); 
	this->m_ElfAttackTime						= GetPrivateProfileInt(MASTER_SKILL_CM, "ElfAttackTime", 600, MASTER_SKILL_DIR); 
	this->m_CriticalDamageEffectDiv1			= GetPrivateProfileInt(MASTER_SKILL_CM, "CriticalDamageEffectDiv1", 600, MASTER_SKILL_DIR); 
	this->m_CriticalDamageEffectDiv2			= GetPrivateProfileInt(MASTER_SKILL_CM, "CriticalDamageEffectDiv2", 600, MASTER_SKILL_DIR); 
	this->m_CriticalDamageEffectMax				= GetPrivateProfileInt(MASTER_SKILL_CM, "CriticalDamageEffectMax", 600, MASTER_SKILL_DIR); 
	this->m_CriticalDamageTimeStart				= GetPrivateProfileInt(MASTER_SKILL_CM, "CriticalDamageTimeStart", 600, MASTER_SKILL_DIR); 
	this->m_CriticalDamageTimeDiv				= GetPrivateProfileInt(MASTER_SKILL_CM, "CriticalDamageTimeDiv", 600, MASTER_SKILL_DIR); 
	this->m_CriticalDamageTimeMax				= GetPrivateProfileInt(MASTER_SKILL_CM, "CriticalDamageTimeMax", 600, MASTER_SKILL_DIR); 
	this->m_BerserkerManaIncDiv					= GetPrivateProfileInt(MASTER_SKILL_CM, "BerserkerManaIncDiv", 600, MASTER_SKILL_DIR); 
	this->m_BerserkerLifeDecDiv					= GetPrivateProfileInt(MASTER_SKILL_CM, "BerserkerLifeDecDiv", 600, MASTER_SKILL_DIR); 
	this->m_BerserkerTimeStart					= GetPrivateProfileInt(MASTER_SKILL_CM, "BerserkerTimeStart", 600, MASTER_SKILL_DIR); 
	this->m_BerserkerTimeDiv					= GetPrivateProfileInt(MASTER_SKILL_CM, "BerserkerTimeDiv", 600, MASTER_SKILL_DIR); 
	this->m_BerserkerTimeMax					= GetPrivateProfileInt(MASTER_SKILL_CM, "BerserkerTimeMax", 600, MASTER_SKILL_DIR); 
	this->m_BerserkerProcentDamageMax				= GetPrivateProfileInt(MASTER_SKILL_CM, "BerserkerProcentDamageMax", 0, MASTER_SKILL_DIR); 
	this->m_BerserkerDefenceDivProcent	= GetPrivateProfileInt(MASTER_SKILL_CM, "BerserkerDefenceDivProcent", 10, MASTER_SKILL_DIR); 
	this->m_ReflectEffectStart					= GetPrivateProfileInt(MASTER_SKILL_CM, "ReflectEffectStart", 600, MASTER_SKILL_DIR); 
	this->m_ReflectEffectDiv					= GetPrivateProfileInt(MASTER_SKILL_CM, "ReflectEffectDiv", 600, MASTER_SKILL_DIR); 
	this->m_ReflectEffectMax					= GetPrivateProfileInt(MASTER_SKILL_CM, "ReflectEffectMax", 600, MASTER_SKILL_DIR); 
	this->m_ReflectTimeStart					= GetPrivateProfileInt(MASTER_SKILL_CM, "ReflectTimeStart", 600, MASTER_SKILL_DIR); 
	this->m_ReflectTimeDiv						= GetPrivateProfileInt(MASTER_SKILL_CM, "ReflectTimeDiv", 600, MASTER_SKILL_DIR); 
	this->m_ReflectTimeMax						= GetPrivateProfileInt(MASTER_SKILL_CM, "ReflectTimeMax", 600, MASTER_SKILL_DIR); 
	this->m_IgnoreDefenseEffectStart			= GetPrivateProfileInt(MASTER_SKILL_CM, "IgnoreDefenseEffectStart", 600, MASTER_SKILL_DIR); 
	this->m_IgnoreDefenseEffectSub				= GetPrivateProfileInt(MASTER_SKILL_CM, "IgnoreDefenseEffectSub", 600, MASTER_SKILL_DIR); 
	this->m_IgnoreDefenseEffectDiv				= GetPrivateProfileInt(MASTER_SKILL_CM, "IgnoreDefenseEffectDiv", 600, MASTER_SKILL_DIR); 
	this->m_IgnoreDefenseEffectMax				= GetPrivateProfileInt(MASTER_SKILL_CM, "IgnoreDefenseEffectMax", 600, MASTER_SKILL_DIR); 
	this->m_IgnoreDefenseTimeStart				= GetPrivateProfileInt(MASTER_SKILL_CM, "IgnoreDefenseTimeStart", 600, MASTER_SKILL_DIR); 
	this->m_IgnoreDefenseTimeDiv				= GetPrivateProfileInt(MASTER_SKILL_CM, "IgnoreDefenseTimeDiv", 600, MASTER_SKILL_DIR); 
	this->m_IgnoreDefenseTimeMax				= GetPrivateProfileInt(MASTER_SKILL_CM, "IgnoreDefenseTimeMax", 600, MASTER_SKILL_DIR); 
	this->m_IncreaseHealthEffectStart			= GetPrivateProfileInt(MASTER_SKILL_CM, "IncreaseHealthEffectStart", 600, MASTER_SKILL_DIR); 
	this->m_IncreaseHealthEffectSub				= GetPrivateProfileInt(MASTER_SKILL_CM, "IncreaseHealthEffectSub", 600, MASTER_SKILL_DIR); 

	//this->m_IncreaseHealthEffectDiv				= GetPrivateProfileInt("SkillInfo", "IncreaseHealthEffectDiv", 600, gDirPath.GetNewPath(lpszFileName)); 
	char szTempEx[256] = { 0 };
	GetPrivateProfileString(MASTER_SKILL_CM, "DecTimePerAttackSpeed", "10.00", szTempEx, 256, MASTER_SKILL_DIR);
	this->m_IncreaseHealthEffectDiv = atof(szTempEx);

	this->m_IncreaseHealthEffectMax				= GetPrivateProfileInt(MASTER_SKILL_CM, "IncreaseHealthEffectMax", 600, MASTER_SKILL_DIR); 
	this->m_IncreaseHealthTimeStart				= GetPrivateProfileInt(MASTER_SKILL_CM, "IncreaseHealthTimeStart", 600, MASTER_SKILL_DIR); 
	this->m_IncreaseHealthTimeDiv				= GetPrivateProfileInt(MASTER_SKILL_CM, "IncreaseHealthTimeDiv", 600, MASTER_SKILL_DIR); 
	this->m_IncreaseHealthTimeMax				= GetPrivateProfileInt(MASTER_SKILL_CM, "IncreaseHealthTimeMax", 600, MASTER_SKILL_DIR); 
	this->m_IncreaseBlockEffectStart			= GetPrivateProfileInt(MASTER_SKILL_CM, "IncreaseBlockEffectStart", 600, MASTER_SKILL_DIR); 
	this->m_IncreaseBlockEffectSub				= GetPrivateProfileInt(MASTER_SKILL_CM, "IncreaseBlockEffectSub", 600, MASTER_SKILL_DIR); 
	this->m_IncreaseBlockEffectDiv				= GetPrivateProfileInt(MASTER_SKILL_CM, "IncreaseBlockEffectDiv", 600, MASTER_SKILL_DIR); 
	this->m_IncreaseBlockEffectMax				= GetPrivateProfileInt(MASTER_SKILL_CM, "IncreaseBlockEffectMax", 600, MASTER_SKILL_DIR); 
	this->m_IncreaseBlockTimeStart				= GetPrivateProfileInt(MASTER_SKILL_CM, "IncreaseBlockTimeStart", 600, MASTER_SKILL_DIR); 
	this->m_IncreaseBlockTimeDiv				= GetPrivateProfileInt(MASTER_SKILL_CM, "IncreaseBlockTimeDiv", 600, MASTER_SKILL_DIR); 
	this->m_IncreaseBlockTimeMax				= GetPrivateProfileInt(MASTER_SKILL_CM, "IncreaseBlockTimeMax", 600, MASTER_SKILL_DIR); 
	// ----
	//this->m_WeaknessEffectStartVsMob			= GetPrivateProfileInt(MASTER_SKILL_CM, "WeaknessEffectStartVsMob", 4, MASTER_SKILL_DIR);
	//this->m_WeaknessEffectDivVsMob				= GetPrivateProfileInt(MASTER_SKILL_CM, "WeaknessEffectDivVsMob", 58, MASTER_SKILL_DIR);
	//this->m_WeaknessEffectMaxVsMob				= GetPrivateProfileInt(MASTER_SKILL_CM, "WeaknessEffectMaxVsMob", 0, MASTER_SKILL_DIR);

	//this->m_WeaknessTimeStartVsMob				= GetPrivateProfileInt(MASTER_SKILL_CM, "WeaknessTimeStartVsMob", 4, MASTER_SKILL_DIR);
	//this->m_WeaknessTimeDivVsMob				= GetPrivateProfileInt(MASTER_SKILL_CM, "WeaknessTimeDivVsMob", 100, MASTER_SKILL_DIR);
	//this->m_WeaknessTimeMaxVsMob				= GetPrivateProfileInt(MASTER_SKILL_CM, "WeaknessTimeMaxVsMob", 0, MASTER_SKILL_DIR);

	//this->m_WeaknessEffectStartVsUser			= GetPrivateProfileInt(MASTER_SKILL_CM, "WeaknessEffectStartVsUser", 3, MASTER_SKILL_DIR);
	//this->m_WeaknessEffectDivVsUser				= GetPrivateProfileInt(MASTER_SKILL_CM, "WeaknessEffectDivVsUser", 93, MASTER_SKILL_DIR);
	//this->m_WeaknessEffectMaxVsUser				= GetPrivateProfileInt(MASTER_SKILL_CM, "WeaknessEffectMaxVsUser", 72, MASTER_SKILL_DIR);

	//this->m_WeaknessTimeStartVsUser				= GetPrivateProfileInt(MASTER_SKILL_CM, "WeaknessTimeStartVsUser", 5, MASTER_SKILL_DIR);
	//this->m_WeaknessTimeDivVsUser				= GetPrivateProfileInt(MASTER_SKILL_CM, "WeaknessTimeDivVsUser", 300, MASTER_SKILL_DIR);
	//this->m_WeaknessTimeMaxVsUser				= GetPrivateProfileInt(MASTER_SKILL_CM, "WeaknessTimeMaxVsUser", 0, MASTER_SKILL_DIR);
	//// ----
	//this->m_InnovationEffectStartVsMob			= GetPrivateProfileInt(MASTER_SKILL_CM, "InnovationEffectStartVsMob", 20, MASTER_SKILL_DIR);
	//this->m_InnovationEffectDivVsMob			= GetPrivateProfileInt(MASTER_SKILL_CM, "InnovationEffectDivVsMob", 90, MASTER_SKILL_DIR);
	//this->m_InnovationEffectMaxVsMob			= GetPrivateProfileInt(MASTER_SKILL_CM, "InnovationEffectMaxVsMob", 0, MASTER_SKILL_DIR);

	//this->m_InnovationTimeStartVsMob			= GetPrivateProfileInt(MASTER_SKILL_CM, "InnovationTimeStartVsMob", 4, MASTER_SKILL_DIR);
	//this->m_InnovationTimeDivVsMob				= GetPrivateProfileInt(MASTER_SKILL_CM, "InnovationTimeDivVsMob", 100, MASTER_SKILL_DIR);
	//this->m_InnovationTimeMaxVsMob				= GetPrivateProfileInt(MASTER_SKILL_CM, "InnovationTimeMaxVsMob", 0, MASTER_SKILL_DIR);

	//this->m_InnovationEffectStartVsUser			= GetPrivateProfileInt(MASTER_SKILL_CM, "InnovationEffectStartVsUser", 12, MASTER_SKILL_DIR);
	//this->m_InnovationEffectDivVsUser			= GetPrivateProfileInt(MASTER_SKILL_CM, "InnovationEffectDivVsUser", 110, MASTER_SKILL_DIR);
	//this->m_InnovationEffectMaxVsUser			= GetPrivateProfileInt(MASTER_SKILL_CM, "InnovationEffectMaxVsUser", 0, MASTER_SKILL_DIR);

	//this->m_InnovationTimeStartVsUser			= GetPrivateProfileInt(MASTER_SKILL_CM, "InnovationTimeStartVsUser", 5, MASTER_SKILL_DIR);
	//this->m_InnovationTimeDivVsUser				= GetPrivateProfileInt(MASTER_SKILL_CM, "InnovationTimeDivVsUser", 300, MASTER_SKILL_DIR);
	//this->m_InnovationTimeMaxVsUser				= GetPrivateProfileInt(MASTER_SKILL_CM, "InnovationTimeMaxVsUser", 0, MASTER_SKILL_DIR);	
	//// ----

	this->m_SleepRateStartVsMob					= GetPrivateProfileInt(MASTER_SKILL_CM, "SleepRateStartVsMob", 20, MASTER_SKILL_DIR);
	this->m_SleepRateDivVsMob					= GetPrivateProfileInt(MASTER_SKILL_CM, "SleepRateDivVsMob", 30, MASTER_SKILL_DIR);
	this->m_SleepRateMaxVsMob					= GetPrivateProfileInt(MASTER_SKILL_CM, "SleepRateMaxVsMob", 0, MASTER_SKILL_DIR);

	this->m_SleepRateStartVsUser				= GetPrivateProfileInt(MASTER_SKILL_CM, "SleepRateStartVsUser", 15, MASTER_SKILL_DIR);
	this->m_SleepRateDivVsUser					= GetPrivateProfileInt(MASTER_SKILL_CM, "SleepRateDivVsUser", 37, MASTER_SKILL_DIR);
	this->m_SleepRateMaxVsUser					= GetPrivateProfileInt(MASTER_SKILL_CM, "SleepRateMaxVsUser", 0, MASTER_SKILL_DIR);

	this->m_SleepTimeStartVsMob					= GetPrivateProfileInt(MASTER_SKILL_CM, "SleepTimeStartVsMob", 5, MASTER_SKILL_DIR);
	this->m_SleepTimeDivVsMob					= GetPrivateProfileInt(MASTER_SKILL_CM, "SleepTimeDivVsMob", 100, MASTER_SKILL_DIR);
	this->m_SleepTimeMaxVsMob					= GetPrivateProfileInt(MASTER_SKILL_CM, "SleepTimeMaxVsMob", 0, MASTER_SKILL_DIR);

	this->m_SleepTimeStartVsUser				= GetPrivateProfileInt(MASTER_SKILL_CM, "SleepTimeStartVsUser", 4, MASTER_SKILL_DIR);
	this->m_SleepTimeDivVsUser					= GetPrivateProfileInt(MASTER_SKILL_CM, "SleepTimeDivVsUser", 250, MASTER_SKILL_DIR);
	this->m_SleepTimeMaxVsUser					= GetPrivateProfileInt(MASTER_SKILL_CM, "SleepTimeMaxVsUser", 0, MASTER_SKILL_DIR);

	LogAddTD("[Skill Addition Info] [SoulBarrier Strengrhen] BaseSkill(Level0):%d, Level1:%d, 2:%d, 3:%d, 4:%d, 5:%d", this->m_wSoulBarrierManaRateLevel[0], this->m_wSoulBarrierManaRateLevel[1], this->m_wSoulBarrierManaRateLevel[2], this->m_wSoulBarrierManaRateLevel[3], this->m_wSoulBarrierManaRateLevel[4], this->m_wSoulBarrierManaRateLevel[5]);

	return TRUE;
}

short CSkillAdditionInfo::GetSoulBarrierManaRateLevel(int iLevel)
{
	if(iLevel < 0 || 
		iLevel > 20
		)
	{
		return 20;
	}

	return this->m_wSoulBarrierManaRateLevel[iLevel];
}