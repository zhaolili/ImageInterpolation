// ImageInterpolazationDlg.cpp : implementation file
//

#include "stdafx.h"
#include <wingdi.h>
#include "ImageInterpolazation.h"
#include "ImageInterpolazationDlg.h"
#include "OriginalImg.h"
#include "InterpolatedImg.h"
#include "FileSaveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define S(x) (x>=2) ? 0.0 : ((x>=1) ? (4-8*x+5*x*x-x*x*x) : (1-2*x*x+x*x*x))
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageInterpolazationDlg dialog

CImageInterpolazationDlg::CImageInterpolazationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageInterpolazationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageInterpolazationDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	checkedIPmethod = 0;
	checkedZoomer = 0;   

	zoomerWidth = 0;
	zoomerHeight = 0;

	rgbBuf = NULL;
	imgBuf = NULL;
	grayBuf = NULL;

	zoomerRGBbuf = NULL;
	zoomerIMGbuf = NULL;
	zoomerGRAYbuf = NULL;

	m_lpbmi = NULL;

	m_width = 0;
	m_height = 0;
}


void CImageInterpolazationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageInterpolazationDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImageInterpolazationDlg, CDialog)
	//{{AFX_MSG_MAP(CImageInterpolazationDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTOPENFILE, OnBtopenfile)
	ON_BN_CLICKED(IDC_BTINTERPOLATE, OnBtinterpolate)
	ON_BN_CLICKED(IDC_GRAY, OnGray)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RadioNearestNeighbor, OnRadioNearestNeighbor)
	ON_BN_CLICKED(IDC_RadioBiLinear, OnRadioBiLinear)
	ON_BN_CLICKED(IDC_RadioBicubic, OnRadioBicubic)
	ON_BN_CLICKED(IDC_RADIOZOOM2, OnRadiozoom2)
	ON_BN_CLICKED(IDC_RADIOZOOM3, OnRadiozoom3)
	ON_BN_CLICKED(IDC_RADIOZOOM4, OnRadiozoom4)
	ON_BN_CLICKED(IDC_BTSAVE, OnBtsave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageInterpolazationDlg message handlers

BOOL CImageInterpolazationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_Author)), TRUE);
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_Author)), FALSE);
	
	// TODO: Add extra initialization here
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImageInterpolazationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageInterpolazationDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageInterpolazationDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CImageInterpolazationDlg::OnBtopenfile() 
{
	// TODO: Add your control notification handler code here
	//if image is already opened
	if (m_orgImg.m_hWnd)
	{
		::DestroyWindow(m_orgImg.m_hWnd);
	}
	if (m_interImg.m_hWnd)
	{
		::DestroyWindow(m_interImg.m_hWnd);
	}

	//initialization
	SetDlgItemText(IDC_GRAY, "gray");
	if (checkedIPmethod!=0)
	{
		((CButton *)GetDlgItem(GetCheckedRadioButton(IDC_RadioNearestNeighbor, IDC_RadioBicubic)))->SetCheck(FALSE);
		checkedIPmethod = 0;
	}
	if (checkedZoomer!=0)
	{
		((CButton *)GetDlgItem(GetCheckedRadioButton(IDC_RADIOZOOM2, IDC_RADIOZOOM4)))->SetCheck(FALSE);
		checkedZoomer = 0;
	}	

	//select an image
	CFileDialog selectDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, NULL, NULL);
	selectDlg.m_ofn.lpstrTitle = TEXT("Select an image") ;
	selectDlg.m_ofn.lpstrFilter="BMP Files (*.bmp)\0*.bmp\0\0";
	int retVal = selectDlg.DoModal();
	CString fext = selectDlg.GetFileExt();
	while((fext != "bmp")&&(retVal!=IDCANCEL))
	{
		MessageBox("invalid image file!");
		retVal = selectDlg.DoModal();
		fext = selectDlg.GetFileExt();
	}
	if (retVal == IDCANCEL)
		return;	

	//get image path name
	inputPathname = selectDlg.GetPathName();
	inputimgnam = selectDlg.GetFileTitle();  //inputimgnam does not include the file extension
	if(LoadSrcImg(inputPathname))
		return;
	else
		MessageBox("Open image failed.");
}

