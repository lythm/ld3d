#include "stdafx.h"
#include "InspectorProperty_Transform.h"
#include "resource.h"


CInspectorProperty_Transform::CInspectorProperty_Transform(CString name, ld3d::Property* pProp, void* pUserData)
	: CInspectorProperty(name, pProp, pUserData, IDD_INSPECTOR_PROPERTY_TRANSFORM)
{
}

CInspectorProperty_Transform::~CInspectorProperty_Transform(void)
{
}

math::Matrix44 CInspectorProperty_Transform::GetValue()
{
	math::Vector3 trans(m_tvx.GetValue(), m_tvy.GetValue(), m_tvz.GetValue());
	math::Vector3 rotation(m_rvx.GetValue(), m_rvy.GetValue(), m_rvz.GetValue());
	math::Vector3 scale(m_svx.GetValue(), m_svy.GetValue(), m_svz.GetValue());

	math::Matrix44 mat = EularToMatrix(rotation);
	mat.SetScale(scale);
	mat.SetTranslation(trans);

	return mat;
}
void CInspectorProperty_Transform::SetValue(const math::Matrix44& value)
{
	math::Vector3 trans = value.GetRow3(3);
	math::Vector3 scale = value.GetScale();
	scale.x = abs(scale.x);
	scale.y = abs(scale.y);
	scale.z = abs(scale.z);
	math::Vector3 rotation = MatrixToEular(value);

	m_tvx.SetValue(trans.x);
	m_tvy.SetValue(trans.y);
	m_tvz.SetValue(trans.z);

	m_rvx.SetValue(rotation.x);
	m_rvy.SetValue(rotation.y);
	m_rvz.SetValue(rotation.z);

	m_svx.SetValue(scale.x);
	m_svy.SetValue(scale.y);
	m_svz.SetValue(scale.z);
}

BOOL CInspectorProperty_Transform::OnInitDialog()
{
	CInspectorProperty::OnInitDialog();

	ld3d::Property_T<math::Matrix44> * pProp = (ld3d::Property_T<math::Matrix44>*)GetProperty();

	SetValue(pProp->Get());

	return true;
}
void CInspectorProperty_Transform::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ROTATION_X_VALUE, m_rvx);
	DDX_Control(pDX, IDC_ROTATION_Y_VALUE, m_rvy);
	DDX_Control(pDX, IDC_ROTATION_Z_VALUE, m_rvz);

	DDX_Control(pDX, IDC_TRANSLATION_X_VALUE, m_tvx);
	DDX_Control(pDX, IDC_TRANSLATION_Y_VALUE, m_tvy);
	DDX_Control(pDX, IDC_TRANSLATION_Z_VALUE, m_tvz);

	DDX_Control(pDX, IDC_SCALE_X_VALUE, m_svx);
	DDX_Control(pDX, IDC_SCALE_Y_VALUE, m_svy);
	DDX_Control(pDX, IDC_SCALE_Z_VALUE, m_svz);

}
BEGIN_MESSAGE_MAP(CInspectorProperty_Transform, CInspectorProperty)
	ON_WM_SIZE()
	ON_EN_KILLFOCUS(IDC_TRANSLATION_X_VALUE, &CInspectorProperty_Transform::OnEnKillfocusValue)
	ON_EN_KILLFOCUS(IDC_TRANSLATION_Y_VALUE, &CInspectorProperty_Transform::OnEnKillfocusValue)
	ON_EN_KILLFOCUS(IDC_TRANSLATION_Z_VALUE, &CInspectorProperty_Transform::OnEnKillfocusValue)

	ON_EN_KILLFOCUS(IDC_ROTATION_X_VALUE, &CInspectorProperty_Transform::OnEnKillfocusValue)
	ON_EN_KILLFOCUS(IDC_ROTATION_Y_VALUE, &CInspectorProperty_Transform::OnEnKillfocusValue)
	ON_EN_KILLFOCUS(IDC_ROTATION_Z_VALUE, &CInspectorProperty_Transform::OnEnKillfocusValue)

	ON_EN_KILLFOCUS(IDC_SCALE_X_VALUE, &CInspectorProperty_Transform::OnEnKillfocusValue)
	ON_EN_KILLFOCUS(IDC_SCALE_Y_VALUE, &CInspectorProperty_Transform::OnEnKillfocusValue)
	ON_EN_KILLFOCUS(IDC_SCALE_Z_VALUE, &CInspectorProperty_Transform::OnEnKillfocusValue)

END_MESSAGE_MAP()


void CInspectorProperty_Transform::OnSize(UINT nType, int cx, int cy)
{
	CInspectorProperty::OnSize(nType, cx, cy);

	AdjustLayout();
}

math::Vector3 CInspectorProperty_Transform::MatrixToEular(const math::Matrix44& mat)
{
	math::Vector3 r;
	math::Matrix44 rm = mat;

	rm.SetScale(math::Vector3(1, 1, 1));
	//rm.Transpose();

	// Assuming the angles are in radians.
	if (rm(1, 0) > 0.998)
	{ // singularity at north pole
		r.x = 0;
		r.y = atan2(rm(0, 2), rm(2, 2));
		r.z = math::MATH_PI/2;
		return r;
	}
	if (rm(1, 0) < -0.998) { // singularity at south pole
		r.x = 0;

		r.y = atan2(rm(0, 2),rm(2, 2));
		r.z = -math::MATH_PI/2;
		return r;
	}

	r.x  = atan2(-rm(1, 2),rm(1, 1));
	r.y  = atan2(-rm(2, 0), rm(0, 0));
	r.z  = asin(rm(1, 0));

	return math::Vector3(-math::R2D(r.x), -math::R2D(r.y), -math::R2D(r.z));
}
math::Matrix44 CInspectorProperty_Transform::EularToMatrix(const math::Vector3& r)
{
	using namespace math;

	return MatrixRotationAxisY(D2R(r.y)) * MatrixRotationAxisZ(D2R(r.z)) * MatrixRotationAxisX(D2R(r.x));
}

