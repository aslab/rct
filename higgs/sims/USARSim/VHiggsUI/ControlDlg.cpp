// ControlDlg.cpp : implementation file
//
// Author: Jaime Fdez. Fisac @ ASLab

#include "stdafx.h"
#include "SimpleUI.h"
#include "ControlDlg.h"
#include "SimpleUIDlg.h"
#include "CmdSocket.h"
#include "VideoSocket.h"
#include "detours.h"
#include "FreeImage/FIIO_Mem.cpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define UTCNAME "Unreal Tournament 2004"
#define UTCAPP  "\\ut2004\\system\\ut2004.exe"
#define UTCCMD " 127.0.0.1?spectatoronly=1?quickstart=true -ini=usarsim.ini"
#define DLLFILE "\\ut2004\\system\\Hook.dll"
#define UTWND FindWindow(NULL,"Unreal Tournament 2004")

#define SPEED_MIN 0.1f
#define SPEED_MAX 2.0f
#define SPEED_STEP 0.2f

#define ZOOM_MIN 0.349f
#define ZOOM_MAX 1.5708f
#define ZOOM_STEP 0.0873f

#define TILT_MIN -0.7854f
#define TILT_MAX 0.7854f
#define TILT_STEP 0.1917f

#define PAN_MIN -3.1415f
#define PAN_MAX 3.1415f
#define PAN_STEP 0.1917f

#define MAX_MSGS 512
#define BLOCK 2048

#define arrayof(x)		(sizeof(x)/sizeof(x[0]))

char _dllPath[512];
char _utPath[512];

/////////////////////////////////////////////////////////////////////////////
// CControlDlg dialog


CControlDlg::CControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CControlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControlDlg)
	m_width = 0;
	m_height = 0;
	m_fps = 0.0f;
	//}}AFX_DATA_INIT
	if (pParent)
		m_parent = (CSimpleUIDlg*)pParent;
	m_cmdFile = NULL;
	m_arOut = m_arIn = NULL;
	m_cmdSocket = NULL;
	m_videoSocket = NULL;
	m_videoState = 0;
	m_imgType = 0;
	m_utclient = NULL;
	m_hookDLL = NULL;
	m_pFrameData = NULL;
	strcpy(_utPath,UTCAPP);
	strcpy(_dllPath,DLLFILE);
}

void CControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControlDlg)
	DDX_Control(pDX, IDC_LIGHT, m_light);
	DDX_Control(pDX, IDC_MSG_TREE, m_cMsgTree);
	DDX_Control(pDX, IDC_SHOWUT, m_showUT);
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDX_Text(pDX, IDC_FPS, m_fps);
	//}}AFX_DATA_MAP
	//=========================================================================
	DDX_Control(pDX, IDC_VEL, m_vel);
	DDX_Control(pDX, IDC_ROT, m_rot);
	//=========================================================================
}


BEGIN_MESSAGE_MAP(CControlDlg, CDialog)
	//{{AFX_MSG_MAP(CControlDlg)
	ON_BN_CLICKED(IDC_ZOOM_IN, OnZoomIn)
	ON_BN_CLICKED(IDC_ZOOM_OUT, OnZoomOut)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SPEED_DOWN, OnSpeedDown)
	ON_BN_CLICKED(IDC_SPEED_UP, OnSpeedUp)
	ON_BN_CLICKED(IDC_SHOWUT, OnShowut)
	ON_BN_CLICKED(IDC_CUP, OnCup)
	ON_BN_CLICKED(IDC_CDOWN, OnCdown)
	ON_BN_CLICKED(IDC_CLEFT, OnCleft)
	ON_BN_CLICKED(IDC_CRIGHT, OnCright)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_VLEFT, OnVleft)
	ON_BN_CLICKED(IDC_VRIGHT, OnVright)
	ON_BN_CLICKED(IDC_VUP, OnVup)
	ON_BN_CLICKED(IDC_VDOWN, OnVdown)
	ON_BN_CLICKED(IDC_LIGHT, OnLight)
	//========================================================================
	ON_EN_CHANGE(IDC_VEL, &CControlDlg::OnEnChangeVel)
	ON_EN_CHANGE(IDC_ROT, &CControlDlg::OnEnChangeRot)
	//========================================================================
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlDlg message handlers

