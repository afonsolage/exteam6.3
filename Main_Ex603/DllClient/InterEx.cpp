#include "stdafx.h"
#include "InterEx.h"
#include "Defines.h"
#include "TMemory.h"
#include "import.h"

#if(DEV_INTERFACE_EX700)

__declspec(naked) void AGPosition()
{
	static float AGPositionW = 61.0f;
	static float AGPositionH = 8.0f;
	static float AGPositionX = 383.0f;
	static float AGPositionY = 431.0f;
	static DWORD AGPosition_buff = 0x0081015D;
	_asm
	{	
	FLD DWORD PTR DS:[AGPositionW]
	FSTP DWORD PTR SS:[EBP-0x18]
	FLD DWORD PTR DS:[AGPositionH]
	FSTP DWORD PTR SS:[EBP-0x14]
	FLD DWORD PTR DS:[AGPositionX]
	FSTP DWORD PTR SS:[EBP-0x10]
	FLD DWORD PTR DS:[AGPositionY]
	FSTP DWORD PTR SS:[EBP-0x0C]
	jmp [AGPosition_buff]
	}
}
__declspec(naked) void SDPosition()
{
	static float SDPositionW = 61.0f;
	static float SDPositionH = 8.0f;
	static float SDPositionX = 196.0f;
	static float SDPositionY = 431.0f;
	static DWORD SDPosition_buff = 0x0081042D;
	_asm
	{	
	FLD DWORD PTR DS:[SDPositionW]
	FSTP DWORD PTR SS:[EBP-0x20]
	FLD DWORD PTR DS:[SDPositionH]
	FSTP DWORD PTR SS:[EBP-0x1C]
	FLD DWORD PTR DS:[SDPositionX]
	FSTP DWORD PTR SS:[EBP-0x10]
	FLD DWORD PTR DS:[SDPositionY]
	FSTP DWORD PTR SS:[EBP-0x0C] 
	jmp [SDPosition_buff]
	}
}
__declspec(naked) void MANAPosition()
{
	static float MANAPositionW = 52.0f;
	static float MANAPositionX = 448.0f;
	static float MANAPositionH = 54.0f;
	static float MANAPositionY = 415.0f;
	static DWORD MANAPosition_buff = 0x0080FE80;
	_asm
	{	
	FLD DWORD PTR DS:[MANAPositionW]
	FSTP DWORD PTR SS:[EBP-0x20]
	FLD DWORD PTR DS:[MANAPositionX]
	FSTP DWORD PTR SS:[EBP-0x0C]
	FLD DWORD PTR DS:[MANAPositionH]
	FSTP DWORD PTR SS:[EBP-0x1C]
	FLD DWORD PTR DS:[MANAPositionY]
	FSTP DWORD PTR SS:[EBP-0x8]
	jmp [MANAPosition_buff]
	}
}

__declspec(naked) void HPPosition()
{
	static float HPPositionW = 51.0f;
	static float HPPositionX = 135.0f;
	static float HPPositionH = 52.0f;
	static float HPPositionY = 414.0f;
	static DWORD HPPosition_buff = 0x0080FC2C;
	_asm
	{             
	FLD DWORD PTR DS:[HPPositionW]
	FSTP DWORD PTR SS:[EBP-0x20]
	FLD DWORD PTR DS:[HPPositionX]
	FSTP DWORD PTR SS:[EBP-0x0C]
	FLD DWORD PTR DS:[HPPositionH]
	FSTP DWORD PTR SS:[EBP-0x1C]
	FLD DWORD PTR DS:[HPPositionY]
	FSTP DWORD PTR SS:[EBP-0x8]
	jmp [HPPosition_buff]
	}
}