//load source image, get the RGB data from bmp file
BOOL CImageInterpolazationDlg::LoadSrcImg(CString fpathnam)
{
	if (m_bmp.m_hObject!=NULL)
		m_bmp.DeleteObject();

	//load source image
	HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), fpathnam, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
	if (hBmp==NULL)
		return FALSE;
	m_bmp.Attach(hBmp);
	DIBSECTION ds;
	BITMAPINFOHEADER &bmpInfo = ds.dsBmih;
	m_bmp.GetObject(sizeof(DIBSECTION), &ds);

	//get image width and height
	m_width		= bmpInfo.biWidth;
	m_height	= bmpInfo.biHeight;

	//read from input image
	CFile infile;
	infile.Open(fpathnam, CFile::modeRead);
	UINT flen = (UINT)infile.GetLength();
	infile.SeekToBegin();
	if (imgBuf)
		delete[] imgBuf;
	imgBuf = new BYTE[flen];
	infile.Read((void *)imgBuf, flen);
	infile.Close();

	//get rgb data
	BITMAPFILEHEADER *bmpfile = (BITMAPFILEHEADER *)imgBuf;
	BITMAPINFOHEADER *bmpinfo = (BITMAPINFOHEADER *)(imgBuf + sizeof(BITMAPFILEHEADER));
	if (bmpfile->bfType != 0x4d42)
	{
		AfxMessageBox("Image is not a bmp file.");
		return FALSE;
	}
	if (bmpinfo->biBitCount!=24)
	{
		AfxMessageBox("Not supported format.");
		return FALSE;
	}
	int bbc = bmpinfo->biBitCount;   //biBitCount
	int bpl = ((bbc*m_width + 31)/32)*4;   //bytes per line, must be divided by 4 Bytes	
	int imgsize = bpl*m_height;
	BYTE *rgbData = (BYTE *)(imgBuf + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));
	if (rgbBuf)
		delete[] rgbBuf;
	if (grayBuf)
		delete[] grayBuf;
	grayBuf = new BYTE[imgsize];
	rgbBuf = new BYTE[imgsize];

	for (int k=0; k<m_height; k++)
	{
		memcpy(rgbBuf+k*bpl, rgbData+k*bpl, bpl);
		memcpy(grayBuf+k*bpl, rgbData+k*bpl, bpl);
	}

	//
	LPBITMAPINFO lpbmp = new BITMAPINFO;
	ZeroMemory(lpbmp, sizeof(BITMAPINFO));
	lpbmp->bmiHeader = *bmpinfo;


	//create the albedo dialog for display
	m_orgImg.Create(IDD_ORGIMG, this);
	//get the space size between the border and client area of the dialog
	CWnd *pWnd = m_orgImg.GetDlgItem(IDC_ORGIMG);
	CRect rect;
	pWnd->GetWindowRect(&rect);
	m_orgImg.ScreenToClient(&rect);
	//set position
	::SetWindowPos(m_orgImg.m_hWnd,HWND_TOPMOST,0, 0, m_width+(2*rect.left),m_height+(2*rect.top),SWP_SHOWWINDOW);
	m_orgImg.ShowWindow(SW_SHOW);

	//set buffer for m_orgdlg
	m_orgImg.SetBuffer(imgBuf, grayBuf, m_width, m_height);

 	//show image
	//This part is done in the OnPaint() function of COriginalImg

	return TRUE;
}


BOOL CImageInterpolazationDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (rgbBuf)
	{
		delete[] rgbBuf;
		rgbBuf = NULL;
	}
	
	if (imgBuf)
	{
		delete[] imgBuf;
		rgbBuf = NULL;
	}

	if (grayBuf)
	{
		delete[] grayBuf;
		grayBuf = NULL;
	}

	if (zoomerRGBbuf)
	{
		delete[] zoomerRGBbuf;
		zoomerRGBbuf = NULL;
	}

	if (zoomerGRAYbuf)
	{
		delete[] zoomerGRAYbuf;
		zoomerGRAYbuf = NULL;
	}

	if (zoomerIMGbuf)
	{
		delete[] zoomerIMGbuf;
		zoomerIMGbuf = NULL;
	}

	if (m_lpbmi)
	{
		delete m_lpbmi;
		m_lpbmi = NULL;
	}
	
	return CDialog::DestroyWindow();
}

//from bottom->top to top->bottom, for bmp file
void CImageInterpolazationDlg::HeadStand(void *buffer, int height, int width, int bitdep)
{
	int imgsize = width*height;
	int dist;
	void *buftmp;
	if (bitdep==8)
	{
		buftmp = new BYTE[imgsize*3];
		dist	 = width*3*sizeof(BYTE);
	}
	else
	{
		buftmp = new USHORT[imgsize*3];
		dist	 = width*3*sizeof(USHORT);
	}
	
	for (int i=0; i<height/2; i++)
	{
		memcpy((BYTE*)buftmp, (BYTE*)buffer+i*dist, dist);
		memcpy((BYTE*)buffer+i*dist, (BYTE*)buffer+(height-1)*dist-i*dist, dist);
		memcpy((BYTE*)buffer+(height-1)*dist-i*dist, buftmp, dist);
	}
	
	delete[] buftmp;
}

