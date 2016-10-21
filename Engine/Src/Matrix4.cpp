#include "Matrix4.h"

namespace engine
{
    Matrix4::Matrix4(void) : Matrix()
    {

    }

    Matrix4::Matrix4(const float v) : Matrix4()
    {
        operator[](0)[0] = v;
        operator[](1)[1] = v;
        operator[](2)[2] = v;
        operator[](3)[3] = v;
    }

    Matrix4::Matrix4(const Vec4 & v) : Matrix4()
    {
        operator[](0)[0] = v[0];
        operator[](1)[1] = v[1];
        operator[](2)[2] = v[2];
        operator[](3)[3] = v[3];
    }

    Matrix4::Matrix4(const Vec4 & param1, const Vec4 & param2, const Vec4 & param3, const Vec4 & param4) : Matrix4()
    {
        operator[](0) = param1;
        operator[](1) = param2;
        operator[](2) = param3;
        operator[](3) = param4;
    }

    Matrix4::Matrix4(const Matrix4 & copy) : Matrix4(copy[0], copy[1], copy[2], copy[3])
    {
        
    }
}