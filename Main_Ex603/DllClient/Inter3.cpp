#include "stdafx.h"
#include "Inter3.h"
#include "Defines.h"
#include "TMemory.h"
#include "Import.h"
#include "Object.h"
#include "Interface.h"
#include "Configs.h"

#if(DEV_INTERFASE_SEASON3)

__declspec(naked) void AGPosition()
{
	static float AGPositionW = 13.0f;
	static float AGPositionH = 39.0f;
	static float AGPositionX = 552.0f;
	static float AGPositionY = 435.0f;
	static DWORD AGPosition_buff = 0x0081015D; //0081015D  |. D95D F4        FSTP DWORD PTR SS:[EBP-C]


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
	static float SDPositionW = 14.0f;
	static float SDPositionH = 39.0f;
	static float SDPositionX = 73.0f;
	static float SDPositionY = 435.0f;
	static DWORD SDPosition_buff = 0x0081042D; //0081042D  |. D95D F4        FSTP DWORD PTR SS:[EBP-C]
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

__declspec(naked) void SDPositionS1()
{
	static float SDPositionW = 99914.0f;
	static float SDPositionH = 99939.0f;
	static float SDPositionX = 99973.0f;
	static float SDPositionY = 99435.0f;

	static DWORD SDPosition_buff = 0x0081042D; //0081042D  |. D95D F4        FSTP DWORD PTR SS:[EBP-C]
	_asm
	{
		FLD DWORD PTR DS : [SDPositionW]
			FSTP DWORD PTR SS : [EBP - 0x20]
			FLD DWORD PTR DS : [SDPositionH]
			FSTP DWORD PTR SS : [EBP - 0x1C]
			FLD DWORD PTR DS : [SDPositionX]
			FSTP DWORD PTR SS : [EBP - 0x10]
			FLD DWORD PTR DS : [SDPositionY]
			FSTP DWORD PTR SS : [EBP - 0x0C]
			jmp[SDPosition_buff]
	}
}

__declspec(naked) void MANAPosition()
{
	static float MANAPositionW = 52.0f;
	static float MANAPositionX = 489.0f;
	static float MANAPositionH = 48.0f;
	static float MANAPositionY = 429.0f;
	static DWORD MANAPosition_buff = 0x0080FE80; //0080FE80  |. D95D F8        FSTP DWORD PTR SS:[EBP-8]
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
	static float HPPositionW = 52.0f;
	static float HPPositionX = 98.0f;
	static float HPPositionH = 48.0f;
	static float HPPositionY = 429.0f;
	static DWORD HPPosition_buff = 0x0080FC2C; //0080FC2C  |. D95D F8        FSTP DWORD PTR SS:[EBP-8]
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

__declspec(naked) void QPosition1()
{
	static float BarNumberY = 445.0f;
	static DWORD QPosition1_buff = 0x008958FF; //008958FF  |. D91C24         FSTP DWORD PTR SS:[ESP]                  ; |
	_asm
	{
		FLD DWORD PTR DS:[BarNumberY]
			FSTP DWORD PTR SS:[ESP]
			jmp [QPosition1_buff]
	}
}
__declspec(naked) void QPosition2()
{
	static float QPosition2X = 227.0f;
	static DWORD QPosition2_buff = 0x00895909; //00895909  |. D91C24         FSTP DWORD PTR SS:[ESP]                  ; |
	_asm
	{
		FLD DWORD PTR DS:[QPosition2X]
			FSTP DWORD PTR SS:[ESP]
			jmp [QPosition2_buff]
	}
}
__declspec(naked) void QPosition3()
{
	static float BarPotionY = 453.0f;
	static DWORD QPosition3_buff = 0x00895913; //00895913  |. D91C24         FSTP DWORD PTR SS:[ESP]                  ; |
	_asm
	{
		FLD DWORD PTR DS:[BarPotionY]
			FSTP DWORD PTR SS:[ESP]
			jmp [QPosition3_buff]
	}
}
__declspec(naked) void QPosition4()
{
	static float QPosition4X = 210.0f;
	static DWORD QPosition4_buff = 0x0089591D; //0089591D  |. D91C24         FSTP DWORD PTR SS:[ESP]                  ; |
	_asm
	{
		FLD DWORD PTR DS:[QPosition4X]
			FSTP DWORD PTR SS:[ESP]
			jmp [QPosition4_buff]
	}
}
__declspec(naked) void WPosition1()
{
	static float BarNumberY = 445.0f;
	static DWORD WPosition1_buff = 0x00895974; //00895974  |. D91C24         FSTP DWORD PTR SS:[ESP]                  ; |
	_asm
	{
		FLD DWORD PTR DS:[BarNumberY]
			FSTP DWORD PTR SS:[ESP]
			jmp [WPosition1_buff]
	}
}
__declspec(naked) void WPosition2()
{
	static float WPosition2X = 257.0f;
	static DWORD WPosition2_buff = 0x0089597E; //0089597E  |. D91C24         FSTP DWORD PTR SS:[ESP]                  ; |
	_asm
	{
		FLD DWORD PTR DS:[WPosition2X]
			FSTP DWORD PTR SS:[ESP]
			jmp [WPosition2_buff]
	}
}
__declspec(naked) void WPosition3()
{
	static float BarPotionY = 453.0f;
	static DWORD WPosition3_buff = 0x00895988; //00895988  |. D91C24         FSTP DWORD PTR SS:[ESP]                  ; |
	_asm
	{
		FLD DWORD PTR DS:[BarPotionY]
			FSTP DWORD PTR SS:[ESP]
			jmp [WPosition3_buff]
	}
}
__declspec(naked) void WPosition4()
{
	static float WPosition4X = 240.0f;
	static DWORD WPosition4_buff = 0x00895992; //00895992  |. D91C24         FSTP DWORD PTR SS:[ESP]                  ; |
	_asm
	{
		FLD DWORD PTR DS:[WPosition4X]
			FSTP DWORD PTR SS:[ESP]
			jmp [WPosition4_buff]
	}
}
__declspec(naked) void EPosition1()
{
	static float BarNumberY = 445.0f;
	static DWORD EPosition1_buff = 0x008959E9; //008959E9  |. D91C24         FSTP DWORD PTR SS:[ESP]                  ; |
	_asm
	{
		FLD DWORD PTR DS:[BarNumberY]
			FSTP DWORD PTR SS:[ESP]
			jmp [EPosition1_buff]
	}
}
__declspec(naked) void EPosition2()
{
	static float EPosition2X = 287.0f;
	static DWORD EPosition2_buff = 0x008959F3; //008959F3  |. D91C24         FSTP DWORD PTR SS:[ESP]                  ; |
	_asm
	{
		FLD DWORD PTR DS:[EPosition2X]
			FSTP DWORD PTR SS:[ESP]
			jmp [EPosition2_buff]
	}
}
__declspec(naked) void EPosition3()
{
	static float BarPotionY = 453.0f;
	static DWORD EPosition3_buff = 0x008959FD; //008959FD  |. D91C24         FSTP DWORD PTR SS:[ESP]                  ; |
	_asm
	{
		FLD DWORD PTR DS:[BarPotionY]
			FSTP DWORD PTR SS:[ESP]
			jmp [EPosition3_buff]
	}
}
__declspec(naked) void EPosition4()
{
	static float EPosition4X = 270.0f;
	static DWORD EPosition4_buff = 0x00895A07; //00895A07  |. D91C24         FSTP DWORD PTR SS:[ESP]                  ; |
	_asm
	{
		FLD DWORD PTR DS:[EPosition4X]
			FSTP DWORD PTR SS:[ESP]
			jmp [EPosition4_buff]
	}
}
__declspec(naked) void NopRShortKey()
{
	static DWORD RButtonAddress = 0x00895ABC; //00895ABC  |. 8BE5           MOV ESP,EBP
	_asm{jmp RButtonAddress}
}

__declspec(naked) void HPNumberPosition()
{
	static float HPNumberPositionX = 45.0f;
	static DWORD HPNumberPosition_buff = 0x0080FDCE; //0080FDCE  |. D985 64FEFFFF  FLD DWORD PTR SS:[EBP-19C]               ; |
	_asm
	{
		FADD DWORD PTR DS:[HPNumberPositionX]
			FSTP DWORD PTR SS:[EBP-0x19C]
			FLD DWORD PTR SS:[EBP-0x19C]
			jmp [HPNumberPosition_buff]
	}
}
__declspec(naked) void MasterButton()
{
	static DWORD MasterButtonAddress1 = 0x0077EC88; //0077EC88  |> 8BE5           MOV ESP,EBP
	_asm
	{
		jmp [MasterButtonAddress1]
	}
}
__declspec(naked) void HelperAll()
{
	static DWORD HelperStopAddress1 = 0x007D28B4;
	_asm
	{
		jmp [HelperStopAddress1]
	}
}

__declspec(naked) void UsingSkillPosition()
{
	static float UsingSkillPositionX = 311.0f;
	static float UsingSkillPositionY = 448.0f;
	static float UsingSkillPositionW = 20.0f;
	static float UsingSkillPositionH = 28.0f;
	static DWORD UsingSkillPosition_buff = 0x008137B0; // 008137B0  |. D95D EC        FSTP DWORD PTR SS:[EBP-14]
	_asm
	{
		FLD DWORD PTR DS : [UsingSkillPositionX]
			FSTP DWORD PTR SS : [EBP - 0x8]
			FLD DWORD PTR DS : [UsingSkillPositionY]
			FSTP DWORD PTR SS : [EBP - 0x4]
			FLD DWORD PTR DS : [UsingSkillPositionW]
			FSTP DWORD PTR SS : [EBP - 0x18]
			FLD DWORD PTR DS : [UsingSkillPositionH]
			FSTP DWORD PTR SS : [EBP - 0x14]
			jmp[UsingSkillPosition_buff]
	}
}
__declspec(naked) void SkillClickPosition()
{
	static float SkillClickPositionX = 310.0f;
	static float SkillClickPositionY = 431.0f;
	static float SkillClickPositionW = 32.0f;
	static float SkillClickPositionH = 38.0f;
	static DWORD SkillClickPosition_buff = 0x008125E4; //008125E4   . D95D E4        FSTP DWORD PTR SS:[EBP-1C]
	_asm
	{
		FLD DWORD PTR DS : [SkillClickPositionX]
			FSTP DWORD PTR SS : [EBP - 0x8]
			FLD DWORD PTR DS : [SkillClickPositionY]
			FSTP DWORD PTR SS : [EBP - 0x4]
			FLD DWORD PTR DS : [SkillClickPositionW]
			FSTP DWORD PTR SS : [EBP - 0x20]
			FLD DWORD PTR DS : [SkillClickPositionH]
			FSTP DWORD PTR SS : [EBP - 0x1C]
			jmp[SkillClickPosition_buff]
	}
}
__declspec(naked) void SkillBarDrawPosition()
{
	static float SkillBarDrawPositionX = 222.0f;
	static float SkillBarDrawPositionY = 480.0f;
	static float SkillBarDrawPositionW = 160.0f;
	static float SkillBarDrawPositionH = 38.0f;
	static DWORD SkillBarDrawPosition_buff = 0x00812818; //00812818   . D95D E4        FSTP DWORD PTR SS:[EBP-1C]
	_asm
	{
		FLD DWORD PTR DS : [SkillBarDrawPositionX]
			FSTP DWORD PTR SS : [EBP - 0x8]
			FLD DWORD PTR DS : [SkillBarDrawPositionY]
			FSTP DWORD PTR SS : [EBP - 0x4]
			FLD DWORD PTR DS : [SkillBarDrawPositionW]
			FSTP DWORD PTR SS : [EBP - 0x20]
			FLD DWORD PTR DS : [SkillBarDrawPositionH]
			FSTP DWORD PTR SS : [EBP - 0x1C]
			jmp[SkillBarDrawPosition_buff]
	}
}
__declspec(naked) void SkillSwitchDraw()
{
	static float SkillSwitchDrawX = 385.0f;
	static float SkillSwitchDrawY = 380.0f;
	static float SkillSwitchDrawW = 32.0f;
	static float SkillSwitchDrawH = 38.0f;
	static float SkillSwitchDrawMW = 385.0f;
	static DWORD SkillSwitchDraw_buff = 0x0081387A; //0081387A  |. D95D DC        FSTP DWORD PTR SS:[EBP-24]
	_asm
	{
		FLD DWORD PTR DS : [SkillSwitchDrawX]
			FSTP DWORD PTR SS : [EBP - 0x8]
			FLD DWORD PTR DS : [SkillSwitchDrawY]
			FSTP DWORD PTR SS : [EBP - 0x4]
			FLD DWORD PTR DS : [SkillSwitchDrawW]
			FSTP DWORD PTR SS : [EBP - 0x18]
			FLD DWORD PTR DS : [SkillSwitchDrawH]
			FSTP DWORD PTR SS : [EBP - 0x14]
			FLD DWORD PTR DS : [SkillSwitchDrawMW]
			FSTP DWORD PTR SS : [EBP - 0x24]
			jmp[SkillSwitchDraw_buff]
	}
}
__declspec(naked) void SkillSwitchClick()
{
	static float SkillSwitchDrawX = 385.0f;
	static float SkillSwitchDrawY = 380.0f;
	static float SkillSwitchDrawW = 32.0f;
	static float SkillSwitchDrawH = 38.0f;
	static float SkillSwitchDrawMW = 385.0f;
	static DWORD SkillSwitchClick_buff = 0x00812C19; //00812C19   . D95D EC        FSTP DWORD PTR SS:[EBP-14]
	_asm
	{
		FLD DWORD PTR DS : [SkillSwitchDrawX]
			FSTP DWORD PTR SS : [EBP - 0x8]
			FLD DWORD PTR DS : [SkillSwitchDrawY]
			FSTP DWORD PTR SS : [EBP - 0x4]
			FLD DWORD PTR DS : [SkillSwitchDrawW]
			FSTP DWORD PTR SS : [EBP - 0x20]
			FLD DWORD PTR DS : [SkillSwitchDrawH]
			FSTP DWORD PTR SS : [EBP - 0x1C]
			FLD DWORD PTR DS : [SkillSwitchDrawMW]
			FSTP DWORD PTR SS : [EBP - 0x14]
			jmp[SkillSwitchClick_buff]
	}
}

DWORD gLevelExperience[MAX_CHARACTER_LEVEL + 1];

void gObjSetExperienceTable() // OK
{
	gLevelExperience[0] = 0;

	DWORD over = 1;

	for (int n = 1; n <= MAX_CHARACTER_LEVEL; n++)
	{
		gLevelExperience[n] = (((n + 9)*n)*n) * 10;

		if (n > 255)
		{
			gLevelExperience[n] += (((over + 9)*over)*over) * 1000;
			over++;
		}
	}
}


void DrawExpBar()
{

	lpCharObj lpObj = (lpCharObj)oUserObjectStruct;

	if (*(DWORD*)MAIN_SCREEN_STATE == 5)
	{
		double ExpNum;
		glColor3f(1.0f, 1.0f, 0.1f);
		pDrawBarForm(221, 436, 1, 5.0f, 0.0f, 0);
		char buff[255];

		DWORD ReadExp = *(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x10);
		DWORD ReadNextExp = *(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x14);


		QWORD CurrentMasterExp;
		QWORD NextMasterExp;

		if (lpObj->Level >= 400)
		{
			//Level = *(WORD*)0x87935D8;
			NextMasterExp = *(QWORD*)0x87935E8;
			CurrentMasterExp = *(QWORD*)0x87935E0;
		}


		if (lpObj->Level >= 400)
		{
			if (NextMasterExp > 0 && CurrentMasterExp > 0)
			{
				double Exp = ((CurrentMasterExp * 50) / (NextMasterExp + (NextMasterExp - CurrentMasterExp))) % 10;
				ExpNum = Exp;
				Exp = 210.0f / 10.0 * Exp;
				Exp = ((Exp > 199) ? 199 : Exp);
				//glColor4f(0.2, 1.0, 0.2, 1.0);
				pDrawBarForm(221, 436, (float)Exp, 5.0, 0.0f, 0);
				glColor4f(1.0, 1.0, 1.0, 0.24f);
				double ExpForm = Exp + 10;
				ExpForm = ((ExpForm > 200) ? 200 : ExpForm);
				pDrawBarForm(221, 436, (float)ExpForm, 5.0, 0.0, 0);
				ExpNum = ((ExpNum > 9) ? 9 : ExpNum);
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glEnable(GL_TEXTURE_2D);

				if (gInterface.IsWorkZone(221, 436, 200, 5))
				{
					wsprintf(buff, "Exp: %u / %u", CurrentMasterExp, NextMasterExp);
					pDrawToolTip(280, 418, buff);
				}
			}
			else
			{
				ExpNum = 0;
			}
		}
		else
		{
			if (ReadExp > 0 && ReadNextExp > 0)
			{
				DWORD ExpRequired = ReadNextExp - gLevelExperience[lpObj->Level - 1];
				DWORD ExpObaited = ReadExp - gLevelExperience[lpObj->Level - 1];

				double Exp = (ExpObaited * 10) / ExpRequired;
				ExpNum = Exp;
				Exp = ((Exp > 199) ? 199 : Exp);
				pDrawBarForm((float)220 + 1.0f, (float)435 + 1.3, (210.0f / 10.0 * (float)Exp), 4.0, 0.0, 0);
				double ExpForm = Exp;
				ExpForm = ((ExpForm > 200) ? 200 : ExpForm);
				glColor4f(1.0f, 1.0f, 1.0f, 0.20000001f);
				pDrawBarForm((float)220 + 1.0f, (float)435 + 1.3, (210.0f / 10.0 * (float)ExpForm + 10), 4.0, 0.0, 0);
				ExpNum = ((ExpNum > 9) ? 9 : ExpNum);
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glEnable(GL_TEXTURE_2D);
				if (gInterface.IsWorkZone(221, 436, 200, 5))
				{
					wsprintf(buff, "Exp: %u / %u", ReadExp, ReadNextExp);
					pDrawToolTip(280, 418, buff);
				}
			}
			else
			{
				ExpNum = 0;
			}
		}
		glColor3f(1.0f, 1.0f, 0.7f);
		pDrawInterfaceNumBer(425, 432, (int)ExpNum, 1);

		//pGLSwitch();
		//glColor3f(1.0f, 1.0f, 1.0f);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_TEXTURE_2D);
	}
}

void InitInter3()
{

	SetRange((LPVOID)0x0080F120, 0x4D1, ASM::NOP);//-> Interface -> Draw Button 0080F120  /$ 55             PUSH EBP
	//-
	SetByte((PVOID)(0x0081365F + 3), 0); //0081365F  |> 837D F4 05      CMP DWORD PTR SS:[EBP-C],5
	SetByte((PVOID)(0x00811857), 0xEB); //00811857  |. 75 45          JNZ SHORT Main.0081189E
	SetRange((LPVOID)0x00811970, 0xAC, ASM::NOP); //00811970  /$ 55             PUSH EBP
	//-
	SetRange((LPVOID)0x0081378F, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0081378F, (LPVOID)UsingSkillPosition, ASM::JMP); //0081378F  |> D905 C4C2D200  FLD DWORD PTR DS:[D2C2C4]
	//-
	SetRange((LPVOID)0x008125C3, 0x24, ASM::NOP);
	SetOp((LPVOID)0x008125C3, (LPVOID)SkillClickPosition, ASM::JMP); //008125C3   > D905 F061D400  FLD DWORD PTR DS:[D461F0]
	//-
	SetRange((LPVOID)0x008127F7, 0x24, ASM::NOP);
	SetOp((LPVOID)0x008127F7, (LPVOID)SkillBarDrawPosition, ASM::JMP); //008127F7   > D905 6461D400  FLD DWORD PTR DS:[D46164]
	//-
	SetRange((LPVOID)0x00813850, 0x2D, ASM::NOP);
	SetOp((LPVOID)0x00813850, (LPVOID)SkillSwitchDraw, ASM::JMP); //00813850  |. D905 F061D400  FLD DWORD PTR DS:[D461F0]
	//-
	SetRange((LPVOID)0x00812BEF, 0x2D, ASM::NOP);
	SetOp((LPVOID)0x00812BEF, (LPVOID)SkillSwitchClick, ASM::JMP); //00812BEF   . D905 F061D400  FLD DWORD PTR DS:[D461F0]

	//-
	SetRange((LPVOID)0x0081013C, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0081013C, (LPVOID)AGPosition, ASM::JMP); //0081013C  |> D905 A057D200  FLD DWORD PTR DS:[D257A0]
	//-
//	SetRange((LPVOID)0x0081040C, 0x24, ASM::NOP);
//	SetOp((LPVOID)0x0081040C, (LPVOID)SDPosition, ASM::JMP); //0081040C  |> D905 A057D200  FLD DWORD PTR DS:[D257A0]

	if (interCustom == 1)
	{
		SetRange((LPVOID)0x0081040C, 0x24, ASM::NOP);
		SetOp((LPVOID)0x0081040C, (LPVOID)SDPositionS1, ASM::JMP);
	}
	if (interCustom == 2 || interCustom == 3)
	{
		SetRange((LPVOID)0x0081040C, 0x24, ASM::NOP);
		SetOp((LPVOID)0x0081040C, (LPVOID)SDPosition, ASM::JMP);
	}
	//-
	SetRange((LPVOID)0x0080FE5F, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0080FE5F, (LPVOID)MANAPosition, ASM::JMP); //0080FE5F  |> D905 E47AD200  FLD DWORD PTR DS:[D27AE4]
	//-
	SetRange((LPVOID)0x0080FC0B, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0080FC0B, (LPVOID)HPPosition, ASM::JMP); //0080FC0B  |> D905 E47AD200  FLD DWORD PTR DS:[D27AE4]
	//-
	SetRange((LPVOID)0x0080FDC2, 0x12, ASM::NOP);
	SetOp((LPVOID)0x0080FDC2, (LPVOID)HPNumberPosition, ASM::JMP); //0080FDC2  |. DC05 404FD200  FADD QWORD PTR DS:[D24F40]               ; |
	//-
	SetRange((LPVOID)0x0077EB47, 0x88, ASM::NOP);
	SetOp((LPVOID)0x0077EB47, (LPVOID)MasterButton, ASM::JMP); //0077EB47  |. 6A 00          PUSH 0
	//-
	//->Q
	SetRange((LPVOID)0x008958F9, 0x9, ASM::NOP);
	SetOp((LPVOID)0x008958F9, (LPVOID)QPosition1, ASM::JMP); //008958F9  |. D905 CCB2D400  FLD DWORD PTR DS:[D4B2CC]                ; |
	//-
	SetRange((LPVOID)0x00895903, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895903, (LPVOID)QPosition2, ASM::JMP); //00895903  |. D905 8043D200  FLD DWORD PTR DS:[D24380]                ; |
	//-
	SetRange((LPVOID)0x0089590D, 0x9, ASM::NOP);
	SetOp((LPVOID)0x0089590D, (LPVOID)QPosition3, ASM::JMP); //0089590D  |. D905 C8B2D400  FLD DWORD PTR DS:[D4B2C8]                ; |
	//-
	SetRange((LPVOID)0x00895917, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895917, (LPVOID)QPosition4, ASM::JMP); //00895917  |. D905 142CD200  FLD DWORD PTR DS:[D22C14]                ; |
	//->W
	SetRange((LPVOID)0x0089596E, 0x9, ASM::NOP);
	SetOp((LPVOID)0x0089596E, (LPVOID)WPosition1, ASM::JMP); //0089596E  |. D905 CCB2D400  FLD DWORD PTR DS:[D4B2CC]                ; |
	//-
	SetRange((LPVOID)0x00895978, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895978, (LPVOID)WPosition2, ASM::JMP); //00895978  |. D905 D052D400  FLD DWORD PTR DS:[D452D0]                ; |
	//-
	SetRange((LPVOID)0x00895982, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895982, (LPVOID)WPosition3, ASM::JMP); //00895982  |. D905 C8B2D400  FLD DWORD PTR DS:[D4B2C8]                ; |
	//-
	SetRange((LPVOID)0x0089598C, 0x9, ASM::NOP);
	SetOp((LPVOID)0x0089598C, (LPVOID)WPosition4, ASM::JMP); //0089598C  |. D905 0C2CD200  FLD DWORD PTR DS:[D22C0C]                ; |
	//-
	//->E
	SetRange((LPVOID)0x008959E3, 0x9, ASM::NOP);
	SetOp((LPVOID)0x008959E3, (LPVOID)EPosition1, ASM::JMP); //008959E3  |. D905 CCB2D400  FLD DWORD PTR DS:[D4B2CC]                ; |
	//-
	SetRange((LPVOID)0x008959ED, 0x9, ASM::NOP);
	SetOp((LPVOID)0x008959ED, (LPVOID)EPosition2, ASM::JMP); //008959ED  |. D905 C4B2D400  FLD DWORD PTR DS:[D4B2C4]                ; |
	//-
	SetRange((LPVOID)0x008959F7, 0x9, ASM::NOP);
	SetOp((LPVOID)0x008959F7, (LPVOID)EPosition3, ASM::JMP); //008959F7  |. D905 C8B2D400  FLD DWORD PTR DS:[D4B2C8]                ; |
	//-
	SetRange((LPVOID)0x00895A01, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895A01, (LPVOID)EPosition4, ASM::JMP); //00895A01  |. D905 C0B2D400  FLD DWORD PTR DS:[D4B2C0]                ; |
	//-
	//->R
	SetRange((LPVOID)0x00895A3D, 0x7E, ASM::NOP);
	SetOp((LPVOID)0x00895A3D, (LPVOID)NopRShortKey, ASM::JMP); //00895A3D  |. 6A 3C          PUSH 3C

	//SetRange((LPVOID)0x007D2473, 0x2F0, ASM::NOP);
	//SetOp((LPVOID)0x007D2473, (LPVOID)HelperAll, ASM::JMP); //007D2473  |. 6A FF          PUSH -1

	//SetRange((LPVOID)0x008105B0, 0x4D1, ASM::NOP);
	//SetOp((LPVOID)0x00895A3D, (LPVOID)NopRShortKey, ASM::JMP);

	SetCompleteHook(0xE8, 0x0080F715, &DrawExpBar); // 0080F715  |. E8 960E0000    CALL zMain.008105B0

}

#endif