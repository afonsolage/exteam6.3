#include "stdafx.h"
#include "LoadMap.h"
#include "TMemory.h"
#include "Import.h"
#include "Defines.h"

LoadMap gLoadMap;

DWORD MapTextOffset        = 0x00402320;
DWORD MapJumpOffset        = 0x005D3027;
DWORD MapJumpOffset2        = 0x005D2D19;
DWORD MapReturnOffset    = 0x005D2C32;

// ----------------------------------------------------------------------------------------------

Naked(LoadNewTextMapName)
{
    _asm
    {
		CMP DWORD PTR SS:[EBP+0x8],0x22
		JNZ NextMapText0
		PUSH 0x73B
		MOV ECX,0x08128ADC
		CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText0:
		// ---
		CMP DWORD PTR SS:[EBP+0x8],0x52       // Arkania MapId: 82
			JNZ NextMapText1
			PUSH 0xC58           // Text.bmd number line: 3160
			MOV ECX,0x08128ADC
			CALL MapTextOffset
			JMP MapJumpOffset
			JMP MapJumpOffset2
			// ---
        // ---
        NextMapText1:
        // ---
        CMP DWORD PTR SS:[EBP+0x8],0x53       // MapId: 83
        JNZ NextMapText2
        PUSH 0xC59           // Text.bmd number line: 3160
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText2:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x54       // Arkania MapId: 84
        JNZ NextMapText3
        PUSH 0xC5A           // Text.bmd number line: 3161
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText3:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x55       // Arkania MapId: 85
        JNZ NextMapText4
        PUSH 0xC5B           // Text.bmd number line: 3162
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText4:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x56       // Arkania MapId: 86
        JNZ NextMapText5
        PUSH 0xC5C           // Text.bmd number line: 3163
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText5:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x57       // Arkania MapId: 87
        JNZ NextMapText6
        PUSH 0xC5D           // Text.bmd number line: 3164
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText6:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x58       // Arkania MapId: 88
        JNZ NextMapText7
        PUSH 0xC5E           // Text.bmd number line: 3165
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText7:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x59       // Arkania MapId: 89
        JNZ NextMapText8
        PUSH 0xC5F           // Text.bmd number line: 3166
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText8:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x5A       // Arkania MapId: 90
        JNZ NextMapText9
        PUSH 0xC60           // Text.bmd number line: 3167
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText9:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x5B       // Arkania MapId: 91
        JNZ NextMapText10
        PUSH 0xC61           // Text.bmd number line: 3168
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText10:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x5C       // Arkania MapId: 92
        JNZ NextMapText11
        PUSH 0xC62           // Text.bmd number line: 3169
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText11:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x5D       // Arkania MapId: 93
        JNZ NextMapText12
        PUSH 0xC63           // Text.bmd number line: 3170
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText12:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x5E       // Arkania MapId: 94
        JNZ NextMapText13
        PUSH 0xC64           // Text.bmd number line: 3171
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText13:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x5F       // Arkania MapId: 95
        JNZ NextMapText14
        PUSH 0xC65           // Text.bmd number line: 3172
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText14:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x60       // Arkania MapId: 96
        JNZ NextMapText15
        PUSH 0xC66           // Text.bmd number line: 3173
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText15:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x61       // Arkania MapId: 97
        JNZ NextMapText16
        PUSH 0xC67           // Text.bmd number line: 3174
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText16:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x62       // Arkania MapId: 98
        JNZ NextMapText17
        PUSH 0xC68           // Text.bmd number line: 3175
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText17:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x63       // Arkania MapId: 99
        JNZ NextMapText18
        PUSH 0xC69           // Text.bmd number line: 3176
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
		NextMapText18:
        // ---
		CMP DWORD PTR SS:[EBP+0x8],0x64       // Arkania MapId: 100
        JNZ ReturnMapLoad
        PUSH 0xC6A           // Text.bmd number line: 3177
        MOV ECX,0x08128ADC
        CALL MapTextOffset
		JMP MapJumpOffset
		JMP MapJumpOffset2
		// ---
        ReturnMapLoad:
        // ---
        JMP MapReturnOffset
    }
}

char* LoadMapName(signed int MapNumber)
{
	if (MapNumber >= 82 && MapNumber <= 100)
	{
		return pGetTextLine(pTextLineThis, (3160 + MapNumber - 82));
	}
	return pMapName(MapNumber);
}

char * Map82 = "NewMap82.tga";
char * Map83 = "NewMap83.tga";
char * Map84 = "NewMap84.tga";
char * Map85 = "NewMap85.tga";
char * Map86 = "NewMap86.tga";
char * Map87 = "NewMap87.tga";
char * Map88 = "NewMap88.tga";
char * Map89 = "NewMap89.tga";
char * Map90 = "NewMap90.tga";
char * Map91 = "NewMap91.tga";
char * Map92 = "NewMap92.tga";
char * Map93 = "NewMap93.tga";
char * Map94 = "NewMap94.tga";
char * Map95 = "NewMap95.tga";
char * Map96 = "NewMap96.tga";
char * Map97 = "NewMap97.tga";
char * Map98 = "NewMap98.tga";
char * Map99 = "NewMap99.tga";
char * Map100 = "NewMap100.tga";