BOOL CControlDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_videoState = 0;
	m_speed = 0.5;
	m_zoom = 0.8727f;
	m_fps = 0;
	m_width = m_height = 0;
	m_lastClock = 0;
	m_frameCount = 0;
	m_drMode = DR_STOP;
	m_pan = m_tilt = 0;

	m_dMsgTree.mt_time = m_cMsgTree.InsertItem(_T("Time:"),0,TVI_LAST);
	m_dMsgTree.mt_state = m_cMsgTree.InsertItem(_T("Robot State"),0,TVI_LAST);
	m_dMsgTree.mt_chassis = m_cMsgTree.InsertItem(_T("Chassis"),m_dMsgTree.mt_state,TVI_LAST);
	m_dMsgTree.mt_ch_rot = m_cMsgTree.InsertItem(_T("Rotation:"),m_dMsgTree.mt_chassis,TVI_LAST);
	m_dMsgTree.mt_ch_loc = m_cMsgTree.InsertItem(_T("Location:"),m_dMsgTree.mt_chassis,TVI_LAST);
	m_dMsgTree.mt_ch_vel = m_cMsgTree.InsertItem(_T("Velocity:"),m_dMsgTree.mt_chassis,TVI_LAST);
	m_dMsgTree.mt_camera = m_cMsgTree.InsertItem(_T("Camera"),m_dMsgTree.mt_state,TVI_LAST);
	m_dMsgTree.mt_ca_fov = m_cMsgTree.InsertItem(_T("FOV:"),m_dMsgTree.mt_camera,TVI_LAST);
	m_dMsgTree.mt_ca_rot = m_cMsgTree.InsertItem(_T("Rotation:"),m_dMsgTree.mt_camera,TVI_LAST);
	m_dMsgTree.mt_ca_vel = m_cMsgTree.InsertItem(_T("Velocity:"),m_dMsgTree.mt_camera,TVI_LAST);
	m_dMsgTree.mt_light = m_cMsgTree.InsertItem(_T("Light:"),m_dMsgTree.mt_state,TVI_LAST);
	m_dMsgTree.mt_battery = m_cMsgTree.InsertItem(_T("Battery:"),m_dMsgTree.mt_state,TVI_LAST);
	m_dMsgTree.mt_sonar = m_cMsgTree.InsertItem(_T("Sonar"),0,TVI_LAST);
	m_dMsgTree.mt_so_count = 0;
	m_dMsgTree.mt_sonars = NULL;
	m_dMsgTree.mt_laser = m_cMsgTree.InsertItem(_T("Laser"),0,TVI_LAST);
	m_dMsgTree.mt_ls_count = 0;
	m_dMsgTree.mt_ls_data = NULL;
	m_dMsgTree.mt_other = m_cMsgTree.InsertItem(_T("Other"),0,TVI_LAST);
	m_cMsgTree.Expand(m_dMsgTree.mt_state,TVE_EXPAND);

	m_cmdSocket = new CCmdSocket(this);
	if (!m_cmdSocket->Create()) {
		MessageBox("Can't create command socket","Socket",MB_OK);
		return TRUE;
	}
	if (!m_cmdSocket->Connect(m_parent->m_cHost,m_parent->m_cPort)) {
		MessageBox("Can't connect to UT server","Connection",MB_OK);
		m_cmdSocket->Close();
		return TRUE;
	}
	m_cmdFile = new CSocketFile(m_cmdSocket);
	m_arIn = new CArchive(m_cmdFile, CArchive::load);
	m_arOut = new CArchive(m_cmdFile, CArchive::store);
	
	if (!m_parent->m_remote) {
		// Remote mode
		if (m_arOut) {
			CString cmd;
			cmd.Format("INIT {ClassName USARBot.%s} {Location %s}\r\n",
				       m_parent->m_model, m_parent->m_position);
			try {
				m_arOut->WriteString(cmd);
				m_arOut->Flush();
			}catch (CException* e) {
				e->Delete();
				MessageBox("Cannot write data!","Error",MB_OK|MB_ICONSTOP);
				//exit(1);
			}
		}
		m_pFrameData = (FrameData*)malloc(sizeof(FrameData));
		if (m_pFrameData==NULL) {
			AfxMessageBox(IDS_MEM_ERROR,MB_OK|MB_ICONASTERISK);
			return TRUE;
		}
		ZeroMemory(m_pFrameData,sizeof(FrameData));
		m_imgHandle.data = m_pFrameData->data;
		m_imgHandle.datalen = sizeof(m_pFrameData->data);

		m_videoSocket = new CVideoSocket(this);
		if (!m_videoSocket->Create()) {
			MessageBox("Can't create video socket","Socket",MB_OK);
			return TRUE;
		}
		if (!m_videoSocket->Connect(m_parent->m_vHost,m_parent->m_vPort)) {
			if (GetLastError()!=WSAEWOULDBLOCK) {
				MessageBox("Can't connect to image server","Connection",MB_OK);
				m_videoSocket->Close();
				return TRUE;
			}
		}
		m_videoSocket->AsyncSelect(FD_READ|FD_CLOSE);
	} else {
		// Local mode
		CWnd* ut = UTWND;
		if (ut!=NULL) {
			ut->SendMessage(WM_CLOSE);
			AfxMessageBox("A Runing UT Client Is Killed!", MB_OK|MB_ICONASTERISK);
		}
		if (!LoadUT()) return TRUE;
		GetpfFrameData();
		if (m_pfFrameData==NULL) return TRUE;
		m_pFrameData = m_pfFrameData();
		RECT posW,posC;
		m_utclient->GetWindowRect(&posW);
		m_utclient->GetClientRect(&posC);
		m_imgWidth = m_parent->m_width;
		m_imgHeight = m_parent->m_height;
		m_UTCOffsetX =  posW.right - posW.left - posC.right;
		m_UTCOffsetY = posW.bottom - posW.top - posC.bottom;
		Sleep(5000);
		m_utclient->SetWindowPos(GetNextWindow(GW_HWNDPREV),
			                     posW.left, posW.top,
								 posW.right - posW.left, posW.bottom - posW.top,
								 SWP_FRAMECHANGED|SWP_NOACTIVATE);
		SetForegroundWindow();
		//AfxMessageBox(IDS_SET_UTC,MB_OK|MB_ICONINFORMATION);
		if (m_arOut) {
			CString cmd;
			cmd.Format("INIT {ClassName USARBot.%s} {Location %s}\r\n",
				       m_parent->m_model, m_parent->m_position);
			try {
				m_arOut->WriteString(cmd);
				m_arOut->Flush();
			}catch (CException* e) {
				e->Delete();
				MessageBox("Cannot write data!","Error",MB_OK|MB_ICONSTOP);
				//exit(1);
			}
		}
		CInfoDlg * info = new CInfoDlg();
		info->DoModal();
		delete info;
		m_showUT.EnableWindow();
		ShowUTC(false);
		SetTimer(IDC_TIMER,(int)(1000/m_parent->m_fps),NULL);
	}

	memset(&m_bmpInfo,0,sizeof(m_bmpInfo));    
	m_bmpInfo.bmiHeader.biSize = sizeof(m_bmpInfo.bmiHeader);
    m_bmpInfo.bmiHeader.biWidth = 0;
    m_bmpInfo.bmiHeader.biHeight = 0;
    m_bmpInfo.bmiHeader.biPlanes = 1;
    m_bmpInfo.bmiHeader.biBitCount = 24;
    m_bmpInfo.bmiHeader.biCompression = BI_RGB;
    m_bmpInfo.bmiHeader.biSizeImage = 0;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CControlDlg::ProcessVideoData()
{
	int count;
	int size;

	if (m_videoState<2) {
#ifdef _DEBUG
		if (log==NULL) log=fopen("log.txt","w");
		fprintf(log,"::Begin Frame T:%d\n",clock());
#endif
		if (m_videoState==0) {
			m_videoSocket->Receive(&m_imgType,1);
			m_videoState++;
		} else {
			m_videoSocket->Receive(&m_imgHandle.filelen,sizeof(UINT));
			m_imgHandle.filelen = ntohl(m_imgHandle.filelen);
			m_pFrameData->size = m_imgHandle.filelen;

			((CButton *)GetDlgItem(IDC_UPDATE))->SetCheck(1);
			UpdateData(FALSE);
			m_pData = m_pFrameData->data;
			m_nBytes = 0;
			m_videoState++;
		}
	}
	else if (m_imgType==0 && m_videoState<4) {
		// For RAW data
		if (m_videoState==2) {
			m_videoSocket->Receive(&m_pFrameData->width,sizeof(USHORT));
			m_pFrameData->width = ntohs(m_pFrameData->width);
			m_videoState++;
		}
		if (m_videoState==3) {
			m_videoSocket->Receive(&m_pFrameData->height,sizeof(USHORT));
			m_pFrameData->height = ntohs(m_pFrameData->height);
			m_pFrameData->size = m_imgHandle.datalen - 2*sizeof(USHORT);
			m_videoState++;

#ifdef _DEBUG
			if (log==NULL) log=fopen("log.txt","w");
				fprintf(log,"Head W:%d H:%d S:%d T:%d\n",m_pFrameData->width,m_pFrameData->height,m_pFrameData->size,clock());
#endif
		}
	}
	else {
		size = m_pFrameData->size - (m_pData - m_pFrameData->data);
		size = size>BLOCK?BLOCK:size;
#ifdef _DEBUG
		fprintf(log,"Data Read:%d",size);
#endif
		count = m_videoSocket->Receive(m_pData,size);
		if (count== SOCKET_ERROR) {
#ifdef _DEBUG
			fprintf(log,"<Error:%d>\n",GetLastError());
#endif
		}
		else {
			m_pData += count;
#ifdef _DEBUG
			fprintf(log," Get:%d T:%d\n",count,clock());
#endif
			if ((UINT)(m_pData-m_pFrameData->data)>=m_pFrameData->size) {
				m_videoSocket->AsyncSelect(FD_WRITE|FD_CLOSE);
#ifdef _DEBUG
				fprintf(log,"::End Frame T:%d\n",clock());
#endif
				if (m_lastClock==0) m_lastClock = clock();
				if (++m_frameCount>=10 || clock()-m_lastClock>CLOCKS_PER_SEC) {
					m_fps = (float)m_frameCount*CLOCKS_PER_SEC/(clock()-m_lastClock);
					m_lastClock = clock();
					m_frameCount = 0;
				}
				
				if (m_imgType>=1 && m_imgType<=5) { // JPEG Format
					int flag = 0;
					if (m_imgType==1) flag = JPEG_QUALITYSUPERB;
					else if (m_imgType==2) flag = JPEG_QUALITYGOOD;
					else if (m_imgType==3) flag = JPEG_QUALITYNORMAL;
					else if (m_imgType==4) flag = JPEG_QUALITYAVERAGE;
					else if (m_imgType==5) flag = JPEG_QUALITYBAD;
					FIBITMAP *bitmap = FreeImage_LoadFromMem(FIF_JPEG, &m_imgHandle, flag);
					m_pFrameData->width = FreeImage_GetWidth(bitmap);
					m_pFrameData->height = FreeImage_GetHeight(bitmap);
					int pitch = m_pFrameData->width*3;
					if (pitch%sizeof(DWORD))
						pitch += sizeof(DWORD) - (pitch%sizeof(DWORD));
					m_pFrameData->size = pitch * m_pFrameData->height;
					FreeImage_ConvertToRawBits(m_pFrameData->data, bitmap, pitch,
											   24, 0xff0000, 0x00ff00, 0x0000ff, true);
					FreeImage_Unload(bitmap);
				}
				
				UpdateVideo();
				Sleep(10);
				((CButton *)GetDlgItem(IDC_UPDATE))->SetCheck(0);
				if (m_width!=m_pFrameData->width || m_height!=m_pFrameData->height) {
					m_width = m_pFrameData->width;
					m_height = m_pFrameData->height;
				}
				UpdateData(FALSE);
				m_videoState = 0;
				return;
			}
		}
	}
	Sleep(20);
	m_videoSocket->AsyncSelect(FD_READ|FD_CLOSE);
}

