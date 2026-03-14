#include "xmldisplaywindow.h"

XmlDisplayWindow::XmlDisplayWindow() {}

XmlDisplayWindow::XmlDisplayWindow(const QString& xmlContent, QWidget *parent)
    : QWidget(parent)
{


    setWindowTitle("Transactions XML");

    QVBoxLayout *layout = new QVBoxLayout(this);
    QTextEdit *textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);
    textEdit->setPlainText(xmlContent);
    layout->addWidget(textEdit);
    setLayout(layout);

    resize(600, 400);
}
