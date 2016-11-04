#include "Circle.h"
#include <cmath>
#include "LogManager.h"


using namespace std;

namespace engine
{
    using namespace tools;

    Circle::Circle(void)
    {
        _density = 0.05;
    }

    Circle & Circle::create(const float r)
    {
        Circle & result = create();

        bool circleInit = result.radius(r);

        assert(circleInit);

        if(!circleInit){ result.initializeError(1); }

        return result;
    }

    const bool Circle::init(void)
    {
        if(!Geometry::init()){ return false; }

        return true;
    }

    const bool Circle::init(const float r)
    {
        if(r <= 1.0f){ return false; }

        _radius = r;
        return false;
    }

    const bool Circle::radius(const float r)
    {
        if(r <= 1.0f){ return false; }
        _radius = r;

        float perimeter = 2 * PI * r;
        vertexsCount(perimeter * _density + 1);
        indiesCount(vertexsCount() + 1);



        vertex(0, Vec3(0.0f));
        indie(0, 0);
        float intervalAngle = PI * 2 / (vertexsCount() - 1);

        for(int i = 0; i < vertexsCount() - 1; ++i)
        {
            vertex(i + 1, Vec3(_radius * cos(intervalAngle * i), _radius * sin(intervalAngle * i)));
            indie(i + 1, i + 1);
        }

        indie(vertexsCount(), 1);

        return true;
    }

    const float Circle::radius(void)
    {
        return _radius;
    }

    const bool Circle::render(const int dp)
     {
         if(!Geometry::render(dp)) { return false; }

         return true;
     }


    const bool Circle::draw(const Matrix4 & projection)
     {
         if(!Geometry::draw(projection)){ return false; }

        glBindVertexArray(vertexArrayObject());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiesBufferObject());

        glDrawElements(GL_TRIANGLE_FAN, indiesCount(), GL_UNSIGNED_SHORT, nullptr);

        return true;
     }

}