
// sqliteAppDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "sqliteApp.h"
#include "sqliteAppDlg.h"
#include "MessageDialog.h"
#include "afxdialogex.h"
#include "MessageBoxAutoClose.h"
#include "sqlite3.h"
#include "MyLog.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CsqliteAppDlg 对话框



CsqliteAppDlg::CsqliteAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CsqliteAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsqliteAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_startDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_endDate);
	DDX_Control(pDX, IDC_EDIT1, m_hideEdit);
}

BEGIN_MESSAGE_MAP(CsqliteAppDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CsqliteAppDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDOK2, &CsqliteAppDlg::OnBnClickedOk2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CsqliteAppDlg::OnNMRClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CsqliteAppDlg::OnNMDblclkList1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CsqliteAppDlg::OnEnKillfocusEdit1)
END_MESSAGE_MAP()


// CsqliteAppDlg 消息处理程序

BOOL CsqliteAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_hideEdit.ShowWindow(SW_HIDE);

	LONG lStyle;
	lStyle = GetWindowLong(m_List.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_List.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD dwStyle = m_List.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_List.SetExtendedStyle(dwStyle); //设置扩展风格
	m_List.SetItemState(0, 0, LVIS_SELECTED|LVIS_FOCUSED);

	CRect rect;
	m_List.GetClientRect(rect);
	m_List.InsertColumn( 0, _T("订单号"), LVCFMT_CENTER, 5*rect.Width()/16,0);
	m_List.InsertColumn( 1, _T("支付时间"), LVCFMT_CENTER, 3*rect.Width()/16,1);
	m_List.InsertColumn( 2, _T("支付金额"), LVCFMT_CENTER, rect.Width()/8,2);
	m_List.InsertColumn( 3, _T("买家用户名"), LVCFMT_CENTER, rect.Width()/8,3);
	m_List.InsertColumn( 4, _T("商户名称"), LVCFMT_CENTER, rect.Width()/8,4);
	m_List.InsertColumn( 5, _T("目标系统"), LVCFMT_CENTER, rect.Width()/8,5);

	sqlite3 *db = NULL;
	char *zErrMsg = 0;
	int rc;
	string errmsg = "";
	rc = sqlite3_open("poscb.db", &db);
	if (rc)
	{
		errmsg = sqlite3_errmsg(db);
		MyLog::Inst()->Log("ERROR:打开poscb.db数据库失败：" + errmsg + "\n");
		sqlite3_close(db);
		return FALSE;
	}else
	{
		MyLog::Inst()->Log("INFO:打开poscb.db数据库成功\n");
	}

	string sqlStr = "SELECT * FROM poscb";
	MyLog::Inst()->Log("INFO:" + sqlStr + "\n");
	const char *sql = sqlStr.c_str();
	int nrow = 0, ncolumn = 0; //查询结果集的行数、列数
    char **azResult; //二维数组存放结果
	sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );

	CString result_merOrderId;
	CString result_payTime;
	CString result_totalAmount;
	CString result_buyerUserName;
	CString result_merName;
	CString result_targetSys;

	for (int i = 1; i <= nrow; i++)
	{
		result_merOrderId.Format(_T("%s"), azResult[(i-1)*31 + 41]);
		result_payTime.Format(_T("%s"), azResult[(i-1)*31 + 44]);

		string totalAmountStr = azResult[(i-1)*31 + 49];
		int money = atoi(totalAmountStr.c_str());
		double dm = money * 0.01 + 0.005;
		double d = int(dm * 100.0) / 100.0;
		char buf[18];
		sprintf_s(buf, "%.2f", d);
		result_totalAmount = buf;

		result_buyerUserName.Format(_T("%s"), azResult[(i-1)*31 + 38]);
		result_merName.Format(_T("%s"), azResult[(i-1)*31 + 54]);

		string targetSysStr = azResult[(i-1)*31 + 48];
		string targetType = "";
		if (targetSysStr.find("Alipay") != string::npos ){
			targetType = "支付宝";
		}else if(targetSysStr.find("WXPay") != string::npos)
		{
			targetType = "微信";
		}
		result_targetSys.Format(_T("%s"), targetType.c_str());

		m_List.InsertItem(0, result_merOrderId);
		m_List.SetItemText(0, 1, result_payTime); 
		m_List.SetItemText(0, 2, result_totalAmount); 
		m_List.SetItemText(0, 3, result_buyerUserName); 
		m_List.SetItemText(0, 4, result_merName); 
		m_List.SetItemText(0, 5, result_targetSys);
	}

	sqlite3_free_table( azResult );
	sqlite3_close(db);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CsqliteAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CsqliteAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CsqliteAppDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CsqliteAppDlg::OnBnClickedOk2()
{
	print_merOrderId = "";
	print_payTime = "";
	print_totalAmount = "";
	print_buyerUserName = "";
	print_merName = "";
	print_targetSys = "";
	m_List.DeleteAllItems();
	// 控件通知处理程序代码
	CTime tm_start;
	m_startDate.GetTime(tm_start);
	CString startBillDate = tm_start.Format("%Y-%m-%d");
	string startBillDateStr = startBillDate.GetBuffer();

	CTime tm_end;
	m_endDate.GetTime(tm_end);
	CString endBillDate = tm_end.Format("%Y-%m-%d");
	string endBillDateStr = endBillDate.GetBuffer();

	CString merId;
	GetDlgItem(IDC_EDIT2)->GetWindowText(merId);
	if (merId.IsEmpty())
	{
		//MessageBoxTimeout(NULL, TEXT("需填写订单号！"), TEXT("警告信息"), MB_ICONINFORMATION, GetSystemDefaultLangID(), 5000);
		MessageDialog *MyDialog = new MessageDialog;
		MyDialog ->mySecond = 1;
		MyDialog ->totalSecond = 3;
		MyDialog ->msgtype_iswarn = true;
		MyDialog ->Create(IDD_DIALOG1, this);
		MyDialog ->SetWindowTextA("警告信息");
		MyDialog ->SetDlgItemTextA(IDC_STATIC, "需填写订单号！3秒后自动关闭");
		MyDialog ->SetTimer(1, 1000, NULL);
		MyDialog ->ShowWindow(SW_SHOW);
		return;
	}
	string merOrderId = merId.GetBuffer();

	sqlite3 *db = NULL;
	char *zErrMsg = 0;
	int rc;
	string errmsg = "";
	rc = sqlite3_open("poscb.db", &db);
	if (rc)
	{
		errmsg = sqlite3_errmsg(db);
		MyLog::Inst()->Log("ERROR:打开poscb.db数据库失败：" + errmsg + "\n");
		sqlite3_close(db);
		return;
	}else
	{
		MyLog::Inst()->Log("INFO:打开poscb.db数据库成功\n");
	}

	string sqlStr = "SELECT * FROM poscb WHERE billDate between '" + startBillDateStr + "' AND '" + endBillDateStr + "'  AND merOrderId = '"
		+ merOrderId + "';";
	MyLog::Inst()->Log("INFO:" + sqlStr + "\n");
	const char *sql = sqlStr.c_str();
	int nrow = 0, ncolumn = 0; //查询结果集的行数、列数
    char **azResult; //二维数组存放结果
	sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
	
	if (nrow == 0)
	{
		//MessageBoxTimeout(NULL, TEXT("暂无数据!"), TEXT("提示信息"), MB_ICONINFORMATION, GetSystemDefaultLangID(), 5000);
		MessageDialog *MyDialog = new MessageDialog;
		MyDialog ->mySecond = 1;
		MyDialog ->totalSecond = 3;
		MyDialog ->msgtype_iswarn = false;
		MyDialog ->Create(IDD_DIALOG1, this);
		MyDialog ->SetWindowTextA("提示信息");
		MyDialog ->SetDlgItemTextA(IDC_STATIC, "暂无数据！3秒后自动关闭");
		MyDialog ->SetTimer(1, 1000, NULL);
		MyDialog ->ShowWindow(SW_SHOW);
		return;
	}
	
	CString result_merOrderId;
	result_merOrderId.Format(_T("%s"), azResult[41]);
	print_merOrderId = azResult[41];

	CString result_payTime;
	result_payTime.Format(_T("%s"), azResult[44]);
	print_payTime = azResult[44];

	CString result_totalAmount;
	string totalAmountStr = azResult[49];
	int money = atoi(totalAmountStr.c_str());
	double dm = money * 0.01 + 0.005;
	double d = int(dm * 100.0) / 100.0;
	char buf[18];
	sprintf_s(buf, "%.2f", d);
	result_totalAmount = buf;
	print_totalAmount = buf;

	CString result_buyerUserName;
	result_buyerUserName.Format(_T("%s"), azResult[38]);
	print_buyerUserName = azResult[38];

	CString result_merName;
	result_merName.Format(_T("%s"), azResult[54]);
	print_merName = azResult[54];

	CString result_targetSys;
	string targetSysStr = azResult[48];
	string targetType = "";
	if (targetSysStr.find("Alipay") != string::npos ){
		targetType = "支付宝";
	}else if(targetSysStr.find("WXPay") != string::npos)
	{
		targetType = "微信";
	}
	result_targetSys.Format(_T("%s"), targetType.c_str());
	print_targetSys = targetType;

	m_List.InsertItem(0, result_merOrderId);
    m_List.SetItemText(0, 1, result_payTime); 
    m_List.SetItemText(0, 2, result_totalAmount); 
    m_List.SetItemText(0, 3, result_buyerUserName); 
	m_List.SetItemText(0, 4, result_merName); 
    m_List.SetItemText(0, 5, result_targetSys); 

	sqlite3_free_table( azResult );
	sqlite3_close(db);
}

void CsqliteAppDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int index = pNMLV->iItem;
	if( index == -1 )
		return;
	HMENU hMenu = ::CreatePopupMenu();
	AppendMenu( hMenu, MF_STRING, 10001, _T("打印") );
	CPoint pt;
	GetCursorPos(&pt); //获得当前鼠标位置
	UINT Cmd = (UINT)::TrackPopupMenu( hMenu, TPM_LEFTALIGN|TPM_RETURNCMD, pt.x, pt.y, 0, m_hWnd, NULL );//弹出菜单
 
	switch( Cmd )//响应点击的菜单
	{
	case 10001:
		printPoscbData();
		break;
 
	}
	*pResult = 0;
}

void CsqliteAppDlg::printPoscbData(){

	int i = m_List.GetSelectionMark();
	CString CmerOrderId = m_List.GetItemText(i, 0);
	CString CpayTime = m_List.GetItemText(i, 1);
	CString CtotalAmount = m_List.GetItemText(i, 2);
	CString CbuyerUserName = m_List.GetItemText(i, 3);
	CString CmerName = m_List.GetItemText(i, 4);
	CString CtargetSys = m_List.GetItemText(i, 5);
	//写入文件
	ofstream fout;
	//string filePath = "D:\\Cworkspace\\CToBTxt\\result_"+ CmerOrderId +".txt";
	string filePath="receipt.txt";
	fout.open(filePath);
	string payTime = "支付时间：" + CpayTime;
	string totalAmount = "支付金额：" + CtotalAmount;
	string buyerUserName = "购买人：" + CbuyerUserName;
	string merName = "商户名称：" + CmerName;
	string targetSys = "目标系统：" + CtargetSys;
	  
	fout << payTime << endl;
	fout << totalAmount << endl;
	fout << buyerUserName << endl;
	fout << merName << endl;
	fout << targetSys << endl;
	fout.close();
	
	typedef int(_stdcall *reprint)(char* path);
	HINSTANCE reprintDll;
	reprint rfunc=NULL;
	reprintDll = LoadLibrary("reprint.dll");
	rfunc = (reprint)GetProcAddress(reprintDll, "reprint");
	//rfunc(filePath.c_str());
	rfunc("receipt.txt");
	FreeLibrary(reprintDll);
}


void CsqliteAppDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;  
    CRect rc;  
    int m_Row = pNMListView->iItem;//获得选中的行  
    int m_Col = pNMListView->iSubItem;//获得选中列  
    m_List.GetSubItemRect(m_Row,m_Col,LVIR_LABEL,rc);//获得子项的RECT；  
    m_hideEdit.SetParent(&m_List);//转换坐标为列表框中的坐标  
    m_hideEdit.MoveWindow(rc);//移动Edit到RECT坐在的位置;  
    m_hideEdit.SetWindowText(m_List.GetItemText(m_Row,m_Col));//将该子项中的值放在Edit控件中；  
    m_hideEdit.ShowWindow(SW_SHOW);//显示Edit控件；  
    m_hideEdit.SetFocus();//设置Edit焦点  
    m_hideEdit.ShowCaret();//显示光标  
    m_hideEdit.SetSel(-1);//将光标移动到最后  
	*pResult = 0;
}


void CsqliteAppDlg::OnEnKillfocusEdit1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_hideEdit.ShowWindow(SW_HIDE);
}
