#include "stdafx.h"
#include "CustomBossDrop.h"
#include "..\include\readscript.h"
#include "..\common\winutil.h"
#include "logproc.h"
#include "GameMain.h"
#include "DSProtocol.h"
#include "gObjMonster.h"
#include "..\common\SetItemOption.h"

bool sortCustomBossDrop(const CustomBossGroup &a, const CustomBossGroup &b)
{
	return a.rate < b.rate;
}


CCustomBossDrop::CCustomBossDrop(void)
{
}


CCustomBossDrop::~CCustomBossDrop(void)
{
}

void CCustomBossDrop::Init()
{
	memset(m_sName, 0, 255);
	m_iDropZen = 0;
	m_groups.clear();
}

void CCustomBossDrop::LoadItem(LPSTR script_file)
{
	this->Init();

	int Token;

	SMDFile = fopen(gDirPath.GetNewPath(script_file), "r");

	if (SMDFile == NULL)
	{
		LogAdd(lMsg.Get(MSGGET(1, 197)), script_file);
		return;
	}

	while (true)
	{
		Token = GetToken();

		if (Token == END)
		{
			break;
		}

		if (Token == 1)
		{
			int section_type = (int)TokenNumber;

			if (section_type == 1)
			{
				while (true)
				{
					Token = GetToken();

					if (Token == 0)
					{
						if (strcmp("end", TokenString) == 0)
						{
							break;
						}
					}

					strcpy_s(this->m_sName, 255, TokenString);

					Token = GetToken();
					this->m_iCode = (int)TokenNumber;

					Token = GetToken();
					this->m_iDropZen = (int)TokenNumber;

					Token = GetToken();
					this->m_iMinZen = (int)TokenNumber;

					Token = GetToken();
					this->m_iMaxZen = (int)TokenNumber;

					Token = GetToken();
					this->m_iDropCount = (int)TokenNumber;
				}
			}

			if (section_type == 2)
			{
				CustomBossGroup group;

				Token = GetToken();
				group.rate = (int)TokenNumber;
				Token = GetToken();
				group.min_lvl = (int)TokenNumber;
				Token = GetToken();
				group.max_lvl = (int)TokenNumber;
				Token = GetToken();
				group.skill_rate = (int)TokenNumber;
				Token = GetToken();
				group.luck_rate = (int)TokenNumber;
				Token = GetToken();
				group.opt4_rate = (int)TokenNumber;
				Token = GetToken();
				group.opt8_rate = (int)TokenNumber;
				Token = GetToken();
				group.opt12_rate = (int)TokenNumber;
				Token = GetToken();
				group.opt16_rate = (int)TokenNumber;
				Token = GetToken();
				group.exc = (int)TokenNumber;
				Token = GetToken();
				group.anc = (int)TokenNumber;
				Token = GetToken();
				group.max_sock = (int)TokenNumber;

				while (true)
				{
					Token = GetToken();

					if (Token == 0)
					{
						if (strcmp("end", TokenString) == 0)
						{
							break;
						}
					}

					int item_type = (int)TokenNumber;
					Token = GetToken();
					int item_index = (int)TokenNumber;

					group.items.push_back(std::make_pair(item_type, item_index));
				}

				if (group.rate == 0 || group.items.size() == 0)
					continue;

				this->m_groups.emplace_back(group);
			}
		}
	}

	if (!this->m_groups.empty())
	{
		std::sort(this->m_groups.begin(), this->m_groups.end(), sortCustomBossDrop);

		int totalRate = 0;
		for (int n = 0; n < this->m_groups.size(); n++)
		{
			totalRate += this->m_groups[n].rate;
		}

		//Recompute the indivual rate of group
		int lastRate = 0;
		for (int n = 0; n < this->m_groups.size(); n++)
		{
			lastRate = (int)(((float)this->m_groups[n].rate / (float)totalRate) * 10000) + lastRate;
			this->m_groups[n].rate = lastRate;
		}

		this->m_groups.back().rate = 10000;
	}

	fclose(SMDFile);
}

CustomBossGroup* CCustomBossDrop::GetGroup(int rnd)
{
	for (int n = 0; n < m_groups.size(); n++)
	{
		if (rnd < m_groups[n].rate)
		{
			return &m_groups[n];
		}
	}

	return &m_groups.back();
}

