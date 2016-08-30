#include "Vec3.h"

#include <cmath>

using namespace std;

namespace engine
{
    Vec3::Vec3(void) : Vec3(0.0f) { }

    Vec3::Vec3(const float v) : Vec3(v, v, v) { }

    Vec3::Vec3(const float x, const float y) : Vec3(x, y, 1.0f) { }

    Vec3::Vec3(const float x, const float y, const float z) : Vec2(x, y)
    {
        this->z = z; 
    }

    Vec3::Vec3(const Vec2 & copy) : Vec3(copy.x, copy.y) { }

    Vec3::Vec3(const Vec3 & copy) : Vec3(copy.x, copy.y, copy.z) { }

    const Vec3 Vec3::operator+(const Vec3 & param) const
    {
        return Vec3(x + param.x, y + param.y, z + param.z);
    }

    const Vec3 & Vec3::operator+=(const Vec3 & param)
    {
        x += param.x;
        y += param.y;
        z += param.z;
        return *this;
    }

    const Vec3 Vec3::operator-(const Vec3 & param) const
    {
        return Vec3(x - param.x, y - param.y, z - param.z);
    }

    const Vec3 & Vec3::operator-=(const Vec3 & param)
    {
        x -= param.x;
        y -= param.y;
        z -= param.z;
        return *this;
    }

    const Vec3 Vec3::operator*(const float param) const
    {
        return Vec3(x * param, y * param, z * param);
    }

    const Vec3 & Vec3::operator*=(const float param)
    {
        x *= param;
        y *= param;
        z *= param;
        return *this;
    }

    const Vec3 Vec3::operator/(const float param) const
    {
        return Vec3(x / param, y / param, z / param);
    }

    const Vec3 & Vec3::operator/=(const float param)
    {
        x /= param;
        y /= param;
        z /= param;
        return *this;
    }

    const Vec3 Vec3::operator-(void) const
    {
        return Vec3(-x, -y, -z);
    }

    const bool Vec3::operator==(const Vec3 & param) const
    {
        return equal(x, param.x) && equal(y, param.y) && equal(z, param.z);
    }

    const Vec3 operator*(const float param_left, const Vec3 & param_right)
    {
        return Vec3(param_right.x * param_left, param_right.y * param_left, param_right.z * param_left);
    }

    iostream & operator<<(iostream & _stream, const Vec3 & param)
    {
        _stream << "Vec3(" << param.x << ", " << param.y << ", " << param.z << ")";
        return _stream;
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