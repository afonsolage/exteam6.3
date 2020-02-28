#include "user.h"

#define BATTLEOFKATO_STATE_NONE			0
#define BATTLEOFKATO_STATE_STANDBY1		1
#define BATTLEOFKATO_STATE_PHAZE1		2
#define BATTLEOFKATO_STATE_STANDBY2		3
#define BATTLEOFKATO_STATE_PHAZE2		4
#define BATTLEOFKATO_STATE_STANDBY3		5
#define BATTLEOFKATO_STATE_PHAZE3		6
#define BATTLEOFKATO_STATE_END			7



struct BATTLEOFKATO_DATA
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

class CImperialBattleOfKato
{
	friend class CImperial;
public:
	CImperialBattleOfKato();
	virtual ~CImperialBattleOfKato();

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
	BATTLEOFKATO_DATA	m_BattleData;
	bool					PortalSetState;
	bool					SuccessValue;
};

static const struct KatoGatePosition
{
	int	Class;
	int	X;
	int Y;
	int Dir;
} g_KatoGate[9] = {

	525, 146, 191, 3,
	527, 119, 192, 3,
	525, 89, 195, 3,
	528, 222, 134, 1,
	524, 222, 160, 1,
	527, 223, 193, 1,
	525, 167, 217, 1
};


static const struct KatoMapAttr
{
	int StartX;
	int StartY;
	int EndX;
	int EndY;
} g_KatoMapAttr[9] = {
	142, 190, 147, 192,
	115, 191, 120, 193,
	85, 195, 90, 197,
	222, 133, 224, 138,
	222, 159, 224, 164,
	222, 192, 224, 197,
	166, 216, 168, 221
};

static const struct KatoTraps
{
	int X;
	int Y;
} g_KatoTrap[15] = {
	113, 194,
	112, 119,
	108, 203,
	98, 204,
	93, 203,
	93, 198,
	94, 194,
	93, 190,
	97, 187,
	109, 87,
	114, 89,
	223, 165,
	222, 169,
	223, 174
};