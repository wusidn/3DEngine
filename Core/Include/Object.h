#pragma once
#ifndef __OBJECT_H__
#define __OBJECT_H__

#define CREATEFUNC(class) static class * create(void)\
{\
   class * result = new class();\
   if(!result->init())\
   {\
        delete result;\
        result = nullptr;\
   }\
   return (class *)result;\
}\

class Object
{
    friend class Gc;
private:
    //引用次数
    int quoteCount;
public:
    //持久
    void retain(void);
    //释放
    void release(void);
    //自动管理
    void autoRelease(void);
protected:
    virtual const bool init(void);
    Object(void){}
    virtual ~Object(void){}
};

#endif //__OBJECT_H__
