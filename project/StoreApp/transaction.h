#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <QString>
#include <QDateTime>

class Transaction
{
public:
    Transaction();
    Transaction(QString itemP, QString typeP, int quantityP, QDateTime dateTimeP,QString cn);
    QString getItem();
    int getQuantity();
    QString getType();
    QDateTime getDateTime();
    QString getCN();

private:
    QString item;
    QString type;
    int quantity;
    QDateTime dateTime;
    QString CN;
};

#endif // TRANSACTION_H
