#include "Node.h"


namespace engine{

    Node::Node(void)
    {
        _parent = nullptr;
    }

    const bool Node::init(void)
    {
        if(!Object::init()){
            return false;
        }
        return true;
    }

    Node * Node::parent(void) const
    {
        return _parent;
    }

    vector<Node *> & Node::chidren(void) 
    {
        return _chidren;
    }

    const void Node::append(Node * child)
    {
        _chidren.push_back(child);
        child->retain();
    }

    const void Node::remove(Node * child)
    {
        auto item = _chidren.begin();
        while(item != _chidren.end()){
            if(*item == child){
                (*item)->release();
                item = _chidren.erase(item);
                continue;
            }
            item++;
        }
    }

    const void Node::clear(void)
    {
        for(auto item  = _chidren.begin(); item != _chidren.end(); ++item){
            (*item)->release();
        }
        _chidren.clear();
    }

    const Vec4 Node::convertToWorldSpace(void) const
    {
        return 0.0;
    }

    const Vec4 Node::convertToNodeSpace(const Node * node) const
    {
        return 0.0;
    }

    const bool Node::render(void)
    {
        return true;
    }
}