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
        vertexDataCount(3);
        colorDataCount(3);
        vertexIndieDataCount(3);

        vertexData(0, vertex_1);
        vertexData(1, vertex_2);
        vertexData(2, vertex_3);

        colorData(0, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f));
        colorData(1, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f));
        colorData(2, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f));

        vertexIndieData(0, 0);
        vertexIndieData(1, 1);
        vertexIndieData(2, 2);

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

        glBindVertexArray(vertexArrayObject());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiesBufferObject());

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, nullptr);


        return true;
     }
}