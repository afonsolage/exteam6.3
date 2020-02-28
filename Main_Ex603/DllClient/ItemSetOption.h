#pragma once
// ----------------------------------------------------------------------------------------------

#if(ENABLE_ITEMSETOPTION)
// ---------------------------------------------------------------------------------------------

#define MAX_SETOPT_LINE			110	//108
#define MAX_SETOPT_COUNT		256	//256
#define MAX_BSETOPT_SIZE		(MAX_SETOPT_COUNT*MAX_SETOPT_LINE)
// ----------------------------------------------------------------------------------------------

//#define pGameWindow				*(HWND*)0x5878000
#define oItemSetOptionBMDLoad	0x004E8916	//0x0040D5AA
#define oItemSetOptionAsm1		0x004E956E	//0x0040E06C
#define oItemSetOptionAsm2		0x004E926B	//0x0040DDDD
#define oItemSetOptionAsm3		0x004EC4C4	//0x00410884
#define oItemSetOptionAsm4		0x004EC2A5	//0x0041072F
#define oItemSetOptionAsm5		0x004EC3A9	//0x004107AF
#define oItemSetOptionAsm6		0x004EBD7F	//0x0041021C
#define oItemSetOptionAsm7		0x004EBEE9	//0x00410360
#define oItemSetOptionAsm8		0x004ECAAA	//0x00410360
#define pFileOpen				((int(__cdecl*)(char* FileName, char* Mode)) 0x9CFEC0)
#define pFileRead				((int(__cdecl*)(int a1, int a2, int a3, int a4)) 0x9CFDDF)
#define pFileClose				((signed int(__cdecl*)(int a1))0x9CFAA6)
#define pFileCRC				((int(__cdecl*)(int a1, int a2, unsigned __int16 a3)) 0x4B1A20)
#define pFileDec				((int(__cdecl*)(int a1, signed int a2)) 0x4071A0)
// ----------------------------------------------------------------------------------------------

class CItemSetOption
{
public:
		CItemSetOption();
		~CItemSetOption();

	void Load();

	static bool BMDLoad(char* FileName);

	static void AsmAncent1();
	static void AsmAncent2();
	static void AsmAncent3();
	static void AsmAncent4();
	static void AsmAncent5();
	static void AsmAncent6();
	static void AsmAncent7();
	static void AsmAncent8();

	DWORD m_dwSetOptionAddress;
	DWORD m_dwJmpReturn1;
	DWORD m_dwJmpReturn2;
	DWORD m_dwJmpReturn3;
	DWORD m_dwJmpReturn4;
	DWORD m_dwJmpReturn5;
	DWORD m_dwJmpReturn6;
	DWORD m_dwJmpReturn7;
	DWORD m_dwJmpReturn8;

	BYTE m_SetOptionData[MAX_BSETOPT_SIZE];
};
// ----------------------------------------------------------------------------------------------

extern CItemSetOption g_ItemSetOption;
// ----------------------------------------------------------------------------------------------

#endif