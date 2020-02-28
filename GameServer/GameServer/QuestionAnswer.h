#pragma once

#if(EVENT_QUESTIONANSWER)

struct QUESTIONANSWER_DATA
{
	char Question[64];
	char Answer[64];
};

struct QUESTIONANSWER_TIME
{
	int Hour;
	int Min;
};

class CQuestionAnswer
{
public:
		 CQuestionAnswer();
		 ~CQuestionAnswer();

	void Init();
	void Load();
	void Read(char* filename);
	void Run();
	void Search();
	void Chat(int aIndex, char* Msg);
	void Reward(int aIndex);

	int m_Enable;
	int m_NumData;

	int m_RewardWCoinC;
	int m_RewardWCoinP;
	int m_RewardGoblin;
	int m_RewardCredit;

	std::vector<QUESTIONANSWER_DATA> m_Data;
	std::vector<QUESTIONANSWER_TIME> m_Time;
};

extern CQuestionAnswer g_QuestionAnswer;


#endif