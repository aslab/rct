#if !defined(AFX_CMDSOCKET_H__F9BBF2BC_44FB_4773_A8FF_E136E1769594__INCLUDED_)
#define AFX_CMDSOCKET_H__F9BBF2BC_44FB_4773_A8FF_E136E1769594__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CmdSocket.h : header file
//

class CControlDlg;

/////////////////////////////////////////////////////////////////////////////
// CCmdSocket command target

class CCmdSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CCmdSocket();
	CCmdSocket(CControlDlg* parent);
	virtual ~CCmdSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCmdSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CCmdSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CControlDlg * m_parent;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMDSOCKET_H__F9BBF2BC_44FB_4773_A8FF_E136E1769594__INCLUDED_)
