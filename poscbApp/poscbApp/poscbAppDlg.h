
// poscbAppDlg.h : 头文件
//

#pragma once
#define COMMENT_CHAR '#'
#include <iostream>
#include <fstream>

typedef struct 
{
	char billBizType[25];
	char buyerId[255];
	char buyerPayAmount[255];
	char buyerUsername[255];
	char couponAmount[255];
	char payDetail[255];
	char settleDate[12];
	char status[255];
	char billQRCode[255];
	char billStatus[255];
	char createTime[25];
	char instMid[255];
	char notifyId[255];
	char timestamp[25];
	char type[255];
}filein_type1;
// CposcbAppDlg 对话框
class CposcbAppDlg : public CDialogEx
{
// 构造
public:
	CposcbAppDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_POSCBAPP_DIALOG };
	CString	username;
	CString	password;
	CString domainName;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();

	bool ReadConfig(const string & filename, map<string, string> & m);
	bool writeConfig(string fromfilename, string tofilename, CString name, CString pw, CString ip);
	bool AnalyseLine(const string & line, string & key, string & value);
	void Trim(string & str);
	bool IsSpace(char c);
	bool IsCommentChar(char c);

	int insertFilein(filein_type1 result);

	void showMyMessageDialog(string moneyMsg, string moneyStr);
};
