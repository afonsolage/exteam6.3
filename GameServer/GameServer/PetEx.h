#pragma once

#if(ENABLE_PETEX)

#define MAX_PETEX_COUNT		100
#define MAX_PETEX_OPTION	5

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

struct PETEX_OPTION
{
	int Type;
	int Value;
};

struct PETEX_DATA
{
	int Active;
	int ItemType;
	int ItemIndex;
	PETEX_OPTION Option[MAX_PETEX_OPTION];
};

struct PETEX_IMMORTAL
{
	int Active;
	int ItemType;
	int ItemIndex;
};

class CPetEx
{
public:
		 CPetEx();
		 ~CPetEx();

	void Init();
	void Load();
	void Read(char* filename);
	bool IsPet(int ItemType);
	bool IsPetImmortal(int ItemType);
	PETEX_DATA* GetPetData(int ItemID);
	bool PetLife(int aIndex);
	void Calc(int aIndex);
	void Exp(int aIndex, __int64 & exp);
	void Zen (int aIndex, float & money);

	int m_Enable;
	int m_PetCount;
	int m_ImmortalCount;
	PETEX_DATA m_Data[MAX_PETEX_COUNT];
	PETEX_IMMORTAL m_Immoirtal[MAX_PETEX_COUNT];
};

extern CPetEx g_PetEx;

#endif