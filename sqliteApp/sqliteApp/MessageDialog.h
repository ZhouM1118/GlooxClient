#pragma once


// MessageDialog �Ի���

class MessageDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MessageDialog)

public:
	MessageDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MessageDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

	int mySecond;
	int totalSecond;
	bool msgtype_iswarn;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
