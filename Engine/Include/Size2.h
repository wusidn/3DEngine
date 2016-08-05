#pragma once
#ifndef __SIZE_H__
#define __SIZE_H__

#include "Struct.h"

namespace engine
{
    class Size2 : public Struct
    {
    public:

        Size2(void);
        Size2(const float v);
        Size2(const float width, const float height);
        Size2(const Size2 & copy);
        
        float width, height;
    };
}

#endif //__SIZE_H__