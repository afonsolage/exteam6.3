#include "StdAfx.h"
#include "GameMain.h"
#include "logproc.h"
#include "..\\include\\ReadScript.h"
#include "TimerEx.h"
#include "ExUser.h"
#include "QuestionAnswer.h"
#include "ExLicense.h"

#if(EVENT_QUESTIONANSWER)

CQuestionAnswer g_QuestionAnswer;

CQuestionAnswer::CQuestionAnswer()
{
	this->Init();
}

CQuestionAnswer::~CQuestionAnswer()
{
}

void CQuestionAnswer::Init()
{
	this->m_Enable = false;
	this->m_NumData = -1;

	this->m_RewardWCoinC = 0;
	this->m_RewardWCoinP = 0;
	this->m_RewardGoblin = 0;
	this->m_RewardCredit = 0;

	this->m_Data.clear();
	this->m_Time.clear();
}

void CQuestionAnswer::Load()
{
	this->Init();

	if(!g_ExLicense.CheckUser(eExUB::Local)  &&
	   !g_ExLicense.CheckUser(eExUB::eternalmu) &&
	   !g_ExLicense.CheckUser(eExUB::Artem) &&
	   !g_ExLicense.CheckUser(eExUB::Artem2))
	{
		return;
	}

	this->Read(gDirPath.GetNewPath("ExData\\Events\\QuestionAnswer.dat"));
}

void CQuestionAnswer::Read(char* filename)
{
	SMDFile = fopen(filename, "r");

	if(SMDFile == NULL)
	{
		LogAdd(lMsg.Get(MSGGET(1, 198)), filename);
		return;
	}

	SMDToken Token;

	int iType = -1;

	while(true)
	{
		Token = GetToken();

        if(Token == END)
		{
            break;
		}

		iType = (int)TokenNumber;

		if(iType < 0 || iType > 3)
		{
			break;
		}

		while(true)
		{
			if(iType == 0)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				this->m_Enable = (int)TokenNumber;
			}
			else if(iType == 1)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				QUESTIONANSWER_TIME List;

				List.Hour = (int)TokenNumber;

				Token = GetToken();
				List.Min = (int)TokenNumber;

				this->m_Time.push_back(List);
			}
			else if(iType == 2)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				this->m_RewardWCoinC = (int)TokenNumber;

				Token = GetToken();
				this->m_RewardWCoinP = (int)TokenNumber;

				Token = GetToken();
				this->m_RewardGoblin = (int)TokenNumber;

				Token = GetToken();
				this->m_RewardCredit = (int)TokenNumber;
			}
			else if(iType == 3)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				QUESTIONANSWER_DATA List;

				memcpy(List.Question, TokenString, sizeof(List.Question));

				Token = GetToken();
				memcpy(List.Answer, TokenString, sizeof(List.Answer));

				this->m_Data.push_back(List);
			}
		}
	}

	fclose(SMDFile);

	LogAdd("%s file load!", filename);
}

void CQuestionAnswer::Run()
{
	if(!this->m_Enable)
	{
		return;
	}

#if(NEWTIMEREX)
	if(g_TimerEx.GetSecond() != 00)
#else
	if(time.wSecond != 00)
#endif
	{
		return;
	}

	SYSTEMTIME systime;

	GetLocalTime(&systime);

	for(std::vector<QUESTIONANSWER_TIME>::iterator it = this->m_Time.begin(); it != this->m_Time.end(); it++)
	{
		if(it->Hour == systime.wHour && it->Min == systime.wMinute)
		{
			this->Search();

			return;
		}
	}
}

void CQuestionAnswer::Search()
{
	int iDataSize = this->m_Data.size();

	if(iDataSize <= 0)
	{
		return;
	}

	this->m_NumData = rand() % iDataSize;

	AllSendServerMsg(this->m_Data[this->m_NumData].Question);
}

void CQuestionAnswer::Chat(int aIndex, char* Msg)
{
	if(!this->m_Enable)
	{
		return;
	}
	
	if(this->m_NumData == -1)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(!strcmp(Msg, this->m_Data[this->m_NumData].Answer))
	{
		this->Reward(aIndex);

		char szText[128];
		sprintf(szText, "[%s] Correct Answer", lpObj->Name);
		AllSendServerMsg(szText);
	
		this->m_NumData = -1;
	}
}

void CQuestionAnswer::Reward(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	bool bWcoinSend = false;

	if(this->m_RewardWCoinC > 0)
	{
		lpObj->GameShop.WCoinC += this->m_RewardWCoinC;
		MsgOutput(aIndex, "[WCoinC]: +%d", this->m_RewardWCoinC);
		bWcoinSend = true;
	}

	if(this->m_RewardWCoinP > 0)
	{
		lpObj->GameShop.WCoinP += this->m_RewardWCoinP;
		MsgOutput(aIndex, "[WCoinP]: +%d", this->m_RewardWCoinP);
		bWcoinSend = true;
	}

	if(this->m_RewardGoblin > 0)
	{
		lpObj->GameShop.GoblinPoint += this->m_RewardGoblin;
		MsgOutput(aIndex, "[WCoinG]: +%d", this->m_RewardGoblin);
		bWcoinSend = true;
	}

	if(this->m_RewardCredit > 0)
	{
		ExUserDataSend(aIndex);
		MsgOutput(aIndex, "[Credit]: +%d", this->m_RewardCredit);
	}

	if(bWcoinSend)
	{
		gGameShop.GDSaveUserInfo(aIndex);
	}
}

#endif