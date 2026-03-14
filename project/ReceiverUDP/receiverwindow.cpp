#include "receiverwindow.h"
#include <QVBoxLayout>
#include <QWidget>

ReceiverWindow::ReceiverWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Setup central widget and layout
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout *layout = new QVBoxLayout(central);

    // Create text display area
    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);
    layout->addWidget(textEdit);

    // Create and start UDP receiver
    receiver = new UdpReceiver(this);
    receiver->startListening();

    // Connect signal to update GUI
    connect(receiver, &UdpReceiver::xmlReceived, this, [this](const QString &xml) {
        textEdit->append("Received XML:\n" + xml + "\n");
    });

    setWindowTitle("UDP Receiver");
    resize(500, 400);
}
