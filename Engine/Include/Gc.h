#pragma once
#ifndef __GC_H__
#define __GC_H__

#include <list>
#include <iostream>
#include "Object.h"
using namespace std;

namespace engine
{    
    class Gc
    {
    public:
        //获取实例
        static Gc & getInstance(void);

        //销毁没有被引用的对象
        void clean(void);
        
        //加入管理对象池
        void watch(const Object &);
    protected:
        Gc(void);
    private:
        //对象池
        list<const Object *> * objectPool;
        static Gc * instance;
    };
}
#endif //__GC_H__
