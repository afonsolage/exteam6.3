#pragma once

#include "protocol.h"

struct USILEVICH_DATA
{
	int DarkSideAgility;
	int ChainDriveVitality;
	int DragonRoarEnergy;
};

struct EVOMU_DATA
{
	int CSRegTimeNeed;
	int CSRegTimeMinus;
	int PvpMap400LvlTpActive;
	int PvpMap400LvlTpMap;
	int PvpMap400LvlTpX;
	int PvpMap400LvlTpY;
	int HPAutoClicker;
};

struct PMSG_USERCONFIG
{
	PBMSG_HEAD2 h;
	EVOMU_DATA EvoConfig;
};

class CUserConfig
{
public:
		CUserConfig();
		~CUserConfig();

	void Load();
	void CheckNullNumber(int& number);

	void ReadUsilevich(char* filename);
	void ReadEvoMU(char* filename);
	void GC_SettingsSend(int aIndex);

	USILEVICH_DATA	m_Usilevich;
	EVOMU_DATA		m_EvoMU;
};

extern CUserConfig g_UserConfig;