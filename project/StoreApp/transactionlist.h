#ifndef TRANSACTIONLIST_H
#define TRANSACTIONLIST_H
#include "transaction.h"
#include <QList>
#include <QString>


class TransactionList
{
public:
    TransactionList();
    void record(const QString & customerName, Transaction *t);
    bool checkItem(const QString &customerName, const QString &itemName);
    QList<Transaction*> getRecordList();

private:
    QMap<QString, QList<Transaction*>> customerTransactions;
};

#endif // TRANSACTIONLIST_H
