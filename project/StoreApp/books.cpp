#include "books.h"
#include <QString>

Books::Books() {

}

Books::Books(QString nameP):Item(nameP)
{
    name = nameP;
}

QString Books::getName()
{
    return name;
}
QString Books::getType() const
{
    return "B";
}
