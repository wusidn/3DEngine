#pragma once
#ifndef __VEC3_H__
#define __VEC3_H__

#include "Vec2.h"

class Vec3 : public Vec2
{
public:
    Vec3(void);
    Vec3(const float v);
    Vec3(const float x, const float y);
    Vec3(const float x, const float y, const float z);
    
    Vec3(const Vec2 & copy);
    Vec3(const Vec3 & copy);
    
    ~Vec3(void);
    
    float z;
};

#endif //__VEC3_H__