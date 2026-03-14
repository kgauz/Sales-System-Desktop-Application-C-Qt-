#ifndef CUSTOMERLIST_H
#define CUSTOMERLIST_H
#include <QList>
#include "customer.h"

class CustomerList
{
public:
    CustomerList();
    void addCustomerNames(Customer *c);
    QList<Customer*> getCustomerNameList();
    QStringList getCustomerNamesAsStrings();



private:

    QList<Customer*>list;

};

#endif // CUSTOMERLIST_H
