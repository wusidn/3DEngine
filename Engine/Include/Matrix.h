#pragma once
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "Struct.h"
#include "Vec.h"

namespace engine
{
    class Matrix : public Struct
    {
    public:
        Vec & operator[](const unsigned int index) const;

    protected:
        Matrix(const unsigned int dimension);
        ~Matrix(void);
        
        Vec ** _data;

    private:
        Matrix(void){}
    };
}

#endif //__MATRIX_H__