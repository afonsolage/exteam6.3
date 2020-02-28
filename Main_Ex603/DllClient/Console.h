#pragma once

#include "stdafx.h"
//#include "Import.h"

enum CNSL_E
{
	cRED			= 1,	//�������
	cGREEN			= 2,	//�������
	cBLUE			= 3,	//�����
	cCYAN			= 4,	//�����
	cYELLOW			= 5,	//������
	cMAGENTA		= 6,	//����������
	cGREY			= 7,	//�������
};

class cConsole
{
public:
	void InitCore();
	void Output(int Color, const char* Format, ...);
	HANDLE Handle(BOOL Input);
};
extern cConsole gConsole;