#if !defined(AFX_FILESAVEDLG_H__A19EA9F9_51AE_48F4_937D_83F5BECF363E__INCLUDED_)
#define AFX_FILESAVEDLG_H__A19EA9F9_51AE_48F4_937D_83F5BECF363E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileSaveDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileSaveDlg dialog

class CFileSaveDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CFileSaveDlg)

public:
	CFileSaveDlg(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(CFileSaveDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();
private:
	char savedir[200];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESAVEDLG_H__A19EA9F9_51AE_48F4_937D_83F5BECF363E__INCLUDED_)
