#pragma once
#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Node.h"
#include "Vec3.h"
#include "ColorRGBA.h"
#include "Camera.h"

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
        const ColorRGBA * colors(void) const;
        const unsigned short * verticeIndies(void) const;

        void vertexData(const unsigned short index, const Vec3 & data);
        void colorData(const unsigned short index, const ColorRGBA & data);
        void vertexIndieData(const unsigned short index, const unsigned short data);

        virtual const bool render(const int dp);
        virtual const bool draw(Camera & viewPort) const;
    private:

        Vec3 * _vertexs;
        ColorRGBA * _colors;
        unsigned short * _verticeIndies;

        Vec3 * _drawVertexs;

        unsigned short _vertexDataCount, _colorDataCount, _vertexIndieDataCount;
        
    };
}

#endif //__GEOMETRY_H__