#pragma once


// MyMessageDialog 对话框

class MyMessageDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MyMessageDialog)

public:
	MyMessageDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MyMessageDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

	int mySecond;
	int totalSecond;
	CString msg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
