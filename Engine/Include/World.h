#pragma once
#ifndef __WORLD_H__
#define __WORLD_H__

#include "Node.h"
#include "Camera.h"
#include <vector>

using namespace std;

namespace engine
{
    class World : public Object
    {
    public:

        CREATEFUNC(World);
        static const vector<World *> & worldPool();

        // static void render(const int td);
        
        const Node & root(void) const;
        
        void append(Node & child);
        void remove(Node & child);
        
    protected:
        World(){}
        ~World();
        virtual const bool init();
        
        Node * _root;
    private:
        static vector<World *> _worldPool;
    };
}

#endif //__WORLD_H__