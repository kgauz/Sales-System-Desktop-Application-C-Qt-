#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <QString>

class Customer{
public:

    Customer() ;

    Customer(QString customerNameP);

    QString getName();

private:

    QString customerName;
};
#endif // CUSTOMER_H
