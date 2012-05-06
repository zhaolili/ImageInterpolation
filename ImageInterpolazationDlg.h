// ImageInterpolazationDlg.h : header file
//

#if !defined(AFX_IMAGEINTERPOLAZATIONDLG_H__F38E23C2_6B6C_44E9_958A_A356E801CA93__INCLUDED_)
#define AFX_IMAGEINTERPOLAZATIONDLG_H__F38E23C2_6B6C_44E9_958A_A356E801CA93__INCLUDED_

#include "InterpolatedImg.h"	// Added by ClassView
#include "OriginalImg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CImageInterpolazationDlg dialog

class CImageInterpolazationDlg : public CDialog
{
// Construction
public:
	BOOL LoadSrcImg(CString fpathnam);
	CImageInterpolazationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CImageInterpolazationDlg)
	enum { IDD = IDD_IMAGEINTERPOLAZATION_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageInterpolazationDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CImageInterpolazationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtopenfile();
	afx_msg void OnBtinterpolate();
	afx_msg void OnGray();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnRadioNearestNeighbor();
	afx_msg void OnRadioBiLinear();
	afx_msg void OnRadioBicubic();
	afx_msg void OnRadiozoom2();
	afx_msg void OnRadiozoom3();
	afx_msg void OnRadiozoom4();
	afx_msg void OnBtsave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Cubic(int zm);
	void BiLinear(int zm);
	CString inputimgnam;
	void GetInterDIB();
	LPBITMAPINFO m_lpbmi;
	CInterpolatedImg m_interImg;
	int zoomerHeight;
	int zoomerWidth;
	BYTE * zoomerGRAYbuf;
	BYTE * zoomerIMGbuf;
	BYTE * zoomerRGBbuf;
	void NearestNeighbor(int zoomer);
	BYTE * grayBuf;
	void HeadStand(void *buffer, int height, int width, int bitdep);
	int m_height;
	int m_width;
	CBitmap m_bmp;
	BYTE * rgbBuf;
	BYTE * imgBuf;
	int checkedZoomer;      //default zoomer is 2
	int checkedIPmethod;    //
	CString inputPathname;
	COriginalImg m_orgImg;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEINTERPOLAZATIONDLG_H__F38E23C2_6B6C_44E9_958A_A356E801CA93__INCLUDED_)
