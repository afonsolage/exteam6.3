#include "stdafx.h"
#include "WzAG.h"
#include "GameMain.h"
// -------------------------------------------------------------------------------

FILE * SMDFile;
char * DataBuffer;
DWORD DataBufferSize;
// -------------------------------------------------------------------------------

WzAG gWzAG;
// -------------------------------------------------------------------------------

BYTE szServerKey[19] = {
	0x29, 0x23, 0xBE, 0x00, 0xE1, 
	0x6C, 0xD6, 0xAE, 0x52, 0x90, 
	0x49, 0xF1, 0xF1, 0xBB, 0xE9,
	0xEB, 0xB3, 0xA6, 0xDB };
// -------------------------------------------------------------------------------

char sztmpServerName[51];
// --------------------------------------------------------------------------------

void GameServerAuthCallBackFunc(int Type, int Data)
{
	if (!Type)
	{
		switch (Data)
		{
		case 1:	ReadCommonServerInfo();			break;
		case 2:	GameMonsterAllCloseAndReLoad();	break;
		case 3:	ReadServerInfo();				break;
		}
	}
}
// -------------------------------------------------------------------------------

void WzAG::GetClientVersion(char * ClientVersion, char * ClientSerial)
{
	char ClientVersionBuff[20];
	char ClientSerialBuff[20];
	// ----
	GetPrivateProfileString("GameServerInfo", "ClientExeVersion", "", ClientVersionBuff, 20, "..\\Data\\Other\\commonloc.cfg");
	GetPrivateProfileString("GameServerInfo", "ClientExeSerial", "", ClientSerialBuff, 20, "..\\Data\\Other\\commonloc.cfg");
	// ----
	memcpy(ClientVersion, ClientVersionBuff, 20);
	memcpy(ClientSerial, ClientSerialBuff, 20);
}
// -------------------------------------------------------------------------------

char * WzAG::GetDataBuffer()
{
	return DataBuffer;
}
// -------------------------------------------------------------------------------

int WzAG::GetDataBufferSize()
{
	return DataBufferSize;
}
// -------------------------------------------------------------------------------

void WzAG::GetKey(char * Key, int StartIndex, int Len)
{
	memcpy(Key, szServerKey, sizeof(szServerKey));
}
// -------------------------------------------------------------------------------

void WzAG::ReleaseData()
{
	delete [] DataBuffer;
	DataBufferSize = 0;
}
// -------------------------------------------------------------------------------

void WzAG::RequestData(int Type)
{
	const char *v2; // esi@1
	FILE *v3; // eax@38
	int result; // eax@40

	v2 = 0;
	switch ( Type )
	{
	case 0:
		v2 = "..\\Data\\Items\\Item.txt";
		break;
	case 1:
		v2 = "..\\Data\\Items\\Item.txt";
		break;
	case 2:
		v2 = "..\\Data\\Skills\\Skill.txt";
		break;
	case 3:
		v2 = "..\\Data\\Skills\\Skill.txt";
		break;
	case 4:
		v2 = "..\\Data\\Quest.txt";
		break;
	case 5:
		v2 = "..\\Data\\Quest.txt";
		break;
	case 6:
		v2 = "..\\Data\\Other\\CheckSum.dat";
		break;
	case 7:
		v2 = "..\\Data\\Monsters\\Monster.txt";
		break;
	case 8:
		v2 = "..\\Data\\Gate.txt";
		break;
	case 9:
		v2 = "..\\Data\\Monsters\\MonsterSetBase.txt";
		break;
	case 11:
		v2 = "..\\data\\Shops\\Shop0.txt";
		break;
	case 12:
		v2 = "..\\data\\Shops\\Shop1.txt";
		break;
	case 13:
		v2 = "..\\data\\Shops\\Shop2.txt";
		break;
	case 14:
		v2 = "..\\data\\Shops\\Shop3.txt";
		break;
	case 15:
		v2 = "..\\data\\Shops\\Shop4.txt";
		break;
	case 16:
		v2 = "..\\data\\Shops\\Shop5.txt";
		break;
	case 17:
		v2 = "..\\data\\Shops\\Shop6.txt";
		break;
	case 18:
		v2 = "..\\data\\Shops\\Shop7.txt";
		break;
	case 19:
		v2 = "..\\data\\Shops\\Shop8.txt";
		break;
	case 20:
		v2 = "..\\data\\Shops\\Shop9.txt";
		break;
	case 21:
		v2 = "..\\data\\Shops\\Shop10.txt";
		break;
	case 22:
		v2 = "..\\data\\Shops\\Shop11.txt";
		break;
	case 23:
		v2 = "..\\data\\Shops\\Shop12.txt";
		break;
	case 24:
		v2 = "..\\Data\\MoveReq.txt";
		break;
	case 25:
		v2 = "..\\Data\\MoveReq.txt";
		break;
	case 26:
		v2 = "..\\Data\\Items\\ItemSetOption.txt";
		break;
	case 27:
		v2 = "..\\Data\\Items\\ItemSetOption.txt";
		break;
	case 28:
		v2 = "..\\Data\\Items\\ItemSetType.txt";
		break;
	case 29:
		v2 = "..\\Data\\Items\\ItemSetType.txt";
		break;
	case 30:
		v2 = "..\\data\\Shops\\Shop13.txt";
		break;
	case 31:
		v2 = "..\\data\\Shops\\Shop14.txt";
		break;
	case 32:
		v2 = "..\\data\\Shops\\Shop15.txt";
		break;
	case 33:
		v2 = "..\\data\\Shops\\Shop16.txt";
		break;
	case 34:
		v2 = "..\\data\\Shops\\Shop17.txt";
		break;
	case 35:
		v2 = "..\\data\\Shops\\Shop18.txt";
		break;
	case 36:
		v2 = "..\\data\\Shops\\Shop19.txt";
		break;
	case 10:
		break;
	}
	v3 = fopen(v2, "rb");	//ok
	FILE * File = v3;
	if ( !v3 )
	{
		MessageBoxA(0, v2, "Error!", 0);
		ExitProcess(0);
	}
	fseek(v3, 0, 2);
	DataBufferSize = ftell(File);
	if ( !DataBufferSize )
	{
		MessageBoxA(0, v2, "Error!", 0);
		ExitProcess(0);
	}
	fseek(File, 0, 0);
	if( DataBuffer != NULL )
	{
		delete[] DataBuffer;
	}
	DataBuffer = new char[DataBufferSize + 1];
	// ----
	fread((void *)DataBuffer, DataBufferSize, 1, File);
	fclose(File);
}
// -------------------------------------------------------------------------------

