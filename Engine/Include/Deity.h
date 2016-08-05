#pragma once
#ifdef __DEITY_H__
#define __DEITY_H__

#include "Object.h"

namespace engine
{
    class Deity : public Object
    {
    public:
        static Deity & getInstance(void);
    };
}

#endif //__DEITY_H__