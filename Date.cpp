#include "Date.h"
#include <QDebug>
#define T_D_YAER   1924 //  ��ɵ�֧��ʼ��������
//ÿ�괺�ڶ�Ӧ�Ĺ�������
static const int springFestival[] = {
    130,217,206,                                // 1968,1969,1970
    127,215,203,123,211,131,218,207,128,216,    // 1971--1980
    205,125,213,202,220,209,219,217,206,127,    // 1981---1990
    215,204,123,210,131,219,207,128,216,205,    // 1991--2000
    124,212,201,122,209,129,218,207,126,214,    // 2001--2010
    203,123,210,131,219,208,128,216,205,125,    // 2011--2020                                       //2011--2020
    212,201,122,210,129,217,206,126,213,203,    // 2021--2030
    123,211,131,219,208,128,215,204,124,212     // 2031--2040
};

//16--18λ��ʾ���£�0--12λ��ʾũ��ÿ�µ����ݣ���λ��ʾ1�£���λ��ʾ12�£�ũ�����¾ͻ��һ���£�
static const int  nLunarData[] = {
    461653,1386,2413,                                            // 1968,1969,1970
    330077,1197,2637,268877,3365,531109,2900,2922,398042,2395,   // 1971--1980
    1179,267415,2635,661067,1701,1748,398772,2742,2391,330031,   // 1981---1990
    1175,1611,200010,3749,527717,1452,2742,332397,2350,3222,     // 1991--2000
    268949,3402,3493,133973,1386,464219,605,2349,334123,2709,    // 2001--2010
    2890,267946,2773,592565,1210,2651,395863,1323,2707,265877,   // 2011--2020
    1706,2773,133557,1206,398510,2638,3366,335142,3411,1450,     // 2021 -- 2030
    200042,2413,723293,1197,2637,399947,3365,3410,334676,2906    // 2031 -- 2040
};

static const int chineseTwentyFourData[] = {
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x69,0x78,0x87,     // 1970
    0x96,0xB4,0x96,0xA6,0x97,0x97,0x78,0x79,0x79,0x69,0x78,0x77,     // 1971
    0x96,0xA4,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 1972
    0xA5,0xB5,0x96,0xA5,0xA6,0x96,0x88,0x78,0x78,0x78,0x87,0x87,     // 1973
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x69,0x78,0x87,     // 1974
    0x96,0xB4,0x96,0xA6,0x97,0x97,0x78,0x79,0x78,0x69,0x78,0x77,     // 1975
    0x96,0xA4,0xA5,0xB5,0xA6,0xA6,0x88,0x89,0x88,0x78,0x87,0x87,     // 1976
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     // 1977
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x79,0x78,0x87,     // 1978
    0x96,0xB4,0x96,0xA6,0x96,0x97,0x78,0x79,0x78,0x69,0x78,0x77,     // 1979
    0x96,0xA4,0xA5,0xB5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 1980
    0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x77,0x87,     // 1981
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x79,0x77,0x87,     // 1982
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x78,0x79,0x78,0x69,0x78,0x77,     // 1983
    0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x87,     // 1984
    0xA5,0xB4,0xA6,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     // 1985
    0xA5,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x79,0x77,0x87,     // 1986
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x79,0x78,0x69,0x78,0x87,     // 1987
    0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 1988
    0xA5,0xB4,0xA5,0xA5,0xA6,0x96,0x88,0x88,0x88,0x78,0x87,0x87,     // 1989
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x79,0x77,0x87,     // 1990
    0x95,0xB4,0x96,0xA5,0x86,0x97,0x88,0x78,0x78,0x69,0x78,0x87,     // 1991
    0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 1992
    0xA5,0xB3,0xA5,0xA5,0xA6,0x96,0x88,0x88,0x88,0x78,0x87,0x87,     // 1993
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x78,0x87,0x87,     // 1994
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x76,0x78,0x69,0x78,0x87,     // 1995
    0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 1996
    0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 1997
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x78,0x87,0x87,     // 1998
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x69,0x78,0x87,     // 1999
    0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 2000
    0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 2001
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x78,0x87,0x87,     // 2002
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x69,0x78,0x87,     // 2003
    0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 2004
    0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 2005
    0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     // 2006
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x69,0x78,0x87,     // 2007
    0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x87,0x78,0x87,0x86,     // 2008
    0xA5,0xB3,0xA5,0xB5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 2009
    0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     // 2010
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x79,0x78,0x87,     // 2011
    0x96,0xB4,0xA5,0xB5,0xA5,0xA6,0x87,0x88,0x87,0x78,0x87,0x86,     // 2012
    0xA5,0xB3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x87,     // 2013
    0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     // 2014
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x79,0x77,0x87,     // 2015
    0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x87,0x88,0x87,0x78,0x87,0x86,     // 2016
    0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x87,     // 2017
    0xA5,0xB4,0xA6,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     // 2018
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x79,0x77,0x87,     // 2019
    0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x86,     // 2020
    0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 2021
    0xA5,0xB4,0xA5,0xA5,0xA6,0x96,0x88,0x88,0x88,0x78,0x87,0x87,     // 2022
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x79,0x77,0x87,     // 2023
    0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x96,     // 2024
    0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 2025
    0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 2026
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x78,0x87,0x87,     // 2027
    0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x96,     // 2028
    0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 2029
    0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 2030
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x78,0x87,0x87,     // 2031
    0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x96,     // 2032
    0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x86,     // 2033
    0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x78,0x88,0x78,0x87,0x87,     // 2034
    0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     // 2035
    0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x96,     // 2036
    0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 2037
    0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87      // 2038
};

