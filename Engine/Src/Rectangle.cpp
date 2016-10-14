#include "Rectangle.h"


namespace engine
{
    Rectangle & Rectangle::create(const Size2 & _size)
    {
        Rectangle & result = create();

        bool rectangleInit = result.init(_size);

        assert(rectangleInit);

        if(!rectangleInit){
            result.initializeError(1);
        }

        return result;
    }

    const bool Rectangle::init(void)
    {
        if(!Geometry::init()){
            return false;
        }
        vertexsCount(4);
        indiesCount(4);
        return true;
    }

    const bool Rectangle::init(const Size2 & _size)
    {
        this->_size = _size;
        Vec3 tempVertexs[4] = {Vec3(.0f, .0f), Vec3(_size.width, .0f), Vec3(.0f, _size.height), Vec3(_size.width, _size.height)};
        vertexs(tempVertexs);

        ColorRGBA tempColors[4] = {ColorRGBA(1.0f, .0f, .0f), ColorRGBA(.0f, 1.0f, .0f), ColorRGBA(1.0f, .0f, .0f), ColorRGBA(.0f, 1.0f, .0f)};
        colors(tempColors);

        unsigned short tempIndies[4] = {0, 1, 2, 3};
        indies(tempIndies);

        return true;
    }

    const bool Rectangle::render(const int dp)
     {
         if(!Geometry::render(dp)){
             return false;
         }

         return true;
     }

     const bool Rectangle::draw(Camera & viewPort)
     {
         if(!Geometry::draw(viewPort)){
             return false;
         }

        glBindVertexArray(vertexArrayObject());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiesBufferObject());

        glDrawElements(GL_TRIANGLE_STRIP, indiesCount(), GL_UNSIGNED_SHORT, nullptr);

        return true;
     }

}