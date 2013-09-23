#pragma once


// CFloatEdit

class CFloatEdit : public CEdit
{
	DECLARE_DYNAMIC(CFloatEdit)

public:
	CFloatEdit();
	virtual ~CFloatEdit();

	float											GetValue() const;
	void											SetValue(float value);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


