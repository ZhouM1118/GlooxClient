
// poscbAppDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "poscbApp.h"
#include "poscbAppDlg.h"
#include "MyMessageDialog.h"
#include "afxdialogex.h"
#include "poscb.h"
#include "MessageBoxAutoClose.h"
#include <stdio.h>
#include "sqlite3.h"
#include <sphelper.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CposcbAppDlg �Ի���
CposcbAppDlg::CposcbAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CposcbAppDlg::IDD, pParent)
{
	//ReadConfig("D:\\Cworkspace\\poscb\\Debug\\Pos.ini", m_app);
	ReadConfig("Pos.ini", m_app);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	username.Format(TEXT("%s"), m_app["XMPP_NAME"].c_str());
	password.Format(TEXT("%s"), m_app["XMPP_PASSWD"].c_str());
	string domain =  m_app["XMPP_IP"] + ":" + m_app["XMPP_PORT"];
	domainName.Format(TEXT("%s"), domain.c_str());
}

void CposcbAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, username);
	DDX_Text(pDX, IDC_EDIT2, password);
	DDX_Text(pDX, IDC_EDIT3, domainName);
}

BEGIN_MESSAGE_MAP(CposcbAppDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CposcbAppDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CposcbAppDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CposcbAppDlg ��Ϣ�������

BOOL CposcbAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CposcbAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CposcbAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CposcbAppDlg::OnBnClickedOk()
{
	MoveWindow(0, 0, 0, 0);
	ShowWindow(SW_HIDE);
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	CString name;
	CString pw;
	CString ipAndPort;
	GetDlgItem(IDC_EDIT1)->GetWindowText(name);
	GetDlgItem(IDC_EDIT2)->GetWindowText(pw);
	GetDlgItem(IDC_EDIT3)->GetWindowText(ipAndPort);
	//writeConfig("D:\\Cworkspace\\poscb\\Debug\\Pos.ini", "D:\\Cworkspace\\poscb\\Debug\\Pos_backup.ini", name, pw, ipAndPort);
	writeConfig("Pos.ini", "Pos_backup.ini", name, pw, ipAndPort);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MyLog::Inst()->Log("INFO:��ʼ��¼\n");
	filein_type1 result;
	while (true)
	{
		char* filein = NULL; 
		filein = poscb::ConnectOpenFire(filein);
		if (filein != NULL && (filein[0] != '\0'))
		{
			memcpy(&result, filein, sizeof(filein_type1));
			string billDate = result.billDate;
			string billDesc = result.billDesc;
			string billNo = result.billNo;

			string billBizType = result.billBizType;
			string buyerId = result.buyerId;
			string buyerPayAmount = result.buyerPayAmount;
			string buyerUsername = result.buyerUsername;
			string couponAmount = result.couponAmount;
			string invoiceAmount = result.invoiceAmount;
			string merOrderId = result.merOrderId;
			string payDetail = result.payDetail;
			string paySeqId = result.resF037;
			string payTime = result.payTime;
			string settleDate = result.settleDate;
			string status = result.status;
			string targetOrderId = result.targetOrderId;
			string targetSys = result.targetSys;
			string totalAmount = result.totalAmount;

			string billQRCode = result.billQRCode;
			string billStatus = result.billStatus;
			string createTime = result.createTime;
			string instMid = result.instMid;
			string merName = result.merName;
			string mid = result.resF042;
			string notifyId = result.notifyId;
			string tid = result.resF041;

			string timestamp = result.timestamp;
			string type = result.type;

			MyLog::Inst()->Log("INFO:���յ��������ݣ�billDate=" + billDate
							+ ",billDesc=" + billDesc 
							+ ",billNo=" + billNo
							+ ",billBizType=" + billBizType
							+ ",buyerId=" + buyerId
							+ ",buyerPayAmount=" + buyerPayAmount
							+ ",buyerUsername=" + buyerUsername
							+ ",couponAmount=" + couponAmount
							+ ",invoiceAmount=" + invoiceAmount
							+ ",merOrderId=" + merOrderId
							+ ",payDetail=" + payDetail
							+ ",paySeqId=" + paySeqId 
							+ ",payTime=" + payTime
							+ ",settleDate=" + settleDate
							+ ",status=" + status
							+ ",targetOrderId=" + targetOrderId
							+ ",targetSys=" + targetSys
							+ ",totalAmount=" + totalAmount
							+ ",billQRCode=" + billQRCode
							+ ",billStatus=" + billStatus
							+ ",createTime=" + createTime
							+ ",instMid=" + instMid 
							+ ",merName=" + merName
							+ ",mid=" + mid
							+ ",notifyId=" + notifyId
							+ ",tid=" + tid
							+ ",timestamp=" + timestamp
							+ ",type=" + type
							+ "\n"
							);
			if(insertFilein(result) == 0)
			{
				int money = atoi(totalAmount.c_str());
				stringstream ss;
				string moneyStr;
				string moneyParam;
				CString voiceMsg;
				double dMoney = money * 0.01 + 0.005;
				double spliteMoney = int(dMoney * 100.0) / 100.0;
				char buf[18];
				sprintf_s(buf, "%.2f", spliteMoney);
				//ss << money * 0.01 + 0.005;
				//ss >> moneyParam;
				moneyParam = buf;
				string messageParams = "2 " + moneyParam;

				string smallMoneyStr;
				double voiceMoney = money * 0.01 + 0.005;
				ss.clear();
				string vstr;
				ss << voiceMoney;
				ss >> vstr;
				MyLog::Inst()->Log("INFO:voiceMoney=" + vstr + "\n");

				int bigMoney = (int)voiceMoney;
				string bigMoneyStr;
				ss.clear();
				ss << bigMoney;
				ss >> bigMoneyStr;
				MyLog::Inst()->Log("INFO:bigMoneyStr=" + bigMoneyStr + "\n");

				int smallMoney = (voiceMoney - bigMoney) * 100;
				ss.clear();
				string sm;
				ss << smallMoney;
				ss >> sm;
				MyLog::Inst()->Log("INFO:smallMoney=" + sm + "\n");
				if (smallMoney < 10 && smallMoney > 0)
				{
					smallMoneyStr = sm + "��";
				}else if(smallMoney == 0){
					smallMoneyStr = "";
				}else
				{
					ss.clear();
					string schum;
					ss << (smallMoney / 10);
					ss >> schum;
					MyLog::Inst()->Log("INFO:smallMoney / 10=" + schum + "\n");
					ss.clear();
					string smodm;
					ss << (smallMoney % 10);
					ss >> smodm;
					if((smallMoney % 10) == 0){
						smallMoneyStr = schum + "��";
					}else
					{
						smallMoneyStr = schum + "��" + smodm + "��";
					}
					MyLog::Inst()->Log("INFO:smallMoney % 10=" + smodm + "\n");
					
				}
				MyLog::Inst()->Log("INFO:smallMoneyStr=" + smallMoneyStr + "\n");

				if (bigMoney == 0)
				{
					moneyStr = "֧�������ˣ�" + smallMoneyStr;
				}else
				{
					moneyStr = "֧�������ˣ�" + bigMoneyStr + "Ԫ" + smallMoneyStr;
				}
				
				voiceMsg = moneyStr.c_str();
				MyLog::Inst()->Log("INFO:������Ϣ��" + moneyStr + "\n");
				if (targetSys.find("Alipay") != string::npos )
				{ 
					//MessageBoxTimeout(NULL, TEXT(moneyStr.c_str()), TEXT("֧����ʾ��Ϣ"), MB_ICONINFORMATION, GetSystemDefaultLangID(), 5000);
					//showMyMessageDialog(moneyMsg, moneyStr);
					ShellExecute(NULL, TEXT("open"), TEXT("message.exe"), TEXT(messageParams.c_str()), NULL, SW_SHOW);

					ISpVoice *pVoice = NULL;
					
					if (FAILED(CoInitialize(NULL)))
					{
						MyLog::Inst()->Log("ERROR:��ʼ����������ʧ�ܣ�\n");
						continue;
					}
					MyLog::Inst()->Log("INFO:��ʼ���������ܳɹ���\n");
					HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER, IID_ISpVoice, (void **)&pVoice);
					ISpObjectToken *pSpObjectToken = NULL;
					if (SUCCEEDED(SpFindBestToken(SPCAT_VOICES, L"language=804", NULL, &pSpObjectToken)))
					{
						pVoice ->SetVoice(pSpObjectToken);
						pVoice ->SetVolume(80);
						pVoice ->SetRate(-2);
						pSpObjectToken ->Release();
					}else
					{
						MyLog::Inst()->Log("ERROR:û�а�װ΢�������⣡\n");
						continue;
					}
					if (SUCCEEDED(hr))
					{
						hr = pVoice ->Speak(voiceMsg.AllocSysString(), SPF_DEFAULT, NULL);
						pVoice ->Release();
						pVoice = NULL;
					}

					::CoUninitialize();
					
				}
			}
		}
	}
	
	//CDialogEx::OnOK();
}


void CposcbAppDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

bool CposcbAppDlg::ReadConfig(const string & filename, map<string, string> & m_app)
{
	m_app.clear();
	ifstream infile(filename.c_str());
	if (!infile) {
		Sleep(2000);
		return false;
	}
	string line, key, value;
	while (getline(infile, line)) {
		if (AnalyseLine(line, key, value)) {
			m_app[key] = value;
		}
	}
    
	infile.close();
	return true;
}

bool CposcbAppDlg::writeConfig(string fromfilename, string tofilename, CString name, CString pw, CString ipAndPort)
{
	ifstream infile;
	infile.open(fromfilename);
	ofstream outfile;
	outfile.open(tofilename);
	if (!infile) {
		Sleep(2000);
		return false;
	}
	CString ip = "";
	CString port = "";
	bool portFlag = false;
	int index = ipAndPort.Find(":");
	if (index == -1)
	{
		ip = ipAndPort;
	}else
	{
		ip = ipAndPort.Left(index);
		port = ipAndPort.Mid(index+1, ipAndPort.GetLength());
		portFlag = true;
	}
	string line;
	while (getline(infile, line)) {
		int pos = 0;
		if (line.empty() || line.find(COMMENT_CHAR) == 0 || line.find("[") == 0 || (pos = line.find('=')) == -1){
			outfile << line << endl;
			continue;
		}
		if (line.substr(0, pos) == "XMPP_NAME") 
		{
			line = "XMPP_NAME=" + name;
		}
		if (line.substr(0, pos) == "XMPP_PASSWD") 
		{
			line = "XMPP_PASSWD=" + pw;

		}
		if (line.substr(0, pos) == "XMPP_IP") 
		{
			line = "XMPP_IP=" + ip;
		}
		if (portFlag && line.substr(0, pos) == "XMPP_PORT") 
		{
			line = "XMPP_PORT=" + port;
		}
		outfile << line << endl;
	}
	outfile.close();
	infile.close();
	if (!remove(fromfilename.c_str()))
	{
		rename(tofilename.c_str(), fromfilename.c_str());
	}
	return true;
}

