#include "Geometry.h"

namespace engine
{
    const unsigned int Geometry::getVertexArrayObject(void) const
    {
        return _vertexArrayObject;
    }

    const unsigned int Geometry::getVertexBufferObject(void) const
    {
        return _vertexBufferObject;
    }

    const unsigned int Geometry::getIndiesBufferObject(void) const
    {
        return _indiesBufferObject;
    }
}