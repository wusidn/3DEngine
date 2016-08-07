#include "Size2.h"

namespace engine
{
    Size2::Size2(void) : Size2(0)
    {
    }
    
    Size2::Size2(const float v) : Size2(v, v)
    {
    }

    Size2::Size2(const float _width, const float _height)
    {
        width = _width;
        height = _height;
    }

    Size2::Size2(const Size2 & copy) : Size2(copy.width, copy.height)
    {

    }

    const Size2 Size2::operator+(const Size2 & param) const
    {
        return Size2(width + param.width, height + param.height);
    }

    const Size2 Size2::operator-(const Size2 & param) const
    {
        return Size2(width - param.width, height - param.height);
    }

}