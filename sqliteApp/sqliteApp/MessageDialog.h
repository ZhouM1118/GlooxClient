#pragma once


// MessageDialog 对话框

class MessageDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MessageDialog)

public:
	MessageDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MessageDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

	int mySecond;
	int totalSecond;
	bool msgtype_iswarn;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
