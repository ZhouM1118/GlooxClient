// MyMessageDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "poscbApp.h"
#include "MyMessageDialog.h"
#include "afxdialogex.h"


// MyMessageDialog 对话框

IMPLEMENT_DYNAMIC(MyMessageDialog, CDialogEx)

MyMessageDialog::MyMessageDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(MyMessageDialog::IDD, pParent)
{

}

MyMessageDialog::~MyMessageDialog()
{
}

void MyMessageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyMessageDialog, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// MyMessageDialog 消息处理程序


void MyMessageDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mySecond >= totalSecond)
	{
		KillTimer(1);
		this->OnCancel();
		return;
	}
	CString msgResult = "";
	switch (mySecond)
	{
	case 1:
		msgResult = msg + "！2秒后自动关闭";
		break;
	case 2:
		msgResult = msg + "！1秒后自动关闭";
		break;
	default:
		msgResult = msg + "！即将关闭";
		break;
	}
	this->SetDlgItemTextA(IDC_STATIC, msgResult);
	mySecond++;
	CDialogEx::OnTimer(nIDEvent);
}
