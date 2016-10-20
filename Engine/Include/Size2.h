#pragma once
#ifndef __SIZE_H__
#define __SIZE_H__

#include "Vec.h"
#include <iostream>

using namespace std;

namespace engine
{
    class Size2 : public Vec
    {
    public:

        Size2(void);
        Size2(const float v);
        Size2(const float width, const float height);
        Size2(const Size2 & copy);


        const Size2 operator+(const Size2 & param) const;
        const Size2 operator-(const Size2 & param) const;

        friend ostream & operator<<(ostream & _stream, const Size2 & param); 

        float width, height;
    };
}

#endif //__SIZE_H__