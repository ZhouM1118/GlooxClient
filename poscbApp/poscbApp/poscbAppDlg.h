
// poscbAppDlg.h : ͷ�ļ�
//

#pragma once
#define COMMENT_CHAR '#'
#include <iostream>
#include <fstream>

typedef struct 
{
	int tratype; //��������
	char rspcode[2+1];//������
	int amount;//���
	char casher[15+1];			//����Ա��
	char counter[15+1];			//��̨��
	char old_origno[6+1];		//��Ϊ�����ཻ��,��ʾԭ������������ԭ��ˮ��
	char old_reference[12+1];	//ԭ���ײο���
	char old_date[4+1];		//ԭ��������4λ
	char old_batch[6+1];		//ԭ�������κ�
	char old_trace[6+1];		//ԭ����ƾ֤��
	char issbank[4+1];		//�����к�
	char issbankname[8+1];		//����������
	char resp_chin[40+1];		//���Ĵ���˵��
	char resF042[15+1];			//�̻��� mid
	char resF041[8+1];			//�ն˺� tid
	char resF060[6+1];			//���κ�
	char resF011[6+1];			//��ˮ��
	char resF037[12+1];			//ϵͳ�ο��� paySeqId
	char resF013[4+1];			//MMDD
	char resF012[6+1];			//HHMMSS
	char resF015[4+1];			//MMDD
	char resF038[6+1];			//��Ȩ��
	char acptbank[4+1];			//�յ��к�
	char acptbankname[8+1];	             //�յ�������
	char resF014[4+1];			//��Ч��
	char billDate[12];
	char billDesc[255];			//�˵�����
	char billNo[28];				//�˵���
	char billBizType[25];
	char buyerId[255];
	char buyerPayAmount[255];
	char buyerUsername[255];
	char couponAmount[255];
	char invoiceAmount[255];
	char merOrderId[28];			//�̻�������
	char payDetail[255];
	char payTime[28];				//֧��ʱ��
	char settleDate[12];
	char status[255];
	char targetOrderId[35];		//Ŀ��ƽ̨����
	char targetSys[25];			//Ŀ��ϵͳ
	char totalAmount[25];		//֧�����
	char billQRCode[255];
	char billStatus[255];
	char createTime[25];
	char instMid[255];
	char merName[255];				//�̻�����
	char notifyId[255];
	char timestamp[25];
	char type[255];
}filein_type1;
// CposcbAppDlg �Ի���
class CposcbAppDlg : public CDialogEx
{
// ����
public:
	CposcbAppDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_POSCBAPP_DIALOG };
	CString	username;
	CString	password;
	CString domainName;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
