#include "stdafx.h"
#include "FileMemory.h"
#include "FileDB.h"
#include "Console.h"
#include "TMemory.h"

#if(ENABLE_FILEMEMORY)

char szText[256];
static DWORD dw005D6918 = 0x005D6918;

int TerainLoad(char* filename)
{
	strcpy(szText, filename);

	if(!strcmp(filename, "Data\\World3\\EncTerrain3.att"))
	{
		pFileEncrypt(0, btTerrainAtt, sizeof(btTerrainAtt));

	}

	return pTerrainLoad(filename);
}

FILE* FileName(char* filename, LPVOID param)
{
	//gConsole.Output(cBLUE, filename);
	strcpy(szText, filename);

	if(!strcmp(szText, "Data\\World3\\EncTerrain3.att"))
	{
		pFileEncrypt(0, btTerrainAtt, sizeof(btTerrainAtt));
	}

	return pFileOpen(filename, param);
}

int FileEncrypt(LPBYTE type, LPBYTE buffer, int size)
{
	//char szWorld[] = "Data\\World3\\EncTerrain3.att";
	//gConsole.Output(cGREEN, "%s %s", szText, szWorld);

	if(!strcmp(szText, "Data\\World3\\EncTerrain3.att"))
	{
		if(type == 0)
		{
			size = sizeof(btTerrainAtt);
			memcpy(buffer, btTerrainAtt, size);
		}
		else
		{

		}

		//memcpy(buffer, btTerrainAtt, size);
		/*for(int i = 0; i < size; i++)
		{
			//buffer[i] = buffer[i] ^ g_DataSecurity.XorFile[i % MAX_XOR];	
			if(i < 128)
			{
				gConsole.Output(cGREY, "%2X | %2X | %d", buffer[i], btTerrainAtt[i], size);
			}
			buffer[i] = btTerrainAtt[i];
		}*/
	}

	return pFileEncrypt(type, buffer, size);
}

void FileMemoryLoad()
{
	//SetOp((LPVOID)0x0062EE31, (LPVOID)FileName, ASM::CALL);

	//SetOp((LPVOID)0x0054C21D, (LPVOID)FileName, ASM::CALL);
	SetOp((LPVOID)0x005D6826, (LPVOID)FileName, ASM::CALL);	//ATT
	//SetOp((LPVOID)0x005D6E64, (LPVOID)FileName, ASM::CALL);
	//SetOp((LPVOID)0x005F3402, (LPVOID)FileName, ASM::CALL);

	//SetOp((LPVOID)0x0054C303, (LPVOID)FileEncrypt, ASM::CALL);
	//SetOp((LPVOID)0x0054C338, (LPVOID)FileEncrypt, ASM::CALL);
	SetOp((LPVOID)0x005D691F, (LPVOID)FileEncrypt, ASM::CALL);		//ATT1
	SetOp((LPVOID)0x005D6951, (LPVOID)FileEncrypt, ASM::CALL);	//ATT2
	//SetOp((LPVOID)0x005D6EFB, (LPVOID)FileEncrypt, ASM::CALL);
	//SetOp((LPVOID)0x005D6F27, (LPVOID)FileEncrypt, ASM::CALL);
	//SetOp((LPVOID)0x005F34D4, (LPVOID)FileEncrypt, ASM::CALL);
	//SetOp((LPVOID)0x005F3506, (LPVOID)FileEncrypt, ASM::CALL);
}

#endif