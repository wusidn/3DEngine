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

        //  Log.info("parent() = {0}", parent());
        //  Log.info("position() = {0}", position());
        //  Log.info("worldCoordinate() = {0}", worldCoordinate());

         if(!Geometry::render(dp)){
             return false;
         }
         Log.info("Triangle Render");

        // Log.debug("---------------------------------------");
        //  for(auto i = 0; i < 3; ++i){
        //      Log.info("vertex[{0}] = {1}", i, *(vertexs() + i) + worldCoordinate());
        //  }
        // Log.debug("");
        // Log.debug("");
         return true;
     }

     const bool Triangle::draw(Camera & viewPort) const
     {
         if(!Geometry::draw(viewPort)){
             return false;
         }

         Log.info("Triangle Draw");
         return true;
     }
}