__declspec(naked) void UsingSkillPosition()
{
	static float UsingSkillPositionX = 309.8f;
	static float UsingSkillPositionY = 442.5f;
	static float UsingSkillPositionW = 20.0f;
	static float UsingSkillPositionH = 28.0f;
	static DWORD UsingSkillPosition_buff = 0x008137B0;
	_asm
	{
	FLD DWORD PTR DS:[UsingSkillPositionX]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[UsingSkillPositionY]
	FSTP DWORD PTR SS:[EBP-0x4]
	FLD DWORD PTR DS:[UsingSkillPositionW]
	FSTP DWORD PTR SS:[EBP-0x18]
	FLD DWORD PTR DS:[UsingSkillPositionH]
	FSTP DWORD PTR SS:[EBP-0x14]
	jmp [UsingSkillPosition_buff]
	}
}
__declspec(naked) void SkillClickPosition()
{
	static float SkillClickPositionX = 310.0f;
	static float SkillClickPositionY = 443.0f;
	static float SkillClickPositionW = 20.0f;
	static float SkillClickPositionH = 27.0f;
	static DWORD SkillClickPosition_buff = 0x008125E4;
	_asm
	{
	FLD DWORD PTR DS:[SkillClickPositionX]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[SkillClickPositionY]
	FSTP DWORD PTR SS:[EBP-0x4]
	FLD DWORD PTR DS:[SkillClickPositionW]
	FSTP DWORD PTR SS:[EBP-0x20]
	FLD DWORD PTR DS:[SkillClickPositionH]
	FSTP DWORD PTR SS:[EBP-0x1C]
	jmp [SkillClickPosition_buff]
	}
}
__declspec(naked) void SkillBarDrawPosition()
{
	static float SkillBarDrawPositionX = 222.0f;
	static float SkillBarDrawPositionY = 480.0f;
	static float SkillBarDrawPositionW = 160.0f;
	static float SkillBarDrawPositionH = 38.0f;
	static DWORD SkillBarDrawPosition_buff = 0x00812818;
	_asm
	{	
	FLD DWORD PTR DS:[SkillBarDrawPositionX]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[SkillBarDrawPositionY]
	FSTP DWORD PTR SS:[EBP-0x4]
	FLD DWORD PTR DS:[SkillBarDrawPositionW]
	FSTP DWORD PTR SS:[EBP-0x20]
	FLD DWORD PTR DS:[SkillBarDrawPositionH]
	FSTP DWORD PTR SS:[EBP-0x1C]
	jmp [SkillBarDrawPosition_buff]
	}
}
__declspec(naked) void SkillSwitchDraw()
{
	static float SkillSwitchDrawX = 385.0f;
	static float SkillSwitchDrawY = 380.0f;
	static float SkillSwitchDrawW = 32.0f;
	static float SkillSwitchDrawH = 38.0f;
	static float SkillSwitchDrawMW = 385.0f;
	static DWORD SkillSwitchDraw_buff = 0x0081387A;
	_asm
	{
		FLD DWORD PTR DS:[SkillSwitchDrawX]
		FSTP DWORD PTR SS:[EBP-0x8]
		FLD DWORD PTR DS:[SkillSwitchDrawY]
		FSTP DWORD PTR SS:[EBP-0x4]	
		FLD DWORD PTR DS:[SkillSwitchDrawW]
		FSTP DWORD PTR SS:[EBP-0x18]
		FLD DWORD PTR DS:[SkillSwitchDrawH]
		FSTP DWORD PTR SS:[EBP-0x14]
		FLD DWORD PTR DS:[SkillSwitchDrawMW]
		FSTP DWORD PTR SS:[EBP-0x24]
		jmp [SkillSwitchDraw_buff]
	}
}
__declspec(naked) void SkillSwitchClick()
{
	static float SkillSwitchDrawX = 385.0f;
	static float SkillSwitchDrawY = 380.0f;
	static float SkillSwitchDrawW = 32.0f;
	static float SkillSwitchDrawH = 38.0f;
	static float SkillSwitchDrawMW = 385.0f;
	static DWORD SkillSwitchClick_buff = 0x00812C19;
	_asm
	{
		FLD DWORD PTR DS:[SkillSwitchDrawX]
		FSTP DWORD PTR SS:[EBP-0x8]
		FLD DWORD PTR DS:[SkillSwitchDrawY]
		FSTP DWORD PTR SS:[EBP-0x4]
		FLD DWORD PTR DS:[SkillSwitchDrawW]
		FSTP DWORD PTR SS:[EBP-0x20]
		FLD DWORD PTR DS:[SkillSwitchDrawH]
		FSTP DWORD PTR SS:[EBP-0x1C]
		FLD DWORD PTR DS:[SkillSwitchDrawMW]
		FSTP DWORD PTR SS:[EBP-0x14]
		jmp [SkillSwitchClick_buff]
	}
}
__declspec(naked) void SkillBarra()
{
	static float SkillBarraX = 307.0f;
	static float SkillBarraY = 436.5f;
	static float SkillBarraW = 20.0f;
	static float SkillBarraH = 32.0f;
	static DWORD SkillBarra_buff = 0x0081379A;
	_asm
	{	
	FLD DWORD PTR DS:[SkillBarraX]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[SkillBarraY]
	FSTP DWORD PTR SS:[EBP-0x4]
	FLD DWORD PTR DS:[SkillBarraW]
	FSTP DWORD PTR SS:[EBP-0x18]
	FLD DWORD PTR DS:[SkillBarraH]
	FSTP DWORD PTR SS:[EBP-0x14]
	jmp [SkillBarra_buff]
	}
}
__declspec(naked) void QPosition1()
{
	static float BarNumberY = 455.0f;
	static DWORD QPosition1_buff = 0x008958FF;
	_asm
	{
	FLD DWORD PTR DS:[BarNumberY]
	FSTP DWORD PTR SS:[ESP]
	jmp [QPosition1_buff]
	}
}
__declspec(naked) void QPosition2()
{
	static float QPosition2X = 222.0f;
	static DWORD QPosition2_buff = 0x00895909;
	_asm
	{
	FLD DWORD PTR DS:[QPosition2X]
	FSTP DWORD PTR SS:[ESP]
	jmp [QPosition2_buff]
	}
}
__declspec(naked) void QPosition3()
{
	static float BarPotionY = 446.0f;
	static DWORD QPosition3_buff = 0x00895913;
	_asm
	{
	FLD DWORD PTR DS:[BarPotionY]
	FSTP DWORD PTR SS:[ESP]
	jmp [QPosition3_buff]
	}
}
__declspec(naked) void QPosition4()
{
	static float QPosition4X = 204.0f;
	static DWORD QPosition4_buff = 0x0089591D;
	_asm
	{
	FLD DWORD PTR DS:[QPosition4X]
	FSTP DWORD PTR SS:[ESP]
	jmp [QPosition4_buff]
	}
}
__declspec(naked) void WPosition1()
{
	static float BarNumberY = 455.0f;
	static DWORD WPosition1_buff = 0x00895974;
	_asm
	{
	FLD DWORD PTR DS:[BarNumberY]
	FSTP DWORD PTR SS:[ESP]
	jmp [WPosition1_buff]
	}
}
__declspec(naked) void WPosition2()
{
	static float WPosition2X = 249.0f;
	static DWORD WPosition2_buff = 0x0089597E;
	_asm
	{
	FLD DWORD PTR DS:[WPosition2X]
	FSTP DWORD PTR SS:[ESP]
	jmp [WPosition2_buff]
	}
}
__declspec(naked) void WPosition3()
{
	static float BarPotionY = 446.0f;
	static DWORD WPosition3_buff = 0x00895988;
	_asm
	{
	FLD DWORD PTR DS:[BarPotionY]
	FSTP DWORD PTR SS:[ESP]
	jmp [WPosition3_buff]
	}
}
__declspec(naked) void WPosition4()
{
	static float WPosition4X = 231.0f;
	static DWORD WPosition4_buff = 0x00895992;
	_asm
	{
	FLD DWORD PTR DS:[WPosition4X]
	FSTP DWORD PTR SS:[ESP]
	jmp [WPosition4_buff]
	}
}
__declspec(naked) void EPosition1()
{
	static float BarNumberY = 455.0f;
	static DWORD EPosition1_buff = 0x008959E9;
	_asm
	{
	FLD DWORD PTR DS:[BarNumberY]
	FSTP DWORD PTR SS:[ESP]
	jmp [EPosition1_buff]
	}
}
__declspec(naked) void EPosition2()
{
	static float EPosition2X = 275.0f;
	static DWORD EPosition2_buff = 0x008959F3;
	_asm
	{
	FLD DWORD PTR DS:[EPosition2X]
	FSTP DWORD PTR SS:[ESP]
	jmp [EPosition2_buff]
	}
}
__declspec(naked) void EPosition3()
{
	static float BarPotionY = 446.0f;
	static DWORD EPosition3_buff = 0x008959FD;
	_asm
	{
	FLD DWORD PTR DS:[BarPotionY]
	FSTP DWORD PTR SS:[ESP]
	jmp [EPosition3_buff]
	}
}
__declspec(naked) void EPosition4()
{
	static float EPosition4X = 257.0f;
	static DWORD EPosition4_buff = 0x00895A07;
	_asm
	{
	FLD DWORD PTR DS:[EPosition4X]
	FSTP DWORD PTR SS:[ESP]
	jmp [EPosition4_buff]
	}
}
_declspec(naked) void RPosition1()
{
	static float BarNumberY = 455.0f;
	static DWORD EPosition1_buff = 0x00895BAE;
	_asm
	{
	FLD DWORD PTR DS:[BarNumberY]
	FSTP DWORD PTR SS:[ESP]
	jmp [EPosition1_buff]
	}
}
__declspec(naked) void RPosition2()
{
	static float RPosition2X = 301.0f;
	static DWORD RPosition2_buff = 0x00895BB8;
	_asm
	{
	FLD DWORD PTR DS:[RPosition2X]
	FSTP DWORD PTR SS:[ESP]
	jmp [RPosition2_buff]
	}
}
__declspec(naked) void RPosition3()
{
	static float BarPotionY = 446.0f;
	static DWORD RPosition3_buff = 0x00895BC2;
	_asm
	{
	FLD DWORD PTR DS:[BarPotionY]
	FSTP DWORD PTR SS:[ESP]
	jmp [RPosition3_buff]
	}
}
__declspec(naked) void RPosition4()
{
	static float RPosition4X = 283.0f;
	static DWORD RPosition4_buff = 0x00895BCC;
	_asm
	{
	FLD DWORD PTR DS:[RPosition4X]
	FSTP DWORD PTR SS:[ESP]
	jmp [RPosition4_buff]
	}
}