void CControlDlg::ProcessMsgData()
{
	CString str;
	int process=1;
	//int tmp;

	do {
		m_arIn->ReadString(str);

		//m_msgList.InsertString(0,str);
		//if (m_msgList.GetCount()>=MAX_MSGS) 
		//	m_msgList.DeleteString(MAX_MSGS);
		
		UpdateMsgTree(str);
		
		//tmp = str.GetLength()*6;
		//if (tmp>maxMsgLen) {
		//	maxMsgLen = tmp;
		//	m_msgList.SetHorizontalExtent(tmp);
		//}
		Sleep(1);
	}while(!m_arIn->IsBufferEmpty());
	UpdateData(false);
}

void CControlDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (m_parent->m_remote) {
		free(m_pFrameData);
		KillTimer(IDC_TIMER);
		if (UTWND!=NULL) {
			if (AfxMessageBox(IDS_CLOSE_UTC,MB_YESNO)==IDYES)
				m_utclient->SendMessage(WM_CLOSE);
		}
	}
	if (m_hookDLL!=NULL)
		FreeLibrary(m_hookDLL);

	if (m_arIn) {
		delete m_arIn;
		m_arIn=NULL;
	}
	if (m_arOut) {
		delete m_arOut;
		m_arOut=NULL;
	}
	if (m_cmdFile) {
		delete m_cmdFile;
		m_cmdFile=NULL;
	}
	if (m_cmdSocket) {
		m_cmdSocket->Close();
		delete m_cmdSocket;
		m_cmdSocket = NULL;
	}
	if (m_videoSocket) {
		m_videoSocket->Close();
		delete m_videoSocket;
		m_videoSocket = NULL;
	}

	m_cMsgTree.DeleteAllItems();
	if (m_dMsgTree.mt_sonars!=NULL)
		free(m_dMsgTree.mt_sonars);
	if (m_dMsgTree.mt_ls_data!=NULL)
		free(m_dMsgTree.mt_ls_data);

	CDialog::OnClose();
}

