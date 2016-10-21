#pragma once 
#ifndef __MATRIX3_H__
#define __MATRIX3_H__

#include "Matrix.h"
#include "Vec3.h"

namespace engine
{
    class Matrix3 : public Matrix<Matrix3, Vec3, 3>
    {
    public:
        Matrix3(void);
        Matrix3(const float v);
        Matrix3(const Vec3 & v);
        Matrix3(const Vec3 & param1, const Vec3 & param2, const Vec3 & param3);
        Matrix3(const Matrix3 & copy);
    };
}

#endif //__MATRIX3_H__