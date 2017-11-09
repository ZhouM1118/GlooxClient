
// sqliteAppDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxdtctl.h"
#include "afxwin.h"
#include <string>

using namespace std;

static string print_merOrderId;
static string print_payTime;
static string print_totalAmount;
static string print_buyerUserName;
static string print_merName;
static string print_targetSys;

// CsqliteAppDlg 对话框
class CsqliteAppDlg : public CDialogEx
{
// 构造
public:
	CsqliteAppDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SQLITEAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk2();
	CListCtrl m_List;
	CDateTimeCtrl m_startDate;
	CDateTimeCtrl m_endDate;

	void printPoscbData();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_hideEdit;
	afx_msg void OnEnKillfocusEdit1();
};