Naked(LoadInterfaceMapName)
{
	_asm
	{
		MOV DWORD PTR SS:[EBP-0x848],0x51
		PUSH 0x00D25498							// Karutan 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x52		// 82 Arkania Custom Map
			PUSH Map82								// Interface Name
			LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
			LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
			CALL InterfaceLoad1
			ADD ESP,0x0C
			MOV DWORD PTR SS:[EBP-0xA74],EAX
			MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
			MOV BYTE PTR SS:[EBP-0x4],0x43
			MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
			LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
			MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
			CALL InterfaceLoad2
			MOV ECX,EAX
			CALL InterfaceLoad3
			MOV BYTE PTR SS:[EBP-0x4],0x2
			LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
			MOV DWORD PTR SS:[EBP-0x4],-0x1
			LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x53		// 83 Custom Map
		PUSH Map83								// Interface Name
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x54		// 84 Arkania Custom Map
		PUSH Map84								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x55		// 85 Arkania Custom Map
		PUSH Map85								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x56		// 86 Arkania Custom Map
		PUSH Map86								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x57		// 87 Arkania Custom Map
		PUSH Map87								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x58		// 88 Arkania Custom Map
		PUSH Map88								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x59		// 89 Arkania Custom Map
		PUSH Map89								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x5A		// 90 Arkania Custom Map
		PUSH Map90								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x5B		// 91 Arkania Custom Map
		PUSH Map91								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x5C		// 92 Arkania Custom Map
		PUSH Map92								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x5D		// 93 Arkania Custom Map
		PUSH Map93								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x5E		// 94 Arkania Custom Map
		PUSH Map94								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x5F		// 95 Arkania Custom Map
		PUSH Map95								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x60		// 96 Arkania Custom Map
		PUSH Map96								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x61		// 97 Arkania Custom Map
		PUSH Map97								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x62		// 98 Arkania Custom Map
		PUSH Map98								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x63		// 99 Arkania Custom Map
		PUSH Map99								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		//----
		MOV DWORD PTR SS:[EBP-0x848],0x64		// 100 Arkania Custom Map
		PUSH Map100								// Interface Name 
		LEA EAX,DWORD PTR SS:[EBP-0x28]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP,0x0C
		MOV DWORD PTR SS:[EBP-0xA74],EAX
		MOV EDX,DWORD PTR SS:[EBP-0xA74]
		MOV DWORD PTR SS:[EBP-0xA78],EDX
		MOV BYTE PTR SS:[EBP-0x4],0x43
		MOV EAX,DWORD PTR SS:[EBP-0xA78]
		PUSH EAX
		LEA ECX,DWORD PTR SS:[EBP-0x848]
		PUSH ECX
		MOV ECX,DWORD PTR SS:[EBP-0x868]
		ADD ECX,0x4
		CALL InterfaceLoad2
		MOV ECX,EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS:[EBP-0x4],0x2
		LEA ECX,DWORD PTR SS:[EBP-0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS:[EBP-0x4],-0x1
		LEA ECX,DWORD PTR SS:[EBP-0x28]
		// ----
		CALL InterfaceLoad4
		MOV ECX,DWORD PTR SS:[EBP-0xC]
		MOV DWORD PTR FS:[0x0],ECX
		// ----
		MOV EDI, 0x0047FD08
		JMP EDI
		// ----
		InterfaceLoad1:
		MOV EDI, 0x0047C220
		JMP EDI
		// ----
		InterfaceLoad2:
		MOV EDI, 0x00480160
		JMP EDI
		// ----
		InterfaceLoad3:
		MOV EDI, 0x00409AF0
		JMP EDI
		// ----
		InterfaceLoad4:
		MOV EDI, 0x00409AD0
		JMP EDI
		// ----
		MOV ESP,EBP
		POP EBP
		RETN
	}
}

void LoadMap::Load()
{
	SetRange((PVOID)0x005D2C13, 31, ASM::NOP);
	SetOp((LPVOID)0x005D2C13, (LPVOID)LoadNewTextMapName, ASM::JMP);

	SetRange((LPVOID)0x0047FC85, 131, ASM::NOP);
	SetOp((LPVOID)0x0047FC85, (LPVOID)LoadInterfaceMapName, ASM::JMP);

	/*SetOp((LPVOID)0x00520ECF, (LPVOID)LoadMapName, ASM::CALL);
	SetOp((LPVOID)0x00520F1F, (LPVOID)LoadMapName, ASM::CALL);
	SetOp((LPVOID)0x0063E743, (LPVOID)LoadMapName, ASM::CALL);
	SetOp((LPVOID)0x00640EB2, (LPVOID)LoadMapName, ASM::CALL);
	SetOp((LPVOID)0x007D2C89, (LPVOID)LoadMapName, ASM::CALL);
	SetOp((LPVOID)0x007E6ABF, (LPVOID)LoadMapName, ASM::CALL);
	SetOp((LPVOID)0x0084ADA7, (LPVOID)LoadMapName, ASM::CALL);*/
}