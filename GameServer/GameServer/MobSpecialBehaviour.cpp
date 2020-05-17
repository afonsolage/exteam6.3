#include "stdafx.h"
#include "MobSpecialBehaviour.h"
#include "GameMain.h"

CMobSpecialBehaviour g_MobSpecialBehaviour;

void CMobSpecialBehaviour::Clear()
{
	this->m_behaviours.clear();
}

void CMobSpecialBehaviour::Load()
{
	this->Clear();

	auto path = gDirPath.GetNewPath("Custom\\MobSpecialBehaviour.dat");

	FILE *file = fopen(path, "r");

	if (file == NULL)
	{
		MessageBoxA(0, "Custom\\MobSpecialBehaviour.dat", "CRITICAL ERROR", 0);
		return;
	}

	char Buff[256];

	int Flag = 0;
	while (!feof(file))
	{
		fgets(Buff, 256, file);

		if (Buff[0] == '/' && Buff[1] == '/')
			continue;

		int mobId;
		int ddRage;
		int poison;
		int sleep;
		int weakness;
		int innovation;

		sscanf(Buff, "%d %d %d %d %d %d", &mobId, &ddRage, &poison, &sleep, &weakness, &innovation);

		this->m_behaviours[mobId] = { ddRage, poison == 1, sleep == 1, weakness == 1, innovation == 1};
	}

	fclose(file);
}

bool CMobSpecialBehaviour::IsPoisonImmune(int mobId)
{
	auto it = this->m_behaviours.find(mobId);

	if (it == this->m_behaviours.end())
		return false;
	else
		return it->second.immunePoison;
}

bool CMobSpecialBehaviour::IsSleepImmune(int mobId)
{
	auto it = this->m_behaviours.find(mobId);

	if (it == this->m_behaviours.end())
		return false;
	else
		return it->second.immuneSleep;
}

bool CMobSpecialBehaviour::IsWeaknessImmune(int mobId)
{
	auto it = this->m_behaviours.find(mobId);

	if (it == this->m_behaviours.end())
		return false;
	else
		return it->second.immuneWeakness;
}

bool CMobSpecialBehaviour::IsInnovationImmune(int mobId)
{
	auto it = this->m_behaviours.find(mobId);

	if (it == this->m_behaviours.end())
		return false;
	else
		return it->second.immuneInnovation;
}

int CMobSpecialBehaviour::GetDoubleDamageRate(int mobId)
{
	auto it = this->m_behaviours.find(mobId);

	if (it == this->m_behaviours.end())
		return 0;
	else
		return it->second.doubleDamageRate;
}
