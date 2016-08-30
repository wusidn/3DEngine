#pragma once
#ifndef __COLOR_RGB_H__
#define __COLOR_RGB_H__

#include "Struct.h"
#include <Vec3.h>

namespace engine
{
    class ColorRGB : public Struct
    {
    public:
        ColorRGB(void);
        ColorRGB(const float gray);
        ColorRGB(const float r, const float g, const float b);

        ColorRGB(const ColorRGB & copy);

        Vec3 rgb(void) const;
        Vec3 rbg(void) const;
        Vec3 grb(void) const;
        Vec3 gbr(void) const;
        Vec3 brg(void) const;
        Vec3 bgr(void) const;

        float r, g, b;
    };
}

#endif //__COLOR_RGB_H__