void CControlDlg::UpdateVideo()
{
	/*
	////////////////////////////////////////////////////
	// Save to file
	BITMAPINFO bi;
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = m_FrameData->width;
    bi.bmiHeader.biHeight = m_FrameData->height;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 24;
    bi.bmiHeader.biCompression = BI_RGB;
    bi.bmiHeader.biSizeImage = m_FrameData->size;
    bi.bmiHeader.biXPelsPerMeter = 0;
    bi.bmiHeader.biYPelsPerMeter = 0;
    bi.bmiHeader.biClrUsed = 0;
    bi.bmiHeader.biClrImportant = 0;

    BITMAPFILEHEADER bmfh;
    bmfh.bfType = 'MB';
    bmfh.bfSize = sizeof(bmfh) + sizeof(BITMAPINFOHEADER) + bi.bmiHeader.biSizeImage;
    bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
    bmfh.bfOffBits = sizeof(bmfh) + sizeof(BITMAPINFOHEADER);
	
	FILE* f = fopen("test.bmp", "wb");	
	fwrite(reinterpret_cast<void*>(&bmfh), sizeof(bmfh), 1, f);
	fwrite(reinterpret_cast<void*>(&(bi.bmiHeader)), sizeof(BITMAPINFOHEADER), 1, f);
	fwrite(reinterpret_cast<void*>(m_FrameData->data), sizeof(BYTE), bi.bmiHeader.biSizeImage, f);
	fclose(f);
	*/
	
	if (m_utclient && !IsIconic() && m_utclient->IsIconic()) {
		::OpenIcon(m_utclient->m_hWnd);
		return;
	}
	////////////////////////
	// Clear Client Area
    if (m_bmpInfo.bmiHeader.biSizeImage!=m_pFrameData->size) {
		GetDlgItem(IDC_VIDEO)->GetWindowRect(&m_bmpRec);
		ScreenToClient(&m_bmpRec);
		int rWidth = m_bmpRec.right-m_bmpRec.left-2;
		int rHeight = m_bmpRec.bottom-m_bmpRec.top-2;
		int append = (rWidth*3)%sizeof(DWORD);
		append = append?sizeof(DWORD)-append:0;
	    m_bmpInfo.bmiHeader.biWidth = rWidth;
		m_bmpInfo.bmiHeader.biHeight = rHeight;
	    m_bmpInfo.bmiHeader.biSizeImage = (rWidth*3+append)*rHeight;

		PBYTE tmp = (PBYTE)malloc(m_bmpInfo.bmiHeader.biSizeImage);
		memset(tmp,0xe9,m_bmpInfo.bmiHeader.biSizeImage);
		SetDIBitsToDevice(GetDC()->m_hDC,m_bmpRec.left+1,m_bmpRec.top+1,m_bmpInfo.bmiHeader.biWidth,m_bmpInfo.bmiHeader.biHeight,0,0,0,m_bmpInfo.bmiHeader.biHeight,tmp,&m_bmpInfo,DIB_RGB_COLORS);
		free(tmp);
		m_imgWidth = m_bmpRec.right-m_bmpRec.left;
		m_imgWidth = m_pFrameData->width>m_imgWidth?m_imgWidth:m_pFrameData->width;
		m_imgHeight = m_bmpRec.bottom-m_bmpRec.top;
		m_imgHeight = m_pFrameData->height>m_imgHeight?m_imgHeight:m_pFrameData->height;
		m_bmpRec.left = (m_bmpRec.right+m_bmpRec.left-m_imgWidth)/2;
		m_bmpRec.top = (m_bmpRec.bottom+m_bmpRec.top-m_imgHeight)/2;
	}

	m_bmpInfo.bmiHeader.biWidth = m_pFrameData->width;
    m_bmpInfo.bmiHeader.biHeight = m_pFrameData->height;
    m_bmpInfo.bmiHeader.biSizeImage = m_pFrameData->size;
	CDC* pDC = GetDC();
	if (pDC) {
		SetDIBitsToDevice(pDC->m_hDC,m_bmpRec.left,m_bmpRec.top,m_imgWidth,m_imgHeight,0,0,0,m_imgHeight,m_pFrameData->data,&m_bmpInfo,DIB_RGB_COLORS);
		ReleaseDC(pDC);
	}
}



