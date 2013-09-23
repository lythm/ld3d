#include "stdafx.h"
#include "InspectorProperty_Color.h"

#include "resource.h"


CInspectorProperty_Color::CInspectorProperty_Color(CString name, ld3d::Property* pProp, void* pUserData) 
		: CInspectorProperty_Simple(name, pProp, pUserData, IDD_INSPECTOR_PROPERTY_COLOR)
{

}


CInspectorProperty_Color::~CInspectorProperty_Color(void)
{
}


BOOL CInspectorProperty_Color::OnInitDialog()
{
	CInspectorProperty_Simple::OnInitDialog();

	SetDlgItemText(IDC_NAME, GetName());

	m_valueButton.EnableOtherButton(L"More...");

	ld3d::Property_T<math::Color4> * pProp = (ld3d::Property_T<math::Color4>*)GetProperty();

	SetValue(pProp->Get());
		
	return true;
}
void CInspectorProperty_Color::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VALUE, m_valueButton);
}
math::Color4 CInspectorProperty_Color::GetValue()
{
	COLORREF clr = m_valueButton.GetColor();

	return math::Color4((float)GetRValue(clr) / 255.0f, 
						(float)GetGValue(clr) / 255.0f,
						(float)GetBValue(clr) / 255.0f,
						1.0f);

}
void CInspectorProperty_Color::SetValue(const math::Color4& v)
{
	m_valueButton.SetColor(RGB(v.r * 255, v.g * 255, v.b * 255));
}
BEGIN_MESSAGE_MAP(CInspectorProperty_Color, CInspectorProperty_Simple)
	ON_BN_CLICKED(IDC_VALUE, &CInspectorProperty_Color::OnBnClickedValue)
END_MESSAGE_MAP()


void CInspectorProperty_Color::OnBnClickedValue()
{

	ld3d::Property_T<math::Color4> * pProp = (ld3d::Property_T<math::Color4>*)GetProperty();
	pProp->Set(GetValue());

	OnValueChanged();

}
