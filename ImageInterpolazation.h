// ImageInterpolazation.h : main header file for the IMAGEINTERPOLAZATION application
//

#if !defined(AFX_IMAGEINTERPOLAZATION_H__A67A5A5C_58CE_4058_9CB2_9AA563FD973C__INCLUDED_)
#define AFX_IMAGEINTERPOLAZATION_H__A67A5A5C_58CE_4058_9CB2_9AA563FD973C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CImageInterpolazationApp:
// See ImageInterpolazation.cpp for the implementation of this class
//

class CImageInterpolazationApp : public CWinApp
{
public:
	CImageInterpolazationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageInterpolazationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CImageInterpolazationApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEINTERPOLAZATION_H__A67A5A5C_58CE_4058_9CB2_9AA563FD973C__INCLUDED_)
