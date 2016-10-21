#pragma once
#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include "Matrix.h"
#include "Vec4.h"

namespace engine
{
    class Matrix4 : public Matrix<Matrix4, Vec4, 4>
    {
    public: 
        Matrix4(void);
        Matrix4(const float v);
        Matrix4(const Vec4 & v);
        Matrix4(const Vec4 & param1, const Vec4 & param2, const Vec4 & param3, const Vec4 & param4);
        Matrix4(const Matrix4 & copy);
    };
}

#endif //__MATRIX4_H__