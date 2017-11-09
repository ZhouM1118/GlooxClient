#pragma once  

#include "../gloox/client.h"
#include "../gloox/messagesessionhandler.h"
#include "../gloox/messageeventhandler.h"
#include "../gloox/messageeventfilter.h"
#include "../gloox/chatstatehandler.h"
#include "../gloox/chatstatefilter.h"
#include "../gloox/connectionlistener.h"
#include "../gloox/disco.h"
#include "../gloox/message.h"
#include "../gloox/gloox.h"
#include "../gloox/lastactivity.h"
#include "../gloox/loghandler.h"
#include "../gloox/logsink.h"
#include "../gloox/connectiontcpclient.h"
#include "../gloox/connectionsocks5proxy.h"
#include "../gloox/connectionhttpproxy.h"
#include "../gloox/messagehandler.h"
#include "../jsoncpp/json.h"
#include "MyLog.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace Json;
using namespace gloox;
using namespace std;

#ifndef _WIN32
# include <unistd.h>
#endif

#include <stdio.h>
#include <string>

#include <cstdio> // [s]print[f]

#if defined( WIN32 ) || defined( _WIN32 )
# include <windows.h>
#endif

#ifdef POSCB_EXPORTS  
#define POSCB_API __declspec(dllexport)  
#else  
#define POSCB_API __declspec(dllimport)  
#endif 

#define COMMENT_CHAR '#'
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
}filein_type;
static char result[4096] = {0};
static int i = 0;
static bool isConnected = false;
static bool isGeted = false;
static map<string, string> m;
static stringstream sstr;
static bool firstConnect = true;
static int times = 0;

namespace poscb
{

	class POSCB_API XmppClient : public MessageSessionHandler, ConnectionListener, LogHandler,
						MessageEventHandler, MessageHandler, ChatStateHandler
	{              //��  
		public:
			XmppClient() : m_session( 0 ), m_messageEventFilter( 0 ), m_chatStateFilter( 0 ) {}
			virtual ~XmppClient() {} 

		public:
			bool ReadConfig(const string & filename, map<string, string> & m);
			bool AnalyseLine(const string & line, string & key, string & value);
			void Trim(string & str);
			bool IsSpace(char c);
			bool IsCommentChar(char c);

			void start(map<string, string> & m);

			string UTF8ToGBK(const char* strUTF8);
			
		private:
			Client *j;
			MessageSession *m_session;
			MessageEventFilter *m_messageEventFilter;
			ChatStateFilter *m_chatStateFilter;

		public:
			// Override ConnectionListener
			virtual void onConnect();
			virtual void onDisconnect(enum gloox::ConnectionError);
			virtual bool onTLSConnect(const struct gloox::CertInfo&);

			// Override MessageSessionHandler
			virtual void handleMessage( const Message& msg, MessageSession * /*session*/ );
			virtual void handleMessageEvent( const JID& from, MessageEventType event );
			virtual void handleChatState( const JID& from, ChatStateType state );
			virtual void handleMessageSession( gloox::MessageSession *session );

			// Override LogHandler
			virtual void handleLog( LogLevel level, LogArea area, const std::string& message )
			{
			  //printf("log: level: %d, area: %d, %s\n", level, area, message.c_str() );
				if (message.find("<") != string::npos)//������������Ϣ
				{
					times = 0;
				}
			  sstr.clear();
			  string levelStr = "";
			  string areaStr = "";
			  sstr<<level;
			  sstr>>levelStr;
			  sstr.clear();
			  sstr<<area;
			  sstr>>areaStr;
			  MyLog::Inst()->Log("INFO:log: level: " + levelStr + ", area: " + areaStr + ", " + message.c_str() + "\n");
			}
	};  
 
	extern "C" POSCB_API char* ConnectOpenFire(char *filein);
	//extern "C" POSCB_API bool getConnectFlag();
	//extern "C" POSCB_API char* getMessage(char *filein);
}