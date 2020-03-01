#pragma once

#include "stdafx.h"
#include "Protocol.h"
#include "Defines.h"

#if(CUSTOM_ADD_POINTS==TRUE)

struct PMSG_ADD_POINTS
{
	PBMSG_HEAD2 h;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD Leadership;
};

struct PMSG_ADD_POINTSRESET
{
	PBMSG_HEAD2 h;
	bool Result;
};

struct GC_RESET_POINT_CFG
{
	PBMSG_HEAD2 h;
	int iResetStatsPriceBonus;
	int iResetStatsPriceCredit;
};

class CAddPoints
{
public:
	CAddPoints();
	~CAddPoints();

	void Init();
	void Load();
	void ImageLoad();
	void BindImage();
	void Draw();
	void Button(DWORD Event);
	void Keybord(DWORD Event);
	void GCPoints();
	void Open(int type);
	void Close();
	bool Result(bool type);

	static void _TC CharacterInfo(LPVOID This, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);
	void DrawResetStats();
	bool ResetsTatsCheckAccept();
	void CheckMaxStats(char* TextStats);
	void CheckMaxStatsEx(int &Stats);

	int ActivePage;
	int ActiveSend;
	int FreePoint;
	bool Click;
	int PointX;

	char StrengthText[6];
	char DexterityText[6];
	char VitalityText[6];
	char EnergyText[6];
	char CommandText[6];

	bool ResetStatsForBonus;
	bool ResetStatsForCredit;
	int ResetStatsPriceBonus;
	int ResetStatsPriceCredit;

	int ReturnTotalPoint();
	void GCResetPointRecv(GC_RESET_POINT_CFG * aRecv);
	float CharX;
	float CharY;
	void CharInfoDraw();

	int m_MaxStats;
	bool m_Loaded;
	bool m_Enabled;
};
extern CAddPoints g_AddPoints;

#endif