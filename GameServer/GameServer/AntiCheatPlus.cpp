#include "StdAfx.h"
#include "AntiCheatPlus.h"
#include "..\\include\\ReadScript_ex.h"
#include "GameMain.h"
#include "LogToFile.h"
#include "logproc.h"
#include "user.h"
#include "ConnectEx.h"
#include "ExLicense.h"
#include "Crc32.h"

#if(ANTI_CHEAT_PLUS==TRUE)
// ----------------------------------------------------------------------------------------------

CLogToFile g_AntiCheatLog("AntiCheat", "..\\AntiCheat\\LOG", TRUE);
// ----------------------------------------------------------------------------------------------

AntiCheatPlus g_AntiCheatPlus;
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::Init()
{
	ZeroMemory(&this->TitleName, sizeof(this->TitleName));
	ZeroMemory(&this->ClassName, sizeof(this->ClassName));
	ZeroMemory(&this->InjectName, sizeof(this->InjectName));
	ZeroMemory(&this->ProcessName, sizeof(this->ProcessName));

	//ZeroMemory(&this->blockhdd, sizeof(this->blockhdd));
	this->blockhdd.clear();
#if(ANTI_CHEAT_PLUS_CRC)
	this->CrcData.clear();
#endif

	this->TitleCount = 0;
	this->ClassCount = 0;
	this->InjectCount = 0;
	this->ProcessCount = 0;

	this->Enable = false;

	this->DumpActive = false;
	this->TitleActive = false;
	this->ClassActive = false;
	this->InjectActive = false;
	this->ProcessActive = false;
	this->EliteActive = true;
	this->MultiWindows = true;
#if(ANTI_CHEAT_PLUS_CRC)
	this->CRCActive = false;
#endif

	this->DumpTime = 10000;
	this->TitleTime = 10000;
	this->ClassTime = 10000;
	this->InjectTime = 10000;
	this->ProcessTime = 10000;
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::Load()
{
	this->Init();

	if(!g_ExLicense.user.AntiCheatPlus)
	{
		return;
	}
	
	this->ReadConfig("..\\AntiCheat\\AntiCheatMain.ini");
	this->Read(eTitleType, "..\\AntiCheat\\CheatBase\\TitleCheat.txt");
	this->Read(eClassType, "..\\AntiCheat\\CheatBase\\ClassCheat.txt");
	this->Read(eInjectType, "..\\AntiCheat\\CheatBase\\InjectCheat.txt");
	this->Read(eProcessType, "..\\AntiCheat\\CheatBase\\ProcessCheat.txt");

	this->ReadBlockHdd("..\\AntiCheat\\BlackList\\HDD_Data.txt");
#if(ANTI_CHEAT_PLUS_CRC)
	this->ReadCRC("../AntiCheat/CheckFiles");
#endif
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::ReadConfig(char* File)
{
	this->Enable = GetPrivateProfileInt("ExTeam", "Enable", 0, File);

	this->DumpActive = GetPrivateProfileInt("ExTeam", "DumpActive", 0, File);
	this->TitleActive = GetPrivateProfileInt("ExTeam", "TitleActive", 0, File);
	this->ClassActive = GetPrivateProfileInt("ExTeam", "ClassActive", 0, File);
	this->InjectActive = GetPrivateProfileInt("ExTeam", "InjectActive", 0, File);
	this->ProcessActive = GetPrivateProfileInt("ExTeam", "ProcessActive", 0, File);
	this->EliteActive  = GetPrivateProfileInt("ExTeam", "EliteActive", 0, File);
	this->MultiWindows = GetPrivateProfileInt("ExTeam", "MultiWindows", 1, File);

	this->m_EnableMaxWindow = GetPrivateProfileInt("ExTeam", "EnableMaxWindow", 0, File);
	this->m_MaxWindow = GetPrivateProfileInt("ExTeam", "MaxWindow", 100, File);
	#if(ANTI_CHEAT_PLUS_CRC)
	this->CRCActive = GetPrivateProfileInt("ExTeam", "CheckFileActive", 0, File);
	#endif
	this->DumpTime = GetPrivateProfileInt("ExTeam", "DumpTime", 10000, File);
	this->TitleTime = GetPrivateProfileInt("ExTeam", "TitleTime", 10000, File);
	this->ClassTime = GetPrivateProfileInt("ExTeam", "ClassTime", 10000, File);
	this->InjectTime = GetPrivateProfileInt("ExTeam", "InjectTime", 10000, File);
	this->ProcessTime = GetPrivateProfileInt("ExTeam", "ProcessTime", 10000, File);
	#if(SCANER_ITEM_DUPE)
	this->ScanItemDupeActive = GetPrivateProfileInt("ExTeam", "ScanItemDupeActive", 0, File);
	#endif
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::Read(int type, char* File)
{
	SMDFile = fopen(File, "r");
	if( SMDFile == NULL )
	{
		return;
	}
	while(true)
	{
		SMDToken Token = GetToken();
		if( Token == END || !strcmp(TokenString, "end") )
		{
			break;
		}
		if(type==eTitleType)
		{
			if(this->TitleCount >= MAX_AH_DB)
			{
				break;
			}
			memcpy(this->TitleName[this->TitleCount],TokenString,sizeof(this->TitleName[this->ClassCount]));
			this->TitleCount++;
		}
		if(type==eClassType)
		{
			if(this->ClassCount >= MAX_AH_DB)
			{
				break;
			}
			memcpy(this->ClassName[this->ClassCount],TokenString,sizeof(this->ClassName[this->ClassCount]));
			this->ClassCount++;
		}
		if(type==eInjectType)
		{
			if(this->InjectCount >= MAX_AH_DB)
			{
				break;
			}
			memcpy(this->InjectName[this->InjectCount],TokenString,sizeof(this->InjectName[this->InjectCount]));
			this->InjectCount++;
		}
		if(type==eProcessType)
		{
			if(this->ProcessCount >= MAX_AH_DB)
			{
				break;
			}
			memcpy(this->ProcessName[this->ProcessCount],TokenString,sizeof(this->ProcessName[this->ProcessCount]));
			this->ProcessCount++;
		}
	}

	if(type==eTitleType)
	{
		LogAdd("[Anti-Cheat] [Title Window] Loaded: %d", this->TitleCount);
	}
	if(type==eClassType)
	{
		LogAdd("[Anti-Cheat] [Class Window] Loaded: %d", this->ClassCount);
	}
	if(type==eInjectType)
	{
		LogAdd("[Anti-Cheat] [Inject Dll] Loaded: %d", this->InjectCount);
	}
	if(type==eProcessType)
	{
		LogAdd("[Anti-Cheat] [Process] Loaded: %d", this->ProcessCount);
	}

	fclose(SMDFile);
	SMDFile = NULL;
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::ReadBlockHdd(char* filename)
{
	char szHwnd[256] = { 0 };

	SMDFile = fopen(filename, "r");

	if( SMDFile == NULL )
	{
		return;
	}

	while(true)
	{
		SMDToken Token = GetToken();

		if( Token == END || !strcmp(TokenString, "end") )
		{
			break;
		}

		BlockHDD_DATA List;

		memcpy(szHwnd, TokenString, sizeof(szHwnd));

		sscanf_s(szHwnd, "%u", &List.hddid);

		this->blockhdd.push_back(List);
	}

	fclose(SMDFile);
	SMDFile = NULL;
}

#if(ANTI_CHEAT_PLUS_CRC)
void AntiCheatPlus::ReadCRC(char* filename)
{
	char szPath[256];
	char szFolder[256];

	sprintf(szPath, "%s/*", filename);

	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(szPath, &wfd);

	if(hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}

	while(true)
	{
		if(strcmp(wfd.cFileName,".") && strcmp(wfd.cFileName,".."))
		{
			sprintf(szFolder, "%s/%s", filename, wfd.cFileName);

			if(wfd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				this->ReadCRC(szFolder);
			}
			else if(wfd.dwFileAttributes == FILE_ATTRIBUTE_ARCHIVE)
			{
				CRC_DATA List;
				List.Key = g_Crc32.Get(szFolder);
				memcpy(List.Path, szFolder, sizeof(List.Path));
				this->CrcData.push_back(List);		
			}
		}

		if(FindNextFile(hFind, &wfd) == NULL)
		{
			break;
		}
	}
	
	FindClose(hFind);

	//SMDFile = fopen(filename, "r");

	//if( SMDFile == NULL )
	//{
	//	return;
	//}

	//while(true)
	//{
	//	SMDToken Token = GetToken();

	//	if( Token == END || !strcmp(TokenString, "end") )
	//	{
	//		break;
	//	} 

	//	CRC_DATA List;

	//	char szCRC[256] = { 0 };
	//	memcpy(szCRC, TokenString, sizeof(szCRC));

	//	sscanf_s(szCRC, "%X", &List.Key);

	//	Token = GetToken();
	//	memcpy(List.Path, TokenString, sizeof(List.Path));
	//	
	//	this->CrcData.push_back(List);		
	//}

	//fclose(SMDFile);
	//SMDFile = NULL;
}
#endif

void AntiCheatPlus::GC_Cheat(int UserIndex)
{
	if(!this->Enable)
	{
		return;
	}
	this->GC_Init(UserIndex);
	this->GC_Config(UserIndex);
	this->GC_Title(UserIndex);
	this->GC_Class(UserIndex);
	this->GC_Inject(UserIndex);
	this->GC_Process(UserIndex);
#if(ANTI_CHEAT_PLUS_CRC)
	this->GC_Crc(UserIndex);
#endif
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::CG_Cheater(PMST_CheaterUser*aRecv, int UserIndex)
{
	if (UserIndex < 0 || UserIndex > OBJMAX-1 )
	{
		return;
	}

	LPOBJ lpUser = &gObj[UserIndex];

	if(aRecv->Result)
	{
		g_AntiCheatLog.Output("[%s][%s] ip[%s] hdd[%d] -> %s", lpUser->AccountID, lpUser->Name, lpUser->Ip_addr, lpUser->hdd_id, aRecv->CheatText);
		GCServerMsgStringSend("..:: Anti-Cheat ::..", lpUser->m_Index, 0);
		GCServerMsgStringSend(aRecv->CheatText, lpUser->m_Index, 0);
		LogAddC(2,"[%s][%s][%s][%d] %s", lpUser->AccountID, lpUser->Name, lpUser->Ip_addr, lpUser->hdd_id, aRecv->CheatText);
#ifdef _RECONNECT_				
		g_ConnectEx.SendClose(UserIndex,NORM_DC);
#else
		CloseClient(UserIndex);
#endif
	}
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::CG_HddSend(CG_PMSG_HDDKEY* aRecv, int UserIndex)
{
	if(!aRecv)
	{
		return;
	}

	if(OBJMAX_RANGE(UserIndex) == 0)
	{
		return;
	}

	LPOBJ lpUser = &gObj[UserIndex];

	lpUser->hdd_id = aRecv->hdd_id;

	if(!this->Enable)
	{
		return;
	}

	for(int i = 0; i < this->blockhdd.size(); i++)
	{
		BlockHDD_DATA & CheckList = this->blockhdd[i];
		if(CheckList.hddid != lpUser->hdd_id)
		{
			continue;
		}
		//GCServerMsgStringSend("..:: Anti-Cheat ::..", lpUser->m_Index, 0);
		//GCServerMsgStringSend("PC Block List", lpUser->m_Index, 0);
#ifdef _RECONNECT_				
		g_ConnectEx.SendClose(UserIndex,NORM_DC);
#else
		CloseClient(UserIndex);
#endif
	}
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Config(int UserIndex)
{
	PMSG_AH_CONFIG pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
	pMsg.type = eAH_Config;

	pMsg.DumpActive = this->DumpActive;
	pMsg.TitleActive = this->TitleActive;
	pMsg.ClassActive = this->ClassActive;
	pMsg.InjectActive = this->InjectActive;
	pMsg.ProcessActive = this->ProcessActive;
	pMsg.EliteActive = this->EliteActive;
	pMsg.MultiWindows = this->MultiWindows;

	pMsg.DumpTime = this->DumpTime;
	pMsg.TitleTime = this->TitleTime;
	pMsg.ClassTime = this->ClassTime;
	pMsg.InjectTime = this->InjectTime;
	pMsg.ProcessTime = this->ProcessTime;

	DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Init(int UserIndex)
{
	PMSG_AH_SUB pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
	pMsg.type = eAH_Init;
	DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Title(int UserIndex)
{
	for(int i = 0; i < this->TitleCount; i++)
	{
		PMSG_CheatBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Title;
		memcpy(pMsg.Name,this->TitleName[i],sizeof(pMsg.Name));
		DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
	}
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Class(int UserIndex)
{
	for(int i = 0; i < this->ClassCount; i++)
	{
		PMSG_CheatBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Class;
		memcpy(pMsg.Name,this->ClassName[i],sizeof(pMsg.Name));
		DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
	}
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Inject(int UserIndex)
{
	for(int i = 0; i < this->InjectCount; i++)
	{
		PMSG_CheatBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Inject;
		memcpy(pMsg.Name,this->InjectName[i],sizeof(pMsg.Name));
		DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
	}
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Process(int UserIndex)
{
	for(int i = 0; i < this->ProcessCount; i++)
	{
		PMSG_CheatBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Process;
		memcpy(pMsg.Name,this->ProcessName[i],sizeof(pMsg.Name));
		DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
	}
}
// ----------------------------------------------------------------------------------------------

#if(ANTI_CHEAT_PLUS_CRC)
void AntiCheatPlus::GC_Crc(int UserIndex)
{
	if(!this->CRCActive)
	{
		return;
	}

	for(int i = 0; i < this->CrcData.size(); i++)
	{
		PMSG_CRCBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFE, sizeof(pMsg));
		pMsg.num = i;
		pMsg.key = this->CrcData[i].Key;
		memcpy(pMsg.path,&this->CrcData[i].Path[24],sizeof(pMsg.path));
		DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
	}
}
#endif
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::CheckMultiWindow(int UserIndex)
{
	if(!this->Enable || this->MultiWindows)
	{
		return;
	}

	if(OBJMAX_RANGE(UserIndex) == FALSE)
	{
		return;
	}

	LPOBJ lpUser = &gObj[UserIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}	

	for(int n=OBJ_STARTUSERINDEX;n<OBJMAX;n++)
	{
		LPOBJ lpTempObj = &gObj[n];

		if(lpTempObj->Connected < PLAYER_PLAYING)
		{
			continue;
		}	

		if(lpTempObj->Type != OBJ_USER)
		{
			continue;
		}

		if(UserIndex == n)
		{
			continue;
		}

		if(lpUser->hdd_id != lpTempObj->hdd_id)
		{
			continue;
		}

		GCServerMsgStringSend("..:: Anti-Cheat ::..", lpUser->m_Index, 0);
		GCServerMsgStringSend("Multi Windows Blocked", lpUser->m_Index, 0);
#ifdef _RECONNECT_				
		g_ConnectEx.SendClose(UserIndex,NORM_DC);
#else
		CloseClient(UserIndex);
#endif
	}
}
// ----------------------------------------------------------------------------------------------
#if(ANTI_CHEAT_PLUS_CRC)
void AntiCheatPlus::CGAnsUpdateFile(PMSG_UPDATEFILE* lpMsg, int aIndex)
{
	return;
	if(!lpMsg)
	{
		return;
	}

	char szFilePath[128] = { 0 };

	for(int i = 0; i < this->CrcData.size(); i++)
	{
		if(i == lpMsg->num)
		{
			memcpy(szFilePath,this->CrcData[i].Path,sizeof(szFilePath));
			break;
		}
	}

	if(szFilePath[0] == 0)
	{
		return;
	}

	DWORD dwPackSize;
	HANDLE hFileR = CreateFile(szFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0x80, NULL);

	if(hFileR == INVALID_HANDLE_VALUE)
	{
		return;
	}

	int filesize = GetFileSize(hFileR, NULL);
	char* szPackBuff = (char*)malloc(filesize);

	ReadFile(hFileR, szPackBuff, filesize, &dwPackSize, 0);

	if(!dwPackSize)
	{
		return;
	}

	CloseHandle(hFileR);

	PMSG_FILESEND pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFD, sizeof(pMsg));
	pMsg.Stage = 1;
	pMsg.Size = 0;
	memcpy(pMsg.Buff, &szFilePath[24], sizeof(pMsg.Buff));
	DataSend(aIndex, (BYTE*)&pMsg, pMsg.h.size);

	bool Break = false;
	int iStartSend = 0;

	while(true)
	{
		PMSG_FILESEND pMsg2;
		pMsg2.h.set((LPBYTE)&pMsg2, 0xFB, 0xFD, sizeof(pMsg2));
		pMsg2.Stage = 2;
		pMsg2.Size = sizeof(pMsg2.Buff);

		int iTotal = iStartSend + pMsg2.Size;

		if(iTotal > dwPackSize)
		{
			pMsg2.Size -= (iTotal - dwPackSize);
			Break = true;
		}

		memset(pMsg2.Buff, 0, sizeof(pMsg2.Buff));
		memcpy(pMsg2.Buff, &szPackBuff[iStartSend], pMsg2.Size);
		DataSend(aIndex, (BYTE*)&pMsg2, pMsg2.h.size);

		iStartSend += pMsg2.Size;

		if(Break)
		{
			break;
		}
	}

	PMSG_FILESEND pMsg3;
	pMsg3.h.set((LPBYTE)&pMsg3, 0xFB, 0xFD, sizeof(pMsg3));
	pMsg3.Stage = 3;
	pMsg3.Size = 0;
	memset(pMsg3.Buff, 0, sizeof(pMsg3.Buff));
	DataSend(aIndex, (BYTE*)&pMsg3, pMsg3.h.size);

	free(szPackBuff);

	GCServerMsgStringSend("..:: Anti-Cheat ::..", aIndex, 0);
	GCServerMsgStringSend("Restart the client", aIndex, 0);
#ifdef _RECONNECT_				
	g_ConnectEx.SendClose(aIndex,NORM_DC);
#else
	CloseClient(UserIndex);
#endif
}
#endif
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::WraitLog(char* Text)
{
	g_AntiCheatLog.Output(Text);
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::CheckMaxWindow(int UserIndex)
{
	//return;

	if(!this->Enable)
	{
		return;
	}

	if(!this->m_EnableMaxWindow)
	{
		return;
	}

	if(OBJMAX_RANGE(UserIndex) == FALSE)
	{
		return;
	}

	LPOBJ lpUser = &gObj[UserIndex];

	int iWaxCount = 0;

	for(int n = OBJ_STARTUSERINDEX; n < OBJMAX; n++)
	{
		LPOBJ lpTempObj = &gObj[n];

		if(lpTempObj->Connected < PLAYER_PLAYING)
		{
			continue;
		}	

		if(lpTempObj->Type != OBJ_USER)
		{
			continue;
		}

		if(lpTempObj->OffTrade != 0)
		{
			continue;
		}

		if(lpTempObj->OffTrade != 0)
		{
			continue;
		}

		if(lpTempObj->OffExp != 0)
		{
			continue;
		}

		if(lpTempObj->m_OfflineMode != 0)
		{
			continue;
		}

		if(lpUser->hdd_id == lpTempObj->hdd_id)
		{
			iWaxCount++;
		}
	}

	if(iWaxCount > this->m_MaxWindow)
	{
		char szTemp[256] = { 0 };
		sprintf(szTemp, "Max Windows Count: %d", this->m_MaxWindow);
		GCServerMsgStringSend("..:: Anti-Cheat ::..", lpUser->m_Index, 0);
		GCServerMsgStringSend(szTemp, lpUser->m_Index, 0);

		#ifdef _RECONNECT_				
		g_ConnectEx.SendClose(UserIndex,NORM_DC);
		#else
		CloseClient(UserIndex);
		#endif
	}
}
// ----------------------------------------------------------------------------------------------

#if(SCANER_ITEM_DUPE)

void AntiCheatPlus::RunItemDupe()
{
	if(!this->ScanItemDupeActive)
	{
		return;
	}

	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		LPOBJ lpUser = &gObj[aIndex];

		if(lpUser->Connected < PLAYER_PLAYING)
		{
			continue;
		}	

		if(lpUser->OffTrade != 0)
		{
			continue;
		}

		if(lpUser->OffExp != 0)
		{
			continue;
		}

		if(lpUser->m_OfflineMode != 0)
		{
			continue;
		}

		for(int i = 0; i < INVENTORY_SIZE; i++)
		{
			if(!lpUser->pInventory[i].IsItem())
			{
				continue;
			}

			if(!this->CheckItemSerial(lpUser->pInventory[i].m_Type))
			{
				continue;
			}

			int iItemSerial = lpUser->pInventory[i].GetNumber();

			if(!this->CheckItemDupe(aIndex, iItemSerial, i))
			{
				GCServerMsgStringSend("..:: Anti-Cheat ::..", aIndex, 0);
				GCServerMsgStringSend("Inventory Item Dupe", aIndex, 0);

				#ifdef _RECONNECT_				
				g_ConnectEx.SendClose(aIndex,NORM_DC);
				#else
				CloseClient(UserIndex);
				#endif		
				
				break;	
			}
		}

		for(int i = 0; i < WAREHOUSE_SIZE; i++)
		{
			if(!lpUser->pWarehouse[i].IsItem())
			{
				continue;
			}

			if(!this->CheckItemSerial(lpUser->pWarehouse[i].m_Type))
			{
				continue;
			}

			int iNextSerial = lpUser->pWarehouse[i].GetNumber();

			if(!this->CheckWareDupe(aIndex, iNextSerial, i))
			{
				GCServerMsgStringSend("..:: Anti-Cheat ::..", aIndex, 0);
				GCServerMsgStringSend("Warehouse Item Dupe", aIndex, 0);

				#ifdef _RECONNECT_				
				g_ConnectEx.SendClose(aIndex,NORM_DC);
				#else
				CloseClient(UserIndex);
				#endif		
				
				break;	
			}
		}
	}
}

bool AntiCheatPlus::CheckItemDupe(int UserIndex, int ItemSerial, int ItemPos)
{
	LPOBJ lpUser = &gObj[UserIndex];

	for(int n = 0; n < INVENTORY_SIZE; n++)
	{
		if(ItemPos == n)
		{
			continue;
		}

		if(!lpUser->pInventory[n].IsItem())
		{
			continue;
		}

		if(!this->CheckItemSerial(lpUser->pInventory[n].m_Type))
		{
			continue;
		}

		int iNextSerial = lpUser->pInventory[n].GetNumber();

		if(ItemSerial == iNextSerial)
		{
			//MsgOutput(UserIndex, "%d = %d ( %d , %d )", ItemPos, n, ItemSerial, iNextSerial);

			return false;
		}
	}

	for(int n = 0; n < WAREHOUSE_SIZE; n++)
	{
		if(!lpUser->pWarehouse[n].IsItem())
		{
			continue;
		}

		if(!this->CheckItemSerial(lpUser->pWarehouse[n].m_Type))
		{
			continue;
		}

		int iNextSerial = lpUser->pWarehouse[n].GetNumber();

		if(ItemSerial == iNextSerial)
		{
			return false;
		}
	}

	return true;
}

bool AntiCheatPlus::CheckWareDupe(int UserIndex, int ItemSerial, int WarePos)
{
	LPOBJ lpUser = &gObj[UserIndex];

	for(int n = 0; n < INVENTORY_SIZE; n++)
	{
		if(!lpUser->pInventory[n].IsItem())
		{
			continue;
		}

		if(!this->CheckItemSerial(lpUser->pInventory[n].m_Type))
		{
			continue;
		}

		int iNextSerial = lpUser->pInventory[n].GetNumber();

		if(ItemSerial == iNextSerial)
		{
			return false;
		}
	}

	for(int n = 0; n < WAREHOUSE_SIZE; n++)
	{
		if(WarePos == n)
		{
			continue;
		}

		if(!lpUser->pWarehouse[n].IsItem())
		{
			continue;
		}

		int iNextSerial = lpUser->pWarehouse[n].GetNumber();

		if(ItemSerial == iNextSerial)
		{
			return false;
		}
	}

	return true;
}

bool AntiCheatPlus::CheckItemSerial(int ItemType)
{
	if(!ItemAttribute[ItemType].Serial)
	{
		return false;
	}

	return true;
}

#endif
// ----------------------------------------------------------------------------------------------

#endif