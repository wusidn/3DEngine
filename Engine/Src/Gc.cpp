#include "Gc.h"


namespace engine
{
    Gc * Gc::instance = nullptr;

    Gc & Gc::getInstance(void)
    {
        if(!instance){ instance = new Gc(); }

        return * instance;
    }

    Gc::Gc(void)
    {
        objectPool = new list<const Object *>();
    }

    Gc::~Gc(void)
    {
        cleanAll();
        delete objectPool;
    }

    void Gc::clean(void)
    {
        for(auto item = objectPool->begin(); item != objectPool->end(); ++item)
        {
            if((*item)->_quoteCount <= 0)
            {
                const Object * temp = (*item);
                delete temp;
                item--;
                objectPool->remove(temp);
            }
        }
    }

    void Gc::watch(const Object & obj)
    {
        objectPool->push_back(&obj);
    }

    void Gc::cleanAll(void)
    {
        for(auto item = objectPool->begin(); item != objectPool->end(); ++item)
        {
            const Object * temp = (*item);
            delete temp;
            item--;
            objectPool->remove(temp);
        }
    }
}