__declspec(naked) void AGNumberPosition()
{
	static float AGNumberPositionX = 35.0f;
	static DWORD AGNumberPosition_buff = 0x0081037F;
	_asm
	{
	FADD DWORD PTR DS:[AGNumberPositionX]
	FSTP DWORD PTR SS:[EBP-0x154]
	FLD DWORD PTR SS:[EBP-0x154]
	jmp [AGNumberPosition_buff]
	}
}

__declspec(naked) void SDNumberPosition()
{
	static float SDNumberPositionX = 35.0f;
	static DWORD SDNumberPosition_buff = 0x0081064F;
	_asm
	{
	FADD DWORD PTR DS:[SDNumberPositionX]
	FSTP DWORD PTR SS:[EBP-0x154]
	FLD DWORD PTR SS:[EBP-0x154]
	jmp [SDNumberPosition_buff]
	}
}

__declspec(naked) void HPNumberPosition()
{
	static float HPNumberPositionX = 30.0f;
	static DWORD HPNumberPosition_buff = 0x0080FDCE;
	_asm
	{
	FADD DWORD PTR DS:[HPNumberPositionX]
	FSTP DWORD PTR SS:[EBP-0x19C]
	FLD DWORD PTR SS:[EBP-0x19C]
	jmp [HPNumberPosition_buff]
	}
}

