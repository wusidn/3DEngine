#pragma once
#ifndef __VEC2_H__
#define __VEC2_H__

#include "Vec.h"
#include <iostream>

using namespace std;

namespace engine
{
    struct Vec2 : public Vec
    {
    public:
        Vec2(void);
        Vec2(const float v);
        Vec2(const float x, const float y);
        Vec2(const Vec2 & copy);
        
        ~Vec2(void);
        
        
        //重载运算符
        const Vec2 operator-(void) const;

        const Vec2 operator+(const Vec2 & param) const;
        Vec2 & operator+=(const Vec2 & param);

        const Vec2 operator-(const Vec2 & param) const;
        Vec2 & operator-=(const Vec2 & param);
        
        const Vec2 operator*(const float param) const;
        Vec2 & operator*=(const float param);

        const Vec2 operator/(const float param) const;
        Vec2 & operator/=(const float param);
        
        friend const Vec2 operator*(const float param_left, const Vec2 & param_right);
        friend ostream & operator<<(ostream & _stream, const Vec2 & param);
        
        //点积
        const float dot(const Vec2 & param) const;
        
        //模
        const float modulo(void) const;
        
        //角度
        const float angle(const Vec2 & param) const;

        //标准化
        const Vec2 normalize(void) const;
        
        float x, y;
    };
}

#endif //__VEC2_H__