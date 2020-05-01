#pragma once

class CMessageHelper
{
public:
	void Clear();
	void Load();
	LPSTR Get(int code);

private:
	std::map<int, std::string> m_messages;
};

extern CMessageHelper lMsg;