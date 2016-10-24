#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Node.h"
#include "Size3.h"
#include "Matrix4.h"


namespace engine
{
    class Camera : public Node
    {
        friend class CameraOutput;
    public:
        CREATEFUNC(Camera);
        // static Camera & create(const Vec3 & _position, )
        Vec3 target(void) const;
        void target(const Vec3 & t);

        //attribute
    protected:
        virtual const bool init(void);

        //准备
        virtual const bool preparatory(const int dt);
        //拍照
        virtual const bool photograph(void);

        virtual ~Camera(){}
    private:
        Camera(){}

        // void calculateProjectionMatrix(void);
        Vec3 _target, _up;
        Matrix4 _projectionMatrix;
        // Vec3 _viewportSize;
    };
}


#endif //__CAMERA_H__