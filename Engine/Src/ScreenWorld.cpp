#include "ScreenWorld.h"
#include "LogManager.h"

#include "Matrix4.h"

namespace engine
{
    using namespace tools;
    ScreenWorld * ScreenWorld::_instance = nullptr;
    ScreenWorld & ScreenWorld::instance(void)
    {
        if(!_instance){ _instance = &create(); }
        return *_instance;
    }

    const Camera & ScreenWorld::screenCamera(void) const
    {
        return *_screenCamera;
    }

    const bool ScreenWorld::init(void)
    {
        if(!World::init()){ return false; }

        _screenCamera = &Camera::create();
        _screenCamera->retain();
        
        return true;
    }

    const bool ScreenWorld::render(const int dt)
    {
        return _root->render(dt);
    }

    const bool ScreenWorld::draw(void)
    {
        return root().draw(Matrix4(1.0f));
    }

    ScreenWorld::~ScreenWorld()
    {
        _screenCamera->release();
        _instance = nullptr;
    }
}