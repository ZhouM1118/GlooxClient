
// poscbApp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <stdio.h>
#include <string>
#include <map>
using namespace std;

static map<string, string> m_app;
// CposcbAppApp:
// �йش����ʵ�֣������ poscbApp.cpp
//

class CposcbAppApp : public CWinApp
{
public:
	CposcbAppApp();

// ��д
public:
	virtual BOOL InitInstance();
	BOOL IsAlreadyRunning();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CposcbAppApp theApp;