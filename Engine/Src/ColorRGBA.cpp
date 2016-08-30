#include "ColorRGBA.h"

namespace engine
{
    ColorRGBA::ColorRGBA(void) : ColorRGBA(0.0f, 1.0f) { }

    ColorRGBA::ColorRGBA(const float gray, const float a) : ColorRGBA(gray, gray, gray, a) { }

    ColorRGBA::ColorRGBA(const float r, const float g, const float b) : ColorRGBA(r, g, b, 1.0f) { }

    ColorRGBA::ColorRGBA(const float r, const float g, const float b, const float a) : ColorRGB(r, g, b)
    {
        this->a = a;
    }

    ColorRGBA::ColorRGBA(const ColorRGB & copy) : ColorRGBA(copy.r, copy.g, copy.b) { }

    ColorRGBA::ColorRGBA(const ColorRGBA & copy) : ColorRGBA(copy.r, copy.g, copy.b, copy.a) { }

    Vec4 ColorRGBA::rgba(void) const
    {
        return Vec4(r, g, b, a);
    }
    Vec4 ColorRGBA::rbga(void) const
    {
        return Vec4(r, b, g, a);
    }
    Vec4 ColorRGBA::grba(void) const 
    {
        return Vec4(g, r, b, a);
    }
    Vec4 ColorRGBA::gbra(void) const 
    {
        return Vec4(g, b, r, a);
    }
    Vec4 ColorRGBA::brga(void) const 
    {
        return Vec4(b, r, g, a);
    }
    Vec4 ColorRGBA::bgra(void) const 
    {
        return Vec4(b, g, r, a);
    }
}