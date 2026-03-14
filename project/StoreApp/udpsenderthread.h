#ifndef UDPSENDERTHREAD_H
#define UDPSENDERTHREAD_H

#include <QThread>
#include <QUdpSocket>
#include <QString>

class UdpSenderThread : public QThread
{
    Q_OBJECT

public:
    explicit UdpSenderThread(const QString &xmlToSend, QObject *parent = nullptr);
    void run() override;

private:
    QString xmlData;
};

#endif // UDPSENDERTHREAD_H
