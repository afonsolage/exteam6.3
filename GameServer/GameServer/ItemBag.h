#ifndef ITEMBAG_H
#define ITEMBAG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_ITEMBAG_ATTR 150

class CItemBagAttr
{

public:

	CItemBagAttr()	// line : 28
	{
		this->m_type=0;
		this->m_index=0;
		this->m_level=0;
		this->m_op1=0;
		this->m_op2=0;
		this->m_op3=0;
	}	// line : 36

public:

	BYTE m_type;	// 0
	BYTE m_index;	// 1
	BYTE m_level;	// 2
	BYTE m_op1;	// 3
	BYTE m_op2;	// 4
	BYTE m_op3;	// 5

};

class CItemBag
{

public:

	CItemBag();
	virtual ~CItemBag();

	virtual void Init(LPSTR name);
	virtual void LoadItem(LPSTR script_file);
	int GetBagCount()	// line : 62
	{
		return this->BagObjectCount;
	};	// line : 64
	virtual BYTE GetType(int n);
	virtual BYTE GetIndex(int n);
	virtual BYTE GetLevel(int n);
	virtual BYTE GetOp1(int n);
	virtual BYTE GetOp2(int n);
	virtual BYTE GetOp3(int n);
	int GetNormalItemCount(){return this->BagNormalItemCount;}	// line : 72
	int GetExItemCount(){return this->BagExItemCount;}	// line : 73

protected:

	CItemBagAttr BagObject[MAX_ITEMBAG_ATTR];	// 4
	int BagObjectCount;	// 388
	int BagNormalItemCount;	// 38C
	int BagExItemCount;	// 390
};

#endif