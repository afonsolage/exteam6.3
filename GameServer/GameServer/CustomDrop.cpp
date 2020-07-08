#include "stdafx.h"
#include "CustomDrop.h"
#include "..\include\readscript.h"
#include "..\common\winutil.h"
#include "logproc.h"
#include "GameMain.h"
#include "DSProtocol.h"
#include "gObjMonster.h"
#include "..\common\SetItemOption.h"

bool sortCustomDrop(const CustomGroup &a, const CustomGroup &b)
{
	return a.rate < b.rate;
}


CCustomDrop::CCustomDrop(void)
{
}


CCustomDrop::~CCustomDrop(void)
{
}

void CCustomDrop::Init()
{
	memset(m_sName, 0, 255);
	m_iDropZen = 0;
	m_groups.clear();
}

void CCustomDrop::LoadItem(LPSTR script_file)
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
				CustomGroup group;

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
		std::sort(this->m_groups.begin(), this->m_groups.end(), sortCustomDrop);

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

CustomGroup* CCustomDrop::GetGroup(int rnd)
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

int CCustomDrop::RndRange(int min, int max)
{
	return (rand() % ((max - min) + 1)) + min;
}

int CCustomDrop::IsProcRnd(int proc, int max)
{
	return rand() % max < proc;
}

void CCustomDrop::DropItem(LPOBJ lpObj)
{
	float dur;
	int type;
	int level;
	BYTE x;
	BYTE y;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum;

	srand((unsigned int)(time(NULL) * lpObj->m_Index));

	for (auto i = 0; i < this->m_iDropCount; i++)
	{
		int v = rand();
		int rnd = v % 10000;

		if (m_iDropZen > 0 && rnd < m_iDropZen)
		{
			int zen = this->RndRange(m_iMinZen, m_iMaxZen);
			x = lpObj->X - 2;
			y = lpObj->Y - 2;
			x += rand() % 3;
			y += rand() % 3;
			MapC[lpObj->MapNumber].MoneyItemDrop(zen, x, y);
			continue;
		}

		CustomGroup* lpGroup = GetGroup(rnd);

		if (lpGroup == NULL || lpGroup->rate == 0 || lpGroup->items.size() == 0)
		{
			LogAddTD("[%s][%s][CustomBossDrop][%s] : (%d)(X:%d/Y:%d) Invalid group at rnd %d",
				lpObj->AccountID, lpObj->Name, this->m_sName, lpObj->MapNumber, lpObj->X, lpObj->Y, rnd);
			continue;
		}

		std::pair<int, int> item = lpGroup->GetRandomItem();

		type = ItemGetNumberMake(item.first, item.second);
		level = this->RndRange(lpGroup->min_lvl, lpGroup->max_lvl);
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
		
		x = lpObj->X;
		y = lpObj->Y;
		if (gObjGetRandomFreeLocation(lpObj->MapNumber, (BYTE&)x, (BYTE&)y, 3, 3, 30) == false)
		{
			x = lpObj->X;
			y = lpObj->Y;
		}

		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, lpObj->m_Index, excOption, setOption, maxSocket);

		CItem EventItem;

		EventItem.Convert(type, Option1, Option2, Option3, 0, 1, 0, NULL, 0xFF, 0, 3);

		LogAddTD("[%s][%s][CustomDrop][%s] : (%d)(X:%d/Y:%d) Item:%s(%d) Level:%d Op1:%d Op2:%d Op3:%d Exc:%d Set:%d MaxSkt:%d",
			lpObj->AccountID, lpObj->Name, this->m_sName, lpObj->MapNumber, lpObj->X, lpObj->Y, EventItem.GetName(),
			type, level, Option1, Option2, Option3, excOption, setOption, maxSocket);
	}
}