void CImageInterpolazationDlg::OnBtinterpolate() 
{
	// TODO: Add your control notification handler code here
	//if interpolation method is not selected
	if (m_orgImg.m_hWnd==NULL)
	{
		MessageBox("No image.");
		return;
	}
	if (m_interImg.m_hWnd!=NULL)
	{
		::DestroyWindow(m_interImg.m_hWnd);
	}
	if (checkedIPmethod==0)
	{
		MessageBox("Choose interpolation.");
		return;
	}
	if (checkedZoomer==0)
	{
		MessageBox("Choose zoomer.");
		return;
	}
	switch (checkedIPmethod)
	{
	case IDC_RadioNearestNeighbor:
		NearestNeighbor(checkedZoomer);
		break;
	case IDC_RadioBiLinear:
		BiLinear(checkedZoomer);
		break;
	case IDC_RadioBicubic:
		Cubic(checkedZoomer);
		break;
	}

	//get DIB of interpolated image, m_lpbmi struct 
	GetInterDIB();
	
	//create the albedo dialog for display
	m_interImg.SetBuffer(zoomerIMGbuf, zoomerGRAYbuf, m_lpbmi, zoomerWidth, zoomerHeight);
	m_interImg.Create(IDD_INTERPOLATEDIMG, this);
	//get the space size between the border and client area of the dialog
	CWnd *pWnd = m_interImg.GetDlgItem(IDC_INTERPOLATEDIMG);
	CRect rect;
	pWnd->GetWindowRect(&rect);
	m_interImg.ScreenToClient(&rect);
	//set position
	int neww = m_width*checkedZoomer;
	int newh = m_height*checkedZoomer;
	::SetWindowPos(m_interImg.m_hWnd, HWND_TOPMOST, 0, 0, m_width+(2*rect.left), m_height+(2*rect.top),SWP_SHOWWINDOW);
	m_interImg.ShowWindow(SW_SHOW);

	//m_interImg.SetBuffer(zoomerIMGbuf, zoomerGRAYbuf, m_lpbmi, zoomerWidth, zoomerHeight);
	int vmaxPos = (int)((newh-m_height+2*rect.top+9)/10);  //suppose i unit means 10pixels
	int hmaxPos = (int)((neww-m_width+2*rect.left+9)/10);
	::SetScrollRange(m_interImg.m_hWnd, SB_VERT, 0, vmaxPos, FALSE);
	::SetScrollRange(m_interImg.m_hWnd, SB_HORZ, 0, hmaxPos, FALSE);

	return;
}

void CImageInterpolazationDlg::OnGray() 
{
	// TODO: Add your control notification handler code here
	if (m_orgImg.m_hWnd==NULL)
	{
		MessageBox("Load image first.");
		return;
	}

	BITMAPINFOHEADER *bmpinfo = (BITMAPINFOHEADER *)(imgBuf + sizeof(BITMAPFILEHEADER));
	int bbc, bpl;

	CString text;
	GetDlgItemText(IDC_GRAY, text);
	if (text=="gray")
	{
		bbc = bmpinfo->biBitCount;   //biBitCount
		bpl = ((bbc*m_width + 31)/32)*4;   //bytes per line, must be divied by 4 Bytes	
		
		int grayscale, r, g, b;
		int i, j, sp;
		for (j=0; j<m_height; j++)
		{
			for (i=0; i<m_width; i++)
			{
				sp = j*bpl + i*3;
				//get color r,g,b value
				r = rgbBuf[sp];
				g = rgbBuf[sp+1];
				b = rgbBuf[sp+2];
				//get gray value
				grayscale = (9798*r + 19238*g + 3728*b)/32768;
				grayBuf[sp] = grayBuf[sp+1] = grayBuf[sp+2] = grayscale;
			}
		}
		
		if (m_interImg.m_hWnd!=NULL)
		{
			bbc = (m_lpbmi->bmiHeader).biBitCount;
			bpl = ((bbc*zoomerWidth + 31)/32)*4;
			
			for (j=0; j<zoomerHeight; j++)
			{
				for (i=0; i<zoomerWidth; i++)
				{
					sp = j*bpl + i*3;
					//get color r,g,b value
					r = zoomerRGBbuf[sp];
					g = zoomerRGBbuf[sp+1];
					b = zoomerRGBbuf[sp+2];
					//get gray value
					grayscale = (9798*r + 19238*g + 3728*b)/32768;
					zoomerGRAYbuf[sp] = zoomerGRAYbuf[sp+1] = zoomerGRAYbuf[sp+2] = grayscale;
				}
			}
			//refresh
			m_interImg.SetFocus();
			m_interImg.Invalidate(FALSE);
		}
		
		SetDlgItemText(IDC_GRAY, "color");
	}
	else
	{
		//original
		bbc = bmpinfo->biBitCount;   //biBitCount
		bpl = ((bbc*m_width + 31)/32)*4;   //bytes per line, must be divied by 4 Bytes
		int imgbytes = bpl * m_height;
		memcpy(grayBuf, rgbBuf, imgbytes);
		//interpolated
		if (m_interImg.m_hWnd!=NULL)
		{
			bbc = (m_lpbmi->bmiHeader).biBitCount;
			bpl = ((bbc*zoomerWidth + 31)/32)*4;
			imgbytes = bpl * zoomerHeight;
			memcpy(zoomerGRAYbuf, zoomerRGBbuf, imgbytes);

			//refresh
			m_interImg.SetFocus();
			m_interImg.Invalidate(FALSE);
		}

		SetDlgItemText(IDC_GRAY, "gray");
	}

	//refresh picture
	m_orgImg.SetFocus();
	m_orgImg.Invalidate(FALSE);    //very useful
	//..... 
	//show gray image	//
}

