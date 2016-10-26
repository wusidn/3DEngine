#include "Node.h"
#include "LogManager.h"
#include "Matrix4.h"

namespace engine
{
    using namespace tools;
    Node::Node(void)
    {
        _parent = nullptr;
        _scale = Vec3(1.0f);
        _accumulativeScale = Vec3(1.0f);
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

    const Vec3 & Node::position(void) const
    {
        return _position;
    }

    void Node::rotate(const Vec3 & vSource)
    {
        _rotate = vSource;
        posterityWorldCoordinateInvalid();
    }

    const Vec3 & Node::rotate(void) const
    {
        return _rotate;
    }

    void Node::scale(const Vec3 & vSource)
    {
        _scale = vSource;
        posterityWorldCoordinateInvalid();
    }

    const Vec3 & Node::scale(void) const
    {
        return _scale;
    }

    const Vec3 Node::convertToWorldSpace(const Vec3 & vSource)
    {
        return calculateWorldCoordinate() + vSource.convertToSize3();
    }

    const Vec3 Node::convertToNodeSpace(const Vec3 & vSource)
    {
        return vSource - calculateWorldCoordinate().convertToSize3();
    }

    const Vec3 Node::calculateWorldCoordinate(void)
    {
        if(_worldCoordinateInvalid){
            return _worldCoordinate;
        }

        _worldCoordinate = _position;
        if(!_parent){
            return _worldCoordinate;
        }

        //世界坐标偏移
        Size3 worldCoordinateOffset = _parent->calculateWorldCoordinate() - Vec3(0.0f);

        //累计旋转   //累计缩放  //累计平移(也就是父级世界坐标)
        _accumulativeRotate = _parent->_accumulativeRotate + _parent->_rotate.convertToSize3();
        _accumulativeScale = _parent->_accumulativeScale * _parent->_scale;

        //旋转
        Matrix4 rotationMatrix = Matrix4::createRotationMatrix(_accumulativeRotate);
        //缩放
        Matrix4 scaleMatrix = Matrix4::createScaleMatrix(_accumulativeScale);
        //平移
        Matrix4 translationMatrix = Matrix4::createTranslationMatrix(worldCoordinateOffset);

        //累计旋转  × 累计缩放 ×  累计平移 × 局域坐标 = 模型世界坐标
        _worldCoordinate = rotationMatrix * scaleMatrix * translationMatrix * Vec4(_position, 1.0);

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
        calculateWorldCoordinate();

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