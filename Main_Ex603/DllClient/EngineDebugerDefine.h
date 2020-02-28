#pragma once

#if(ENGINE_DEBUGER)

#define MAX_INTERFACE_DATA	100

enum 
{
	eCONSOLE_RED			= 1,	//Красный
	eCONSOLE_GREEN			= 2,	//Зеленый
	eCONSOLE_BLUE			= 3,	//Синий
	eCONSOLE_CYAN			= 4,	//Белый
	eCONSOLE_YELLOW			= 5,	//Жолтый
	eCONSOLE_MAGENTA		= 6,	//Фиолетовый
	eCONSOLE_GREY			= 7,	//Голубой
};

enum 
{
	eDrawTypeText,
	eDrawTypeImage,
};

struct INTERFACE_DATA
{
	int TypeDraw;
	int Index;				// -> TEXT: Color | IMAGE: Index
	int PosX;
	int PosY;
	int Width;
	int Heigh;				// -> Align;
	char Path[MAX_PATH];	// -> TEXT: Message | IMAGE: Path folder Images
};

struct INTERFACE_IMAGE
{
	int ImageIndex;
	int Index;				// -> TEXT: Color | IMAGE: Index
	int PosX;
	int PosY;
	int Width;
	int Heigh;				// -> Align;
	char Path[MAX_PATH];	// -> TEXT: Message | IMAGE: Path folder Images
};

struct INTERFACE_DRAW
{
	int TypeDraw;
	int Index;				// -> TEXT: Color | IMAGE: Index
	int PosX;
	int PosY;
	int Width;
	int Heigh;				// -> Align;
	char Path[MAX_PATH];	// -> TEXT: Message | IMAGE: Path folder Images
};

#endif