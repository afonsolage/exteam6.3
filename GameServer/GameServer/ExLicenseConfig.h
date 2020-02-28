#pragma once

struct USER_MedoniAndrei
{
	int GateMapNumber;
	int GateMapX;
	int GateMapY;
};

class CExLicenseConfig
{
public:
		CExLicenseConfig();
		~CExLicenseConfig();

	void Load();

	void ReadMedoniAndrei(char* filename);

	USER_MedoniAndrei m_MedoniAndrei;
};

extern CExLicenseConfig g_ExLicenseConfig;