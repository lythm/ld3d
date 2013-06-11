#pragma once

#include "InspectorProperty_Simple.h"
#include "afxcolorbutton.h"


class CInspectorProperty_Color : public CInspectorProperty_Simple
{
public:
	CInspectorProperty_Color(CString name, ld3d::Property* pProp, void* pUserData = nullptr);
	virtual ~CInspectorProperty_Color(void);

	math::Color4					GetValue();
	void							SetValue(const math::Color4& v);

private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö
	enum { IDD = IDD_INSPECTOR_PROPERTY_COLOR };


	virtual BOOL OnInitDialog();
public:
	CMFCColorButton m_valueButton;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedValue();
};

