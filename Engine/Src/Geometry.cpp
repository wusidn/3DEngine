#include "Geometry.h"
#include <iostream>
#include <cstring>
#include "LogManager.h"

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

        _vertexDataCount = count;
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

    const Vec3 * Geometry::vertexs(void) const 
    {
        return _vertexs;
    }
    const ColorRGBA * Geometry::colors(void) const
    {
        return _colors;
    }
    const unsigned short * Geometry::verticeIndies(void) const 
    {
        return _verticeIndies;
    }

    const bool Geometry::render(const int dp)
    {
        if(!Node::render(dp)){
            return false;
        }
        return true;
    }

    const bool Geometry::draw(Camera & viewPort) const
    {
        //视口坐标
        Vec3 viewPortSpacePosition = viewPort.convertToNodeSpace(position());

        for(auto i = 0; i < _vertexDataCount; ++i){
            _drawVertexs[i] = vertexs()[i] + viewPortSpacePosition;
            Log.info("{0}", _drawVertexs[i]);
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
        if(_drawVertexs){
            delete[] _drawVertexs;
        }
    }
}