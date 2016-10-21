#include "Matrix3.h"

namespace engine
{

    Matrix3::Matrix3(void) : Matrix()
    {

    }

    Matrix3::Matrix3(const float v) : Matrix3()
    {
        operator[](0)[0] = v;
        operator[](1)[1] = v;
        operator[](2)[2] = v;
    }

    Matrix3::Matrix3(const Vec3 & v) : Matrix3()
    {
        operator[](0)[0] = v[0];
        operator[](1)[1] = v[1];
        operator[](2)[2] = v[2];
    }

    Matrix3::Matrix3(const Vec3 & param1, const Vec3 & param2, const Vec3 & param3) : Matrix3()
    {
        operator[](0) = param1;
        operator[](1) = param2;
        operator[](2) = param3;
    }

    Matrix3::Matrix3(const Matrix3 & copy) : Matrix3(copy[0], copy[1], copy[2])
    {

    }
}