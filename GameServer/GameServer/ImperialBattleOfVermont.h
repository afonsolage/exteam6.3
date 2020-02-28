
#include "user.h"

#define BATTLEOFVERMONT_STATE_NONE			0
#define BATTLEOFVERMONT_STATE_STANDBY1		1
#define BATTLEOFVERMONT_STATE_PHAZE1		2
#define BATTLEOFVERMONT_STATE_STANDBY2		3
#define BATTLEOFVERMONT_STATE_PHAZE2		4
#define BATTLEOFVERMONT_STATE_STANDBY3		5
#define BATTLEOFVERMONT_STATE_PHAZE3		6
#define BATTLEOFVERMONT_STATE_END			7



struct BATTLEOFVERMONT_DATA
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

class CImperialBattleOfVermont
{
	friend class CImperial;
public:
	CImperialBattleOfVermont();
	virtual ~CImperialBattleOfVermont();

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
	BATTLEOFVERMONT_DATA	m_BattleData;
	bool					PortalSetState;
	bool					SuccessValue;
};

static const struct VermontGatePosition
{
	int	Class;
	int	X;
	int Y;
	int Dir;
} g_VermontGate[9] = {

	525, 75, 67, 3,
	524, 50, 65, 3,
	527, 19, 65, 3,
	525, 37, 93, 1,
	524, 41, 117, 1,
	527, 55, 154, 1,
	525, 107, 112, 3
};


static const struct VermontMapAttr
{
	int StartX;
	int StartY;
	int EndX;
	int EndY;
} g_VermontMapAttr[9] = {
	71, 66, 76, 68,
	46, 63, 51, 65,
	15, 64, 20, 66,
	36, 92, 38, 97,
	40, 116, 43, 121,
	54, 153, 56, 158,
	103, 110, 108, 112
};

static const struct VermontTraps
{
	int X;
	int Y;
} g_VermontTrap[10] = {
	40, 65,
	30, 65,
	30, 65,
	41, 120,
	41, 124,
	45, 128,
	49, 128,
	54, 129,
	54, 134
};

