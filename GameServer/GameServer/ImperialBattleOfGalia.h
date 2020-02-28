
#include "user.h"

#define BATTLEOFGALIA_STATE_NONE			0
#define BATTLEOFGALIA_STATE_STANDBY1		1
#define BATTLEOFGALIA_STATE_PHAZE1			2
#define BATTLEOFGALIA_STATE_STANDBY2		3
#define BATTLEOFGALIA_STATE_PHAZE2			4
#define BATTLEOFGALIA_STATE_STANDBY3		5
#define BATTLEOFGALIA_STATE_PHAZE3			6
#define BATTLEOFGALIA_STATE_END				7

struct BATTLEOFGALIA_DATA
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

class CImperialBattleOfGalia
{
	friend class CImperial;
public:
	CImperialBattleOfGalia();
	virtual ~CImperialBattleOfGalia();

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
	BATTLEOFGALIA_DATA		m_BattleData;
	bool					PortalSetState;
	bool					SuccessValue;
};