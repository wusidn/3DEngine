#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

#include "Object.h"

namespace engine
{
    class Scene : public Object
    {
    public:
        CREATEFUNC(Scene);

    protected:
        virtual const bool init();
    };
}

#endif //__SCENE_H__