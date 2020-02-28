#define _QUEST_SYSTEM_H_
#ifdef _QUEST_SYSTEM_H_

#define S5MAX_QUEST 1000
#define ELFQUEST_DIR "..\\Data\\Quest\\ElfQuest.ini"
#define GENSQUEST_DIR "..\\Data\\Quest\\GensQuest.ini"

class NewS5Quest
{
private:
	struct
	{
		int Mob;
		int CountMob;
		int Proc;
		char MSG[50];
		char MS2[50];
		int iType;
		int iIndex;
		int iLevel;
		int iCount;
	}ElfQuest[S5MAX_QUEST];
	int eCount;

	struct
	{
		int Mob;
		int CountMob;
		int Proc;
		char MSG[50];
		char MS2[50];
		int Contribution;
	}GensQuest[S5MAX_QUEST];
	int gCount;

	void ElfMainQuest(LPOBJ lpObj);
	void GensMainQuest(LPOBJ lpObj);

	void ElfMonsterKillProc(LPOBJ lpObj, LPOBJ lpTargetObj);
	void GensMonsterKillProc(LPOBJ lpObj, LPOBJ lpTargetObj);

	void ElfReward(LPOBJ lpObj,int Rew);
	void GensReward(LPOBJ lpObj,int Rew);
public:
	void ReadConfig();
	void NPCQuest(int aIndex);

	void MainKillMonster(LPOBJ lpObj, LPOBJ lpTargetObj);
	void Info(int aIndex);

};
extern NewS5Quest S5Quest;

#endif _QUEST_SYSTEM_H_