// MessageParser.h: interface for the CMessageParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGEPARSER_H__005A0F1C_9C50_4279_B21D_834693D519A9__INCLUDED_)
#define AFX_MESSAGEPARSER_H__005A0F1C_9C50_4279_B21D_834693D519A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMessageParser  
{
public:
	CString GetString(CString name, int start, int& end);
	static CString GetString(CString name, CString str, int start, int& end);
	static void GetStrings(CString name, CString str, char delimiter, int* count, CString* data);
	void GetStrings(CString name, char delimiter, int* count, CString* data);
	float GetFloat(CString name);
	int GetInt(CString name);
	static float GetFloat(CString name, CString str);
	static int GetInt(CString name, CString str);
	static void GetInts(CString name, CString str, char delimiter, int* count, int* data);
	static void GetFloats(CString name, CString str, char delimiter, int* count, float* data);
	static CString GetString(CString name, CString str);
	void GetInts(CString name, char delimiter, int* count, int* data);
	void GetFloats(CString name, char delimiter, int* count, float* data);
	CString GetString(CString name);
	void SetMessage(CString str);
	CString m_message;
	CMessageParser();
	virtual ~CMessageParser();

};

#endif // !defined(AFX_MESSAGEPARSER_H__005A0F1C_9C50_4279_B21D_834693D519A9__INCLUDED_)
