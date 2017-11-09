// MyMessageDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "poscbApp.h"
#include "MyMessageDialog.h"
#include "afxdialogex.h"


// MyMessageDialog �Ի���

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


// MyMessageDialog ��Ϣ�������


void MyMessageDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		msgResult = msg + "��2����Զ��ر�";
		break;
	case 2:
		msgResult = msg + "��1����Զ��ر�";
		break;
	default:
		msgResult = msg + "�������ر�";
		break;
	}
	this->SetDlgItemTextA(IDC_STATIC, msgResult);
	mySecond++;
	CDialogEx::OnTimer(nIDEvent);
}
