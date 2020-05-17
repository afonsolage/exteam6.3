#include "stdafx.h"
#include "MessageHelper.h"
#include "GameMain.h"

CMessageHelper lMsg;

void CMessageHelper::Clear()
{
	m_messages.clear();
}

void CMessageHelper::Load()
{
	this->Clear();

	auto path = gDirPath.GetNewPath("Custom\\Messages.dat");

	FILE *file = fopen(path, "r");

	if (file == NULL)
	{
		MessageBoxA(0, "Custom\\Messages.dat", "CRITICAL ERROR", 0);
		return;
	}

	char Buff[2568];

	int Flag = 0;
	while (!feof(file))
	{
		fgets(Buff, 2568, file);

		if (Buff[0] == '/' && Buff[1] == '/')
			continue;

		int code;
		char msg[2056];

		sscanf(Buff, "%d %[^\t\n]", &code, &msg);

		this->m_messages[code] = msg;
	}

	fclose(file);
}

LPSTR CMessageHelper::Get(int code)
{
	auto it = this->m_messages.find(code);

	if (it == this->m_messages.end())
		return "";

	return const_cast<char*>(it->second.c_str());
}