HBRUSH CImageInterpolazationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

//nearest neighbor interpolation
void CImageInterpolazationDlg::NearestNeighbor(int zm)
{
	BITMAPINFOHEADER *bmpinfo = (BITMAPINFOHEADER *)(imgBuf + sizeof(BITMAPFILEHEADER));
	int bbc = bmpinfo->biBitCount;   //biBitCount
	int zoomer = zm;
	zoomerWidth = m_width*zoomer;
	zoomerHeight = m_height*zoomer;
	int bpl = ((bbc*zoomerWidth + 31)/32)*4;   //bytes per line, must be divied by 4 Bytes
	int obpl = ((bbc*m_width+31)/32)*4;
	int bufsize = bpl*zoomerHeight;

	if (zoomerRGBbuf)
	{
		delete[] zoomerRGBbuf;
		zoomerRGBbuf = NULL;
	}		
	if (zoomerGRAYbuf)
	{
		delete[] zoomerGRAYbuf;
		zoomerGRAYbuf = NULL;
	}	

	zoomerRGBbuf = new BYTE[bufsize];
	zoomerGRAYbuf = new BYTE[bufsize];
	memset(zoomerRGBbuf, 0, bufsize);
	memset(zoomerGRAYbuf, 0, bufsize);

	int oj, oi, osp, sp;
	for (int j=0; j<zoomerHeight; j++)
	{
		for (int i=0; i<zoomerWidth; i++)
		{
			oj = (int)(j/(float)zoomer);
			oi = (int)(i/(float)zoomer);
			sp = j*bpl + i*3;
			osp = oj*obpl + oi*3;
			zoomerRGBbuf[sp] = rgbBuf[osp];
			zoomerGRAYbuf[sp] = grayBuf[osp];
			zoomerRGBbuf[sp+1] = rgbBuf[osp+1];
			zoomerGRAYbuf[sp+1] = grayBuf[osp+1];
			zoomerRGBbuf[sp+2] = rgbBuf[osp+2];
			zoomerGRAYbuf[sp+2] = grayBuf[osp+2];
		}
	}
}

//bilinear interpolation
void CImageInterpolazationDlg::BiLinear(int zm)
{
	BITMAPINFOHEADER *bmpinfo = (BITMAPINFOHEADER *)(imgBuf + sizeof(BITMAPFILEHEADER));
	int bbc = bmpinfo->biBitCount;   //biBitCount
	int zoomer = zm;
	zoomerWidth = m_width*zoomer;
	zoomerHeight = m_height*zoomer;
	int bpl = ((bbc*zoomerWidth + 31)/32)*4;   //bytes per line, must be divied by 4 Bytes
	int obpl = ((bbc*m_width+31)/32)*4;
	int bufsize = bpl*zoomerHeight;
	
	if (zoomerRGBbuf)
	{
		delete[] zoomerRGBbuf;
		zoomerRGBbuf = NULL;
	}		
	if (zoomerGRAYbuf)
	{
		delete[] zoomerGRAYbuf;
		zoomerGRAYbuf = NULL;
	}	
	
	zoomerRGBbuf = new BYTE[bufsize];
	zoomerGRAYbuf = new BYTE[bufsize];
	memset(zoomerRGBbuf, 0, bufsize);
	memset(zoomerGRAYbuf, 0, bufsize);
	
	int oj, oi,  sp, i, j;
	int osp, ospj, ospi, ospij;
	float ni, nj, u, v;
	float u1v1, u1v, uv1, uv;
	for (j=0; j<zoomerHeight; j++)
	{
		for (i=0; i<zoomerWidth; i++)
		{
			ni = i/(float)zoomer;
			nj = j/(float)zoomer;
			oj = (int)nj;
			oi = (int)ni;

			if ((oj>=(m_height-1))||(oi>=(m_width-1)))
			{
				osp = oj*obpl+oi*3;
				zoomerRGBbuf[sp] = rgbBuf[osp];
				zoomerRGBbuf[sp+1] = rgbBuf[osp+1];
				zoomerRGBbuf[sp+2] = rgbBuf[osp+2];
				zoomerGRAYbuf[sp] = grayBuf[osp];
				zoomerGRAYbuf[sp+1] = grayBuf[osp+1];
				zoomerGRAYbuf[sp+2] = grayBuf[osp+2];
				continue;
			}

			u = nj - oj;
			v = ni - oi;
			u1v1 = (1-u)*(1-v);
			uv1 = (1-v)*u;
			u1v = (1-u)*v;
			uv = u*v;

			sp = j*bpl + i*3;
			osp = oj*obpl + oi*3;
			ospi = oj*obpl + (oi+1)*3;
			ospj = (oj+1)*obpl + oi*3;
			ospij = (oj+1)*obpl + (oi+1)*3;			

			zoomerRGBbuf[sp] = (int)(u1v1*rgbBuf[osp] + u1v*rgbBuf[ospi] + uv1*rgbBuf[ospj] + uv*rgbBuf[ospij]);
			zoomerRGBbuf[sp+1] = (int)(u1v1*rgbBuf[osp+1] + u1v*rgbBuf[ospi+1] + uv1*rgbBuf[ospj+1] + uv*rgbBuf[ospij+1]);
			zoomerRGBbuf[sp+2] = (int)(u1v1*rgbBuf[osp+2] + u1v*rgbBuf[ospi+2] + uv1*rgbBuf[ospj+2] + uv*rgbBuf[ospij+2]);

			zoomerGRAYbuf[sp] = (int)(u1v1*grayBuf[osp] + u1v*grayBuf[ospi] + uv1*grayBuf[ospj] + uv*grayBuf[ospij]);			
			zoomerGRAYbuf[sp+1] = (int)(u1v1*grayBuf[osp+1] + u1v*grayBuf[ospi+1] + uv1*grayBuf[ospj+1] + uv*grayBuf[ospij+1]);
			zoomerGRAYbuf[sp+2] = (int)(u1v1*grayBuf[osp+2] + u1v*grayBuf[ospi+2] + uv1*grayBuf[ospj+2] + uv*grayBuf[ospij+2]);
		}
	}	
}


