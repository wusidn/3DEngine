#pragma once
#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Node.h"
#include "Vec3.h"
#include "ColorRGBA.h"
#include "Matrix4.h"
#include <GL/glew.h>

namespace engine
{
    class Geometry : public Node
    {
    public:

    protected:
        virtual ~Geometry(void);
        virtual const bool init(void);

        void vertexsCount(const unsigned short count);
        void colorsCount(const unsigned short count);
        void indiesCount(const unsigned short count);

        const unsigned short vertexsCount(void) const;
        const unsigned short colorsCount(void) const;
        const unsigned short indiesCount(void) const;

        void vertex(const unsigned short index, const Vec3 & data);
        void color(const unsigned short index, const ColorRGBA & data);
        void indie(const unsigned short index, const unsigned short data);

        void vertexs(const Vec3 * data);
        void colors(const ColorRGBA * data);
        void indies(const unsigned short * data);

        void vertexs(const Vec3 * data, const unsigned short count, const unsigned short startIndex = 0);
        void colors(const ColorRGBA * data, const unsigned short count, const unsigned short startIndex = 0);
        void indies(const unsigned short * data, const unsigned short count, const unsigned short startIndex = 0);

        const Vec3 * vertexs(void) const;
        const ColorRGBA * colors(void) const;
        const unsigned short * indies(void) const;

        const GLuint vertexArrayObject(void) const;
        const GLuint vertexBufferObject(void) const;
        const GLuint indiesBufferObject(void) const;

        virtual const bool render(const int dp);
        virtual const bool draw(const Matrix4 & projection);
    private:

        Vec3 * _vertexs;
        ColorRGBA * _colors;
        unsigned short * _indies;

        Vec3 * _drawVertexs;

        GLuint _vertexArrayObject, _vertexBufferObject, _indiesBufferObject;
        unsigned short _vertexsCount, _colorsCount, _indiesCount;
        
    };
}

#endif //__GEOMETRY_H__