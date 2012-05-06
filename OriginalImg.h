#if !defined(AFX_ORIGINALIMG_H__F250CC28_2E01_41B0_ACC4_74C40837D8EE__INCLUDED_)
#define AFX_ORIGINALIMG_H__F250CC28_2E01_41B0_ACC4_74C40837D8EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OriginalImg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COriginalImg dialog

class COriginalImg : public CDialog
{
// Construction
public:
	void SetBuffer(BYTE *img, BYTE *gray, int w, int h);
	COriginalImg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COriginalImg)
	enum { IDD = IDD_ORGIMG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COriginalImg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COriginalImg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_height;
	int m_width;
	BYTE * grayBuf;
	BYTE * imgBuf;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORIGINALIMG_H__F250CC28_2E01_41B0_ACC4_74C40837D8EE__INCLUDED_)
