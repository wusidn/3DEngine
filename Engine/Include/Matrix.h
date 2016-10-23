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

        //取反
        C operator-(void) const
        {
            C result;
            for(unsigned i = 0; i < dimension; ++i)
            {
                result[i] = -operator[](i);
            }
            return result;
        }


        //加法
        C operator+(const C & m) const
        {
            C result;
            for(unsigned i = 0; i < dimension; ++i)
            {
                result[i] = operator[](i) + m[i];
            }
            return result;
        }

        C & operator+=(const C & m)
        {
            for(unsigned i = 0; i < dimension; ++i)
            {
                operator[](i) += m[i];
            }
            return *this;
        }

        //减法
        C operator-(const C & m) const
        {
            return operator+(-m);
        }

        C & operator-=(const C & m)
        {
            return operator+=(-m);
        }

        //乘法
        T operator*(const T & v) const
        {
            T result;
            for(unsigned int i = 0; i < dimension; ++i)
            {
                for(unsigned int n = 0; n < dimension; ++n)
                {
                    result[i] += v[i] * operator[](i)[n];
                }
            }
            return result;
        }


        C operator*(const C & m) const
        {
            C result;
            for(unsigned int i = 0; i < dimension; ++i)
            {
                for(unsigned int n = 0; n < dimension; ++n)
                {
                    for(unsigned int j = 0; j < dimension; ++j)
                    {
                        result[i][n] += operator[](i)[j] * m[j][n];
                    }
                }
            }
            return result;
        }


    protected:
        Matrix(void){}
        ~Matrix(void){}

    private:
        T data[dimension];
    };
}

#endif //__MATRIX_H__