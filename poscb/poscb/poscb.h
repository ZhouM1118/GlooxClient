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
	char billBizType[25];
	char buyerId[255];
	char buyerPayAmount[255];
	char buyerUsername[255];
	char couponAmount[255];
	char invoiceAmount[255];
	char settleDate[12];
	char status[255];
	char billQRCode[255];
	char billStatus[255];
	char createTime[25];
	char instMid[255];
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
	{              //类  
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
				if (message.find("<") != string::npos)//假设是心跳信息
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