bool CposcbAppDlg::AnalyseLine(const string & line, string & key, string & value)
{
	if (line.empty())
		return false;
	int pos = 0;
	if (line.find(COMMENT_CHAR) == 0 || line.find("[") == 0) 
	{
		return false;// �еĵ�һ���ַ���ע���ַ���[���������
	}
    
	if ((pos = line.find('=')) == -1){
		return false;  // û��=��
	}
	key = line.substr(0, pos);
	value = line.substr(pos + 1, line.size()- (pos + 1));
    
	Trim(key);
	if (key.empty()) {
		return false;
	}
	Trim(value);
	return true;
}

//�޳���һ�еĿո����
void CposcbAppDlg::Trim(string & str)
{
	if (str.empty()) {
		return;
	}
	int i, start_pos, end_pos;
	//�޳���һ�п�ͷ���ֵĿո����
	for (i = 0; i < str.size(); ++i) {
		if (!IsSpace(str[i])) {
			break;
		}
	}
	if (i == str.size()) { // ȫ���ǿհ��ַ���
		str = "";
		return;
	}
    
	start_pos = i;
	//�޳���һ�н�β���ֵĿո����
	for (i = str.size() - 1; i >= 0; --i) {
		if (!IsSpace(str[i])) {
			break;
		}
	}
	end_pos = i;
    
	str = str.substr(start_pos, end_pos - start_pos + 1);
}

bool CposcbAppDlg::IsSpace(char c)
{
	if (' ' == c || '\t' == c)
		return true;
	return false;
}

bool CposcbAppDlg::IsCommentChar(char c)
{
	switch(c) {
		case COMMENT_CHAR:
			return true;
		default:
			return false;
	}
} 

void CposcbAppDlg::showMyMessageDialog(string moneyMsg, string moneyStr){
	MyMessageDialog *MyDialog = new MyMessageDialog;
	MyDialog ->mySecond = 1;
	MyDialog ->totalSecond = 3;
	MyDialog ->msg = moneyMsg.c_str();
	MyDialog ->Create(IDD_DIALOG1, this);
	MyDialog ->SetWindowTextA("֧����ʾ��Ϣ");
	MyDialog ->SetDlgItemTextA(IDC_STATIC, TEXT(moneyStr.c_str()));
	MyDialog ->SetTimer(1, 1000, NULL);
	MyDialog ->ShowWindow(SW_SHOW);
	return;
}

