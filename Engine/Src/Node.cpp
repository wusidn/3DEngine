#include "Node.h"
#include "LogManager.h"
#include "Matrix4.h"

namespace engine
{
    using namespace tools;
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

    Node & Node::root(void)
    {
        Node * result = this;
        while(result->parent()){
            result = result->parent();
        }
        return *result;
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
                break;
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
        return worldCoordinate() + vSource.convertToSize3();
    }

    const Vec3 Node::convertToNodeSpace(const Vec3 & vSource)
    {
        return vSource - worldCoordinate().convertToSize3();
    }

    const Vec3 Node::worldCoordinate(void)
    {
        if(_worldCoordinateInvalid){
            return _worldCoordinate;
        }

        _worldCoordinate = _position;
        if(!_parent){
            return _worldCoordinate;
        }

        Vec3 parentWorldCoordinate = _parent->worldCoordinate().convertToSize3();

        //累计旋转   //累计缩放  //累计平移(也就是父级世界坐标)

        //累计旋转  × 累计缩放 ×  累计平移 × 局域坐标 = 模型世界坐标

        // //旋转
        // Matrix4 rotationMatrix = Matrix4::createRotationMatrix(_parent->rotate());
        // //缩放
        // Matrix4 scaleMatrix = Matrix4::createScaleMatrix(_parent->scale());
        // //平移
        // _worldCoordinate = rotationMatrix * scaleMatrix * (_position + _parent->worldCoordinate().convertToSize3());

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

    const bool Node::render(const int dt)
    {
        //计算运动区间

        //更新世界坐标系位置
        worldCoordinate();

        for(auto node : _chidren){
            if(!node->render(dt)){
                return false;
            }
        }
        return true;
    }

    const bool Node::draw(const Matrix4 & projection)
    {

        for(auto node : _chidren){
            if(!node->draw(projection)){
                return false;
            }
        }
        return true;
    }
}