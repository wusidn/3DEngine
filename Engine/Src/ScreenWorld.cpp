#include "ScreenWorld.h"

namespace engine
{

    ScreenWorld & ScreenWorld::instance(void)
    {
        if(!_instance){
            _instance = &create();
        }

        return *_instance;
    }

    const bool ScreenWorld::init(void)
    {
        if(!World::init()){
            return false;
        }
        
        return true;
    }

    ScreenWorld::ScreenWorld()
    {

    }
    ScreenWorld::~ScreenWorld()
    {
        _instance = nullptr;
    }
}