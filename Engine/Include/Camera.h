#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Node.h"


namespace engine
{
    class Camera : public Node
    {
    public:
        CREATEFUNC(Camera);
    protected:
        virtual const bool init(void); 
        virtual ~Camera(){}
    private:
        Camera(){}

        Vec3 _viewportSize;
    };
}


#endif //__CAMERA_H__