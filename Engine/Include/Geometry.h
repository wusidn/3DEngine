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

    protected:
        virtual ~Geometry(void);
        virtual const bool init(void);

        void vertexDataCount(const unsigned short count);
        void colorDataCount(const unsigned short count);
        void vertexIndieDataCount(const unsigned short count);
    private:

        Vec3 * vertexs;
        Vec4 * colors;
        unsigned short * verticeIndies;
        unsigned int _vertexArrayObject, _vertexBufferObject, _indiesBufferObject;
    };
}

#endif //__GEOMETRY_H__