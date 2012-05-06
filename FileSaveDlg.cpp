// FileSaveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageInterpolazation.h"
#include "FileSaveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileSaveDlg

IMPLEMENT_DYNAMIC(CFileSaveDlg, CFileDialog)

CFileSaveDlg::CFileSaveDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
		//GetModuleFileName(NULL, savedir, 200);
		m_ofn.lpstrTitle = TEXT("Save interpolated image") ;
		m_ofn.lpstrFilter="BMP Files (*.bmp)\0*.bmp\0\0";
		//m_ofn.lpstrInitialDir = (LPCTSTR)savedir;	//default path
}


BEGIN_MESSAGE_MAP(CFileSaveDlg, CFileDialog)
	//{{AFX_MSG_MAP(CFileSaveDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CFileSaveDlg::OnInitDialog() 
{
	CFileDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
