#include "StdAfx.h"
#ifdef FORMUL_CONFIG
#include "FormulConfig.h"



extern cFormulConfig FormulConfig;

void cFormulConfig::Load()
{
	GetPrivateProfileString("FormulConfig", "DKMinDmg","",this->DKMinDmg,LENGHT_STR,FORMUL_CONFIG_DIR);
}

bool cFormulConfig::ReadString(char str[LENGHT_STR])
{
	for(int i; i < LENGHT_STR; i++)
		for(int j; j < 3; j++)
			if(str[i] == )
}



#endif