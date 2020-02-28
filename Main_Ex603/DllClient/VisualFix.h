#pragma once

#include "stdafx.h"
#include "Protocol.h"
#include "Object.h"

class cVisualFix
{
public:
	short aIndex;
	int AttackHP;
	int AttackSD;
	int Life;
	int SD;
	int Mana;
	int AG;
	int MaxLife;
	int MaxSD;
	int MaxMana;
	int MaxAG;
	int UpPoint;
	int Exp;
	int AttackRate;
	int DamageRate;
	int FinalDamage;


	bool PlayerKill;

	char LifeTab[50];
	char ManaTab[50];
	char SDTab[50];
	char AGTab[50];

	void InitVisualFix();

	void RecvIndex(PMSG_JOINRESULT * Data);
	void RecvDamage(PMSG_ATTACKRESULT * Data);
	void RecvHPSD(PMSG_REFILL * Data);
	void RecvMPAG(PMSG_MANASEND * Data);
	void RecvUpPoint(PMSG_CHARMAPJOINRESULT * Data);
	void RecvUpLevel(PMSG_LEVELUP * Data);
	void RecvDownPoint(PMSG_LVPOINTADDRESULT * Data);
	void RecvRespawn();
	void RecvKilledObject(PMSG_DIEPLAYER * Data);
	void RecvExp(PMSG_KILLPLAYER * Data);
	void RecvMasterExp(PMSG_KILLPLAYER_EXT * Data);

	static void DrawDamageHP(int a1, int a2, int a3, float a4, char a5, char a6);
	static void DrawDamageSD(int a1, int a2, int a3, float a4, char a5, char a6);
	static void DrawFinalDamage(int a1, int a2, int a3, float a4, char a5, char a6);

	static void DrawHp(float a1, float a2, int a3, float a4);
	static void DrawMp(float a1, float a2, int a3, float a4);
	static void DrawAg(float a1, float a2, int a3, float a4);
	static void DrawSd(float a1, float a2, int a3, float a4);

	static void DrawTabHP(signed int a1, signed int a2, LPCSTR lpMultiByteStr);
	static void DrawTabMP(signed int a1, signed int a2, LPCSTR lpMultiByteStr);
	static void DrawTabSD(signed int a1, signed int a2, LPCSTR lpMultiByteStr);
	static void DrawTabAG(signed int a1, signed int a2, LPCSTR lpMultiByteStr);

	static void InfoHp(int a1, const char *a2, ...);
	static void InfoMp(int a1, const char *a2, ...);
	static void InfoPoint(int a1, const char *a2, ...);

	static void DrawCircle(DWORD ModelID, float Arg2, float Arg3, float Arg4, float Arg5, float Arg6, float Arg7, float Arg8, float Arg9, int Arg10, int Arg11, int Arg12);

	//static void CalculateAttackRate(lpCharObj lpUser, LPVOID EDX);
	//static void CalculateDamageRate(lpCharObj lpUser, LPVOID EDX);

	//static int GetAttackRate();
	//static int GetDamageRate();

	void GCVisualInit();
};
extern cVisualFix gVisualFix;