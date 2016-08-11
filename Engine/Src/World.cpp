#include "World.h"
#include <algorithm>


namespace engine
{
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
        if(!Object::init()){
            return false;
        }
        worldPool.push_back(this);

        root = &Node::create();
        root->retain();

        return true;
    }

    void World::append(Node & child)
    {
        root->append(child);
    }

    void World::remove(Node & child)
    {
        root->remove(child);
    }

    const bool World::render(void) const
    {
        return true;
    }
}