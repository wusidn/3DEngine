#include "Camera.h"

namespace engine
{
    const bool Camera::init(void)
    {
        if(!Node::init()){ return false; }

        position(Vec3(.0f));
        // __viewportSize = Vec3(.0f);
        return true;
    }

    const bool Camera::preparatory(const int dt)
    {
        return root().render(dt);
    }

    const bool Camera::photograph(void)
    {
        return root().draw(Matrix4(1.0));
    }
}