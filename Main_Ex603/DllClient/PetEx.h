#pragma once

#if(ENABLE_PETEX)
// -------------------------------------------------------------------------------
#define DEBUG_PET_CRASH			0
#define MAX_PETEX_COUNT			100
#define MAX_PETEX_OPTION		5
#define MAX_PETEX_EFFECT		1000
#define PETEX_PATH				".\\Data\\Custom\\Configs\\Pets.dat"
// -------------------------------------------------------------------------------
#define PI						3.14159265
#define CS_SET_HELPER(x)		(((x)&0x03))
#define LODWORD(h)				((DWORD)(__int64(h) & __int64(0xffffffff)))
#define SLODWORD(x)				(*((DWORD*)&(x)))
// -------------------------------------------------------------------------------
#define pPreviewPetThis			*(DWORD*)0x007BC4F04
#define oUserTextObject			*(int*)0x8128AC0
#define gObjCreatePet			((void(__thiscall*)(int ItemID)) 0x00835CF0)
#define gObjCreateBug			((int(__cdecl*)(int ID, int PetStruct, int PetObjectView, int Mode, int arg5)) 0x00501700)
#define gObjCreateBug2			((LPVOID(__cdecl*)(int ID, int PetStruct, int PetObjectView, int Mode, int arg5)) 0x5013B0)
#define pTextLineThis			((LPVOID(*)()) 0x8128ADC)
#define pGetTextLine_			((char*(__thiscall*)(LPVOID This, int LineNumber)) 0x402320)
#define pObjectMaxBug			((int(__cdecl*)(int a1, unsigned __int8 a2, int a3, int a4)) 0x5EBBB0)
#define pRefreshViewPortItem	((int(*)(int a1)) 0x6411A0)
#define pPetsMovement			((void(*)(int a1, char a2)) 0x501790)
#define pet_4C8640				((char(__thiscall*)(LPVOID This, char a2)) 0x4C8640)
#define sub_57D9A0				((DWORD(__cdecl*)(DWORD)) 0x57D9A0)
#define sub_96A340				((int(__thiscall*)(LPVOID This, signed int a2)) 0x96A340)
#define sub_402BC0				((LPVOID(*)())0x402BC0)
#define sub_58AA80				((DWORD(__cdecl*)(DWORD)) 0x58AA80)
#define sub_5012D0				((DWORD(__cdecl*)(DWORD)) 0x5012D0)
#define sub_4DB230				((LPVOID(*)())0x4DB230)
#define sub_925280				((int(__thiscall*)(LPVOID This,int a1, short a2)) 0x925280)
#define	sub_7DF910				((int(__stdcall*)(signed int PosX, signed int PosY, int a3, signed int a4, signed int a5, char a6)) 0x7DF910)
#define sub_4CDA10				((LPVOID(*)())0x4CDA10)
#define sub_969AD0				((int(__thiscall*)(LPVOID This, signed int a2)) 0x969AD0)
#define sub_959CC0				((int(__cdecl*)(DWORD, DWORD)) 0x959CC0)
#define sub_95A1C0				((int(__cdecl*)(DWORD a1, DWORD a2, float *a3)) 0x95A1C0)
#define sub_9CFA0D				((int(*)()) 0x9CFA0D)
#define sub_5DBA10				((char(__cdecl*)(float a1, float a2, float a3)) 0x5DBA10)
// -------------------------------------------------------------------------------

enum
{
	ePET_NONE,
	ePET_DAMAGE,
	ePET_DEFENCE,
	ePET_IGNOREDEFENCE,
	ePET_CRITICALDAMAGE,
	ePET_EXELLENTDAMAGEe,
	ePET_DOUBLEDAMAGE,
	ePET_DECRISEDAMAGE,
	ePET_REFLECTDAMAGE,
	ePET_SD,
	ePET_LIFE,
	ePET_MAGICDAMAGE, 
	ePET_EXPERIENCE,
	ePET_ZENMONEY,
};

struct PETEX_EFFECT
{
	int Index;
	int ItemType;
	int ItemIndex;
	int EffectIndex;
	float ColorR;
	float ColorG;
	float ColorB;
	float ColorSize;
	float ColorMain;
	float ColorSide;
};

struct PETEX_OPTION
{
	int ItemType;
	int ItemIndex;
	int Type;
	int Value;
};

struct PETEX_DATA
{
	int Active;
	int ItemType;
	int ItemIndex;
	float PetZ;
	float PetSize;
	float InvSize;
	float InvX;
	float InvY;
	char ModelName[64];
};

class CPetEx
{
public:
	CPetEx();
	~CPetEx();

	void Load();
	void Read(char* filename);

	static void LoadModel();
	static void LoadTexture();
	static bool IsPet(int ItemID, bool Preview);
	static PETEX_DATA* GetPetData(int ItemID, bool Preview);
	static void PreviewCharSet(lpViewObj lpObj, BYTE * CharSet, lpViewObj Object, int Mode);
	static void CreatePetHook(int ItemID);
	static bool ResetPetPreview(int ItemID);
	static char	PetHPBar(int a1, int a2);
	static void	RefreshViewPortItem(int a1);
	static void	PetsMovement(int a1, char a2);
	static void	PetFollowCharacter(int a1, float MaxPos);
	static void InventorySize();
	static char CreateEffect(int a4, char a5);

	int m_Enable;
	int m_PetCount;
	int m_OptCount;
	int m_EffectCount;
	DWORD m_PetTickCount;

	PETEX_DATA m_Data[MAX_PETEX_COUNT];
	PETEX_OPTION m_Option[MAX_PETEX_OPTION];
	PETEX_EFFECT m_Effect[MAX_PETEX_EFFECT];
};

extern CPetEx g_PetEx;

#endif