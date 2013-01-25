#pragma once
#include "InspectorProperty.h"
#include "afxwin.h"
#include "FloatEdit.h"


class CInspectorProperty_Transform : public CInspectorProperty
{
public:
	CInspectorProperty_Transform(CString name, const math::Matrix44& value, void* pUserData = nullptr);
	virtual ~CInspectorProperty_Transform(void);

	math::Matrix44								GetValue();
	void										SetValue(const math::Matrix44& value);
private:
	math::Vector3								MatrixToEular(const math::Matrix44& mat);
	math::Matrix44								EularToMatrix(const math::Vector3& r);

	enum { IDD = IDD_INSPECTOR_PROPERTY_TRANSFORM };
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö

	math::Matrix44								m_value;

	void										AdjustLayout();
public:
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnKillfocusValue();
	CFloatEdit m_rvx;
	CFloatEdit m_rvy;
	CFloatEdit m_rvz;

	CFloatEdit m_tvx;
	CFloatEdit m_tvy;
	CFloatEdit m_tvz;

	CFloatEdit m_svx;
	CFloatEdit m_svy;
	CFloatEdit m_svz;

};

