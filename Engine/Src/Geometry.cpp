#include "Geometry.h"

namespace engine
{
    const bool Geometry::init(void)
    {
        if(!Node::init()){
            return false;
        }

        vertexs = colors = nullptr;
        verticeIndies = nullptr;
        return true;
    }

    void Geometry::vertexDataCount(const unsigned short count)
    {
        if(vertexs){
            delete[] vertexs;
        }

        if(!count){
            vertexs = nullptr;
            return;
        }

        vertexs = new Vec3[count];
    }

    void Geometry::colorDataCount(const unsigned short count)
    {
        if(colors){
            delete[] colors;
        }

        if(!count){
            colors = nullptr;
            return;
        }

        colors = new Vec4[count];
    }

    void Geometry::vertexIndieDataCount(const unsigned short count)
    {
        if(verticeIndies){
            delete[] verticeIndies;
        }

        if(!count){
            verticeIndies = nullptr;
        }

        verticeIndies = new unsigned short[count];
    }

    Geometry::~Geometry(void)
    {
        if(vertexs){
            delete[] vertexs;
        }
        if(colors){
            delete[] colors;
        }
        if(verticeIndies){
            delete[] verticeIndies;
        }
    }
}