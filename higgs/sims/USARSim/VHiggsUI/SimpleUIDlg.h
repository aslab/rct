// SimpleUIDlg.h : header file
//

#if !defined(AFX_SIMPLEUIDLG_H__366088CF_EBD5_410F_9F70_5FB860F4BD3C__INCLUDED_)
#define AFX_SIMPLEUIDLG_H__366088CF_EBD5_410F_9F70_5FB860F4BD3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSimpleUIDlg dialog

class CSimpleUIDlg : public CDialog
{
// Construction
public:
	int m_width;
	int m_height;
	CSimpleUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSimpleUIDlg)
	enum { IDD = IDD_SIMPLEUI_DIALOG };
	CSliderCtrl	m_cResolution;
	CString	m_model;
	CString	m_position;
	CString	m_cHost;
	UINT	m_cPort;
	CString	m_vHost;
	UINT	m_vPort;
	float	m_fps;
	int		m_local;
	int		m_remote;
	int		m_resValue;
	CString	m_resText;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleUIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSimpleUIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRemote();
	afx_msg void OnLocal();
	afx_msg void OnReleasedcaptureResolution(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposFps2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEUIDLG_H__366088CF_EBD5_410F_9F70_5FB860F4BD3C__INCLUDED_)