static const char* s_pchDayName[] = {
    ("*"),
    ("��һ"), ("����"), ("����"), ("����"), ("����"),
    ("����"), ("����"), ("����"), ("����"), ("��ʮ"),
    ("ʮһ"), ("ʮ��"), ("ʮ��"), ("ʮ��"), ("ʮ��"),
    ("ʮ��"), ("ʮ��"), ("ʮ��"), ("ʮ��"), ("��ʮ"),
    ("إһ"), ("إ��"), ("إ��"), ("إ��"), ("إ��"),
    ("إ��"), ("إ��"), ("إ��"), ("إ��"), ("��ʮ")
};

/*ũ���·���*/
static const char* s_pchMonName[] = {
    ("*"),
    ("����"), ("����"), ("����"), ("����"),
    ("����"), ("����"), ("����"), ("����"),
    ("����"), ("ʮ��"), ("����"), ("����")
};

// 24����
static const char* s_pchSolarTerm[] = {
    ("С��"), ("��"), ("����"), ("��ˮ"), ("����"), ("����"), ("����"), ("����"),
    ("����"), ("С��"), ("â��"), ("����"), ("С��"), ("����"), ("����"), ("����"),
    ("��¶"), ("���"), ("��¶"), ("˪��"), ("����"), ("Сѩ"), ("��ѩ"), ("����")
};


// ����㷨
static const char* s_pchTiangan[] = {
    ("��"), ("��"), ("��"), ("��"), ("��"),
    ("��"), ("��"), ("��"), ("��"), ("��"),
};

// ��������
static const char* s_pchAnimal[] = {
    ("��"), ("ţ"), ("��"), ("��"), ("��"), ("��"),
    ("��"), ("��"), ("��"), ("��"), ("��"), ("��"),
};

// ��ַ�㷨
static const char* s_pchDizhi[] = {
    ("��"), ("��"), ("��"), ("î"), ("��"), ("��"),
    ("��"), ("δ"), ("��"), ("��"), ("��"), ("��"),
};

/*����ÿ��ǰ�������*/
int monthAdd[] = {
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};


Date::Date(QObject* parent) : QObject(parent)
{

}

/**
 * @brief Date::getSpringFestivalMonth ��ȡ���괺���Ǽ��¼���
 * @param year
 * @return
 */
quint16 Date::getSpringFestivalDate(int year)
{
    int nTemp = year - 1968;
    int springFestivalMonth = springFestival[nTemp] / 100;
    int springFestivalDay = springFestival[nTemp] % 100;
    qDebug() << springFestivalMonth << springFestivalDay;

    return (springFestivalMonth << 8) | springFestivalDay;
}

int Date::getFirstDayOfWeek(int year, int month)
{
    int week = 0;
    // ��ȡ����1��1�������ڼ�
    week = (year + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400) % 7;
    week += getTotalMonthDays(year, month);
    return week % 7;
}

