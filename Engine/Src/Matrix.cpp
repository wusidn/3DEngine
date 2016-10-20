#include "Matrix.h"


namespace engine
{

    Matrix::Matrix(const unsigned int dimension)
    {
        _data = new Vec*[dimension];
    }

    Matrix::~Matrix(void)
    {
        delete[] _data;
    }

    Vec & Matrix::operator[](const unsigned int index) const
    {
        return **((Vec**)_data + index);
    }
}