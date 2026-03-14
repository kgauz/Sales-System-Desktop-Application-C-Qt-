#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>

class UdpReceiver : public QObject
{
    Q_OBJECT

public:
    explicit UdpReceiver(QObject *parent = nullptr);
    void startListening();

signals:
    void xmlReceived(const QString &xmlData);  // Signal to send XML to GUI

private slots:
    void readPendingDatagrams();

private:
    QUdpSocket *udpSocket;
};

#endif // UDPRECEIVER_H