int CposcbAppDlg::insertFilein(filein_type1 result)
{
	sqlite3 *db = NULL;
	char *zErrMsg = 0;
	int rc;
	string errmsg = "";

	rc = sqlite3_open("poscb.db", &db);
	if (rc)
	{
		errmsg = sqlite3_errmsg(db);
		MyLog::Inst()->Log("ERROR:��poscb.db���ݿ�ʧ�ܣ�" + errmsg + "\n");
		sqlite3_close(db);
		return 1;
	}else
	{
		MyLog::Inst()->Log("INFO:��poscb.db���ݿ�ɹ�\n");
	}

	const char *sql = "CREATE TABLE poscb(id INTEGER PRIMARY KEY,billDate VARCHAR(255),billDesc VARCHAR(255),billNo VARCHAR(255),billBizType VARCHAR(255),buyerId VARCHAR(255),buyerPayAmount VARCHAR(255),buyerUsername VARCHAR(255),couponAmount VARCHAR(255),invoiceAmount VARCHAR(255),merOrderId VARCHAR(255),payDetail VARCHAR(255),paySeqId VARCHAR(255),payTime VARCHAR(255),settleDate VARCHAR(255),status VARCHAR(255),targetOrderId VARCHAR(255),targetSys VARCHAR(255),totalAmount VARCHAR(255),billQRCode VARCHAR(255),billStatus VARCHAR(255),createTime VARCHAR(255),instMid VARCHAR(255),merName VARCHAR(255),mid VARCHAR(255),notifyId VARCHAR(255),tid VARCHAR(255),timestamp VARCHAR(255),type VARCHAR(255),remarks1 VARCHAR(255),remarks2 VARCHAR(255));";
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	//errmsg = zErrMsg;
	//MyLog::Inst()->Log("INFO:�������ݱ�" + errmsg + "\n");

	string billDate = result.billDate;
	string billDesc = result.billDesc;
	string billNo = result.billNo;

	string billBizType = result.billBizType;
	string buyerId = result.buyerId;
	string buyerPayAmount = result.buyerPayAmount;
	string buyerUsername = result.buyerUsername;
	string couponAmount = result.couponAmount;
	string invoiceAmount = result.invoiceAmount;
	string merOrderId = result.merOrderId;
	string payDetail = result.payDetail;
	string paySeqId = result.resF037;
	string payTime = result.payTime;
	string settleDate = result.settleDate;
	string status = result.status;
	string targetOrderId = result.targetOrderId;
	string targetSys = result.targetSys;
	string totalAmount = result.totalAmount;

	string billQRCode = result.billQRCode;
	string billStatus = result.billStatus;
	string createTime = result.createTime;
	string instMid = result.instMid;
	string merName = result.merName;
	string mid = result.resF042;
	string notifyId = result.notifyId;
	string tid = result.resF041;

	string timestamp = result.timestamp;
	string type = result.type;

	string sqlStr = "INSERT INTO \"poscb\" VALUES(NULL , '" + billDate + "', '"
		+ billDesc + "', '" + billNo + "', '" + billBizType + "', '" + buyerId + "', '"
		+ buyerPayAmount + "', '" + buyerUsername + "', '" + couponAmount + "', '" + invoiceAmount + "', '"
		+ merOrderId + "', '" + payDetail + "', '" + paySeqId + "', '" + payTime + "', '"
		+ settleDate + "', '" + status + "', '" + targetOrderId + "', '" + targetSys + "', '"
		+ totalAmount + "', '" + billQRCode + "', '" + billStatus + "', '" + createTime + "', '"
		+ instMid + "', '" + merName + "', '" + mid + "', '" + notifyId + "', '"
		+ tid + "', '" + timestamp + "', '" + type + "','', '')";
	MyLog::Inst()->Log("INFO:�������ݿ�sql��" + sqlStr + "\n");
	sql = sqlStr.c_str();
	//sql = "INSERT INTO \"poscb\" VALUES(NULL ,"+billDate+",'200605011206', 18.9 );";
	rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		errmsg = zErrMsg;
		MyLog::Inst()->Log("ERROR:��������ʧ�ܣ�" + errmsg + "\n");
		//sqlite3_free(zErrMsg);
		return 1;
	}

	int nrow = 0, ncolumn = 0; //��ѯ�����������������
    char **azResult; //��ά�����Ž��
	sql = "SELECT * FROM poscb ";
    sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
    int i = 0 ;
	for( i=0 ; i<( nrow + 1 ) * ncolumn ; i++ )
	{
		string result = azResult[i];
		MyLog::Inst()->Log("INFO:����Ϊ��" + result + "\n");
	}
	sqlite3_free_table( azResult );
	sqlite3_close(db);
	return 0;
}