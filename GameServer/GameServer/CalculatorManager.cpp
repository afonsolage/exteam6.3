#include "StdAfx.h"
#ifdef CALCULATOR_MANAGER
#include "CalculatorManager.h"



cCalculatorManager CalculatorManager;

void cCalculatorManager::Load()
{
	//Dark_Wizard
	this->DW_MinWizDamagePercent = GetPrivateProfileInt("Dark_Wizard", "MinWizDamagePercent", 100, CALCULATOR_MANAGER_DIR);
	this->DW_MaxWizDamagePercent = GetPrivateProfileInt("Dark_Wizard", "MaxWizDamagePercent", 100, CALCULATOR_MANAGER_DIR);

	//Dark_Knight
	this->DK_MinDamagePercent = GetPrivateProfileInt("Dark_Knight", "MinDamagePercent", 100, CALCULATOR_MANAGER_DIR);
	this->DK_MaxDamagePercent = GetPrivateProfileInt("Dark_Knight", "MaxDamagePercent", 100, CALCULATOR_MANAGER_DIR);

	//Fairy_Elf
	this->FE_MinDamagePercent = GetPrivateProfileInt("Fairy_Elf", "MinDamagePercent", 100, CALCULATOR_MANAGER_DIR);
	this->FE_MaxDamagePercent = GetPrivateProfileInt("Fairy_Elf", "MaxDamagePercent", 100, CALCULATOR_MANAGER_DIR);

	//Magic_Gladiator
	this->MG_MinDamagePercent = GetPrivateProfileInt("Magic_Gladiator", "MinDamagePercent", 100, CALCULATOR_MANAGER_DIR);
	this->MG_MaxDamagePercent = GetPrivateProfileInt("Magic_Gladiator", "MaxDamagePercent", 100, CALCULATOR_MANAGER_DIR);
	this->MG_MinWizDamagePercent = GetPrivateProfileInt("Magic_Gladiator", "MinWizDamagePercent", 100, CALCULATOR_MANAGER_DIR);
	this->MG_MaxWizDamagePercent = GetPrivateProfileInt("Magic_Gladiator", "MaxWizDamagePercent", 100, CALCULATOR_MANAGER_DIR);

	//Dark_Lord
	this->DL_MinDamagePercent = GetPrivateProfileInt("Dark_Lord", "MinDamagePercent", 100, CALCULATOR_MANAGER_DIR);
	this->DL_MaxDamagePercent = GetPrivateProfileInt("Dark_Lord", "MaxDamagePercent", 100, CALCULATOR_MANAGER_DIR);

	//Summoner
	this->SUM_MinimumWizardryDamagePercent = GetPrivateProfileInt("Summoner", "MinimumWizardryDamagePercent", 100, CALCULATOR_MANAGER_DIR);
	this->SUM_MaximumWizardryDamagePercent = GetPrivateProfileInt("Summoner", "MaximumWizardryDamagePercent", 100, CALCULATOR_MANAGER_DIR);
	this->SUM_MinimumCurseDamagePercent = GetPrivateProfileInt("Summoner", "MinimumCurseDamagePercent", 100, CALCULATOR_MANAGER_DIR);
	this->SUM_MaximumCurseDamagePercent = GetPrivateProfileInt("Summoner", "MaximumCurseDamagePercent", 100, CALCULATOR_MANAGER_DIR);

	//RageFighter
	this->RF_DamageMinPercent = GetPrivateProfileInt("RageFighter", "DamageMinPercent", 100, CALCULATOR_MANAGER_DIR);
	this->RF_DamageMaxPercent = GetPrivateProfileInt("RageFighter", "DamageMaxPercent", 100, CALCULATOR_MANAGER_DIR);
}



#endif
