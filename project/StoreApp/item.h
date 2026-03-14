#ifndef ITEM_H
#define ITEM_H
#include <QString>

class Item
{
public:
    Item();
    Item(QString nameP);
    virtual QString getName() =0;
    virtual ~Item() {}
    virtual QString getType() const = 0;

protected:
   QString name;
};

#endif // ITEM_H
