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
        return !_state;
    }

    const unsigned short Object::fault(void) const
    {
        return _state;
    }

    const bool Object::init(void)
    {
        _quoteCount = 0;
        _state = 0;
        return true;
    }
}
