
// poscbApp.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "poscbApp.h"
#include "poscbAppDlg.h"
#include "MessageBoxAutoClose.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CposcbAppApp

BEGIN_MESSAGE_MAP(CposcbAppApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CposcbAppApp ����

CposcbAppApp::CposcbAppApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CposcbAppApp ����

CposcbAppApp theApp;


// CposcbAppApp ��ʼ��

BOOL CposcbAppApp::InitInstance()
{
	/*
	dlg.ReadConfig("Pos.ini", m_app);
	if (m_app["ISCONNECTED"] == "0")
	{
		MessageBoxTimeout(NULL, TEXT("�ѵ�¼����������ԭ�н���"), TEXT("��¼������Ϣ"), MB_ICONERROR, GetSystemDefaultLangID(), 5000);
		return false;
	}*/
	if (IsAlreadyRunning()){
		MessageBoxTimeout(NULL, TEXT("�ѵ�¼����������ԭ�н���"), TEXT("��¼������Ϣ"), MB_ICONERROR, GetSystemDefaultLangID(), 5000);
		return false;
	}
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	
	CposcbAppDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

BOOL CposcbAppApp::IsAlreadyRunning()
{
    BOOL bRet = FALSE;
	HANDLE hMutex = ::CreateMutex(NULL, TRUE, TEXT("poscbApp"));

    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        bRet = TRUE;
        HWND hWnd = FindWindow(TEXT("poscbApp"), TEXT("����CɨB�ͻ���"));
        SetForegroundWindow(hWnd);
    }
    if (hMutex)
    {
        ::ReleaseMutex(hMutex);
    }
    return bRet;
}