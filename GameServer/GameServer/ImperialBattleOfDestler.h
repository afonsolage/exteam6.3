
#include "user.h"

#define BATTLEOFDESTLER_STATE_NONE			0
#define BATTLEOFDESTLER_STATE_STANDBY1		1
#define BATTLEOFDESTLER_STATE_PHAZE1		2
#define BATTLEOFDESTLER_STATE_STANDBY2		3
#define BATTLEOFDESTLER_STATE_PHAZE2		4
#define BATTLEOFDESTLER_STATE_STANDBY3		5
#define BATTLEOFDESTLER_STATE_PHAZE3		6
#define BATTLEOFDESTLER_STATE_END			7



struct BATTLEOFDESTLER_DATA
{
	void Reset()
	{
		for(int i=0;i<3;++i)
		{
			this->AIGroups[i] = -1;
		}
		for(int n=0;n<9;++n)
		{
			this->GateIndex[n] = -1;
		}
		this->CurrentLeaderIndex = -1;
		this->MonsterCount = 0;
		this->TrapIndex = -1;
		this->NotifyCount = -1;
	}
	int AIGroups[3];
	int CurrentLeaderIndex;
	int GateIndex[9];
	int Time;
	int TickCount;
	int CurrentState;
	int MonsterCount;
	int CurrentAIGroup;
	int TrapIndex;
	int PhazeStep;
	BYTE NotifyCount;
};

class CImperialBattleOfDestler
{
	friend class CImperial;
public:
	CImperialBattleOfDestler();
	virtual ~CImperialBattleOfDestler();

	void SetState(int iState);
	void SetNextState();
	void SetState_NONE();
	void SetState_STANDBY1();
	void SetState_PHAZE1();
	void SetState_STANDBY2();
	void SetState_PHAZE2();
	void SetState_STANDBY3();
	void SetState_PHAZE3();
	void SetState_END();
	void Run();
	void ProcState_NONE();
	void ProcState_STANDBY1();
	void ProcState_PHAZE1();
	void ProcState_STANDBY2();
	void ProcState_PHAZE2();
	void ProcState_STANDBY3();
	void ProcState_PHAZE3();
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
	BATTLEOFDESTLER_DATA	m_BattleData;
	bool					PortalSetState;
	bool					SuccessValue;
};

static const struct DestlerGatePosition
{
	int	Class;
	int	X;
	int Y;
	int Dir;
} g_DestlerGate[9] = {

	525, 234, 29, 1,
	524, 233, 55, 1,
	525, 216, 80, 3,
	525, 194, 25, 3,
	524, 166, 25, 3,
	525, 154, 53, 1,
	525, 180, 79, 1
};


static const struct DestlerMapAttr
{
	int StartX;
	int StartY;
	int EndX;
	int EndY;

} g_DestlerMapAttr[9] = {
	232, 28, 236, 33,
	231, 55, 234, 59,
	212, 79, 216, 80,
	190, 24, 194, 26,
	162, 24, 168, 26,
	154, 53, 156, 57,
	179, 79, 181, 85
};

static const struct DestlerTraps
{
	int X;
	int Y;
} g_DestlerTrap[12] = {
	232, 61,
	225, 66,
	219, 68,
	220, 75,
	220, 83,
	160, 25,
	155, 27,
	155, 32,
	155, 37,
	155, 44,
	155, 50
};
