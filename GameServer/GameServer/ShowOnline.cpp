#include "StdAfx.h"
#include "user.h"


#ifdef _UPDATE8_
int ShowOnlineCount;
void setShowOnline(int online)
{
	ShowOnlineCount = online;
};
int getShowOnline()
{
	return ShowOnlineCount;
};

#endif