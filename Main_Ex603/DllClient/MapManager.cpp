#include "stdafx.h"
#include "MapManager.h"
#include "TMemory.h"
#include "Import.h"

#if(CUSTOM_MAP_MANAGER)

CMapManager g_MapManager;

CMapManager::CMapManager()
{
	this->m_Enable = false;
}

CMapManager::~CMapManager()
{
}

void CMapManager::Load()
{
	SetOp((LPVOID)0x0047FD98, (LPVOID)this->NewMap, ASM::JMP);

	SetOp((LPVOID)0x005AD21C, (LPVOID)this->MapEffectAdded, ASM::CALL);	//005AD21C  CALL Main.008E5D90
	SetOp((LPVOID)0x005EEB25, (LPVOID)this->MapEffectAdded, ASM::CALL);	//005EEB25  CALL Main.008E5D90
	SetOp((LPVOID)0x00813F1D, (LPVOID)this->MapEffectAdded, ASM::CALL);	//00813F1D  CALL Main.008E5D90
	SetOp((LPVOID)0x008DE68B, (LPVOID)this->MapEffectAdded, ASM::CALL);	//008DE68B  CALL Main.008E5D90	Sound
	SetOp((LPVOID)0x008E3519, (LPVOID)this->MapEffectAdded, ASM::CALL);	//008E3519  CALL Main.008E5D90	fix effect
	SetOp((LPVOID)0x008E390C, (LPVOID)this->MapEffectAdded, ASM::CALL);	//008E390C  CALL Main.008E5D90	?
	SetOp((LPVOID)0x008E41E9, (LPVOID)this->MapEffectAdded, ASM::CALL);	//008E41E9  CALL Main.008E5D90
	SetOp((LPVOID)0x008E480F, (LPVOID)this->MapEffectAdded, ASM::CALL);	//008E480F  CALL Main.008E5D90
	SetOp((LPVOID)0x008E5969, (LPVOID)this->MapEffectAdded, ASM::CALL);	//008E5969  CALL Main.008E5D90
	SetOp((LPVOID)0x008E5DB9, (LPVOID)this->MapEffectAdded, ASM::CALL);	//008E5DB9  CALL Main.008E5D90
	SetOp((LPVOID)0x008E5E09, (LPVOID)this->MapEffectAdded, ASM::CALL);	//008E5E09  CALL Main.008E5D90
	SetOp((LPVOID)0x008E5E59, (LPVOID)this->MapEffectAdded, ASM::CALL);	//008E5E59  CALL Main.008E5D90

	SetOp((LPVOID)0x005F1696, (LPVOID)this->MapLightingEffect3, ASM::JMP);

	SetOp((LPVOID)0x004D9473, (LPVOID)this->MapRainEffect1, ASM::JMP);
	SetOp((LPVOID)0x0072BD76, (LPVOID)this->MapRainEffect2, ASM::JMP);
	SetOp((LPVOID)0x0072C46F, (LPVOID)this->MapRainEffect3, ASM::JMP);
	SetOp((LPVOID)0x0072C8A0, (LPVOID)this->MapRainEffect4, ASM::JMP);
	SetOp((LPVOID)0x0072CD18, (LPVOID)this->MapRainEffect5, ASM::JMP);
	SetOp((LPVOID)0x0072C50B, (LPVOID)this->MapRainEffect6, ASM::JMP);

	SetOp((LPVOID)0x0062F45D, (LPVOID)MapDrawAlphaRock6, ASM::CALL);
	SetOp((LPVOID)0x005D9654, (LPVOID)MapDrawAlphaRock6, ASM::CALL);
}

__declspec(naked)void CMapManager::NewMap()
{
	static int MapNum = 0;
	static int NewMapJmp = 0x0047FDA1;
	static int OldMapJmp = 0x0047FDB3;

	_asm
	{
		MOV EAX, DWORD PTR DS:[0x0E61E18]
		MOV MapNum, EAX
	}

	if(MapNum == 40 || MapNum == 82
//#if(EVENT_GROUPVSGROUP)		
		|| MapNum == 83
//#endif
		)
	{
		_asm
		{
			JMP NewMapJmp
		}
	}

	_asm
	{
		JMP OldMapJmp
	}
}

