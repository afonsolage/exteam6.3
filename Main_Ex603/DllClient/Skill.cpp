#include "stdafx.h"
#include "Object.h"
#include "Skill.h"
#include "TMemory.h"
#include "Import.h"


//int sub_626190()
#define pLoadSkill			((int(*)())0x626190)	

CSkill g_Skill;

CSkill::CSkill()
{

}
// ----------------------------------------------------------------------------------------------

CSkill::~CSkill()
{

}
// ----------------------------------------------------------------------------------------------

void CSkill::Load()
{

/*
	v92 = v90 + 776;
*/
	
	SetOp((LPVOID)0x00664156, (LPVOID)g_Skill.GCMagicAttack, ASM::CALL);

	SetOp((LPVOID)0x0064667E, (LPVOID)g_Skill.TeleportSkill, ASM::CALL);

	SetOp((LPVOID)0x00633FFB, (LPVOID)this->LoadSkill, ASM::CALL);

	//SetByte((LPVOID)(0x0055F171+1), 0x50);
	//SetByte((LPVOID)(0x0055F171+2), 0xC3);
	//Limit
	//SetByte((LPVOID)(0x00969ADD+3), 0x50);
	//SetByte((LPVOID)(0x00969ADD+4), 0xC3);

}
// ----------------------------------------------------------------------------------------------

//int  sub_614710(signed int a1, int a2, int a3, int a4)
#define sub_614710			((int(__cdecl*)(signed int a1, char *a2, int a3, int a4))0x614710)	

int CSkill::LoadSkill()
{
	//char SkillPath[] = "Data\\Skill\\";
	//pLoadModel(0xC350, SkillPath, "Poison", 1);


  //pLoadModel(502, "Data\\Effect\\", "magic_powerup", -1);
  //pLoadTexture(502, "Effect\\", 10497, 9728);

  pLoadModel(32587, "Data\\Effect\\", "shiny06", -1);
  sub_614710(32587, "Effect\\", 10497, 9728);

	return pLoadSkill();
}
// ----------------------------------------------------------------------------------------------

int CSkill::GCMagicAttack(unsigned __int8 *a1, int a2, int a3)
{
	int Result = sub_645BA0(a1, a2, a3);

	PMSG_MAGICATTACK_RESULT * lpMsg = (PMSG_MAGICATTACK_RESULT*)a1;
	int MagicNumber = MAKE_NUMBERW(lpMsg->MagicNumberH, lpMsg->MagicNumberL); //loc5
	int SourceNumber = MAKE_NUMBERW(lpMsg->SourceNumberH, lpMsg->SourceNumberL); //loc3
	int TargetNumber = MAKE_NUMBERW(lpMsg->TargetNumberH, lpMsg->TargetNumberL); //loc5

	if(MagicNumber == 618)
	{
		TargetNumber &= 0x7FFFu;

		int iNumber1 = sub_57D9A0(SourceNumber);
		int iNumber2 = sub_57D9A0(TargetNumber);

		lpViewObj lpObj1    = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), iNumber1);//v7 = (DWORD *)pPreviewThis();
		lpViewObj lpObj2    = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), iNumber2);//v7 = (DWORD *)pPreviewThis();
		 
		if(lpObj1 && lpObj2)
		{
			ObjectModel* lpModel1 = &lpObj1->m_Model;
			ObjectModel* lpModel2 = &lpObj2->m_Model;

			//g_Skill.TeleportSkill(&lpObj2->m_Model);

			g_Skill.ExpansionSkill(&lpObj2->m_Model);

			// -> Meteorit Storm 
			//g_Skill.MeteorStorm(lpObj2);

		}
	}

	return Result;
}
// ----------------------------------------------------------------------------------------------



void CSkill::ManaShield()
{
   // if ( v90 != *(DWORD*)0x7BC4F04 )
    {
       // sub_552710(v90);
        //*(float *)(v92 + 140) = 0.0;
    }
   // *(BYTE *)(v90 + 34) = 1;

}
// ----------------------------------------------------------------------------------------------