//cubic convolution interpolation
void CImageInterpolazationDlg::Cubic(int zm)
{
	BITMAPINFOHEADER *bmpinfo = (BITMAPINFOHEADER *)(imgBuf + sizeof(BITMAPFILEHEADER));
	int bbc = bmpinfo->biBitCount;   //biBitCount
	int zoomer = zm;
	zoomerWidth = m_width*zoomer;
	zoomerHeight = m_height*zoomer;
	int bpl = ((bbc*zoomerWidth + 31)/32)*4;   //bytes per line, must be divied by 4 Bytes
	int obpl = ((bbc*m_width+31)/32)*4;
	int bufsize = bpl*zoomerHeight;
	int i, j, m, n;
	int oj, oi, osp, sp;
	float ni, nj, u, v;

	//
	if (zoomerRGBbuf)
	{
		delete[] zoomerRGBbuf;
		zoomerRGBbuf = NULL;
	}		
	if (zoomerGRAYbuf)
	{
		delete[] zoomerGRAYbuf;
		zoomerGRAYbuf = NULL;
	}	
	zoomerRGBbuf = new BYTE[bufsize];
	zoomerGRAYbuf = new BYTE[bufsize];
	memset(zoomerRGBbuf, 0, bufsize);
	memset(zoomerGRAYbuf, 0, bufsize);
	
	///////
	float s_uplus1, s_u, s_uminus1, s_uminus2;
	float s_vplus1, s_v, s_vminus1, s_vminus2;
	float x, r, g, b;

	float A[4] = {0.0, 0.0, 0.0, 0.0};
	float C[4] = {0.0, 0.0, 0.0, 0.0};
	BYTE **B = new BYTE *[4];
	BYTE **Bg = new BYTE *[4];
	BYTE **Bb = new BYTE *[4];
	for (j=0; j<4; j++)
 	{
		B[j] = new BYTE[4];
		Bg[j] = new BYTE[4];
		Bb[j] = new BYTE[4];
	}

	for (j=0; j<zoomerHeight; j++)
	{
		for (i=0; i<zoomerWidth; i++)
		{
			sp = j*bpl + i*3;
			ni = i/(float)zoomer;
			nj = j/(float)zoomer;
			oj = (int)nj;
			oi = (int)ni;
			u = nj - oj;
			v = ni - oi;

			if ((oj>=(m_height-2))||(oi>=(m_width-2))||(oj==0)||(oi==0))
			{
				osp = oj*obpl+oi*3;
				zoomerRGBbuf[sp] = rgbBuf[osp];
				zoomerRGBbuf[sp+1] = rgbBuf[osp+1];
				zoomerRGBbuf[sp+2] = rgbBuf[osp+2];
				zoomerGRAYbuf[sp] = grayBuf[osp];
				zoomerGRAYbuf[sp+1] = grayBuf[osp+1];
				zoomerGRAYbuf[sp+2] = grayBuf[osp+2];
				continue;
			}

			x = ((u+1)>=0)?(u+1):(-u-1);
			s_uplus1 = (x>=2) ? 0.0 : ((x>=1) ? (4-8*x+5*x*x-x*x*x) : (1-2*x*x+x*x*x));
			x = (u>=0)?u:(-u);
			s_u = (x>=2) ? 0.0 : ((x>=1) ? (4-8*x+5*x*x-x*x*x) : (1-2*x*x+x*x*x));
			x = ((u-1)>=0)?(u-1):(-u+1);
			s_uminus1 = (x>=2) ? 0.0 : ((x>=1) ? (4-8*x+5*x*x-x*x*x) : (1-2*x*x+x*x*x));
			x = ((u-2)>=0)?(u-2):(-u+2);
			s_uminus2 = (x>=2) ? 0.0 : ((x>=1) ? (4-8*x+5*x*x-x*x*x) : (1-2*x*x+x*x*x));
			A[0] = s_uplus1;
			A[1] = s_u;
			A[2] = s_uminus1;
			A[3] = s_uminus2;

			x = ((v+1)>=0)?(v+1):(-v-1);
			s_vplus1 = (x>=2) ? 0.0 : ((x>=1) ? (4-8*x+5*x*x-x*x*x) : (1-2*x*x+x*x*x));
			x = (v>=0)?v:(-v);
			s_v = (x>=2) ? 0.0 : ((x>=1) ? (4-8*x+5*x*x-x*x*x) : (1-2*x*x+x*x*x));
			x = ((v-1)>=0)?(v-1):(-v+1);
			s_vminus1 = (x>=2) ? 0.0 : ((x>=1) ? (4-8*x+5*x*x-x*x*x) : (1-2*x*x+x*x*x));
			x = ((v-2)>=0)?(v-2):(-v+2);
			s_vminus2 = (x>=2) ? 0.0 : ((x>=1) ? (4-8*x+5*x*x-x*x*x) : (1-2*x*x+x*x*x));
			C[0] = s_vplus1;
			C[1] = s_v;
			C[2] = s_vminus1;
			C[3] = s_vminus2;

			//assignMatrix(B, orgbufR, oj+1, oi+1);
			//////////////////////////////////////////////////////////////////////////
			osp = (oj-1)*obpl + (oi-1)*3;
			B[0][0] = grayBuf[osp];
			Bg[0][0] = grayBuf[osp+1];
			Bb[0][0] = grayBuf[osp+2];

			osp = (oj-1)*obpl + oi*3;
			B[0][1] = grayBuf[osp];
			Bg[0][1] = grayBuf[osp+1];
			Bb[0][1] = grayBuf[osp+2];

			osp = (oj-1)*obpl + (oi+1)*3;			
			B[0][2] = grayBuf[osp];
			Bg[0][2] = grayBuf[osp+1];
			Bb[0][2] = grayBuf[osp+2];

			osp = (oj-1)*obpl + (oi+2)*3;			
			B[0][3] = grayBuf[osp];
			Bg[0][3] = grayBuf[osp+1];
			Bb[0][3] = grayBuf[osp+2];
			
			osp = oj*obpl + (oi-1)*3;			
			B[1][0] = grayBuf[osp];
			Bg[1][0] = grayBuf[osp+1];
			Bb[1][0] = grayBuf[osp+2];

			osp = oj*obpl + oi*3;
			B[1][1] = grayBuf[osp];
			Bg[1][1] = grayBuf[osp+1];
			Bb[1][1] = grayBuf[osp+2];

			osp = oj*obpl + (oi+1)*3;
			B[1][2] = grayBuf[osp];
			Bg[1][2] = grayBuf[osp+1];
			Bb[1][2] = grayBuf[osp+2];

			osp = oj*obpl + (oi+2)*3;
			B[1][3] = grayBuf[osp];
			Bg[1][3] = grayBuf[osp+1];
			Bb[1][3] = grayBuf[osp+2];
			
			osp = (oj+1)*obpl + (oi-1)*3;			
			B[2][0] = grayBuf[osp];
			Bg[2][0] = grayBuf[osp+1];
			Bb[2][0] = grayBuf[osp+2];

			osp = (oj+1)*obpl + oi*3;
			B[2][1] = grayBuf[osp];
			Bg[2][1] = grayBuf[osp+1];
			Bb[2][1] = grayBuf[osp+2];

			osp = (oj+1)*obpl + (oi+1)*3;
			B[2][2] = grayBuf[osp];
			Bg[2][2] = grayBuf[osp+1];
			Bb[2][2] = grayBuf[osp+2];

			osp = (oj+1)*obpl + (oi+2)*3;
			B[2][3] = grayBuf[osp];
			Bg[2][3] = grayBuf[osp+1];
			Bb[2][3] = grayBuf[osp+2];
			
			osp = (oj+2)*obpl + (oi-1)*3;			
			B[3][0] = grayBuf[osp];
			Bg[3][0] = grayBuf[osp+1];
			Bb[3][0] = grayBuf[osp+2];

			osp = (oj+2)*obpl + oi*3;
			B[3][1] = grayBuf[osp];
			Bg[3][1] = grayBuf[osp+1];
			Bb[3][1] = grayBuf[osp+2];

			osp = (oj+2)*obpl + (oi+1)*3;
			B[3][2] = grayBuf[osp];
			Bg[3][2] = grayBuf[osp+1];
			Bb[3][2] = grayBuf[osp+2];

			osp = (oj+2)*obpl + (oi+2)*3;
			B[3][3] = grayBuf[osp];
			Bg[3][3] = grayBuf[osp+1];
			Bb[3][3] = grayBuf[osp+2];
			//////////////////////////////////////////////////////////////////////////
			r=0.0;
			g=0.0;
			b=0.0;
			for (n=0; n<4; n++)
			{
				for (m=0; m<4; m++)
				{
					r += A[m]*B[m][n]*C[n];
					g += A[m]*Bg[m][n]*C[n];
					b += A[m]*Bb[m][n]*C[n];
				}
					
			}
			
			r = (r>0)?((r<255)?r:255):0;
			g = (g>0)?((g<255)?g:255):0;
			b = (b>0)?((b<255)?b:255):0;
			zoomerGRAYbuf[sp] = (int) r;
			zoomerGRAYbuf[sp+1] = (int) g;
			zoomerGRAYbuf[sp+2] = (int) b;


			//////////////////////////////////////////////////////////////////////////
			osp = (oj-1)*obpl + (oi-1)*3;
			B[0][0] = rgbBuf[osp];
			Bg[0][0] = rgbBuf[osp+1];
			Bb[0][0] = rgbBuf[osp+2];
			osp = (oj-1)*obpl + oi*3;
			B[0][1] = rgbBuf[osp];
			Bg[0][1] = rgbBuf[osp+1];
			Bb[0][1] = rgbBuf[osp+2];
			osp = (oj-1)*obpl + (oi+1)*3;
			B[0][2] = rgbBuf[osp];
			Bg[0][2] = rgbBuf[osp+1];
			Bb[0][2] = rgbBuf[osp+2];
			osp = (oj-1)*obpl + (oi+2)*3;
			B[0][3] = rgbBuf[osp];
			Bg[0][3] = rgbBuf[osp+1];
			Bb[0][3] = rgbBuf[osp+2];
			
			osp = oj*obpl + (oi-1)*3;
			B[1][0] = rgbBuf[osp];
			Bg[1][0] = rgbBuf[osp+1];
			Bb[1][0] = rgbBuf[osp+2];
			osp = oj*obpl + oi*3;
			B[1][1] = rgbBuf[osp];
			Bg[1][1] = rgbBuf[osp+1];
			Bb[1][1] = rgbBuf[osp+2];
			osp = oj*obpl + (oi+1)*3;
			B[1][2] = rgbBuf[osp];
			Bg[1][2] = rgbBuf[osp+1];
			Bb[1][2] = rgbBuf[osp+2];
			osp = oj*obpl + (oi+2)*3;
			B[1][3] = rgbBuf[osp];
			Bg[1][3] = rgbBuf[osp+1];
			Bb[1][3] = rgbBuf[osp+2];
			
			osp = (oj+1)*obpl + (oi-1)*3;
			B[2][0] = rgbBuf[osp];
			Bg[2][0] = rgbBuf[osp+1];
			Bb[2][0] = rgbBuf[osp+2];
			osp = (oj+1)*obpl + oi*3;
			B[2][1] = rgbBuf[osp];
			Bg[2][1] = rgbBuf[osp+1];
			Bb[2][1] = rgbBuf[osp+2];
			osp = (oj+1)*obpl + (oi+1)*3;
			B[2][2] = rgbBuf[osp];
			Bg[2][2] = rgbBuf[osp+1];
			Bb[2][2] = rgbBuf[osp+2];
			osp = (oj+1)*obpl + (oi+2)*3;
			B[2][3] = rgbBuf[osp];
			Bg[2][3] = rgbBuf[osp+1];
			Bb[2][3] = rgbBuf[osp+2];
			
			osp = (oj+2)*obpl + (oi-1)*3;
			B[3][0] = rgbBuf[osp];
			Bg[3][0] = rgbBuf[osp+1];
			Bb[3][0] = rgbBuf[osp+2];
			osp = (oj+2)*obpl + oi*3;
			B[3][1] = rgbBuf[osp];
			Bg[3][1] = rgbBuf[osp+1];
			Bb[3][1] = rgbBuf[osp+2];
			osp = (oj+2)*obpl + (oi+1)*3;
			B[3][2] = rgbBuf[osp];
			Bg[3][2] = rgbBuf[osp+1];
			Bb[3][2] = rgbBuf[osp+2];
			osp = (oj+2)*obpl + (oi+2)*3;
			B[3][3] = rgbBuf[osp];
			Bg[3][3] = rgbBuf[osp+1];
			Bb[3][3] = rgbBuf[osp+2];
			//////////////////////////////////////////////////////////////////////////
			r=0.0;
			g=0.0;
			b=0.0;
			for (n=0; n<4; n++)
			{
				for (m=0; m<4; m++)
				{
					r += A[m]*B[m][n]*C[n];
					g += A[m]*Bg[m][n]*C[n];
					b += A[m]*Bb[m][n]*C[n];
				}
				
			}
			r = (r>0)?((r<255)?r:255):0;
			g = (g>0)?((g<255)?g:255):0;
			b = (b>0)?((b<255)?b:255):0;			
			zoomerRGBbuf[sp] = (int) r;
			zoomerRGBbuf[sp+1] = (int) g;
			zoomerRGBbuf[sp+2] = (int) b;
 		}
	}


	for (j=0; j<4; j++)
	{
		delete[] B[j];
		delete[] Bg[j];
		delete[] Bb[j];
		B[j] = NULL;
		Bg[j] = NULL;
		Bb[j] = NULL;
	}
	delete[] B;
	delete[] Bg;
	delete[] Bb;
	B = NULL;
	Bg = NULL;
	Bb = NULL;	
}


