#include "../Include/Vec2.h"

#include <cmath>

Vec2::Vec2(void)
{
    x = y = 0;
}

Vec2::Vec2(const float v)
{
    x = y = v;
}

Vec2::Vec2(const float x, const float y)
{
    this->x = x;
    this->y = y;
}

Vec2::Vec2(const Vec2 & copy)
{
    x = copy.x;
    y = copy.y;
}

Vec2::~Vec2(void)
{
    
}

const Vec2 Vec2::operator+(const Vec2 & param) const
{
    return Vec2(x + param.x, y + param.y);
}

const Vec2 Vec2::operator-(const Vec2 & param) const
{
    return Vec2(x - param.x, y - param.y);
}

const Vec2 Vec2::operator*(const float param) const
{
    return Vec2(x * param, y * param);
}

const Vec2 Vec2::operator/(const float param) const
{
    return Vec2(x / param, y / param);
}

const Vec2 operator*(const float param_left, const Vec2 & param_right)
{
    return Vec2(param_right.x * param_left, param_right.y * param_left);
}

const float Vec2::dot(const Vec2 & param) const
{
    return x * param.x + y * param.y;
}

const float Vec2::modulo(void) const
{
    return sqrt(dot(*this));
}

const float Vec2::angle(const Vec2 & param) const
{
    return acos(dot(param) / modulo() / param.modulo()) / PI * 180;
}