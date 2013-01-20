
// GameEditorDoc.cpp : CGameEditorDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "GameEditor.h"
#endif

#include "GameEditorDoc.h"

#include <propkey.h>
#include "StartDialog.h"
#include "ProgressDlg.h"
#include "ProjectWizard.h"
#include "editor_utils.h"
#include "MainFrm.h"
#include "Project.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGameEditorDoc

IMPLEMENT_DYNCREATE(CGameEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CGameEditorDoc, CDocument)
END_MESSAGE_MAP()


// CGameEditorDoc ����/����

CGameEditorDoc::CGameEditorDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CGameEditorDoc::~CGameEditorDoc()
{
}

BOOL CGameEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	CProjectWizard pw(util_get_main_frame());
	if(IDOK != pw.DoModal())
	{
		return FALSE;
	}

	util_update_object_view(Project::Instance()->Root());
	util_update_assets_view();

	SetTitle(Project::Instance()->GetGameSceneFile().c_str());

	return CDocument::OnNewDocument();
}


// CGameEditorDoc ���л�

void CGameEditorDoc::Serialize(CArchive& ar)
{
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CGameEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CGameEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CGameEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGameEditorDoc ���

#ifdef _DEBUG
void CGameEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGameEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGameEditorDoc ����


BOOL CGameEditorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	using namespace ld3d;

	util_update_obj_property_grid(GameObjectPtr());
	util_update_object_view(GameObjectPtr());

	ProjectPtr pProject = Project::Instance();

	pProject->Close();
	
	if(pProject->Load(lpszPathName) == false)
	{
		util_log_info(L"Failed to open project.");
		return FALSE;
	}

	util_log_info(L"Project openned.");
	util_update_object_view(Project::Instance()->Root());
	return CDocument::OnOpenDocument(lpszPathName);
}



BOOL CGameEditorDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: �ڴ����ר�ô����/����û���


	ProjectPtr pProject =Project::Instance();

		
	if(pProject->Save(lpszPathName) == false)
	{
		util_log_info(L"Failed to save project.");
		return FALSE;
	}
	util_log_info(L"Project saved.");
	

	return CDocument::OnSaveDocument(lpszPathName);
}
