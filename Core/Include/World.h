#pragma once
#ifndef __WORLD_H__
#define __WORLD_H__

#include "Node.h"
#include <vector>

using namespace std;

class World : public Node
{
public:

    CREATEFUNC(World);
    static const vector<World *> & getWorldPool();
    
protected:
    World(){}
    ~World();
    virtual const bool init();
    
private:
    static vector<World * > worldPool;
    
    virtual const bool render(void) const; 
};

#endif //__WORLD_H__