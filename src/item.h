#ifndef ITEM_H
#define ITEM_H


class basicItem
{
    public:
        basicItem();
        virtual ~basicItem();
    protected:

    private:
        unsigned int maxStackSize;


};


class itemContainer
{
public:
    itemContainer(basicItem* item);
    ~itemContainer();

private:
    basicItem* item;
    unsigned int itemCount;

};


#endif // ITEM_H
