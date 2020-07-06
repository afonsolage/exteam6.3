#pragma once

#include "..\common\zzzitem.h"
#include "user.h"

struct CustomGroup
{
	int	rate;
	int min_lvl;
	int	max_lvl;
	int	skill_rate;
	int	luck_rate;
	int	opt4_rate;
	int	opt8_rate;
	int	opt12_rate;
	int	opt16_rate;
	int exc;
	int anc;
	int max_sock;

	std::vector<std::pair<int, int>> items;

	std::pair<int, int> GetRandomItem()
	{
		int rnd = rand();
		int n = rnd % items.size();
		return items[n];
	}
};

class CCustomDrop
{
public:
	CCustomDrop(void);
	virtual ~CCustomDrop(void);

	void Init();
	void LoadItem(LPSTR script_file);

	const char* GetName() const { return this->m_sName; }

	BOOL HasDrops() { return m_groups.size() > 0; }
	int GetCode() { return m_iCode; }

protected:
	char	m_sName[255];
	int		m_iCode;
	int		m_iDropZen;
	int		m_iMinZen;
	int		m_iMaxZen;
	int		m_iDropCount;

	std::vector<CustomGroup>	m_groups;

	CustomGroup* GetGroup(int rnd);

	virtual void DropItem(LPOBJ lpObj);

	int RndRange(int min, int max);
	BOOL IsProcRnd(int proc, int max);
};

