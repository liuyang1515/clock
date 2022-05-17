#ifndef DEBUG_H
#define DEBUG_H

#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QMutex>
#include <QTime>
static void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
        case QtDebugMsg:
            text = QString("Debug:");
            break;

        case QtWarningMsg:
            text = QString("Warning:");
            break;

        case QtCriticalMsg:
            text = QString("Critical:");
            break;

        case QtFatalMsg:
            text = QString("Fatal:");
            default:break;
    }


    QString contextInfo = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString cDataTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString cDate = QString("(%1)").arg(cDataTime);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(contextInfo).arg(msg).arg(cDate);

    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream textStream(&file);
    textStream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}

#endif // DEBUG_H
