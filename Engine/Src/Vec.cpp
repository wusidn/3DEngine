#include "Vec.h"

namespace engine
{
    float & Vec::operator[](const unsigned int index) const
    {
        return *((float *)this + index);
    }
}