#pragma once

enum eDungeonConquerorStates
{
	eDC_STATE_CLOSED,
	eDC_STATE_REG,
	eDC_STATE_WAIT,
	eDC_STATE_START,
};

class CDungeonConqueror
{
public:
	void Clear();
	void Load();
	void Tick();
	

private:
	void ProcessClosedState();
	void ProcessRegState();
	void ProcessWaitState();
	void ProcessStartState();

	bool m_Enabled;
	int m_RegWeekDay;
	int m_RegHour;
	int m_RegMin;
	int m_StartWeekDay;
	int m_StartHour;
	int m_StartMin;
	int m_WaitDuration;
	int m_EventDuration;


	eDungeonConquerorStates m_State;
};

extern CDungeonConqueror g_DungeonConqueror;