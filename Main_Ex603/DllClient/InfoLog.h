#pragma once

#include "stdafx.h"
#include "Protocol.h"
#include "ChatExpanded.h"

#if(CUSTOM_EX_CHAT==TRUE)

class CInfoLog
{
public:
		CInfoLog();
		~CInfoLog();

	void Init();
	void Load();

	void GCChatProc(PMSG_CHATDATA* lpChat);
	void GCChatWhisperRecv(CHAT_WHISPER_EX* lpMsg);

	void Output(LPSTR folder, LPSTR filename, LPSTR szMsg, ...);

	char szMsg[256];
	wchar_t pwText[256];
	char psText[256];
};
extern CInfoLog g_InfoLog;

#endif