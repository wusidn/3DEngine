#pragma once
#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <cassert>
using namespace std;

#define NDEBUG

namespace engine
{
    #define CREATEFUNC(class) static class & create(void)\
    {\
    class * result = new class();\
    bool initRes = result->init();\
    \
    assert(initRes);\
    \
    if(!initRes)\
    {\
        result->_state = 1;\
    }\
    result->autoRelease();\
    return *(class *)result;\
    }\

    class Object
    {
        friend class Gc;
    public:
        //持久
        void retain(void);
        //释放
        void release(void);
        //自动管理
        void autoRelease(void);

        //可用状态
        const bool ready(void) const;
        //检查错误
        const unsigned short fault(void) const;
    protected:
        virtual const bool init(void);
        Object(void){}
        virtual ~Object(void){}

        //状态
        unsigned short _state;
    private:
        //引用次数
        int _quoteCount;
    };
}

#endif //__OBJECT_H__
