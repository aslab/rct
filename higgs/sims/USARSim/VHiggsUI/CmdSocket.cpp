// CmdSocket.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleUI.h"
#include "CmdSocket.h"
#include "ControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCmdSocket

CCmdSocket::CCmdSocket()
{
}

CCmdSocket::CCmdSocket(CControlDlg * parent)
{
	m_parent = parent;
}

CCmdSocket::~CCmdSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CCmdSocket, CSocket)
	//{{AFX_MSG_MAP(CCmdSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CCmdSocket member functions

void CCmdSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CSocket::OnReceive(nErrorCode);
	m_parent->ProcessMsgData();
}
