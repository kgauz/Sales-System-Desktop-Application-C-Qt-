#ifndef TRANSACTIONMAINWINDOW_H
#define TRANSACTIONMAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QToolBar>
#include <QWidget>
#include <QVBoxLayout>
#include "transactionlist.h"
#include <QDateTime>
#include "customerlist.h"
#include "xmldisplaywindow.h"
#include "store.h"
#include "secondwindow.h"

class TransactionMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit TransactionMainWindow(TransactionList *tranList, CustomerList *cusLists,Store *s,QWidget *parent = nullptr);
    QString generateXmlFromRecords();


signals:

public slots:
    void refresh();
    void onShowXmlClicked();
    void onRestoreClicked();
    void onAddCustomerClicked();


private:
    void setupUi();
    QToolBar *file;
    QToolBar *add;
    QToolBar *restore;
    QTreeView *tree;
    QStandardItem *item;
    QStandardItemModel *itemModel;
    QWidget *widget;
    TransactionList *list;
    CustomerList *customerLists;
    QVBoxLayout *layout;
    Store *store;
    XmlDisplayWindow *xmlWindow = nullptr;
    SecondWindow* transWindow = nullptr;


};

#endif // TRANSACTIONMAINWINDOW_H
