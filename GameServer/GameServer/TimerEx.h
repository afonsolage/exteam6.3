#pragma once

class CTimerEx
{
public:
		CTimerEx();
		~CTimerEx();

	void Init();
	void Run();
	int GetSecond();

private:
	int m_TickSecond;

};

extern CTimerEx g_TimerEx;