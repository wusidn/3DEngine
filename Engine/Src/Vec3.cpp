#include "Vec3.h"

#include <cmath>

namespace engine
{
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

    const Vec3 Vec3::operator+(const Vec3 & param) const
    {
        return Vec3(x + param.x, y + param.y, z + param.z);
    }

    const Vec3 Vec3::operator-(const Vec3 & param) const
    {
        return Vec3(x - param.x, y - param.y, z - param.z);
    }

    const Vec3 Vec3::operator*(const float param) const
    {
        return Vec3(x * param, y * param, z * param);
    }

    const Vec3 Vec3::operator/(const float param) const
    {
    return Vec3(x / param, y / param, z / param);
    }

    const Vec3 operator*(const float param_left, const Vec3 & param_right)
    {
        return Vec3(param_right.x * param_left, param_right.y * param_left, param_right.z * param_left);
    }

    const float Vec3::dot(const Vec3 & param) const
    {
        return x * param.x + y * param.y + z * param.z;
    }

    const Vec3 Vec3::cross(const Vec3 & param) const
    {
        return Vec3(y * param.z - z * param.y, z * param.x - x * param.z, x * param.y - y * param.x);
    }

    const float Vec3::modulo(void) const
    {
        return sqrt(dot(*this));
    }

    Vec3::~Vec3(void)
    {
        
    }
}