__declspec(naked) void HPNumberPosition2()
{
	static float HPNumberPositionY = 450.0f;
	static DWORD HPNumberPosition2_buff = 0x0080FF0F;
	_asm
	{	
	FLD DWORD PTR DS:[HPNumberPositionY]
	FSTP DWORD PTR SS:[ESP]
	FLD DWORD PTR SS:[EBP-0xC]
	jmp [HPNumberPosition2_buff]
	}
}

__declspec(naked) void MANANumberPosition()
{
	static float MANANumberPositionX = 25.0f;
	static DWORD MANANumberPosition_buff = 0x008100B1;
	_asm
	{
	FADD DWORD PTR DS:[MANANumberPositionX]
	FSTP DWORD PTR SS:[EBP-0x1AC]
	FLD DWORD PTR SS:[EBP-0x1AC]
	jmp [MANANumberPosition_buff]
	}
}
//EXP
__declspec(naked) void EXP1()
{
	static float EXP1 = 92.0f;
	static DWORD EXP1_buff = 0x008113E4;
	_asm
	{
	FLD DWORD PTR DS:[EXP1]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXP1_buff]
	}
}

__declspec(naked) void EXP2()
{
	static float EXP2 = 92.0f;
	static DWORD EXP2_buff = 0x0081152E;
	_asm
	{
	FLD DWORD PTR DS:[EXP2]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXP2_buff]
	}
}

