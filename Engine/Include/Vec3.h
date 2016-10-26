#pragma once
#ifndef __VEC3_H__
#define __VEC3_H__

#include "Vec2.h"
#include "Size3.h"

namespace engine
{
    struct Vec3 : public Vec2
    {
    public:
        Vec3(void);
        Vec3(const float v);
        Vec3(const float x, const float y);
        Vec3(const float x, const float y, const float z);
        
        Vec3(const Vec2 & copy);
        Vec3(const Vec3 & copy);
        
        ~Vec3(void);
        
        //重载运算符
        // const Vec3 operator+(const float s) const;
        const Vec3 operator+(const Size3 & offset) const;
        const Vec3 & operator+=(const Size3 & offset);
        // const Vec3 operator-(const float s) const;
        const Size3 operator-(const Vec3 & v) const;
        const Vec3 operator-(const Size3 & offset) const;
        const Vec3 & operator-=(const Size3 & offset);

        const Vec3 operator*(const float s) const;
        const Vec3 operator*(const Vec3 & v) const;

        const Vec3 & operator*=(const float s);
        const Vec3 operator/(const float s) const;
        const Vec3 & operator/=(const float s);

        const Vec3 operator-(void) const;
        const bool operator==(const Vec3 & v) const;
        
        //这个乘法好像没意义  暂留
        friend const Vec3 operator*(const float s, const Vec3 & v);
        friend ostream & operator<<(ostream & _stream, const Vec3 & v);

        Size3 convertToSize3(void) const;
        
        //点积
        const float dot(const Vec3 & v) const;
        
        //叉积
        const Vec3 cross(const Vec3 & v) const;
        
        //模
        const float modulo(void) const;

        //标准化
        const Vec3 normalize(void) const;
        
        float z;
    };
}

#endif //__VEC3_H__