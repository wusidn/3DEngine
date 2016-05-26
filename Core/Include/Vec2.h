#pragma once
#ifndef __VEC2_H__
#define __VEC2_H__

#include "Struct.h"

struct Vec2 : public Struct
{
public:
    Vec2(void);
    Vec2(const float v);
    Vec2(const float x, const float y);
    Vec2(const Vec2 & copy);
    
    ~Vec2(void);
    
    
    //重载运算符
    const Vec2 operator+(const Vec2 & param) const;
    const Vec2 operator-(const Vec2 & param) const;
    
    const Vec2 operator*(const float param) const;
    const Vec2 operator/(const float param) const;
    
    friend const Vec2 operator*(const float param_left, const Vec2 & param_right);
    
    //点积
    const float dot(const Vec2 & param) const;
    
    //模
    const float modulo(void) const;
    
    //角度
    const float angle(const Vec2 & param) const;
    
    float x, y;
};

#endif //__VEC2_H__