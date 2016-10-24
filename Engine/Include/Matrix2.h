#pragma once
#ifndef __MATRIX2_H__
#define __MATRIX2_H__

#include "Matrix.h"
#include "Vec2.h"

namespace engine
{
    class Matrix2 : public Matrix<Matrix2, Vec2, 2>
    {
    public:
        Matrix2(void);
        Matrix2(const float v);
        Matrix2(const Vec2 & v);
        Matrix2(const Vec2 & v1, const Vec2 & v2);
        Matrix2(const Matrix2 & copy);

    protected:
        // Matrix2(void){}
    private:
    };
}


#endif //__MATRIX2_H__