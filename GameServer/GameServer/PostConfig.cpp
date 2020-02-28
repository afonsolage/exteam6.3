#include "StdAfx.h"
#include "PostConfig.h"
#include "Message.h"
#include "user.h"

#include "GMMng.h"

#ifdef _POST_CONFIG_
extern cPostConfig PostConfig;
void cPostConfig::Load(){
	
	GetPrivateProfileString("Post", "PostName","/post",this->CommandPost,100,POST_CONFIG_DIR);
	this->PostLevel = GetPrivateProfileInt("Post","PostLevel",100,POST_CONFIG_DIR);
	this->PostMoney = GetPrivateProfileInt("Post","PostMoney",1000000,POST_CONFIG_DIR);
	GetPrivateProfileString("Post", "PostPrist","[post]:",this->PostPrist,100,POST_CONFIG_DIR);
	this->PostColor = GetPrivateProfileInt("Post","PostColor",1,POST_CONFIG_DIR);
	if(this->PostColor < 1 || this->PostColor > 9)
	{
		this->PostColor = 3;
	}
	this->PostPCPoint = GetPrivateProfileInt("Post","PostPCPoint",1000000,POST_CONFIG_DIR);
	this->MoneyType = GetPrivateProfileInt("Post","MoneyType",1,POST_CONFIG_DIR);
	
};
void cPostConfig::SetCommand(){
	cCommand.Add("/exjow", 635, 1);
	cCommand.Add("/vipteleport", 636, 1);
};
void cPostConfig::StartCommand(int aIndex){

LPOBJ lpObj = &gObj[aIndex];
#if(_BAN_SYSTEM_)
	if ( lpObj->BanPost > time(NULL) )
	{
		MsgOutput(lpObj->m_Index, "[BanPost] %d Sec", (lpObj->BanPost-time(NULL)));
		return;
	}
#endif
if(lpObj->Level < ExConfig.Command.PostLevel)
{
	MsgNormal(aIndex,"Need Level %d",ExConfig.Command.PostLevel);
	return;
}
#if(_POST_FOR_PCPOINT_)
if(ExConfig.Command.MoneyType == 1)
{
	if(lpObj->PCPoint < ExConfig.Command.PostPCPoint)
	{
		MsgNormal(aIndex,"Need Pc Point: %d",ExConfig.Command.PostPCPoint);
		return;
	}
}
else
{
	if(lpObj->Money < ExConfig.Command.PostMoney)
	{
		MsgNormal(aIndex,"Need Money: %d",ExConfig.Command.PostMoney);
		return;
	}
}
#else
if(lpObj->Money < ExConfig.Command.PostMoney)
{
	MsgNormal(aIndex,"Need Money: %d",ExConfig.Command.PostMoney);
	return;
}
#endif
char Message[100];

//return;

switch(ExConfig.Command.PostColor)
{
	case 1: sprintf(Message, "~%s %s",ExConfig.Command.PostPrist, szMsg);break;
	case 2: sprintf(Message, "@%s %s",ExConfig.Command.PostPrist, szMsg);break;
	case 3: sprintf(Message, "@@%s %s",ExConfig.Command.PostPrist, szMsg);break;
	case 4: sprintf(Message, "%s %s",ExConfig.Command.PostPrist, szMsg);break;
	default: sprintf(Message, "~%s %s",ExConfig.Command.PostPrist, szMsg);
}
if(ExConfig.Command.PostColor == 4)
{
	ChatMessageTwo(aIndex, Message);
}
else
{
	ChatMessageOne(aIndex, Message);
}

lpObj->Money -= ExConfig.Command.PostMoney;
GCMoneySend(aIndex,lpObj->Money);

};


#endif

//POST
//================
void PostMessage (int aIndex,char* szMsg)
{
LPOBJ lpObj = &gObj[aIndex];
#if(_BAN_SYSTEM_)
	if ( lpObj->BanPost > time(NULL) )
	{
		MsgOutput(lpObj->m_Index, "[BanPost] %d Sec", (lpObj->BanPost-time(NULL)));
		return;
	}
#endif
//int PostLevel = GetPrivateProfileInt("Post","PostLevel",100,"..\\Data\\ExData\\Commands.ini");
if(lpObj->Level < ExConfig.Command.PostLevel)
{
	MsgNormal(aIndex,"Need Level %d",ExConfig.Command.PostLevel);
	return;
}
//int PostMoney = GetPrivateProfileInt("Post","PostMoney",1000000,"..\\Data\\ExData\\Commands.ini");
#if(_POST_FOR_PCPOINT_)
if(ExConfig.Command.MoneyType == 1)
{
	if(lpObj->PCPoint < ExConfig.Command.PostPCPoint)
	{
		MsgNormal(aIndex,"Need Pc Point: %d",ExConfig.Command.PostPCPoint);
		return;
	}
}
else
{
	if(lpObj->Money < ExConfig.Command.PostMoney)
	{
		MsgNormal(aIndex,"Need Money: %d",ExConfig.Command.PostMoney);
		return;
	}
}
#else
if(lpObj->Money < ExConfig.Command.PostMoney)
{
	MsgNormal(aIndex,"Need Money: %d",ExConfig.Command.PostMoney);
	return;
}
#endif
char Message[100];

//return;

switch(ExConfig.Command.PostColor)
{
	case 1: sprintf(Message, "~%s %s",ExConfig.Command.PostPrist, szMsg);break;
	case 2: sprintf(Message, "@%s %s",ExConfig.Command.PostPrist, szMsg);break;
	case 3: sprintf(Message, "@@%s %s",ExConfig.Command.PostPrist, szMsg);break;
	case 4: sprintf(Message, "%s %s",ExConfig.Command.PostPrist, szMsg);break;
	default: sprintf(Message, "~%s %s",ExConfig.Command.PostPrist, szMsg);
}
if(ExConfig.Command.PostColor == 4)
{
	ChatMessageTwo(aIndex, Message);
}
else
{
	ChatMessageOne(aIndex, Message);
}

lpObj->Money -= ExConfig.Command.PostMoney;
GCMoneySend(aIndex,lpObj->Money);

}