__declspec(naked) void EXP3()
{
	static float EXP3 = 92.0f;
	static DWORD EXP3_buff = 0x008116F5;
	_asm
	{
	FLD DWORD PTR DS:[EXP3]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXP3_buff]
	}
}

__declspec(naked) void EXP4()
{
	static float EXP4 = 92.0f;
	static DWORD EXP4_buff = 0x008117FE;
	_asm
	{
	FLD DWORD PTR DS:[EXP4]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXP4_buff]
	}
}

//EXP MASTER
__declspec(naked) void EXPMASTER1()
{
	static float EXPMASTER1 = 92.0f;
	static DWORD EXPMASTER1_buff = 0x00810B4D;
	_asm
	{
	FLD DWORD PTR DS:[EXPMASTER1]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXPMASTER1_buff]
	}
}

__declspec(naked) void EXPMASTER2()
{
	static float EXPMASTER2 = 92.0f;
	static DWORD EXPMASTER2_buff = 0x00810C91;
	_asm
	{
	FLD DWORD PTR DS:[EXPMASTER2]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXPMASTER2_buff]
	}
}

__declspec(naked) void EXPMASTER3()
{
	static float EXPMASTER3 = 92.0f;
	static DWORD EXPMASTER3_buff = 0x00810E58;
	_asm
	{
	FLD DWORD PTR DS:[EXPMASTER3]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXPMASTER3_buff]
	}
}

__declspec(naked) void EXPMASTER4()
{
	static float EXPMASTER4 = 92.0f;
	static DWORD EXPMASTER4_buff = 0x00810F55;
	_asm
	{
	FLD DWORD PTR DS:[EXPMASTER4]
	FSTP QWORD PTR SS:[EBP-0x10]
	jmp [EXPMASTER4_buff]
	}
}

__declspec(naked) void SDScale()
{
	static DWORD SDScale_buff = 0x008105F9;
	static double Alto = 16.0f;
	static double Ancho = 64.0f;
	_asm
	{
	FMUL DWORD PTR SS:[EBP-0x1C]
	FDIV QWORD PTR DS:[Alto]
	FSTP DWORD PTR SS:[EBP-0x148]
	FLD DWORD PTR SS:[EBP-0x148]
	PUSH ECX
	FSTP DWORD PTR SS:[ESP]
	FLD DWORD PTR SS:[EBP-0x20]
	FDIV QWORD PTR DS:[Ancho]
	FSTP DWORD PTR SS:[EBP-0x14C]
	FLD DWORD PTR SS:[EBP-0x14C]
	PUSH ECX
	FSTP DWORD PTR SS:[ESP]
	FLD DWORD PTR SS:[EBP-0x8]
	FMUL DWORD PTR SS:[EBP-0x1C]
	FDIV QWORD PTR DS:[Alto]
	FSTP DWORD PTR SS:[EBP-0x150]
	FLD DWORD PTR SS:[EBP-0x150]
	jmp [SDScale_buff]
	}
}

__declspec(naked) void AGScale()
{
	static DWORD AGScale_buff = 0x00810329;
	static double Alto = 16.0f;
	static double Ancho = 64.0f;
	_asm
	{
	FMUL DWORD PTR SS:[EBP-0x14]
	FDIV QWORD PTR DS:[Alto]
	FSTP DWORD PTR SS:[EBP-0x148]
	FLD DWORD PTR SS:[EBP-0x148]
	PUSH ECX
	FSTP DWORD PTR SS:[ESP]
	FLD DWORD PTR SS:[EBP-0x18]
	FDIV QWORD PTR DS:[Ancho]
	FSTP DWORD PTR SS:[EBP-0x14C]
	FLD DWORD PTR SS:[EBP-0x14C]
	PUSH ECX
	FSTP DWORD PTR SS:[ESP]
	FLD DWORD PTR SS:[EBP-0x8]
	FMUL DWORD PTR SS:[EBP-0x14]
	FDIV QWORD PTR DS:[Alto]
	FSTP DWORD PTR SS:[EBP-0x150]
	FLD DWORD PTR SS:[EBP-0x150]
	jmp [AGScale_buff]
	}
}

