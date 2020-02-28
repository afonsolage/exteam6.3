#ifdef IMPERIAL_CONFLICT_OLD
#include "ImperialBattleOfDestler.h"
#include "ImperialBattleOfVermont.h"
#include "ImperialBattleOfKato.h"
#include "ImperialBattleOfGalia.h"
#include "ImperialBattleOfErkanne.h"
#include "ImperialBattleOfRaymond.h"
#include "ImperialBattleOfGaion.h"
#include "..\common\winutil.h"
#include "..\include\prodef.h"

#define IMPERIAL_STATE_NONE		0
#define IMPERIAL_STATE_OPEN		1
#define IMPERIAL_STATE_DESTLER	2
#define IMPERIAL_STATE_VERMONT	3
#define IMPERIAL_STATE_KATO		4
#define IMPERIAL_STATE_GALIA	5
#define IMPERIAL_STATE_ERKANNE	6
#define IMPERIAL_STATE_RAYMOND	7
#define IMPERIAL_STATE_GAION	8
#define IMPERIAL_STATE_ENDED	9

#define IMPERIAL_REWARD_DIR "..\\Data\\Events\\ImperialFort.ini"

struct IMPERIAL_EVENT_INFO
{
	void Reset()
	{
		this->PartyID = -1;
		this->iState = 0;
		Tick = 0;
		Time = 0;
	}
	short PartyID;
	int iState;
	DWORD Tick;
	int Time;
	int Day;
};


class CImperial
{
public:
	CImperial();
	virtual ~CImperial();

	void Init();

	void Run();
	void SetState_OPEN();
	void SetState_DESTLER();
	void SetState_VERMONT();
	void SetState_KATO();
	void SetState_GALIA();
	void SetState_ERKANNE();
	void SetState_RAYMOND();
	void SetState_GAION();
	void SetState_ENDED();
	void ProcState_OPEN();
	void ProcState_DESTLER();
	void ProcState_VERMONT();
	void ProcState_KATO();
	void ProcState_GALIA();
	void ProcState_ERKANNE();
	void ProcState_RAYMOND();
	void ProcState_GAION();
	void ProcState_ENDED();
	void SetState(int iState);
	bool EnterEvent(short aIndex);
	void SetTrapIndex(short aIndex, int Day);
	bool UsePortalGate(LPOBJ lpObj, int gt);
	int GetSpecificState();
	void SendEventInterface();
	int	GiveRewardExp(int aIndex, int Exp);
	int LevelUp(int iUserIndex, int iAddExp);
	void SendFailMessage(int aIndex);

	int GetCurrentDay();
	bool GateAttack(int Class);

	struct 
	{
		int Type;
		int Index;
		int Level;
		int Skill;
		int Luck;
		int Opt;
		int Exl;
		int Anc;
	}iItem[7][200];
	int iCount[7];
	void LoadRewardItem();
	bool ImperialReward(LPOBJ lpObj, LPOBJ lpMobObj);
private:
	IMPERIAL_EVENT_INFO m_ImperialData;
	CImperialBattleOfDestler m_BattleOfDestler;
	CImperialBattleOfVermont m_BattleOfVermont;
	CImperialBattleOfKato m_BattleOfKato;
	CImperialBattleOfGalia m_BattleOfGalia;
	CImperialBattleOfErkanne m_BattleOfErkanne;
	CImperialBattleOfRaymond m_BattleOfRaymond;
	CImperialBattleOfGaion m_BattleOfGaion;
};

static const struct ImperialGates
{
	int Day;
	int Gate;
} g_ImperialGate[7] = 
{
	1, 307,
	2, 312,
	3, 317,
	4, 307,
	5, 312,
	6, 317,
	7, 322
};

static const struct ImperialExpTable
{
	int		Day;
	__int64 Experience;
} g_ExpTable[7] = {
	1,	500000,
	2,	600000,
	3,	700000,
	4,	800000,
	5,	900000,
	6,	1000000,
	7,	5000000
};
extern CImperial g_Imperial;
#endif