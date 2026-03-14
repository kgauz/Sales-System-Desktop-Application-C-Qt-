#include "udpsenderthread.h"
#include <QHostAddress>

UdpSenderThread::UdpSenderThread(const QString &xmlToSend, QObject *parent)
    : QThread(parent), xmlData(xmlToSend)
{
   // connect(this, &QThread::finished, this, &QObject::deleteLater);

}

void UdpSenderThread::run()
{
    QUdpSocket udpSocket;
    QByteArray datagram = xmlData.toUtf8();
    udpSocket.writeDatagram(datagram, QHostAddress::Broadcast, 45454);
}
