#pragma once

#if(DEV_USERSHOP)

class CUserShop
{
public:
		CUserShop();
		~CUserShop();
	void Load();
	void Bind();
	void Draw();
	void DrawItem(int X, int Y, int Type, int Index, int Level);
	void Button(DWORD Event);
};

extern CUserShop g_UserShop;

#endif