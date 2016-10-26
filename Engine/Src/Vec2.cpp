#include "Vec2.h"

#include <cmath>

namespace engine
{        
    Vec2::Vec2(void) : Vec2(0.0f) { }

    Vec2::Vec2(const float v) : Vec2(v, v) { }

    Vec2::Vec2(const float x, const float y)
    {
        this->x = x;
        this->y = y;
    }

    Vec2::Vec2(const Vec2 & copy) : Vec2(copy.x, copy.y) { }

    Vec2::~Vec2(void)
    {
        
    }

    const Vec2 Vec2::operator-(void) const
    {
        return Vec2(-x, -y);
    }

    const Vec2 Vec2::operator+(const Vec2 & v) const
    {
        return Vec2(x + v.x, y + v.y);
    }

    Vec2 & Vec2::operator+=(const Vec2 & v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    const Vec2 Vec2::operator-(const Vec2 & v) const
    {
        return Vec2(x - v.x, y - v.y);
    }

    Vec2 & Vec2::operator-=(const Vec2 & v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    const Vec2 Vec2::operator*(const float v) const
    {
        return Vec2(x * v, y * v);
    }

    Vec2 & Vec2::operator*=(const float s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    const Vec2 Vec2::operator/(const float s) const
    {
        return Vec2(x / s, y / s);
    }

    Vec2 & Vec2::operator/=(const float s)
    {
        x /= s;
        y /= s;
        return *this;
    }

    const Vec2 operator*(const float s, const Vec2 & v)
    {
        return Vec2(v.x * s, v.y * s);
    }

    ostream & operator<<(ostream & _stream, const Vec2 & param)
    {
         _stream << "Vec2(" <<  param.x << ", " << param.y << ")";
         return _stream;
    }

    const float Vec2::dot(const Vec2 & v) const
    {
        return x * v.x + y * v.y;
    }

    const float Vec2::modulo(void) const
    {
        return sqrt(dot(*this));
    }

    const float Vec2::angle(const Vec2 & v) const
    {
        return acos(dot(v) / modulo() / v.modulo()) / PI * 180;
    }

    const Vec2 Vec2::normalize(void) const
    {
        return operator/(modulo());
    }

}