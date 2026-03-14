#include "customer.h"

Customer::Customer() {

}

Customer::Customer(QString customerNameP)
{
    customerName = customerNameP;
}

QString Customer::getName()
{
    return customerName;
}

