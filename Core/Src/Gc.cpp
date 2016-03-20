#include "../Include/Gc.h"

Gc * Gc::instance = nullptr;

Gc & Gc::getInstance(void)
{
        if(!instance){
        instance = new Gc();
    }

    return * instance;
}


Gc::Gc(void)
{
    this->objectPool = new list<const Object *>();
}

void Gc::clean(void)
{
    for(auto item = objectPool->begin(); item != objectPool->end(); ++item)
    {
        cout << "foreach: " << *item << ", quoteCount: " << (*item)->quoteCount << endl;
        if((*item)->quoteCount <= 0){
            const Object * temp = (*item);
            delete temp;
            item--;
            objectPool->remove(temp);
        }
    }
}

void Gc::watch(const Object * obj)
{
    if(!obj){
        return;
    }

    objectPool->push_back(obj);
}
