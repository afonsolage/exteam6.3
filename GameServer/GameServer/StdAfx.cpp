// stdafx.cpp : source file that includes just the standard includes
//	GameServer.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include <chrono>

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

void ListFilesInDir(LPSTR dir_path, std::vector<std::string>& output)
{
	std::string pattern(dir_path);
    pattern.append("\\*");
    WIN32_FIND_DATA data;
    HANDLE hFind;
    if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			if (strncmp(".", data.cFileName, 260) == 0)
				continue;
			if (strncmp("..", data.cFileName, 260) == 0)
				continue;

			output.emplace_back(data.cFileName);
        } while (FindNextFile(hFind, &data) != 0);
        FindClose(hFind);
    }
}

DWORD GetEpoch()
{
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	return ms.count() / 1000;
}