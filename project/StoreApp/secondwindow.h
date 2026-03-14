#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QSpinBox>
#include <QListWidget>
#include "mainwindow.h"
#include "secondwindow.h"

class Store;
class CustomerList;
class Transaction;
class TransactionList;

class SecondWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SecondWindow(Store *str, CustomerList *customers, TransactionList *transactions,QWidget *parent = nullptr);
    void check(QString n, QString i);

signals:
    void showTranWindow();
    void customerListFinalized();
    void showThirdWindow();

public slots:
    void showItemsW();
    void showThirdW();
    void addItem2();
    void exit();
    void updateCustomerComboBox();
    void updateItemComboBox();
    void onComboBoxTextChanged(const QString &text);

private:
    void setupUi();
    QComboBox *comboBoxCustomer;
    QComboBox * comboBoxItem;
    QLabel * labelTitle;
    QLabel * labelCustomer;
    QLabel * labelItem;
    QLabel *typeLabel;
    QLabel * quantityLabel;
    QLabel * t;
    QSpinBox *spinBox;
    QListWidget *listWidget;
    QGridLayout *layout;
    Store *storeBook;
    CustomerList *customerName;
    TransactionList *tranList;
    Transaction *tran;
    MainWindow *window ;
    QPushButton *addButton;
    QPushButton *doneButton;
};

#endif // SECONDWINDOW_H
