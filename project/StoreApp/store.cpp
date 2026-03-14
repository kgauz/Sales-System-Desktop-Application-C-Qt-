#include "store.h"

Store::Store() {}

void Store::addItem(Item *i)
{
    item_list.append(i);
    backuPList();
}
void Store::backuPList()
{
    backUp_list = item_list;
}

void Store::restore()
{
    if(!(backUp_list.isEmpty()))
    {
        item_list = backUp_list;
    }
}

QList<Item *> Store::getItemLIst()
{
   return item_list;
}

