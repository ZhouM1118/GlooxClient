
// messageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "message.h"
#include "messageDlg.h"
#include "afxdialogex.h"
#include "MyLog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmessageDlg 对话框



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


// CmessageDlg 消息处理程序

BOOL CmessageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*
	//获取屏幕大小
	int xSize = ::GetSystemMetrics (SM_CXSCREEN);  
    int ySize = ::GetSystemMetrics (SM_CYSCREEN);
	//设置窗口大小
	int cx = (xSize*2)/7;  
    int cy = (ySize*2)/9;
	CWnd::MoveWindow(CRect(1,0,cx,cy));

	RECT rect;
	GetClientRect(&rect);
	MoveWindow(1, 0, rect.right, rect.bottom);
	
	*/

	

	//设置窗体背景颜色
	m_brush.CreateSolidBrush(RGB(0,160,233));

	//设置字体属性
	font.CreatePointFont(240, _T("黑体"));
	GetDlgItem(IDC_STATIC) ->SetFont(&font);
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	MyLog::Inst()->Log("INFO:messageTypeDlg="+messageType+"\n");
	MyLog::Inst()->Log("INFO:totalMoneyDlg="+totalMoney+"\n");
	if (messageType == "1")
	{
		GetDlgItem(IDC_STATIC) ->SetWindowTextW(_T("连接服务器成功！"));
	}else if (messageType == "2")
	{
		CString Cmoney(totalMoney.c_str());
		CString msg = _T("支付宝到账：") + Cmoney;
		GetDlgItem(IDC_STATIC) ->SetWindowTextW(msg);
	}
	
	mySecond = 1;
	totalSecond = 3;
	this ->SetTimer(1, 1000, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmessageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmessageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmessageDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
			GetDlgItem(IDC_STATIC) ->SetWindowTextW(_T("连接服务器成功！"));
		}else if (messageType == "2")
		{
			CString Cmoney(totalMoney.c_str());
			CString msg = _T("支付宝到账：") + Cmoney;
			GetDlgItem(IDC_STATIC) ->SetWindowTextW(msg);
		}
		
		break;
	case 2:
		if (messageType == "1")
		{
			GetDlgItem(IDC_STATIC) ->SetWindowTextW(_T("连接服务器成功！"));
		}else if (messageType == "2")
		{
			CString Cmoney(totalMoney.c_str());
			CString msg = _T("支付宝到账：") + Cmoney;
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
