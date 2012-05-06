#if !defined(AFX_INTERPOLATEDIMG_H__4FCD82AF_6740_443A_9362_0B8850140605__INCLUDED_)
#define AFX_INTERPOLATEDIMG_H__4FCD82AF_6740_443A_9362_0B8850140605__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InterpolatedImg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInterpolatedImg dialog

class CInterpolatedImg : public CDialog
{
// Construction
public:
	void SetBuffer(BYTE *img, BYTE *gray, LPBITMAPINFO lpbmi, int w, int h);
	CInterpolatedImg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInterpolatedImg)
	enum { IDD = IDD_INTERPOLATEDIMG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterpolatedImg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInterpolatedImg)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	LPBITMAPINFO m_lpbmi;
	int m_height;
	int m_width;
	BYTE * zoomerGRAYbuf;
	BYTE * zoomerIMGbuf;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERPOLATEDIMG_H__4FCD82AF_6740_443A_9362_0B8850140605__INCLUDED_)
