#include "../Include/World.h"

vector<World *> World::worldPool;

const vector<World *> & World::getWorldPool()
{
    return worldPool;
}


Wrold::World()
{
    
}

World::~World()
{
    auto index = find(worldPool.begin(), worldPool.end(), this);
    if(index !== worldPool.end())
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
