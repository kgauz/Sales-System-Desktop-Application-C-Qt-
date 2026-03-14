#ifndef MAGAZINES_H
#define MAGAZINES_H

#include "item.h"


class Magazines : public Item
{
public:
    Magazines();
    Magazines(QString nameP);
    QString getName()override;
    QString getType() const override;
};

#endif // MAGAZINES_H
