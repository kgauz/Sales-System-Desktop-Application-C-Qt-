#include "magazines.h"

Magazines::Magazines() {}

Magazines::Magazines(QString nameP)
{
    name = nameP;
}

QString Magazines::getName()
{
    return name;
}
QString Magazines::getType() const
{
    return "M";
}

