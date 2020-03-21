#pragma once 

#if(DEV_EXMENU_V3)

/*
	newui_position02
	MonsterCount
	0x7A0C - BattleSkill
*/

enum EXMENU_NUMBER
{
	eVERSION_NO = 0,
	eVERSION_NS = 1,
	eVERSION_ET = 2,
	eVERSION_WB = 3,
};

class CExMenuV3
{
public:
	CExMenuV3();
	~CExMenuV3();

	void Init();
	void LoadIMG();
	void Bind();
	void Load(EXMENU_NUMBER Number);
	void DrawMain();
	void DrawMenu();
	void DrawWindow();
	float DrawButton(char* Text, int ID, float X, float Y, bool disabled = false);

	void CursorButton(DWORD Event);

	void DrawMenu2();
	void DrawWindow2();

	bool m_Enable;
	int m_Version;
};

extern CExMenuV3 g_ExMenuV3;

#endif