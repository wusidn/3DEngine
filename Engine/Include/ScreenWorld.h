#pragma once
#ifndef __SCREEN_WORLD_H__
#define __SCREEN_WORLD_H__
#include "World.h"

namespace engine
{
    class ScreenWorld : public World
    {
    public:
        static ScreenWorld & instance(void);
    protected:
        ScreenWorld();
        virtual ~ScreenWorld();
        virtual const bool init(void);
    private:
        CREATEFUNC(ScreenWorld);
        static ScreenWorld * _instance;
    };
}

#endif //__SCREEN_WORLD_H__