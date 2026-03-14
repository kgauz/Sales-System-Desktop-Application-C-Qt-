#ifndef CUSTOMERNAMEWINDOW_H
#define CUSTOMERNAMEWINDOW_H
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include "customerlist.h"

#include <QMainWindow>


class Customer;
class CustomerList;

class CustomerNameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit CustomerNameWindow(CustomerList *existingList, QWidget *parent = nullptr);

signals:
    void customerAded();
    void showItemWindow();

private slots:
    void addNames();
    void emitFinalized();
    void display();



private:
    QLabel *name_label;
    QLineEdit *lineEdit;
    QGridLayout *layout;
    QPushButton *button;
    QWidget *widget;
    Customer *customer;
    CustomerList *list;
    QPushButton *doneButton ;



};

#endif // CUSTOMERNAMEWINDOW_H
