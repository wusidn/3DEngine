#include "Zeus.h"
#include "LogManager.h"

#include <GL/freeglut.h>

namespace engine
{

    using namespace tools;

    Zeus & Zeus::getInstance()
    {
        static Zeus & instance = Zeus::create();
        instance.retain();
        return instance;
    }

    const bool Zeus::init()
    {
        if(!Object::init())
        {
            return false;
        }

        glutReshapeFunc([](const int _width, const int _height){
            Log.info("width: {0}, height: {1}", _width, _height);
        });

        return true;
    }

    void Zeus::reshapeWindow(const int width, const int height) const
    {
        if(!width * height)
        {
            Log.error("Zeus::reshapeWindow: width and height Can not be zero");
            return;
        }
        glutReshapeWindow(width, height);
    }
}