int Date::getTotalMonthDays(int year, int month)
{
    int nDays = 0;
    int nLoopDay = isLoopYaer(year) ? 1 : 0;
    switch (month) {
    case  1: nDays = 0;            break;
    case  2: nDays = 31;            break;
    case  3: nDays = 59 + nLoopDay; break;
    case  4: nDays = 90 + nLoopDay; break;
    case  5: nDays = 120 + nLoopDay; break;
    case  6: nDays = 151 + nLoopDay; break;
    case  7: nDays = 181 + nLoopDay; break;
    case  8: nDays = 212 + nLoopDay; break;
    case  9: nDays = 243 + nLoopDay; break;
    case 10: nDays = 273 + nLoopDay; break;
    case 11: nDays = 304 + nLoopDay; break;
    case 12: nDays = 334 + nLoopDay; break;
    default: nDays = 0; break;
    }
    return nDays;
}

int Date::getMonthDays(int year, int month)
{
    int nDays = 0;
    int nLoopDay = isLoopYaer(year) ? 1 : 0;
    switch (month) {
    case  1: nDays = 31;            break;
    case  2: nDays = 28 + nLoopDay; break;
    case  3: nDays = 31;            break;
    case  4: nDays = 30;            break;
    case  5: nDays = 31;            break;
    case  6: nDays = 30;            break;
    case  7: nDays = 31;            break;
    case  8: nDays = 31;            break;
    case  9: nDays = 30;            break;
    case 10: nDays = 31;            break;
    case 11: nDays = 30;            break;
    case 12: nDays = 31;            break;
    default: nDays = 30;            break;
    }

    return nDays;
}

// �ж��Ƿ�������
bool Date::isLoopYaer(int year)
{
    return (((0 == (year % 4)) && (0 != (year % 100))) || (0 == (year % 400)));
}

/**
 * @brief Date::getLunarDate ����ũ��
 * @param year  ��
 * @param month ��
 * @param day ��
 * @return
 */
QString Date::getLunarDate(int year, int month, int day) {
    int nTheDate, nIsEnd, nMonTemp, k, n, nBit;
    // �Ȼ�ȡ��������
    QString strDate = holiday(month, day);
    // ����24����
    QString strSolarTerms = solarTerms(year, month, day);

    /*���ڼ���ũ������õ��괺�ڵĹ������ڣ����磺2015�괺������Ϊ��2��19�գ�����
            �Դ�Ϊ�ֽ�㣬2.19ǰ���ũ����2014��ũ������2014��ũ�����������㣩��
            2.19�Լ�֮������ڣ�ũ��Ϊ2015��ũ������2015��ũ�����������㣩��*/
    nMonTemp = year - 1968;
    int springFestivalMonth = springFestival[nMonTemp] / 100;
    int springFestivalDaty = springFestival[nMonTemp] % 100;

    if (month < springFestivalMonth)
    {
        nMonTemp--;
        nTheDate = 365 * 1 + day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;

        if ((!(year % 4)) && (month > 2))
            nTheDate = nTheDate + 1;

        if ((!((year - 1) % 4)))
            nTheDate = nTheDate + 1;
    }
    else if (month == springFestivalMonth)
    {
        if (day < springFestivalDaty) {
            nMonTemp--;
            nTheDate = 365 * 1 + day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;

            if ((!(year % 4)) && (month > 2))
                nTheDate = nTheDate + 1;

            if ((!((year - 1) % 4)))
                nTheDate = nTheDate + 1;
        }
        else {
            nTheDate = day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;

            if ((!(year % 4)) && (month > 2))
                nTheDate = nTheDate + 1;
        }
    }
    else {
        nTheDate = day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;
        if ((!(year % 4)) && (month > 2))
            nTheDate = nTheDate + 1;
    }
    /*--����ũ����ɡ���֧���¡���---*/
    nIsEnd = 0;

    while (nIsEnd != 1) {
        if (nLunarData[nMonTemp] < 4095)
            k = 11;
        else
            k = 12;
        n = k;
        while (n >= 0) {
            // ��ȡwNongliData(m)�ĵ�n��������λ��ֵ
            nBit = nLunarData[nMonTemp];

            nBit = nBit >> n;
            nBit = nBit % 2;
            if (nTheDate <= (29 + nBit)) {
                nIsEnd = 1;
                break;
            }

            nTheDate = nTheDate - 29 - nBit;
            n = n - 1;
        }

        if (nIsEnd)
            break;

        nMonTemp = nMonTemp + 1;
    }

    // ũ����������
    year = 1969 + nMonTemp - 1;
    month = k - n + 1;
    day = nTheDate;

    if (k == 12) {
        if (month == (nLunarData[nMonTemp] / 65536) + 1)
            month = 1 - month;
        else if (month > (nLunarData[nMonTemp] / 65536) + 1)
            month = month - 1;
    }

    // ��ʾװ����ũ��
    // only day == 1 ,return month name
    if (1 == day) {
        if (month < 1) {
            strDate = QString::fromLocal8Bit("��") + QString::fromLocal8Bit(s_pchMonName[month * -1]);
            return strDate;
        }

        // ��������
        if ("" != strDate) return strDate;

        // ����ũ������
        strDate = lunarFestival(month, day);

        // ����н��գ�ֱ����ʾ
        if ("" == strDate) {
            // ������첻��24��������ʾũ������
            strDate = strSolarTerms;
            if ("" == strDate) {
                strDate = QString::fromLocal8Bit(s_pchMonName[month]);
            }
        }

    }
    else {
        // ��������
        if ("" != strDate) return strDate;

        // ����ũ������
        strDate = lunarFestival(month, day);
        // ����н��գ�ֱ����ʾ
        if ("" == strDate) {
            // ������첻��24��������ʾũ������
            strDate = strSolarTerms;
            if ("" == strDate) {
                strDate = QString::fromLocal8Bit(s_pchDayName[day]);
            }
        }
    }

    return strDate;
}

