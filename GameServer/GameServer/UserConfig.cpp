#include "StdAfx.h"
#include "UserConfig.h"
#include "GameMain.h"
#include "ExLicense.h"
#include "GameMain.h"

CUserConfig g_UserConfig;

CUserConfig::CUserConfig()
{
}

CUserConfig::~CUserConfig()
{
}

void CUserConfig::Load()
{
	if(g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ulasevich2))
	{
		this->ReadUsilevich(gDirPath.GetNewPath("ExData\\User\\Usilevich.ini"));
	}

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))
	{
		this->ReadEvoMU(gDirPath.GetNewPath("ExData\\User\\EvoMU.ini"));
	}
}

void CUserConfig::CheckNullNumber(int& number)
{
	if(number <= 0)
	{
		number = 1;
	}
}

void CUserConfig::ReadUsilevich(char* filename)
{
	this->m_Usilevich.DarkSideAgility = GetPrivateProfileInt("ExTeam", "DarkSideAgility", 10, filename);
	this->m_Usilevich.ChainDriveVitality = GetPrivateProfileInt("ExTeam", "ChainDriveVitality", 8, filename);
	this->m_Usilevich.DragonRoarEnergy = GetPrivateProfileInt("ExTeam", "DragonRoarEnergy", 10, filename);

	this->CheckNullNumber(this->m_Usilevich.DarkSideAgility);
	this->CheckNullNumber(this->m_Usilevich.ChainDriveVitality);
	this->CheckNullNumber(this->m_Usilevich.DragonRoarEnergy);
}

void CUserConfig::ReadEvoMU(char* filename)
{
	this->m_EvoMU.CSRegTimeNeed = GetPrivateProfileInt("ExTeam", "CSRegTimeNeed", 40000, filename);
	this->m_EvoMU.CSRegTimeMinus = GetPrivateProfileInt("ExTeam", "CSRegTimeMinus", 4000, filename);
	this->m_EvoMU.PvpMap400LvlTpActive = GetPrivateProfileInt("ExTeam", "PvpMap400LvlTpActive", 0, filename);
	this->m_EvoMU.PvpMap400LvlTpMap = GetPrivateProfileInt("ExTeam", "PvpMap400LvlTpMap", 0, filename);
	this->m_EvoMU.PvpMap400LvlTpX = GetPrivateProfileInt("ExTeam", "PvpMap400LvlTpX", 0, filename);
	this->m_EvoMU.PvpMap400LvlTpY = GetPrivateProfileInt("ExTeam", "PvpMap400LvlTpY", 0, filename);
	this->m_EvoMU.HPAutoClicker = GetPrivateProfileInt("ExTeam", "HPAutoClicker", 0, filename);
}

void CUserConfig::GC_SettingsSend(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	PMSG_USERCONFIG pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xC0, sizeof(pMsg));
	memcpy(&pMsg.EvoConfig, &this->m_EvoMU, sizeof(pMsg.EvoConfig));
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

