#include "Geometry.h"
#include <iostream>
#include <cstring>

using namespace std;

namespace engine
{
    const bool Geometry::init(void)
    {
        if(!Node::init()){
            return false;
        }

        _vertexs = nullptr;
        _colors = nullptr;
        _verticeIndies = nullptr;

        _vertexDataCount = _colorDataCount = _vertexIndieDataCount = 0;

        return true;
    }

    void Geometry::vertexDataCount(const unsigned short count)
    {
        _vertexDataCount = 0;
        if(_vertexs){
            delete[] _vertexs;
        }

        if(!count){
            _vertexs = nullptr;
            return;
        }

        _vertexs = new Vec3[count];
        if(!_vertexs) return;

        _vertexDataCount = count;
        memset(_vertexs, 0, sizeof(Vec3) * _vertexDataCount);
    }

    void Geometry::colorDataCount(const unsigned short count)
    {
        _colorDataCount = 0;
        if(_colors){
            delete[] _colors;
        }

        if(!count){
            _colors = nullptr;
            return;
        }

        _colors = new ColorRGBA[count];
        if(!_colors) return;

        _colorDataCount = count;
        memset(_colors, 0, sizeof(ColorRGBA) * _colorDataCount);
    }

    void Geometry::vertexIndieDataCount(const unsigned short count)
    {
        _vertexIndieDataCount = 0;

        if(_verticeIndies){
            delete[] _verticeIndies;
        }

        if(!count){
            _verticeIndies = nullptr;
        }

        _verticeIndies = new unsigned short[count];
        if(!_verticeIndies) return;

        _vertexIndieDataCount = count;
        memset(_verticeIndies, 0, sizeof(unsigned short) * _vertexIndieDataCount);
    }

    const unsigned short Geometry::vertexDataCount(void) const
    {
        return _vertexDataCount;
    }
    
    const unsigned short Geometry::colorDataCount(void) const
    {
        return _colorDataCount;
    }

    const unsigned short Geometry::vertexIndieDataCount(void) const
    {
        return _vertexIndieDataCount;
    }

    void Geometry::vertexData(const unsigned short index, const Vec3 & data)
    {
        if(index >= _vertexDataCount){
            //错误信息
            return;
        }
        *(_vertexs + index) = data;
    }

    void Geometry::colorData(const unsigned short index, const ColorRGBA & data)
    {
        if(index >= _colorDataCount){
            //错误信息
            return;
        }
        *(_colors + index) = data;
    }

    void Geometry::vertexIndieData(const unsigned short index, const unsigned short data)
    {
        if(index >= _vertexIndieDataCount){
            //错误信息
            return;
        }
        *(_verticeIndies + index) = data;
    }

    const bool Geometry::render(const int dp)
    {
        if(!Node::render(dp)){
            return false;
        }
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
        if(_verticeIndies){
            delete[] _verticeIndies;
        }
    }
}