void CControlDlg::ShowUTC(BOOL show)
{
	m_show = show;
	if (!show) {
		HDC hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
		m_utclient->SetWindowPos(this,
			  				     GetDeviceCaps(hScrDC, HORZRES)-10,
								 GetDeviceCaps(hScrDC, VERTRES)-10,
								 m_UTCOffsetX+m_imgWidth, m_UTCOffsetY+m_imgHeight,
								 SWP_FRAMECHANGED|SWP_NOACTIVATE);
		DeleteDC(hScrDC);
	}
	else {
		RECT posW;
		GetWindowRect(&posW);
		m_utclient->SetWindowPos(this,
			                     posW.left-m_UTCOffsetX-m_imgWidth, posW.top,
								 m_UTCOffsetX+m_imgWidth, m_UTCOffsetY+m_imgHeight,
								 SWP_FRAMECHANGED|SWP_NOACTIVATE);
	}
}

void CControlDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent==IDC_TIMER) {
		// Just in case
		if (UTWND==NULL) {
			KillTimer(IDC_TIMER);
			CString tmp;
			tmp.Format(IDS_CANT_CATCH_UTC,". Server stopped");
			AfxMessageBox(tmp,MB_OK|MB_ICONSTOP);
		}
		if (m_pFrameData==NULL)
			m_pFrameData = m_pfFrameData();
		if (m_pFrameData /*&& m_pFrameData->state!=FRAME_PENDING*/) {
			if (m_lastClock==0) m_lastClock = clock();
			if (++m_frameCount>=10 || clock()-m_lastClock>CLOCKS_PER_SEC) {
				m_fps = (float)m_frameCount*CLOCKS_PER_SEC/(clock()-m_lastClock);
				m_lastClock = clock();
				m_frameCount = 0;
			}
			if (m_width!=m_pFrameData->width || m_height!=m_pFrameData->height) {
				m_width = m_pFrameData->width;
				m_height = m_pFrameData->height;
			}
			((CButton *)GetDlgItem(IDC_UPDATE))->SetCheck(1);
			UpdateData(FALSE);
			UpdateVideo();
			Sleep(2);
			((CButton *)GetDlgItem(IDC_UPDATE))->SetCheck(0);
			UpdateData(FALSE);
			m_pFrameData->sequence += 1;
		}
	}	
	CDialog::OnTimer(nIDEvent);
}

BOOL CControlDlg::LoadUT()
{
	// Load UTClient
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	CHAR szFullExe[1024] = "\0";
	CHAR szMesg[1024]="\0";
	PCHAR pszFileExe = NULL;
    
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);

	SearchPath(NULL, _utPath, "exe", arrayof(szFullExe), szFullExe, &pszFileExe);
    if (!DetourCreateProcessWithDll(szFullExe[0] ? szFullExe : NULL,
		                            UTCCMD, NULL, NULL, TRUE,
                                    CREATE_DEFAULT_ERROR_MODE, NULL, NULL,
                                    &si, &pi, _dllPath, NULL)) {
		int errno;
		errno = GetLastError();
		if (errno==2) {
			AfxMessageBox( IDS_OPEN_UT2003, MB_OK|MB_ICONSTOP );
			errno = 0;
			CFileDialog * pcf = new CFileDialog(true,".exe","ut2004",
				                                OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
												"Executable Files (*.exe)|*.exe");
			pcf->DoModal();
			CString utPath = pcf->GetPathName();
			CString file = pcf->GetFileName();
			delete pcf;
			utPath.Replace("\\","\\\\");
			strncpy(_utPath,(LPCSTR)utPath,512);
			utPath.Replace((LPCSTR)file,"Hook.dll");
			strncpy(_dllPath,(LPCSTR)utPath,512);
			if (!DetourCreateProcessWithDll(_utPath,
		                            UTCCMD, NULL, NULL, TRUE,
                                    CREATE_DEFAULT_ERROR_MODE, NULL, NULL,
                                    &si, &pi, _dllPath, NULL))
				errno = GetLastError();
		}
		if (errno) {
			CString strMsg;
			strMsg.Format( IDS_HOOK_ERROR, errno );
			AfxMessageBox( strMsg, MB_OK|MB_ICONSTOP );
			return false;
		}
    }

	int time=0;
	while (time<60000) {
		Sleep(100);
		if ((m_utclient=FindWindow(NULL,UTCNAME))!=NULL)
			break;
		time+=100;
	}
	if (m_utclient==NULL) {
        CString strMsg;
		strMsg.Format( IDS_CANT_CATCH_UTC, UTCNAME );
		AfxMessageBox( strMsg, MB_OK|MB_ICONSTOP );
		return false;
	}
	
	return true;
}

void CControlDlg::GetpfFrameData()
{
	CString strMsg;

	if ((m_hookDLL = LoadLibrary(_dllPath))==NULL) {
		strMsg.Format(IDS_DLL_LOAD_ERROR,_dllPath,GetLastError());
		AfxMessageBox( strMsg, MB_OK|MB_ICONSTOP );
		return;
	}
	if ((m_pfFrameData = (pfFrameData)GetProcAddress(m_hookDLL, "getFrameData"))==NULL) {
		strMsg.Format(IDS_DLL_PROCADDR_ERROR,"getFrameData",GetLastError());
		AfxMessageBox( strMsg, MB_OK|MB_ICONSTOP );
		FreeLibrary(m_hookDLL);
	}
}

void CControlDlg::OnShowut() 
{
	// TODO: Add your control notification handler code here
	if (m_parent->m_remote) {
		m_showUT.SetWindowText(m_show?"Show UT":"Hide UT");
		ShowUTC(!m_show);	
	}
}

