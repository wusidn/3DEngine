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

        const unsigned short vertexDataCount(void) const;
        const unsigned short colorDataCount(void) const;
        const unsigned short vertexIndieDataCount(void) const;

        const Vec3 * vertexs(void) const;
        const Vec4 * colors(void) const;
        const unsigned short * verticeIndies(void) const;

        virtual const bool render(const int dp);
    private:

        Vec3 * _vertexs;
        Vec4 * _colors;
        unsigned short * _verticeIndies;
    };
}

#endif //__GEOMETRY_H__