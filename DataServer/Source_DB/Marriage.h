#pragma once

struct PMSG_REQ_MARRIAGE_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool bClass;
	char szName[11];
};

struct PMSG_ANS_MARRIAGE_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	char szMarriageName[11];
};
// ----
struct PMSG_REQ_MARRIAGE_INSERT
{
	PBMSG_HEAD2 h;
	int aIndex1;
	int aIndex2;
	char szName1[11];
	char szName2[11];
};

struct PMSG_ANS_MARRIAGE_INSERT
{
	PBMSG_HEAD2 h;
	int aIndex1;
	int aIndex2;
	bool bResult;
};
// ----
struct PMSG_REQ_MARRIAGE_DELETE
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool bClass;
	char szName[11];
};

struct PMSG_ANS_MARRIAGE_DELETE
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool bResult;
};
// ----
class CMarriage
{
public:
			CMarriage();
			~CMarriage();

	bool	Connect();
	void    CreateTable();
	void	GDLoad(PMSG_REQ_MARRIAGE_LOAD* aRecv, int uIndex);
	void    GDInset(PMSG_REQ_MARRIAGE_INSERT* aRecv, int uIndex);
	void    GDDelete(PMSG_REQ_MARRIAGE_DELETE* aRecv, int uIndex);

	CQuery	m_DBQuery;
};
extern CMarriage g_Marriage;