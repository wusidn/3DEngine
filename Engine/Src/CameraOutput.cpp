#include "CameraOutput.h"

namespace engine
{
    const bool CameraOutput::init(void)
    {
        if(!Node::init()){
            return false;
        }
        return true;
    }

    const bool CameraOutput::render(const int td)
    {
        if(!Node::render(td)){
            return false;
        }

        if(!_camera){
            return false;
        }

        return camera().root().render(td);
    }

    const bool CameraOutput::draw(Camera & viewPort) const
    {
        if(!Node::draw(viewPort)){
            return false;
        }

        if(!_camera){
            return false;
        }

        return camera().root().draw(viewPort);
    }
}