#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include<QString>
#include"qstringlist.h"

#pragma comment(lib, "ws2_32")
using namespace std;

/* 用于取得错误信息 */
DWORD g_dwErr;

/* 保存数组的大小 */
const int MAX_SIZE = 40960;

/*
        此结构体用于保存天气信息
*/
typedef struct stWeatherInfo
{
    string date;        //日期
    string wea;                //天气
    string tem;                //温度
    string win;                //风力
}WeatherInfo, * pWeatherInfo;

/* 用于处理THML中的数据，把相应信息放入结构体中 */
void GetWeather(const string& s);

string UtfToGbk(string strValue)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, strValue.c_str(), -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_UTF8, 0, strValue.c_str(), -1, wstr, len);
    len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
    if (wstr) delete[] wstr;
    return string(str);
}

QString weather()
{
    /* 初始化 */
    WSADATA wsdata;
    WSAStartup(MAKEWORD(2, 2), &wsdata);

    const char* hostname = "www.weather.com.cn";
    struct hostent* host = gethostbyname(hostname);

    /* 初始化一个连接服务器的结构体 */
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(80);

    /* 此处也可以不用这么做，不需要用gethostbyname，把网址ping一下，得出IP也是可以的 */
    serveraddr.sin_addr.S_un.S_addr = *((int*)*host->h_addr_list);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        //cout << "socket error" << endl;
        return "";
    }
    //cout << "socket succeed" << endl;

    if (connect(sock, (struct sockaddr*)&serveraddr, sizeof(sockaddr_in)) == -1) {
        g_dwErr = GetLastError();
        //cout << "connect error" << endl;
        closesocket(sock);
        return "";
    }
    //cout << "connect succeed" << endl;

    /* GET请求 */
    const char* bufSned = "GET http://www.weather.com.cn/weather/101200101.shtml\r\n";

    /* 发送GET请求 */
    if (send(sock, bufSned, strlen(bufSned), 0) > 0) {
       // cout << "send succeed" << endl;
    }
    else {
        g_dwErr = GetLastError();
        //cout << "send error, 错误编号： " << g_dwErr << endl;
        closesocket(sock);
        return "";
    }

    char BufRecv[MAX_SIZE] = {};
    int nLen = 0;
    string HtmlData;

    /* 开始接收数据 */
    while ((nLen = recv(sock, BufRecv, MAX_SIZE, 0)) > 0) {
        /* 把数组拼接成string类型，方便下面的处理 */
        HtmlData += BufRecv;
    }

    /* 开始分析HTML */
    string Area0 = "<input type=\"hidden\" id=\"hidden_title\" value=\"";
    string Area2 = "\" />";

    string::size_type PosBegin0;
    string::size_type PosBegin;

    string s;
    PosBegin0 = HtmlData.find(Area0);//Area0字符串首次出现的位置
    PosBegin = HtmlData.find(Area2, PosBegin0);//从Area0字符位置处寻找Area2字符串的位置
    s = HtmlData.substr(PosBegin0+Area0.length(), PosBegin - PosBegin0-Area0.length());//天气信息
    /* 结束HTML分析 */
    QString a=QString::fromLocal8Bit(UtfToGbk(s).data());
    a.replace(QRegExp("[\\s]+")," ");
  QStringList temp=a.split(" ");
   a="";
   for (int index = 0;index < temp.count();index++) {

                    a=a+ "\n"+temp[index];


      }
    return QString(QString::fromLocal8Bit("今日天气\n更新时间")+a);
    /* 处理存储有天气部分的HTML代码 */
    closesocket(sock);
    return 0;
}
