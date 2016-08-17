#pragma once
#ifndef __NODE_H__
#define __NODE_H__

#include "Object.h"
#include "Vec4.h"
// #include "World.h"

#include <vector>

using namespace std;

namespace engine
{
    class Node : public Object
    {
        friend class World;
    public:
        Vec4 position, rotate, scale;
            
        CREATEFUNC(Node);
        
        
        Node * parent(void) const;
        vector<Node *> & chidren(void);
        
        void append(Node & child);
        void remove(Node & child);
        
        void clear(void);
        
        const Vec4 convertToWorldSpace(void) const;
        const Vec4 convertToNodeSpace(const Node &) const;
        
    protected:
        Node(void);
        
        virtual const bool init(void);
    private:
        Node * _parent;
        vector<Node *> _chidren;
        
        virtual const bool render(const float dp);
    };
}

#endif //__NODE_H__