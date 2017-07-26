// SimpleUI.h : main header file for the SIMPLEUI application
//

#if !defined(AFX_SIMPLEUI_H__D49F269D_4A84_423E_9219_C75211C660E6__INCLUDED_)
#define AFX_SIMPLEUI_H__D49F269D_4A84_423E_9219_C75211C660E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSimpleUIApp:
// See SimpleUI.cpp for the implementation of this class
//

class CSimpleUIApp : public CWinApp
{
public:
	CSimpleUIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleUIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSimpleUIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEUI_H__D49F269D_4A84_423E_9219_C75211C660E6__INCLUDED_)