/**
 * @brief Date::getLunarMonAndDay ��Ӧ���ʱ��ũ����ʾ
 * @param year
 * @param month
 * @param day
 * @return
 */
QString Date::getLunarMonAndDay(int year, int month, int day)
{
    int nTheDate, nIsEnd, nMonTemp, k, n, nBit;
    QString strDate = "";
    /*���ڼ���ũ������õ��괺�ڵĹ������ڣ����磺2015�괺������Ϊ��2��19�գ�����
            �Դ�Ϊ�ֽ�㣬2.19ǰ���ũ����2014��ũ������2014��ũ�����������㣩��
            2.19�Լ�֮������ڣ�ũ��Ϊ2015��ũ������2015��ũ�����������㣩��*/
    nMonTemp = year - 1968;
    int springFestivalMonth = springFestival[nMonTemp] / 100;
    int springFestivalDaty = springFestival[nMonTemp] % 100;

    if (month < springFestivalMonth)
    {
        nMonTemp--;
        nTheDate = 365 * 1 + day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;

        if ((!(year % 4)) && (month > 2))
            nTheDate = nTheDate + 1;

        if ((!((year - 1) % 4)))
            nTheDate = nTheDate + 1;
    }
    else if (month == springFestivalMonth)
    {
        if (day < springFestivalDaty) {
            nMonTemp--;
            nTheDate = 365 * 1 + day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;

            if ((!(year % 4)) && (month > 2))
                nTheDate = nTheDate + 1;

            if ((!((year - 1) % 4)))
                nTheDate = nTheDate + 1;
        }
        else {
            nTheDate = day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;

            if ((!(year % 4)) && (month > 2))
                nTheDate = nTheDate + 1;
        }
    }
    else {
        nTheDate = day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;
        if ((!(year % 4)) && (month > 2))
            nTheDate = nTheDate + 1;
    }
    /*--����ũ����ɡ���֧���¡���---*/
    nIsEnd = 0;

    while (nIsEnd != 1) {
        if (nLunarData[nMonTemp] < 4095)
            k = 11;
        else
            k = 12;
        n = k;
        while (n >= 0) {
            // ��ȡwNongliData(m)�ĵ�n��������λ��ֵ
            nBit = nLunarData[nMonTemp];

            nBit = nBit >> n;
            nBit = nBit % 2;
            if (nTheDate <= (29 + nBit)) {
                nIsEnd = 1;
                break;
            }

            nTheDate = nTheDate - 29 - nBit;
            n = n - 1;
        }

        if (nIsEnd)
            break;

        nMonTemp = nMonTemp + 1;
    }

    // ũ����������
    year = 1969 + nMonTemp - 1;
    month = k - n + 1;
    day = nTheDate;

    if (k == 12) {
        if (month == (nLunarData[nMonTemp] / 65536) + 1)
            month = 1 - month;
        else if (month > (nLunarData[nMonTemp] / 65536) + 1)
            month = month - 1;
    }

    // ��ʾװ����ũ��
    // only day == 1 ,return month name
    if (1 == day) {
        if (month < 1) {
            strDate = QString::fromLocal8Bit("��") + QString::fromLocal8Bit(s_pchMonName[month * -1]);
            return strDate;
        }

        strDate = QString::fromLocal8Bit(s_pchMonName[month]);

    }
    else {
        strDate = QString::fromLocal8Bit(s_pchMonName[month]) + QString::fromLocal8Bit(s_pchDayName[day]);
    }

    return strDate;
}

