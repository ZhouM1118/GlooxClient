
// sqliteAppDlg.h : ͷ�ļ�
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

// CsqliteAppDlg �Ի���
class CsqliteAppDlg : public CDialogEx
{
// ����
public:
	CsqliteAppDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SQLITEAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
