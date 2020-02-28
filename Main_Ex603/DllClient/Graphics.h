#include "stdafx.h"

extern bool g_bGlowGraphic;

#if(NEW_GLOW_EFFECT)



static DWORD gSelectEnter = 0x0040AB4A;
static DWORD gGraphicsEnter = 0x00777B3B;
static DWORD gSelectASMJmp00 = gSelectEnter+6;
static DWORD gGraphicsASM00Jmp00 = gGraphicsEnter+5;


class Graphics
{
public:
	Graphics();
	// ----
	void		Load();
	static void	InitGraphics();
	static void	InterfaceDraw();
	static int  SelectDraw(int value);

}; extern Graphics gGraphics;

#endif