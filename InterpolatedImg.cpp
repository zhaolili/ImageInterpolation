// InterpolatedImg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageInterpolazation.h"
#include "InterpolatedImg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInterpolatedImg dialog


CInterpolatedImg::CInterpolatedImg(CWnd* pParent /*=NULL*/)
	: CDialog(CInterpolatedImg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInterpolatedImg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	zoomerGRAYbuf = NULL;
	zoomerIMGbuf = NULL;
	m_lpbmi = NULL;
	m_width = 0;
	m_height = 0;
}


void CInterpolatedImg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterpolatedImg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInterpolatedImg, CDialog)
	//{{AFX_MSG_MAP(CInterpolatedImg)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterpolatedImg message handlers

void CInterpolatedImg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	zoomerIMGbuf = NULL;
	zoomerGRAYbuf = NULL;
	m_lpbmi = NULL;
	::DestroyWindow(this->m_hWnd);
	CDialog::OnClose();
}

BOOL CInterpolatedImg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_DISPLAYER)), TRUE);
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_DISPLAYER)), FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInterpolatedImg::SetBuffer(BYTE *img, BYTE *gray, LPBITMAPINFO lpbmi, int w, int h)
{
	zoomerIMGbuf = img;
	zoomerGRAYbuf = gray;
	m_lpbmi = lpbmi;
	m_width = w;
	m_height = h;
}

void CInterpolatedImg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CWnd *pWnd = GetDlgItem(IDC_INTERPOLATEDIMG);
	if (pWnd==NULL)
	{
		MessageBox("error!");
		return;
	}
	CRect rect;
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);
	pWnd->MoveWindow(rect.left, rect.top, m_width, m_height, true);	
	CPaintDC pdc(pWnd);	
	::SetStretchBltMode(pdc, COLORONCOLOR);
	StretchDIBits(pdc.GetSafeHdc(),  0,  0, m_width,  m_height,  0,  0,  m_width,  m_height, zoomerGRAYbuf,  m_lpbmi,  DIB_RGB_COLORS,  SRCCOPY);  
	// Do not call CDialog::OnPaint() for painting messages
}

