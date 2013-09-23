// IntEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameEditor.h"
#include "IntEdit.h"


// CIntEdit

IMPLEMENT_DYNAMIC(CIntEdit, CEdit)

CIntEdit::CIntEdit()
{

}

CIntEdit::~CIntEdit()
{
}


BEGIN_MESSAGE_MAP(CIntEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CIntEdit ��Ϣ�������




void CIntEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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

	// digit
	if(isdigit(nChar) == 0)
	{
		return;
	}

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}
int CIntEdit::GetValue() const
{
	CString str;
	GetWindowText(str);
	
	return StrToInt(str);
}
void CIntEdit::SetValue(int value)
{
	CString str;
	str.Format(L"%d", value);
	SetWindowText(str);
}
