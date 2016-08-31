#include "Size3.h"

namespace engine
{
    Size3::Size3(void) : Size3(0.0f) { }

    Size3::Size3(const float v) : Size3(v, v, v){ }

    Size3::Size3(const float width, const float height) : Size3(width, height, 0.0f) { }

    Size3::Size3(const float width, const float height, const float depth) : Size2(width, height)
    {
        this->depth = depth;
    }

    Size3::Size3(const Size3 & copy) : Size3(copy.width, copy.height, copy.depth) { }

    Size3::Size3(const Size2 & copy) : Size3(copy.width, copy.height) { }

    ostream & operator<<(ostream & _stream, const Size3 & param)
    {
        _stream << "Size3(" << param.width << ", " << param.height << ", " << param.depth << ")";
        return _stream;
    }

}