//Get DIB of interpolated picture
void CImageInterpolazationDlg::GetInterDIB()
{
	//image width and height
	int imgw = zoomerWidth;
	int imgh = zoomerHeight;
	
	//BITMAPINFO
	if (m_lpbmi)
		delete m_lpbmi;
	
	m_lpbmi = new BITMAPINFO;
	ZeroMemory(m_lpbmi, sizeof(BITMAPINFO));
	m_lpbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); //The number of bytes required by the structure
	m_lpbmi->bmiHeader.biWidth = imgw; //The width of the bitmap, in pixels
	m_lpbmi->bmiHeader.biHeight = imgh;
	m_lpbmi->bmiHeader.biPlanes = 1; //The number of planes for the target device. This value must be set to 1
	m_lpbmi->bmiHeader.biBitCount = 24; //The number of bits-per-pixel
	m_lpbmi->bmiHeader.biCompression = BI_RGB;  //An uncompressed format
	m_lpbmi->bmiHeader.biSizeImage = 0; //The size, in bytes, of the image. This may be set to zero for BI_RGB bitmaps	
	m_lpbmi->bmiHeader.biXPelsPerMeter = 0; //The horizontal resolution, in pixels-per-meter, of the target device for the bitmap
	m_lpbmi->bmiHeader.biYPelsPerMeter = 0;	
	m_lpbmi->bmiHeader.biClrUsed = 0; //The number of color indexes in the color table that are actually used by the bitmap. 
	// 									//If this value is zero, the bitmap uses the maximum number of colors 
	// 									//corresponding to the value of the biBitCount member for the compression mode specified by biCompression.
	m_lpbmi->bmiHeader.biClrImportant = 0;  //The number of color indexes that are required for displaying the bitmap. If this value is zero, all colors are required.	
}

