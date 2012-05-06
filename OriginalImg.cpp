// OriginalImg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageInterpolazation.h"
#include "OriginalImg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COriginalImg dialog


COriginalImg::COriginalImg(CWnd* pParent /*=NULL*/)
	: CDialog(COriginalImg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COriginalImg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	imgBuf = NULL;
	grayBuf = NULL;
	m_width = 0;
	m_height = 0;
}


void COriginalImg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COriginalImg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COriginalImg, CDialog)
	//{{AFX_MSG_MAP(COriginalImg)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COriginalImg message handlers

void COriginalImg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here	
	
	CWnd *pWnd = GetDlgItem(IDC_ORGIMG);
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
	//show  image
	BITMAPINFOHEADER *bmpinfo = (BITMAPINFOHEADER *)(imgBuf + sizeof(BITMAPFILEHEADER));
	LPBITMAPINFO lpbmp = new BITMAPINFO;
	ZeroMemory(lpbmp, sizeof(BITMAPINFO));
	lpbmp->bmiHeader = *bmpinfo;
	StretchDIBits(pdc.GetSafeHdc(),  0,  0, m_width,  m_height,  0,  0,  m_width,  m_height, grayBuf,  lpbmp,  DIB_RGB_COLORS,  SRCCOPY);  
	// Do not call CDialog::OnPaint() for painting messages
}

void COriginalImg::SetBuffer(BYTE *img, BYTE *gray, int w, int h)
{
	imgBuf = img;
	grayBuf = gray;
	m_width = w;
	m_height = h;
}

BOOL COriginalImg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_DISPLAYER)), TRUE);
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_DISPLAYER)), FALSE);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COriginalImg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	imgBuf = NULL;
	grayBuf = NULL;
	::DestroyWindow(this->m_hWnd);
	CDialog::OnClose();
}
