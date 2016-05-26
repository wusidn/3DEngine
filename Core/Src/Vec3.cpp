#include "../Include/Vec3.h"


Vec3::Vec3(void) : Vec2()
{
    z = 0;
}

Vec3::Vec3(const float v) : Vec2(v)
{
    z = v;
}

Vec3::Vec3(const float x, const float y) : Vec2(x, y)
{
    Vec3();
}

Vec3::Vec3(const float x, const float y, const float z) : Vec3(x, y)
{
    this->z = z; 
}

Vec3::Vec3(const Vec2 & copy)
{
    Vec3(copy.x, copy.y);
}

Vec3::Vec3(const Vec3 & copy)
{
    x = copy.x;
    y = copy.y;
    z = copy.z;
}

const float Vec3::dot(const Vec3 & param) const
{
    return x * param.x + y * param.y + z * param.z;
}

const Vec3 Vec3::cross(const Vec3 & param) const
{
    return Vec3(y * param.z - z * param.y, z * param.x - x * param.z, x * param.y - y * param.x);
}

Vec3::~Vec3(void)
{
    
}