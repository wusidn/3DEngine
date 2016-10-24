#include "Matrix2.h"

#include "LogManager.h"

namespace engine
{

    Matrix2::Matrix2(void) : Matrix()
    {

    }

    Matrix2::Matrix2(const float v) : Matrix2()
    {
        operator[](0)[0] = v;
        operator[](1)[1] = v;
    }

    Matrix2::Matrix2(const Vec2 & v) : Matrix2()
    {
        operator[](0)[0] = v[0];
        operator[](1)[1] = v[1];
    }

    Matrix2::Matrix2(const Vec2 & v_1, const Vec2 & v_2) : Matrix2()
    {
        operator[](0) = v_1;
        operator[](1) = v_2;
    }

    Matrix2::Matrix2(const Matrix2 & copy) : Matrix2(copy[0], copy[1])
    {
    }
    
}