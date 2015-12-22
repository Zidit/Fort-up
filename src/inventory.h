#ifndef INVENTORY_H
#define INVENTORY_H


#include "item.h"
#include <vector>

class inventory
{
    public:
        inventory();
        virtual ~inventory();

        bool addItem(itemContainer *item);

    protected:
    private:
        unsigned inventorySize;
        std::vector<itemContainer*> items;


};

#endif // INVENTORY_H
