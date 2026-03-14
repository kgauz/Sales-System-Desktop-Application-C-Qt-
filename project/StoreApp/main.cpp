#include "mainwindow.h"
#include "secondwindow.h"
#include "customernamewindow.h"
#include "transactionmainwindow.h"
#include "store.h"
#include "transactionlist.h"
#include "transaction.h"
#include <QApplication>
#include <QDateTime>


int main(int argc, char *argv[])
{
        QApplication a(argc, argv);

        Store *store = new Store();
        CustomerList *customers = new CustomerList();
        TransactionList *transactions = new TransactionList();

        SecondWindow *s = new SecondWindow(store, customers, transactions);
        TransactionMainWindow *tran = new TransactionMainWindow(transactions, customers,store);

        QObject::connect(s, &SecondWindow::customerListFinalized, tran, &TransactionMainWindow::refresh);
        QObject::connect(s, &SecondWindow::showTranWindow, tran, &TransactionMainWindow::show);


       tran->resize(400,400);



    return a.exec();

}
