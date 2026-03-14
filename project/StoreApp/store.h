#ifndef STORE_H
#define STORE_H
#include <QList>
#include "item.h"

class Store
{
public:
    Store();
    void addItem(Item *i);
    void backuPList();
    void restore();
    QList<Item*> getItemLIst();

private:
    QList<Item*> item_list;
    QList<Item*> backUp_list;

};

#endif // STORE_H
