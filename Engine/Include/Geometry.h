#pragma once
#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Node.h"
#include "Vec3.h"
#include "Vec4.h"

namespace engine
{
    class Geometry : public Node
    {
    public:
        const unsigned int getVertexArrayObject(void) const;
        const unsigned int getVertexBufferObject(void) const;
        const unsigned int getIndiesBufferObject(void) const;
    protected:
        virtual ~Geometry();
        virtual const bool init(void);
    private:

        Geometry(){}

        Vec3 * vertices;
        Vec4 * colors;
        unsigned short * vertexIndies;
        unsigned int _vertexArrayObject, _vertexBufferObject, _indiesBufferObject;
    };
}

#endif //__GEOMETRY_H__