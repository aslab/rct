// VideoSocket.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleUI.h"
#include "VideoSocket.h"
#include "ControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoSocket

CVideoSocket::CVideoSocket()
{
}

CVideoSocket::CVideoSocket(CControlDlg * parent)
{
	m_parent = parent;
}

CVideoSocket::~CVideoSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CVideoSocket, CSocket)
	//{{AFX_MSG_MAP(CVideoSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CVideoSocket member functions

void CVideoSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_parent->ProcessVideoData();
}

void CVideoSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	Send("OK",2);
	AsyncSelect(FD_READ|FD_CLOSE);
}
