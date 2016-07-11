#include "World.h"
#include <algorithm>


namespace engine{

    vector<World *> World::worldPool;

    const vector<World *> & World::getWorldPool()
    {
        return worldPool;
    }


    World::~World()
    {
        auto index = std::find(worldPool.begin(), worldPool.end(), this);
        if(index != worldPool.end())
        {
            worldPool.erase(index);
        }
    }

    const bool World::init()
    {
        if(!Node::init()){
            return false;
        }
        worldPool.push_back(this);
        return true;
    }

    const bool World::render(void) const
    {
        return true;
    }
}