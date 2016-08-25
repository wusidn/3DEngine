#include "Geometry.h"

namespace engine
{
    const bool Geometry::init(void)
    {
        if(!Node::init()){
            return false;
        }

        return true;
    }
}