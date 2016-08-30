#include "Camera.h"

namespace engine
{
    const bool Camera::init(void)
    {
        if(!Node::init()){
            return false;
        }

        position(Vec3(.0f));
        _viewportSize = Vec3(.0f);
        return true;
    }
}