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

/* ����ȡ�ô�����Ϣ */
DWORD g_dwErr;

/* ��������Ĵ�С */
const int MAX_SIZE = 40960;

/*
        �˽ṹ�����ڱ���������Ϣ
*/
typedef struct stWeatherInfo
{
    string date;        //����
    string wea;                //����
    string tem;                //�¶�
    string win;                //����
}WeatherInfo, * pWeatherInfo;

/* ���ڴ���THML�е����ݣ�����Ӧ��Ϣ����ṹ���� */
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
    /* ��ʼ�� */
    WSADATA wsdata;
    WSAStartup(MAKEWORD(2, 2), &wsdata);

    const char* hostname = "www.weather.com.cn";
    struct hostent* host = gethostbyname(hostname);

    /* ��ʼ��һ�����ӷ������Ľṹ�� */
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(80);

    /* �˴�Ҳ���Բ�����ô��������Ҫ��gethostbyname������ַpingһ�£��ó�IPҲ�ǿ��Ե� */
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

    /* GET���� */
    const char* bufSned = "GET http://www.weather.com.cn/weather/101200101.shtml\r\n";

    /* ����GET���� */
    if (send(sock, bufSned, strlen(bufSned), 0) > 0) {
       // cout << "send succeed" << endl;
    }
    else {
        g_dwErr = GetLastError();
        //cout << "send error, �����ţ� " << g_dwErr << endl;
        closesocket(sock);
        return "";
    }

    char BufRecv[MAX_SIZE] = {};
    int nLen = 0;
    string HtmlData;

    /* ��ʼ�������� */
    while ((nLen = recv(sock, BufRecv, MAX_SIZE, 0)) > 0) {
        /* ������ƴ�ӳ�string���ͣ���������Ĵ��� */
        HtmlData += BufRecv;
    }

    /* ��ʼ����HTML */
    string Area0 = "<input type=\"hidden\" id=\"hidden_title\" value=\"";
    string Area2 = "\" />";

    string::size_type PosBegin0;
    string::size_type PosBegin;

    string s;
    PosBegin0 = HtmlData.find(Area0);//Area0�ַ����״γ��ֵ�λ��
    PosBegin = HtmlData.find(Area2, PosBegin0);//��Area0�ַ�λ�ô�Ѱ��Area2�ַ�����λ��
    s = HtmlData.substr(PosBegin0+Area0.length(), PosBegin - PosBegin0-Area0.length());//������Ϣ
    /* ����HTML���� */
    QString a=QString::fromLocal8Bit(UtfToGbk(s).data());
    a.replace(QRegExp("[\\s]+")," ");
  QStringList temp=a.split(" ");
   a="";
   for (int index = 0;index < temp.count();index++) {

                    a=a+ "\n"+temp[index];


      }
    return QString(QString::fromLocal8Bit("��������\n����ʱ��")+a);
    /* ����洢���������ֵ�HTML���� */
    closesocket(sock);
    return 0;
}
