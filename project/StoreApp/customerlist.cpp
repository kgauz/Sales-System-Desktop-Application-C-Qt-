#include "customerlist.h"

CustomerList::CustomerList() {}

void CustomerList::addCustomerNames(Customer *c)
{
    list.append(c);
}

QList<Customer *> CustomerList::getCustomerNameList()
{
    return list;
}
QStringList CustomerList::getCustomerNamesAsStrings()
{
    QStringList names;
    for (Customer *c : std::as_const(list)) {
        if (c) names.append(c->getName());
    }
    return names;
}
