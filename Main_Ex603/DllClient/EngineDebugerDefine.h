#pragma once

#if(ENGINE_DEBUGER)

#define MAX_INTERFACE_DATA	100

enum 
{
	eCONSOLE_RED			= 1,	//�������
	eCONSOLE_GREEN			= 2,	//�������
	eCONSOLE_BLUE			= 3,	//�����
	eCONSOLE_CYAN			= 4,	//�����
	eCONSOLE_YELLOW			= 5,	//������
	eCONSOLE_MAGENTA		= 6,	//����������
	eCONSOLE_GREY			= 7,	//�������
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