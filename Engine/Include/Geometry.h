#pragma once
#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <GL/glew.h>

#include "Node.h"
#include "Vec3.h"
#include "Matrix4.h"
#include "Materia.h"
#include "ShaderProgram.h"

namespace engine
{
    using namespace tools;
    class Geometry : public Node
    {
    public:
        const bool bindMateria(Materia & m);
    protected:
        virtual ~Geometry(void);
        virtual const bool init(void);

        //指定数据大小
        void vertexsCount(const unsigned short count);
        void indiesCount(const unsigned short count);

        //获取数据大小
        const unsigned short vertexsCount(void) const;
        const unsigned short indiesCount(void) const;

        //修改指定位置数据
        void vertex(const unsigned short index, const Vec3 & data);
        void indie(const unsigned short index, const unsigned short data);

        //全部数据一次写入
        void vertexs(const Vec3 * data);
        void indies(const unsigned short * data);

        //指定位置写入指定长度的数据
        void vertexs(const Vec3 * data, const unsigned short count, const unsigned short startIndex = 0);
        void indies(const unsigned short * data, const unsigned short count, const unsigned short startIndex = 0);

        //数据起始地址
        const Vec3 * vertexs(void) const;
        const unsigned short * indies(void) const;

        //顶点对象
        const GLuint vertexArrayObject(void) const;
        //顶点数据缓存对象
        const GLuint vertexBufferObject(void) const;
        //顶点数据顺序对象
        const GLuint indiesBufferObject(void) const;

        virtual const bool render(const int dp);
        virtual const bool draw(const Matrix4 & projection);
    private:

        //创建并使用当前设置所需要的着色器
        const bool updateShaderProgram(void);

        //顶点数据及顺序
        Vec3 * _vertexs;
        unsigned short * _indies;
        unsigned short _vertexsCount, _indiesCount;

        string customVertextShaderFile, customFragmentShaderFile;
        
        //材质对象
        Materia * _materia;

        //着色器对象
        ShaderProgram * _shaderProgram;

        //gl对象
        GLuint _vertexArrayObject, _vertexBufferObject, _indiesBufferObject;
        
    };
}

#endif //__GEOMETRY_H__