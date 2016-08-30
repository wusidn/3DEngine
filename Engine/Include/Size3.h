#pragma once
#ifndef __SIZE3_H__
#define __SIZE3_H__

#include "Size2.h"

namespace engine
{
    class Size3 : public Size2
    {
    public:
        Size3(void);
        Size3(const float v);
        Size3(const float _width, const float _height);
        Size3(const float _width, const float _height, const float _depth);
        Size3(const Size3 & copy);
        Size3(const Size2 & copy);
        
        float depth;
    };
}

#endif //__SIZE3_H__