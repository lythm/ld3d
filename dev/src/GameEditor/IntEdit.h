#pragma once


// CIntEdit

class CIntEdit : public CEdit
{
	DECLARE_DYNAMIC(CIntEdit)

public:
	CIntEdit();
	virtual ~CIntEdit();

	int														GetValue() const;
	void													SetValue(int value);
protected:

	

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


