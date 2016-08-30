#include "Geometry.h"

namespace engine
{
    const bool Geometry::init(void)
    {
        if(!Node::init()){
            return false;
        }

        _vertexs = _colors = nullptr;
        _verticeIndies = nullptr;

        return true;
    }

    void Geometry::vertexDataCount(const unsigned short count)
    {
        if(_vertexs){
            delete[] _vertexs;
        }

        if(!count){
            _vertexs = nullptr;
            return;
        }

        _vertexs = new Vec3[count];
    }

    void Geometry::colorDataCount(const unsigned short count)
    {
        if(_colors){
            delete[] _colors;
        }

        if(!count){
            _colors = nullptr;
            return;
        }

        _colors = new Vec4[count];
    }

    void Geometry::vertexIndieDataCount(const unsigned short count)
    {
        if(_verticeIndies){
            delete[] _verticeIndies;
        }

        if(!count){
            _verticeIndies = nullptr;
        }

        _verticeIndies = new unsigned short[count];
    }

    const unsigned short Geometry::vertexDataCount(void) const
    {
        return sizeof(_verticeIndies) / sizeof(Vec3);
    }
    
    const unsigned short Geometry::colorDataCount(void) const
    {
        return sizeof(_colors) / sizeof(Vec4);
    }

    const unsigned short Geometry::vertexIndieDataCount(void) const
    {
        return sizeof(_verticeIndies) / sizeof(unsigned short);
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