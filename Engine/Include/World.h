#pragma once
#ifndef __WORLD_H__
#define __WORLD_H__

#include "Node.h"
#include <vector>

using namespace std;

namespace engine
{
    class World : public Object
    {
    public:

        CREATEFUNC(World);
        static const vector<World *> & getWorldPool();

        const Node & root(void) const;
        
        void append(Node & child);
        void remove(Node & child);
        
    protected:
        World(){}
        ~World();
        virtual const bool init();
        
    private:
        static vector<World *> worldPool;
        Node * _root;
        virtual const bool render(void) const; 
    };
}

#endif //__WORLD_H__