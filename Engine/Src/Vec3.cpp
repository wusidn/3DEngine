#include "Vec3.h"

#include <cmath>

using namespace std;

namespace engine
{
    Vec3::Vec3(void) : Vec3(0.0f) { }

    Vec3::Vec3(const float v) : Vec3(v, v, v) { }

    Vec3::Vec3(const float x, const float y) : Vec3(x, y, 0.0f) { }

    Vec3::Vec3(const float x, const float y, const float z) : Vec2(x, y)
    {
        this->z = z; 
    }

    Vec3::Vec3(const Vec2 & copy) : Vec3(copy.x, copy.y) { }

    Vec3::Vec3(const Vec3 & copy) : Vec3(copy.x, copy.y, copy.z) { }

    const Vec3 Vec3::operator+(const Size3 & offset) const
    {
        return Vec3(x + offset.width, y + offset.height, z + offset.depth);
    }

    const Vec3 & Vec3::operator+=(const Size3 & offset)
    {
        x += offset.width;
        y += offset.height;
        z += offset.depth;
        return *this;
    }

    const Size3 Vec3::operator-(const Vec3 & v) const
    {
        return Size3(x - v.x, y - v.y, z - v.z);
    }

    const Vec3 Vec3::operator-(const Size3 & offset) const
    {
        return Vec3(x - offset.width, y - offset.height, z - offset.depth);
    }

    const Vec3 & Vec3::operator-=(const Size3 & offset)
    {
        x -= offset.width;
        y -= offset.height;
        z -= offset.depth;
        return *this;
    }

    const Vec3 Vec3::operator*(const float s) const
    {
        return Vec3(x * s, y * s, z * s);
    }

    const Vec3 Vec3::operator*(const Vec3 & v) const
    {
        return Vec3(x * v.x, y * v.y, z * v.z);
    }

    const Vec3 & Vec3::operator*=(const float s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    const Vec3 Vec3::operator/(const float s) const
    {
        return Vec3(x / s, y / s, z / s);
    }

    const Vec3 & Vec3::operator/=(const float s)
    {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    const Vec3 Vec3::operator-(void) const
    {
        return Vec3(-x, -y, -z);
    }

    const bool Vec3::operator==(const Vec3 & v) const
    {
        return equal(x, v.x) && equal(y, v.y) && equal(z, v.z);
    }

    const Vec3 operator*(const float s, const Vec3 & v)
    {
        return Vec3(v.x * s, v.y * s, v.z * s);
    }

    ostream & operator<<(ostream & _stream, const Vec3 & v)
    {
        _stream << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
        return _stream;
    }

    Size3 Vec3::convertToSize3(void) const
    {
        return Size3(x, y, z);
    }

    const float Vec3::dot(const Vec3 & v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    const Vec3 Vec3::cross(const Vec3 & v) const
    {
        return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    const float Vec3::modulo(void) const
    {
        return sqrt(dot(*this));
    }

    const Vec3 Vec3::normalize(void) const
    {
        return operator/(modulo());
    }

    Vec3::~Vec3(void)
    {
        
    }
}