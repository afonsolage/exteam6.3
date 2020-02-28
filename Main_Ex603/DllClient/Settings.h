#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Protocol.h"
#if(CUSTOM_WIN_SETTINGS==TRUE)
// ----------------------------------------------------------------------------------------------

class Settings
{
public:
		 Settings();
		 ~Settings();

	void Init();
	void BindImages();
	void Draw();
	void Button(DWORD Event);
};
extern Settings g_Settings;
// ----------------------------------------------------------------------------------------------
#endif