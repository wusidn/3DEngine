#include "Vec4.h"

namespace engine
{        
    Vec4::Vec4(void) : Vec4(0.0f) { }

    Vec4::Vec4(const float v) : Vec4(v, v, v, v) { }

    Vec4::Vec4(const float x, const float y) : Vec4(x, y, 0.0f) { }

    Vec4::Vec4(const float x, const float y, const float z) : Vec4(x, y, z, 0.0f) { }

    Vec4::Vec4(const float x, const float y, const float z, const float w) : Vec3(x, y, z)
    {
        this->w = w;
    }

    Vec4::Vec4(const Vec3 & copy) : Vec4(copy.x, copy.y, copy.z) { }

    Vec4::Vec4(const Vec3 & v, const float s) : Vec4(v)
    {
        w = s;
    }

    Vec4::Vec4(const Vec4 & copy) : Vec4(copy.x, copy.y, copy.z, copy.w) { }

    ostream & operator<<(ostream & _stream, const Vec4 & param)
    {
        _stream << "Vec4(" << param.x << ", " << param.y << ", " << param.z << ", " << param.w << ")";
        return _stream;
    }

    Vec4::~Vec4(void)
    {
        
    }
}