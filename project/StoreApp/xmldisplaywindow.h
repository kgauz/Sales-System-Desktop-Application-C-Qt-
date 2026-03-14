// xmldisplaywindow.h
#ifndef XMLDISPLAYWINDOW_H
#define XMLDISPLAYWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>

class XmlDisplayWindow : public QWidget
{
    Q_OBJECT
public:
    explicit XmlDisplayWindow(const QString& xmlContent, QWidget *parent = nullptr);
    XmlDisplayWindow();

};

#endif // XMLDISPLAYWINDOW_H
