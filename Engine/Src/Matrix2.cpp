#include "Matrix2.h"

#include "LogManager.h"

namespace engine
{
    
    Matrix2::Matrix2(void) : Matrix(2)
    {
        for(int i = 0; i < 2; ++i){
            _data[i] = &data[i];
        }
    }

    Matrix2::Matrix2(const Vec2 & param1, const Vec2 & param2) : Matrix2()
    {
        data[0] = param1;
        data[1] = param2;
    }

    Matrix2::Matrix2(const Matrix2 & copy) : Matrix2(*(Vec2 *)&(copy[0]), *(Vec2 *)&(copy[1]))
    {

    }
}