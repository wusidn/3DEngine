#pragma once
#ifndef __VEC2_H__
#define __VEC2_H__

#include "Struct.h"

class Vec2 : public Struct
{
public:
    Vec2(void);
    Vec2(const float v);
    Vec2(const float x, const float y);
    Vec2(const Vec2 & copy);
    
    ~Vec2(void);
    
    float x, y;
};

#endif //__VEC2_H__