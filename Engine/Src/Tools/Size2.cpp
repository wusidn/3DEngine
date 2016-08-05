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
}