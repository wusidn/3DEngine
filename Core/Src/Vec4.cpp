#include "Vec4.h"

Vec4::Vec4(void) : Vec3()
{
    w = 0;
}

Vec4::Vec4(const float v) : Vec3(v)
{
    w = v;
}

Vec4::Vec4(const float x, const float y) : Vec3(x, y)
{
    Vec4();
}

Vec4::Vec4(const float x, const float y, const float z) : Vec3(x, y, z)
{
    Vec4();
}

Vec4::Vec4(const float x, const float y, const float z, const float w) : Vec3(x, y, z)
{
    this->w = w;
}

Vec4::Vec4(const Vec3 & copy) : Vec3(copy)
{
    Vec4();
}

Vec4::Vec4(const Vec4 & copy)
{
    this->x = copy.x;
    this->y = copy.y;
    this->z = copy.z;
    this->w = copy.w;
}

Vec4::~Vec4(void)
{
    
}