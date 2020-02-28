#pragma once

#include "stdafx.h"
//#include "Import.h"

enum CNSL_E
{
	cRED			= 1,	//Красный
	cGREEN			= 2,	//Зеленый
	cBLUE			= 3,	//Синий
	cCYAN			= 4,	//Белый
	cYELLOW			= 5,	//Жолтый
	cMAGENTA		= 6,	//Фиолетовый
	cGREY			= 7,	//Голубой
};

class cConsole
{
public:
	void InitCore();
	void Output(int Color, const char* Format, ...);
	HANDLE Handle(BOOL Input);
};
extern cConsole gConsole;