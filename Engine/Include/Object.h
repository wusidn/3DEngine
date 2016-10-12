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
        result->initializeError(1);\
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

        //获取可用状态
        const bool ready(void) const;
        //获取错误码 (0表示无错误)
        const unsigned short fault(void) const;
    protected:
        virtual const bool init(void);
        Object(void){}
        virtual ~Object(void){}

        void initializeError(const unsigned short errorCode);

    private:
        //引用次数
        int _quoteCount;

        //初始化错误码
        unsigned short _initializeErrorCode;
    };
}

#endif //__OBJECT_H__
