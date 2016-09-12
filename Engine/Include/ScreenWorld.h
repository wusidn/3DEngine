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

        const Camera & screenCamera(void) const;
    protected:
        ScreenWorld(){}
        virtual ~ScreenWorld();
        virtual const bool init(void);

        virtual const bool draw(void);
        
    private:
        CREATEFUNC(ScreenWorld);
        static ScreenWorld * _instance;

        Camera * _screenCamera;
    };
}

#endif //__SCREEN_WORLD_H__