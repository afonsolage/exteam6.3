#include "user.h"

#define BATTLEOFGAION_STATE_NONE			0
#define BATTLEOFGAION_STATE_STANDBY1		1
#define BATTLEOFGAION_STATE_PHAZE1			2
#define BATTLEOFGAION_STATE_STANDBY2		3
#define BATTLEOFGAION_STATE_PHAZE2			4
#define BATTLEOFGAION_STATE_STANDBY3		5
#define BATTLEOFGAION_STATE_PHAZE3			6
#define BATTLEOFGAION_STATE_STANDBY4		7
#define BATTLEOFGAION_STATE_PHAZE4			8
#define BATTLEOFGAION_STATE_END				9



struct BATTLEOFGAION_DATA
{
	void Reset()
	{
		for(int n=0;n<10;++n)
		{
			this->GateIndex[n] = -1;
		}
		this->CurrentLeaderIndex = -1;
		this->MonsterCount = 0;
		this->TrapIndex = -1;
		this->NotifyCount = -1;
	}
	int CurrentLeaderIndex;
	int GateIndex[10];
	int Time;
	int TickCount;
	int CurrentState;
	int MonsterCount;
	int CurrentAIGroup;
	int TrapIndex;
	int PhazeStep;
	BYTE NotifyCount;
};

class CImperialBattleOfGaion
{
	friend class CImperial;
public:
	CImperialBattleOfGaion();
	virtual ~CImperialBattleOfGaion();

	void SetState(int iState);
	void SetNextState();
	void SetState_NONE();
	void SetState_STANDBY1();
	void SetState_PHAZE1();
	void SetState_STANDBY2();
	void SetState_PHAZE2();
	void SetState_STANDBY3();
	void SetState_PHAZE3();
	void SetState_STANDBY4();
	void SetState_PHAZE4();
	void SetState_END();
	void Run();
	void ProcState_NONE();
	void ProcState_STANDBY1();
	void ProcState_PHAZE1();
	void ProcState_STANDBY2();
	void ProcState_PHAZE2();
	void ProcState_STANDBY3();
	void ProcState_PHAZE3();
	void ProcState_STANDBY4();
	void ProcState_PHAZE4();
	void ProcState_END();
	int	 GetEventTime();
	int  GetEventState();
	void SendImperialPlayers(LPBYTE lpMsg, int iSize);
	void SendEventInterface();
	void SendEventState();
	void MonsterProc();
	void OperatePortalGate(bool Block, bool ForAll, int aIndex);
	void SetMapAttr(int Gate);
	bool EnterPortal(LPOBJ lpObj);

	void SetSuccessValue(bool SuccessValue) { this->SuccessValue = SuccessValue; }
	bool GetSuccessValue() { return this->SuccessValue; }

	void ResetData();
	void CreateAIGroup(int iGroupNumber);
	void DeleteAIGroup(int iGroupNumber);
	void CreateGates();

private:
	BATTLEOFGAION_DATA		m_BattleData;
	bool					PortalSetState;
	bool					SuccessValue;
};

static const struct GaionGatePosition
{
	int	Class;
	int	X;
	int Y;
	int Dir;
} g_GaionGate[10] = {

	528, 81, 68, 3,
	527, 50, 69, 3,
	528, 32, 90, 1,
	528, 34, 176, 1,
	527, 52, 191, 3,
	528, 69, 166, 1,
	528, 156, 132, 3,
	527, 197, 132, 3,
	528, 225, 159, 1,
	528, 214, 24, 3
};


static const struct GaionMapAttr
{
	int StartX;
	int StartY;
	int EndX;
	int EndY;
} g_GaionMapAttr[10] = {
	77, 67, 82, 69,
	46, 68, 51, 70,
	31, 89, 33, 94,
	33, 175, 35, 180,
	51, 190, 56, 192,
	68, 162, 69, 167,
	155, 131, 160, 133,
	195, 131, 201, 133,
	224, 158, 226, 163,
	210, 23, 215, 25
};

static const struct GaionTraps
{
	int X;
	int Y;
} g_GaionTrap[26] = {
	44, 74,
	44, 69,
	37, 66,
	37, 70,
	29, 67,
	29, 75,
	34, 75,
	33, 80,
	33,	86,
	29, 84,
	58, 190,
	64, 190,
	69, 190,
	69, 184,
	69, 179,
	68, 165,
	68, 171,
	204, 131,
	208, 132,
	213, 132,
	217, 133,
	225, 135,
	224, 140,
	224, 145,
	225, 150,
	225, 153
};