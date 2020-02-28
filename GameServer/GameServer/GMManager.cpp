#include "StdAfx.h"
#include "GMManager.h"
#include "GameMain.h"
#include "logproc.h"
#include "ExFunction.h"
#include "Functions.h"
#include "user.h"
#include "ExLicense.h"
#include "Message.h"
// -------------------------------------------------------------------------------

GMManager g_GMManager;
// -------------------------------------------------------------------------------

GMManager::GMManager()
{
	this->Init();
}
// -------------------------------------------------------------------------------

GMManager::~GMManager()
{
	// ----
}
// -------------------------------------------------------------------------------

void GMManager::Init()
{
	this->Enable = false;
	this->GMCount = 0;
	ZeroMemory(&this->gm_data,sizeof(this->gm_data));
}
// -------------------------------------------------------------------------------

void GMManager::Load()
{
	this->Init();
	// ----
	if(g_ExLicense.user.GM_Manager == false)
	{
		return;
	}
	// ----
	if(!CheckFile(gDirPath.GetNewPath(GM_MANAGER_DIR)))
	{
		return;
	}
	// ----
	this->Enable = GetPrivateProfileInt("ExTeam", "Enable", 0, gDirPath.GetNewPath(GM_MANAGER_DIR));
	this->Read(gDirPath.GetNewPath(GM_MANAGER_DIR));
}
// -------------------------------------------------------------------------------

void GMManager::Read(char* File)
{
    FILE *file = fopen(File,"r");
	// ----
    if (file == NULL)
    {
        return;
    }
	// ----
	this->GMCount = 0;
    char Buff[256];
    int Flag = 0;
	// ----
    while (!feof(file))
    {
        fgets(Buff,256,file);
		// ----
        if(Ex_IsBadFileLine(Buff, Flag))
		{
            continue;
		}
		// ----
        if (Flag == 1)
        {
			int n[11];
            char GetGMName[11];
            int isAdmin;
			// --
            sscanf(Buff, "%d %10s %d %d %d %d %d %d %d %d %d %d %d",&isAdmin, &GetGMName, &n[0], &n[1], &n[2], &n[3], &n[4], &n[5],  &n[6], &n[7], &n[8], &n[9], &n[10]);
			// --
			this->gm_data[this->GMCount].Type				= isAdmin;
			strncpy(this->gm_data[this->GMCount].Name, GetGMName, 10);
            this->gm_data[this->GMCount].cmd_gg				= n[0];
            this->gm_data[this->GMCount].cmd_sellpremium	= n[1];
            this->gm_data[this->GMCount].cmd_sellcredit		= n[2];
            this->gm_data[this->GMCount].cmd_gmove			= n[3];
            this->gm_data[this->GMCount].cmd_banchar		= n[4];
            this->gm_data[this->GMCount].cmd_exreload		= n[5];
            this->gm_data[this->GMCount].cmd_banchat		= n[6];
            this->gm_data[this->GMCount].cmd_disconnect		= n[7];
            this->gm_data[this->GMCount].cmd_trace			= n[8];
			this->gm_data[this->GMCount].cmd_sendwcoin		= n[9];
			this->gm_data[this->GMCount].cmd_item			= n[10];

            this->GMCount++;
        }
    }
	// ----
    fclose(file);
    LogAdd("[GMManager] Load successfully. Total GMs: %d", this->GMCount);
}
// -------------------------------------------------------------------------------

bool GMManager::CheckCommand(int aIndex, int cmd_type)
{
	if(g_ExLicense.user.GM_Manager == false)
	{
		return true;
	}
	// ----
	if(!this->Enable)
	{
		return false;
	}
	// ----
	if(!gObjIsConnectedEx(aIndex))
	{
		return false;
	}
	// ----
	LPOBJ lpUser = &gObj[aIndex];
	// ----
	for(int i = 0; i < this->GMCount; i++)
	{
		if( this->gm_data[i].Type > 0 )
		{
			if( lpUser->Name[0] == this->gm_data[i].Name[0] )
			{
				if( !strcmp(lpUser->Name, this->gm_data[i].Name) )
				{
					// ----
					if(this->gm_data[i].Type == 0)
					{
						return false;
					}
					// ----
					switch(cmd_type)
					{
					case egm_cmd_gg:
						{
							if(this->gm_data[i].cmd_gg)
							{
								return true;
							}
						}
						break;
					case egm_cmd_sellpremium:
						{
							if(this->gm_data[i].cmd_sellpremium)
							{
								return true;
							}
						}
						break;
					case egm_cmd_sellcredit:
						{
							if(this->gm_data[i].cmd_sellcredit)
							{
								return true;
							}
						}
						break;
					case egm_cmd_gmove:
						{
							if(this->gm_data[i].cmd_gmove)
							{
								return true;
							}
						}
						break;
					case egm_cmd_banchar:
						{
							if(this->gm_data[i].cmd_banchar)
							{
								return true;
							}
						}
						break;
					case egm_cmd_exreload:
						{
							if(this->gm_data[i].cmd_exreload)
							{
								return true;
							}
						}
						break;
					case egm_cmd_banchat:
						{
							if(this->gm_data[i].cmd_banchat)
							{
								return true;
							}
						}
						break;
					case egm_cmd_disconnect:
						{
							if(this->gm_data[i].cmd_disconnect)
							{
								return true;
							}
						}
						break;
					case egm_cmd_trace:
						{
							if(this->gm_data[i].cmd_trace)
							{
								return true;
							}
						}
						break;
					case egm_cmd_sendwcoin:
						{
							if(this->gm_data[i].cmd_sendwcoin)
							{
								return true;
							}
						}
						break;
					case egm_cmd_item:
						{
							if(this->gm_data[i].cmd_item)
							{
								return true;
							}
						}
						break;
					default:
						{
							return false;
						}
					}
				}
			}
		}
	}
	// ----
	return false;
}
// -------------------------------------------------------------------------------

void GMManager::ConnectAdmin(int aIndex)
{
	if(g_ExLicense.user.GM_Manager == false)
	{
		return;
	}
	// ----
	if(!this->Enable)
	{
		return;
	}
	// ----
	if ( aIndex < 0 || aIndex > OBJMAX-1)
	{
		return;
	}
	// ----
	LPOBJ lpUser = &gObj[aIndex];
	// ----
	for(int i = 0; i < this->GMCount; i++)
	{
		if( this->gm_data[i].Type > 0 )
		{
			if( lpUser->Name[0] == this->gm_data[i].Name[0] )
			{
				if( !strcmp(lpUser->Name, this->gm_data[i].Name) )
				{
					if(this->gm_data[i].Type == 1)
					{
						MessaageAllGlobal("[Administrator] %s Connected", lpUser->Name);
					}
					if(this->gm_data[i].Type == 2)
					{
						MessaageAllGlobal("[Game Master] %s Connected", lpUser->Name);
					}
				}
			}
		}
	}
}
// -------------------------------------------------------------------------------