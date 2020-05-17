#pragma once

struct MOB_BEHAVIOUR
{
	int doubleDamageRate;
	bool immunePoison;
	bool immuneSleep;
	bool immuneWeakness;
	bool immuneInnovation;
};

class CMobSpecialBehaviour
{
public:
	void Clear();
	void Load();

	bool IsPoisonImmune(int mobId);
	bool IsSleepImmune(int mobId);
	bool IsWeaknessImmune(int mobId);
	bool IsInnovationImmune(int mobId);

	int GetDoubleDamageRate(int mobId);
private:
	std::map<int, MOB_BEHAVIOUR> m_behaviours;
};

extern CMobSpecialBehaviour g_MobSpecialBehaviour;