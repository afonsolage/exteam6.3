#include "StdAfx.h"
#include "protocol.h"
#include "Interface.h"
#include "StatsAdvance.h"

#if(DEV_STATS_ADVANCE)

CStatsAdvance g_StatsAdvance;

CStatsAdvance::CStatsAdvance()
{
	this->m_Enable = false;
	this->m_Loaded = false;

	memset(&this->m_Data, 0, sizeof(this->m_Data));
}

CStatsAdvance::~CStatsAdvance()
{
}

void CStatsAdvance::Bind()
{
	gInterface.BindObject(eADVANCE_STAT_INFO, ex_INFO_2, 22, 19, -1, -1);
}

void CStatsAdvance::Load()
{
	this->m_Enable = true;
}

void CStatsAdvance::DrawInfo()
{
	if(!this->m_Enable && !this->m_Loaded)
	{
		return;
	}

	if(!gInterface.CheckWindow(ObjWindow::Character))
	{
		return;
	}

	DWORD dwColor = eWhite;
	float flDrawX = this->m_CharX + 142;	//450;
	float flDrawY = this->m_CharY + 339;	//18;

	gInterface.DrawGUI(eADVANCE_STAT_INFO, flDrawX , flDrawY);

	if(!gInterface.IsWorkZone(eADVANCE_STAT_INFO))
	{
		return;
	}

	flDrawX = this->m_CharX - 15;	//450;
	flDrawY = 0;//this->m_CharY - 52;	//18;

	float flWidth = 190;
	float flHight = 430;

	gInterface.DrawBarForm(flDrawX, flDrawY, flWidth, flHight, 0, 0, 0, 150);	
	flDrawY += 2;

	///////
	gInterface.DrawFormat(eAncient, flDrawX, flDrawY, flWidth, 3, "Advance Stats");
	flDrawY += 10;
	///////

	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "Level: %d", this->m_Data.Level);
	//flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "MasterLevel: %d", this->m_Data.MasterLevel);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "Reset: %d", this->m_Data.Reset);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "GrandReset: %d", this->m_Data.GrandReset);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "TotalDamageReflect: %d", this->m_Data.TotalDamageReflect);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "FullDamageReflectRate: %d", this->m_Data.FullDamageReflectRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "CriticalDamageRate: %d", this->m_Data.CriticalDamageRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "CriticalDamagePower: %d", this->m_Data.CriticalDamagePower);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ExellentDamageRate: %d", this->m_Data.ExellentDamageRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ExellentDamagePower: %d", this->m_Data.ExellentDamagePower);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "DoubleDamageRate: %d", this->m_Data.DoubleDamageRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "TripleDamageRate: %d", this->m_Data.TripleDamageRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "DamageReductionRate: %d", this->m_Data.DamageReductionRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ShieldSkillDamageReductionRate: %d", this->m_Data.ShieldSkillDamageReductionRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "SDDamageReductionRate: %d", this->m_Data.SDDamageReductionRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "SDDecreaseDamageRate: %d", this->m_Data.SDDecreaseDamageRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "IgnoreDefenceRate: %d", this->m_Data.IgnoreDefenceRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "IgnoreSDRate: %d", this->m_Data.IgnoreSDRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "IncreaseDamagePvP: %d", this->m_Data.IncreaseDamagePvP);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "IncreaseDefencePvP: %d", this->m_Data.IncreaseDefencePvP);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ResistDoubleDamageRate: %d", this->m_Data.ResistDoubleDamageRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ResistIgnoreDefenceRate: %d", this->m_Data.ResistIgnoreDefenceRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ResistIgnoreSDRate: %d", this->m_Data.ResistIgnoreSDRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ResistCriticalDamageRate: %d", this->m_Data.ResistCriticalDamageRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ResistExellentDamageRate: %d", this->m_Data.ResistExellentDamageRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ResistStumRate: %d", this->m_Data.ResistStumRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ResistIce: %d", this->m_Data.ResistIce);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ResistPoison: %d", this->m_Data.ResistPoison);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ResistLighting: %d", this->m_Data.ResistLighting);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ResistFire: %d", this->m_Data.ResistFire);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ResistEarth: %d", this->m_Data.ResistEarth);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ResistWind: %d", this->m_Data.ResistWind);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "ResistWater: %d", this->m_Data.ResistWater);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "FullHPRestoreRate: %d", this->m_Data.FullHPRestoreRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "FullMPRestoreRate: %d", this->m_Data.FullMPRestoreRate);
	flDrawY = this->DrawLine(flDrawX, flDrawY, flWidth, "FullSDRestoreRate: %d", this->m_Data.FullSDRestoreRate);
}

float CStatsAdvance::DrawLine(float PosX, float PosY, int Width, LPCSTR Text, ...)
{
	float flResult = 0.0;
	DWORD dwColor = eWhite;

	char szBuff[256];
	int iBuffLen = sizeof(szBuff)-1;
	ZeroMemory(szBuff, iBuffLen);

	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(szBuff, iBuffLen, Text, args);
	va_end(args);

	pDrawColorText(szBuff, PosX, PosY, Width, 0, dwColor, 0, 3);

	pDrawColorButton(0x7880, PosX + 10, PosY + 10, Width - 20, 0.85, NULL, NULL, eOrange);

	flResult = PosY + 12;

	return flResult;
}

void CStatsAdvance::Button(DWORD Event)
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinStatsAdvance))
	{
		//return;
	}
}

void CStatsAdvance::Recv(PMSG_STATS_ADVANCE* lpMsg)
{
	if(!lpMsg->Result)
	{
		return;
	}

	memcpy(&this->m_Data, &lpMsg->StatInfo, sizeof(this->m_Data));

	this->m_Loaded = true;
}

void CStatsAdvance::Send()
{

}

#endif