#pragma once

#if(CUSTOM_EXTEXT)

#define MAX_EXTEXT	500

class CExText
{
public:
		CExText();
		~CExText();

	void Init();
	void Load();
	void Read(char* filename);
	void LoadText();
	void SetText(int number, char* Text);
	char* GetText(int number);

	char m_Path[128];
	char m_Text[MAX_EXTEXT][128];	
};

extern CExText g_ExText;

#endif