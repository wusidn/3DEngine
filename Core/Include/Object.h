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
    //
    int quoteCount;
public:
    //
    void retain(void);
    //
    void release(void);
    //
    void autoRelease(void);
protected:
    virtual const bool init(void);
    virtual ~Object(void);
};

#endif //__OBJECT_H__
