#pragma once

#if(CUSTOM_CHATFILTER)

#define MAX_FILTER_SYNTAX 1000

struct FILTER_INFO
{
	char label[64];
};

class CChatFilter
{
public:
		 CChatFilter();
		 ~CChatFilter();
	void Load();
	void Read(char* FileName);
	void CheckSyntax(int aIndex, char* text);
private:
	bool m_Active;
	bool m_Enable;
	int m_iChatBanMin;
	std::vector<FILTER_INFO> m_FilterInfo;
	int m_Count;
};

extern CChatFilter g_ChatFilter;

#endif