void CImageInterpolazationDlg::OnRadioNearestNeighbor() 
{
	// TODO: Add your control notification handler code here
	checkedIPmethod = IDC_RadioNearestNeighbor;
}

void CImageInterpolazationDlg::OnRadioBiLinear() 
{
	// TODO: Add your control notification handler code here
	checkedIPmethod = IDC_RadioBiLinear;
}

void CImageInterpolazationDlg::OnRadioBicubic() 
{
	// TODO: Add your control notification handler code here
	checkedIPmethod = IDC_RadioBicubic;
}

void CImageInterpolazationDlg::OnRadiozoom2() 
{
	// TODO: Add your control notification handler code here
	checkedZoomer = 2;
}

void CImageInterpolazationDlg::OnRadiozoom3() 
{
	// TODO: Add your control notification handler code here
	checkedZoomer = 3;
}

void CImageInterpolazationDlg::OnRadiozoom4() 
{
	// TODO: Add your control notification handler code here
	checkedZoomer = 4;
}

void CImageInterpolazationDlg::OnBtsave() 
{
	// TODO: Add your control notification handler code here
	if ((m_interImg.m_hWnd==NULL)&&(m_orgImg.m_hWnd==NULL))
	{
		MessageBox("No image.");
		return;
	}
	BYTE *outbuf;
	if (m_interImg.m_hWnd == NULL)
	{
		zoomerHeight = m_height;
		zoomerWidth = m_width;
		outbuf	= grayBuf;
	}
	else
		outbuf = zoomerGRAYbuf;

	CString strw, strh;
	strw.Format("%d", zoomerWidth);
	strh.Format("%d", zoomerHeight);
	CString defaultnam = inputimgnam + strw + "x" + strh + ".bmp";

	CFileSaveDlg fDlg(FALSE, NULL, defaultnam, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_EXPLORER|OFN_OVERWRITEPROMPT , NULL, NULL);
	
	CString pathname;  //output directory and file name
	if ( IDOK == fDlg.DoModal() )
	{
		pathname = fDlg.GetPathName();
    }
	
	//output
	// int bbc = (m_lpbmi->bmiHeader).biBitCount;
	int bbc = 24;		//
	int bpl = ((bbc*zoomerWidth + 31)/32)*4;
	int imagesize = bpl*zoomerHeight;
	
	//file header information
	BITMAPFILEHEADER bfh;
	bfh.bfType = 0x4d42;  //bm
	bfh.bfSize = imagesize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfOffBits = bfh.bfSize - imagesize;
	
	//bitmap data information
	BITMAPINFOHEADER bih;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = zoomerWidth;
	bih.biHeight = zoomerHeight;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = 0;
	bih.biSizeImage = imagesize;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;
	
	//
	FILE *fp = fopen(pathname, "wb");
	if (!fp)
	{
		MessageBox("intrinsic images saving failed.");
		return;
	}
	fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);
	fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);
	fwrite(outbuf, 1, imagesize, fp);
	fclose(fp);

	MessageBox("saved.");
	
	return;
}


