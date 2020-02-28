#pragma once

#if(ENABLE_PETEX)

class CPetOld
{
public:
	CPetOld();
	~CPetOld();

	void Load();

	// -> FENRIR ASM
	static int GetFenrirSkillColor(ObjectPreview * gPreview);
	static void SetNewPetSkins();
	static void FixVisualBug();
	static void AsmTest3();
	static void AsmTest4();
	static void AsmTest5();
	static void AsmTest6();
	static void SetNewPetMovement();
	static void SetNewPetScale();
	static void SetNewPetSkillEffect();
	static void SetNewPetItemLevelTooltipLines();
	static void SetNewPetItemNameColor();

	DWORD m_Buffer;
};

extern CPetOld g_PetOld;

#endif