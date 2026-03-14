#include "udpreceiver.h"
#include <QHostAddress>

UdpReceiver::UdpReceiver(QObject *parent)
    : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
}

void UdpReceiver::startListening()
{
    udpSocket->bind(QHostAddress::AnyIPv4, 45454, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udpSocket, &QUdpSocket::readyRead, this, &UdpReceiver::readPendingDatagrams);
}

void UdpReceiver::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());

        QString xmlData = QString::fromUtf8(datagram);
        emit xmlReceived(xmlData);  // Send XML to the main window
    }
}
