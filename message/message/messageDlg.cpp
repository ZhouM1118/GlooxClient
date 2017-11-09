
// messageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "message.h"
#include "messageDlg.h"
#include "afxdialogex.h"
#include "MyLog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmessageDlg �Ի���



CmessageDlg::CmessageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmessageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmessageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CmessageDlg ��Ϣ�������

BOOL CmessageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*
	//��ȡ��Ļ��С
	int xSize = ::GetSystemMetrics (SM_CXSCREEN);  
    int ySize = ::GetSystemMetrics (SM_CYSCREEN);
	//���ô��ڴ�С
	int cx = (xSize*2)/7;  
    int cy = (ySize*2)/9;
	CWnd::MoveWindow(CRect(1,0,cx,cy));

	RECT rect;
	GetClientRect(&rect);
	MoveWindow(1, 0, rect.right, rect.bottom);
	
	*/

	

	//���ô��屳����ɫ
	m_brush.CreateSolidBrush(RGB(0,160,233));

	//������������
	font.CreatePointFont(240, _T("����"));
	GetDlgItem(IDC_STATIC) ->SetFont(&font);
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	MyLog::Inst()->Log("INFO:messageTypeDlg="+messageType+"\n");
	MyLog::Inst()->Log("INFO:totalMoneyDlg="+totalMoney+"\n");
	if (messageType == "1")
	{
		GetDlgItem(IDC_STATIC) ->SetWindowTextW(_T("���ӷ������ɹ���"));
	}else if (messageType == "2")
	{
		CString Cmoney(totalMoney.c_str());
		CString msg = _T("֧�������ˣ�") + Cmoney;
		GetDlgItem(IDC_STATIC) ->SetWindowTextW(msg);
	}
	
	mySecond = 1;
	totalSecond = 3;
	this ->SetTimer(1, 1000, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmessageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmessageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmessageDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (mySecond >= totalSecond)
	{
		KillTimer(1);
		this->OnCancel();
		return;
	}
	switch (mySecond)
	{
	case 1:
		if (messageType == "1")
		{
			GetDlgItem(IDC_STATIC) ->SetWindowTextW(_T("���ӷ������ɹ���"));
		}else if (messageType == "2")
		{
			CString Cmoney(totalMoney.c_str());
			CString msg = _T("֧�������ˣ�") + Cmoney;
			GetDlgItem(IDC_STATIC) ->SetWindowTextW(msg);
		}
		
		break;
	case 2:
		if (messageType == "1")
		{
			GetDlgItem(IDC_STATIC) ->SetWindowTextW(_T("���ӷ������ɹ���"));
		}else if (messageType == "2")
		{
			CString Cmoney(totalMoney.c_str());
			CString msg = _T("֧�������ˣ�") + Cmoney;
			GetDlgItem(IDC_STATIC) ->SetWindowTextW(msg);
		}
		
		break;
	}
	mySecond++;
	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CmessageDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor == CTLCOLOR_STATIC){
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkColor(RGB(0,160,233));
	}
	return m_brush;
}
