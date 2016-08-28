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
        // verticees = new Vec3[3];
        return true;
    }

    const bool Triangle::init(const Vec3 & vertex_1, const Vec3 & vertex_2, const Vec3 & vertex_3)
    {
        if(vertex_1 == vertex_2 || vertex_2 == vertex_3 || vertex_1 == vertex_3){
            return false;
        }
        // vertices[0] = vertex_1;
        // vertices[1] = vertex_2;
        // vertices[2] = vertex_3;
        return true;
    }
}