void InitInterEx()
{
//    SetRange((LPVOID)0x0080F270, 0x4D1, ASM::NOP);//-> Interface -> Draw Button
//	//-
//	SetRange((LPVOID)0x0081028C, 0x24, ASM::NOP);
//	SetOp((LPVOID)0x0081028C, (LPVOID)AGPosition, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x0081055C, 0x24, ASM::NOP);
//	SetOp((LPVOID)0x0081055C, (LPVOID)SDPosition, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x0080FFAF, 0x24, ASM::NOP);
//	SetOp((LPVOID)0x0080FFAF, (LPVOID)MANAPosition, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x0080FD5B, 0x24, ASM::NOP);
//	SetOp((LPVOID)0x0080FD5B, (LPVOID)HPPosition, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x008138DF, 0x24, ASM::NOP);
//	SetOp((LPVOID)0x008138DF, (LPVOID)UsingSkillPosition, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00812713, 0x24, ASM::NOP);
//	SetOp((LPVOID)0x00812713, (LPVOID)SkillClickPosition, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00812947, 0x24, ASM::NOP);
//	SetOp((LPVOID)0x00812947, (LPVOID)SkillBarDrawPosition, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x008139A0, 0x2D, ASM::NOP);
//	SetOp((LPVOID)0x008139A0, (LPVOID)SkillSwitchDraw, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00812D3F, 0x2D, ASM::NOP);
//	SetOp((LPVOID)0x00812D3F, (LPVOID)SkillSwitchClick, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00813779, 0x24, ASM::NOP);
//	SetOp((LPVOID)0x00813779, (LPVOID)SkillBarra, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00810373, 0x12, ASM::NOP);
//	SetOp((LPVOID)0x00810373, (LPVOID)AGNumberPosition, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00810643, 0x12, ASM::NOP);
//	SetOp((LPVOID)0x00810643, (LPVOID)SDNumberPosition, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x0080FF12, 0x12, ASM::NOP);
//	SetOp((LPVOID)0x0080FF12, (LPVOID)HPNumberPosition, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00810B50, 0x12, ASM::NOP);
//	SetOp((LPVOID)0x00810B50, (LPVOID)MANANumberPosition, ASM::JMP);
//	//->Q
//	SetRange((LPVOID)0x00895A49, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895A49, (LPVOID)QPosition1, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00895A53, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895A53, (LPVOID)QPosition2, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00895A5D, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895A5D, (LPVOID)QPosition3, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00895A67, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895A67, (LPVOID)QPosition4, ASM::JMP);
//	//->W
//	SetRange((LPVOID)0x00895ABE, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895ABE, (LPVOID)WPosition1, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00895AC8, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895AC8, (LPVOID)WPosition2, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00895AD2, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895AD2, (LPVOID)WPosition3, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00895ADC, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895ADC, (LPVOID)WPosition4, ASM::JMP);
//	//-
//	//->E
//	SetRange((LPVOID)0x00895B33, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895B33, (LPVOID)EPosition1, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00895B3D, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895B3D, (LPVOID)EPosition2, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00895B47, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895B47, (LPVOID)EPosition3, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00895B51, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895B51, (LPVOID)EPosition4, ASM::JMP);
//	//-R
//	SetRange((LPVOID)0x00895BA8, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895BA8, (LPVOID)RPosition1, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00895BB2, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895BB2, (LPVOID)RPosition2, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00895BBC, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895BBC, (LPVOID)RPosition3, ASM::JMP);
//	//-
//	SetRange((LPVOID)0x00895BC6, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00895BC6, (LPVOID)RPosition4, ASM::JMP);
////EXP
//	SetRange((LPVOID)0x008113DE, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x008113DE, (LPVOID)EXP1, ASM::JMP);
//	SetRange((LPVOID)0x00811528, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00811528, (LPVOID)EXP2, ASM::JMP);
//	SetRange((LPVOID)0x008116EF, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x008116EF, (LPVOID)EXP3, ASM::JMP);
//	SetRange((LPVOID)0x008117F8, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x008117F8, (LPVOID)EXP4, ASM::JMP);
//
////EXPMASTER
//	SetRange((LPVOID)0x00810B47, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00810B47, (LPVOID)EXPMASTER1, ASM::JMP);
//	SetRange((LPVOID)0x00810C8B, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00810C8B, (LPVOID)EXPMASTER2, ASM::JMP);
//	SetRange((LPVOID)0x00810E52, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00810E52, (LPVOID)EXPMASTER3, ASM::JMP);
//	SetRange((LPVOID)0x00810F4F, 0x9, ASM::NOP);
//	SetOp((LPVOID)0x00810F4F, (LPVOID)EXPMASTER4, ASM::JMP);
//
////Posicion Numero HPMANAetc
//	SetFloat((PVOID)(0x00D461A4), 430);
////Posicion Exp
//	SetDouble((PVOID)(0x00D461C8), 450);
////Posicion Numero Exp
//	SetDouble((PVOID)(0x00D461C0), 572);
////Tamaño numeros general (Prueba)
//	SetDouble((PVOID)(0x00D27AF8), 0.400000011920929);
//
//	SetRange((LPVOID)0x008105AF, 5, ASM::NOP);
//	//SetJmp((LPVOID)0x008105AF, SDScale);
//	SetOp((LPVOID)0x008105AF, SDScale, ASM::JMP);
//	
//	SetRange((LPVOID)0x008102DF, 5, ASM::NOP);
//	//SetJmp((LPVOID)0x008102DF, AGScale);
//	SetOp((LPVOID)0x008102DF, AGScale, ASM::JMP);

	SetDword((LPVOID)(0x004D9746+3),480);

    SetRange((LPVOID)0x0080F120, 0x4D1, ASM::NOP);//-> Interface -> Draw Button
	//-
	SetRange((LPVOID)0x0081013C, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0081013C, (LPVOID)AGPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0081040C, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0081040C, (LPVOID)SDPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0080FE5F, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0080FE5F, (LPVOID)MANAPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0080FC0B, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0080FC0B, (LPVOID)HPPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0081378F, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0081378F, (LPVOID)UsingSkillPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x008125C3, 0x24, ASM::NOP);
	SetOp((LPVOID)0x008125C3, (LPVOID)SkillClickPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x008127F7, 0x24, ASM::NOP);
	SetOp((LPVOID)0x008127F7, (LPVOID)SkillBarDrawPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x00813850, 0x2D, ASM::NOP);
	SetOp((LPVOID)0x00813850, (LPVOID)SkillSwitchDraw, ASM::JMP);
	//-
	SetRange((LPVOID)0x00812BEF, 0x2D, ASM::NOP);
	SetOp((LPVOID)0x00812BEF, (LPVOID)SkillSwitchClick, ASM::JMP);
	//-
	//SetRange((LPVOID)0x00813779, 0x24, ASM::NOP);
	//SetOp((LPVOID)0x00813779, (LPVOID)SkillBarra, ASM::JMP);
	//-
	//SetRange((LPVOID)0x00810373, 0x12, ASM::NOP);
	//SetOp((LPVOID)0x00810373, (LPVOID)AGNumberPosition, ASM::JMP);
	//-
	//SetRange((LPVOID)0x00810643, 0x12, ASM::NOP);
	//SetOp((LPVOID)0x00810643, (LPVOID)SDNumberPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0080FDC2, 0x12, ASM::NOP);
	SetOp((LPVOID)0x0080FDC2, (LPVOID)HPNumberPosition, ASM::JMP);
	//-
	//SetRange((LPVOID)0x00810B50, 0x12, ASM::NOP);
	//SetOp((LPVOID)0x00810B50, (LPVOID)MANANumberPosition, ASM::JMP);
	//->Q
	SetRange((LPVOID)0x008958F9, 0x9, ASM::NOP);
	SetOp((LPVOID)0x008958F9, (LPVOID)QPosition1, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895903, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895903, (LPVOID)QPosition2, ASM::JMP);
	//-
	SetRange((LPVOID)0x0089590D, 0x9, ASM::NOP);
	SetOp((LPVOID)0x0089590D, (LPVOID)QPosition3, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895917, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895917, (LPVOID)QPosition4, ASM::JMP);
	//->W
	SetRange((LPVOID)0x0089596E, 0x9, ASM::NOP);
	SetOp((LPVOID)0x0089596E, (LPVOID)WPosition1, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895978, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895978, (LPVOID)WPosition2, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895982, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895982, (LPVOID)WPosition3, ASM::JMP);
	//-
	SetRange((LPVOID)0x0089598C, 0x9, ASM::NOP);
	SetOp((LPVOID)0x0089598C, (LPVOID)WPosition4, ASM::JMP);
	//-
	//->E
	SetRange((LPVOID)0x008959E3, 0x9, ASM::NOP);
	SetOp((LPVOID)0x008959E3, (LPVOID)EPosition1, ASM::JMP);
	//-
	SetRange((LPVOID)0x008959ED, 0x9, ASM::NOP);
	SetOp((LPVOID)0x008959ED, (LPVOID)EPosition2, ASM::JMP);
	//-
	SetRange((LPVOID)0x008959F7, 0x9, ASM::NOP);
	SetOp((LPVOID)0x008959F7, (LPVOID)EPosition3, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895A01, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895A01, (LPVOID)EPosition4, ASM::JMP);
	//-R
	//SetRange((LPVOID)0x00895BA8, 0x9, ASM::NOP);
	//SetOp((LPVOID)0x00895BA8, (LPVOID)RPosition1, ASM::JMP);
	//-
	//SetRange((LPVOID)0x00895BB2, 0x9, ASM::NOP);
	//SetOp((LPVOID)0x00895BB2, (LPVOID)RPosition2, ASM::JMP);
	//-
	//SetRange((LPVOID)0x00895BBC, 0x9, ASM::NOP);
	//SetOp((LPVOID)0x00895BBC, (LPVOID)RPosition3, ASM::JMP);
	//-
	//SetRange((LPVOID)0x00895BC6, 0x9, ASM::NOP);
	//SetOp((LPVOID)0x00895BC6, (LPVOID)RPosition4, ASM::JMP);

	return;

//EXP
	SetRange((LPVOID)0x008113DE, 0x9, ASM::NOP);
	SetOp((LPVOID)0x008113DE, (LPVOID)EXP1, ASM::JMP);
	SetRange((LPVOID)0x00811528, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00811528, (LPVOID)EXP2, ASM::JMP);
	SetRange((LPVOID)0x008116EF, 0x9, ASM::NOP);
	SetOp((LPVOID)0x008116EF, (LPVOID)EXP3, ASM::JMP);
	SetRange((LPVOID)0x008117F8, 0x9, ASM::NOP);
	SetOp((LPVOID)0x008117F8, (LPVOID)EXP4, ASM::JMP);

//EXPMASTER
	SetRange((LPVOID)0x00810B47, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00810B47, (LPVOID)EXPMASTER1, ASM::JMP);
	SetRange((LPVOID)0x00810C8B, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00810C8B, (LPVOID)EXPMASTER2, ASM::JMP);
	SetRange((LPVOID)0x00810E52, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00810E52, (LPVOID)EXPMASTER3, ASM::JMP);
	SetRange((LPVOID)0x00810F4F, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00810F4F, (LPVOID)EXPMASTER4, ASM::JMP);

//Posicion Numero HPMANAetc
	SetFloat((PVOID)(0x00D461A4), 430);
//Posicion Exp
	SetDouble((PVOID)(0x00D461C8), 450);
//Posicion Numero Exp
	SetDouble((PVOID)(0x00D461C0), 572);
//Tamaño numeros general (Prueba)
	SetDouble((PVOID)(0x00D27AF8), 0.400000011920929);

	SetRange((LPVOID)0x008105AF, 5, ASM::NOP);
	//SetJmp((LPVOID)0x008105AF, SDScale);
	SetOp((LPVOID)0x008105AF, SDScale, ASM::JMP);
	
	SetRange((LPVOID)0x008102DF, 5, ASM::NOP);
	//SetJmp((LPVOID)0x008102DF, AGScale);
	SetOp((LPVOID)0x008102DF, AGScale, ASM::JMP);
}

#endif