void CControlDlg::OnCup() 
{
	// TODO: Add your control notification handler code here
	m_drMode = DR_FORWARD;
	Drive();
}

void CControlDlg::OnCdown() 
{
	// TODO: Add your control notification handler code here
	m_drMode = DR_BACKWARD;
	Drive();
}

void CControlDlg::OnCleft() 
{
	// TODO: Add your control notification handler code here
	m_drMode = DR_LEFT;
	Drive();
}

void CControlDlg::OnCright() 
{
	// TODO: Add your control notification handler code here
	m_drMode = DR_RIGHT;
	Drive();
}

void CControlDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	m_drMode = DR_STOP;
	Drive();
}
void CControlDlg::OnSpeedUp() 
{
	// TODO: Add your control notification handler code here
	m_speed += SPEED_STEP;
	m_speed = m_speed>SPEED_MAX?SPEED_MAX:m_speed;
	Drive();
}

void CControlDlg::OnSpeedDown() 
{
	// TODO: Add your control notification handler code here
	m_speed -= SPEED_STEP;
	m_speed = m_speed<SPEED_MIN?SPEED_MIN:m_speed;
	Drive();
}

void CControlDlg::Drive()
{
	CString cmd;
	if (m_arOut==NULL) return;
	switch (m_drMode){
		case DR_FORWARD:
			if(!m_speed)m_speed=0.5;
			cmd.Format("DRIVE {Left %f} {Right %f}\r\n",m_speed,m_speed);
			break;
		case DR_BACKWARD:
			if(!m_speed)m_speed=0.5;
			cmd.Format("DRIVE {Left -%f} {Right -%f}\r\n",m_speed,m_speed);
			break;
		case DR_LEFT:
			if(!m_speed)m_speed=0.5;
			cmd.Format("DRIVE {Left -%f} {Right %f}\r\n",m_speed,m_speed);
			break;
		case DR_RIGHT:
			if(!m_speed)m_speed=0.5;
			cmd.Format("DRIVE {Left %f} {Right -%f}\r\n",m_speed,m_speed);
			break;
		case DR_STOP:
			cmd = "DRIVE {Left 0} {Right 0}\r\n";
			break;

//===========================================================================================
		case DR_TRANSROT:
			cmd.Format("DRIVE {Left %f} {Right %f}\r\n",m_speed-rot_speed,m_speed+rot_speed);
			break;
//===========================================================================================

		default:
			cmd = "";
	}
	m_arOut->WriteString(cmd);
	m_arOut->Flush();
}

void CControlDlg::OnVleft() 
{
	// TODO: Add your control notification handler code here
	//m_pan -= PAN_STEP;
	//m_pan = m_pan<PAN_MIN?PAN_MIN:m_pan;
	m_pan = -PAN_STEP;
	m_tilt = 0;
	Camera();
}

void CControlDlg::OnVright() 
{
	// TODO: Add your control notification handler code here
	//m_pan += PAN_STEP;
	//m_pan = m_pan<PAN_MIN?PAN_MIN:m_pan;
	m_pan = PAN_STEP;
	m_tilt = 0;
	Camera();
}

void CControlDlg::OnVup() 
{
	// TODO: Add your control notification handler code here
	//m_tilt += TILT_STEP;
	//m_tilt = m_tilt<TILT_MIN?TILT_MIN:m_tilt;
	m_tilt = TILT_STEP;
	m_pan = 0;
	Camera();
}

void CControlDlg::OnVdown() 
{
	// TODO: Add your control notification handler code here
	//m_tilt -= TILT_STEP;
	//m_tilt = m_tilt<TILT_MIN?TILT_MIN:m_tilt;
	m_tilt = -TILT_STEP;
	m_pan = 0;
	Camera();
}

void CControlDlg::OnZoomIn() 
{
	// TODO: Add your control notification handler code here
	m_zoom -= ZOOM_STEP;
	m_zoom = m_zoom<ZOOM_MIN?ZOOM_MIN:m_zoom;
	m_pan = 0;
	m_tilt = 0;
	Camera();
}

void CControlDlg::OnZoomOut() 
{
	// TODO: Add your control notification handler code here
	m_zoom += ZOOM_STEP;
	m_zoom = m_zoom>ZOOM_MAX?ZOOM_MAX:m_zoom;
	m_pan = 0;
	m_tilt = 0;
	Camera();
}

void CControlDlg::Camera()
{
	CString cmd;

	if (m_arOut==NULL) return;
	cmd.Format("CAMERA {Rotation 0,%f,%f} {Zoom %f}\r\n",m_tilt,m_pan,m_zoom);
	m_arOut->WriteString(cmd);
	m_arOut->Flush();
}

#define UU_DEG 0.00549325f 
// 360/65535

void CControlDlg::UpdateMsgTree(CString str)
//==========================================================================================================
		//Also updates global variables containing sensor and state data
//==========================================================================================================

