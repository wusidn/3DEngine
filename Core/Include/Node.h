#pragma once
#ifndef __NODE_H__
#define __NODE_H__

#include "Object.h"
#include "Vec4.h"

#include <vector>

using namespace std;

class Node : public Object
{
public:
    Vec4 position, rotate, scale;
        
    CREATEFUNC(Node);   
    virtual const bool init(void);
    
    Node * parent(void) const;
    vector<Node *> & chidren(void);
    
    const void append(Node * child);
    const void remove(Node * child);
    
    const void clear(void);
    
protected:
    Node(void);
private:
    Node * _parent;
    vector<Node *> _chidren;
    
    virtual const bool _render(void) const;
};

#endif //__NODE_H__