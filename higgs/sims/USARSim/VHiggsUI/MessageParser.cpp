// MessageParser.cpp: implementation of the CMessageParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MessageParser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessageParser::CMessageParser()
{

}

CMessageParser::~CMessageParser()
{

}

void CMessageParser::SetMessage(CString str)
{
	m_message = str;
}

CString CMessageParser::GetString(CString name, CString str)
{
	CString myName = "{" + name;
	int p1,p2;

	p1 = str.Find(LPCSTR(myName));
	if (p1<0) return "";
	p1 += myName.GetLength();
	p2 = str.Find("}",p1);
	CString result = str.Mid(p1, p2-p1);
	result.TrimLeft();
	result.TrimRight();
	return result;
}

CString CMessageParser::GetString(CString name)
{
	return GetString(name, m_message);
}

void CMessageParser::GetInts(CString name, CString str, char delimiter, int* count, int* data)
{
	CString dataStr = GetString(name,str);
	CString tmp;
	int p1=0,p2=0,idx=0;

	while (p1>=0) {
		p2 = dataStr.Find(delimiter,p1);
		if (p2>0) {
			tmp = dataStr.Mid(p1,p2-p1);
			p2 += 1;
		}
		else tmp = dataStr.Mid(p1);
		p1 = p2;
		data[idx++] = atoi(LPCSTR(tmp));
		if (idx>=*count) return;
	}
	*count = idx;
}

void CMessageParser::GetInts(CString name, char delimiter, int* count, int* data)
{
	GetInts(name,m_message,delimiter,count,data);
}

void CMessageParser::GetFloats(CString name, CString str, char delimiter, int* count, float* data)
{
	CString dataStr = GetString(name,str);
	CString tmp;
	int p1=0,p2=0,idx=0;

	while (p1>=0&&p2>=0) {
		p1 = dataStr.Find(delimiter,p2);
		if (p1>0) {
			tmp = dataStr.Mid(p2,p1-p2);
			p2 = p1+1;
		}
		else tmp = dataStr.Mid(p2);
		data[idx++] = (float)atof(LPCSTR(tmp));
		if (idx>=*count) return;
	}
	*count = idx;
}

void CMessageParser::GetFloats(CString name, char delimiter, int* count, float* data)
{
	GetFloats(name,m_message,delimiter,count,data);
}

int CMessageParser::GetInt(CString name, CString str)
{
	return atoi(LPCSTR(GetString(name,str)));
}

float CMessageParser::GetFloat(CString name, CString str)
{
	return (float)atof(LPCSTR(GetString(name,str)));
}

int CMessageParser::GetInt(CString name)
{
	return atoi(LPCSTR(GetString(name)));
}

float CMessageParser::GetFloat(CString name)
{
	return (float)atof(LPCSTR(GetString(name)));
}

void CMessageParser::GetStrings(CString name, CString str, char delimiter, int *count, CString *data)
{
	CString dataStr = GetString(name,str);
	CString tmp;
	int p1=0,p2=0,idx=0;

	while (p1>=0&&p2>=0) {
		p1 = dataStr.Find(delimiter,p2)+1;
		if (p1>0) {
			p2 = dataStr.Find(delimiter,p1);
			if (p2>0) 
				tmp = dataStr.Mid(p1,p2-p1);
			else tmp = dataStr.Mid(p1);
		}
		else tmp = dataStr;
		data[idx++] = tmp;
		if (idx>=*count) return;
	}
	*count = idx;
}

void CMessageParser::GetStrings(CString name, char delimiter, int *count, CString *data)
{
	GetStrings(name, m_message, delimiter, count, data);
}

CString CMessageParser::GetString(CString name, CString str, int start, int &end)
{
	if (start<0) {
		end = -1;
		return "";
	}
	CString myName = "{" + name;
	int p1,p2;

	p1 = str.Find(LPCSTR(myName),start);
	if (p1<0) {
		end = -1;
		return "";
	}
	p1 += myName.GetLength();
	p2 = str.Find("}",p1);
	CString result = str.Mid(p1, p2-p1);
	result.TrimLeft();
	result.TrimRight();
	end = p2;
	return result;
}

CString CMessageParser::GetString(CString name, int start, int &end)
{
	return GetString(name, m_message, start, end);
}
