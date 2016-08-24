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
        
        CREATEFUNC(Node);
        
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
        void position(const Vec4 & vSource);
        const Vec4 & position(void) const;

        //旋转
        void rotate(const Vec4 & vSource);
        const Vec4 & rotate(void) const;

        //缩放
        void scale(const Vec4 & vSource);
        const Vec4 & scale(void) const;
        
        //将当前坐标转为世界坐标
        const Vec4 convertToWorldSpace(const Vec4 & vSource) const;
        //将世界坐标转换为当前坐标
        const Vec4 convertToNodeSpace(const Vec4 & vSource) const;
        
    protected:
        Node(void);
        
        virtual const bool init(void);
    private:
        //父元素
        Node * _parent;

        //子元素
        vector<Node *> _chidren;

        //矩阵变换
        Vec4 _position, _rotate, _scale;
        
        virtual const bool render(const float dp);
    };
}

#endif //__NODE_H__