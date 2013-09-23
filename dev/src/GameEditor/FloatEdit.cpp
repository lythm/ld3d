// FloatEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "GameEditor.h"
#include "FloatEdit.h"


// CFloatEdit

IMPLEMENT_DYNAMIC(CFloatEdit, CEdit)

CFloatEdit::CFloatEdit()
{

}

CFloatEdit::~CFloatEdit()
{
}


BEGIN_MESSAGE_MAP(CFloatEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CFloatEdit 消息处理程序




void CFloatEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// backspace 
	// enter
	// escape
	if(nChar == '\b' || nChar == 8 || nChar == 0xd)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		return;
	}

	CPoint pos = GetCaretPos();
	int caret = LOWORD(CharFromPos(pos));
	CString text;
	GetWindowText(text);

	// sign
	if(nChar == '-')
	{
		if(caret == 0)
		{
			if(text.GetLength() == 0 || (text.GetLength() != 0 && text[0] != '-'))
			{
				CEdit::OnChar(nChar, nRepCnt, nFlags);
				return;
			}
			return;
		}
		return;
	}

	// .

	if(nChar == '.')
	{
		if(text.Find('.') != -1)
		{
			return;
		}

		if(caret == 0)
		{
			return;
		}

		if(caret == 1 &&text[0] == '-')
		{
			return;
		}
		
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		return;
	}

	// digit
	if(isdigit(nChar) == 0)
	{
		return;
	}

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}
float CFloatEdit::GetValue() const
{
	CString str;
	GetWindowText(str);

	return _wtof(str);
}
void CFloatEdit::SetValue(float value)
{
	CString str;
	str.Format(L"%.3f", value);
	SetWindowText(str);
}
