#include "stdafx.h"
#include "Object.h"
#include "User.h"
#include "TMemory.h"
#include "ExLicense.h"
#include "Configs.h"

#define EVOMU	TRUE

// --------------------------------------------------------------------------------------------	
//		Attack Speed
// --------------------------------------------------------------------------------------------	

static DWORD ATTACK_RET = 0x00550A16;
static WORD CLASS = 0;
static WORD STR_SPEED = 0;
static WORD MAG_SPEED = 0;

__declspec(naked) void FixAttackSpeed()
{
	_asm
	{
		MOV EAX,DWORD PTR DS:[0x8128AC8]
		MOVZX ECX,WORD PTR DS:[EAX+0xB]
		MOV CLASS,CX
		MOVZX ECX,WORD PTR DS:[EAX+0x54]
		MOV STR_SPEED,CX
		MOVZX ECX,WORD PTR DS:[EAX+0x60]
		MOV MAG_SPEED,CX
	}
	// --------------------------------------------

	gObjUser.MagickAttack = gObjUser.GetActiveSkill();

	// --------------------------------------------	
	// -> Dark Knight

	if( CLASS == DarkKnight || CLASS == BladeKnight || CLASS == BladeMaster )
	{
		if(STR_SPEED > 3000)
		{
			STR_SPEED = 3000;
		}
	}

	// --------------------------------------------	
	// -> Dark Wizard

	if( CLASS == DarkWizard || CLASS == SoulMaster || CLASS == GrandMaster )
	{
		if( gObjUser.MagickAttack == SKILL_EVIL ||
			
#if(EVOMU==TRUE)
			gObjUser.MagickAttack == 8	||
			gObjUser.MagickAttack == 13	||
			gObjUser.MagickAttack == 38 ||
			gObjUser.MagickAttack == 39 ||
#endif
			gObjUser.MagickAttack == SKILL_FLAME	||
			//Master skills
			gObjUser.MagickAttack == 385	||	
			gObjUser.MagickAttack == 382	||	
			gObjUser.MagickAttack == 387	)
		{
			if(MAG_SPEED > 450 && MAG_SPEED < 480)
			{
				MAG_SPEED = 450;
			}
			else if(MAG_SPEED > 600 && MAG_SPEED < 690)
			{
				MAG_SPEED = 600;
			}
			else if(MAG_SPEED > 850 && MAG_SPEED < 1105)
			{
				MAG_SPEED = 850;
			}
			else if(MAG_SPEED > 1350 && MAG_SPEED < 2355)
			{
				MAG_SPEED = 1350;
			}
			else if(MAG_SPEED > 2850)
			{
				MAG_SPEED = 2850;
			}
		}
		else if(gObjUser.MagickAttack == SKILL_INFERNO	||
				gObjUser.MagickAttack == 381)
		{
			if(MAG_SPEED > 3276)
			{
				MAG_SPEED = 3276;
			}
		}
	}

	// --------------------------------------------	
	// -> Elf

	if( CLASS == Elf || CLASS == MuseElf || CLASS == HightElf )
	{
		if(gObjUser.MagickAttack == SKILL_CROSSBOW ||	/*
		 gObjUser.MagickAttack == 490 ||
		   gObjUser.MagickAttack == 491 ||
		   gObjUser.MagickAttack == 492 ||
		   gObjUser.MagickAttack == 493 ||
		   gObjUser.MagickAttack == 494 */
		   
		   //Master Skills 6.2
		   gObjUser.MagickAttack == 414 ||
		   gObjUser.MagickAttack == 418
		   )
		{
			if(STR_SPEED > 508 && STR_SPEED < 550)
			{
				STR_SPEED = 508;
			}
			else if (STR_SPEED > 799 && STR_SPEED < 1150)
			{
				STR_SPEED = 799;
			}
		}
#if(EVOMU==TRUE)
		else if(gObjUser.MagickAttack == 52	||
				gObjUser.MagickAttack == 51 ||
				//Master Skills 6.2
				gObjUser.MagickAttack == 416	||
				gObjUser.MagickAttack == 424)
		{
			if(STR_SPEED > 500)
			{
				STR_SPEED = 500;
			}
		}
#endif
	}

	// --------------------------------------------	
	// -> Magic Gladiator

	if( CLASS == MagicGladiator || CLASS == DuelMaster )
	{
		if( gObjUser.MagickAttack == 55 ||
			gObjUser.MagickAttack == 490 ||
			//Master Skills 6.2
			gObjUser.MagickAttack == 492
			)
		{
			if(STR_SPEED > 1368)
			{
				STR_SPEED = 1368;
			}
		}
		if( gObjUser.MagickAttack == SKILL_EVIL ||
#if(EVOMU==TRUE)
			gObjUser.MagickAttack == 8	||
			gObjUser.MagickAttack == 13	||
#endif
			gObjUser.MagickAttack == SKILL_FLAME	||
			//Master Skills 6.2
			gObjUser.MagickAttack == 487		||	
			gObjUser.MagickAttack == 484	
			)
		{
			if(MAG_SPEED > 450 && MAG_SPEED < 480)
			{
				MAG_SPEED = 450;
			}
			else if(MAG_SPEED > 600 && MAG_SPEED < 690)
			{
				MAG_SPEED = 600;
			}
			else if(MAG_SPEED > 850 && MAG_SPEED < 1105)
			{
				MAG_SPEED = 850;
			}
			else if(MAG_SPEED > 1350 && MAG_SPEED < 2355)
			{
				MAG_SPEED = 1350;
			}
			else if(MAG_SPEED > 2850)
			{
				MAG_SPEED = 2850;
			}
		}
		if(gObjUser.MagickAttack == SKILL_INFERNO	||
			//Master Skills 6.2
			gObjUser.MagickAttack == 486	)
		{
			if(MAG_SPEED > 3276)
			{
				MAG_SPEED = 3276;
			}
		}

		if(gObjUser.MagickAttack == 56)
		{
			if(STR_SPEED > 1368 && STR_SPEED < 1368)
			{
				STR_SPEED = 1368;
			}
		}
	}

	// --------------------------------------------	
	// -> Dark Lord

	if( CLASS == DarkLord || CLASS == LordEmperor)
	{
		if(gObjUser.MagickAttack == SKILL_FIRESCREAM ||
			//Master Skills 6.2
		   gObjUser.MagickAttack == 518		||
		   gObjUser.MagickAttack == 520)
		{
			if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal) || 
				g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2))
			{
				if(g_dwDivFireScreamSpeed > 0)
				{
					STR_SPEED = STR_SPEED / g_dwDivFireScreamSpeed;
				}
			}

			if(STR_SPEED > 249 && STR_SPEED < 264)
			{
				STR_SPEED = 249;
			}
			else if(STR_SPEED > 324 && STR_SPEED < 367)
			{
				STR_SPEED = 324;
			}
			else if(STR_SPEED > 449 && STR_SPEED < 575)
			{
				STR_SPEED = 449;
			}
			else if(STR_SPEED > 699 && STR_SPEED < 1200)
			{
				STR_SPEED = 699;
			}
			else if(STR_SPEED > 1449)
			{
				STR_SPEED = 1449;
			}
			//if(STR_SPEED > 249 && STR_SPEED < 264)
			//{
			//	STR_SPEED = 249;
			//}
			//else if(STR_SPEED > 324 && STR_SPEED < 367)
			//{
			//	STR_SPEED = 324;
			//}
			//else if(STR_SPEED > 449 && STR_SPEED < 575)
			//{
			//	STR_SPEED = 449;
			//}
			//else if(STR_SPEED > 699 && STR_SPEED < 1200)
			//{
			//	STR_SPEED = 699;
			//}
			//else if(STR_SPEED > 1449)
			//{
			//	STR_SPEED = 1449;
			//}
		}
	}

	// --------------------------------------------	
	// -> Rage Fighter

	if( CLASS == Monk || CLASS == 22/*FirstMaster*/ )
	{
		if( gObjUser.MagickAttack == 261 || 
			gObjUser.MagickAttack == 490 || 
			gObjUser.MagickAttack == 265 ||
			//Master Skills 6.2
			gObjUser.MagickAttack == 555 ||
			gObjUser.MagickAttack == 552
			)
		{
			if(STR_SPEED > 4476)
			{
				STR_SPEED = 4476;
			}
			else if(STR_SPEED > 754 && STR_SPEED < 1087)
			{
				STR_SPEED = 754;
			}
		}
	}

	// --------------------------------------------

	_asm
	{
		//MOV EAX,DWORD PTR DS:[0x8128AC8]
		MOVZX ECX,WORD PTR DS:[STR_SPEED]
		MOV DWORD PTR SS:[EBP-0x28],ECX
		FILD DWORD PTR SS:[EBP-0x28]
		FMUL QWORD PTR DS:[0x0D27C88]              ; FLOAT 0.004000000189989805
		FSTP DWORD PTR SS:[EBP-0x10]
		//MOV EDX,DWORD PTR DS:[0x8128AC8]
		MOVZX EAX,WORD PTR DS:[MAG_SPEED]
		MOV DWORD PTR SS:[EBP-0x2C],EAX
		FILD DWORD PTR SS:[EBP-0x2C]
		FMUL QWORD PTR DS:[0x0D27C88]              ; FLOAT 0.004000000189989805
		FSTP DWORD PTR SS:[EBP-0x0C]
		//MOV ECX,DWORD PTR DS:[0x8128AC8]
		MOVZX EDX,WORD PTR DS:[MAG_SPEED]
		MOV DWORD PTR SS:[EBP-0x30],EDX
		FILD DWORD PTR SS:[EBP-0x30]
		FMUL QWORD PTR DS:[0x0D281C0]              ; FLOAT 0.002000000094994903
		FSTP DWORD PTR SS:[EBP-0x4]
		FLD DWORD PTR SS:[EBP-0x10]

		JMP ATTACK_RET
	}
}
// --------------------------------------------------------------------------------------------	

static DWORD RETURN_attack2 = 0x0055157D;

__declspec(naked) void FixAttackSpeed2()
{
	_asm
	{
		MOVZX EDX,WORD PTR DS:[STR_SPEED]
		JMP RETURN_attack2
	}
}
// --------------------------------------------------------------------------------------------	

void InitAttackSpeed()
{
	//SetRange((LPVOID)0x004EC223, 80, ASM::NOP);
	//SetOp((LPVOID)0x004EC223, (LPVOID)FixAttackSpeed, ASM::JMP);

	//SetNop(0x004EC223,80);
	//WriteJmp(0x004EC223 , (DWORD)&FixAttackSpeed);

	SetOp((LPVOID)0x005509CE, (LPVOID)FixAttackSpeed, ASM::JMP);
	SetOp((LPVOID)0x00551573, (LPVOID)FixAttackSpeed2, ASM::JMP);
}
// --------------------------------------------------------------------------------------------	