#include "Triangle.h"
#include "LogManager.h"

namespace engine
{

    using namespace tools;
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

        vertexDataCount(3);
        return true;
    }

    const bool Triangle::init(const Vec3 & vertex_1, const Vec3 & vertex_2, const Vec3 & vertex_3)
    {
        // if(vertex_1 == vertex_2 || vertex_2 == vertex_3 || vertex_1 == vertex_3){
        //     return false;
        // }
        vertexData(0, vertex_1);
        vertexData(1, vertex_2);
        vertexData(2, vertex_3);

        return true;
    }

     const bool Triangle::render(const int dp)
     {
         position(position() + Vec3(1.0f, 1.0f));

         if(!Geometry::render(dp)){
             return false;
         }

         return true;
     }

     const bool Triangle::draw(Camera & viewPort)
     {
         if(!Geometry::draw(viewPort)){
             return false;
         }

         return true;
     }
}