// MessageDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "sqliteApp.h"
#include "MessageDialog.h"
#include "afxdialogex.h"


// MessageDialog 对话框

IMPLEMENT_DYNAMIC(MessageDialog, CDialogEx)

MessageDialog::MessageDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(MessageDialog::IDD, pParent)
{

}

MessageDialog::~MessageDialog()
{
}

void MessageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MessageDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &MessageDialog::OnEnChangeEdit1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// MessageDialog 消息处理程序


void MessageDialog::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void MessageDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mySecond >= totalSecond)
	{
		KillTimer(1);
		this->OnCancel();
		return;
	}
	CString msg = "";
	switch (mySecond)
	{
	case 1:
		msg = msgtype_iswarn ? "需填写订单号！2秒后自动关闭" : "暂无数据！2秒后自动关闭";
		break;
	case 2:
		msg = msgtype_iswarn ? "需填写订单号！1秒后自动关闭" : "暂无数据！1秒后自动关闭";
		break;
	default:
		msg = msgtype_iswarn ? "需填写订单号！即将关闭" : "暂无数据！即将关闭";
		break;
	}
	this->SetDlgItemTextA(IDC_STATIC, msg);
	mySecond++;
	CDialogEx::OnTimer(nIDEvent);
}
