#pragma once
#ifndef __COLOR_RGBA__
#define __COLOR_RGBA__

#include "ColorRGB.h"
#include "Vec4.h"

namespace engine
{
    class ColorRGBA : public ColorRGB
    {
    public:
        ColorRGBA(void);
        ColorRGBA(const float rgba);
        ColorRGBA(const float gray, const float a);
        ColorRGBA(const float r, const float g, const float b);
        ColorRGBA(const float r, const float g, const float b, const float a);

        Vec4 rgba(void) const;
        Vec4 rbga(void) const;
        Vec4 grba(void) const;
        Vec4 gbra(void) const;
        Vec4 brga(void) const;
        Vec4 bgra(void) const;

        float a;
    };
}

#endif //__COLOR_RGBA__