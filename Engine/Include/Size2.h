#pragma once
#ifndef __SIZE_H__
#define __SIZE_H__

#include "Struct.h"

namespace engine
{
    class Size2 : public Struct
    {
    public:

        float width, height;

        Size2(void);
        Size2(const float v);
        Size2(const float width, const float height);
        Size2(const Size2 & copy);


        const Size2 operator+(const Size2 & param) const;
        const Size2 operator-(const Size2 & param) const;
        
    };
}

#endif //__SIZE_H__