/**
 * @brief Date::getLunarTime  ���������ʲô���� ��������
 * @param year
 * @return
 */
QString Date::getLunarTime(int year)
{
    int ntemp = 0;
    // ũ��ʱ��
    QString strTime = "";
    if (year > T_D_YAER) {
        ntemp = year - T_D_YAER;
        strTime.append(QString::fromLocal8Bit(s_pchTiangan[ntemp % 10]));
        strTime.append(QString::fromLocal8Bit(s_pchDizhi[ntemp % 12]));
        strTime.append(QString::fromLocal8Bit(s_pchAnimal[ntemp % 12]));
        strTime.append(QString::fromLocal8Bit("��"));
    }

    return strTime;
}


/**
 * @brief Date::holiday ��������
 * @param month
 * @param day
 * @return
 */
QString Date::holiday(int month, int day)
{
    int temp = (month << 8) | day;
    QString strHoliday = "";
    switch (temp) {
    case 0x0101: strHoliday = QString::fromLocal8Bit("Ԫ��");  break;
    case 0x020E: strHoliday = QString::fromLocal8Bit("���˽�"); break;
    case 0x0308: strHoliday = QString::fromLocal8Bit("��Ů��"); break;
    case 0x0401: strHoliday = QString::fromLocal8Bit("���˽�"); break;
    case 0x0501: strHoliday = QString::fromLocal8Bit("�Ͷ���"); break;
    case 0x0504: strHoliday = QString::fromLocal8Bit("�����"); break;
    case 0x0601: strHoliday = QString::fromLocal8Bit("��ͯ��"); break;
    case 0x0701: strHoliday = QString::fromLocal8Bit("������"); break;
    case 0x0801: strHoliday = QString::fromLocal8Bit("������"); break;
    case 0x090A: strHoliday = QString::fromLocal8Bit("��ʦ��"); break;
    case 0x0A01: strHoliday = QString::fromLocal8Bit("�����"); break;
    case 0x0C18: strHoliday = QString::fromLocal8Bit("ʥ����"); break;
    case 0x0405: strHoliday = QString::fromLocal8Bit("������"); break;

    default: break;
    }

    return strHoliday;
}

/**
 * @brief Date::chineseTwentyFourDay ����24����
 * @param year
 * @param month
 * @param day
 * @return
 */
QString Date::solarTerms(int year, int month, int day) {
    int dayTemp = 0;
    int index = (year - 1970) * 12 + month - 1;

    if (day < 15) {
        dayTemp = 15 - day;
        if ((chineseTwentyFourData[index] >> 4) == dayTemp)
            return QString::fromLocal8Bit(s_pchSolarTerm[2 * (month - 1)]);
        else
            return "";

    }
    else if (day > 15) {
        dayTemp = day - 15;
        if ((chineseTwentyFourData[index] & 0x0f) == dayTemp)
            return QString::fromLocal8Bit(s_pchSolarTerm[2 * (month - 1) + 1]);
    }

    return "";
}

/**
 * @brief Date::lunarFestival ũ�����ڽ���
 * @param month
 * @param day
 * @return ����
 */
QString Date::lunarFestival(int month, int day) {
    int temp = (month << 8) | day;
    QString strFestival = "";
    switch (temp) {
    case 0x0101: strFestival = QString::fromLocal8Bit("����");  break;
    case 0x010F: strFestival = QString::fromLocal8Bit("Ԫ����"); break;
    case 0x0202: strFestival = QString::fromLocal8Bit("��̧ͷ"); break;
    case 0x0505: strFestival = QString::fromLocal8Bit("�����"); break;
    case 0x0707: strFestival = QString::fromLocal8Bit("��Ϧ��"); break;
    case 0x080F: strFestival = QString::fromLocal8Bit("�����"); break;
    case 0x0909: strFestival = QString::fromLocal8Bit("������"); break;
    case 0x0C08: strFestival = QString::fromLocal8Bit("���˽�"); break;
    default: break;
    }

    return strFestival;
}

