// MessageDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sqliteApp.h"
#include "MessageDialog.h"
#include "afxdialogex.h"


// MessageDialog �Ի���

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


// MessageDialog ��Ϣ�������


void MessageDialog::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void MessageDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		msg = msgtype_iswarn ? "����д�����ţ�2����Զ��ر�" : "�������ݣ�2����Զ��ر�";
		break;
	case 2:
		msg = msgtype_iswarn ? "����д�����ţ�1����Զ��ر�" : "�������ݣ�1����Զ��ر�";
		break;
	default:
		msg = msgtype_iswarn ? "����д�����ţ������ر�" : "�������ݣ������ر�";
		break;
	}
	this->SetDlgItemTextA(IDC_STATIC, msg);
	mySecond++;
	CDialogEx::OnTimer(nIDEvent);
}