void CSkill::TeleportSkill(ObjectModel* lpModel)
{
	int a1 = (int)lpModel;
	// -> Teleport
  sub_5509C0();
  sub_542310(lpModel, 151, 1);
  *(float *)(a1 + 148) = 0.0;
  *(BYTE *)(a1 + 23) = 1;
  sub_6D8F20(32049, a1 + 252, a1 + 264, a1 + 156, 0, 0, -1, 0, 0, 0, 0.0, -1);
  //sub_6D8F20(32049, lpModel->VecPosX, lpModel->Unknown264, (int)(lpModel + 156), 0, 0, -1, 0, 0, 0, 0.0, -1);
  sub_6D6AD0(118, 0, 0);

  // -> Expansion of Wiz Streng
/*	sub_5509C0();
	sub_542310(a1, 177, 1);
	float v54[3];
	v54[0] = 0.30000001;
	v54[1] = 0.2;
	v54[2] = 0.89999998;
	sub_6D8F20(502, a1 + 252, a1 + 264, (int)&v54, 0, a1, -1,0,0,0,0.0,-1);
	sub_6D6AD0(840, 0, 0);*/
}
// ----------------------------------------------------------------------------------------------


void CSkill::ExpansionSkill(ObjectModel* lpModel)
{
	//int a1 = (int)lpModel;
	//// -> Expansion of Wiz Streng
	//sub_5509C0();
	//sub_542310(lpModel, 177, 1);
	//float v54[3];
	//v54[0] = 0.30000001;
	//v54[1] = 0.2;
	//v54[2] = 0.89999998;
	//sub_6D8F20(502, a1 + 252, a1 + 264, (int)&v54, 0, a1, -1,0,0,0,0.0,-1);
	//sub_6D6AD0(840, 0, 0);

	int a1 = (int)lpModel;
	// -> Expansion of Wiz Streng
	sub_5509C0();
	sub_542310(lpModel, 177, 1);
	float v54[3];
	v54[0] = 0.30000001;
	v54[1] = 0.2;
	v54[2] = 0.89999998;
	sub_6D8F20(32077, a1 + 252, a1 + 264, (int)&v54, 0, a1, -1,0,0,0,0.0,-1);
	sub_6D6AD0(840, 0, 0);
}
// ----------------------------------------------------------------------------------------------

void CSkill::MeteoritSkill(lpViewObj lpObj1, ObjectModel* ObjectModel1)
{
	int a1 = (int)lpObj1;
	int a2 = (int)ObjectModel1;
	// -> Meteorit shtorm skill
    if ( a1 != oUserPreviewStruct )
    {
        if ( *(DWORD *)(ObjectModel1 + 48) == 1163 )
        sub_552710(lpObj1);
        else
        sub_5518F0(lpObj1);
        *(float *)(ObjectModel1 + 140) = 0.0;
    }
    *(BYTE *)(lpObj1 + 34) = 1;
}


//BOOL __cdecl sub_54EA00(int a1)
#define sub_54EA00	((int(__cdecl*)(ObjectModel* a1))0x54EA00)


void CSkill::MeteorStorm(lpViewObj lpObj1)
{
	int a1 = (int)lpObj1;
	ObjectModel* lpModel = &lpObj1->m_Model;


   //sub_6D8F20(259, a1 + 1028, a1 + 1040, a1 + 932, 0, 0, -1, 0, 0, 0, 0.0, -1);
   // sub_6D6AD0(16, (int)lpModel, 0);

   //sub_542310(lpModel, 1, 1);
   //sub_6D6AD0(16, (int)lpModel, 0);

   // sub_6D8F20(32072, a1 + 1028, a1 + 1040, a1 + 932, 0, 0, -1, 0, 0, 0, 0.0, -1);
   // sub_6D6AD0(121, 0, 0);

	//sub_542310(lpModel, 4, 1);

	//sub_5509C0();
	//sub_542310(lpModel, 50, 1);

	//*(float *)(lpModel + 140) = 0.0;

	// *(BYTE *)(lpObj1 + 34) = 1;
	sub_5509C0();
	sub_542310(lpModel, 177, 1);

	sub_54EA00(lpModel);
	sub_6D6AD0(86, (int)lpModel, 0);

	*(float *)(lpModel + 140) = 0.0;

	*(BYTE *)(lpObj1 + 34) = 1;
}
// ----------------------------------------------------------------------------------------------



//*********************************************************************************

//signed int sub_749A30(int a1)
//{
//  sub_5509C0();
//  sub_542310(a1, 151, 1);
//  *(float *)(a1 + 148) = 0.0;
//  *(BYTE *)(a1 + 23) = 1;
//  sub_6D8F20(32049, a1 + 252, a1 + 264, a1 + 156, 0, 0, -1, 0, 0, 0, 0.0, -1);
//  return sub_6D6AD0(118, 0, 0);
//}
//*********************************************************************************