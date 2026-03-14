#ifndef BOOKS_H
#define BOOKS_H
#include <QString>
#include "item.h"

class Books : public Item
{
public:
    Books();
    Books(QString nameP) ;
    QString getName() override;
    QString getType() const override;

};

#endif // BOOKS_H
