
// poscbAppDlg.h : 头文件
//

#pragma once
#define COMMENT_CHAR '#'
#include <iostream>
#include <fstream>

typedef struct 
{
	int tratype; //交易类型
	char rspcode[2+1];//返回码
	int amount;//金额
	char casher[15+1];			//操作员号
	char counter[15+1];			//柜台号
	char old_origno[6+1];		//若为撤销类交易,表示原交易所撤销的原流水号
	char old_reference[12+1];	//原交易参考号
	char old_date[4+1];		//原交易日期4位
	char old_batch[6+1];		//原交易批次号
	char old_trace[6+1];		//原交易凭证号
	char issbank[4+1];		//发卡行号
	char issbankname[8+1];		//发卡行名称
	char resp_chin[40+1];		//中文错误说明
	char resF042[15+1];			//商户号 mid
	char resF041[8+1];			//终端号 tid
	char resF060[6+1];			//批次号
	char resF011[6+1];			//流水号
	char resF037[12+1];			//系统参考号 paySeqId
	char resF013[4+1];			//MMDD
	char resF012[6+1];			//HHMMSS
	char resF015[4+1];			//MMDD
	char resF038[6+1];			//授权号
	char acptbank[4+1];			//收单行号
	char acptbankname[8+1];	             //收单行名称
	char resF014[4+1];			//有效期
	char billDate[12];
	char billDesc[255];			//账单描述
	char billNo[28];				//账单号
	char billBizType[25];
	char buyerId[255];
	char buyerPayAmount[255];
	char buyerUsername[255];
	char couponAmount[255];
	char invoiceAmount[255];
	char merOrderId[28];			//商户订单号
	char payDetail[255];
	char payTime[28];				//支付时间
	char settleDate[12];
	char status[255];
	char targetOrderId[35];		//目标平台单号
	char targetSys[25];			//目标系统
	char totalAmount[25];		//支付金额
	char billQRCode[255];
	char billStatus[255];
	char createTime[25];
	char instMid[255];
	char merName[255];				//商户名称
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
