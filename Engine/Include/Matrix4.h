#pragma once
#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include "Matrix.h"
#include "Vec4.h"
#include "Size3.h"

namespace engine
{
    class Matrix4 : public Matrix<Matrix4, Vec4, 4>
    {
    public: 
        Matrix4(void);
        Matrix4(const float v);
        Matrix4(const Vec4 & v);
        Matrix4(const float s1, const float s2, const float s3, const float s4);
        Matrix4(const Vec4 & v1, const Vec4 & v2, const Vec4 & v3, const Vec4 & v4);
        Matrix4(const Matrix4 & copy);
        
        static Matrix4 createTranslationMatrix(const Size3 & size);
        static Matrix4 createRotationMatrix(const Vec3 & angle);
        static Matrix4 createScaleMatrix(const Vec3 & scale);

    };
}

#endif //__MATRIX4_H__