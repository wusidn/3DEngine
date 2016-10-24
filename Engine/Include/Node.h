#pragma once
#ifndef __NODE_H__
#define __NODE_H__

#include "Object.h"
#include "Vec4.h"
#include "Matrix4.h"
// #include "World.h"

#include <vector>

using namespace std;

namespace engine
{
    class Camera;
    class Node : public Object
    {
        friend class World;
        friend class ScreenWorld;
        friend class Camera;
    public:
        
        CREATEFUNC(Node);

        //根元素
        Node & root(void);
        
        //父元素
        Node * parent(void) const;
        //所有子元素
        vector<Node *> & chidren(void);
        
        //添加子元素
        void append(Node & child);

        //删除子元素
        void remove(Node & child);
        
        //清空子元素
        void clear(void);

        //位置
        void position(const Vec3 & vSource);
        const Vec3 position(void) const;

        //旋转
        void rotate(const Vec3 & vSource);
        const Vec3 rotate(void) const;

        //缩放
        void scale(const Vec3 & vSource);
        const Vec3 scale(void) const;
        
        //将当前坐标转为世界坐标
        const Vec3 convertToWorldSpace(const Vec3 & vSource);
        //将世界坐标转换为当前坐标
        const Vec3 convertToNodeSpace(const Vec3 & vSource);
        
    protected:
        Node(void);
        virtual const bool init(void);
        //获取节点位置的世界坐标
        const Vec3 worldCoordinate(void);
        //标记世界坐标无效
        void worldCoordinateInvalid(void);

        //计算所有顶点的世界坐标系
        virtual const bool render(const int dt);

        //绘制
        virtual const bool draw(const Matrix4 & projection);
    private:

        //父元素
        Node * _parent;

        //子元素
        vector<Node *> _chidren;

        //矩阵变换
        Vec3 _position, _rotate, _scale;

        //世界坐标
        Vec3 _worldCoordinate;
        //世界坐标是否有效
        bool _worldCoordinateInvalid;

        //所有后代的世界坐标设为无效
        void posterityWorldCoordinateInvalid(void);
        
    };
}

#endif //__NODE_H__