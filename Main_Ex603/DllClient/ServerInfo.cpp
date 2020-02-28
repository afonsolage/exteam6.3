#include "stdafx.h"
#include "ServerInfo.h"
#include "Interface.h"
#include "TMemory.h"
#include "ReadScript.h"

CServerInfo g_ServerInfo;

CServerInfo::CServerInfo()
{
	this->m_data.clear();
}

CServerInfo::~CServerInfo()
{
}

void CServerInfo::Load()
{
	//00953CFC - hook
	this->m_data.clear();

	this->Read("Data/Custom/Configs/ServerInfo.dat");

	SetOp((LPVOID)0x00953F38, this->ServerDrawTextHook, ASM::CALL);
	SetOp((LPVOID)0x00953F6E, this->ServerDrawTextHook, ASM::CALL);
	SetOp((LPVOID)0x00953FA1, this->ServerDrawTextHook, ASM::CALL);
	SetOp((LPVOID)0x00953FD4, this->ServerDrawTextHook, ASM::CALL);
}

void CServerInfo::Read(char* filename)
{
	SMDToken Token;

	SMDFile = fopen(filename, "r");

	if(!SMDFile)
	{
		return;
	}

	while(true)
	{
		Token = GetToken();

		if( Token == END || !strcmp(TokenString, "end") )
		{
			break;
		}

		SERVERINFO_DATA list;

		memcpy(list.ServerName, TokenString, sizeof(list.ServerName));

		Token = GetToken();
		list.SubServerNum = TokenNumber;

		Token = GetToken();
		memcpy(list.ServerText, TokenString, sizeof(list.ServerText));

		this->m_data.push_back(list);
	}

	fclose(SMDFile);
}

int CServerInfo::ServerDrawText(int a1, signed int a2, signed int a3)
{
  int v3; // eax@10
  int v4; // eax@11
  int v5; // eax@12
  int v6; // eax@13
  DWORD *v8; // [sp+4h] [bp-24h]@2
  void *v9; // [sp+Ch] [bp-1Ch]@1
  int v10; // [sp+18h] [bp-10h]@5

  v9 = (void *)pGetTextNumber(276);
  if ( v9 )
    v8 = (DWORD*)sub_953620(v9);
  else
    v8 = 0;
  v8[1] = sub_9527D0((char *)a1);
  v8[2] = a2 % 20 + 1;
  v8[3] = a2;
  v8[4] = a3;
  *((BYTE *)v8 + 20) = *(BYTE *)(a1 + v8[2] + 24);
  if ( a3 < 128 )
  {
    if ( a3 < 100 )
      v10 = 562;
    else
      v10 = 561;
  }
  else
  {
    v10 = 560;
  }
  switch ( *((BYTE *)v8 + 20) )
  {
    case 0:
      v3 = sub_402320(v10);
      pSetItemTextLine((int)v8 + 21, "%s-%d %s", a1 + 45, v8[2], v3);
      break;
    case 1:
      v4 = sub_402320(v10);
      pSetItemTextLine((int)v8 + 21, "%s-%d(Non-PVP) %s", a1 + 45, v8[2], v4);
      break;
    case 2:
      v5 = sub_402320(v10);
      pSetItemTextLine((int)v8 + 21, "%s-%d(Gold PVP) %s", a1 + 45, v8[2], v5);
      break;
    case 3:
      v6 = sub_402320(v10);
      //pSetItemTextLine(*(char*)(v8 + 21), "%s-%d(Gold) %s", a1 + 45, v8[2], v6);
	  //pSetItemTextLine(*(int*)(v8 + 21), "test");
	  //v8[21] = 't';
      break;
    //default:
      //return sub_9526C0((DWORD *)a1, (char)v8);
  }
  //return sub_9526C0((DWORD *)a1, (char)v8);
  return FALSE;
}

void CServerInfo::ServerDrawTextHook(int a1, char *a2, char* ServerName, int SubServerNum, char* TextConnect)
{
	for(int i = 0; i < g_ServerInfo.m_data.size(); i++)
	{
		if(!strcmp(ServerName, g_ServerInfo.m_data[i].ServerName))
		{
			if(SubServerNum == g_ServerInfo.m_data[i].SubServerNum)
			{
				pSetItemTextLine(a1, g_ServerInfo.m_data[i].ServerText);
				return;
			}	
		}
	}

	pSetItemTextLine(a1, a2, ServerName, SubServerNum, TextConnect);

	
}