#pragma once
#ifndef __CAMERA_OUTPUT_H__
#define __CAMERA_OUTPUT_H__

#include "Node.h"
#include "Camera.h"

namespace engine
{
    class CameraOutput : public Node
    {
    public:
        CREATEFUNC(CameraOutput);

        Camera & camera(void) const;
        void camera(Camera & linkCamera);

    protected:

        virtual const bool init(void);

        virtual const bool render(const int dt);
        //绘制
        virtual const bool draw(Camera & viewPort);
    private:
        Camera * _camera;
    };
}

#endif //__CAMERA_OUTPUT_H__