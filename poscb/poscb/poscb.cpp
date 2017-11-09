#include "poscb.h" 
#include "MessageBoxAutoClose.h"

#include <shellapi.h>

namespace poscb
{
	bool XmppClient::ReadConfig(const string & filename, map<string, string> & m)
	{
		printf( "==================读取配置文件==================\n" );
		MyLog::Inst()->Log("INFO:读取配置文件\n");
		m.clear();
		ifstream infile(filename.c_str());
		if (!infile) {
			printf( "==================配置文件打开失败，请重试！==================");
			MyLog::Inst()->Log("ERROR:配置文件打开失败，请重试！\n");
			Sleep(2000);
			return false;
		}
		string line, key, value;
		while (getline(infile, line)) {
			if (AnalyseLine(line, key, value)) {
				m[key] = value;
			}
		}
    
		infile.close();
		return true;
	}

	bool XmppClient::AnalyseLine(const string & line, string & key, string & value)
	{
		if (line.empty())
			return false;
		int pos = 0;
		if (line.find(COMMENT_CHAR) == 0 || line.find("[") == 0) 
		{
			return false;// 行的第一个字符是注释字符或“[”，则忽略
		}
    
		if ((pos = line.find('=')) == -1){
			return false;  // 没有=号
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

	//剔除这一行的空格或换行
	void XmppClient::Trim(string & str)
	{
		if (str.empty()) {
			return;
		}
		int i, start_pos, end_pos;
		//剔除这一行开头部分的空格或换行
		for (i = 0; i < str.size(); ++i) {
			if (!IsSpace(str[i])) {
				break;
			}
		}
		if (i == str.size()) { // 全部是空白字符串
			str = "";
			return;
		}
    
		start_pos = i;
		//剔除这一行结尾部分的空格或换行
		for (i = str.size() - 1; i >= 0; --i) {
			if (!IsSpace(str[i])) {
				break;
			}
		}
		end_pos = i;
    
		str = str.substr(start_pos, end_pos - start_pos + 1);
	}

	bool XmppClient::IsSpace(char c)
	{
		if (' ' == c || '\t' == c)
			return true;
		return false;
	}

	bool XmppClient::IsCommentChar(char c)
	{
		switch(c) {
			case COMMENT_CHAR:
				return true;
			default:
				return false;
		}
	} 

	string XmppClient::UTF8ToGBK(const char* strUTF8)  
	{  
		int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);  
		wchar_t* wszGBK = new wchar_t[len+1];  
		memset(wszGBK, 0, len*2+2);  
		MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);  
		len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);  
		char* szGBK = new char[len+1];  
		memset(szGBK, 0, len+1);  
		WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);  
		string strTemp(szGBK);  
		if(wszGBK) delete[] wszGBK;  
		if(szGBK) delete[] szGBK;  
		return strTemp;  
	}

	void XmppClient::start(map<string, string> & m)
	{
		gloox::JID jid( m["XMPP_NAME"]+"@"+m["XMPP_IP"] );
		//j = new gloox::Client( jid, m["XMPP_PASSWD"] );
		string port = m["XMPP_PORT"];
		j = new gloox::Client( jid, m["XMPP_PASSWD"], atoi(port.c_str()));
		j->registerConnectionListener( this );
		j->registerMessageSessionHandler( this, 0 );
		j->disco()->setVersion( "messageTest", GLOOX_VERSION, "Linux" );
		j->disco()->setIdentity( "client", "bot" );
		j->disco()->addFeature( XMLNS_CHAT_STATES );
		StringList ca;
		ca.push_back( "/path/to/cacert.crt" );
		j->setCACerts( ca );

		j->logInstance().registerLogHandler( LogLevelDebug, LogAreaAll, this );

		//非阻塞方式连接，需自主调用recv()接收数据
		if( j->connect( false ) )
		{
			int i = 0;
			ConnectionError ce = ConnNoError;
			//无限循环监听
			while( ce == ConnNoError )
			{
				if(isGeted)
				{
					return;
				}
				if(isConnected)
				{
					sstr.clear();
					sstr<<times;
					string timesstr = "";
					sstr >> timesstr;
					MyLog::Inst()->Log("INFO:times="+timesstr+"\n");
					if (times > 15)
					{
						isConnected = false;
						times = 0;
						delete( j );
						return;
					}
					times++;
				}
				sstr.clear();
				sstr<<i;
				string istr = "";
				sstr >> istr;
				MyLog::Inst()->Log("INFO:第"+istr+"次循环监听\n");
				ce = j->recv(10000000);
				sstr.clear();
				sstr<<ce;
				string cestr = "";
				sstr >> cestr;
				MyLog::Inst()->Log("INFO:ce = " + cestr + "\n");
				i++;
			}
			printf( "ce: %d\n", ce );
			sstr.clear();
			sstr<<ce;
			string cestr = "";
			sstr >> cestr;
			MyLog::Inst()->Log("ERROR:ce = " + cestr + "\n");
		}

		delete( j );
	}

	void XmppClient::onConnect()
	{
		printf( "==================连接成功==================\n" );
		MyLog::Inst()->Log("INFO:连接成功\n");
		isConnected = true;
		//MessageBox(NULL, TEXT("连接成功"), TEXT("提示信息"), MB_OK);
		if (firstConnect)
		{
			
			ShellExecute(NULL, TEXT("open"), TEXT("message.exe"), TEXT("1 0"), NULL, SW_SHOW);
			firstConnect = false;
		}
		
		//HWND wnd = GetConsoleWindow();
		//ShowWindow(wnd, SW_HIDE);
		//ShowWindow(wnd,SW_SHOWMINNOACTIVE);
	}

	void XmppClient::onDisconnect( ConnectionError e )
	{
		printf( "==================连接失败==================\n" );
		MyLog::Inst()->Log("ERROR:连接失败\n");
		isConnected = false;
		firstConnect = true;
		if( e == ConnAuthenticationFailed )
		{
			printf( "auth failed. reason: %d\n", j->authError() );
			sstr.clear();
			string authErrorStr = "";
			sstr<<j->authError();
			sstr>>authErrorStr;
			MyLog::Inst()->Log("ERROR:auth failed. reason:" + authErrorStr + "\n");
		}
		Sleep( 10000 );
		//delete(j);
	}

	bool XmppClient::onTLSConnect( const CertInfo& info )
	{
		time_t from( info.date_from );
		time_t to( info.date_to );
		
		printf( "status: %d\nissuer: %s\npeer: %s\nprotocol: %s\nmac: %s\ncipher: %s\ncompression: %s\n",
				info.status, info.issuer.c_str(), info.server.c_str(),
				info.protocol.c_str(), info.mac.c_str(), info.cipher.c_str(),
				info.compression.c_str() );
		printf( "from: %s", ctime( &from ) );
		printf( "to:   %s", ctime( &to ) );
		sstr.clear();
		string statusStr = "";
		sstr<<info.status;
		sstr>>statusStr;
		MyLog::Inst()->Log("INFO:status: "+ statusStr + ",issuer: " + info.issuer + ",peer: " + info.server
			+ ",protocol: " + info.protocol + ",mac: " + info.mac + ",cipher: " + info.cipher
			+ ",compression: " + info.compression + ",from: " + ctime( &from ) + ",to: " + ctime( &to ) + "\n");
		return true;
	}

	//接收到信息时会触发该方法
	void XmppClient::handleMessage( const Message& msg, MessageSession * /*session*/ )
	{
		printf( "type: %d, subject: %s, message: %s, thread id: %s\n", msg.subtype(),
				msg.subject().c_str(), UTF8ToGBK(msg.body().c_str()), msg.thread().c_str() );
		sstr.clear();
		string statusStr = "";
		sstr<<msg.subtype();
		sstr>>statusStr;
		MyLog::Inst()->Log("INFO:type: "+ statusStr + ",subject: " + msg.subject() + ",message: " + UTF8ToGBK(msg.body().c_str())
			+ ",thread id: " + msg.thread() + "\n");
		//解析json信息数据，组成签购单小票
		Json::Reader reader;
		Json::Value value;
		Json::Value payloadValue;
		Json::Value billPaymentValue;
		if(!reader.parse(UTF8ToGBK(msg.body().c_str()), value))
		{
			printf("==================解析body_json数据失败==================\n");
			MyLog::Inst()->Log("ERROR:解析body_json数据失败\n");
			return;
		}
	 
		//const char* totalAmount = value["payload"]["billPayment"]["totalAmount"].asCString();
		int totalAmountInt = value["payload"]["billPayment"]["totalAmount"].asInt();
		stringstream ta;
		string totalAmountStr;
		ta << totalAmountInt;
		ta >> totalAmountStr;
		int buyerPayAmountInt = value["payload"]["billPayment"]["buyerPayAmount"].asInt();
		stringstream bpa;
		string buyerPayAmountStr;
		bpa << buyerPayAmountInt;
		bpa >> buyerPayAmountStr;
		int couponAmountInt = value["payload"]["billPayment"]["couponAmount"].asInt();
		stringstream ca;
		string couponAmountStr;
		ca << couponAmountInt;
		ca >> couponAmountStr;
		int invoiceAmountInt = value["payload"]["billPayment"]["invoiceAmount"].asInt();
		stringstream ia;
		string invoiceAmountStr;
		ia << invoiceAmountInt;
		ia >> invoiceAmountStr;

		const char* billDate = value["payload"]["billDate"].asCString();
		const char* billDesc = value["payload"]["billDesc"].asCString();
		const char* billNo = value["payload"]["billNo"].asCString();

		const char* billBizType = value["payload"]["billPayment"]["billBizType"].asCString();
		const char* buyerId = value["payload"]["billPayment"]["buyerId"].asCString();
		const char* buyerUsername = value["payload"]["billPayment"]["buyerUsername"].asCString();
		const char* merOrderId = value["payload"]["billPayment"]["merOrderId"].asCString();
		const char* paySeqId = value["payload"]["billPayment"]["paySeqId"].asCString();
		const char* payDetail = value["payload"]["billPayment"]["payDetail"].asCString();
		const char* payTime = value["payload"]["billPayment"]["payTime"].asCString();
		const char* settleDate = value["payload"]["billPayment"]["settleDate"].asCString();
		const char* status = value["payload"]["billPayment"]["status"].asCString();
		const char* targetOrderId = value["payload"]["billPayment"]["targetOrderId"].asCString();
		const char* targetSys = value["payload"]["billPayment"]["targetSys"].asCString();

		MyLog::Inst()->Log("INFO:解析JSON数据：billDate=" + value["payload"]["billDate"].asString()
						+ ",billDesc=" + value["payload"]["billDesc"].asString()
						+ ",billNo=" + value["payload"]["billNo"].asString()
						+ ",billBizType=" + value["payload"]["billPayment"]["billBizType"].asString()
						+ ",buyerId=" + value["payload"]["billPayment"]["buyerId"].asString()
						+ ",buyerPayAmount=" + buyerPayAmountStr
						+ ",buyerUsername=" + value["payload"]["billPayment"]["buyerUsername"].asString()
						+ ",couponAmount=" + couponAmountStr
						+ ",billQRCode=" + value["payload"]["billQRCode"].asString()
						+ ",billStatus=" + value["payload"]["billStatus"].asString() 
						+ ",createTime=" + value["payload"]["createTime"].asString()
						+ ",instMid=" + value["payload"]["instMid"].asString() 
						+ ",merName=" + value["payload"]["merName"].asString()
						+ ",mid=" + value["payload"]["mid"].asString()
						+ ",notifyId=" + value["payload"]["notifyId"].asString()
						+ ",tid=" + value["payload"]["tid"].asString() 
						+ ",timestamp=" + value["timestamp"].asString()
						+ ",type=" + value["type"].asString()
						+ "\n");

		filein_type message;

		strcpy_s(message.billDate, billDate);
		strcpy_s(message.billDesc, billDesc);
		strcpy_s(message.billNo, billNo);

		char* filein = result;
		memcpy(filein, &message, sizeof(message));
		isGeted = true;
		//写入文件
		/*
		ofstream fout;
		fout.open("D:\\Cworkspace\\CToBTxt\\result_"+value["payload"]["billNo"].asString()+".txt");

		fout << billNo << endl;
		fout << merOrderId << endl;
		fout << paySeqId << endl;
		fout << payTime << endl;
		fout << targetSys << endl;
		fout.close();*/

		m_messageEventFilter->raiseMessageEvent( MessageEventDisplayed );
	#if defined( WIN32 ) || defined( _WIN32 )
		Sleep( 1000 );
	#else
		sleep( 1 );
	#endif
		m_messageEventFilter->raiseMessageEvent( MessageEventComposing );
		m_chatStateFilter->setChatState( ChatStateComposing );
	#if defined( WIN32 ) || defined( _WIN32 )
		Sleep( 2000 );
	#else
		sleep( 2 );
	#endif
		/*
		m_session->send( re, sub );

		if( msg.body() == "quit" )
		j->disconnect();*/
	}

	void XmppClient::handleMessageEvent( const JID& from, MessageEventType event )
	{
		printf( "==================received event: %d from: %s\n", event, from.full().c_str() );
		string eventStr = "";
		sstr.clear();
		sstr<<event;
		sstr>>eventStr;
		MyLog::Inst()->Log("INFO:received event: " + eventStr + ",from:" + from.full() + "\n");
	}

	void XmppClient::handleChatState( const JID& from, ChatStateType state )
	{
		printf( "==================received state: %d from: %s\n", state, from.full().c_str() );
		string stateStr = "";
		sstr.clear();
		sstr<<state;
		sstr>>stateStr;
		MyLog::Inst()->Log("INFO:received event: " + stateStr + ",from:" + from.full() + "\n");
	}

	void XmppClient::handleMessageSession( MessageSession *session )
	{
		printf( "==================接收到新信息==================\n");
		MyLog::Inst()->Log("INFO:接收到新信息\n");
		// this example can handle only one session. so we get rid of the old session 
		j->disposeMessageSession( m_session );
		m_session = session;
		m_session->registerMessageHandler( this );
		m_messageEventFilter = new MessageEventFilter( m_session );
		m_messageEventFilter->registerMessageEventHandler( this );
		m_chatStateFilter = new ChatStateFilter( m_session );
		m_chatStateFilter->registerChatStateHandler( this );
	}

	char* ConnectOpenFire(char *filein)
	{
		isGeted = false;
		XmppClient *r = new XmppClient();
		if (isConnected)
		{
			r->start(m);
		//}else if (r->ReadConfig("D:\\Cworkspace\\poscb\\Debug\\Pos.ini", m))
		}else if (r->ReadConfig("Pos.ini", m))
		{
			printf("===================连接失败，重新连接========================\n");
			MyLog::Inst()->Log("INFO:连接失败，重新连接\n");
			r->start(m);
			//delete( r );
		}
		while (isConnected && isGeted)
		{
			return result;
		}
	}
}