#pragma once

#if(CUSTOM_MANAGER)

struct DARKREVAN_ATTACK_BLOCK
{
	int Map;
};

class CManager
{
public:
	CManager();
	~CManager();

	void Load();
	void Read(char* filename);

	std::vector<DARKREVAN_ATTACK_BLOCK> m_DarkRevenAttackBlock;;

};

extern CManager g_Manager;

#endif