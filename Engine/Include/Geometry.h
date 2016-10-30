#pragma once
#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <GL/glew.h>

#include "Node.h"
#include "Vec3.h"
#include "Matrix4.h"
#include "Materia.h"

namespace engine
{
    class Geometry : public Node
    {
    public:
        const bool bindMateria(Materia & m);
    protected:
        virtual ~Geometry(void);
        virtual const bool init(void);

        void vertexsCount(const unsigned short count);
        void indiesCount(const unsigned short count);

        const unsigned short vertexsCount(void) const;
        const unsigned short indiesCount(void) const;

        void vertex(const unsigned short index, const Vec3 & data);
        void indie(const unsigned short index, const unsigned short data);

        void vertexs(const Vec3 * data);
        void indies(const unsigned short * data);

        void vertexs(const Vec3 * data, const unsigned short count, const unsigned short startIndex = 0);
        void indies(const unsigned short * data, const unsigned short count, const unsigned short startIndex = 0);

        const Vec3 * vertexs(void) const;
        const unsigned short * indies(void) const;

        const GLuint vertexArrayObject(void) const;
        const GLuint vertexBufferObject(void) const;
        const GLuint indiesBufferObject(void) const;

        virtual const bool render(const int dp);
        virtual const bool draw(const Matrix4 & projection);
    private:

        Vec3 * _vertexs;
        unsigned short * _indies;
        unsigned short _vertexsCount, _indiesCount;
        
        Materia * _materia;

        GLuint _vertexArrayObject, _vertexBufferObject, _indiesBufferObject;
        
    };
}

#endif //__GEOMETRY_H__