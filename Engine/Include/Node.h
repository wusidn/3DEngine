#pragma once
#ifndef __NODE_H__
#define __NODE_H__

#include "Object.h"
#include "Vec4.h"

#include <vector>

using namespace std;

namespace engine
{
    class Node : public Object
    {
    public:
        Vec4 position, rotate, scale;
            
        CREATEFUNC(Node);   
        
        
        Node * parent(void) const;
        vector<Node *> & chidren(void);
        
        const void append(Node & child);
        const void remove(Node & child);
        
        const void clear(void);
        
        const Vec4 convertToWorldSpace(void) const;
        const Vec4 convertToNodeSpace(const Node &) const;
        
    protected:
        Node(void);
        
        virtual const bool init(void);
    private:
        Node * _parent;
        vector<Node *> _chidren;
        
        virtual const bool render(void);
    };
}

#endif //__NODE_H__