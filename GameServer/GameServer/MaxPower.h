#pragma once

/*
	0 - Damage
	1 - MinDefence
	2 - IgnoreDefence
	3 - CriticalDamageRate
	4 - ExellentDamageRate
	5 - DoubleDamage
	6 - AbsordDamage
	7 - ReflectDamage
	8 - SD
	9 - Life
	10 - Wizard Damage
	11 - Exp
	12 - Zen
*/

  //CLASS_WIZARD = 0x0,
  //CLASS_KNIGHT = 0x1,
  //CLASS_ELF = 0x2,
  //CLASS_MAGUMSA = 0x3,
  //CLASS_DARKLORD = 0x4,
  //CLASS_SUMMONER = 0x5,
  //CLASS_MONK = 0x6,

#define MaxPower_Dir "..\\Data\\ExData\\MaxPower.ini"

class cMaxPower
{
public:
	void Load();
	void Main(int aIndex);
private:

	void DK(int aIndex);
	void DW(int aIndex);
	void Elf(int aIndex);
	void MG(int aIndex);
	void DL(int aIndex);
	void SUM(int aIndex);
	void RF(int aIndex);

	bool Enable;

	//-> DK
	int MaxDamageDK;
	int MaxDefenceDK;
	int MaxIgnoreDefenceRateDK;
	int MaxCriticalDamageRateDK;
	int MaxExellentDamageRateDK;
	int MaxDoubleDamageRateDK;
	int MaxAbsordDamageRateDK;
	int MaxReflectDamageRateDK;
	int MaxWizardDamageDK;
	int MaxLifeDK;
	int MaxSdDK;

	//-> DW
	int MaxDamageDW;
	int MaxDefenceDW;
	int MaxIgnoreDefenceRateDW;
	int MaxCriticalDamageRateDW;
	int MaxExellentDamageRateDW;
	int MaxDoubleDamageRateDW;
	int MaxAbsordDamageRateDW;
	int MaxReflectDamageRateDW;
	int MaxWizardDamageDW;
	int MaxLifeDW;
	int MaxSdDW;

	//-> Elf
	int MaxDamageElf;
	int MaxDefenceElf;
	int MaxIgnoreDefenceRateElf;
	int MaxCriticalDamageRateElf;
	int MaxExellentDamageRateElf;
	int MaxDoubleDamageRateElf;
	int MaxAbsordDamageRateElf;
	int MaxReflectDamageRateElf;
	int MaxWizardDamageElf;
	int MaxLifeElf;
	int MaxSdElf;

	//-> MG
	int MaxDamageMG;
	int MaxDefenceMG;
	int MaxIgnoreDefenceRateMG;
	int MaxCriticalDamageRateMG;
	int MaxExellentDamageRateMG;
	int MaxDoubleDamageRateMG;
	int MaxAbsordDamageRateMG;
	int MaxReflectDamageRateMG;
	int MaxWizardDamageMG;
	int MaxLifeMG;
	int MaxSdMG;

	//-> DL
	int MaxDamageDL;
	int MaxDefenceDL;
	int MaxIgnoreDefenceRateDL;
	int MaxCriticalDamageRateDL;
	int MaxExellentDamageRateDL;
	int MaxDoubleDamageRateDL;
	int MaxAbsordDamageRateDL;
	int MaxReflectDamageRateDL;
	int MaxWizardDamageDL;
	int MaxLifeDL;
	int MaxSdDL;

	//-> SUM
	int MaxDamageSUM;
	int MaxDefenceSUM;
	int MaxIgnoreDefenceRateSUM;
	int MaxCriticalDamageRateSUM;
	int MaxExellentDamageRateSUM;
	int MaxDoubleDamageRateSUM;
	int MaxAbsordDamageRateSUM;
	int MaxReflectDamageRateSUM;
	int MaxWizardDamageSUM;
	int MaxLifeSUM;
	int MaxSdSUM;

	//-> RF
	int MaxDamageRF;
	int MaxDefenceRF;
	int MaxIgnoreDefenceRateRF;
	int MaxCriticalDamageRateRF;
	int MaxExellentDamageRateRF;
	int MaxDoubleDamageRateRF;
	int MaxAbsordDamageRateRF;
	int MaxReflectDamageRateRF;
	int MaxWizardDamageRF;
	int MaxLifeRF;
	int MaxSdRF;
};
extern cMaxPower gMaxPower;