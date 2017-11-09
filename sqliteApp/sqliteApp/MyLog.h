#pragma once  
#ifndef EASY_LOG_H_8080  
#define EASY_LOG_H_8080  
#include <memory>  
#include <ctime>  
#include <iostream>  
#include <fstream> 
#include <string>
#include <io.h>
#include <direct.h>
#define LOG_PATH "log/"
class MyLog  
{  
public:  
    static MyLog * Inst()
	{  
        if (0 == _instance.get())
		{  
            _instance.reset(new MyLog);  
        }  
        return _instance.get();  
    }  
  
    void Log(std::string msg); // д��־�ķ��� 
	//std::string getDateStr(int type, tm ltm);
private:  
    MyLog(void){}  
    virtual ~MyLog(void){}  
    friend class std::auto_ptr<MyLog>;  
    static std::auto_ptr<MyLog> _instance;
};  
  
std::auto_ptr<MyLog> MyLog::_instance;  

std::string getDateStr(int type, tm ltm)
{
	std::string dateStr = "";
	char yearStr[5], monthStr[3], dayStr[3], hourStr[3], minuteStr[3], secondStr[3];
	
	sprintf_s(yearStr, "%d", ltm.tm_year+1900);              // �ꡣ
	sprintf_s(monthStr, "%d", ltm.tm_mon+1);            // �¡�
	sprintf_s(dayStr, "%d", ltm.tm_mday);                // �ա�
	if(type == 1)
	{
		sprintf_s(hourStr, "%d", ltm.tm_hour);              // ʱ��
		sprintf_s(minuteStr, "%d", ltm.tm_min);          // �֡�
		if (minuteStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
		{
			minuteStr[2] = '\0';
			minuteStr[1] = minuteStr[0];
			minuteStr[0] = '0';
		}
		sprintf_s(secondStr, "%d", ltm.tm_sec);          // �롣
		if (secondStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
		{
			secondStr[2] = '\0';
			secondStr[1] = secondStr[0];
			secondStr[0] = '0';
		}
		char s[23];
		sprintf_s(s, "%s-%s-%s %s:%s:%s : ", yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr);
		dateStr = s;
		return dateStr;
	}
	char a[11];   
	sprintf_s(a, "%s-%s-%s", yearStr, monthStr, dayStr);
	dateStr = a;
	return dateStr;
}
  
void MyLog::Log(std::string loginfo) 
{  
	time_t now;
	tm ltm;
	time(&now);
	localtime_s(&ltm, &now);
    std::ofstream ofs;  
	if (_access(LOG_PATH, 0) != 0)
	{
		_mkdir(LOG_PATH);
	}
	ofs.open(LOG_PATH + getDateStr(0, ltm) + ".log", std::ofstream::app);  
	loginfo += getDateStr(1, ltm);
    ofs.write(loginfo.c_str(), loginfo.size());   
    ofs.close();  
}  
#endif  