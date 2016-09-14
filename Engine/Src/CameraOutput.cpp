#include "CameraOutput.h"
#include "LogManager.h"

namespace engine
{
    using namespace tools;
    const bool CameraOutput::init(void)
    {
        if(!Node::init()){
            return false;
        }
        return true;
    }


    Camera & CameraOutput::camera(void) const
    {
        return *_camera;
    }
    void CameraOutput::camera(Camera & linkCamera)
    {
        _camera = &linkCamera;
    }

    const bool CameraOutput::render(const int td)
    {
        if(!Node::render(td)){
            return false;
        }

        if(!_camera){
            return false;
        }

        return camera().preparatory(td);
    }

    const bool CameraOutput::draw(Camera & viewPort)
    {
        if(!Node::draw(viewPort)){
            return false;
        }

        if(!_camera){
            return false;
        }

        //设置摄像机投影到gl空间的位置

        //拍照
        return camera().photograph();
    }
}