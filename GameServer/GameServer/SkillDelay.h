#ifndef SKILLDELAY_H
#define SKILLDELAY_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSkillDelay
{

public:

	CSkillDelay();
	virtual ~CSkillDelay();

	void Init();
	BOOL Check(WORD skill);
	BOOL CanUse(WORD skill);

private:

	DWORD LastSkillUseTime[600];
};

#endif