int CCustomBossDrop::RndRange(int min, int max)
{
	return (rand() % ((max - min) + 1)) + min;
}

int CCustomBossDrop::IsProcRnd(int proc, int max)
{
	return rand() % max < proc;
}

void CCustomBossDrop::DropItem(LPOBJ lpBoss, LPOBJ lpKiller)
{
	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum;

	auto maxHitUser = gObjMonsterTopHitDamageUser(lpBoss);

	if (maxHitUser != -1 && gObjIsConnected(maxHitUser))
	{
		lpKiller = &gObj[maxHitUser];
	}

	srand((unsigned int)(time(NULL) * lpKiller->m_Index));

	for (auto i = 0; i < this->m_iDropCount; i++)
	{
		int v = rand();
		int rnd = v % 10000;

		if (m_iDropZen > 0 && rnd < m_iDropZen)
		{
			int zen = this->RndRange(m_iMinZen, m_iMaxZen);
			x = lpKiller->X - 2;
			y = lpKiller->Y - 2;
			x += rand() % 3;
			y += rand() % 3;
			MapC[lpKiller->MapNumber].MoneyItemDrop(zen, x, y);
			continue;
		}

		CustomBossGroup* lpGroup = GetGroup(rnd);

		if (lpGroup == NULL || lpGroup->rate == 0 || lpGroup->items.size() == 0)
		{
			LogAddTD("[%s][%s][CustomBossDrop][%s] : (%d)(X:%d/Y:%d) Invalid group at rnd %d",
				lpKiller->AccountID, lpKiller->Name, this->m_sName, lpKiller->MapNumber, lpKiller->X, lpKiller->Y, rnd);
			continue;
		}

		std::pair<int, int> item = lpGroup->GetRandomItem();

		type = ItemGetNumberMake(item.first, item.second);
		level = this->RndRange(lpGroup->min_lvl, lpGroup->max_lvl);
		x = lpKiller->X;
		y = lpKiller->Y;
		dur = 0;
		Option1 = IsProcRnd(lpGroup->skill_rate, 10000);
		Option2 = IsProcRnd(lpGroup->luck_rate, 10000);

		v = rand();
		rnd = v % 10000;

		if (rnd < lpGroup->opt16_rate)
			Option3 = 4;
		else if (rnd < lpGroup->opt12_rate)
			Option3 = 3;
		else if (rnd < lpGroup->opt8_rate)
			Option3 = 2;
		else if (rnd < lpGroup->opt4_rate)
			Option3 = 1;
		else
			Option3 = 0;

		auto res = g_HuntingSystem.GetSkillIncValue(lpKiller->m_Index, eHS_SPCDROP);
		if (res > 0)
		{
			auto rate = (int)(res * 100);

			if (rand() % 100 < rate)
			{
				Option3 = 4; //+16
				Option2 = 1; //+L
			}
		}

		auto setOption = 0;
		auto excOption = 0;

		if (lpGroup->exc == TRUE)
		{
			excOption = NewOptionRand(0);
		}
		else if (lpGroup->anc == TRUE)
		{
			setOption = gSetItemOption.GenSetOption(type);
		}

		auto maxSocket = 0;
		if (g_SocketOption.CheckItemType(type) == TRUE)
		{
			maxSocket = lpGroup->max_sock;
		}

		ItemSerialCreateSend(lpKiller->m_Index, (BYTE)lpKiller->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, lpKiller->m_Index, excOption, setOption, maxSocket);

		CItem EventItem;

		EventItem.Convert(type, Option1, Option2, Option3, 0, 1, 0, NULL, 0xFF, 0, 3);

		LogAddTD("[%s][%s][CustomBoxDrop][%s] : (%d)(X:%d/Y:%d) Item:%s(%d) Level:%d Op1:%d Op2:%d Op3:%d Exc:%d Set:%d MaxSkt:%d",
			lpKiller->AccountID, lpKiller->Name, this->m_sName, lpKiller->MapNumber, lpKiller->X, lpKiller->Y, EventItem.GetName(),
			type, level, Option1, Option2, Option3, excOption, setOption, maxSocket);
	}

	char tmp[256] = { 0 };
	sprintf(tmp, "%s Killed %s", lpKiller->Name, this->m_sName);
	AllSendServerMsg(tmp);
}