#include "../Include/Vec2.h"

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