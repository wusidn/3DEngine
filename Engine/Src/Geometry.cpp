#include "Geometry.h"
#include <iostream>
#include <cstring>
#include "LogManager.h"
#include "Zeus.h"
#include "Matrix4.h"

using namespace std;

namespace engine
{
    using namespace tools;
    const bool Geometry::init(void)
    {
        if(!Node::init()){
            return false;
        }

        _vertexs = nullptr;
        _colors = nullptr;
        _indies = nullptr;
        _drawVertexs = nullptr;

        _vertexArrayObject = _vertexBufferObject = _indiesBufferObject = 0;

        _vertexsCount = _colorsCount = _indiesCount = 0;

        return true;
    }

    void Geometry::vertexsCount(const unsigned short count)
    {
        colorsCount(count);
        
        _vertexsCount = 0;
        if(_vertexs){
            delete[] _vertexs;
        }

        if(_drawVertexs){
            delete[] _drawVertexs;
        }

        if(!count){
            _vertexs = nullptr;
            return;
        }

        _vertexs = new Vec3[count];
        _drawVertexs = new Vec3[count];
        if(!_vertexs || !_drawVertexs) return;


        //申请顶点数组对象
        while(!_vertexArrayObject){
            glGenVertexArrays(1, &_vertexArrayObject);
        }

        //申请缓存对象
        while(!_vertexBufferObject){
            glGenBuffers(1, &_vertexBufferObject);
        }

        _vertexsCount = count;
    }

    void Geometry::colorsCount(const unsigned short count)
    {
        _colorsCount = 0;
        if(_colors){
            delete[] _colors;
        }

        if(!count){
            _colors = nullptr;
            return;
        }

        _colors = new ColorRGBA[count];
        if(!_colors) return;

        _colorsCount = count;
    }

    void Geometry::indiesCount(const unsigned short count)
    {
        _indiesCount = 0;

        if(_indies){
            delete[] _indies;
        }

        if(!count){
            _indies = nullptr;
        }

        _indies = new unsigned short[count];
        if(!_indies) return;

        //申请缓存对象
        while(!_indiesBufferObject){
            glGenBuffers(1, &_indiesBufferObject);
        }

        _indiesCount = count;
        memset(_indies, 0, sizeof(unsigned short) * _indiesCount);
    }




    const unsigned short Geometry::vertexsCount(void) const
    {
        return _vertexsCount;
    }
    
    const unsigned short Geometry::colorsCount(void) const
    {
        return _colorsCount;
    }

    const unsigned short Geometry::indiesCount(void) const
    {
        return _indiesCount;
    }




    const GLuint Geometry::vertexArrayObject(void) const
    {
        return _vertexArrayObject;
    }
    const GLuint Geometry::vertexBufferObject(void) const
    {
        return _vertexBufferObject;
    }
    const GLuint Geometry::indiesBufferObject(void) const
    {
        return _indiesBufferObject;
    }




    void Geometry::vertex(const unsigned short index, const Vec3 & data)
    {
        if(index >= _vertexsCount){
            //错误信息
            return;
        }
        *(_vertexs + index) = data;
    }

    void Geometry::color(const unsigned short index, const ColorRGBA & data)
    {
        if(index >= _colorsCount){
            //错误信息
            return;
        }
        *(_colors + index) = data;
    }

    void Geometry::indie(const unsigned short index, const unsigned short data)
    {
        if(index >= _indiesCount){
            //错误信息
            return;
        }
        *(_indies + index) = data;
    }


    void Geometry::vertexs(const Vec3 * data)
    {
        vertexs(data, _vertexsCount, 0);
    }
    
    void Geometry::vertexs(const Vec3 * data, const unsigned short count, const unsigned short startIndex)
    {
        memcpy(_vertexs + startIndex, data, (_vertexsCount - startIndex) * sizeof(Vec3));
    }
    
    void Geometry::colors(const ColorRGBA * data, const unsigned short count, const unsigned short startIndex )
    {
        memcpy(_colors + startIndex, data, (_colorsCount - startIndex) * sizeof(ColorRGBA));
    }

    void Geometry::colors(const ColorRGBA * data)
    {
        colors(data, _colorsCount, 0);
    }

    void Geometry::indies(const unsigned short * data, const unsigned short count, const unsigned short startIndex)
    {
        memcpy(_indies + startIndex, data, (_indiesCount - startIndex) * sizeof(unsigned short));
    }

    void Geometry::indies(const unsigned short * data)
    {
       indies(data, _indiesCount, 0);
    }



    const Vec3 * Geometry::vertexs(void) const 
    {
        return _vertexs;
    }
    const ColorRGBA * Geometry::colors(void) const
    {
        return _colors;
    }
    const unsigned short * Geometry::indies(void) const 
    {
        return _indies;
    }


    const bool Geometry::render(const int dp)
    {
        if(!Node::render(dp)){
            return false;
        }
        return true;
    }

    const bool Geometry::draw(const Matrix4 & projection)
    {
        if(!_vertexsCount){
            return false;
        }

        if(!Node::draw(projection)){
             return false;
        }

        if(_indiesCount){
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indiesBufferObject);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * _indiesCount, _indies, GL_STATIC_DRAW);
        }


        glBindVertexArray(_vertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);

        glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * _vertexsCount + sizeof(ColorRGBA) * _colorsCount, nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec3) * _vertexsCount, _drawVertexs);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vec3) * _vertexsCount, sizeof(ColorRGBA) * _colorsCount, _colors);


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void *)(sizeof(Vec3) * _vertexsCount));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        //启用着色器程序
        Zeus::instance().defaultShaderProgram().use();


        //创建旋转  缩放  平移到世界坐标 矩阵
        //旋转
        Matrix4 rotationMatrix = Matrix4::createRotationMatrix(rotate() + accumulativeRotateOffset());
        //缩放
        Matrix4 scaleMatrix = Matrix4::createScaleMatrix(scale() + accumulativeScaleOffset());
        //平移
        Matrix4 translationMatrix = Matrix4::createTranslationMatrix(position().convertToSize3() + worldCoordinateOffset());

        //m
        Matrix4 modelMatrix = rotationMatrix * scaleMatrix * translationMatrix;

        //v 

        //p



        return true;
    }

    Geometry::~Geometry(void)
    {
        if(_vertexs){
            delete[] _vertexs;
        }
        if(_colors){
            delete[] _colors;
        }
        if(_indies){
            delete[] _indies;
        }
        if(_drawVertexs){
            delete[] _drawVertexs;
        }

        if(_vertexBufferObject){
            glDeleteBuffers(1, &_vertexBufferObject);
        }
        if(_vertexBufferObject){
            glDeleteBuffers(1, &_indiesBufferObject);
        }
        if(_vertexBufferObject){
            glDeleteVertexArrays(1, &_vertexArrayObject);
        }
    }
}