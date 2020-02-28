#pragma once

#include "..\common\zzzitem.h"
#include "user.h"

struct CustomBoxGroup
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
	int exc_rate;

	std::vector<std::pair<int, int>> items;

	std::pair<int, int> GetRandomItem()
	{
		int rnd = rand();
		int n = rnd % items.size();
		return items[n];
	}
};

class CCustomBoxDrop
{
public:
	CCustomBoxDrop(void);
	virtual ~CCustomBoxDrop(void);

	void Init();
	void LoadItem(LPSTR script_file);

	BOOL DropItem(LPOBJ lpObj);

	BOOL HasDrops() {return m_groups.size() > 0;}
	int GetCode() {return m_iCode;}


private:
	char	m_sName[255];
	int		m_iCode;
	int		m_iDropZen;
	int		m_iMinZen;
	int		m_iMaxZen;

	std::vector<CustomBoxGroup>	m_groups;

	CustomBoxGroup* GetGroup(int rnd);

	int RndRange(int min, int max);
	BOOL IsProcRnd(int proc, int max);
};

