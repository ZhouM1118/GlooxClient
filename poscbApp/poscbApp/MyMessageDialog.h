#pragma once


// MyMessageDialog �Ի���

class MyMessageDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MyMessageDialog)

public:
	MyMessageDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MyMessageDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

	int mySecond;
	int totalSecond;
	CString msg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
