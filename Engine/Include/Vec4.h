#pragma once
#ifndef __VEC4_H__
#define __VEC4_H__

#include "Vec3.h"

namespace engine
{        
    struct Vec4 : public Vec3
    {
    public:
        Vec4(void);
        Vec4(const float v);
        Vec4(const float x, const float y);
        Vec4(const float x, const float y, const float z);
        Vec4(const float x, const float y, const float z, const float w);
        
        Vec4(const Vec3 & copy);
        Vec4(const Vec4 & copy);

        Vec4(const Vec3 & v, const float s);

        friend ostream & operator<<(ostream & _stream, const Vec4 & param);
        
        ~Vec4(void); 
        
        float w;
    };
}

#endif //__VEC4_H__