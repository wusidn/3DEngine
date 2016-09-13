#include "ScreenWorld.h"
#include "LogManager.h"

namespace engine
{
    using namespace tools;
    ScreenWorld * ScreenWorld::_instance = nullptr;
    ScreenWorld & ScreenWorld::instance(void)
    {
        if(!_instance){
            _instance = &create();
        }
        return *_instance;
    }

    const Camera & ScreenWorld::screenCamera(void) const
    {
        return *_screenCamera;
    }

    const bool ScreenWorld::init(void)
    {
        if(!World::init()){
            return false;
        }

        _screenCamera = &Camera::create();
        _screenCamera->retain();
        
        return true;
    }

    const bool ScreenWorld::render(const int td)
    {
        Log.info("ScreenWorld Render");

        return _root->render(td);
    }

    const bool ScreenWorld::draw(void)
    {

        Log.info("ScreenWorld Draw");

        return root().draw(*_screenCamera);
    }

    ScreenWorld::~ScreenWorld()
    {
        _screenCamera->release();
        _instance = nullptr;
    }
}