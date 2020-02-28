#pragma once

//#define DEBUG_DRAW__	1

extern int exWinWidth;
extern int exWinHeight;

class Start
{
private:
	char IP[16];
	char Serial[17];
	char Version[6];
public:
	void InitOGLHook();
	void Load();

	void Connect();
	void Fix();

	static int GameLoad();
	static void __fastcall MoveListInit(LPVOID This, LPVOID EDX, int Arg1, int Arg2);

	void SpeedCalc();
#ifdef DEBUG_DRAW__
	void Init_sub_636420_sub_636450();
	static double Crack_sub_636420(float a1);
	static double Crack_sub_636450(float a1);
#endif
};
extern Start gStart;