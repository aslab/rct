// SimpleUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleUI.h"
#include "SimpleUIDlg.h"
#include "ControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MIN_FPS 1
#define MAX_FPS 60

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
// CSimpleUIDlg dialog

CSimpleUIDlg::CSimpleUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimpleUIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSimpleUIDlg)
	m_model = _T("");
	m_position = _T("");
	m_cHost = _T("");
	m_cPort = 0;
	m_vHost = _T("");
	m_vPort = 0;
	m_fps = 0;
	m_local = -1;
	m_remote = -1;
	m_resValue = 0;
	m_resText = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimpleUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimpleUIDlg)
	DDX_Control(pDX, IDC_RESOLUTION, m_cResolution);
	DDX_CBString(pDX, IDC_MODEL, m_model);
	DDX_Text(pDX, IDC_POSITION, m_position);
	DDX_Text(pDX, IDC_CHOST, m_cHost);
	DDX_Text(pDX, IDC_CPORT, m_cPort);
	DDX_Text(pDX, IDC_VHOST, m_vHost);
	DDX_Text(pDX, IDC_VPORT, m_vPort);
	DDX_Text(pDX, IDC_FPS, m_fps);
	DDV_MinMaxFloat(pDX, m_fps, 1.e-002f, 60.f);
	DDX_Radio(pDX, IDC_LOCAL, m_local);
	DDX_Radio(pDX, IDC_REMOTE, m_remote);
	DDX_Slider(pDX, IDC_RESOLUTION, m_resValue);
	DDX_Text(pDX, IDC_RESOLUTION2, m_resText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSimpleUIDlg, CDialog)
	//{{AFX_MSG_MAP(CSimpleUIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_REMOTE, OnRemote)
	ON_BN_CLICKED(IDC_LOCAL, OnLocal)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_RESOLUTION, OnReleasedcaptureResolution)
	ON_NOTIFY(UDN_DELTAPOS, IDC_FPS2, OnDeltaposFps2)
	ON_BN_CLICKED(IDC_START, OnStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleUIDlg message handlers

BOOL CSimpleUIDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	m_cHost = "127.0.0.1";
	m_cPort = 3000;
	m_vHost = "127.0.0.1";
	m_vPort = 5003;
	m_model = "P2DX";
	m_position = "4.5,1.9,1.8";
	m_remote = 1;
	m_local = 0;
	m_fps = 10;
	m_cResolution.SetRange(0,20,TRUE);
	m_resText = "320x240";
	m_resValue = 10;
	m_width = 320;
	m_height = 240;
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSimpleUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSimpleUIDlg::OnPaint() 
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
HCURSOR CSimpleUIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSimpleUIDlg::OnRemote() 
{
	// TODO: Add your control notification handler code here
	m_remote = 0;
	m_local = 1;
	GetDlgItem(IDC_VHOST)->EnableWindow(true);
	GetDlgItem(IDC_VPORT)->EnableWindow(true);
	GetDlgItem(IDC_RESOLUTION)->EnableWindow(false);
	GetDlgItem(IDC_FPS)->EnableWindow(false);
	GetDlgItem(IDC_FPS2)->EnableWindow(false);
	UpdateData(FALSE);
}

void CSimpleUIDlg::OnLocal() 
{
	// TODO: Add your control notification handler code here
	m_remote = 1;
	m_local = 0;
	GetDlgItem(IDC_VHOST)->EnableWindow(false);
	GetDlgItem(IDC_VPORT)->EnableWindow(false);
	GetDlgItem(IDC_RESOLUTION)->EnableWindow(true);
	GetDlgItem(IDC_FPS)->EnableWindow(true);
	GetDlgItem(IDC_FPS2)->EnableWindow(true);
	UpdateData(FALSE);
}

void CSimpleUIDlg::OnReleasedcaptureResolution(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_width = 160 + 16*m_resValue;
	m_height = 120 + 12*m_resValue;
	m_resText.Format("%dx%d",m_width,m_height);
	UpdateData(FALSE);
	*pResult = 0;
}

void CSimpleUIDlg::OnDeltaposFps2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if (m_fps>10 || (m_fps==10 && pNMUpDown->iDelta>0))
		m_fps += pNMUpDown->iDelta*2;
	else
		m_fps += pNMUpDown->iDelta;
	m_fps = m_fps<MIN_FPS?MIN_FPS:(m_fps>MAX_FPS?MAX_FPS:m_fps);
	UpdateData(FALSE);
	*pResult = 0;
}

void CSimpleUIDlg::OnStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_fps<0.01 || m_fps>60) return;
	GetDlgItem(IDC_START)->EnableWindow(false);
	CControlDlg * cDlg = new CControlDlg(this);
	cDlg->DoModal();
	delete cDlg;
	GetDlgItem(IDC_START)->EnableWindow(true);
}
