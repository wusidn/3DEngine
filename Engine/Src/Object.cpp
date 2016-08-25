#include "Object.h"
#include "Gc.h"

namespace engine
{
    void Object::retain(void)
    {
        this->_quoteCount++;
    }

    void Object::release(void)
    {
        this->_quoteCount--;
    }

    void Object::autoRelease(void)
    {
        Gc::getInstance().watch(*this);
    }

    const bool Object::ready(void) const
    {
        return !_initializeErrorCode;
    }

    const unsigned short Object::fault(void) const
    {
        return _initializeErrorCode;
    }

    const bool Object::init(void)
    {
        _quoteCount = 0;
        _initializeErrorCode = 0;
        return true;
    }

    void Object::initializeError(const unsigned short errorCode)
    {
        if(!errorCode){
            return;
        }
        _initializeErrorCode = errorCode;
    }
}