{
	if (str.Find("STA",0)==0) {
		CString tmp;
		int n,count=3;
		int int3[3];
		float float3[3];

		tmp = "Time:"+CMessageParser::GetString("Time",str);
		m_cMsgTree.SetItemText(m_dMsgTree.mt_time,(LPCSTR)tmp);
		
		CMessageParser::GetInts("Camera",str,',',&count,int3);
		int3[0] = (int)(int3[0]*UU_DEG);
		int3[1] = (int)(int3[1]*UU_DEG);
		tmp.Format("Rotation(Deg): Pitch=%d Yaw=%d",int3[0],int3[1]);
		m_cMsgTree.SetItemText(m_dMsgTree.mt_ca_rot,(LPCSTR)tmp);
		
		n = CMessageParser::GetInt("Zoom",str);
		tmp.Format("FOV(Deg):%d",n);
		m_cMsgTree.SetItemText(m_dMsgTree.mt_ca_fov,(LPCSTR)tmp);

		CMessageParser::GetFloats("CameraVel",str,',',&count,float3);
		float3[0]*=UU_DEG;
		float3[1]*=UU_DEG;
		tmp.Format("Velocity(Deg/s): TiltSpeed=%4.2f PanSpeed=%4.2f",float3[0],float3[1]);
		m_cMsgTree.SetItemText(m_dMsgTree.mt_ca_vel,(LPCSTR)tmp);

	//==========================================================================================================
		//The following code has been partially "commented" and copied within a different "if" case, as it was incorrectly placed.
		//-->The Location and Orientation data are not contained in the STA (State) message from GameBots
		//-->Nor is the Camera, but for the time being it causes no damage to leave it here

		/*
		
		CMessageParser::GetInts("Attitude",str,',',&count,int3);
		int3[0] = (int)(int3[0]*UU_DEG);
		int3[1] = (int)(int3[1]*UU_DEG);
		int3[2] = (int)(int3[2]*UU_DEG);
		tmp.Format("Rotation(Deg): Pitch=%d Yaw=%d Roll=%d",int3[0],int3[1],int3[2]);
		m_cMsgTree.SetItemText(m_dMsgTree.mt_ch_rot,(LPCSTR)tmp);

		CMessageParser::GetFloats("Location",str,',',&count,float3);
		tmp.Format("Location(UU): X=%6.2f Y=%6.2f Z=%6.2f",float3[0],float3[1],float3[2]);
		m_cMsgTree.SetItemText(m_dMsgTree.mt_ch_loc,(LPCSTR)tmp);
		
		CMessageParser::GetFloats("Velocity",str,',',&count,float3);
		tmp.Format("Velocity(UU/s): X=%6.2f Y=%5.2f Z=%5.2f",float3[0],float3[1],float3[2]);
		m_cMsgTree.SetItemText(m_dMsgTree.mt_ch_vel,(LPCSTR)tmp);

		*/

		tmp.Format("Light: On=%s Intensity=%d",(LPCSTR)CMessageParser::GetString("LightToggle",str),CMessageParser::GetInt("LightIntensity",str));
		m_cMsgTree.SetItemText(m_dMsgTree.mt_light,(LPCSTR)tmp);

		tmp.Format("Battery(%%):%d",(int)CMessageParser::GetFloat("Battery",str));
		m_cMsgTree.SetItemText(m_dMsgTree.mt_battery,(LPCSTR)tmp);

		/*
		tmp = "Chassis: " +
			  m_cMsgTree.GetItemText(m_dMsgTree.mt_ch_rot) + " " +
			  m_cMsgTree.GetItemText(m_dMsgTree.mt_ch_loc) + " " +
			  m_cMsgTree.GetItemText(m_dMsgTree.mt_ch_vel);
		m_cMsgTree.SetItemText(m_dMsgTree.mt_chassis,(LPCSTR)tmp);
		*/

		//TODO: Find the actual GameBots message containing the Camera data and use it to update the message tree
		tmp = "Camera: " +
			  m_cMsgTree.GetItemText(m_dMsgTree.mt_ca_fov) + " " +
			  m_cMsgTree.GetItemText(m_dMsgTree.mt_ca_rot) + " " +
			  m_cMsgTree.GetItemText(m_dMsgTree.mt_ca_vel);
		m_cMsgTree.SetItemText(m_dMsgTree.mt_camera,(LPCSTR)tmp);
	}
	else if (str.Find("{Type Sonar}",0)>0) {
		CString tmp[32], sonar="Sonar:";
		int pos1=0, pos2=0, count=0;
		while (pos1>=0 && count<32) {
			tmp[count++] = CMessageParser::GetString("Name",str, pos1, pos2);
			pos1 = pos2;
		}
		if (pos1<0) count--;
		if (m_dMsgTree.mt_sonars==NULL) {
			m_dMsgTree.mt_so_count = count;
			m_dMsgTree.mt_sonars = (HTREEITEM *)malloc(sizeof(HTREEITEM)*count);
			for (int i=0;i<count;i++) 
				m_dMsgTree.mt_sonars[i] = m_cMsgTree.InsertItem(_T("Name:"),m_dMsgTree.mt_sonar,TVI_LAST);
		}
		for (int i=0;i<count;i++) {

//=========================================================================================================
			//Stores the sonar data (numeric value) to a global variable

			sonar_data[i]=CMessageParser::GetFloat("Range",tmp[i]);

//=========================================================================================================

			tmp[i].Replace("Name ","");
			tmp[i].Replace("Range ",":");
			sonar += tmp[i] + " ";
			m_cMsgTree.SetItemText(m_dMsgTree.mt_sonars[i],(LPCSTR)tmp[i]);
			
		}
		m_cMsgTree.SetItemText(m_dMsgTree.mt_sonar,(LPCSTR)sonar);
	}
	else if (str.Find("{Type RangeScanner}",0)>0) {
		CString dataStr = "Laser(";
		dataStr += CMessageParser::GetString("Name",str) +"):" + CMessageParser::GetString("Range",str);
		m_cMsgTree.SetItemText(m_dMsgTree.mt_laser,(LPCSTR)dataStr);

//=================================================================================================================
		//MODIFICATION INTRODUCED: Will save the laser data to a global variable instead of as a temporary float array

		float *tmp=laser_data;

//=================================================================================================================

		//float tmp[256];
		int count = 181; //Modified from 256 to 181, which is the actual number of elements in the array
		CMessageParser::GetFloats("Range",str,',',&count,tmp);
		int lines = count/8;
		int lastLn = count%8;
		if (lastLn) lines+=1;
		if (m_dMsgTree.mt_ls_data==NULL) {
			m_dMsgTree.mt_ls_count = lines;
			m_dMsgTree.mt_ls_data = (HTREEITEM *)malloc(sizeof(HTREEITEM)*lines);
			for (int i=0;i<lines;i++) 
				m_dMsgTree.mt_ls_data[i] = m_cMsgTree.InsertItem(_T("Data:"),m_dMsgTree.mt_laser,TVI_LAST);
		}
		lines-=1;
		for (int i=0;i<lines;i++) {
			dataStr.Format("Data: %6.2f %6.2f %6.2f %6.2f  %6.2f %6.2f %6.2f %6.2f",
				   tmp[i*8],tmp[i*8+1],tmp[i*8+2],tmp[i*8+3],tmp[i*8+4],tmp[i*8+5],tmp[i*8+6],tmp[i*8+7]);
			m_cMsgTree.SetItemText(m_dMsgTree.mt_ls_data[i],(LPCSTR)dataStr);
		}
		if (lines>=0) {
			if (lastLn==0) lastLn = 8;
			CString data;
			dataStr = "Data: ";
			for (int i=0;i<lastLn;i++) {
				data.Format("%6.2f ",tmp[lines*8+i]);
				dataStr += data;
			}
			m_cMsgTree.SetItemText(m_dMsgTree.mt_ls_data[lines],(LPCSTR)dataStr);
		}

		
	}
//==========================================================================================================
	//Added case for Ground Truth --> Location and Orientation

	else if (str.Find("{Type GroundTruth}",0)>0) {
		CString tmp;
		int n,count=3;
		int int3[3];
		float float3[3];

		CMessageParser::GetFloats("Location",str,',',&count,float3);
		tmp.Format("Location: X=%6.2f Y=%6.2f Z=%6.2f",float3[0],float3[1],float3[2]);
		m_cMsgTree.SetItemText(m_dMsgTree.mt_ch_loc,(LPCSTR)tmp);		

		//Saves the robot's location to a global variable
		location_data[0]=float3[0];
		location_data[1]=float3[1];
		location_data[2]=float3[2]; //No need to convert data from Unreal Units to metres (GroundTruth is already in metres)
		//gps_data //TODO: Convert metres from origin to gps coordinates

		CMessageParser::GetFloats("Orientation",str,',',&count,float3);
		float3[0] = 6.283185307-float3[0]; //Conversion to right-hand angle criteria
		float3[1] = 6.283185307-float3[1];
		float3[2] = 6.283185307-float3[2];
		int3[0] = (int)(float3[0]*180/3.141592654); //Conversion to degrees
		int3[1] = (int)(float3[1]*180/3.141592654);
		int3[2] = (int)(float3[2]*180/3.141592654);
		tmp.Format("Rotation(Deg): Pitch=%d Yaw=%d Roll=%d",int3[0],int3[1],int3[2]);
		m_cMsgTree.SetItemText(m_dMsgTree.mt_ch_rot,(LPCSTR)tmp);

		//Saves the robot's orientation to a global variable
		orientation_data=float3[2];

		//Writes the Rotation and Location on the MessageTree
		tmp = "Chassis: " +
			  m_cMsgTree.GetItemText(m_dMsgTree.mt_ch_rot) + " " +
			  m_cMsgTree.GetItemText(m_dMsgTree.mt_ch_loc) + " " +
			  m_cMsgTree.GetItemText(m_dMsgTree.mt_ch_vel);
		m_cMsgTree.SetItemText(m_dMsgTree.mt_chassis,(LPCSTR)tmp);
		
	}
//==========================================================================================================
	else {
		CString tmp = "Other: " + str;
		m_cMsgTree.SetItemText(m_dMsgTree.mt_other,(LPCSTR)tmp);
	}

}

