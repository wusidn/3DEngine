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

    const bool Camera::preparatory(const int td)
    {
        return root().render(td);
    }

    const bool Camera::photograph(void)
    {
        return root().draw(*this);
    }
}