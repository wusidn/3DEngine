#include "../Include/Object.h"
#include "../Include/Gc.h"


void Object::retain(void)
{
    this->quoteCount++;
}

void Object::release(void)
{
    this->quoteCount--;
}

void Object::autoRelease(void)
{
    Gc::getInstance().watch(this);
}

const bool Object::init(void)
{
    quoteCount = 0;
    return true;
}
