#include "StdAfx.h"
#include "dirent.h"
#include "Configs.h"
#include "logproc.h"

bool FilterName(char * Names)
{
	if(!strcmp(Names,"."))	return false;
	if(!strcmp(Names,".."))	return false;
	if(!strcmp(Names,"CastleSiege"))	return false;
	if(!strcmp(Names,"Chat"))	return false;
	if(!strcmp(Names,"Connect"))	return false;
	if(!strcmp(Names,"Kanturu"))	return false;
	if(!strcmp(Names,"Kundun"))	return false;

	return true;
}

void DeleteLogs()
{
	if(!ExConfig.CommonServer.DeleteLogs) return;

	struct dirent *entry;

	DIR * dir = opendir(".\\LOG\\");

	if (!dir) 
	{
		return;
	}

	while ( (entry = readdir(dir)) != NULL)
	{
		if(!FilterName(entry->d_name))	continue;

		char InfoDate[100];

		sprintf(InfoDate, ".\\LOG\\%s",entry->d_name);

		if (remove(InfoDate)==NULL)
		{
			LogAddC(2,"Done Logs: %s",entry->d_name);
		}
	}
	closedir(dir);
}