bool CMapManager::MapEffectAdded()
{
	bool Result = false;

	if(pMapNumber == 68)
	{
		Result = true;
	}
	else if(pMapNumber == 82 || pMapNumber == 83)
	//else if(pMapNumber == 83)
	{
		Result = true;
	}

	return Result;
}

__declspec(naked)void CMapManager::MapLightingEffect3()
{
	static DWORD dwJmpLightON3 = 0x005F16A3;
	static DWORD dwJmpLightOFF3 = 0x005F1848;
	static DWORD dwJmpLightNew3 = 0x005F16BC;

	if(pMapNumber == 10)
	{
		_asm { JMP dwJmpLightON3 }
	}
	else if(pMapNumber == 82 && rand()%20 == 0)
	{
		_asm { JMP dwJmpLightNew3 }
	}
	else
	{
		_asm { JMP dwJmpLightOFF3 }
	}
}

__declspec(naked)void CMapManager::MapRainEffect1()	//enable rain
{
	static DWORD dwJmpRain1ON = 0x004D9559;
	static DWORD dwJmpRain1OFF = 0x004D9480;

	if(pMapNumber == 10 || pMapNumber == 82)
	{
		_asm { JMP dwJmpRain1ON }
	}
	else
	{
		_asm { JMP dwJmpRain1OFF }
	}
}

__declspec(naked)void CMapManager::MapRainEffect2()	//time rain
{
	static DWORD dwJmpRain2ON = 0x0072BD86;
	static DWORD dwJmpRain2OFF = 0x0072BD7F;
	static DWORD dwJmpRAinForever = 0x0072BDA8;

	if(pMapNumber == 10)
	{
		_asm { JMP dwJmpRain2ON }
	}
	else if(pMapNumber == 82)
	{
		_asm { JMP dwJmpRAinForever }
	}
	else
	{
		_asm { JMP dwJmpRain2OFF }
	}
}

__declspec(naked)void CMapManager::MapRainEffect3()	//end rain
{
	static DWORD dwJmpRain3ON = 0x0072C47F;
	static DWORD dwJmpRain3OFF = 0x0072C478;

	if(pMapNumber == 10 || pMapNumber == 82)
	{
		_asm { JMP dwJmpRain3ON }
	}
	else
	{
		_asm { JMP dwJmpRain3OFF }
	}
}

__declspec(naked)void CMapManager::MapRainEffect4()	//draw rain
{
	static DWORD dwJmpRain4ON = 0x0072C8B8;
	static DWORD dwJmpRain4OFF = 0x0072C8A9;

	if(pMapNumber == 10 || pMapNumber == 82)
	{
		_asm { JMP dwJmpRain4ON }
	}
	else
	{
		_asm { JMP dwJmpRain4OFF }
	}
}

__declspec(naked)void CMapManager::MapRainEffect5()	//color rain
{
	static DWORD dwJmpRain5ON = 0x0072CD81;
	static DWORD dwJmpRain5OFF = 0x0072CD21;

	if(pMapNumber == 10 || pMapNumber == 82)
	{
		_asm { JMP dwJmpRain5ON }
	}
	else
	{
		_asm { JMP dwJmpRain5OFF }
	}
}

__declspec(naked)void CMapManager::MapRainEffect6()	//rain effect end
{
	static DWORD dwJmpRain6ON = 0x0072C540;
	static DWORD dwJmpRain6OFF = 0x0072C514;

	if(pMapNumber == 10 || pMapNumber == 82)
	{
		_asm { JMP dwJmpRain6ON }
	}
	else
	{
		_asm { JMP dwJmpRain6OFF }
	}
}

bool CMapManager::MapDrawAlphaRock6()
{
	bool Result = false;

	if(pMapNumber == 80 || pMapNumber == 81)
	{
		Result = true;
	}

	if(pMapNumber == 82)
	{
		Result = true;
	}

	return Result;
}

#endif