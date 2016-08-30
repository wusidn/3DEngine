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
        child.retain();
    }

    void Node::remove(Node & child)
    {
        auto item = _chidren.begin();
        while(item != _chidren.end()){
            if(*item == &child){
                (*item)->release();
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
    }

    const Vec3 Node::position(void) const
    {
        return _position;
    }

    void Node::rotate(const Vec3 & vSource)
    {
        _rotate = vSource;
    }

    const Vec3 Node::rotate(void) const
    {
        return _rotate;
    }

    void Node::scale(const Vec3 & vSource)
    {
        _scale = vSource;
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

        Vec3 tempPosition = _position;
        Node * tempNode = parent();
        if(!tempNode){
            return 0.0f;
        }
        //旋转

        //缩放

        //平移
        tempPosition += tempNode->worldCoordinate();
        //当前世界坐标有效
        _worldCoordinateInvalid = true;
        return tempPosition;
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