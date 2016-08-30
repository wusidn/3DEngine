#include "ColorRGB.h"

namespace engine
{
    ColorRGB::ColorRGB(void) : ColorRGB(.0f, .0f, .0f) { }

    ColorRGB::ColorRGB(const float gray) : ColorRGB(gray, gray, gray) { }

    ColorRGB::ColorRGB(const float r, const float g, const float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    ColorRGB::ColorRGB(const ColorRGB & copy) : ColorRGB(copy.r, copy.g, copy.b) { }

    Vec3 ColorRGB::rgb(void) const
    {
        return Vec3(r, g, b);
    }
    Vec3 ColorRGB::rbg(void) const
    {
        return Vec3(r, b, g);
    }
    Vec3 ColorRGB::grb(void) const 
    {
        return Vec3(g, r, b);
    }
    Vec3 ColorRGB::gbr(void) const 
    {
        return Vec3(g, b, r);
    }
    Vec3 ColorRGB::brg(void) const 
    {
        return Vec3(b, r, g);
    }
    Vec3 ColorRGB::bgr(void) const 
    {
        return Vec3(b, g, r);
    }
}