void CControlDlg::OnLight() 
{
	// TODO: Add your control notification handler code here
	if (m_arOut==NULL) return;
	CString str;
	m_light.GetWindowText(str);
	if (str=="Turn On") {
		m_light.SetWindowText("Turn Off");
		m_arOut->WriteString("DRIVE {Light True}\r\n");
	} else {
		m_light.SetWindowText("Turn On");
		m_arOut->WriteString("DRIVE {Light False}\r\n");
	}
	m_arOut->Flush();
}



//========================================================================================================================

//Added functions for Corba-Based and Enhanced UI control


void CControlDlg::SetTransRot(float v,float w)
{
	if(v&&(v==w||v==-w))w=w*1.1; //Avoids sending a ZERO value to a motor (leaving it loose when it is meant to be blocked). 
	m_speed=v;
	//Constrain speed according to maximum and minimum (only if seen fit)
	//m_speed = m_speed>SPEED_MAX?SPEED_MAX:m_speed;
	//m_speed = m_speed<SPEED_MIN?SPEED_MIN:m_speed;
	rot_speed=w;
	m_drMode=DR_TRANSROT;
	Drive();
}


void CControlDlg::OnEnChangeVel()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString vel_str, rot_str;
	float v,w;
	m_vel.GetWindowText(vel_str);
	v=(float)strtod(vel_str,NULL);
	m_rot.GetWindowText(rot_str);
	w=(float)strtod(rot_str,NULL);
	SetTransRot(v,w);

}

void CControlDlg::OnEnChangeRot() //This function is identic to OnEnChangeVel (at least in the first approach)
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString vel_str, rot_str; //Local buffers, large enough to prevent errors with reasonable inputs
	float v,w;
	m_vel.GetWindowText(vel_str);
	v=(float)strtod(vel_str,NULL);
	m_rot.GetWindowText(rot_str);
	w=(float)strtod(rot_str,NULL);
	SetTransRot(v,w);

}
