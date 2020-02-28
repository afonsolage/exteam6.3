#include "stdafx.h"
#include "Map.h"
#include "Console.h"
#include "TMemory.h"
#include "Import.h"

#if(CUSTOM_NEW_MAP)

CMap g_Map;

void CMap::Load()
{
	SetOp((LPVOID)0x0047FD98, (LPVOID)this->NewMap, ASM::JMP);
	SetOp((LPVOID)0x0047FC85, (LPVOID)this->NewMapWellcome, ASM::JMP);
	SetOp((LPVOID)0x005D2C13, (LPVOID)this->NewMapName, ASM::JMP);
	//SetOp((LPVOID)0x005EE908, (LPVOID)this->NewMapEffect, ASM::CALL);
}

__declspec(naked)void CMap::NewMap()
{
	static int MapNum = 0;
	static int NewMapJmp = 0x0047FDA1;
	static int OldMapJmp = 0x0047FDB3;

	_asm
	{
		MOV EAX, DWORD PTR DS:[0x0E61E18]
		MOV MapNum, EAX
	}

	if(MapNum == 40 || MapNum == 82)//83
	{
		_asm
		{
			JMP NewMapJmp
		}
	}

	_asm
	{
		JMP OldMapJmp
	}
}

__declspec(naked)void CMap::NewMapWellcome()
{
	static int szMapKarutan = 0x00D25498;
	static int Call_0047C220 = 0x0047C220;
	static int Call2_00480160 = 0x00480160;
	static int Call3_00409AF0 = 0x00409AF0;
	static int Call4_00409AD0 = 0x00409AD0;

	_asm
	{
		MOV DWORD PTR SS:[EBP-0x848],0x51
		PUSH szMapKarutan                     ; ASCII "MapName_Karutan.tga"
		LEA EAX,[EBP-0x28]
		PUSH EAX
		LEA ECX,[EBP-0x864]
		PUSH ECX
		CALL Call_0047C220
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0x0A74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0x0A74]
		MOV DWORD PTR SS:[EBP-0x0A78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0x0A78]
		PUSH EAX
		LEA ECX,[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,4
		CALL Call2_00480160
		MOV ECX,EAX
		CALL Call3_00409AF0

		MOV DWORD PTR SS:[EBP-0x848], 82
		PUSH szMapKarutan                     ; ASCII "MapName_Karutan.tga"
		LEA EAX,[EBP-0x28]
		PUSH EAX
		LEA ECX,[EBP-0x864]
		PUSH ECX
		CALL Call_0047C220
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0x0A74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0x0A74]
		MOV DWORD PTR SS:[EBP-0x0A78],EDX
		MOV BYTE PTR SS:[EBP-0x4],43
		MOV EAX,DWORD PTR SS:[EBP-0x0A78]
		PUSH EAX
		LEA ECX,[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL Call2_00480160
		MOV ECX,EAX
		CALL Call3_00409AF0

		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,[EBP-0x864]
		CALL Call4_00409AD0
		MOV DWORD PTR SS:[EBP-0x4],-1
		LEA ECX,[EBP-0x28]
		CALL Call4_00409AD0
		MOV ECX,DWORD PTR SS:[EBP-0x0C]
		MOV DWORD PTR FS:[0x0],ECX
		MOV ESP,EBP
		POP EBP
		RETN
	}
}

char* CMap::GetNewMapName(int MapNumber)
{
	if(MapNumber == 0x52)
	{
		return "Battle Guard";
	}

	return "No Name";
}

__declspec(naked)void CMap::NewMapName()
{
	static int MapName = 0;
	static int TextLine = 0;
	static int Call_00402320 = 0x00402320;
	static int Jmp_005D3027 = 0x005D3027;
	static int Jne_005D2C32 = 0x005D2C32;

	_asm
	{
		MOV ECX, DWORD PTR SS:[EBP+0x08]
		MOV MapName, ECX
	}

	if(MapName == 0x22)
	{
		TextLine = 0x73B;
	}
	else if(MapName == 0x52)
	{
		TextLine = 3160;
	}
	else
	{
		_asm
		{
			JMP Jne_005D2C32
		}
	}

	_asm
	{
		PUSH TextLine
		MOV ECX, 0x08128ADC
		CALL Call_00402320
		JMP Jmp_005D3027
	}
}

void CMap::NewMapEffect(int a1)
{
	sub_5EC0E0(a1);

	if(pMapNumber == 82)
	{
		int v2 = *(DWORD *)(a1 + 48);
		int v3 = *(DWORD *)(a1 + 60);

		//gConsole.Output(cGREEN, "%d %d", v2, v3);

		switch(v2)
		{
		case 90:

			break;
		case 92:
			{
				int v38, v34;
				float v35 = 0.0;
				float v36 = 0.0;
				float v37 = 0.0;
				sub_545030((float *)a1, (int)&*(DWORD*)0x7BC08D0, (int)&v35, (int)&v38, 0);
				sub_545030((float *)a1, (int)&*(DWORD*)0x7BC0900, (int)&v35, (int)&v34, 0);
				if ( (signed int)rand() % 30 == 1 )
				  sub_72D060(32134, (int)&v38, (int)&v34, a1 + 264, 18, 0, 50.0, -1, 0, 0, -1, 0, -1);
			}
			break;
		case 93:

			break;
		case 96:
		
			break;
		case 98:
			if (!(rand() % 3))
			{
				int v42;
				float v31 = 0.0;
				float v32 = 0.0;
				float v33 = 0.0;
				sub_545030((float *)a1, (int)&*(DWORD*)0x7BC08D0, (int)&v31, (int)&v42, 0);
				float v45 = 0.5;
				float v46 = 0.60000002;
				pPlayDynamicEffect(32301, (DWORD *)(a1 + 252), (int)(a1 + 264), &v45, 2, 1.0, 0);
			}
			break;
		case 101:

			break;
		case 102:

			break;
		case 103:

			break;
		}

		 float v62 = 0.1;

		//if(v2 == 92)	
		//	for (int m = 0; m < 20; ++m )
         //       pPlayDynamicEffect(32370, (DWORD *)(a1 + 252), (int )(a1 + 264), &v62, 1, *(float *)(a1 + 96), a1);	//32146

		/*if(v2 == 101)
			for (int m = 0; m < 20; ++m )
                pPlayDynamicEffect(0x7D02, (DWORD *)(a1 + 252), (int )(a1 + 264), &v62, 1, *(float *)(a1 + 96), a1);
		if(v2 == 90)
			for (int m = 0; m < 20; ++m )
                pPlayDynamicEffect(32263, (DWORD *)(a1 + 252), (int )(a1 + 264), &v62, 1, *(float *)(a1 + 96), a1);*/
		/*switch(v2)
		{
	       case 92:
			  //*(float *)&v15 = 1.0;
			  float v16 = 0.40000001;
			  float v17 = 0.40000001;
			//  float v8 = *(float*)0x5EF5A1C * 0.0005000000237487257;
			 // sub_4DB0C0(v8);
			 //float v9 = (v8 + 1.0) * 0.5;
			 // if ( v9 > 0.8999999761581421 )
			  {
				for (int i = 0; i < 2; ++i )
				  sub_6D8F20(32370, (DWORD *)(a1 + 252), (int)(a1 + 264), 1.0, 0, 0, -1, 0, (signed int)*(float *)(a1 + 96), 0, 0.0, -1);
			  }
			  break;	
		}*/
	}



}


#endif

