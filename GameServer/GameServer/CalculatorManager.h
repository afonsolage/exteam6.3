#include "StdAfx.h"

#ifdef CALCULATOR_MANAGER

#define CALCULATOR_MANAGER_DIR	"..\\Data\\ExData\\CalculatorManager.ini"

class cCalculatorManager
{
public:

	void Load();

	//Dark_Wizard
	int DW_MinWizDamagePercent;
	int DW_MaxWizDamagePercent;

	//Dark_Knight
	int DK_MinDamagePercent;
	int DK_MaxDamagePercent;

	//Fairy_Elf
	int FE_MinDamagePercent;
	int FE_MaxDamagePercent;

	//Magic_Gladiator
	int MG_MinDamagePercent;
	int MG_MaxDamagePercent;
	int MG_MinWizDamagePercent;
	int MG_MaxWizDamagePercent;

	//Dark_Lord
	int DL_MinDamagePercent;
	int DL_MaxDamagePercent;

	//Summoner
	int SUM_MinimumWizardryDamagePercent;
	int SUM_MaximumWizardryDamagePercent;
	//---------
	int SUM_MinimumCurseDamagePercent;
	int SUM_MaximumCurseDamagePercent;


	//RageFighter
	int RF_DamageMinPercent;
	int RF_DamageMaxPercent;


};
extern cCalculatorManager CalculatorManager;

#endif
