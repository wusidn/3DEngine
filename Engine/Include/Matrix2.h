#pragma once
#ifndef __MATRIX2_H__
#define __MATRIX2_H__

#include "Matrix.h"
#include "Vec2.h"

namespace engine
{
    class Matrix2 : public Matrix
    {
    public:
        Matrix2(const Vec2 & param1, const Vec2 & param2);
        Matrix2(const Matrix2 & copy);
    protected:
        Matrix2(void);
    private:
        Vec2 data[2];
    };
}


#endif //__MATRIX2_H__