#pragma once
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "Struct.h"
#include "Vec.h"

namespace engine
{
    template<typename C, typename T, unsigned dimension>
    class Matrix : public Struct
    {
    public:
        T & operator[](const unsigned int index) const
        {
            return *(T *)(&data[index]);
        }


        //加法
        C operator+(const C & param) const
        {
            C result;
            for(unsigned i = 0; i < dimension; ++i)
            {
                result[i] = operator[](i) + param[i];
            }
            return result;
        }

        C & operator+=(const C & param)
        {
            for(unsigned i = 0; i < dimension; ++i)
            {
                operator[](i) += param[i];
            }
            return *this;
        }

        //减法



    protected:
        Matrix(void){}
        ~Matrix(void){}

    private:
        T data[dimension];
    };
}

#endif //__MATRIX_H__