void CInterpolatedImg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	SCROLLINFO scrollinfo; 
	GetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
	switch (nSBCode) 
	{ 
	case SB_LEFT: 
		ScrollWindow((scrollinfo.nPos-scrollinfo.nMin)*10,0); 
		scrollinfo.nPos = scrollinfo.nMin; 
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
		break; 
	case SB_RIGHT: 
		ScrollWindow((scrollinfo.nPos-scrollinfo.nMax)*10,0); 
		scrollinfo.nPos = scrollinfo.nMax; 
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
		break; 
	case SB_LINELEFT: 
		scrollinfo.nPos -= 1; 
		if (scrollinfo.nPos<scrollinfo.nMin) 
		{ 
			scrollinfo.nPos = scrollinfo.nMin; 
			break; 
		} 
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
		ScrollWindow(10,0); 
		break; 
	case SB_LINERIGHT: 
		scrollinfo.nPos += 1; 
		if (scrollinfo.nPos>scrollinfo.nMax) 
		{ 
			scrollinfo.nPos = scrollinfo.nMax; 
			break; 
		} 
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
		ScrollWindow(-10,0); 
		break; 
	case SB_PAGELEFT: 
		scrollinfo.nPos -= 5; 
		if (scrollinfo.nPos<scrollinfo.nMin) 
		{ 
			scrollinfo.nPos = scrollinfo.nMin; 
			break; 
		} 
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
		ScrollWindow(10*5,0); 
		break; 
	case SB_PAGERIGHT: 
		scrollinfo.nPos += 5; 
		if (scrollinfo.nPos>scrollinfo.nMax) 
		{ 
			scrollinfo.nPos = scrollinfo.nMax; 
			break; 
		} 
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
		ScrollWindow(-10*5,0); 
		break; 
	case SB_THUMBPOSITION: 
		break; 
	case SB_THUMBTRACK: 
		ScrollWindow((scrollinfo.nPos-nPos)*10,0); 
		scrollinfo.nPos = nPos; 
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL); 
		break; 
	case SB_ENDSCROLL: 
		break; 
	} 

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CInterpolatedImg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	SCROLLINFO scrollinfo; 
	GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
	switch (nSBCode) 
	{ 
	case SB_BOTTOM: 
		ScrollWindow(0,(scrollinfo.nPos-scrollinfo.nMax)*10); 
		scrollinfo.nPos = scrollinfo.nMax; 
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		break; 
	case SB_TOP: 
		ScrollWindow(0,(scrollinfo.nPos-scrollinfo.nMin)*10); 
		scrollinfo.nPos = scrollinfo.nMin; 
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		break; 
	case SB_LINEUP: 
		scrollinfo.nPos -= 1; 
		if (scrollinfo.nPos<scrollinfo.nMin) 
		{ 
			scrollinfo.nPos = scrollinfo.nMin; 
			break; 
		} 
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		ScrollWindow(0,10); 
		break; 
	case SB_LINEDOWN: 
		scrollinfo.nPos += 1; 
		if (scrollinfo.nPos>scrollinfo.nMax) 
		{ 
			scrollinfo.nPos = scrollinfo.nMax; 
			break; 
		} 
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		ScrollWindow(0,-10); 
		break; 
	case SB_PAGEUP: 
		scrollinfo.nPos -= 5; 
		if (scrollinfo.nPos<scrollinfo.nMin) 
		{ 
			scrollinfo.nPos = scrollinfo.nMin; 
			break; 
		} 
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		ScrollWindow(0,10*5); 
		break; 
	case SB_PAGEDOWN: 
		scrollinfo.nPos += 5; 
		if (scrollinfo.nPos>scrollinfo.nMax) 
		{ 
			scrollinfo.nPos = scrollinfo.nMax; 
			break; 
		} 
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		ScrollWindow(0,-10*5); 
		break; 
	case SB_ENDSCROLL: 
		// MessageBox("SB_ENDSCROLL"); 
		break; 
	case SB_THUMBPOSITION: 
		// ScrollWindow(0,(scrollinfo.nPos-nPos)*10); 
		// scrollinfo.nPos = nPos; 
		// SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		break; 
	case SB_THUMBTRACK: 
		ScrollWindow(0,(scrollinfo.nPos-nPos)*10); 
		scrollinfo.nPos = nPos; 
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		break; 
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CInterpolatedImg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if (m_hWnd)
	{
		SCROLLINFO vscrollinfo; 
		GetScrollInfo(SB_VERT,&vscrollinfo,SIF_ALL); 
		SCROLLINFO hscrollinfo;
		GetScrollInfo(SB_HORZ, &hscrollinfo, SIF_ALL);
 		CRect rect;
		GetClientRect(&rect);
		int ch = rect.bottom-rect.top;
		int cw = rect.right - rect.left;
		int vmaxPos = 0;  //suppose i unit means 10pixels
		int hmaxPos = 0;
		CRect prect;
	

		//vertical
		if (ch < (m_height-vscrollinfo.nPos*10))
		{
			vmaxPos = (int)((m_height-ch + 2*rect.top + 9)/10);			
		}
		else
		{
			ScrollWindow(0,(vscrollinfo.nPos-vscrollinfo.nMin)*10); 
			vscrollinfo.nPos = vscrollinfo.nMin; 
			SetScrollInfo(SB_VERT,&vscrollinfo,SIF_ALL); 
		}
		//horizontal
		if (cw < (m_width-hscrollinfo.nPos*10))
		{
			hmaxPos = (int)((m_width-cw + 2*rect.left + 9)/10);	
		}
		else
		{
			ScrollWindow((hscrollinfo.nPos-hscrollinfo.nMin)*10,0); 
			hscrollinfo.nPos = hscrollinfo.nMin; 
			SetScrollInfo(SB_HORZ,&hscrollinfo,SIF_ALL); 
		}
		::SetScrollRange(this->m_hWnd, SB_VERT, 0, vmaxPos, FALSE);
		::SetScrollRange(this->m_hWnd, SB_HORZ, 0, hmaxPos, FALSE);

	}
	
	// TODO: Add your message handler code here
	
}
