#include "World.h"
#include <algorithm>
#include <Zeus.h>

namespace engine
{

    vector<World *> World::_worldPool;

    const vector<World *> & World::worldPool()
    {
        return _worldPool;
    }


    World::~World()
    {
        auto index = std::find(_worldPool.begin(), _worldPool.end(), this);
        if(index != _worldPool.end())
        {
            _worldPool.erase(index);
        }
    }

    const bool World::init()
    {
        if(!Object::init()){
            return false;
        }
        _worldPool.push_back(this);
        retain();

        _root = &Node::create();
        _root->retain();
        _root->position(Vec3(.0f));

        return true;
    }
    
    const Node & World::root(void) const
    {
        return *_root;
    }

    void World::append(Node & child)
    {
        _root->append(child);
    }

    void World::remove(Node & child)
    {
        _root->remove(child);
    }

    const bool World::render(const int td)
    {
        return _root->render(td);
    }

     const bool World::draw(const Camera & viewPort) const
     {
         return true;
     }

}