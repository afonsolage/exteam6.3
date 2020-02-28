#include "stdafx.h"
#include "Interface.h"
#include "Protocol.h"

class cHpBar
{
	private:
		BOOL isDraw;
		short aIndex;
		int HP;
		int MaxHP;
	public:
		void Load();
		//void SetupMob(int Life, int MaxLife, short index);
		void Recv(PMSG_ATTACKRESULT * Recv);
		void Draw();
		void WorkHpBar(bool work);
		short RetIndex();
};
extern cHpBar HpBar;
