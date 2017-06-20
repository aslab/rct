#if !defined(AFX_VIDEOSOCKET_H__6E066FAE_6B47_4343_88A8_1A0AB51A7006__INCLUDED_)
#define AFX_VIDEOSOCKET_H__6E066FAE_6B47_4343_88A8_1A0AB51A7006__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoSocket.h : header file
//

class CControlDlg;

/////////////////////////////////////////////////////////////////////////////
// CVideoSocket command target

class CVideoSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CVideoSocket();
	CVideoSocket(CControlDlg * parent);
	virtual ~CVideoSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CVideoSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CControlDlg * m_parent;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOSOCKET_H__6E066FAE_6B47_4343_88A8_1A0AB51A7006__INCLUDED_)
