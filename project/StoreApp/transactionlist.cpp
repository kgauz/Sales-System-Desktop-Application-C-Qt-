#include "transactionlist.h"
#include "transaction.h"

TransactionList::TransactionList() {}

void TransactionList::record(const QString &customerName, Transaction *t)
{
    if (checkItem(customerName, t->getItem())) {
        customerTransactions[customerName].append(t);
    }
}

bool TransactionList::checkItem(const QString &customerName, const QString &itemName)
{
    const QList<Transaction*> &list = customerTransactions[customerName];
    for (Transaction *t : list) {
        if (t->getItem() == itemName) {
            return false;
        }
    }
    return true;
}

QList<Transaction*> TransactionList::getRecordList()
{
    QList<Transaction*> all;
    for (const auto &list : std::as_const(customerTransactions)) {
        all.append(list);
    }
    return all;
}




