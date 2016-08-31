#include "Node.h"


namespace engine
{
    Node::Node(void)
    {
        _parent = nullptr;
    }

    const bool Node::init(void)
    {
        if(!Object::init()){
            return false;
        }
        worldCoordinateInvalid();
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

    void Node::append(Node & child)
    {
        _chidren.push_back(&child);
        if(child._parent){
            child._parent->remove(child);
        }
        child._parent = this;
        child.retain();
    }

    void Node::remove(Node & child)
    {
        auto item = _chidren.begin();
        while(item != _chidren.end()){
            if(*item == &child){
                (*item)->release();
                (*item)->_parent = nullptr;
                item = _chidren.erase(item);
                continue;
            }
            item++;
        }
    }

    void Node::clear(void)
    {
        for(auto item  = _chidren.begin(); item != _chidren.end(); ++item){
            (*item)->release();
        }
        _chidren.clear();
    }

    void Node::position(const Vec3 & vSource)
    {
        _position = vSource;
        worldCoordinateInvalid();
    }

    const Vec3 Node::position(void) const
    {
        return _position;
    }

    void Node::rotate(const Vec3 & vSource)
    {
        _rotate = vSource;
        posterityWorldCoordinateInvalid();
    }

    const Vec3 Node::rotate(void) const
    {
        return _rotate;
    }

    void Node::scale(const Vec3 & vSource)
    {
        _scale = vSource;
        posterityWorldCoordinateInvalid();
    }

    const Vec3 Node::scale(void) const
    {
        return _scale;
    }

    const Vec3 Node::convertToWorldSpace(const Vec3 & vSource)
    {
        return worldCoordinate() + vSource;
    }

    const Vec3 Node::convertToNodeSpace(const Vec3 & vSource)
    {
        return vSource - worldCoordinate();
    }

    const Vec3 Node::worldCoordinate(void)
    {
        if(_worldCoordinateInvalid){
            return _worldCoordinate;
        }

        _worldCoordinate = _position;
        Node * tempNode = parent();
        if(!tempNode){
            return _worldCoordinate;
        }
        //旋转

        //缩放

        //平移
        _worldCoordinate += tempNode->worldCoordinate();
        //当前世界坐标有效
        _worldCoordinateInvalid = true;
        return _worldCoordinate;
    }

    void Node::worldCoordinateInvalid(void)
    {
        _worldCoordinateInvalid = false;
        posterityWorldCoordinateInvalid();
    }

    void Node::posterityWorldCoordinateInvalid(void)
    {
        for(auto node : _chidren){
            node->worldCoordinateInvalid();
        }
    }

    const bool Node::render(const int dp)
    {
        //计算运动区间

        //更新世界坐标系位置
        worldCoordinate();

        for(auto node : _chidren){
            if(!node->render(dp)){
                return false;
            }
        }
        return true;
    }

    void Node::draw(void) const
    {
        
    }
}