bool WzAG::SetInfo(int CountryCode, BYTE Partition, short ServerCode, char * ServerVersion, char * ServerName, int ServerType, void(*CallBack)(int, int))
{
	if( DataBuffer )		
	{
		delete [] DataBuffer;
	}
	// ----
	if( DataBufferSize )
	{
		DataBufferSize = 0;
	}
	// ----
	strcpy(sztmpServerName, ServerName);
	// ----
	return true;
}
// -------------------------------------------------------------------------------

void WzAG::SetSubInfo(int ServerMaxUser, int ObjTotalUser, int MonsterHP, int ItemDropPer, float AddExperience, int EventFlag)
{
	// ----
}
// -------------------------------------------------------------------------------

char * WzAG::GetCountryNameByCode(int iCountryCode)
{
	return (iCountryCode==1)?("English"):(iCountryCode==2)?("Japan"):(iCountryCode==3)?("China"):(iCountryCode==4)?("Taiwan"):(iCountryCode==5)?("Thailand"):(iCountryCode==6)?("Phillipines"):(iCountryCode==7)?("Vietnam"):("Korea");
}
// -------------------------------------------------------------------------------

char * WzAG::GetServerTypeByType(int ServerType)
{
	return (ServerType==1)?("TestServer"):(ServerType==2)?("Internal Server"):("MainServer");
}
// -------------------------------------------------------------------------------

char * WzAG::GetEventFlag(int Flag)
{
	char * ReturnText = new char[512];
	memset(ReturnText, 0, 512);
	// ----
	if(EVENT_ACTIVE(1))		strcat(ReturnText, "| Devil Square Event | ");
	if(EVENT_ACTIVE(2))		strcat(ReturnText, "| Blood Castle Event | ");
	if(EVENT_ACTIVE(256))	strcat(ReturnText, "| XMas Star Event | ");
	if(EVENT_ACTIVE(512))	strcat(ReturnText, "| Fire Cracker Event | ");
	if(EVENT_ACTIVE(1024))	strcat(ReturnText, "| Heart Of Love Event | ");
	if(EVENT_ACTIVE(2048))	strcat(ReturnText, "| Medal Event | ");
	if(EVENT_ACTIVE(4096))	strcat(ReturnText, "| Ring Attack Event | ");
	if(EVENT_ACTIVE(8192))	strcat(ReturnText, "| EventChip Event | ");
	if(EVENT_ACTIVE(16384))	strcat(ReturnText, "| Eledora Event | ");
	if(EVENT_ACTIVE(65536))	strcat(ReturnText, "| NProtect CheckSum | ");
	// ----
	return ReturnText;
}
// -------------------------------------------------------------------------------