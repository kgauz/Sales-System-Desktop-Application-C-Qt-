#include "transaction.h"

Transaction::Transaction() {}

Transaction::Transaction(QString itemP, QString typeP, int quantityP, QDateTime dateTimeP,QString cn)
{
    item = itemP;
    type = typeP;
    quantity = quantityP;
    dateTime = dateTimeP;
    CN = cn;
}

QString Transaction::getItem()
{
    return item;
}

int Transaction::getQuantity()
{
    return quantity;
}

QString Transaction::getType()
{
    return type;
}

QDateTime Transaction::getDateTime()
{
    return dateTime;
}

QString Transaction::getCN()
{
    return CN;
}
