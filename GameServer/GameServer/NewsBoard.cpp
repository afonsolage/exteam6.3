#include "StdAfx.h"
#include "..\common\winutil.h"
#include "..\include\readscript_ex.h"
#include "user.h"
#include "NewsBoard.h"
#include "GameMain.h"
#include "logproc.h"

#if(CUSTOM_NEWS==TRUE)
// -------------------------------------------------------------------------------

NewsBoard g_NewsBoard;
// -------------------------------------------------------------------------------

NewsBoard::NewsBoard()
{
	this->Init();
}
// -------------------------------------------------------------------------------

NewsBoard::~NewsBoard()
{
	// ----
}
// -------------------------------------------------------------------------------

void NewsBoard::Init()
{
	this->m_LoadedCount = 0;
	this->m_ShowOnLogin	= false;
	// ----
	for( int i = 0; i < MAX_NEWS_LIST; i++ )
	{
		this->m_Data[i].Title.Date[0]	= 0;
		this->m_Data[i].Title.Time[0]	= 0;
		this->m_Data[i].Title.Text[0]	= 0;
		this->m_Data[i].Text[0]			= 0;
	}
}
// -------------------------------------------------------------------------------

void NewsBoard::ReadListData(char * File)
{
	int Token;
	// ----
	SMDFile = fopen(File, "r");
	// ----
	if( SMDFile == 0 )
	{
		MsgBox(lMsg.Get(MSGGET(0, 112)), File);
		return;
	}
	// ----
	while(true) 
	{
		Token = GetToken();
		// ----
		if( Token == END || !strcmp(TokenString, "end") || this->m_LoadedCount >= MAX_NEWS_LIST)
		{
			break;
		}
		else
		{
			memcpy(this->m_Data[this->m_LoadedCount].Title.Date, TokenString, 11);
			Token = GetToken();
			memcpy(this->m_Data[this->m_LoadedCount].Title.Time, TokenString, 6);
			Token = GetToken();
			memcpy(this->m_Data[this->m_LoadedCount].Title.Text, TokenString, 69);
			Token = GetToken();
			memcpy(this->m_Data[this->m_LoadedCount].Text, TokenString, 1024-1);
			// ----
			this->m_LoadedCount++;
		}
	}
	// ----
	LogAddTD("[NewsBoard] [%d] Item loaded from list", this->m_LoadedCount);
	fclose(SMDFile);	
}
// -------------------------------------------------------------------------------

void NewsBoard::ReadMainData(char * File)
{
	this->Enable = GetPrivateProfileInt("ExTeam", "Enable", 1, File);
	this->NPC_Class = GetPrivateProfileInt("ExTeam", "NPC_Class", 0, File);
	this->NPC_Map = GetPrivateProfileInt("ExTeam", "NPC_Map", 0, File);
	this->NPC_X = GetPrivateProfileInt("ExTeam", "NPC_X", 0, File);
	this->NPC_Y = GetPrivateProfileInt("ExTeam", "NPC_Y", 0, File);
	this->m_ShowOnLogin	= GetPrivateProfileIntA("ExTeam", "ShowOnLogin", 0, File);
}
// -------------------------------------------------------------------------------

void NewsBoard::Load()
{
	this->Init();
	this->ReadListData(gDirPath.GetNewPath("ExData\\NewsList.txt"));
	this->ReadMainData(gDirPath.GetNewPath("ExData\\NewsMain.ini"));
}
// -------------------------------------------------------------------------------

bool NewsBoard::Dialog(int aIndex, int aNpcIndex)
{
	if(!this->Enable)
	{
 		return false;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNpcIndex];

	if(		lpNpc->Class		== this->NPC_Class 
		&&	lpNpc->MapNumber	== this->NPC_Map
		&&	lpNpc->X			== this->NPC_X
		&&	lpNpc->Y			== this->NPC_Y )
	{
		this->OpenMain(lpUser);
		return true;
	}
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

void NewsBoard::OpenMain(LPOBJ lpUser)
{
	if(!this->Enable)
	{
 		return;
	}

	if( lpUser->Connected != PLAYER_PLAYING )
	{
		return;
	}
	// ----
	NEWS_ANS_TITLES pAnswer = { 0 };
	PHeadSetW((LPBYTE)&pAnswer, 0xFD, sizeof(NEWS_ANS_TITLES));
	// ----
	pAnswer.RealCount = this->m_LoadedCount;
	// ----
	for( int i = 0; i < this->m_LoadedCount; i++ )
	{
		strcpy(pAnswer.Titles[i].Date, this->m_Data[i].Title.Date);
		strcpy(pAnswer.Titles[i].Time, this->m_Data[i].Title.Time);
		strcpy(pAnswer.Titles[i].Text, this->m_Data[i].Title.Text);
	}
	// ----
	DataSend(lpUser->m_Index, (LPBYTE)&pAnswer, sizeof(NEWS_ANS_TITLES));
}
// -------------------------------------------------------------------------------

void NewsBoard::OpenItem(LPOBJ lpUser, NEWS_REQ_NEWS * Request)
{
	if(!this->Enable)
	{
 		return;
	}

	if( lpUser->Connected != PLAYER_PLAYING )
	{
		return;
	}
	// ----
	if( Request->ID < 0 || Request->ID >= MAX_NEWS_LIST )
	{
		return;
	}
	// ----
	NEWS_ANS_NEWS pAnswer = { 0 };
	PHeadSetW((LPBYTE)&pAnswer, 0xFE, sizeof(NEWS_ANS_NEWS));
	// ----
	pAnswer.ID = Request->ID;
	// ----
	strcpy(pAnswer.News.Title.Date, this->m_Data[Request->ID].Title.Date);
	strcpy(pAnswer.News.Title.Time, this->m_Data[Request->ID].Title.Time);
	strcpy(pAnswer.News.Title.Text, this->m_Data[Request->ID].Title.Text);
	strcpy(pAnswer.News.Text, this->m_Data[Request->ID].Text);
	// ----
	DataSend(lpUser->m_Index, (LPBYTE)&pAnswer, sizeof(NEWS_ANS_NEWS));
}
// -------------------------------------------------------------------------------
#endif