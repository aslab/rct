#if !defined(AFX_CONTROLDLG_H__917D5561_6084_45E1_A576_2B178677B882__INCLUDED_)
#define AFX_CONTROLDLG_H__917D5561_6084_45E1_A576_2B178677B882__INCLUDED_

#include "VideoSocket.h"	// Added by ClassView
#include "CmdSocket.h"	// Added by ClassView
#include "MessageParser.h"
#include "InfoDlg.h"
#include "FreeImage/FIIO_Mem.h"
#include "afxwin.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ControlDlg.h : header file
//

typedef struct MessageTree_t {
	HTREEITEM mt_time;
	HTREEITEM mt_state;
	  HTREEITEM mt_chassis;
	    HTREEITEM mt_ch_rot;
	    HTREEITEM mt_ch_loc;
	    HTREEITEM mt_ch_vel;
	  HTREEITEM mt_camera;
	    HTREEITEM mt_ca_fov;
	    HTREEITEM mt_ca_rot;
		HTREEITEM mt_ca_vel;
	  HTREEITEM mt_light;
	  HTREEITEM mt_battery;
	HTREEITEM mt_sonar;
	  UINT mt_so_count;
	  HTREEITEM * mt_sonars;
	HTREEITEM mt_laser;
	  UINT mt_ls_count;
	  HTREEITEM * mt_ls_data;
	HTREEITEM mt_other;
} MessageTree;

typedef struct FrameData_t {
	BYTE state;
	BYTE sequence;
	USHORT width;
	USHORT height;
	UINT size;
	BYTE data[640*480*3+1];
} FrameData;

#define FRAME_PENDING 0
#define FRAME_OK 1
#define FRAME_ERROR 2

typedef FrameData * (WINAPI *pfFrameData)(void);

#ifdef _DEBUG
static FILE* log;
#endif

enum {
	DR_STOP,
	DR_FORWARD,
	DR_BACKWARD,
	DR_LEFT,
	DR_RIGHT
	//=======================================================================
	//Extra case for simultaneous translation and rotation movement
	,
	DR_TRANSROT
	//=======================================================================
};
class CSimpleUIDlg;
class CCmdSocket;
class CVideoSocket;
class CMessageParser;

/////////////////////////////////////////////////////////////////////////////
// CControlDlg dialog

class CControlDlg : public CDialog
{
// Construction
public:
	BOOL m_show;
	void UpdateVideo();

	CControlDlg(CWnd* pParent = NULL);   // standard constructor
	void ProcessMsgData();
	void ProcessVideoData();
// Dialog Data
	//{{AFX_DATA(CControlDlg)
	enum { IDD = IDD_CONTROL_DLG };
	CButton	m_light;
	CTreeCtrl	m_cMsgTree;
	CButton	m_showUT;
	UINT	m_width;
	UINT	m_height;
	float	m_fps;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	fiio_mem_handle m_imgHandle;
	BYTE m_imgType;
	clock_t m_lastClock;
	int m_frameCount;
	RECT m_bmpRec;
	BYTE m_videoState;
	CSocketFile * m_cmdFile;
	CArchive * m_arIn;
	CArchive * m_arOut;
	CVideoSocket * m_videoSocket;
	CCmdSocket * m_cmdSocket;
	CSimpleUIDlg * m_parent;
	FrameData * m_pFrameData;
	CWnd* m_utclient;
	HINSTANCE m_hookDLL;
	pfFrameData m_pfFrameData;
	BITMAPINFO m_bmpInfo;
	int m_UTCOffsetX;
	int m_UTCOffsetY;
	BYTE m_drMode; 
	float m_zoom;
	float m_speed;
	float m_pan;
	float m_tilt;
	MessageTree m_dMsgTree;

//=======================================================================================
	float rot_speed; //Additional variable to allow simultaneous translation and rotation
//=======================================================================================

	void UpdateMsgTree(CString str);
	void Camera();
	void Drive();
	void ShowUTC(BOOL show);
	BOOL LoadUT();
	void GetpfFrameData();

	// Generated message map functions
	//{{AFX_MSG(CControlDlg)
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSpeedDown();
	afx_msg void OnSpeedUp();
	afx_msg void OnShowut();
	afx_msg void OnCup();
	afx_msg void OnCdown();
	afx_msg void OnCleft();
	afx_msg void OnCright();
	afx_msg void OnStop();
	afx_msg void OnVleft();
	afx_msg void OnVright();
	afx_msg void OnVup();
	afx_msg void OnVdown();
	afx_msg void OnLight();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_imgHeight;
	int m_imgWidth;
	int m_nBytes;
	LPBYTE m_pData;
public:
	//===============================================================================================

	//Added functions for Corba-based and enhanced UI control

	afx_msg void OnEnChangeVel();
	afx_msg void OnEnChangeRot();
	void SetTransRot(float v,float w);
	

	CEdit m_vel;
	CEdit m_rot;

	//Additional variables to store Sensor Data
	float location_data[3]; //local X,Y,Z in metres
	float orientation_data;
	float gps_data[3]; //GPS coordinates. NOT IN USE FOR THE MOMENT
	float laser_data[181];
	float sonar_data[32];


	//===============================================================================================
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLDLG_H__917D5561_6084_45E1_A576_2B178677B882__INCLUDED_)
