#include "Triangle.h"

namespace engine
{

    Triangle & Triangle::create(const Vec3 & vertex_1, const Vec3 & vertex_2, const Vec3 & vertex_3)
    {
        Triangle & result = create();
        if(!result.init(vertex_1, vertex_2, vertex_3)){
            result.initializeError(1);
        }
        return result;
    }

    const bool Triangle::init(void)
    {
        if(!Geometry::init()){
            return false;
        }
        return true;
    }

    const bool Triangle::init(const Vec3 & vertex_1, const Vec3 & vertex_2, const Vec3 & vertex_3)
    {
        if(vertex_1 == vertex_2 || vertex_2 == vertex_3 || vertex_1 == vertex_3){
            return false;
        }
        _vertex_1 = vertex_1;
        _vertex_2 = vertex_2;
        _vertex_3 = vertex_3;
        return true;
    }
}