#pragma once
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "Struct.h"
#include "Vec.h"

#include <iostream>

using namespace std;

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


        friend ostream & operator<<(ostream & _stream, const Matrix & m)
        {
            _stream << "Matrix" << dimension << ":" << endl;
            for(unsigned int i = 0; i < dimension; ++i)
            {
                _stream << "\t\t";
                i ? _stream << "  " : _stream << "[ ";
                for(unsigned int n = 0; n < dimension; ++n)
                {
                    if(n) _stream << ", ";
                    _stream << m[i][n];
                }
                i >= dimension - 1 ? _stream << " ]" : _stream << endl;
            }
            return _stream;
        }


    protected:
        Matrix(void){}
        ~Matrix(void){}

    private:
        T data[dimension];
    };
}

#endif //__MATRIX_H__