void CInspectorProperty_Transform::OnEnKillfocusValue()
{
	ld3d::Property_T<math::Matrix44> * pProp = (ld3d::Property_T<math::Matrix44>*)GetProperty();

	pProp->Set(GetValue());

	OnValueChanged();
}

void CInspectorProperty_Transform::AdjustLayout()
{
	CRect rc;
	GetClientRect(rc);

	int width = rc.Width();
	int label_width = 6;
	int label_padding = 10;
	int edit_width = (width - 2 * INSPECTOR_PROPERTY_ROW_H_PADDING - label_width * 3  - label_padding * 5) / 3;
	
	int offset = 0;

	// translation
	CWnd* pWnd = GetDlgItem(IDC_TRANSLATION);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					INSPECTOR_PROPERTY_ROW_H_PADDING, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					rc.Width() - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					INSPECTOR_PROPERTY_ROW_HEIGHT, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	offset += INSPECTOR_PROPERTY_ROW_HEIGHT;

	// translation row
	// x label
	int row_offset = INSPECTOR_PROPERTY_ROW_H_PADDING;
	pWnd = GetDlgItem(IDC_TRANSLATION_X);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					label_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);
	row_offset +=  label_width + label_padding;

	// x value
	pWnd = GetDlgItem(IDC_TRANSLATION_X_VALUE);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					edit_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	row_offset += edit_width + label_padding;

	// y label
	pWnd = GetDlgItem(IDC_TRANSLATION_Y);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					label_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	row_offset += label_width + label_padding;

	// y value
	pWnd = GetDlgItem(IDC_TRANSLATION_Y_VALUE);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					edit_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	row_offset += edit_width + label_padding;

	// z label
	pWnd = GetDlgItem(IDC_TRANSLATION_Z);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					label_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	row_offset += label_width + label_padding;

	// z value
	pWnd = GetDlgItem(IDC_TRANSLATION_Z_VALUE);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					edit_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	offset += INSPECTOR_PROPERTY_ROW_HEIGHT;
	
		
	// rotation
	pWnd = GetDlgItem(IDC_ROTATION);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					INSPECTOR_PROPERTY_ROW_H_PADDING, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					rc.Width() - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					INSPECTOR_PROPERTY_ROW_HEIGHT, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	offset += INSPECTOR_PROPERTY_ROW_HEIGHT;

	// rotation row
	// x label
	row_offset = INSPECTOR_PROPERTY_ROW_H_PADDING;
	pWnd = GetDlgItem(IDC_ROTATION_X);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					label_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);
	row_offset +=  label_width + label_padding;

	// x value
	pWnd = GetDlgItem(IDC_ROTATION_X_VALUE);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					edit_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	row_offset += edit_width + label_padding;

	// y label
	pWnd = GetDlgItem(IDC_ROTATION_Y);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					label_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	row_offset += label_width + label_padding;

	// y value
	pWnd = GetDlgItem(IDC_ROTATION_Y_VALUE);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					edit_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	row_offset += edit_width + label_padding;

	// z label
	pWnd = GetDlgItem(IDC_ROTATION_Z);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					label_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	row_offset += label_width + label_padding;

	// z value
	pWnd = GetDlgItem(IDC_ROTATION_Z_VALUE);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					edit_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);


	offset += INSPECTOR_PROPERTY_ROW_HEIGHT;
	
		
	// scale
	pWnd = GetDlgItem(IDC_SCALE);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					INSPECTOR_PROPERTY_ROW_H_PADDING, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					rc.Width() - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					INSPECTOR_PROPERTY_ROW_HEIGHT, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	offset += INSPECTOR_PROPERTY_ROW_HEIGHT;

	// scale row
	// x label
	row_offset = INSPECTOR_PROPERTY_ROW_H_PADDING;
	pWnd = GetDlgItem(IDC_SCALE_X);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					label_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);
	row_offset +=  label_width + label_padding;

	// x value
	pWnd = GetDlgItem(IDC_SCALE_X_VALUE);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					edit_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	row_offset += edit_width + label_padding;

	// y label
	pWnd = GetDlgItem(IDC_SCALE_Y);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					label_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	row_offset += label_width + label_padding;

	// y value
	pWnd = GetDlgItem(IDC_SCALE_Y_VALUE);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					edit_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	row_offset += edit_width + label_padding;

	// z label
	pWnd = GetDlgItem(IDC_SCALE_Z);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					label_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);

	row_offset += label_width + label_padding;

	// z value
	pWnd = GetDlgItem(IDC_SCALE_Z_VALUE);
	if(pWnd == nullptr)
	{
		return;
	}
	pWnd->SetWindowPos(nullptr, 
					row_offset, 
					offset + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					edit_width, 
					INSPECTOR_PROPERTY_ROW_HEIGHT - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);

}
int CInspectorProperty_Transform::GetHeight()
{
	return 6 * INSPECTOR_PROPERTY_ROW_HEIGHT + 1;
}
